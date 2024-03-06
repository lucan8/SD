#include <iostream>
#include <fstream>
#include <vector>
//50p
using namespace std;
int main(){
    vector<char> v;

    int n, m, k = 1;
    char c;

    ifstream fin("trompeta.in");
    ofstream fout("trompeta.out");

    fin >> n >> m;
    fin.ignore();
    //Cantam toate notele
    if (n == m){
        while (fin >> c)
            fout << c;
        return 0;
    }
    //Citim prima nota si o pune pe stiva
    fin >> c;
    v.push_back(c);
    
    while (fin >> c){
        k ++; //Incrementam contorul de nr
        //Daca nota aceasta e mai placuta decat ultima pusa si putem face schimbare atunci o facem
        //n-k+v.size() indica daca ne permitam sa facem o inlocuire
        while (!v.empty() && c > v.back() && n - k + v.size() >= m)
            v.pop_back();

        //Daca stiva e plina nu mai adaugam nimic
        if (v.size() < m)
            v.push_back(c);
    }

    for (auto& x : v)
        fout << x;
}