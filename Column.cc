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

Column::Column(const Column &obj){
//  shallow copy
    dict = obj.dict;
    dict2 = obj.dict2;
    dict3 = obj.dict3;
    dict4 = obj.dict4;
    set_dict = obj.set_dict;
    set_dict2 = obj.set_dict2;
    set_dict3 = obj.set_dict3;
    set_dict4 = obj.set_dict4;
    data_arr = obj.data_arr;
    distinct_num = obj.distinct_num;
    bit_num = obj.bit_num;
    column_name = obj.column_name;
    column_type = obj.column_type;
    record_num = obj.record_num;
};

Column::~Column() { 
	    switch(column_type) {
		case STRING : set_dict.clear(); dict.clear(); break;
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
	    case STRING : set_dict.insert(val); break;
	    case DOUBLE : set_dict2.insert(Util::strToDouble(val)); break;
	    case UINT : set_dict3.insert(Util::strToUint(val)); break;
	    case INT : set_dict4.insert(Util::strToInt(val)); break;
	}
}
    
void Column::make_dict(){
        // NULL:0 set is always contained in dict.
    	unsigned int i=0;
	switch(column_type) {
	    case STRING : for(auto it=set_dict.begin(); it!=set_dict.end(); it++) dict.insert({(*it), i++}); break;
	    case DOUBLE : for(auto it=set_dict2.begin(); it!=set_dict2.end(); it++) dict2.insert({(*it), i++}); break;
	    case UINT : for(auto it=set_dict3.begin(); it!=set_dict3.end(); it++) dict3.insert({(*it), i++}); break;
	    case INT : for(auto it=set_dict4.begin(); it!=set_dict4.end(); it++) dict4.insert({(*it), i++}); break;
	} 
}

void Column::setDistinct(){
        switch(column_type) {
	    case STRING : distinct_num = dict.size(); break;
	    case DOUBLE : distinct_num = dict2.size(); break;
	    case UINT : distinct_num = dict3.size(); break;
	    case INT : distinct_num = dict4.size(); break;
	    default: cout << "Nothing in setDistinct(). " << endl;
    	}
}
   
void Column::make_arr(){
        bit_num = (int)ceil(log2(distinct_num));
        data_arr = PackedArray_create(bit_num, record_num);
}


void Column::fill_arr(int index, string val){
	//cout << "fill " << dict.left.at(val) << " in!" << endl;
	switch(column_type) {
	    case STRING : PackedArray_set(data_arr, index, dict.left.at(val)); break;
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
	    case STRING : s = dict.right.at(ret); break;
	    case DOUBLE : d = dict2.right.at(ret); break;
	    case UINT : u = dict3.right.at(ret); break;
	    case INT : i = dict4.right.at(ret); break;
	    default: cout << "Nothing returned in getValue(" << index << ")." << endl; return;
	}
}
unsigned int Column::getRawFromIndex(int index){
    unsigned int ret;
    ret = PackedArray_get(data_arr, index);
    return ret;
}
unsigned int Column::getRight(string left_val){
	switch(column_type) {
	    case STRING : return dict.left.at(left_val); break;
	    case DOUBLE : return dict2.left.at(Util::strToDouble(left_val)); break;
	    case UINT : return dict3.left.at(Util::strToUint(left_val)); break;
	    case INT : return dict4.left.at(Util::strToInt(left_val)); break;
	    default: cout << "Nothing returned in getRight(" << left_val << ")." << endl; assert(false);
	}
}
string Column::getLeft(unsigned int right_val){ //only string
	switch(column_type) {
	    case STRING : return dict.right.at(right_val); break;
	    case DOUBLE : return to_string(dict2.right.at(right_val)); break;
	    case UINT : return to_string(dict3.right.at(right_val)); break;
	    case INT : return to_string(dict4.right.at(right_val)); break;
	    default: cout << "Nothing returned in getRight(" << right_val << ")." << endl; assert(false);
	}
}

vector<int> Column::getIndexes(unsigned int right_val){
    vector<int> ret;
    for(int i=0; i<record_num; i++){
	if(getRawFromIndex(i) == right_val) ret.push_back(i);
    }
    return ret;
}

void Column::printMap() {
    	cout << column_name << "<" << column_type << ">" << " dictionary: " << endl;
	switch(column_type) {
	    case STRING : for(auto it=dict.left.begin(); it!=dict.left.end(); ++it){cout << (*it).first << " : " << (*it).second << endl;} break;
	    case DOUBLE : for(auto it=dict2.left.begin(); it!=dict2.left.end(); ++it){cout << (*it).first << " : " << (*it).second << endl;} break;
	    case UINT : for(auto it=dict3.left.begin(); it!=dict3.left.end(); ++it){cout << (*it).first << " : " << (*it).second << endl;} break;
	    case INT : for(auto it=dict4.left.begin(); it!=dict4.left.end(); ++it){cout << (*it).first << " : " << (*it).second << endl;} break;
	    default : cout << "column_type wrong in printMap()" << endl;
    	}
}

int Column::getColMemory(){

    int ret = (int)ceil(bit_num * record_num / 8.0); // PackedArray
    switch(column_type) { // dict and set_dict
	case STRING : ret += (sizeof(string)+sizeof(unsigned int))*dict.size() + sizeof(string) * set_dict.size(); break; 
	case DOUBLE : ret += (sizeof(double)+sizeof(unsigned int))*dict2.size() + sizeof(double) * set_dict2.size(); break; 
	case UINT : ret += (sizeof(unsigned int)+sizeof(unsigned int))*dict3.size() + sizeof(unsigned int) * set_dict3.size(); break; 
	case INT : ret += (sizeof(int)+sizeof(unsigned int))*dict4.size() + sizeof(int) * set_dict4.size(); break;
    }
    return ret;
}

//assume c1 and c2 are same domain.
TransMap Column::makeHashTable(Column* c1, Column* c2) {
    TransMap ret;
    switch(c1->column_type){
	case STRING:
	    {auto it_c1 = c1->dict.left.begin();
	    auto it_c2 = c2->dict.left.begin();
	    while(it_c1 != c1->dict.left.end() && it_c2 != c2->dict.left.end())
	    {
		if((*it_c1).first.compare((*it_c2).first) == 0)
		{
		    ret.insert({(*it_c1).second, (*it_c2).second});
		    it_c1++;
		}
		else if((*it_c1).first.compare((*it_c2).first) > 0)
		{
		    it_c2++;
		}
		else
		{
		    it_c1++;
		}
	    }}
	    break;
	case DOUBLE:
	    {auto it_c1 = c1->dict2.left.begin();
	    auto it_c2 = c2->dict2.left.begin();
	    while(it_c1 != c1->dict2.left.end() && it_c2 != c2->dict2.left.end())
	    {
		if((*it_c1).first == (*it_c2).first)
		{
		    ret.insert({(*it_c1).second, (*it_c2).second});
		    it_c1++;
		}
		else if((*it_c1).first > (*it_c2).first)
		{
		    it_c2++;
		}
		else
		{
		    it_c1++;
		}
	    }}
	    break;
	case UINT:
	    {auto it_c1 = c1->dict3.left.begin();
	    auto it_c2 = c2->dict3.left.begin();
	    while(it_c1 != c1->dict3.left.end() && it_c2 != c2->dict3.left.end())
	    {
		if((*it_c1).first == (*it_c2).first)
		{
		    ret.insert({(*it_c1).second, (*it_c2).second});
		    it_c1++;
		}
		else if((*it_c1).first > (*it_c2).first)
		{
		    it_c2++;
		}
		else
		{
		    it_c1++;
		}
	    }}
	    break;
	case INT:
	    auto it_c1 = c1->dict4.left.begin();
	    auto it_c2 = c2->dict4.left.begin();
	    while(it_c1 != c1->dict4.left.end() && it_c2 != c2->dict4.left.end())
	    {
		if((*it_c1).first == (*it_c2).first)
		{
		    ret.insert({(*it_c1).second, (*it_c2).second});
		    it_c1++;
		}
		else if((*it_c1).first > (*it_c2).first)
		{
		    it_c2++;
		}
		else
		{
		    it_c1++;
		}
	    }
	    break;
    }
    return ret;
}



