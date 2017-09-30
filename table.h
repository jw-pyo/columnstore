#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <vector>
#include <set>
#include <tuple>
#include <utility>


using namespace std;
vector<string> split(const string &s, char delim) {
            vector<string> elems;
                split(s, delim, back_inserter(elems));
                    return elems;
};

/*
 * template<typename T>
class SortedDict {

    public:
        SortedDict<T>() {};
        SortedDict (T[] &dataArr) {

            //  1. count the distinct value
            //  2. sort
            //
            encoded_dict.insert(dataArr, dataArr + sizeof(T));

        };

        set<T> encoded_dict;
};
*/

template<typename T1>
class Column {
    public:
        Column<T1>(int num) {
            items = (T1 *)malloc(sizeof(T1)*num);
        };

        T1* items;
        //SortedDict s_dict;
        //Column<T1>* prev=NULL;
};


class Table<uint32_t, uint32_t, uint32_t> {

    public:
       // Table<T1, T2, T3>(int num) {
       //     
       //     Column<T1> col_1 = Column<T1>(num);
       //     Column<T2> col_2 = Column<T2>(num);
       //     Column<T3> col_3 = Column<T3>(num);
       // };

        Table(const char* data) {
        
        ifstream dataFile(data);
        string line;
        set<uint32_t> t1;
        set<uint32_t> t2;
        set<uint32_t> t3;

        while(getline(dataFile, line, '\n'))
            {
               vector<string> line_arr = split(line, ',');
               t1.insert(line_arr.get(0));
               t2.insert(line_arr.get(1));
               t3.insert(line_arr.get(2));
            }
        for(set<uint32_t>::iterator i = t1.begin(); i!= t1.end(); i++)
                printf(*i);
        };
    Column<uint32_t> col_1;
    Column<uint32_t> col_2;
    Column<uint32_t> col_3;
};
/*
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
