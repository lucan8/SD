#include <iostream>
#include <fstream>
#include <stdint.h>
#include <vector>
#include <queue>
#include <algorithm>
#include <queue>
#include <numeric>
using namespace std;

enum proc_choice{in_use, free_proc};
//100p
struct ProcComparator{
    bool operator()(const pair<uint32_t, uint64_t>& p1, const pair<uint32_t, uint64_t>& p2){
        if (p1.second == p2.second)
            return p1.first > p2.first;
        return p1.second > p2.second;
    }
    bool operator()(uint32_t v1, uint32_t v2){
        return v1 > v2;
    }
};


void freeProc(priority_queue<pair<uint32_t, uint64_t>, 
                    vector<pair<uint32_t, uint64_t>>, ProcComparator>& in_use, priority_queue<uint32_t, 
                    vector<uint32_t>, ProcComparator>& free_proc, uint64_t start_time){
    while (!in_use.empty()){
        pair<uint32_t, uint64_t> curr_proc = in_use.top();

        if (start_time < curr_proc.second)
            return;

        free_proc.push(curr_proc.first);
        in_use.pop();
    }
}
int main(){
    ifstream fin("proc2.in");
    ofstream fout("proc2.out");

    uint32_t nr_proc, nr_tasks;
    fin >> nr_proc >> nr_tasks;


    //Vector for proc_index to be moved inside free pq
    vector<uint32_t> free_aux(nr_proc);
    iota(free_aux.begin(), free_aux.end(), 1);

    priority_queue<pair<uint32_t, uint64_t>, vector<pair<uint32_t, uint64_t>>, ProcComparator> in_use;
    priority_queue<uint32_t, vector<uint32_t>, ProcComparator> free_proc(free_aux.begin(), free_aux.end());

    while (nr_tasks--){
        uint64_t st, dur, finish;
        fin >> st >> dur;
        finish = st + dur;

        //Freeing processors with finish time lower than the start
        freeProc(in_use, free_proc, st);

        uint32_t chosen_proc = free_proc.top();
        fout << chosen_proc << '\n';

        in_use.emplace(chosen_proc, finish);
        free_proc.pop();
    }
}