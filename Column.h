#ifndef _COLUMN_H_
#define _COLUMN_H_

#include <iostream>
#include <vector>
#include <set>
#include <map>
#include <algorithm>
#include <stdlib.h>
#include <math.h>
#include <typeinfo>

#include "EncodedDict.h"
//#include "DataArray.h"

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
	Column<T>(string* table_col_namelist, int record_num_, int col_num_)	{
	    name = table_col_namelist[col_num_ + 2];
	    record_num = record_num_;
	    col_num = col_num_;
	    //data input
	    ifstream dataFile(table_col_namelist[0]);
	    string line;
	    int i = 0;
	    while(getline(dataFile, line)){
	    	string* line_arr = strSplit(line,",");
		push_back(line_arr[col_num]);
		i++; 
	    }

	    assert(i == record_num);
	   // make encoded dictionary
	    make_edict(table_col_namelist);

	};

	~Column<T>()	{ 
	    sdict.clear();
	    delete edict;
	    cout << "Delete Column: " << name  << endl;
	};

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
	
	void	print_info() {
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
	
	map<string, int> sdict;
	typename map<string, int>::iterator itr;
	EncodedDict* edict; // eliminate duplication, 
	int record_num;
	int col_num;
	int distinct_num=0;
	int bit_num;
	string name;
};

#endif

