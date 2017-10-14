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
	Column(string* table_info, int col_num_, bool lossy=false)	{
	    
	    //assume data are all in.
        //set_dict is already made.
        data_arr = PackedArray_create(bit, record_num);
	    
	    }


	};

	~Column<T>()	{ 
	    sdict.clear();
	    delete edict;
	    cout << "Delete Column: " << name  << endl;
	};
    
    void    push_setdict(string val) {
        set_dict.insert(val);
    }
    
    void    make_dict(){
        int i=0;
        for(set<string>::iterator it=set_dict.begin(); it!=set_dict.end(); it++){
            dict.insert(pair<string, int>((*it), i++);
        }
    }

    void    fill_arr(int index, string val){
        for(int i=0; i<record_num; i++){
            PackedArray_set(data_arr, index, dict[val]);
            }
        }



	void	push_back(string val) {
	    //it is used for making sorted dictionary.
	    
	    if(sdict.count(val) > 0) {}
	    else{
		sdict.insert(pair<string, int>(val, distinct_num++));
	    //	cout << "in sdict: " << val << "   " << (distinct_num - 1) << endl;
	    }
	};

	void	make_edict(string* table_col_namelist_) {
	    // it is used for making packed-encoded array
	    //
	    bit_num = (int)ceil(log2(distinct_num)); //think about null value
	    edict = new EncodedDict(table_col_namelist_, sdict, col_num, bit_num, record_num);
	}
	
	/*void	print() {
	    cout << name << " column:" << endl;
	    int i = 0;
	    for(typename vector<T>::iterator itr = m_col.begin(); itr != m_col.end(); itr++) {
		cout << "Column[" << i << "]: " << *itr << endl;
		i++; }
	};*/
	
	void	print_sdict() {
	    cout << "=============================" << endl;
	    cout << "\'" << name << "\' sdict is ... " << endl;
	    for(itr = sdict.begin(); itr != sdict.end(); ++itr) {
		cout << "sdict[" << (*itr).first << "]: " << (*itr).second << endl;
		 }
	    cout << "\ndistinct_num: " << distinct_num << endl;
	    cout << "=============================" << endl;

	};

	void print_max() {
	}

	int get_size(){
	    int size_ = sizeof(sdict) + sizeof(int)*4 + name.size();
	    size_ += edict->get_size();
	    return size_;
	}

	/*vector<int> equal(T val){
	    ostringstream oss;
	    oss << val;
	    string val_ = oss.str();
	    vector<int> ret;
	    for(int i=0; i<record_num; i++)
	    {
		if(val_ == edict->get_record(i))
		{
		    ret.push_back(i);
		}
	    }
	    
	    return ret;
	
	}*/

	map<string, int> dict;
    set<string> set_dict;
	PackedArray* data_arr; 
	int distinct_num=0;
	int bit_num;
};

#endif

