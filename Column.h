#ifndef _COLUMN_H_
#define _COLUMN_H_

#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
#include <stdlib.h>
#include <math.h>
#include <typeinfo>
#include <sstream>

#include "EncodedDict.h"

typedef boost::bimap<bimaps::multiset_of<string>, bimaps::set_of<int>> bimap_t;
typedef bimap_t::value_type value_type;


using namespace std;



template <typename U>
struct CompareByMember {
        // This is a pointer-to-member, it represents a member of class T
    	// The data member has type U
 	 bool operator()(const U &lhs, const U &rhs) {
     	     return lhs < rhs;
		}
	};

template <typename T>
class Column {
    public:
	Column(string* table_info, int col_num_, bool lossy=false) {
	    
	//assume data are all in.
        //set_dict is already made.
        data_arr = PackedArray_create(bit, record_num);
	};

	~Column<T>() { 
	    set_dict.clear();
	    dict.clear();
	    PackedArray_destroy(data_arr);
	    cout << "Delete Column: " << name  << endl;
	};
    
    void    push_setdict(string val) {
        set_dict.insert(val);
    }
    
    void    make_dict(){
        int i=0;
        for(set<string>::iterator it=set_dict.begin(); it!=set_dict.end(); it++){
            dict.insert(value_type((*it), i++));
        }
    }

    void    fill_arr(int index, string val){
        for(int i=0; i<record_num; i++){
            PackedArray_set(data_arr, index, dict[val]);
            }
        }
    string  getValue(int index){
    	uint32_t ret;
    	PackedArray_get(data_arr, index, &ret);
	return dict.right.at(ret);
	}
	
    bimap_t dict;
    set<string> set_dict;
    PackedArray* data_arr; 
    int distinct_num=0;
    int bit_num;
};

#endif

