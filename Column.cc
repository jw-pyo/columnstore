#include "Column.h"

using namespace std;

//template <typename T>
Column::Column(string column_name_, string column_type_, int record_num_, bool lossy) {
	    
	//assume data are all in.
        column_name = column_name_;
	if(column_type_ == "string") column_type = STRING;
	else if(column_type_ == "double") column_type = DOUBLE;
	else if(column_type_ == "unsigned int") column_type = UINT;
	else if(column_type_ == "int") column_type = INT;
	else cout << "column type not defined in " << column_name << endl; 
	record_num = record_num_;
};

Column::~Column() { 
	    switch(column_type) {
		case STRING : set_dict1.clear(); dict1.clear(); break;
		case DOUBLE : set_dict2.clear(); dict2.clear(); break;
		case UINT : set_dict3.clear(); dict3.clear(); break;
		case INT : set_dict4.clear(); dict4.clear(); break;
		default: cout << "Nothing deleted in " << column_name << " column. Please check the type. " << endl;
	    }
	    PackedArray_destroy(data_arr);
	    cout << "Delete Column: " << column_name  << endl;
};

void Column::push_setdict(string val) {
        
	switch(column_type) {
	    case STRING : set_dict1.insert(val); break;
	    case DOUBLE : set_dict2.insert(Util::strToDouble(val)); break;
	    case UINT : set_dict3.insert(Util::strToUint(val)); break;
	    case INT : set_dict4.insert(Util::strToInt(val)); break;
	}
}
    
void Column::make_dict(){
        unsigned int i=0;
	switch(column_type) {
	    case STRING : for(auto it=set_dict1.begin(); it!=set_dict1.end(); it++) dict1.insert({(*it), i++}); break;
	    case DOUBLE : for(auto it=set_dict2.begin(); it!=set_dict2.end(); it++) dict2.insert({(*it), i++}); break;
	    case UINT : for(auto it=set_dict3.begin(); it!=set_dict3.end(); it++) dict3.insert({(*it), i++}); break;
	    case INT : for(auto it=set_dict4.begin(); it!=set_dict4.end(); it++) dict4.insert({(*it), i++}); break;
	} 
}

void Column::setDistinct(){
        switch(column_type) {
	    case STRING : distinct_num = dict1.size(); break;
	    case DOUBLE : distinct_num = dict2.size(); break;
	    case UINT : distinct_num = dict3.size(); break;
	    case INT : distinct_num = dict4.size(); break;
	    default: cout << "Nothing in setDistinct(). " << endl;
    	}
}
   
void Column::make_arr(){
        int bit = (int)ceil(log2(distinct_num));
        data_arr = PackedArray_create(bit, record_num);
}


void Column::fill_arr(int index, string val){
	//cout << "fill " << dict.left.at(val) << " in!" << endl;
	switch(column_type) {
	    case STRING : PackedArray_set(data_arr, index, dict1.left.at(val)); break;
	    case DOUBLE : PackedArray_set(data_arr, index, dict2.left.at(Util::strToDouble(val))); break;
	    case UINT : PackedArray_set(data_arr, index, dict3.left.at(Util::strToUint(val))); break;
	    case INT : PackedArray_set(data_arr, index, dict4.left.at(Util::strToInt(val))); break;
            default: cout << "Nothing in fill_arr(" << index << ", " << val << " )." << endl;
	}
}

void Column::getValue(int index, string &s, double &d, unsigned int &u, int &i){
    	unsigned int ret;
    	ret = PackedArray_get(data_arr, index);
	switch(column_type) {
	    case STRING : s = dict1.right.at(ret); break;
	    case DOUBLE : d = dict2.right.at(ret); break;
	    case UINT : u = dict3.right.at(ret); break;
	    case INT : i = dict4.right.at(ret); break;
	    default: cout << "Nothing returned in getValue(" << index << ")." << endl; return;
	}
}
    
void Column::printMap() {
    	cout << column_name << "<" << column_type << ">" << " dictionary: " << endl;
	switch(column_type) {
	    case STRING : for(auto it=dict1.left.begin(); it!=dict1.left.end(); ++it){cout << (*it).first << " : " << (*it).second << endl;} break;
	    case DOUBLE : for(auto it=dict2.left.begin(); it!=dict2.left.end(); ++it){cout << (*it).first << " : " << (*it).second << endl;} break;
	    case UINT : for(auto it=dict3.left.begin(); it!=dict3.left.end(); ++it){cout << (*it).first << " : " << (*it).second << endl;} break;
	    case INT : for(auto it=dict4.left.begin(); it!=dict4.left.end(); ++it){cout << (*it).first << " : " << (*it).second << endl;} break;
	    default : cout << "column_type wrong in printMap()" << endl;
    	}
}

