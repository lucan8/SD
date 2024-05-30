#include <iostream>
#include <vector>
#include <stdint.h>
using namespace std;
//60p
int main(){
    uint16_t arr_size;
    cin >> arr_size;
    vector<uint64_t> arr(arr_size, 0);

    for (uint16_t i = 0; i < arr_size; ++i)
        cin >> arr[i];
    
    uint32_t nr_interesting = 0;

    for (uint16_t i = 0; i < arr.size() - 1; ++i){
        pair<uint64_t, uint16_t> minimum(arr[i], 0);
        uint16_t traversed_elem = 1;

        for (uint16_t j = i + 1; j < arr.size(); ++j){
            if (minimum.second >= traversed_elem / 2 + traversed_elem % 2)
                ++nr_interesting;

            if (arr[j] <= minimum.first)
                minimum = make_pair(arr[j], traversed_elem);

            ++traversed_elem;
        }
        
        if (minimum.second >= traversed_elem / 2 + traversed_elem % 2)
            ++nr_interesting;  
    }
    cout << nr_interesting << endl;
}
