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
#include <math.h> //for floor, ceil
#include <mutex>
#include <thread>
#include <chrono>
#include "Column.h"
//#include "Intermediate.h"

using namespace std;
using namespace std::chrono;
typedef struct inter_set{
    inter_set(){};
    vector<int> c1_records;
    vector<int> c2_records;
} inter_set;

static int static_i=0;
/*
typedef struct Intermediate{
    Intermediate(){};
    void _Join(Table* t1, Column* c1, 
*/
class Table {

    public:
        Table();
	Table(vector<string> table_info, int record_num_);
       ~Table();
       /*----LOADING & PRINT FUNCTION----*/
       void getRecord(int index, bool EndLine=true);
       void getRecordWithColumn(int index);
       void getAllRecord(vector<int>* record_list=NULL);
       void printColName(bool EndLine = true); // refer column_name
       void getResult(int recordNumber);
       
       /*----ABOUT QUERIES----*/
       //void putJoinTable(Table* t, int col);
       //void outJoinTable();
       void where_or(int table_num, int col_num, char op, string threshold); //DEPRECATED
       void select(vector<int> column_list);
       void where(int table_num, int col_num, char op, string threshold);
       void where_and(int table_num, int col_num, char op, string threshold);
       void Join(Table* t1, Table* t2, int c1, int c2, bool isFirst=true);
       void PartitionJoin(Table* t1, Table* t2, int c1, int c2);
       void firstCallback(TransMap& transmap, map<unsigned int, inter_set>& mid_storage, Table* t1, int c1, int no);
       void secondCallback(map<unsigned int, inter_set>& mid_storage, int no);
       
       /*----ABOUT INFO----*/ 
       void reset();
       void getTblMemory();
       //Table* materialize();
       
    
    /*----MEMBER VARIABLES----*/
    vector<Column*> column;
    vector<string> column_name;
    vector<string> column_type;
    string t_name;
    int record_num;
    int col_num;
    bool isEmpty;
    mutex mtx;
    /*----ABOUT QUERY & INTERMEDIATE REPRESENTATION----*/
    vector<int> select_column;
    vector<int> where_row;
    vector<Table*> jointbl_ptr;
    vector<int> joincol_num;
    vector<vector<int>> record_set;

};

#endif
