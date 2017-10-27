#include <iostream>
#include <stdlib.h>
#include <sys/resource.h>
#include <sys/time.h>
#include <unistd.h>

#include "Table.h"

using namespace std;

int main(){

cout << "start " << endl;
struct rusage usage;
struct timeval start, end;
vector<string> sensors_name {"data/sensors.csv", "sensors", "SID", "unsigned int", "EID", "unsigned int", "TYPE", "unsigned int"};
vector<string> entities_name {"data/entities.csv", "entities", "EID", "unsigned int", "NAME", "string", "TYPE", "unsigned int"};
vector<string> sample_game_name {"data/sample-game.csv", "sample-game", "SID", "unsigned int", "TS", "double", "X", "int", "Y", "int", "Z", "int", "V", "unsigned int", "A", "unsigned int", "VX", "int", "VY", "int", "VZ", "int", "AX", "int", "AY", "int", "AZ", "int"};

getrusage(RUSAGE_SELF, &usage);
start = usage.ru_utime;
/* table load */
Table* t_sensors = new Table(sensors_name, 42);
Table* t_entities = new Table(entities_name, 21);
Table* t_sample_game = new Table(sample_game_name, 1048576);

getrusage(RUSAGE_SELF, &usage);
end = usage.ru_utime;
cout << "Time to load sample table: " << (end.tv_sec+end.tv_usec/100000.0) - (start.tv_sec + start.tv_usec/100000.0) << " sec" << endl;
cout << "Use memory with table load: " << usage.ru_maxrss/(1024*1024) << " Mbytes" <<  endl;


/* table select */



//query 1-1
getrusage(RUSAGE_SELF, &usage);
start = usage.ru_utime;
Table* join1_1 = new Table();
//cout << "join1_1 - where_row: " << join1_1->where_row.size() << endl;
join1_1->Join(t_sample_game, t_sensors, 0, 0, 10);
join1_1->getResult(10);
getrusage(RUSAGE_SELF, &usage);
end = usage.ru_utime;
cout << "Query 1-1 time: " << (end.tv_sec+end.tv_usec/100000.0) - (start.tv_sec + start.tv_usec/100000.0) << " sec" << endl;
t_sample_game->reset();
t_sensors->reset();

//query 2-1
getrusage(RUSAGE_SELF, &usage);
start = usage.ru_utime;
Table* join2_1 = new Table();
join2_1->Join(t_sample_game, t_sensors, 0, 0, 10);
cout << "record set size: " << join2_1->record_set.size() << endl;
join2_1->where(0, 5, '>', "5000000");
for(auto it=join2_1->where_row.begin(); it!=join2_1->where_row.end(); ++it) {cout << (*it) << endl;}
join2_1->where_and(1, 2, '=', "2");
cout << "record set size: " << join2_1->record_set.size() << endl;
for(auto it=join2_1->where_row.begin(); it!=join2_1->where_row.end(); ++it) {cout << (*it) << endl;}
join2_1->getResult(10);
getrusage(RUSAGE_SELF, &usage);
end = usage.ru_utime;
cout << "Query 2-1 time: " << (end.tv_sec+end.tv_usec/100000.0) - (start.tv_sec + start.tv_usec/100000.0) << " sec" << endl;
t_sample_game->reset();
t_sensors->reset();

//query 2-2
getrusage(RUSAGE_SELF, &usage);
start = usage.ru_utime;
Table* join2_2 = new Table();

t_sample_game->where(0, 5, '>', "5000000");
t_sensors->where(1, 2, '=', "2");
join2_2->Join(t_sample_game, t_sensors, 0, 0, 10);
join2_2->getResult(10);
getrusage(RUSAGE_SELF, &usage);
end = usage.ru_utime;
cout << "Query 2-2 time: " << (end.tv_sec+end.tv_usec/100000.0) - (start.tv_sec + start.tv_usec/100000.0) << " sec" << endl;
delete join2_2;
t_sample_game->reset();
t_sensors->reset();

//query 3-1
//Table* join3_1 = new Table();
//join3_1->Join(


/*Table join*/
/*
Table* join_table = new Table();
join_table->Join(t_sample_game, t_sensors, 0, 0, 20);
*/
//Table* join_table2 = new Table();
//join_table2->Join(t_sample_game, t_sensors, 0, 0, 100);

delete t_sensors;
delete t_entities;
delete t_sample_game;
//delete join_table;
//delete join_table2;
//getrusage(RUSAGE_SELF, &usage);
//cout << "Use memory after deleting: " << usage.ru_maxrss/(1024*1024) << " Mbytes" <<  endl;

return 0;
}

