#include <iostream>
#include <vector>
#include <stack>
#include <fstream>
#include <sstream>
using namespace std;


void empty_stack(stack<char>& s){
    while (!s.empty())
        s.pop();
}

int main(){
    vector<char> v; //Reserve inca 10 cand e plin
    stack <char> s;

    ifstream fin("editor.in");
    ofstream fout("editor.out");

    char c;
    int nr, ok;

    fin >> nr; fin.ignore(); //Nr de linii din fisier

    while (nr){
        ok = 1;
        fin >> c; //Primul caracter de pe linie

        while (c != 'E'){ //Parsam totul pana la E
            if (c != '*') //Adaaugam caracter
                v.push_back(c);
            else if (!v.empty()) //Stergem caracter
                v.pop_back();
            
            fin >> c; //Citim urmatorul caracter
        }
       
       for (auto& x : v){
           if (x == '(' || x == '['){ //Deschidem paranteza
                s.push(x);
           }
           //Incercam sa inchidem ultima paranteza
           else if (!s.empty()){
                    if((s.top() == '(' && x == ')') || (s.top() == '[' && x == ']'))
                        s.pop();

                    else{//Parantezare incorecta
                            ok = 0;
                            break;
                        }
           }
            else if (x == ')' || x == ']'){
                ok = 0;
                break;
            }
       }
       if (ok && s.empty())
           fout << ":)";
       else
           fout << ":(";

        if (nr > 1)
            fout << endl;

        nr --; 
        //Curatam containerele inainte de refolosire pt linia urmatoare
        if (!v.empty())
            v.clear();
        empty_stack(s);
    }
}