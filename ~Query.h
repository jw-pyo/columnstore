#ifndef _QUERY_H_
#define _QUERY_H_


#include "Table.h"
using namespace std;

typedef struct tempCol {
    vector<int> index;
    string name;
    bool isJoined=false;
} tempCol;

class Query {
    public:

	Query(){};

	~Query(){};

	static void where(vector<tempCol>& indexes, Table& t);
	static void PartitionedJoin(){}
	static void Join(){}
	static void Materialize(){}

};




#endif
