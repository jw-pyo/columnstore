#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <vector>
#include <set>
#include <tuple>
#include <utility>


using namespace std;
template<typename T>
class SortedDict {

    public:
        SortedDict<T>() {};
        SortedDict (T[] &dataArr) {

            /*  1. count the distinct value
             *  2. sort
             */
            encoded_dict.insert(dataArr, dataArr + sizeof(T));

        };

        set<T> encoded_dict;
};

template<typename T1>
class Column {
    public:
        Column<T1>(int num) {
            items = (T1 *)malloc(sizeof(T1)*num);
        };

        T1* items;
        SortedDict s_dict;
        Column<T1>* prev=NULL;
};

/*
template<typename T, typename ...Types>
class Table{

    public:
        Table<T a, Types ...args>(int num) {
            
            int arg_num = sizeof...(Types);
            for(int i=0; i<arg_num; i++)
                {
                    Column<typeid(T)> col(3);

                }

        
        
        
        };
        Table(const char* data);

    Column<T>* col;

};

int main(int argc, char* argv[]) {
    // EID(u), NAME, TYPE
//    Table<int(autoincrement), std::string, std::uint32_t> t_entities ("data/entities.csv");
    // SID(u), EID, TYPE
//    Table<std::uint32_t, std::uint32_t, std::uint32_t> t_sensors ("data/sensors.csv");
    // SID(u), TS, X, Y, Z, V, A, VX, VY, VZ, AX, AY, AZ
//    Table<std::uint32_t, double, int, int, int, std::uint32_t, std::uint32_t, int, int, int, int, int, int> t_events ("data/full-game.csv");

  Column<int> col_int(5);
  col_int.items= {2,4,5,6,7};
  for(int i=0; i<5; i++)
  printf("%d\n", col_int.items[i]);
  return 0;
    }
    */
