#include <iostream>
#include <fstream>
#include <stack>
#include <set>
#include <algorithm>
#include <vector>
//90p(intreaba la lab)
using namespace std;

bool intersect(set<int>::iterator st1, set<int>::iterator end1, 
set<int>::iterator st2, set<int>::iterator end2){
    while (st1 != end1 && st2 != end2){
        if (*st1 < *st2)
            st1 ++;
        else if(*st1 > *st2)
            st2 ++;
        else
            return true;
    }

    return false;
}

bool intersect(vector<int>::iterator st1, vector<int>::iterator end1, 
vector<int>::iterator st2, vector<int>::iterator end2){
    while (st1 != end1 && st2 != end2){
        if (*st1 < *st2)
            st1 ++;
        else if(*st1 > *st2)
            st2 ++;
        else
            return true;
    }

    return false;
}

void countingSort(vector<int>& in, int vmin, int vmax, vector<int>& out){
    vector<int> ap(vmax, 0); //Poate fii si de marime vmax - vmin + 1

    for (auto& x : in) //Umplere vectori de frecv
        ap[x] ++; 
    
    for (int i = 0; i <= vmax; i++) //Indexii
        ap[i] = ap[i - 1] + i;
    
    for (int i = in.size() - 1; i >= 0; i--) //Output
        out[--ap[in[i]]] = in[i];

}
int main(){
    ifstream fin("liste.in");
    ofstream fout("liste.out");

    int n, length, elem; //nr de liste, lungimea fiecareia, elem din lista

    //stack<set<int>> st;
    stack<vector<int>> st;
    set<int> s;

    fin >> n;

     while (n){
        fin >> length;
        vector<int> v, out;
        int vmax = -1, vmin = 120;
        v.reserve(length);
        out.reserve(length);

        while (length){
            fin >> elem;
            if (elem > vmax)
                vmax = elem;
            if (elem < vmin)
                vmin = elem;

            v.push_back(elem);
            length --;
        }
        countingSort(v, vmin, vmax, out);
        //Cat timp avem intersectie intre liste vecine, unificam si scoatem lista de pe stiva
        while (!st.empty())
            if (intersect((st.top()).begin(), (st.top()).end(), out.begin(), out.end())){
                set_union((st.top()).begin(), (st.top()).end(), out.begin(), out.end(), inserter(out, out.begin()));
                st.pop();
            }
            else break;

        st.push(out); //La final adaugam lista(unificata)
        
        n --;
    }
    fout << st.size();
    /*
    while (n){
        fin >> length;

        while (length){
            fin >> elem;
            s.insert(elem);
            length --;
        }
        //Cat timp avem intersectie intre liste vecine, unificam si scoatem lista de pe stiva
        while (!st.empty())
            if (intersect((st.top()).begin(), (st.top()).end(), s.begin(), s.end())){
                set_union((st.top()).begin(), (st.top()).end(), s.begin(), s.end(), inserter(s, s.begin()));
                st.pop();
            }
            else break;

        st.push(s); //La final adaugam lista(unificata)

        s.clear();
        n --;
    }
    fout << st.size();
    */
}