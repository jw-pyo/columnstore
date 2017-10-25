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

void Table::getRecord(int index, bool EndLine) {
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
	if(EndLine) cout << endl;
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
void Table::printColName(bool EndLine){
    for(auto it = column_name.begin(); it != column_name.end(); ++it){
	cout << (*it) << "|" ;
    }
    if(EndLine) cout << endl;
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
		case STRING: if(q.compare(threshold) == 0) where_row.push_back(i); break;
		case DOUBLE: if(w==Util::strToDouble(threshold)) where_row.push_back(i); break;
		case UINT: if(e==Util::strToUint(threshold)) where_row.push_back(i); break;
		case INT: if(r==Util::strToInt(threshold)) where_row.push_back(i); break;
	    }
	}
    }
    else if(op == '>'){
	for(int i=0; i<record_num; i++){
	    string q; double w; unsigned int e; int r;
	    column[col_num]->getValue(i, q, w, e, r);
	    switch(column[col_num]->column_type){
		case STRING: if(q.compare(threshold) > 0) where_row.push_back(i); break;
		case DOUBLE: if(w > Util::strToDouble(threshold)) where_row.push_back(i); break;
		case UINT: if(e > Util::strToUint(threshold)) where_row.push_back(i); break;
		case INT: if(r > Util::strToInt(threshold)) where_row.push_back(i); break;
	    }
	}
    }
    else if(op == '<'){
	for(int i=0; i<record_num; i++){
	    string q; double w; unsigned int e; int r;
	    column[col_num]->getValue(i, q, w, e, r);
	    switch(column[col_num]->column_type){
		case STRING: if(q.compare(threshold) < 0) where_row.push_back(i); break;
		case DOUBLE: if(w < Util::strToDouble(threshold)) where_row.push_back(i); break;
		case UINT: if(e < Util::strToUint(threshold)) where_row.push_back(i); break;
		case INT: if(r < Util::strToInt(threshold)) where_row.push_back(i); break;
	    }
	}
    }
    else{
	cout << "Invalid op in where clause. " << endl;
	assert(false);
    }
}

void Table::where_and(int col_num, char op, string threshold){
    vector<int> erase_list; 
    if(op =='='){
	for(auto j = where_row.begin(); j != where_row.end(); ++j)
	{
    	    string q; double w; unsigned int e; int r;
	    column[col_num]->getValue(*j, q, w, e, r);
	    switch(column[col_num]->column_type){
		case STRING: if(q.compare(threshold) != 0) erase_list.push_back(*j); break;
		case DOUBLE: if(w != Util::strToDouble(threshold)) erase_list.push_back(*j); break;
		case UINT: if(e != Util::strToUint(threshold)) erase_list.push_back(*j); break;
		case INT: if(r != Util::strToInt(threshold)) erase_list.push_back(*j); break;
	    }
	}
    }
    else if(op =='>'){
	for(auto j = where_row.begin(); j != where_row.end(); ++j)
	{
    	    string q; double w; unsigned int e; int r;
	    column[col_num]->getValue(*j, q, w, e, r);
	    switch(column[col_num]->column_type){
		case STRING: if(q.compare(threshold) <= 0) erase_list.push_back(*j); break;
		case DOUBLE: if(w <= Util::strToDouble(threshold)) erase_list.push_back(*j); break;
		case UINT: if(e <= Util::strToUint(threshold)) erase_list.push_back(*j); break;
		case INT: if(r <= Util::strToInt(threshold)) erase_list.push_back(*j); break;
	    }
	}
    }
    if(op =='<'){
	for(auto j = where_row.begin(); j != where_row.end(); ++j)
	{
    	    string q; double w; unsigned int e; int r;
	    column[col_num]->getValue(*j, q, w, e, r);
	    switch(column[col_num]->column_type){
		case STRING: if(q.compare(threshold) >= 0) erase_list.push_back(*j); break;
		case DOUBLE: if(w >= Util::strToDouble(threshold)) erase_list.push_back(*j); break;
		case UINT: if(e >= Util::strToUint(threshold)) erase_list.push_back(*j); break;
		case INT: if(r >= Util::strToInt(threshold)) erase_list.push_back(*j); break;
	    }
	}
    }

    for(auto it=erase_list.begin(); it != erase_list.end(); ++it){
	auto a = find(where_row.begin(), where_row.end(), *it);
	if (a != where_row.end()) where_row.erase(a);
    }
}

void Table::where_or(int col_num, char op, string threshold){
    vector<int> add_list; 
    if(op =='='){
	for(int j = 0; j < record_num; j++)
	{
    	    string q; double w; unsigned int e; int r;
	    column[col_num]->getValue(j, q, w, e, r);
	    switch(column[col_num]->column_type){
		case STRING: if(q.compare(threshold) == 0) add_list.push_back(j); break;
		case DOUBLE: if(w == Util::strToDouble(threshold)) add_list.push_back(j); break;
		case UINT: if(e == Util::strToUint(threshold)) add_list.push_back(j); break;
		case INT: if(r == Util::strToInt(threshold)) add_list.push_back(j); break;
	    }
	}
    }
    else if(op =='>'){
	for(int j = 0; j < record_num; j++)
	{
    	    string q; double w; unsigned int e; int r;
	    column[col_num]->getValue(j, q, w, e, r);
	    switch(column[col_num]->column_type){
		case STRING: if(q.compare(threshold) > 0) add_list.push_back(j); break;
		case DOUBLE: if(w > Util::strToDouble(threshold)) add_list.push_back(j); break;
		case UINT: if(e > Util::strToUint(threshold)) add_list.push_back(j); break;
		case INT: if(r > Util::strToInt(threshold)) add_list.push_back(j); break;
	    }
	}
    }
    else if(op =='<'){
	for(int j = 0; j < record_num; j++)
	{
    	    string q; double w; unsigned int e; int r;
	    column[col_num]->getValue(j, q, w, e, r);
	    switch(column[col_num]->column_type){
		case STRING: if(q.compare(threshold) < 0) add_list.push_back(j); break;
		case DOUBLE: if(w < Util::strToDouble(threshold)) add_list.push_back(j); break;
		case UINT: if(e < Util::strToUint(threshold)) add_list.push_back(j); break;
		case INT: if(r < Util::strToInt(threshold)) add_list.push_back(j); break;
	    }
	}
    }

    for(auto it=add_list.begin(); it != add_list.end(); ++it){
	
	if(find(where_row.begin(), where_row.end(), (*it)) == where_row.end()) where_row.push_back(*it);
    }
    // sort where_row vector in ascending order 
    sort(where_row.begin(), where_row.end());
}

void Table::Join(Table *t1, Table *t2, int c1, int c2, int printRecord, bool isFirst){

    // if second join
    if(!isFirst){ t1 = this;
	//TODO: implement the secondary join	
	jointbl_ptr.push_back(t2);
	joincol_num.push_back(c2);	
	


	return;
	}
	
    	jointbl_ptr.push_back(t1);
	jointbl_ptr.push_back(t2);
	joincol_num.push_back(c1);
	joincol_num.push_back(c2);

    	TransMap transmap = Column::makeHashTable(t1->column[c1], t2->column[c2]);
    	TransMap reverse_transmap = Column::makeHashTable(t2->column[c2], t1->column[c1]);
	TransMap::iterator it;
    	unordered_map<unsigned int, inter_set> mid_storage; // not used after Join
    	vector<pair<int, int>> record_set; //TODO: change the ds to vector<vector<int>>
		  
	for(it = transmap.begin(); it!=transmap.end(); ++it){
	    mid_storage.insert({it->first, inter_set()});
	}

	for(int i=0; i< t1->record_num; i++){
	    it = transmap.find(t1->column[c1]->getRawFromIndex(i));
	    if(it==transmap.end()) continue;
	    else mid_storage[it->first].c1_records.push_back(i);
	}

	for(int i=0; i<t2->record_num; i++){
	    it = reverse_transmap.find(t2->column[c2]->getRawFromIndex(i));
	    if(it==reverse_transmap.end()) continue;
	    else mid_storage[it->second].c2_records.push_back(i);
	}
	// make record_set
	unordered_map<unsigned int, inter_set>::iterator mid_it;
	for(mid_it = mid_storage.begin(); mid_it != mid_storage.end(); ++mid_it){
	    inter_set temp = mid_it->second;
	    for(auto c1_it = temp.c1_records.begin(); c1_it != temp.c1_records.end(); ++c1_it){
		for(auto c2_it=temp.c2_records.begin(); c2_it != temp.c2_records.end(); ++c2_it){
		    record_set.push_back({*c1_it, *c2_it});
		}
	    }
	}
	int _printRecord = printRecord < record_set.size() ? printRecord : record_set.size();	
	int i =0;
	// print the join record index set
	cout << "Join record index set: " << endl;
	for(auto rs_it = record_set.begin(); i<_printRecord; i++) {	
	    cout << "[" << rs_it->first << ", " << rs_it->second << "]" << endl;
	    rs_it++;
	}
	
	// print the join result
	cout << " Join Result: " << endl;
	i = 0;
	string s;
    	double d;
	unsigned int u;
	int z;
	t1->printColName(false);
	cout << " || ";
	t2->printColName(true);
	for(auto rs_it = record_set.begin(); i<_printRecord; i++){
	    t1->getRecord(rs_it->first, false);
	    cout << " || ";
	    t2->getRecord(rs_it->second);
	    rs_it++;
	}
}


/*void Table::materialize(Table* one, Table* two){
    //int join_num = inter.size();
    //if(join_num == 1)
    //{
	//for(auto it=inter[0].record_set.begin(); it!=inter[0].record_set.end(); ++it){
	  //  int c1_index = it->first;
	    //int c2_index = it->second;
	   // one->getRecordNoLine(it->first);
	   // two->getRecord(it->second);
//	}
 //   }


    vector<Column*> mat_columns;
    vector<vector<int>> mat_records;
    for(int i=0; i<inter.size(); i++){
	for(auto it=inter[i].record_set.begin(); it!=inter[i].record_set.end(); ++it){

	}
    }
}
*/

//void Table::getMemSize();
