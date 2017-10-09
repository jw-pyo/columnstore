//#include "Column.h"

#include "PackedArray.h"
//#include "DataArray.h"
#include "Table.h"
#include "util.h"

#include <stdio.h>
#include <iostream>
#include <vector>
#include <fstream>

using namespace std;

int main(){

string sensors_name[5] = {"data/sensors.csv", "sensors", "SID", "EID", "TYPE"};
string entities_name[5] = {"data/entities.csv", "entities", "EID", "NAME", "TYPE"};
string sample_game_name[15] = {"data/sample-game.csv", "sample-game", "SID", "TS", "X", "Y", "Z", "V", "A", "VX", "VY", "VZ", "AX", "AY", "AZ"};
//string full_game_name[14] = {"sample-game", "SID", "TS", "X", "Y", "Z", "V", "A", "VX", "VY", "VZ", "AX", "AY", "AZ"};

//DataArray_3<uint32_t, uint32_t, uint32_t>* sensors = new DataArray_3<uint32_t, uint32_t, uint32_t>(sensors_name, "data/sensors.csv", 42);
//DataArray_3<uint32_t, string, uint32_t>* entities = new DataArray_3<uint32_t, string, uint32_t>(entities_name, "data/entities.csv", 21);
//DataArray_13<uint32_t, double, int, int, int, uint32_t, uint32_t, int, int, int, int, int, int>* sample_game = new DataArray_13<uint32_t, double, int, int, int, uint32_t, uint32_t, int, int, int, int, int, int>(sample_game_name, "data/sample-game.csv", 1048576);
//put the dataarray into Table

Table_3<unsigned int, string, unsigned int>* t_sensors = new Table_3<unsigned int, string, unsigned int>(entities_name, 21);

//delete t_sensors;
//delete entities;
//delete sample_game;

//t_sensors->col_2->print_info();
//t_sensors->col_0->edict->print_edict(-1);
t_sensors->col_1->edict->print_edict(-1);
//t_sensors->col_2->edict->print_edict(-1);

/*
sample_game->col_1.print();

sensors->col_1.print();    
sensors->col_2.print_set();
sensors->col_2.print_max(); //would be 21 
printf("size of sample_game: %ld\n", sizeof(*sample_game));
printf("\n\n\n\n\n");
entities->col_2.allocate_sdict();
*/
return 0;
}
