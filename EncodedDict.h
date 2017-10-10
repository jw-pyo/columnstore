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
#include <assert.h>

#include "PackedArray.h"
#include "util.h"

using namespace std;


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
	    // make sdict_array
	    sdict_array = new string[sdict.size()];
	    for(map<string, int>::iterator it=sdict.begin(); it!=sdict.end(); ++it){
		sdict_array[(*it).second] = (*it).first;
	    }
	    
	    cout << "Start Creating edict: " << t_name << "->" << c_name << endl;
	    cout << "total_bit: " << total_bit << endl;
	    cout << "bit_num: " << bit_num << endl;
	    cout << "record_num: " << record_num << endl;
	    
	    if (bit_num <=8) {
		block_num = (int)ceil((double)total_bit/8);
		contents_8 = (unsigned char*)calloc(block_num, sizeof(unsigned char));
		unit_bit = 8;
		cout << "block_num: " << block_num << endl;
	    }

	    else if (bit_num <=16) {
		block_num = (int)ceil((double)total_bit/16);
		contents_16 = (unsigned short*)calloc(block_num, sizeof(unsigned short));
		unit_bit = 16;
		cout << "block_num: " << block_num << endl;
	    }

	    else if (bit_num <=32) {
		block_num = (int)ceil((double)total_bit/32);
		contents_32 = (unsigned int*)calloc(block_num, sizeof(unsigned int));
		//temp = (unsigned int*)calloc(block_num, sizeof(unsigned int));
		unit_bit = 32;
		cout << "block_num: " << block_num << endl;
	    }
	    
	    else {
	       cout << "This type is not supported." << endl;
	       assert(1);
	    }

	    ifstream dataFile(data_path[0]);
	    string line;
	    if (bit_num <= 8) {
		//O(n^2)	    
    	    for(int i=0; i<record_num; i++) {
		getline(dataFile, line);
		string* line_arr = strSplit(line, ",");
		//O(n)
		shift_left_bit8(contents_8, block_num, bit_num, i);
		//O(logn)
		contents_8[block_num - 1] |= (unsigned char)sdict[(line_arr[col_num])];
		if(i % 5000 == 0)
		    cout << i << " records are loaded," << endl;
	    }
	    for(int k=0; k < block_num; k++) {
	//	cout << "contents[" << k << "] " << bitset<8>((unsigned char)contents_8[k]) << endl;
	    	}
	    }

	    else if(bit_num <= 16) {
	    for(int i=1; i<=record_num; i++) {
		getline(dataFile, line);
		string* line_arr = strSplit(line, ",");
		shift_left_bit16(contents_16, block_num, bit_num);
		contents_16[block_num - 1] |= (unsigned short)sdict[(line_arr[col_num])];
	    }
	    for(int k=0; k < block_num; k++) {
	//	cout << "contents[" << k << "] " << (unsigned int)contents_16[k] << endl;
	    	}
	    }
	    
	    else if(bit_num <= 32) {
	    for(int i=0; i<record_num; i++) {
		getline(dataFile, line);
		string* line_arr = strSplit(line, ",");
		shift_left_bit32(contents_32, block_num, bit_num);
		contents_32[block_num - 1] |= (unsigned int)sdict[(line_arr[col_num])];
		//for(int j=0; j<block_num; j++)	
		//{
		//    cout <<  bitset<32>((unsigned int)contents_32[j]) << "   ";
		//}
		//cout << " " << endl;
	    }
	    for(int k=0; k < block_num; k++) {
	//	cout << "contents[" << k << "] " << (unsigned int)contents_32[k] << endl;
	    	}
	    }
	    else{
	    	cout << "This type is not supported." << endl;
		assert(1);
	    }

	    cout << "\nComplete Creating edict: " << t_name << "->" << c_name << endl;
	    
	};
	
	~EncodedDict() {
	
	    if(bit_num <=8) free(contents_8);
	    else if(bit_num <=16) free(contents_16);
	    else if(bit_num <=32) free(contents_32);
	    delete[] sdict_array;
	    cout << "\nDelete edict: " << t_name  << "->" << c_name << endl;
	};

	void shift_left_bit8(unsigned char* arr, int len, int shift, int input_rec_i){
	    if(input_rec_i==0) return;

	    int base = (bit_num * input_rec_i - 1 ) % unit_bit; 
	    int j = (len - 1) - (int)ceil((double)(bit_num*input_rec_i - 1 - base) / unit_bit);
	    if(j == 0) j = 1;

	    for(int i = j - 1; i < len - 1; i++){
		arr[i] = (arr[i] << shift) | ((arr[i+1] >> (8 - shift)));
	    }
	    arr[len-1] = (arr[len-1] << shift) & 0xFF;
	}

	void shift_left_bit16(uint16_t* arr, int len, int bit){
	    for(int i = 0; i < len - 1; i++){
		arr[i] = (arr[i] << bit) | ((arr[i+1] >> (16 - bit)));
	    }
	    arr[len-1] = (arr[len-1] << bit) & 0xFFFF;
	}
	
	void shift_left_bit32(uint32_t* arr, int len, int bit){

	    for(int i = 0; i < len - 1; i++){
		arr[i] = (arr[i] << bit) | ((arr[i+1] >> (32 - bit)));
	    }
	    arr[len-1] = (arr[len-1] << bit) & 0xFFFFFFFF;
	}

	unsigned char get_encodedbit8(unsigned char* arr, int ind){
	    int base = (bit_num * record_num - 1 ) % unit_bit; 
	    int j = (int)ceil((double)(ind - base) / unit_bit);
	    int container_base = unit_bit - ((ind - base) % unit_bit);
	    if(container_base == unit_bit) container_base = 0;
	    //in arr[j], container_base-th index is the return value

	    unsigned char ret = 0x00;
	    ret |= ((arr[j] >> container_base) & 0x01);
	    return ret;
	}
	
	unsigned short get_encodedbit16(unsigned short* arr, int ind){
	    int base = (bit_num * record_num - 1 ) % unit_bit; 
	    int j = (int)ceil((double)(ind - base) / unit_bit);
	    int container_base = unit_bit - ((ind - base) % unit_bit);
	    if(container_base == unit_bit) container_base = 0;
	    //in arr[j], container_base-th index is the return value

	    unsigned short ret = 0x0000;
	    ret |= ((arr[j] >> container_base) & 0x0001);
	    return ret;
	}

	unsigned int get_encodedbit32(unsigned int* arr, int ind){
	    int base = (bit_num * record_num - 1 ) % unit_bit; 
	    int j = (int)ceil((double)(ind - base) / unit_bit);
	    int container_base = unit_bit - ((ind - base) % unit_bit);
	    if(container_base == unit_bit) container_base = 0;
	    //in arr[j], container_base-th index is the return value

	    unsigned int ret = 0x00000000;
	    ret |= ((arr[j] >> container_base) & 0x00000001);
	    return ret;
	}

	string decode(unsigned int ret) {
	//use binary search
	return sdict_array[ret];	
	}
	void print_edict(int index=-1) {
	    cout << "Print edict: " << t_name << "->" << c_name << endl;
	   
	    if(index == -1) {
	    for(int i=0; i<record_num; i++){
		if(bit_num <=8){
		unsigned char ret = 0x00;
		for(int k = 0; k<bit_num; k++) {
		    ret <<= 1;
		    ret |= get_encodedbit8(contents_8, i*bit_num + k);
		    }
		    cout << "record " << i << ": " << decode((unsigned int)ret) << endl; 
		}
		else if(bit_num <=16){
		unsigned short ret = 0x0000;
		for(int k = 0; k<bit_num; k++) {
		    ret <<= 1;
		    ret |= get_encodedbit16(contents_16, i*bit_num + k);
		    }
		    cout << "record " << i << ": " << (unsigned int)ret << endl; 
		}
		else if(bit_num <=32){
		unsigned int ret = 0x00000000;
		for(int k = 0; k<bit_num; k++) {
		    ret <<= 1;
		    ret |= get_encodedbit32(contents_32, i*bit_num + k);
		    }
		    cout << "record " << i << ": " << (unsigned int)ret << endl; 
		}
	    }
	    
	    }

	    else if(index >=0 && index <record_num){
		if(bit_num <=8) {
		unsigned char ret = 0x00;
		for (int k=0; k<bit_num; k++) {
		    ret <<=1;
		    ret |= get_encodedbit8(contents_8, index*bit_num + k);
		    }
		    cout << "record " << index << ": " << (unsigned int)ret << endl;
		}
		else if(bit_num <=16) {
		unsigned short ret = 0x0000;
		for (int k=0; k<bit_num; k++) {
		    ret <<=1;
		    ret |= get_encodedbit16(contents_16, index*bit_num + k);
		    }
		    cout << "record " << index << ": " << (unsigned int)ret << endl;
		}
		else if(bit_num <=32) {
		unsigned int ret = 0x00000000;
		for (int k=0; k<bit_num; k++) {
		    ret <<=1;
		    ret |= get_encodedbit32(contents_32, index*bit_num + k);
		    }
		    cout << "record " << index << ": " << (unsigned int)ret << endl;
		}
	    }

	    else {
	    	cout << "The record number is not in the range. " << endl;
		assert(false);
	    }
	}
	
	int get_size(){
          int size_ = sizeof(8)*3 + sizeof(int)*6 + t_name.size() + c_name.size() + sizeof(*sdict_array);
	  if(bit_num <=8) size_ += sizeof(*contents_8);
	  if(bit_num <=16) size_ += sizeof(*contents_16);
	  if(bit_num <=32) size_ += sizeof(*contents_32);
	  return size_;
	  
	}

	void get_record(){};


	void* contents;	
	unsigned char* contents_8;
	unsigned short* contents_16;
	unsigned int* contents_32;
	//PackedArray* contents;
	
	private:
	string* sdict_array;
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
