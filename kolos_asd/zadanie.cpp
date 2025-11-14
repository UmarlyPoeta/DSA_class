#include <iostream>
#include <string>

#define max 100

using namespace std;

class biblioteka {
private:
    string tab[max];
    int t;

public:
    biblioteka() { t = -1;};

    void push(string title) {
        if (t > max - 1) {
            cout << "pelna biblioteka" << endl;
            return;
        }

        t++;
        tab[t] = title;
    }

    void pop() {
        if (t == -1) {
            cout << "stos pusty" << endl;
            return;
        }
        cout << "Zdjeto: " << tab[t] << endl;
        t--;
    }

    void top() {
        cout << "Na wierzchu: " << tab[t] << endl;
    }

    void list() {
        if (t == -1) {
            cout << "stos pusty" << endl;
            return;
        }

        cout << "Stos: ";
        for (int i = 0; i < t; i++) {
            cout << tab[i] << " -> ";
        }
        cout << tab[t] << endl;

    }
};


int main() {

    biblioteka bib;

    bib.push("Algorytmy");
    bib.push("Struktury danych");
    bib.top();
    bib.list();
    bib.pop();
    bib.top();




    return 0;
}