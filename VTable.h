#include <unordered_map>

using namespace std;
// rid : v_space's index
// it starts from 1
typedef struct __vtable__ {
    __vtable__() {};
    unordered_map<int, int> v_table;
} VTable;
