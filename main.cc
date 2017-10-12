#include "Table.h"
#include "util.h"

#include <iostream>
#include <stdlib.h>
#include <sys/resource.h>
#include <sys/time.h>
#include <unistd.h>
using namespace std;

int main(){

struct rusage usage;
struct timeval start, end;
string sensors_name[5] = {"data/sensors.csv", "sensors", "SID", "EID", "TYPE"};
string entities_name[5] = {"data/entities.csv", "entities", "EID", "NAME", "TYPE"};
string sample_game_name[15] = {"data/sample-game.csv", "sample-game", "SID", "TS", "X", "Y", "Z", "V", "A", "VX", "VY", "VZ", "AX", "AY", "AZ"};
//string full_game_name[14] = {"sample-game", "SID", "TS", "X", "Y", "Z", "V", "A", "VX", "VY", "VZ", "AX", "AY", "AZ"};


//Table_3<unsigned int, unsigned int, unsigned int>* t_sensors = new Table_3<unsigned int, unsigned int, unsigned int>(sensors_name, 42);
//Table_3<unsigned int, string, unsigned int>* t_entities = new Table_3<unsigned int, string, unsigned int>(entities_name, 21);
getrusage(RUSAGE_SELF, &usage);
start = usage.ru_utime;
Table_13<unsigned int, double, int, int, int, unsigned int, unsigned int, int, int, int, int, int, int>* t_sample_game = new Table_13<unsigned int, double, int, int, int, unsigned int, unsigned int, int, int, int, int, int, int>(sample_game_name, 1048576);
getrusage(RUSAGE_SELF, &usage);
end = usage.ru_utime;
cout << "StartTime to load sample table: " << start.tv_sec << "." << start.tv_usec << endl;
cout << "EndTime to load sample table: " << end.tv_sec << "." << end.tv_usec << endl;
cout << "Use memory with table load: " << usage.ru_maxrss/(1024*1024) << " Mbytes" <<  endl;

/*
t_sample_game->col_0->edict->get_record(0);
t_sample_game->col_1->edict->get_record(1);
t_sample_game->col_2->edict->get_record(2);
t_sample_game->col_3->edict->get_record(3);
t_sample_game->col_4->edict->get_record(4);
t_sample_game->col_5->edict->get_record(5);
t_sample_game->col_6->edict->get_record(6);
t_sample_game->col_7->edict->get_record(7);
t_sample_game->col_8->edict->get_record(8);
t_sample_game->col_9->edict->get_record(9);
t_sample_game->col_1->edict->get_record(10);
t_sample_game->col_1->edict->get_record(11);
t_sample_game->col_1->edict->get_record(12);
t_sample_game->col_1->edict->get_record(13);
t_sample_game->col_1->edict->get_record(14);
t_sample_game->col_1->edict->get_record(15);
t_sample_game->col_1->edict->get_record(16);
t_sample_game->col_1->edict->get_record(17);
t_sample_game->col_1->edict->get_record(18);
t_sample_game->col_1->edict->get_record(19);
*/
t_sample_game->sid_40();
t_sample_game->v_less_5000000();
//t_sample_game->col_1->edict->print_record(10,20, false);
//select('*', t_sample_game->col_0->equal(40), t_sample_game);

//delete t_sample_game;


//delete t_sensors;
//delete t_entities;
delete t_sample_game;

//getrusage(RUSAGE_SELF, &usage);
//cout << "Use memory after deleting: " << usage.ru_maxrss/(1024*1024) << " Mbytes" <<  endl;

return 0;
}
