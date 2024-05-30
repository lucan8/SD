#include <iostream>
#include <stdint.h>
#include <vector>
#include <algorithm>
using namespace std;

//0p???
const uint32_t modulo_number = 1e9 + 7;
uint32_t myLog2(uint32_t val){
    uint32_t log_res = 0;
    while (val){
        log_res++;
        val >>= 1;
    }
    return log_res - 1;
}

void fillPower2(vector<uint32_t>& power2){
    power2[0] = 1;
    for (uint32_t i = 1; i < power2.size(); ++i)
        power2[i] = (power2[i - 1] * 2) % modulo_number;
}

vector<vector<uint32_t>> getMaxRMQ(const vector<uint32_t>& seq_elem){
    //Carefull with precision problems
    vector<vector<uint32_t>> rmq_max(myLog2(seq_elem.size()) + 1);
    rmq_max[0] = seq_elem;

    for (uint32_t i = 1; i < rmq_max.size(); ++i){
        //Making sure we don't go out of range
        rmq_max[i].reserve(seq_elem.size() + 1 - (1 << i));
        for (uint32_t j = 0; j < rmq_max[i].capacity(); ++j){
            //Splitting the range in two, j to j + 2^(i-1) - 1, j + 2^(i-1)  to j + 2^i - 1
            rmq_max[i].push_back(max(rmq_max[i - 1][j], rmq_max[i - 1][j + (1 << i - 1)]));
        }
    }
    return rmq_max;
}

int main(){
    uint32_t nr_seq, nr_queries;
    cin >> nr_seq;

    vector<uint32_t> seq_elem(nr_seq), results;
    for (uint32_t i = 0; i < nr_seq; i++)
        cin >> seq_elem[i];

    vector<uint32_t> power2(nr_seq);
    fillPower2(power2);

    vector<vector<uint32_t>> rmq_max = getMaxRMQ(seq_elem);

    cin >> nr_queries;
    results.reserve(nr_queries);

    while (nr_queries --){
        uint32_t st, fin;
        cin >> st >> fin;
        st--, fin--;

        //Carefull with precision problems
        uint32_t log2_max_len = myLog2(fin - st + 1);
        uint32_t chosen_elem = max(
                                    rmq_max[log2_max_len][st],
                                    rmq_max[log2_max_len][fin - (1 << log2_max_len) + 1]
                                  )
                             * power2[fin - st] % modulo_number;
        results.push_back(chosen_elem);
    }
    for (int i = 0; i < results.size(); ++i)
        cout << results[i] << '\n';
    
}