#include "PackedArray.h" 
#include <vector>
#include <string>

#include "VTable.h"
#include "VSpace.h"
using namespace std;
class Delta {
    public:
	Delta(){};
	~Delta(){};
	void Insert(vector<string> column_value, int tx_time){ 
	    records.push_back(column_value);
	    tombstone.push_back(false);
	    is_versioned.push_back(false);
	    insert_time.push_back(tx_time);
	};
	void Delete(int lineNumber) { tombstone[lineNumber]=true;};
	void Scan(VTable* v_table, vector<VSpace>& v_space, int record_num, int col_ind, char op, string threshold, int tx_time) {
	    //TODO: find and print the corresponding raw_record.
	    vector<int> corres_index;
	    vector<bool> corres_version;
	    for(int i=0; i<tombstone.size(); i++){
	    	if(tombstone[i]) continue;
		if(insert_time[i] > tx_time) continue;
		
		if(is_versioned[i]) { //if it has version
		    corres_version.push_back(true);
		    corres_index.push_back(i);
		}
		else {
		    corres_version.push_back(false);
		    corres_index.push_back(i);
		}
	    }
	    //print
	    for(int i=0; i<corres_index.size(); i++){
		if(!corres_version[i]) { printDeltaRecord(corres_index[i]); }
		else { v_space[v_table->v_table[ record_num + corres_index[i] ] - 1].printRecent(tx_time); } //TODO
	    }	
	}

	void printDeltaRecord(int index){
	    for(string s: records[index])
	    {
		cout << s;
		if(s != *records[index].end()){ cout << "|";}
	    } cout << endl;
	}

	vector<vector<string>> records; // 어떻게??
	vector<bool> tombstone;
	vector<bool> is_versioned;
	vector<int> insert_time;
	VSpace* v_space;
};
