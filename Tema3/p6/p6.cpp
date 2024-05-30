#include <iostream>
#include <fstream>
#include <stdint.h>
#include <vector>
#include <queue>
using namespace std;

//100p
struct timbComp{
    //desc by interval head, asc by cost
    bool operator()(const pair<uint32_t, uint32_t>& p1, const pair<uint32_t, uint32_t>& p2){
        if (p1.first == p2.first)
            return p1.second > p2.second;
        return p1.first < p2.first; 
    }
};

int main(){
    uint32_t nr_pages, nr_intervals, max_seq;
    ifstream fin("timbre.in");
    ofstream fout("timbre.out");

    fin >> nr_pages >> nr_intervals >> max_seq;
    //first: interval last, second: const
    vector<pair<uint32_t, uint32_t>> timbre_aux; 
    while (nr_intervals--){
        pair<uint32_t, uint32_t> timbru;
        fin >> timbru.first >> timbru.second;
        timbre_aux.push_back(timbru);
    }
    priority_queue<pair<uint32_t, uint32_t>, vector<pair<uint32_t, uint32_t>>, timbComp>
        timbre(timbre_aux.begin(), timbre_aux.end());
    
    uint32_t curr_page = nr_pages;
    uint32_t min_cost = 0;

    //Choosing the intervals decendingly by max_number
    //Because we might not be able to use those number for pages later
    while (curr_page){
        pair<uint32_t, uint32_t> chosen = timbre.top();
        //Trimming the intervals to max size as page
        while (chosen.first > curr_page){
            timbre.pop();
            timbre.emplace(curr_page, chosen.second);
            chosen = timbre.top();
        }
        //Interval chosen is the best cost at current time
        min_cost += chosen.second;
        curr_page -= min(chosen.first, max_seq);
        timbre.pop();
    }
    fout << min_cost;


}