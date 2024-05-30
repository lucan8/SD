#include <iostream>
#include <stdint.h>
#include <math.h>
#include <vector>
#include <tuple>
using namespace std;


//20p
//Going with both routes, at each pair we choose the value that gives the smallest diff
enum change{new_min, new_max, none};
bool operator <(const tuple<change, int64_t, int64_t>& p1, 
                const tuple<change, int64_t, int64_t>& p2){
        return get<1>(p1) < get<1>(p2);
}

tuple<change, int64_t, int64_t> determineChoice(const pair<int64_t, int64_t>& min_max, 
                                                int64_t new_val){
     if (new_val > min_max.second)
            return make_tuple(new_max, new_val - min_max.first, new_val);
    else if (new_val < min_max.first)
            return make_tuple(new_min, min_max.second - new_val, new_val);
        else
            return make_tuple(none, min_max.second - min_max.first, new_val);
}


void changeMinMax(pair<int64_t, int64_t>& min_max,
                  const tuple<change, int64_t, int64_t>& choice){
    
    switch (get<0>(choice)){
            case new_max:
                min_max.second = get<2>(choice);
                break;
            
            case new_min:
                min_max.first = get<2>(choice);
                break;

            default:
                break;
        }
}
int main(){
    uint32_t nr_fighters_pairs;
    cin >> nr_fighters_pairs;

    //Going through with both routes and chosing the best one
    int64_t dac, samurai;
    cin >> dac >> samurai;

    //At first the minimum and maximum are equal
    pair<int64_t, int64_t>  min_max_dac(dac, dac), 
                            min_max_samurai(samurai, samurai);
    
    while (--nr_fighters_pairs){
        cin >> dac >> samurai;
        
        //Choosing best option for both routes, change made, new_difference, value tested
        tuple<change, int64_t, int64_t> choice_dac = 
                                        min(determineChoice(min_max_dac, dac), 
                                            determineChoice(min_max_dac, samurai)),

                                        choice_samurai = 
                                        min(determineChoice(min_max_samurai, dac), 
                                            determineChoice(min_max_samurai, samurai));

        changeMinMax(min_max_dac, choice_dac);
        changeMinMax(min_max_samurai, choice_samurai);
    }

    cout << min(min_max_dac.second - min_max_dac.first,
                min_max_samurai.second - min_max_samurai.first)  << '\n';
}