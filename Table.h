#ifndef _TABLE_H_
#define _TABLE_H_

#include <sys/resource.h>
#include <sys/time.h>
#include <unistd.h>
#include <vector>
#include <iostream>
#include <fstream>
#include <string>
#include <iomanip> // for setprecision
#include <stdio.h> // for strcat


#include "Column.h"
//#include "Intermediate.h"

using namespace std;

typedef struct inter_set{
    inter_set(){};
    vector<unsigned int> c1_records;
    vector<unsigned int> c2_records;
} inter_set;

/*
typedef struct Intermediate{
    Intermediate(){};
    void _Join(Table* t1, Column* c1, 
*/
// for sensors.csv, entities.csv
class Table {

    public:
        Table();
	Table(vector<string> table_info, int record_num_);
       ~Table();
       void getRecord(int index, bool EndLine=true);
       void getRecordWithColumn(int index);
       void getAllRecord(vector<int>* record_list=NULL);
       void printColName(bool EndLine = true); // refer column_name
       void getResult();
       void select(vector<int> column_list);
       void where(int table_num, int col_num, char op, string threshold);
       void where_and(int table_num, int col_num, char op, string threshold);
       void where_or(int table_num, int col_num, char op, string threshold);
       void Join(Table* t1, Table* t2, int c1, int c2, int printRecord, bool isFirst=true);
       void reset();
       //void materialize(Table* one, Table* two);
       //void getMemSize();
       //Table* materialize();
       
    //Column** column;
    //vector<Intermediate> inter;
    vector<Column*> column;
    vector<string> column_name;
    vector<string> column_type;
    string t_name;
    int record_num;
    int col_num;
    //about query
    vector<int> select_column;
    vector<int> where_row;
    vector<Table*> jointbl_ptr;
    vector<int> joincol_num;
    vector<vector<int>> record_set;

};

#endif
