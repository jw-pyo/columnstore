#include <vector>

using namespace std;
/*
enum {
    STRING,
    DOUBLE,
    UINT,
    INT
};*/

struct VRecord {
    public:
    VRecord(int tx_time, vector<string> _raw_value){
	CSN = tx_time;
	raw_value = _raw_value;
    };
    ~VRecord(){ raw_value.clear(); };
    void printRecord() {
	for(string s: raw_value){
	    cout << s ;
	    if(s!=*raw_value.end()) { cout << "|"; }
	} cout << endl;
    }
    int CSN;
    vector<string> raw_value;
};

struct VSpace {
    public:
    VSpace(int _r_id) { r_id = _r_id; };
    ~VSpace(){ v_records.clear(); };
    void printRecent(int tx_time){ // print recent record in given time
	for(auto it=v_records.rbegin(); it!=v_records.rend(); ++it){
	    if(tx_time > it->CSN) { (*it).printRecord(); break; }
	}
    }

    int recentCSN;
    int r_id;
    vector<VRecord> v_records;
};
