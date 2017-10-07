#ifndef _COLUMN_H_
#define _COLUMN_H_

#include <iostream>
#include <vector>
#include <set>
#include <map>
#include <algorithm>
#include <stdlib.h>
#include <math.h>

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

	    ifstream dataFile(table_col_namelist[0]);
	    string line;
	    int i = 0;
	    while(getline(dataFile, line)){
	    	string* line_arr = strSplit(line, ",");
		push_back(convert_to<T>(line_arr[col_num]));
	   	i++; 
	    }

	    assert(i == record_num);

	    make_edict(table_col_namelist);

	};

	~Column<T>()	{ 
	    sdict.clear();
	    delete edict;
	    cout << "Column " << name << " is free from memory." << endl;
	};

	void	push_back(T val) {
	    if(sdict.count(val) > 0) {}
	    else{
		sdict.insert(pair<T, int>(val, distinct_num++));
	    }
	};
	void	make_edict(string* table_col_namelist_) {
	    distinct_num = sdict.size();
	    bit_num = (int)floor(log2((double)distinct_num)); //think about null value
	    edict = new EncodedDict<T>(table_col_namelist_, sdict, col_num, bit_num, record_num);
	    //return edict;
	    //edict.make_contents(raw_col);
	    //edict.print_edict();
	}

	/*void	allocate_sdict()  { //DEPRECATED
	    sdict = (T*)malloc(distinct_num * sizeof(T));
	    int i = 0;
	    for(typename set<T>::iterator itr = m_set.begin(); itr != m_set.end(); ++itr) {
		sdict[i] = *itr;
		cout << sdict[i] << endl;
		i++;
	    }	
	};*/
	
	/*void	print() {
	    cout << name << " column:" << endl;
	    int i = 0;
	    for(typename vector<T>::iterator itr = m_col.begin(); itr != m_col.end(); itr++) {
		cout << "Column[" << i << "]: " << *itr << endl;
		i++; }
	};*/
	
	void	print_info() {
	    cout << "=============================" << endl;
	    cout << "'" << name << "' sdict is ... " << endl;
	    for(typename map<T, int>::iterator itr = sdict.begin(); itr != sdict.end(); ++itr) {
		cout << "sdict[" << (*itr).first << "]: " << (*itr).second << endl;
		 }
	    cout << "\ndistinct_num: " << distinct_num << endl;
	    cout << "=============================" << endl;

	};

	void print_max() {
	}
	
	map<T, int> sdict;
	typename map<T, int>::iterator it;
	EncodedDict<T>* edict; // eliminate duplication, 
	int record_num;
	int col_num;
	int distinct_num=0;
	int bit_num;
	string name;
};

#endif

