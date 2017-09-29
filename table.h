#include <stdio.h>
#include <stdarg.h>
#include <string>




template<typename T, typename ... Types>
class Table{

    public:
        Table();
        Table(const char* data);



                }


int main(int argc, char* argv[]) {
    // EID(u), NAME, TYPE
    Table<int(autoincrement), std::string, std::uint32_t> t_entities ("data/entities.csv");
    // SID(u), EID, TYPE
    Table<std::uint32_t, std::uint32_t, std::uint32_t> t_sensors ("data/sensors.csv");
    // SID(u), TS, X, Y, Z, V, A, VX, VY, VZ, AX, AY, AZ
    Table<std::uint32_t, double, int, int, int, std::uint32_t, std::uint32_t, int, int, int, int, int, int> t_events ("data/full-game.csv");

    
    }
