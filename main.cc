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
//Table* t_sample_game = new Table(sample_game_name, 1048576);

getrusage(RUSAGE_SELF, &usage);
end = usage.ru_utime;
cout << "Time to load sample table: " << (end.tv_sec+end.tv_usec/100000.0) - (start.tv_sec + start.tv_usec/100000.0) << " sec" << endl;
cout << "Use memory with table load: " << usage.ru_maxrss/(1024*1024) << " Mbytes" <<  endl;


/* table select */
t_entities->select(vector<int> {0,1});
/* where query */
vector<int> where_query = (t_entities->where_and(vector<int> {2, 1}, vector<char> {'=','='}, vector<string> {"1", "\"Ball 1\""}));
t_entities->getAllRecord();
t_entities->getAllRecord(&where_query);

/*Table join*/
//Table* join_table = new Table();
//join_table->Join(t_sensors->column[2], t_entities->column[2], 1600);
//join_table->Join(
//join_table->materialize(t_sensors, t_entities);

//t_sample_game->sid_40();
//t_sample_game->v_less_5000000();
//t_sample_game->col_1->edict->print_record(10,20, false);
//select('*', t_sample_game->col_0->equal(40), t_sample_game);

//delete t_sample_game;


delete t_sensors;
delete t_entities;
//delete t_sample_game;
//delete join_table;
//getrusage(RUSAGE_SELF, &usage);
//cout << "Use memory after deleting: " << usage.ru_maxrss/(1024*1024) << " Mbytes" <<  endl;

return 0;
}

