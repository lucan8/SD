#include <iostream>
#include <fstream>
#include <vector>
#include <stack>
using namespace std;
//De ce e necesara parsarea?
int main(){
    vector<char> v;
    stack<char>s;

    ifstream fin("par.in");
    ofstream fout("par.out");

    int n, inv = 0;
    char c;
    fin >> n;
    if (n % 2){
        fout << -1;
        return 0;
    }

    fin.ignore();


    while (fin >> c){
        if (v.empty()) //Daca stiva e goala pune paranteza
            v.push_back(c);
        else if (v.back() == '(' && c == ')')
            v.pop_back();
            else
                v.push_back(c);
    }
    
    for (auto& c : v)
        if (s.empty()) //Daca stiva e goala pune paranteza
            s.push(c);
            
        else if ((c == ')' && s.top() == ')') || (c == '(' && s.top() == '(')){ //Inversam dr sau st
                inv ++;
                s.pop();
        }
        else
            s.push(c); //')(' doar punem pe stiva

    if (!s.empty()) //')(' inversam ambele paranteze
        inv += 2;
    fout << inv;

}