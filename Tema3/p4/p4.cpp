#include <iostream>
#include <queue>
#include <stdint.h>
#include <fstream>
#include <functional>
using namespace std;
/// 100p
struct enemyComp{
    bool operator()(uint32_t v1, uint32_t v2){
        return v1 > v2;
    }
};
int main(){
    uint16_t enemy_offset;
    uint32_t nr_enemies;

    ifstream fin("bleach.in");
    ofstream fout("bleach.out");

    fin >> nr_enemies >> enemy_offset;

    vector<int> enemies_pow_aux(nr_enemies);
    while (nr_enemies--)
        fin >> enemies_pow_aux[nr_enemies];
    
    sort(enemies_pow_aux.begin(), enemies_pow_aux.end());

    long long int min_power = enemies_pow_aux.front();
    long long int partial_sum = 0;
    
    for (uint32_t i = 0; i < enemies_pow_aux.size() - 1; ++i){
        partial_sum += enemies_pow_aux[i];
        min_power = max(min_power, enemies_pow_aux[i + 1] - partial_sum);
    }

    fout << min_power << '\n';
    
    // priority_queue<uint32_t, vector<uint32_t>, greater<uint32_t>> enemies_pow(
    //                                                                         enemies_pow_aux.begin(),
    //                                                                         enemies_pow_aux.end()
    //                                                                         );
    
}