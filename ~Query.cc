#include "Query.h"

static void Query::Join(string col_name1, string col_name2, vector<tempCol>& indexes, Table& t){
    
    int col=0;
    for(auto it=t->column_name.begin(); it!=t->column_name.end(); it++)
    {
	if((*it) == col_name) break;
	col++;
    }

    switch(op){
	case EQUAL:
    	    unsigned int right_val;
	    try
	    {
		right_val = t->column[col]->getRight(threshold);
	    }
	    catch(...)
	    {
		cout << "No corresponding value in dictionary. " << endl;
		return;
	    }

//	    indexes.push_back(tempCol()
    }}
