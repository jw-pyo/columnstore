#include <iostream>
#include <stdlib.h>
#include <sys/resource.h>
#include <sys/time.h>
#include <unistd.h>

#include <thread>
#include <mutex>
#include <chrono>

#include "Table.h"

using namespace std;
using namespace std::chrono;

//static int static_i = 0;
int main(){

cout << "start " << endl;
high_resolution_clock::time_point begin, end;
vector<string> sensors_name {"data/sensors.csv", "sensors", "SID", "unsigned int", "EID", "unsigned int", "TYPE", "unsigned int"};
vector<string> entities_name {"data/entities.csv", "entities", "EID", "unsigned int", "NAME", "string", "TYPE", "unsigned int"};
vector<string> sample_game_name {"data/sample-game.csv", "sample-game", "SID", "unsigned int", "TS", "double", "X", "int", "Y", "int", "Z", "int", "V", "unsigned int", "A", "unsigned int", "VX", "int", "VY", "int", "VZ", "int", "AX", "int", "AY", "int", "AZ", "int"};

/* table load */
begin = high_resolution_clock::now();
Table* t_sensors = new Table(sensors_name, 42);
Table* t_entities = new Table(entities_name, 21);
Table* t_sample_game = new Table(sample_game_name, 1048576);
end = high_resolution_clock::now();
auto duration = duration_cast<microseconds>(end-begin).count()/1000000.0;
cout << "Elapsed time loading 3 tables: " << duration << " sec" << endl;

t_sensors->getTblMemory();
t_entities->getTblMemory();
t_sample_game->getTblMemory();
/* table select */

//query 1-1

begin = high_resolution_clock::now();
Table* join1_1 = new Table();
join1_1->Join(t_sample_game, t_sensors, 0, 0);
join1_1->getResult(5);
end = high_resolution_clock::now();
duration = duration_cast<microseconds>(end-begin).count()/1000000.0;
cout << "-------------------TIME--------------------" << endl;
cout << "Query 1-1 time: " << duration << " sec" << endl;
join1_1->getTblMemory();
t_sample_game->reset();
t_sensors->reset();

//1-1 partition();
begin = high_resolution_clock::now();
Table* part1_1 = new Table();

part1_1->PartitionJoin(t_sample_game, t_sensors, 0, 0);
part1_1->getResult(5);
end = high_resolution_clock::now();
duration = duration_cast<microseconds>(end-begin).count()/1000000.0;
cout << "-------------------TIME--------------------" << endl;
cout << "Query 1-1 Partition join time: " << duration << " sec" << endl;
part1_1->getTblMemory();
t_sample_game->reset();
t_sensors->reset();

//query 2-1
begin = high_resolution_clock::now();
Table* join2_1 = new Table();
join2_1->Join(t_sample_game, t_sensors, 0, 0);
join2_1->where(0, 5, '<', "1000000");
join2_1->where_and(1, 2, '=', "1");
join2_1->getResult(5);
end = high_resolution_clock::now();
duration = duration_cast<microseconds>(end-begin).count()/1000000.0;
cout << "-------------------TIME--------------------" << endl;
cout << "Query 2-1 time: " << duration << " sec" << endl;
join2_1->getTblMemory();
t_sample_game->reset();
t_sensors->reset();

//query 2-2
begin = high_resolution_clock::now();
Table* join2_2 = new Table();
join2_2->Join(t_sensors, t_sample_game, 0, 0);
join2_2->where(1, 5, '<', "1000000");
join2_2->where_and(0, 2, '=', "1");
join2_2->getResult(5);
end = high_resolution_clock::now();
duration = duration_cast<microseconds>(end-begin).count()/1000000.0;
cout << "-------------------TIME--------------------" << endl;
cout << "Query 2-2 time: " << duration << " sec" << endl;
join2_2->getTblMemory();
t_sample_game->reset();
t_sensors->reset();

//query 2-3
begin = high_resolution_clock::now();
Table* join2_3 = new Table();

t_sample_game->where(0, 5, '<', "1000000");
t_sensors->where(1, 2, '=', "1");
join2_3->Join(t_sample_game, t_sensors, 0, 0);
join2_3->getResult(5);
end = high_resolution_clock::now();
duration = duration_cast<microseconds>(end-begin).count()/1000000.0;
cout << "-------------------TIME--------------------" << endl;
cout << "Query 2-3 time: " << duration << " sec" << endl;
join2_3->getTblMemory();
delete join2_3;
t_sample_game->reset();
t_sensors->reset();

//query 2-4
begin = high_resolution_clock::now();
Table* join2_4 = new Table();

t_sample_game->where(1, 5, '<', "1000000");
t_sensors->where(0, 2, '=', "1");
join2_4->Join(t_sensors, t_sample_game, 0, 0);
join2_4->getResult(5);
end = high_resolution_clock::now();
duration = duration_cast<microseconds>(end-begin).count()/1000000.0;
cout << "-------------------TIME--------------------" << endl;
cout << "Query 2-4 time: " << duration << " sec" << endl;
join2_4->getTblMemory();
delete join2_4;
t_sample_game->reset();
t_sensors->reset();
//query 3-1
begin = high_resolution_clock::now();
Table* join3_1 = new Table();
join3_1->Join(t_sample_game, t_sensors, 0, 0);
join3_1->Join(t_sensors, t_entities, 1, 0, false);

join3_1->where(2, 1, '=', "\"Ball 1\"");
join3_1->where_and(0, 5, '<', "1000000");
join3_1->getResult(5);
end = high_resolution_clock::now();
duration = duration_cast<microseconds>(end-begin).count()/1000000.0;
cout << "-------------------TIME--------------------" << endl;
cout << "Query 3-1 time: " << duration << " sec" << endl;
join3_1->getTblMemory();
delete join3_1;
t_sample_game->reset();
t_sensors->reset();
t_entities->reset();

//query 3-2
begin = high_resolution_clock::now();
Table* join3_2 = new Table();
t_entities->where(2, 1, '=', "\"Ball 1\"");
t_sample_game->where(0, 5, '<', "1000000");
join3_2->Join(t_sample_game, t_sensors, 0, 0);
join3_2->Join(t_sensors, t_entities, 1, 0, false);
join3_2->getResult(5);
end = high_resolution_clock::now();
duration = duration_cast<microseconds>(end-begin).count()/1000000.0;
cout << "-------------------TIME--------------------" << endl;
cout << "Query 3-2 time: " << duration << " sec" << endl;
join3_2->getTblMemory();
delete join3_2;
t_sample_game->reset();
t_sensors->reset();
t_entities->reset();

//query 3-3
begin = high_resolution_clock::now();
Table* join3_3 = new Table();
join3_3->Join(t_sample_game, t_sensors, 0, 0);
join3_3->Join(t_sensors, t_entities, 1, 0, false);
join3_3->where(0, 5, '<', "1000000");
join3_3->where_and(2, 1, '=', "\"Ball 1\"");
join3_3->getResult(5);
end = high_resolution_clock::now();
duration = duration_cast<microseconds>(end-begin).count()/1000000.0;
cout << "-------------------TIME--------------------" << endl;
cout << "Query 3-3 time: " << duration << " sec" << endl;
join3_3->getTblMemory();
delete join3_3;
t_sample_game->reset();
t_sensors->reset();
t_entities->reset();

//query 3-4
begin = high_resolution_clock::now();
Table* join3_4 = new Table();
t_sample_game->where(0, 5, '<', "1000000");
t_entities->where(2, 1, '=', "\"Ball 1\"");
join3_4->Join(t_sample_game, t_sensors, 0, 0);
join3_4->Join(t_sensors, t_entities, 1, 0, false);
join3_4->getResult(5);
end = high_resolution_clock::now();
duration = duration_cast<microseconds>(end-begin).count()/1000000.0;
cout << "-------------------TIME--------------------" << endl;
cout << "Query 3-4 time: " << duration << " sec" << endl;
join3_4->getTblMemory();
delete join3_4;
t_sample_game->reset();
t_sensors->reset();
t_entities->reset();

//query 3-5
begin = high_resolution_clock::now();
Table* join3_5 = new Table();
t_sample_game->where(1, 5, '<', "1000000");
t_entities->where(2, 1, '=', "\"Ball 1\"");
join3_5->Join(t_sensors, t_sample_game, 0, 0);
join3_5->Join(t_sensors, t_entities, 1, 0, false);
join3_5->getResult(5);
end = high_resolution_clock::now();
duration = duration_cast<microseconds>(end-begin).count()/1000000.0;
cout << "-------------------TIME--------------------" << endl;
cout << "Query 3-5 time: " << duration << " sec" << endl;
join3_5->getTblMemory();
delete join3_5;
t_sample_game->reset();
t_sensors->reset();
t_entities->reset();


delete t_sensors;
delete t_entities;
delete t_sample_game;

return 0;
}

