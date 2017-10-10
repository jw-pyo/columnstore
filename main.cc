#include "Table.h"
#include "util.h"

#include <iostream>
#include <stdlib.h>
#include <sys/resource.h>

using namespace std;

int main(){

struct rusage usage;

string sensors_name[5] = {"data/sensors.csv", "sensors", "SID", "EID", "TYPE"};
string entities_name[5] = {"data/entities.csv", "entities", "EID", "NAME", "TYPE"};
string sample_game_name[15] = {"data/sample-game.csv", "sample-game", "SID", "TS", "X", "Y", "Z", "V", "A", "VX", "VY", "VZ", "AX", "AY", "AZ"};
//string full_game_name[14] = {"sample-game", "SID", "TS", "X", "Y", "Z", "V", "A", "VX", "VY", "VZ", "AX", "AY", "AZ"};


Table_3<unsigned int, unsigned int, unsigned int>* t_sensors = new Table_3<unsigned int, unsigned int, unsigned int>(sensors_name, 42);
Table_3<unsigned int, string, unsigned int>* t_entities = new Table_3<unsigned int, string, unsigned int>(entities_name, 21);
Table_13<unsigned int, double, int, int, int, unsigned int, unsigned int, int, int, int, int, int, int>* t_sample_game = new Table_13<unsigned int, double, int, int, int, unsigned int, unsigned int, int, int, int, int, int, int>(sample_game_name, 1048576);
//t_sensors->col_2->print_sdict();
//t_sensors->col_1->edict->print_edict(-1);
//t_entities->col_1->edict->print_edict(-1);
t_sample_game->col_2->edict->print_edict(100000);
//t_sensors->col_2->edict->print_edict(-1);
//t_sensors->select("NAME")->filter("EID", LESS, 3);
//delete t_sample_game;

getrusage(RUSAGE_SELF, &usage);
delete t_sensors;
delete t_entities;
cout << "Use memory: " << usage.ru_maxrss/1024 << " Kbytes" <<  endl;

return 0;
}
