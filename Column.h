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
#include <boost/bimap.hpp>
#include "PackedArray.h"
using namespace std;



template <typename U>
struct CompareByMember {
        // This is a pointer-to-member, it represents a member of class T
    	// The data member has type U
 	 bool operator()(const U &lhs, const U &rhs) {
     	     return lhs < rhs;
		}
	};

//template <typename T>
class Column {
    public:
	Column(string column_name_, string column_type_, int record_num_, bool lossy=false) {
	    
	//assume data are all in.
        //set_dict is already made.
        record_num = record_num_;
	};

	~Column() { 
	    set_dict.clear();
	    dict.clear();
	    PackedArray_destroy(data_arr);
	    cout << "Delete Column: " << column_name  << endl;
	};
    
    void    push_setdict(string val) {
        set_dict.insert(val);
    }
    
    void    make_dict(){
        int i=0;
        for(set<string>::iterator it=set_dict.begin(); it!=set_dict.end(); it++){
            dict.insert({(*it), i++});
        }
    }

    void    setDistinct(){
        distinct_num = dict.size();
    }
   
    void    make_arr(){
        int bit = (int)ceil(log2(distinct_num));
        data_arr = PackedArray_create(bit, record_num);
    }


    void    fill_arr(int index, string val){
            PackedArray_set(data_arr, index, dict.left.at(val));
        }
    string  getValue(int index){
    	uint32_t ret;
    	ret = PackedArray_get(data_arr, index);
	    return dict.right.at((int)ret);
	}
	
    typedef boost::bimap<string, int> bimap_t;
    //typedef bimap_t::value_type value_type;
    bimap_t dict;
    set<string> set_dict;
    PackedArray* data_arr; 
    int distinct_num=0;
    int bit_num;
    string column_name;
    string column_type;
private:
    int record_num;
};

#endif

