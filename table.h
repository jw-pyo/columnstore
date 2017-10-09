#ifndef _TABLE_H_
#define _TABLE_H_

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <vector>
#include <set>
#include <tuple>
#include <utility>
#include <fstream>

#include "util.h"
#include "Column.h"
#include "DataArray.h"
using namespace std;

// for sensors.csv, entities.csv
template<typename T_1, typename T_2, typename T_3>
class Table_3 {

    public:
       Table_3<T_1, T_2, T_3> (string* table_col_namelist, int record_num_) {
	    name = table_col_namelist[1];
	    record_num = record_num_;
            col_0 = new Column<T_1>(table_col_namelist, record_num, 0);
            col_1 = new Column<T_2>(table_col_namelist, record_num, 1);
            col_2 = new Column<T_3>(table_col_namelist, record_num, 2);
	    
	    cout << "Create Table: " << name << endl;
        };

       ~Table_3<T_1, T_2, T_3> () {
    	    delete col_0;
	    delete col_1;
	    delete col_2;
	    cout << "Destructor Column: " << name << endl;

       };

    Column<T_1>* col_0;
    Column<T_2>* col_1;
    Column<T_3>* col_2;
    string name;
    int record_num;
};

template<typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13>
class Table_13 {
    public:
       Table_13<T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13> (string* table_col_namelist, int record_num_) {
	    name = table_col_namelist[1];
            record_num = record_num_;
	    col_0 = new Column<T1> (table_col_namelist, record_num, 0);
            col_1 = new Column<T2> (table_col_namelist, record_num, 1);
            col_2 = new Column<T3> (table_col_namelist, record_num, 2);
            col_3 = new Column<T4> (table_col_namelist, record_num, 3);
            col_4 = new Column<T5> (table_col_namelist, record_num, 4);
            col_5 = new Column<T6> (table_col_namelist, record_num, 5);
            col_6 = new Column<T7> (table_col_namelist, record_num, 6);
            col_7 = new Column<T8> (table_col_namelist, record_num, 7);
            col_8 = new Column<T9> (table_col_namelist, record_num, 8);
            col_9 = new Column<T10> (table_col_namelist,record_num, 9);
            col_10 = new Column<T11> (table_col_namelist, record_num, 10);
            col_11 = new Column<T12> (table_col_namelist, record_num, 11);
            col_12 = new Column<T13> (table_col_namelist, record_num, 12);

        };

    Column<T1>* col_0;
    Column<T2>* col_1;
    Column<T3>* col_2;
    Column<T4>* col_3;
    Column<T5>* col_4;
    Column<T6>* col_5;
    Column<T7>* col_6;
    Column<T8>* col_7;
    Column<T9>* col_8;
    Column<T10>* col_9;
    Column<T11>* col_10;
    Column<T12>* col_11;
    Column<T13>* col_12;
    string name;
    int record_num;
};

#endif
