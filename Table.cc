#include "Table.h"

using namespace std;
Table::Table(){
};

Table::Table(vector<string> table_info, int record_num_){
    //set the metadata
    string datapath = table_info[0];
    t_name = table_info[1];
    record_num = record_num_;
    
    for(int i=2; i<table_info.size(); i+=2){
        column_name.push_back(table_info[i]);
        column_type.push_back(table_info[i+1]);
    }
    col_num = column_name.size();
    //allocate the column
    //**column = new Column*[col_num];
    
    for(int i=0; i<col_num; i++){
	column.push_back(new Column(column_name[i], column_type[i], record_num, false));
    	select_column.push_back(i);
    }
    //input data
    ifstream dataFile(table_info[0]);
    string line;
    //make set(unique, sorted) : 1 read
    //for(int i=0; getline(line, dataFile); i++){
    while(getline(dataFile, line)){
        string* records = Util::strSplit(line, ",");
        for(int j=0; j<col_num; j++){
            column[j]->push_setdict(records[j]);
        }
    }
    //make dictionary
    for(int j=0; j<col_num; j++){
        column[j]->make_dict();
        column[j]->setDistinct();
        column[j]->make_arr();
    }
    //column[0]->printMap();
    //column[1]->printMap();
    //column[2]->printMap();
    //make packed array : 2 read
    //for(int i=0; getline(dataFile, line); i++){
    dataFile.clear();
    dataFile.seekg(0); 
    int i = 0;
    while(getline(dataFile, line)){
        string* records = Util::strSplit(line, ",");
        for(int j=0; j<col_num; j++){
            column[j]->fill_arr(i, records[j]);
	}
	i++;
    }

    cout << "finish making table" << endl;
};

Table::~Table() {
    for(int i=0; i<col_num; i++){
        delete column[i];
    }
    column.clear();
    column_name.clear();
    column_type.clear();
};

void Table::getRecord(int index) {
    string s;
    double d;
    unsigned int u;
    int i;
    	for(int j : select_column) {
    	    column[j]->getValue(index, s, d, u, i);
    	    if(column_type[j] == "string") cout << s << "|" ;
    	    else if(column_type[j] == "double") cout << setprecision(17) << d << "|" ;
    	    else if(column_type[j] == "unsigned int") cout << u << "|" ;
    	    else if(column_type[j] == "int") cout << i << "|" ;
    	    //cout<< column[j]->getValue(index) << "|" ;
	}
	cout << endl;
}

void Table::getRecordNoLine(int index) {
    string s;
    double d;
    unsigned int u;
    int i;
    for(int j: select_column) {
	column[j]->getValue(index, s, d, u, i);
	if(column_type[j] == "string") cout << s << "|" ;
	else if(column_type[j] == "double") cout << setprecision(17) << d << "|" ;
	else if(column_type[j] == "unsigned int") cout << u << "|" ;
	else if(column_type[j] == "int") cout << i << "|" ;
    }
}
void Table::getRecordWithColumn(int index) {
    string s;
    double d;
    unsigned int u;
    int i;
    cout << "|";
    for(int j: select_column)
    {
	cout << column_name[j] << "|";
    } cout << endl;
    cout << "----------------------------------------" << endl; 
    for(int j: select_column) {
	column[j]->getValue(index, s, d, u, i);
	if(column_type[j] == "string") cout << s << "|" ;
	else if(column_type[j] == "double") cout << setprecision(17) << d << "|" ;
	else if(column_type[j] == "unsigned int") cout << u << "|" ;
	else if(column_type[j] == "int") cout << i << "|" ;
	//cout<< column[j]->getValue(index) << "|" ;
    }
	cout << endl;
};

void Table::getAllRecord(vector<int>* record_list){
    string s; double d; unsigned int u; int i;
    for(int j: select_column)
    {
	cout << column_name[j] << "|";
    } cout << endl;
    cout << "----------------------------------------" << endl; 
    if(record_list == NULL)
    {
	for(int i=0; i<record_num; i++) getRecord(i);
    }
    else
    {
    	for(auto &i: *record_list) 
	{
	    getRecord(i);
    	}
    }
}

void Table::getResult(){
    string s; double d; unsigned int u; int i;
    for(int j: select_column)
    {
	cout << column_name[j] << "|";
    } cout << endl;
    cout << "----------------------------------------" << endl; 
    for(int k: where_row)
	getRecord(k);
}

void Table::select(vector<int> column_list){
    select_column.clear();
    for(auto it=column_list.begin(); it!= column_list.end(); ++it){
	int j = (*it);
	select_column.push_back(j);
    }
}

void Table::where(int col_num, char op, string threshold){
    // update where_row
    where_row.clear();
    if(op == '='){
	for(int i=0; i<record_num; i++){
	    string q; double w; unsigned int e; int r;
	    column[col_num]->getValue(i, q, w, e, r);
	    switch(column[col_num]->column_type){
		case STRING: if(q.compare(threshold[i]) == 0) where_row.push_back(i); break;
		case DOUBLE: if(w==Util::strToDouble(threshold[i])) where_row.push_back(i); break;
		case UINT: if(e==Util::strToUint(threshold[i])) where_row.push_back(i); break;
		case INT: if(r==Util::strToInt(threshold[i])) where_row.push_back(i); break;
	    }
	}
    }
    else if(op == '>'){
	for(int i=0; i<record_num; i++){
	    string q; double w; unsigned int e; int r;
	    column[col_num]->getValue(i, q, w, e, r);
	    switch(column[col_num]->column_type){
		case STRING: if(q.compare(threshold[i]) > 0) where_row.push_back(i); break;
		case DOUBLE: if(w > Util::strToDouble(threshold[i])) where_row.push_back(i); break;
		case UINT: if(e > Util::strToUint(threshold[i])) where_row.push_back(i); break;
		case INT: if(r > Util::strToInt(threshold[i])) where_row.push_back(i); break;
	    }
	}
    }
    else if(op == '<'){
	for(int i=0; i<record_num; i++){
	    string q; double w; unsigned int e; int r;
	    column[col_num]->getValue(i, q, w, e, r);
	    switch(column[col_num]->column_type){
		case STRING: if(q.compare(threshold[i]) < 0) where_row.push_back(i); break;
		case DOUBLE: if(w < Util::strToDouble(threshold[i])) where_row.push_back(i); break;
		case UINT: if(e < Util::strToUint(threshold[i])) where_row.push_back(i); break;
		case INT: if(r < Util::strToInt(threshold[i])) where_row.push_back(i); break;
	    }
	}
    }
    else{
	cout << "Invalid op in where clause. " << endl;
	assert(false);
    }
}

void Table::where_and(int col_num, char op, string threshold){
    
    if(op =='='){
	for(auto j = where_row.begin(); j != where_row.end(); ++j)
	{
    	    string q; double w; unsigned int e; int r;
	    column[col_num]->getValue(*j, q, w, e, r);
	    switch(column[col_num]->column_type){
		case STRING: if(q.compare(threshold) == 0) where_row.erase(j); break;
		case DOUBLE: if(w==Util::strToDouble(threshold)) where_row.erase(j); break;
		case UINT: if(e==Util::strToUint(threshold)) where_row.erase(j); break;
		case INT: if(r==Util::strToInt(threshold)) where_row.erase(j); break;
	    }
	}
    }
}



void Table::Join(Column* c1, Column* c2, int printRecord){
    inter.push_back(Intermediate());
    inter[inter.size() - 1].Join(c1, c2, printRecord);
}

void Table::materialize(Table* one, Table* two){
   /* int join_num = inter.size();
    if(join_num == 1)
    {
	for(auto it=inter[0].record_set.begin(); it!=inter[0].record_set.end(); ++it){
	    int c1_index = it->first;
	    int c2_index = it->second;
	    one->getRecordNoLine(it->first);
	    two->getRecord(it->second);
	}
    }*/
    vector<Column*> mat_columns;
    vector<vector<int>> mat_records;
    for(int i=0; i<inter.size(); i++){
	for(auto it=inter[i].record_set.begin(); it!=inter[i].record_set.end(); ++it){

}



void Table::getMemSize() {};

