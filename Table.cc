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
    cout << "|";
    for(int j=0; j < col_num; j++)
    {
	cout << column_name[j] << "|";
    } cout << endl;
    cout << "----------------------------------------" << endl; 
    for(int j=0; j<col_num-1; j++) {
	column[j]->getValue(index, s, d, u, i);
	if(column_type[j] == "string") cout << s << "|" ;
	else if(column_type[j] == "double") cout << setprecision(17) << d << "|" ;
	else if(column_type[j] == "unsigned int") cout << u << "|" ;
	else if(column_type[j] == "int") cout << i << "|" ;
	//cout<< column[j]->getValue(index) << "|" ;
    }

	column[col_num - 1]->getValue(index, s, d, u, i);
	if(column_type[col_num - 1] == "string") cout << s << endl;
	else if(column_type[col_num - 1] == "double") cout << setprecision(17) << d << endl;
	else if(column_type[col_num - 1] == "unsigned int") cout << u << endl;
	else if(column_type[col_num - 1] == "int") cout << i << endl;
    //cout << column[col_num - 1]->getValue(index) << endl;
};

Table* Table::select(vector<int> column_list, string alias_name){
    Table* ret = new Table();
    ret->record_num = record_num;
    ret->col_num = column_list.size();
    ret->t_name = alias_name;
    for(auto it=column_list.begin(); it!= column_list.end(); ++it){
	int j = (*it);
	ret->column_name.push_back(column_name[j]);
	ret->column_type.push_back(column_type[j]);
	ret->column.push_back(new Column(*column[j]));
    }

    return ret;
    
}

/*void Table::where_and(vector<int> column_list, vector<char> op, vector<string> threshold){
    
    Table* ret = new Table();
    ret->record_num = record_num;
    ret->col_num = column_list.size();
    ret->t_name = alias_name;
    for(auto it=column_list.begin(); it!= column_list.end(); ++it){
	int j = (*it);
	ret->column_name.push_back(column_name[j]);
	ret->column_type.push_back(column_type[j]);
	ret->column.push_back(new Column(*column[j]));
    }

   // return ret;
}*/
void Table::Join(Column* c1, Column* c2, int printRecord){
    inter.push_back(Intermediate(c1, c2, printRecord));
}

void Table::materialize(){
    int join_num = inter.size();
    if(join_num == 1)
    {
	for(auto it=inter[0].record_set.begin(); it!=inter[0].record_set.end(); ++it){
	    int c1_index = it->first;
	    int c2_index = it->second;

    }





void Table::getMemSize() {};

