//#include "table.h"
#include "Column.h"
#include <stdio.h>
int main(){

   /* 
  Column<int> col_int(5);
  col_int.items[0]= 2;
  col_int.items[1]= 4;
  col_int.items[2]= 5;
  col_int.items[3]= 6;
  col_int.items[4]= 7;
  for(int i=0; i<5; i++)
  printf("%d\n", col_int.items[i]);
*/

    // EID(u), NAME, TYPE
//    Table<int(autoincrement), std::string, std::uint32_t> t_entities ("data/entities.csv");
    // SID(u), EID, TYPE
//Table<std::uint32_t, std::uint32_t, std::uint32_t> t_sensors ("data/sensors.csv");
    // SID(u), TS, X, Y, Z, V, A, VX, VY, VZ, AX, AY, AZ
//    Table<std::uint32_t, double, int, int, int, std::uint32_t, std::uint32_t, int, int, int, int, int, int> t_events ("data/full-game.csv");
//int a[] = {0,0,0,3,4,5,5,56,6,6};

//SortedDict s_d(a);
//printf(s_d.encoded_dict);

Column<std::string> col = Column<std::string>("testcolumn");
col.push_back("anifjief");
col.push_back("cbcijjpofd");
col.push_back("bcvd");

col.print();
printf("%lu\n", sizeof(col));

col.sort();
col.print();
    return 0;
}
