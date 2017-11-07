#include "Table.h"

using namespace std;
Table::Table(){
record_num=0;
col_num=0;
isEmpty = true;
where_row = vector<int> {};
jointbl_ptr = vector<Table*> {};
joincol_num = vector<int> {};
for(int i=0; i<col_num; i++){
    column[i] = new Column();
}
//static_i = 0;
};

Table::Table(vector<string> table_info, int record_num_){
    //set the metadata
    isEmpty = false;
  //  static_i = 0;
    string datapath = table_info[0];
    t_name = table_info[1];
    record_num = record_num_;
    for(int i=0; i<record_num; i++)
    {
	where_row.push_back(i);
    }
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
void Table::getResult(int recordNumber){
    // print maximum recordNumber results.
    string s; double d; unsigned int u; int i;
    int count=0;
    cout << "----RESULT----" << endl;
    if(jointbl_ptr.size() == 0)
    {
	for(int j: select_column)
	{
	    cout << column_name[j] << "|";
	} cout << endl;
	cout << "----------------------------------------" << endl; 
	for(int k: where_row)
	{
	    getRecord(k);
	    count++;
	    if(count >= recordNumber) return;
	}
    }
    else {
	int tbl_num = jointbl_ptr.size();
	for(int j=0; j<tbl_num; j++){
	    for(int k=0; k<jointbl_ptr[j]->col_num; k++){
		cout << jointbl_ptr[j]->column_name[k] << "|";
	    } if(j!=tbl_num - 1) {cout << " || " ;} else { cout << endl; }
	}
	
	for(int l: where_row){
	    for(int j=0; j<tbl_num; j++){
		jointbl_ptr[j]->getRecord(record_set[l][j], false);
	    	if(j!=tbl_num - 1) {cout << " || " ;} else { cout << endl; }
	    }
	    count++;
	    if(count >= recordNumber) return;
	}
    }
}
/*
void Table::putJoinTable(Table* t, int col){
    jointbl_ptr.push_back(t);
    joincol_num.push_back(col);
}
void Table::outJoinTable(){
    jointbl_ptr.clear();
    joincol_num.clear();
}*/
void Table::select(vector<int> column_list){
    select_column.clear();
    for(auto it=column_list.begin(); it!= column_list.end(); ++it){
	int j = (*it);
	select_column.push_back(j);
    }
}

void Table::where(int table_num, int col_num, char op, string threshold){
    // update where_row
    where_row.clear();
    Table* tbl = this;
    if(jointbl_ptr.size() != 0) {
    tbl = jointbl_ptr[table_num];
    if(op == '='){
	for(int i=0; i<record_num; i++){
	    string q; double w; unsigned int e; int r;
	    tbl->column[col_num]->getValue(record_set[i][table_num], q, w, e, r);
	    switch(tbl->column[col_num]->column_type){
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
	    tbl->column[col_num]->getValue(record_set[i][table_num], q, w, e, r);
	    switch(tbl->column[col_num]->column_type){
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
	    tbl->column[col_num]->getValue(record_set[i][table_num], q, w, e, r);
	    switch(tbl->column[col_num]->column_type){
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
    // if no Jointable
    else{
    if(op == '='){
	for(int i=0; i<record_num; i++){
	    string q; double w; unsigned int e; int r;
	    tbl->column[col_num]->getValue(i, q, w, e, r);
	    switch(tbl->column[col_num]->column_type){
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
	    tbl->column[col_num]->getValue(i, q, w, e, r);
	    switch(tbl->column[col_num]->column_type){
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
	    tbl->column[col_num]->getValue(i, q, w, e, r);
	    switch(tbl->column[col_num]->column_type){
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

    //cout << "where row from " << where_row[0] << " to " << where_row[where_row.size() -1] << endl;
}
void Table::where_and(int table_num, int col_num, char op, string threshold){
    vector<int> erase_list;
    int i=0;
    Table* tbl=this;
    if(jointbl_ptr.size() != 0){
    tbl = jointbl_ptr[table_num];
    if(op =='='){
	for(int j: where_row)
	{
    	    string q; double w; unsigned int e; int r;
	    tbl->column[col_num]->getValue(record_set[j][table_num], q, w, e, r);
	    switch(tbl->column[col_num]->column_type){
		case STRING: if(q.compare(threshold) != 0) erase_list.push_back(i); break;
		case DOUBLE: if(w != Util::strToDouble(threshold)) erase_list.push_back(i); break;
		case UINT: if(e != Util::strToUint(threshold)) erase_list.push_back(i); break;
		case INT: if(r != Util::strToInt(threshold)) erase_list.push_back(i); break;
	    }
	    i++;
	}
    }
    else if(op =='>'){
	for(int j : where_row)
	{
    	    string q; double w; unsigned int e; int r;
	    tbl->column[col_num]->getValue(record_set[j][table_num], q, w, e, r);
	    switch(tbl->column[col_num]->column_type){
		case STRING: if(q.compare(threshold) <= 0) erase_list.push_back(i); break;
		case DOUBLE: if(w <= Util::strToDouble(threshold)) erase_list.push_back(i); break;
		case UINT: if(e <= Util::strToUint(threshold)) erase_list.push_back(i); break;
		case INT: if(r <= Util::strToInt(threshold)) erase_list.push_back(i); break;
	    }
	    i++;
	}
    }
    else if(op =='<'){
	for(int j : where_row)
	{
    	    string q; double w; unsigned int e; int r;
	    tbl->column[col_num]->getValue(record_set[j][table_num], q, w, e, r);
	    switch(tbl->column[col_num]->column_type){
		case STRING: if(q.compare(threshold) >= 0) erase_list.push_back(i); break;
		case DOUBLE: if(w >= Util::strToDouble(threshold)) erase_list.push_back(i); break;
		case UINT: if(e >= Util::strToUint(threshold)) erase_list.push_back(i); break;
		case INT: if(r >= Util::strToInt(threshold)) erase_list.push_back(i); break;
	    }
	    i++;
	}
    }
    }
    //if no Jointable
    else {

    if(op =='='){
	for(int j: where_row)
	{
    	    string q; double w; unsigned int e; int r;
	    tbl->column[col_num]->getValue(j, q, w, e, r);
	    switch(tbl->column[col_num]->column_type){
		case STRING: if(q.compare(threshold) != 0) erase_list.push_back(i); break;
		case DOUBLE: if(w != Util::strToDouble(threshold)) erase_list.push_back(i); break;
		case UINT: if(e != Util::strToUint(threshold)) erase_list.push_back(i); break;
		case INT: if(r != Util::strToInt(threshold)) erase_list.push_back(i); break;
	    }
	    i++;
	}
    }
    else if(op =='>'){
	for(int j : where_row)
	{
    	    string q; double w; unsigned int e; int r;
	    tbl->column[col_num]->getValue(j, q, w, e, r);
	    switch(tbl->column[col_num]->column_type){
		case STRING: if(q.compare(threshold) <= 0) erase_list.push_back(i); break;
		case DOUBLE: if(w <= Util::strToDouble(threshold)) erase_list.push_back(i); break;
		case UINT: if(e <= Util::strToUint(threshold)) erase_list.push_back(i); break;
		case INT: if(r <= Util::strToInt(threshold)) erase_list.push_back(i); break;
	    }
	    i++;
	}
    }
    else if(op =='<'){
	for(int j : where_row)
	{
    	    string q; double w; unsigned int e; int r;
	    tbl->column[col_num]->getValue(j, q, w, e, r);
	    switch(tbl->column[col_num]->column_type){
		case STRING: if(q.compare(threshold) >= 0) erase_list.push_back(i); break;
		case DOUBLE: if(w >= Util::strToDouble(threshold)) erase_list.push_back(i); break;
		case UINT: if(e >= Util::strToUint(threshold)) erase_list.push_back(i); break;
		case INT: if(r >= Util::strToInt(threshold)) erase_list.push_back(i); break;
	    }
	    i++;
	}
    }
    }

    int k=0;
    for(auto it=erase_list.begin(); it != erase_list.end(); ++it){
    	//cout << *(where_row.begin() + ((*it)-k)) << endl;
	where_row.erase(where_row.begin() + ((*it) - k));
    	k++;
    }


    //cout << "where row from " << where_row[0] << " to " << where_row[where_row.size() -1] << endl;
}

//DEPRECATED
void Table::where_or(int table_num, int col_num, char op, string threshold){
    vector<int> add_list; 
    Table* tbl = this;
    if(jointbl_ptr.size() != 0){
	tbl = jointbl_ptr[table_num];
    }
    
    
    if(op =='='){
	for(int j = 0; j < record_num; j++)
	{
    	    string q; double w; unsigned int e; int r;
	    tbl->column[col_num]->getValue(j, q, w, e, r);
	    switch(tbl->column[col_num]->column_type){
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
	    tbl->column[col_num]->getValue(j, q, w, e, r);
	    switch(tbl->column[col_num]->column_type){
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
	    tbl->column[col_num]->getValue(j, q, w, e, r);
	    switch(tbl->column[col_num]->column_type){
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

void Table::Join(Table *t1, Table *t2, int c1, int c2, bool isFirst){

    // if second join
    if(!isFirst)
    {
	//TODO: implement the secondary join	
	jointbl_ptr.push_back(t2);
	joincol_num.push_back(c2);
	// 1. make transmap of related two columns.
    	TransMap transmap = Column::makeHashTable(t1->column[c1], t2->column[c2]);
    	TransMap reverse_transmap = Column::makeHashTable(t2->column[c2], t1->column[c1]);
    	unordered_map<unsigned int, vector<int>> mid_storage; // not used after Join
    	//vector<pair<int, int>> record_set; //TODO: change the ds to vector<vector<int>>

	for(auto it = transmap.begin(); it!=transmap.end(); ++it)
	{
	    mid_storage.insert({it->first, vector<int>{}});
	}
	
	//TODO: optimization : you shouldn't traverse whole table records but record_set
	int col_index = 0;
	for(auto jointbl_ptr_it : jointbl_ptr)
	{
	    if(jointbl_ptr_it == t1) break;
	    col_index++;
	}

	//2. make mid_storage of latter column.
	
	//for(int i=0; i<t2->record_num; i++){
	for(int i: t2->where_row)
	{
	    auto it = reverse_transmap.find(t2->column[c2]->getRawFromIndex(i));
	    if(it==reverse_transmap.end()) continue;
	    else mid_storage[it->second].push_back(i);
	}
	
	// make record_set
	int ii=0;
	vector<vector<int>> ret;

	for(auto it=record_set.begin(); it!=record_set.end(); ++it)
	{
	    int c1_index = (*it)[col_index]; // c1's record number of record set
	    unsigned int c1_bitValue = jointbl_ptr[col_index]->column[col_index]->getRawFromIndex(c1_index);
	    for(auto it_1=mid_storage.begin(); it_1 != mid_storage.end(); ++it_1)
	    {
		if(it_1->first == c1_bitValue)
		{
		    for(auto it_2=it_1->second.begin(); it_2 != it_1->second.end(); ++it_2)
	    	    {
    			ret.push_back(vector<int> {});
			for(int iii: *it)
			{
			    ret[ii].push_back(iii);
		    	}
	    		ret[ii].push_back(*it_2);
    			ii++;
		    }
		}
	    }
	}
	
	record_set = ret;
	record_num = record_set.size();
    	return;
    }
	
    else 
    {  //first join

	jointbl_ptr.push_back(t1);
	jointbl_ptr.push_back(t2);
	joincol_num.push_back(c1);
	joincol_num.push_back(c2);

    	TransMap transmap = Column::makeHashTable(t1->column[c1], t2->column[c2]);
    	TransMap reverse_transmap = Column::makeHashTable(t2->column[c2], t1->column[c1]);
    	MidStor mid_storage; // not used after Join
    	//vector<pair<int, int>> record_set; //TODO: change the ds to vector<vector<int>>

	for(auto it = transmap.begin(); it!=transmap.end(); ++it)
	{
	    mid_storage.insert({it->first, inter_set()});
	}

	//for(int i=0; i< t1->record_num; i++){
	for(int i: t1->where_row)
	{
	    auto it = transmap.find(t1->column[c1]->getRawFromIndex(i));
	    if(it==transmap.end()) continue;
	    else mid_storage[it->first].c1_records.push_back(i);
	}

	//for(int i=0; i<t2->record_num; i++){
	for(int i: t2->where_row)
	{
	    auto it = reverse_transmap.find(t2->column[c2]->getRawFromIndex(i));
	    if(it==reverse_transmap.end()) continue;
	    else mid_storage[it->second].c2_records.push_back(i);
	}

	// make record_set
	int ii=0;
	for(auto mid_it = mid_storage.begin(); mid_it != mid_storage.end(); ++mid_it)
	{
	    inter_set temp = mid_it->second;
	    for(auto c1_it = temp.c1_records.begin(); c1_it != temp.c1_records.end(); ++c1_it)
	    {
		for(auto c2_it=temp.c2_records.begin(); c2_it != temp.c2_records.end(); ++c2_it)
		{
		    //record_set.push_back({*c1_it, *c2_it});
		    record_set.push_back(vector<int> {});
		    record_set[ii].push_back(*c1_it);
		    record_set[ii].push_back(*c2_it);
		    where_row.push_back(ii);
		    ii++;
		}
	    }
	}
	
	record_num = record_set.size();
    }
}

void Table::PartitionJoin(Table* t1, Table* t2, int c1, int c2){
    //first join
    high_resolution_clock::time_point begin, end;
    begin = high_resolution_clock::now();
    jointbl_ptr.push_back(t1);
    jointbl_ptr.push_back(t2);
    joincol_num.push_back(c1);
    joincol_num.push_back(c2);

    TransMap transmap = Column::makeHashTable(t1->column[c1], t2->column[c2]);
    TransMap reverse_transmap = Column::makeHashTable(t2->column[c2], t1->column[c1]);
    MidStor mid_storage; // not used after Join

    for(auto it = transmap.begin(); it!=transmap.end(); ++it){
	mid_storage.insert({it->first, inter_set()});
    }
   /* 
    for(int i: t1->where_row)
    {
	auto it = transmap.find(t1->column[c1]->getRawFromIndex(i));
	if(it==transmap.end());
	else mid_storage[it->first].c1_records.push_back(i);
    }

    for(int i: t2->where_row){
    	auto it = reverse_transmap.find(t2->column[c2]->getRawFromIndex(i));
	if(it==reverse_transmap.end());
	else mid_storage[it->second].c2_records.push_back(i);
	}*/
    cout << "mid_storage size: " << mid_storage.size() << endl;	
    thread firstThread[2];
    thread secondThread[4];
	firstThread[0] = thread(&Table::firstCallback, this, ref(transmap), ref(mid_storage), ref(t1), ref(c1), 0);
	firstThread[1] = thread(&Table::_firstCallback, this, ref(reverse_transmap), ref(mid_storage), ref(t2), ref(c2), 1);
	//firstThread[2] = thread(&Table::_firstCallback, this, ref(reverse_transmap), ref(mid_storage), ref(t2), ref(c2), 0);
	//firstThread[3] = thread(&Table::_firstCallback, this, ref(reverse_transmap), ref(mid_storage), ref(t2), ref(c2), 1);
/*    for(int i=0; i<4; i++)
    {
	firstThread[i] = thread(&Table::firstCallback, this, ref(transmap), ref(mid_storage), ref(t1), ref(c1), i);
    }*/
    for(int i=0; i<2; i++)
    {
	firstThread[i].join();
    }
    for(int i=0; i<4; i++)
    {
	secondThread[i] = thread(&Table::secondCallback, this, ref(mid_storage), i);
    }
    for(int i=0; i<4; i++)
    {
	secondThread[i].join();
    }
    for(int i=0; i<static_i; i++){
	where_row.push_back(i);
	//cout << i << ": where_Row" << endl;
    }

   record_num = record_set.size();
    // copy it: cout << duration_cast<microseconds>(high_resolution_clock::now() - begin).count()/1000000.0 << endl;
}
void Table::firstCallback(TransMap& transmap, MidStor& mid_storage, Table* t1, int c1, int no){
    //int end = (int)ceil(t1->where_row.size()/2.0*(no+1));
    int end = t1->where_row.size();
    for(int start=0; start < end; start++)
    {
	auto it = transmap.find(t1->column[c1]->getRawFromIndex(t1->where_row[start]));
	if(it==transmap.end());
	else{ 
	    mid_storage[it->first].c1_records.push_back(t1->where_row[start]);
	}
    }


}
void Table::_firstCallback(TransMap& reverse_transmap, MidStor& mid_storage, Table* t2, int c2, int no){
    //int end = (int)ceil(t2->where_row.size()/2.0*(no+1));
    int end = t2->where_row.size();
    for(int start=0; start < end; start++)
    {
	auto it = reverse_transmap.find(t2->column[c2]->getRawFromIndex(t2->where_row[start]));
	if(it==reverse_transmap.end());
	else{
	    mid_storage[it->second].c2_records.push_back(t2->where_row[start]);
	}
    }
}
void Table::secondCallback(MidStor& mid_storage, int no){
	// make record_set
	//int static_ii = 0;
	vector<vector<int>> record_set_;
	int from = (int)ceil(mid_storage.size()/4*no);
	int to = (int)ceil(mid_storage.size()/4*(no+1));
	auto mid_it = mid_storage.begin();
	cout << from << ":from" << endl;
	cout << to << ": to" << endl;
	advance(mid_it, from);
	int i=0;
	int ii=0;
	while(i < to - from){
	    inter_set temp = mid_it->second;
	    for(auto c1_it = temp.c1_records.begin(); c1_it != temp.c1_records.end(); ++c1_it){
		for(auto c2_it=temp.c2_records.begin(); c2_it != temp.c2_records.end(); ++c2_it){
		    //record_set.push_back({*c1_it, *c2_it});
		   // mtx.lock();
		    record_set_.push_back(vector<int> {});
		    record_set_[ii].push_back(*c1_it);
		    record_set_[ii].push_back(*c2_it);
		    ii++;
		    //static_i++;
		   // mtx.unlock();
		    //where_row.push_back(static_i++);
		    
		}
	    }
		i++;
		mid_it++;
	}
	mtx.lock();
	record_set.insert(end(record_set), begin(record_set_), end(record_set_));
	mtx.unlock();
	mtx.lock();
	static_i += record_set_.size();
	mtx.unlock();
}

void Table::reset(){
	select_column.clear();
	for(int i=0; i<col_num; i++){
	    select_column.push_back(i);
	}
	where_row.clear();
	for(int i=0; i<record_num; i++){
	    where_row.push_back(i);
	}
	jointbl_ptr.clear();
	joincol_num.clear();
	record_set.clear();
        record_num = column[0]->record_num;
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

void Table::getTblMemory(){
    int ret = 0;
    for(int i=0; i<col_num; i++){
	ret += column[i]->getColMemory();
    }
    ret += sizeof(string) * column_name.size();
    ret += sizeof(string) * column_type.size();
    ret += sizeof(int) * select_column.size();
    ret += sizeof(int) * where_row.size();
    ret += sizeof(Table*) * jointbl_ptr.size();
    ret += sizeof(int) * joincol_num.size();
    ret += sizeof(int) * jointbl_ptr.size()* record_set.size();
    cout << "----------------------MEMORY------------------------" << endl;
    cout << "Table " << t_name <<"'s memory: " << ret/1024.0/1024.0 << "M bytes. " << endl;
    cout << "----------------------------------------------------" << endl;
};
