#ifndef _INTERMEDIATE_H_
#define _INTERMEDIATE_H_

#include <vector>
#include <unordered_map>
#include <algorithm>

#include "Column.h"

using namespace std;

typedef struct inter_set{
    inter_set(){};

    vector<unsigned int> c1_records;
    vector<unsigned int> c2_records;
} inter_set;

class Intermediate {
    public:

	Intermediate(){};
	~Intermediate(){};
	void Join(Column* c1, Column* c2,  int printRecord){
	    if(c1 == NULL) {NextJoin(c2, printRecord); return;}
	    transmap = Column::makeHashTable(c1, c2);
	    reverse_transmap = Column::makeHashTable(c2, c1);
	    TransMap::iterator it;
	  
	    for(it = transmap.begin(); it!=transmap.end(); ++it){
		mid_storage.insert({it->first, inter_set()});
	    }

	    for(int i=0; i<c1->record_num; i++){
		it = transmap.find(c1->getRawFromIndex(i));
		if(it==transmap.end()) continue;
		else mid_storage[it->first].c1_records.push_back(i);
	    }
	    for(int i=0; i<c2->record_num; i++){
		it = reverse_transmap.find(c2->getRawFromIndex(i));
		if(it==reverse_transmap.end()) continue;
		else mid_storage[it->second].c2_records.push_back(i);
	    }
	    // make record_set
	    unordered_map<unsigned int, inter_set>::iterator mid_it;
	    for(mid_it = mid_storage.begin(); mid_it != mid_storage.end(); ++mid_it){
		inter_set temp = mid_it->second;
		for(auto c1_it = temp.c1_records.begin(); c1_it != temp.c1_records.end(); ++c1_it){
		    for(auto c2_it=temp.c2_records.begin(); c2_it != temp.c2_records.end(); ++c2_it){
			record_set.push_back({(*c1_it), (*c2_it)});
		    }
		}
	    }
	    int _printRecord = printRecord < record_set.size() ? printRecord : record_set.size();
	    string s;
	    double d;
	    unsigned int u;
	    int z;
	    int i =0;
	    for(auto rs_it = record_set.begin(); i<_printRecord; i++){
		c1->getValue(rs_it->first, s, d, u, z);
		switch(c1->column_type){
		    case STRING: cout << s << "----"; break;
		    case DOUBLE: cout << d << "----"; break;
		    case UINT: cout << u << "----"; break;
		    case INT: cout << z << "----"; break;
		}

		c2->getValue(rs_it->second, s, d, u, z); 
		switch(c2->column_type){
		    case STRING: cout << s << "----"<< endl; break;
		    case DOUBLE: cout << d << "----"<< endl; break;
		    case UINT: cout << u << "----"<< endl;  break;
		    case INT: cout << z << "----"<< endl; break;
		}
		cout << rs_it->first << ", " << rs_it->second <<endl;
		rs_it++;
	    }
	}
	void NextJoin(Column* c2, int printRecord){
	
	
	
	
	
	}	
	TransMap transmap, reverse_transmap;
	unordered_map<unsigned int, inter_set> mid_storage; // not used after Join
	vector<pair<int, int>> record_set;

};

#endif
