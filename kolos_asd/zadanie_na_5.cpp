#include <iostream>

using namespace std;

typedef struct komunikat {
    string data;
    int priority;
    int time;
    komunikat* next;

    komunikat(string d, int p, int t) : data(d), priority(p), time(t), next(nullptr) {};
} komunikat;

class system_kom {
private:
    komunikat* head;

public:
    system_kom() {head = nullptr;}
    ~system_kom() {
        komunikat* tmp;
        while (head) {
            tmp = head;
            head = head->next;
            delete tmp;
        }
    }
    
    void dodaj_komunikat(komunikat* k) {
        if (!head || k->priority > head->priority || 
            (k->priority == head->priority && k->time < head->time)) {
            k->next = head;
            head = k;
            return;
        }

        komunikat* tmp = head;
        while (tmp->next) {
            if (k->priority > tmp->next->priority || 
                (k->priority == tmp->next->priority && k->time < tmp->next->time)) {
                k->next = tmp->next;
                tmp->next = k;
                return;
            }
            tmp = tmp->next;
        }

        tmp->next = k;
    }

    void przetworz_komunikat() {
        if (!head) {
            cout << "Brak kom" << endl;
            return;
        }
        
        komunikat* tmp = head;
        cout << "przet: " << head->data << endl;
        head = head->next;
        delete tmp;
    }

    void wyswietl_kolejnosc() {
        if (!head) {
            cout << "Bfor pusty" << endl;
            return;
        }

        komunikat* tmp = head;
        cout << "Kolejność: ";

        while (tmp->next) {
            cout << tmp->data << " -> ";
            tmp = tmp->next;
        }

        cout << tmp->data << endl;
    }
};

int main() {
    system_kom s;

    s.dodaj_komunikat(new komunikat("A", 3, 80));
    s.dodaj_komunikat(new komunikat("B", 5, 90));
    s.dodaj_komunikat(new komunikat("C", 5, 120));
    s.dodaj_komunikat(new komunikat("D", 3, 100));
    s.wyswietl_kolejnosc();

    return 0;
}