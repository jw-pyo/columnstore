#ifndef _ENCODEDDICT_H_
#define _ENCODEDDICT_H_

#include <iostream>
#include <vector>
#include <algorithm>
#include <stdlib.h>
#include <math.h>
#include <bitset>

#include "DataArray.h"

using namespace std;
template<typename T>
class EncodedDict {
    public:
	EncodedDict (set<T, int> sdict, int bit_num, int record_num)	{
	    this.bit_num = bit_num;
	    this.record_num = record_num;
	    contents = 0x0;

	};

	void make_contents(DataColumn* raw_col) {
	    for(int i=0; i<raw_col.record_num; i++) {
		bitset<bit_num*record_num> temp = hex(raw_col.value[i]);
	        contents = (contents << bit_num) | temp;  
	    }
	}
	void copyFromColumnElements()	{};




	bitset<bit_num*record_num> contents; // >= bit_num * record_num;
	int bit_num;
	int record_num;
};

#endif

