#ifndef _COLUMN_H_
#define _COLUMN_H_

#include <iostream>
#include <vector>
#include <set>
#include <algorithm>
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
	
	Column<T>()	{};
	
	Column<T>(string name_, int record_num_)	{
	    name = name_;
	    record_num = record_num_;
	    m_col.reserve(record_num);
	};

	~Column<T>()	{ 
	    m_col.clear();
	    cout << "Column " << name << " is free from memory." << endl;
	};

	void	push_back(T val) {
	    m_col.push_back(val);
	    m_set.insert(val);
	};

	void	print() {
	    cout << name << " column:" << endl;
	    int i = 0;
	    for(typename vector<T>::iterator itr = m_col.begin(); itr != m_col.end(); itr++) {
		cout << "Column[" << i << "]: " << *itr << endl;
		i++; }
	};
	
	void	print_set() {
	    cout << name << " column(eliminate dup):" << endl;
	    int i = 0;
	    for(typename set<T>::iterator itr = m_set.begin(); itr != m_set.end(); ++itr) {
		cout << "Column[" << i << "]: " << *itr << endl;
		i++; }
	};

	void sort() {
	    std::sort(m_col.begin(), m_col.end(), CompareByMember<T>());
	};
	// optimize: delete m_col after making m_set
	void optimize() {
	    m_col.clear();
	
	};
	
	vector<T> m_col; // real data Column
	set<T> m_set; //the real data of eliminating duplication
	EncodedDict* e_dict; // eliminate duplication, 
	string name;
	int record_num;
};

#endif

