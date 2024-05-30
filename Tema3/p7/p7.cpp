#include <fstream>
#include <iostream>
#include <stdint.h>
#include <vector>
#include <unordered_map>
using namespace std;

//43p
int main(){
    uint32_t nr_elem, nr_sir_bun = 0;
    ifstream fin("sirbun.in");
    ofstream fout("sirbun.out");

    fin >> nr_elem;
    vector<uint32_t> elements(nr_elem, 0);

    for (uint32_t i = 0; i < nr_elem; ++i)
        fin >> elements[i];

    for (uint32_t i = 0; i < nr_elem; ++i){
        unordered_map<uint32_t, uint32_t> elem_ap;
        for (uint32_t j = i; j < nr_elem; ++j){
            uint32_t new_val = elements[j];
            unordered_map<uint32_t, uint32_t> :: iterator found;
            //Cautam loc pt aceasta valoare si o inseram in table
            do{
                found = elem_ap.find(new_val --);
            } while (found != elem_ap.end() && new_val != 0);

            if (found == elem_ap.end()){
                elem_ap[new_val + 1] = 1;
                ++nr_sir_bun;
            }
            else
                break;
        }
    }
    fout << nr_sir_bun;
}