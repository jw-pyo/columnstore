#ifndef _DATAARRAY_H_
#define _DATAARRAY_H_
#include <fstream>
#include <string>
#include <stdlib.h>
#include "util.h"

using namespace std;
template<typename T>
struct DataColumn {
    public:
        DataColumn<T>()	{};	
	DataColumn<T> (string name, int record_num) {
	    this->name = name;
	    this->record_num = record_num;
	    value = (T*)malloc(sizeof(T)*record_num);
	}
	
	T* value;
	int record_num;
	string name;

};

template<typename T_1, typename T_2, typename T_3>
class DataArray_3 {

    public:
       DataArray_3<T_1, T_2, T_3> (string* table_col_namelist, string data, int num) {
	    name = table_col_namelist[0];
            record_num = num;
	    rawcol_1 = DataColumn<T_1> (table_col_namelist[1], num);
            rawcol_2 = DataColumn<T_2> (table_col_namelist[2], num);
            rawcol_3 = DataColumn<T_3> (table_col_namelist[3], num);

	    ifstream dataFile(data);
	    string line;
	    int i=0;
	    while(getline(dataFile, line))
            {
	       string* line_arr = strSplit(line, ",");
	       rawcol_1.value[i] = convert_to<T_1>(line_arr[0]);
	       rawcol_2.value[i] = convert_to<T_2>(line_arr[1]);
	       rawcol_3.value[i] = convert_to<T_3>(line_arr[2]);
	       i++;
	    }		 
        };

        ~DataArray_3<T_1, T_2, T_3> () {
	    delete rawcol_1.value;
	    delete rawcol_2.value;
	    delete rawcol_3.value;
	};

    DataColumn<T_1> rawcol_1;
    DataColumn<T_2> rawcol_2;
    DataColumn<T_3> rawcol_3;
    string name;
    int record_num;
};

template<typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13>
class DataArray_13 {

    public:
       DataArray_13<T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13> (string* table_col_namelist, string data, int num) {
	    name = table_col_namelist[0];
            record_num = num;
	    rawcol_1 = DataColumn<T1> (table_col_namelist[1], num);
            rawcol_2 = DataColumn<T2> (table_col_namelist[2], num);
            rawcol_3 = DataColumn<T3> (table_col_namelist[3], num);
            rawcol_4 = DataColumn<T4> (table_col_namelist[4], num);
            rawcol_5 = DataColumn<T5> (table_col_namelist[5], num);
            rawcol_6 = DataColumn<T6> (table_col_namelist[6], num);
            rawcol_7 = DataColumn<T7> (table_col_namelist[7], num);
            rawcol_8 = DataColumn<T8> (table_col_namelist[8], num);
            rawcol_9 = DataColumn<T9> (table_col_namelist[9], num);
            rawcol_10 =DataColumn<T10> (table_col_namelist[10], num);
            rawcol_11 =DataColumn<T11> (table_col_namelist[11], num);
            rawcol_12 =DataColumn<T12> (table_col_namelist[12], num);
            rawcol_13 =DataColumn<T13> (table_col_namelist[13], num);

	    ifstream dataFile(data);
	    string line;
	    int i=0;
	    while(getline(dataFile, line))
            {
	       string* line_arr = strSplit(line, ",");
	       rawcol_1.value[i] = convert_to<T1>(line_arr[0]);
	       rawcol_2.value[i] = convert_to<T2>(line_arr[1]);
	       rawcol_3.value[i] = convert_to<T3>(line_arr[2]);
	       rawcol_4.value[i] = convert_to<T4>(line_arr[3]);
	       rawcol_5.value[i] = convert_to<T5>(line_arr[4]);
	       rawcol_6.value[i] = convert_to<T6>(line_arr[5]);
	       rawcol_7.value[i] = convert_to<T7>(line_arr[6]);
	       rawcol_8.value[i] = convert_to<T8>(line_arr[7]);
	       rawcol_9.value[i] = convert_to<T9>(line_arr[8]);
	       rawcol_10.value[i] = convert_to<T10>(line_arr[9]);
	       rawcol_11.value[i] = convert_to<T11>(line_arr[10]);
	       rawcol_12.value[i] = convert_to<T12>(line_arr[11]);
	       rawcol_13.value[i] = convert_to<T13>(line_arr[12]);
	       i++;
	    }

        };

        ~DataArray_13<T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13> () {
	    delete rawcol_1.value;
	    delete rawcol_2.value;
	    delete rawcol_3.value;
	    delete rawcol_4.value;
	    delete rawcol_5.value;
	    delete rawcol_6.value;
	    delete rawcol_7.value;
	    delete rawcol_8.value;
	    delete rawcol_9.value;
	    delete rawcol_10.value;
	    delete rawcol_11.value;
	    delete rawcol_12.value;
	    delete rawcol_13.value;
	};
    DataColumn<T1> rawcol_1;
    DataColumn<T2> rawcol_2;
    DataColumn<T3> rawcol_3;
    DataColumn<T4> rawcol_4;
    DataColumn<T5> rawcol_5;
    DataColumn<T6> rawcol_6;
    DataColumn<T7> rawcol_7;
    DataColumn<T8> rawcol_8;
    DataColumn<T9> rawcol_9;
    DataColumn<T10> rawcol_10;
    DataColumn<T11> rawcol_11;
    DataColumn<T12> rawcol_12;
    DataColumn<T13> rawcol_13;
    string name;
    int record_num;
};

#endif
