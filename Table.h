#ifndef _TABLE_H_
#define _TABLE_H_

#include <sys/resource.h>
#include <sys/time.h>
#include <unistd.h>
#include <vector>
#include <iostream>
#include <fstream>
#include <string>
#include <boost/variant.hpp>

#include "util.h"
#include "Column.h"

using namespace std;

// for sensors.csv, entities.csv
class Table {

    public:
       Table (string* table_info, int record_num_);
       ~Table ();
       void getRecord(int index);
       void getMemSize();

    //Column** column;
    vector<Column*> column;
    vector<string> column_name;
    vector<string> column_type;
    string t_name;
    int record_num;
    int col_num;

};
/*
template<typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13>
class Table_13 {
    public:
       Table_13<T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13> (string* table_col_namelist, int record_num_) {
	    name = table_col_namelist[1];
            record_num = record_num_;
	    col_0 = new Column<T1> (table_col_namelist, record_num, 0);
	    struct rusage usage;
	    struct timeval start, end;

	    getrusage(RUSAGE_SELF, &usage);
	    unsigned int a  = usage.ru_maxrss/1024/1024;
            col_1 = new Column<T2> (table_col_namelist, record_num, 1, false);
	    getrusage(RUSAGE_SELF, &usage);
	    unsigned int b = usage.ru_maxrss/1024/1024;
	    cout <<"Performance of TS column: " << b - a << "Mbytes." << endl;
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

       ~Table_13<T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13> () {
    	    delete col_0;
	    delete col_1;
	    delete col_2;
    	    delete col_3;
	    delete col_4;
	    delete col_5;
    	    delete col_6;
	    delete col_7;
	    delete col_8;
    	    delete col_9;
	    delete col_10;
	    delete col_11;
	    delete col_12;
	    cout << "Destructor Column: " << name << endl;

       };
      void get_row(int index){
      
      cout << "record[" << index << "]: " << col_0->edict->get_record(index) << "|" <<
	  col_1->edict->get_record(index) << "|" <<
	  col_2->edict->get_record(index) << "|" <<
	  col_3->edict->get_record(index) << "|" <<
	  col_4->edict->get_record(index) << "|" <<
	  col_5->edict->get_record(index) << "|" <<
	  col_6->edict->get_record(index) << "|" <<
	  col_7->edict->get_record(index) << "|" <<
	  col_8->edict->get_record(index) << "|" <<
	  col_9->edict->get_record(index) << "|" <<
	  col_10->edict->get_record(index) << "|" <<
	  col_11->edict->get_record(index) << "|" <<
	  col_12->edict->get_record(index) << endl;
      
      
      };
      void sid_40(){
       cout << "SID = 40, rowcount and top 20 rows " << endl;
       cout << "================================== " << endl;
       vector<int> index_set;
       unsigned int encoded = (unsigned int)(col_0->sdict["40"]);
       for(int i=0; i < record_num; i++)
       	{
	    unsigned int enc = (unsigned int)(col_0->edict->get_encodedbit8(col_0->edict->contents_8, i));
	    if (encoded == enc)
	    {
		index_set.push_back(i);
		if(index_set.size() <20)
		{
		   get_row(i);
	    }
	    }
	}
        cout << "rowcount: " << index_set.size() << endl;
       cout << "================================== " << endl;
	index_set.clear();
       
    };
      void v_less_5000000(){
       cout << "V < 5,000,000, rowcount and top 20 rows " << endl;
       cout << "================================== " << endl;
       vector<int> index_set;
       unsigned int encoded = (unsigned int)col_5->sdict["5000000"];
       for(int i=0; i < record_num; i++)
       	{
	    unsigned int enc = (unsigned int)col_5->edict->get_encodedbit32(col_5->edict->contents_32, i);
	    if (enc < encoded)
	    {
		index_set.push_back(i);
		//if(index_set.size() == 0)
		//{
		//    get_row(i);
	    //}
	    }
	}
        cout << "rowcount: " << index_set.size() << endl;
       cout << "================================== " << endl;
       
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
*/
#endif
