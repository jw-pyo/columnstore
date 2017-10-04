#ifndef _ENCODEDDICT_H_
#define _ENCODEDDICT_H_

#include <iostream>
#include <vector>
#include <algorithm>
#include <map>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <bitset>
#include <boost/dynamic_bitset.hpp>

#include "PackedArray.h"
#include "DataArray.h"

using namespace std;




template<typename T>
class EncodedDict {
    public:
	EncodedDict<T> (DataColumn<T> raw_col, map<T, int> sdict, int bit_num_, int record_num_)	{
	    bit_num = bit_num_;
	    record_num = record_num_;
	    int total_bit = bit_num * record_num;
	    contents = PackedArray_create((uint32_t)bit_num, (uint32_t)record_num);

	    for(int i=0; i<raw_col.record_num; i++) {
		PackedArray_set(contents, i, raw_col.value[i]); 
	
	    }

	    cout << "Print Encoded Dictionary" << endl;
	    cout << contents << endl;
	    cout << "Encoded size is " << sizeof(contents) << " bytes." << endl;
	};

	/*void make_contents(DataColumn<T>* raw_col) {
	    for(int i=0; i<raw_col->record_num; i++) {
		bitset<bit_num*record_num> temp = hex(raw_col->value[i]);
	        contents = (contents << bit_num) | temp;  
	    }
	}*/

	void print_edict() {
	    cout << "Print Encoded Dictionary" << endl; 
	    cout << contents << endl;
	}
	void copyFromColumnElements()	{};
	
	PackedArray* contents;
	int bit_num;
	int record_num;
};

#endif

