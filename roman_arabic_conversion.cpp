#include <fst/fstlib.h>
#include <iostream>
#include <string>
#include <map>

using namespace std;
using namespace fst;

int main() {

    string roman;
    cout << "Enter a Roman numeral (using I, V, X, L, C): ";
    cin >> roman;

  
    map<char, int> roman_map = {
        {'I', 1},
        {'V', 5},
        {'X', 10},
        {'L', 50},
        {'C', 100}
    };

  
    StdVectorFst fst;

    int start = fst.AddState();
    fst.SetStart(start);
    int current = start;

  
    for (char c : roman) {
  
        if (roman_map.find(c) == roman_map.end()) {
            cout << "Invalid Roman numeral character: " << c << endl;
            return 0;
        }

        int next = fst.AddState();
        int value = roman_map[c];
        fst.AddArc(current, StdArc(c, value, 0, next)); 
        current = next;
    }

    fst.SetFinal(current, StdArc::Weight::One());

  
    int arabic_value = 0;
    StateIterator<StdVectorFst> siter(fst);
    for (; !siter.Done(); siter.Next()) {
        auto state = siter.Value();
        for (ArcIterator<StdVectorFst> aiter(fst, state); !aiter.Done(); aiter.Next()) {
            const StdArc &arc = aiter.Value();
            arabic_value += arc.olabel;
        }
    }

    cout << "Arabic numeral: " << arabic_value << endl;

    return 0;
}
