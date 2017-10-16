#ifndef _TABLE_CPP_
#define _TABLE_CPP_

#include "Table.h"

using namespace std;

Table::Table(string* table_info, int record_num_){
    //set the metadata
    string datapath = table_info[0];
    t_name = table_info[1];
    record_num = record_num_;
    for(int i=2; i<table_info->size(); i+=2){
        column_name.push_back(table_info[i]);
        column_type.push_back(table_info[i+1]);
    }
    col_num = column_name.size();

    //allocate the column
    //**column = new Column*[col_num];
    
    for(int i=0; i<col_num; i++){
        column.push_back(new Column(column_name[i], column_type[i], record_num, false));
    }
    //input data
    ifstream dataFile(table_info[0]);
    string line;
    //make set(unique, sorted) : 1 read
    //for(int i=0; getline(line, dataFile); i++){
    while(getline(dataFile, line)){
        string* records = strSplit(line, ",");
        for(int j=0; j<col_num; j++){
            column[j]->push_setdict(records[j]);
        }
    }
    //make dictionary
    for(int j=0; j<col_num; j++){
        column[j]->setDistinct();
        column[j]->make_dict();
        column[j]->make_arr();
    }
    //make packed array : 2 read
    for(int i=0; getline(dataFile, line); i++){
    //while(getline(line, dataFile)){
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
    column.clear();
    column_name.clear();
    column_type.clear();
};

void Table::getRecord(int index) {
    for(int j=0; j<col_num-1; j++) {
	cout<< column[j]->getValue(index) << "|" ;
    }
    cout << column[col_num - 1]->getValue(index) << endl;
};

void Table::getMemSize() {};

#endif
