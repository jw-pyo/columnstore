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
	    
	    // make sdict
	    /*ifstream dataFile(table_col_namelist[0]);
	    string line;
	    int i=0;
	    while(getline(dataFile, line))
            {
	       string* line_arr = strSplit(line, ",");
	       col_0->push_back(convert_to<T_1>(line_arr[0]));
	       col_1->push_back(convert_to<T_2>(line_arr[1]));
	       col_2->push_back(convert_to<T_3>(line_arr[2]));
	       i++;
	    }

	    assert(i==record_num);
*/
	    // make sdict
	    /*for(int i=0; i<num; i++)
            {
	       col_1.push_back(data_array->rawcol_1.value[i]);
	       col_2.push_back(data_array->rawcol_2.value[i]);
	       col_3.push_back(data_array->rawcol_3.value[i]);
	    }*/
	    // make edict
/*		col_0->make_edict(table_col_namelist, 0);
		col_1->make_edict(table_col_namelist, 1);
		col_2->make_edict(table_col_namelist, 2);*/
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

       Table_13<T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13> (string* table_col_namelist, string data, int num) {
	    name = table_col_namelist[0];
            col_1 = Column<T1> (table_col_namelist[1], num);
            col_2 = Column<T2> (table_col_namelist[2], num);
            col_3 = Column<T3> (table_col_namelist[3], num);
            col_4 = Column<T4> (table_col_namelist[4], num);
            col_5 = Column<T5> (table_col_namelist[5], num);
            col_6 = Column<T6> (table_col_namelist[6], num);
            col_7 = Column<T7> (table_col_namelist[7], num);
            col_8 = Column<T8> (table_col_namelist[8], num);
            col_9 = Column<T9> (table_col_namelist[9], num);
            col_10 = Column<T10> (table_col_namelist[10], num);
            col_11 = Column<T11> (table_col_namelist[11], num);
            col_12 = Column<T12> (table_col_namelist[12], num);
            col_13 = Column<T13> (table_col_namelist[13], num);

	    ifstream dataFile(data);
	    string line;
	    while(getline(dataFile, line))
            {
	       string* line_arr = strSplit(line, ",");
	       col_1.push_back(convert_to<T1>(line_arr[0]));
	       col_2.push_back(convert_to<T2>(line_arr[1]));
	       col_3.push_back(convert_to<T3>(line_arr[2]));
	       col_4.push_back(convert_to<T4>(line_arr[3]));
	       col_5.push_back(convert_to<T5>(line_arr[4]));
	       col_6.push_back(convert_to<T6>(line_arr[5]));
	       col_7.push_back(convert_to<T7>(line_arr[6]));
	       col_8.push_back(convert_to<T8>(line_arr[7]));
	       col_9.push_back(convert_to<T9>(line_arr[8]));
	       col_10.push_back(convert_to<T10>(line_arr[9]));
	       col_11.push_back(convert_to<T11>(line_arr[10]));
	       col_12.push_back(convert_to<T12>(line_arr[11]));
	       col_13.push_back(convert_to<T13>(line_arr[12]));
	    }		 
        };

    Column<T1> col_1;
    Column<T2> col_2;
    Column<T3> col_3;
    Column<T4> col_4;
    Column<T5> col_5;
    Column<T6> col_6;
    Column<T7> col_7;
    Column<T8> col_8;
    Column<T9> col_9;
    Column<T10> col_10;
    Column<T11> col_11;
    Column<T12> col_12;
    Column<T13> col_13;
    string name;
};
/*
int main(int argc, char* argv[]) {
    // EID(u), NAME, TYPE
//    Table<int(autoincrement), std::string, std::uint32_t> t_entities ("data/entities.csv");
    // SID(u), EID, TYPE
//    Table<std::uint32_t, std::uint32_t, std::uint32_t> t_sensors ("data/sensors.csv");
    // SID(u), TS, X, Y, Z, V, A, VX, VY, VZ, AX, AY, AZ
//    Table<std::uint32_t, double, int, int, int, std::uint32_t, std::uint32_t, int, int, int, int, int, int> t_events ("data/full-game.csv");

  Column<int> col_int(5);
  col_int.items= {2,4,5,6,7};
  for(int i=0; i<5; i++)
  printf("%d\n", col_int.items[i]);
  return 0;
    }
    */


#endif
