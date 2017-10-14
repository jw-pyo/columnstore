#ifndef _TABLE_CPP_
#define _TABLE_CPP_

#include "Table.h"

using namespace std;
Table::Table(string* table_info)  {
    //set the metadata
    datapath = table_info[0];
    t_name = table_info[1];
    for(int i=2; i<table_info.size(); i+=2){
        column_name.push_back(table_info[i]);
        column_type.push_back(table_info[i+1]);
    }
    col_num = column_name.size();

    //allocate the column
    *column = new Column*[col_num];

    for(int i=0; i<col_num; i++){
        column[i] = new Column(column_name[i], column_type[i]);
    }
    //input data
    ifstream dataFile(table_info[0]);
    string line;
    //make set(unique, sorted)
    for(int i=0; getline(line, dataFile), i++){
        string* records = strSplit(line, ",");
        for(int j=0; j<col_num; j++){
            column[j]->push_setdict(records[j]);
        }
    }
    //make dictionary
    for(int j=0; j<col_num; j++){
        column[j]->make_dict();
    }
    //make packed array
    for(int i=0; getline(line, dataFile), i++){
        string* records = strSplit(line, ",");
        for(int j=0; j<col_num; j++){
            column[j]->fill_arr(i, records[j]);
        }
    }



};


Table::~Table() {
    for(int i=0; i<col_num; i++){
        delete column[i];
    }
    delete column_num;
    column_name.clear();
    column_type.clear();

};


void Table::getMemSize() {};

#endif
