#ifndef _COLUMN_H_
#define _COLUMN_H_

#include <iostream>
#include <vector>
#include <map>
#include <unordered_map>
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

typedef unordered_map<unsigned int, unsigned int> TransMap;
class Column {
    public:
    Column();
    Column(string column_name_, string column_type_, int record_num_, bool lossy=false);
    Column(const Column &obj); //shallow copy
    ~Column();
    
    void    		push_setdict(string val);
    void    		make_dict();
    void    		setDistinct();
    void    		make_arr();
    void    		fill_arr(int index, string val);
    void    		printMap();
    int	    		getColMemory();
    static TransMap 	makeHashTable(Column* c1, Column* c2);
    /*ABOUT ARRAY*/
    void    		getValue(int index, string &s, double &d, unsigned int &u, int &i);
    vector<int>		getIndexes(unsigned int right_val);
    unsigned int	getRawFromIndex(int index);
    /*ABOUT DICT*/
    unsigned int 	getRight(string left_val);
    string 		getLeft(unsigned int right_val);
    
    typedef boost::bimap<string, unsigned int> bimap_t;
    typedef boost::bimap<double, unsigned int> bimap_t2;
    typedef boost::bimap<unsigned int, unsigned int> bimap_t3;
    typedef boost::bimap<int, unsigned int> bimap_t4;
    bimap_t dict;
    bimap_t2 dict2;
    bimap_t3 dict3;
    bimap_t4 dict4;
    set<string> set_dict;
    set<double> set_dict2;
    set<unsigned int> set_dict3;
    set<int> set_dict4;

    PackedArray* data_arr; 
    int distinct_num=0;
    int bit_num;
    string column_name;
    int column_type;
    int record_num;
};
#endif
