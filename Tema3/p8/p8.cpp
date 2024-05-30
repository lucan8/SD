#include <iostream>
#include <stdint.h>
#include <vector>
#include <numeric>
using namespace std;

//36P
const uint32_t modulo_number = 666013;
enum op_choices{insert_1 = 1, insert_2 = 2, sum3 = 3};
enum val_types{black, red};

pair<uint32_t, uint32_t> getMinMax(uint32_t v1, uint32_t v2){
    if (v1 < v2)
        return make_pair(v1, v2);
    return make_pair(v2, v1);
}


uint32_t myReduce(uint32_t init_val, uint32_t start, uint32_t end, const vector<uint32_t>& v){
    for (uint32_t i = start; i <= end; ++i)
        init_val = (init_val + v[i]) % modulo_number;
    
    return init_val;
}


//Ideea: rmq with sums
int main(){
    uint32_t nr_operations, last_black = 0, last_red = 0, final_sum = 0;
    cin >> nr_operations;

    vector<uint32_t> v;
    v.reserve(nr_operations);

    while (nr_operations--){
        uint16_t op_choice;
        cin >> op_choice;

        //Get rid of redundancy
        switch (op_choice){
            case insert_1:
                {
                    uint32_t val, pos;
                    cin >> pos >> val;
                    last_red = pos;

                    //Th index will be moved with 1 to the right
                    //If the insertions happens before the last_black elem
                    if (last_red <= last_black)
                        last_black++;

                    v.insert(v.begin() + pos, val);
                }
                break;
            case insert_2:
                {
                    uint32_t val, pos;
                    cin >> pos >> val;
                    last_black = pos;

                    //Th index will be moved with 1 to the right
                    //If the insertions happens before the last_red elem
                    if (last_black <= last_red)
                        last_red++;

                    v.insert(v.begin() + pos, val);
                }
                break;
            case sum3:
                {
                    pair<uint32_t, uint32_t> min_max = getMinMax(last_black, last_red);
                    final_sum = myReduce(final_sum, min_max.first, min_max.second, v);
                }
                break;
            default:
                break;
        }
    }
    cout << final_sum << endl;
    
}