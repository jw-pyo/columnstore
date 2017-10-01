#ifndef _COLUMN_H_
#define _COLUMN_H_

#include <iostream>
#include <vector>
#include <algorithm>

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
	Column<T>(string name_)	{ name = name_; };
	virtual ~Column<T>()	{ m_col.clear(); };
	void	push_back(T val) { m_col.push_back(val); };
	void	print() {
	    cout << name << " column:" << endl;
	    int i = 0;
	    for(typename vector<T>::iterator itr = m_col.begin(); itr != m_col.end(); itr++) {
		cout << "Column[" << i << "]: " << *itr << endl;
		i++; }
	};

	void sort() {
	    std::sort(m_col.begin(), m_col.end(), CompareByMember<T>());
	}
	







	vector<T> m_col;
	string name;
};

#endif

