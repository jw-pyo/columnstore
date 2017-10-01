#include "Table.h"
#include "Column.h"
#include "util.h"

#include <stdio.h>
#include <vector>
#include <fstream>

using namespace std;

int main(){

string sensors_name[4] = {"sensors", "SID", "EID", "TYPE"};
Table<uint32_t, uint32_t, uint32_t>* sensors = new Table<uint32_t, uint32_t, uint32_t>(sensors_name, "data/sensors.csv", 42);
sensors->col_1.print();    
sensors->col_3.print_set();
return 0;
}
