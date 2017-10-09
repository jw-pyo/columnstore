#ifndef _ENCODEDDICT_H_
#define _ENCODEDDICT_H_

#include <iostream>
#include <vector>
#include <algorithm>
#include <map>
#include <stdlib.h>
#include <stdio.h>
#include <limits.h>
#include <math.h>
#include <bitset>
#include <boost/dynamic_bitset.hpp>

#include "PackedArray.h"
#include "util.h"
//#include "DataArray.h"

using namespace std;
/*void show(const void *object, size_t size)
{
       const unsigned char *byte;
       for ( byte = object; size--; ++byte )
	{
	    unsigned char mask;
	    for ( mask = 1 << (CHAR_BIT - 1); mask; mask >>= 1 )
	    {
		putchar(mask & *byte ? '1' : '0');
	    }
	    putchar(' ');
	}
	putchar('\n');
}*/

void shift_left_bit8(unsigned char* arr, int len, int bit){
   // cout << "Before" << endl;
   // cout << "" << endl;

    for(int i = 0; i < len - 1; i++){
	arr[i] = (arr[i] << bit) | ((arr[i+1] >> (8 - bit)));
    }
    arr[len-1] = (arr[len-1] << bit) & 0xFF;
   // cout << "After" << endl;
   // cout << "" << endl;
}


void shift_left_bit16(uint16_t* arr, int len, int bit){
    int i;
   // cout << "Before" << endl;
   // cout << "" << endl;

    for(i = 0; i < len - 1; ++i){
	arr[i] = (arr[i] << bit) | ((arr[i+1] >> (16 - bit)) & (uint16_t)(pow(2, 16-bit) - 1));
    }
    arr[len-1] = arr[len-1] << bit;
   // cout << "After" << endl;
   // cout << "" << endl;
}
void shift_left_bit32(uint32_t* arr, int len, int bit){
    int i;
   // cout << "Before" << endl;
   // cout << "" << endl;

    for(i = 0; i < len - 1; ++i){
	arr[i] = (arr[i] << bit) | ((arr[i+1] >> (32 - bit)) & (uint32_t)(pow(2, 32-bit) - 1));
    }
    arr[len-1] = arr[len-1] << bit;
   // cout << "After" << endl;
   // cout << "" << endl;
}

//template<typename T>
class EncodedDict {
    public:
	EncodedDict (string* data_path, map<string, int> sdict, int col_num_, int bit_num_, int record_num_)	{
	    t_name = data_path[1];
	    c_name = data_path[2+col_num_];
	    col_num = col_num_;
	    bit_num = bit_num_;
	    record_num = record_num_;
	    total_bit = bit_num * record_num;
	    void* temp;
	    //contents = PackedArray_create((uint32_t)bit_num, (uint32_t)record_num);
	    cout << "total_bit: " << total_bit << endl;
	    cout << "bit_num: " << bit_num << endl;
	    
	    if (bit_num <=8) {
		block_num = (int)ceil((double)total_bit/8);
		contents_8 = (unsigned char*)calloc(block_num, sizeof(unsigned char));
		//temp = (unsigned char*)calloc(block_num, sizeof(unsigned char));
		unit_bit = 8;
		cout << "block_num: " << block_num << endl;
	    }

	    else if (bit_num <=16) {
		block_num = (int)ceil((double)total_bit/16);
		contents_16 = (unsigned short*)calloc(block_num, sizeof(unsigned short));
		//temp = (unsigned short*)calloc(block_num, sizeof(unsigned short));
		unit_bit = 16;
	    }

	    else if (bit_num <=32) {
		block_num = (int)ceil((double)total_bit/32);
		contents_32 = (unsigned int*)calloc(block_num, sizeof(unsigned int));
		//temp = (unsigned int*)calloc(block_num, sizeof(unsigned int));
		unit_bit = 32;
	    }
	    
	    else {
	       cout << "This type is not supported." << endl;
	       assert(1);
	    }

	    ifstream dataFile(data_path[0]);
	    string line;
	    if (bit_num <= 8) {
	    for(int i=0; i<record_num; i++) {
		getline(dataFile, line);
		string* line_arr = strSplit(line, ",");
		//	PackedArray_set(contents, i, raw_col.value[i]);
		shift_left_bit8(contents_8, block_num, bit_num);
		//cout << convert_to<T>(line_arr[col_num])<< endl;
		contents_8[block_num - 1] |= (unsigned char)sdict[(line_arr[col_num])];
	    //for(int k=0; k < block_num; k++) {
	//	cout << "contents[" << k << "] " << bitset<8>((unsigned int)contents_8[k]) << endl;
	  //  	}
	  //  }
	    }
	    //show(contents, (int)ceil(total_bit/8));
	    for(int k=0; k < block_num; k++) {
		cout << "contents[" << k << "] " << bitset<8>((unsigned char)contents_8[k]) << endl;
	    	}
	    }

	    else if(bit_num <= 16) {
	    for(int i=1; i<=record_num; i++) {
		getline(dataFile, line);
		string* line_arr = strSplit(line, ",");
		shift_left_bit16(contents_16, block_num, bit_num);
		contents_16[block_num - 1] |= (unsigned short)sdict[(line_arr[col_num])];
		for(int j=0; j<block_num; j++)	
		{
		    cout <<  bitset<16>((unsigned int)contents_16[j]) << "   ";
		}
		cout << " " << endl;
	    }
	    for(int k=0; k < block_num; k++) {
		cout << "contents[" << k << "] " << (unsigned int)contents_16[k] << endl;
	    	}
	    }
	    else if(bit_num <= 32) {
	    for(int i=0; i<record_num; i++) {
		getline(dataFile, line);
		string* line_arr = strSplit(line, ",");
		shift_left_bit32(contents_32, block_num, bit_num);
		contents_32[block_num - 1] |= (unsigned int)sdict[(line_arr[col_num])];
		for(int j=0; j<block_num; j++)	
		{
		    cout <<  bitset<32>((unsigned int)contents_32[j]) << "   ";
		}
		cout << " " << endl;
	    }
	    //show(contents, (int)ceil(total_bit/8));
	    for(int k=0; k < block_num; k++) {
		cout << "contents[" << k << "] " << (unsigned int)contents_32[k] << endl;
	    	}
	    }
	    else{
	    	cout << "This type is not supported." << endl;
		assert(1);
	    }

	    
	    //free(temp);
	    cout << "\nCreate Encoded Dictionary: " <<data_path[1] << "->" << data_path[2+col_num] << endl;
	    cout << "**************************" << endl;
	};
	
	~EncodedDict() {
	
	    free(contents_8);
	    cout << "\nDelete Encoded Dictionary: " << t_name  << "->" << c_name << endl;
	};

	/*void make_contents(DataColumn<T>* raw_col) {
	    for(int i=0; i<raw_col->record_num; i++) {
		bitset<bit_num*record_num> temp = hex(raw_col->value[i]);
	        contents = (contents << bit_num) | temp;  
	    }
	}*/
	unsigned char get_encodedbit(unsigned char* arr, int ind){
	    int base = (bit_num * record_num - 1 ) % unit_bit; 
	    int j = (int)ceil((double)(ind - base) / unit_bit);
	    int container_base = unit_bit - ((ind - base) % unit_bit);
	    if(container_base == unit_bit) container_base = 0;
	    //in arr[j], container_base-th index is the return value

	    unsigned char ret = 0x00;
	    ret |= ((arr[j] >> container_base) & 0x01);
	    return ret;
	}

	void print_edict(int index=-1) {
	    cout << "Encoded Dict: " << endl;
	    
	    for(int i=0; i<record_num; i++){
		unsigned char ret = 0x00;
		for(int k = 0; k<bit_num; k++) {
		    ret <<= 1;
		    ret |= get_encodedbit(contents_8, i*bit_num + k);
		}
		    cout << "record " << i << ": " << (unsigned int)ret << endl; 
	    }
	}

	/*void print_edict(int index=-1) {
	    cout << "Print Encoded Dictionary : " << t_name << "->" << c_name << endl; 
	    
	    if(index==-1){
	    	for(int i=0; i < record_num ; i++){
		    for(int j=0; j < block_num ; j++){
		        
			if((record_num - 1 - i)*bit_num  >= j*unit_bit && (record_num - 1 - i)*bit_num < (j + 1)*unit_bit) {
			    int inner_index = (i*bit_num) % unit_bit;
			    if (unit_bit <=8){
			    	unsigned char ret = (contents_8[block_num - j] >> inner_index) & (unsigned char)(pow(2, (unit_bit - inner_index)) - 1);
				if(inner_index + bit_num > unit_bit && j!=0){
				    ret = ret | ((contents_8[block_num - j - 1] & (unsigned char)(pow(2, inner_index + bit_num - unit_bit) - 1)) << (unit_bit - inner_index));
				}

				cout << "index: " << i << " value: " << (unsigned short)ret << endl;
				break;
			    }
			}
		    
		    }

	    	}
	    }
	    // index is not -1
	    for(int i=0; i<record_num; i++) {

	    }
	}
	*/
	void get_record(){};


	void* contents;	
	unsigned char* contents_8;
	unsigned short* contents_16;
	unsigned int* contents_32;
	//PackedArray* contents;
	
	private:
	int col_num; // the i-th column of table
	int bit_num; // the number of bits that encoded value 
	int record_num; // total record number
	int unit_bit; // the unit of bits. bit_num <= unit_bit and unit_bit can be 8, 16, 32
	int total_bit; // = bit_num * record_num
	int block_num; // the number of arrays that have to make
	string t_name; // name of table
	string c_name; // name of column
};

#endif

