#ifndef _COLUMN_H_
#define _COLUMN_H_

#include <iostream>
#include <vector>
#include <map>
#include <stdlib.h>
#include <boost/bimap.hpp>
#include <sstream>

#include "PackedArray.h"
#include "util.h"
using namespace std;

enum {
    STRING,
    DOUBLE,
    UINT,
    INT
};

//template <typename T>
class Column {
    public:
	Column(string column_name_, string column_type_, int record_num_, bool lossy=false);
	~Column();
    void    push_setdict(string val);
    void    make_dict();
    void    setDistinct();
    void    make_arr();
    void    fill_arr(int index, string val);
    void    getValue(int index, string &s, double &d, unsigned int &u, int &i);
    void    printMap();
    
    typedef boost::bimap<string, unsigned int> bimap_t1;
    typedef boost::bimap<double, unsigned int> bimap_t2;
    typedef boost::bimap<unsigned int, unsigned int> bimap_t3;
    typedef boost::bimap<int, unsigned int> bimap_t4;
    //typedef bimap_t::value_type value_type;
    bimap_t1 dict1;
    bimap_t2 dict2;
    bimap_t3 dict3;
    bimap_t4 dict4;
    set<string> set_dict1;
    set<double> set_dict2;
    set<unsigned int> set_dict3;
    set<int> set_dict4;

    PackedArray* data_arr; 
    int distinct_num=0;
    int bit_num;
    string column_name;
    int column_type;
private:
    int record_num;
};
#endif
