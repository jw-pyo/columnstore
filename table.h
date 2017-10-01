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
using namespace std;


template<typename T1, typename T2, typename T3>
class Table {

    public:
       Table<T1, T2, T3> (string* table_col_namelist, string data, int num) {
	    name = table_col_namelist[0];
            col_1 = Column<T1> (table_col_namelist[1], num);
            col_2 = Column<T2> (table_col_namelist[2], num);
            col_3 = Column<T3> (table_col_namelist[3], num);

	    ifstream dataFile(data);
	    string line;
	    while(getline(dataFile, line))
            {
	       string* line_arr = strSplit(line, ",");
	       col_1.push_back(convert_to<T1>(line_arr[0]));
	       col_2.push_back(convert_to<T2>(line_arr[1]));
	       col_3.push_back(convert_to<T3>(line_arr[2]));
	    }		 
        };

    Column<T1> col_1;
    Column<T2> col_2;
    Column<T3> col_3;
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
