//#include "table.h"
#include "Column.h"
#include "util.h"
#include <stdio.h>
#include <vector>
#include <fstream>

using namespace std;



int main(){

string[4] sensors_name = {"sensors", "SID", "EID", "TYPE"};

Column<int>* col = new Column<int>("sensors", 126);
ifstream dataFile("data/sensors.csv");
string line;

while(getline(dataFile, line))
            {
	       string* line_arr = strSplit(line, ",");
	       col->push_back(stoi(line_arr[0]));
	    }		 
col->push_back("anifjief");
col->push_back("cbcijjpofd");
col->push_back("bcvd");
col->push_back("bcvd");
col->print();
col->print_set();
printf("%lu\n", sizeof(*col));

col->sort();
col->print();

printf("After sorting: %lu\n", sizeof(*col));
col->optimize();
printf("After optimizing: %lu\n", sizeof(*col));


delete col;
    return 0;
}
