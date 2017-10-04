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
#include "DataArray.h"

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
	
	Column<T>()	{};
	
	Column<T>(string name_, int record_num_)	{
	    name = name_;
	    record_num = record_num_;
	};

	~Column<T>()	{ 
	    sdict.clear();
	    cout << "Column " << name << " is free from memory." << endl;
	};

	void	push_back(T& val) {
	    if(sdict.count(val) <= 0) sdict.insert(pair<T, int>(val, distinct_num++));
	    else;
	};
	void	make_edict(DataColumn<T> raw_col) {
	    distinct_num = sdict.size();
	    bit_num = (int)floor(log2((double)distinct_num)); //think about null value
	    edict = new EncodedDict<T>(raw_col, sdict, bit_num, record_num);
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
	
	void	print_sdict() {
	    cout << name << " column(eliminate dup):" << endl;
	    int i = 0;
	    for(typename map<T, int>::iterator itr = sdict.begin(); itr != sdict.end(); ++itr) {
		cout << "Column[" << i << "]: " << *itr << endl;
		i++; }
	};

	/*void sort() {
	    std::sort(m_col.begin(), m_col.end(), CompareByMember<T>());
	};*/

	void print_max() {
	    cout << name << ": max value is " << *m_set.rbegin() << endl;
	}

	int get_index(T& val) {
	}

	
	set<T> m_set; //the real data of eliminating duplication
	map<T, int> sdict;
	EncodedDict<T>* edict; // eliminate duplication, 
	int record_num;
	int distinct_num=0;
	int bit_num;
	string name;
};

#endif

