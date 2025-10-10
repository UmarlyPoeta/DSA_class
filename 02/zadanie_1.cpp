#include <iostream>
#include <string>
#include <fstream>

using namespace std;


struct Node {
    string imie;
    string nazwisko;
    int rozp_kad;
    int kon_kad;
    string partia;
    Node* next;
};


class List {
private:
    Node* head;
public:
    List() : head(nullptr) {}
    ~List() {
        Node* current = head;
        while (current) {
            Node* next = current->next;
            delete current;
            current = next;
        }
    }

    void insert(const string& imie, const string& nazwisko, int rozp_kad, int kon_kad, const string& partia) {
        Node* node = new Node{imie, nazwisko, rozp_kad, kon_kad, partia, nullptr};
    
        if (!head || head->rozp_kad > rozp_kad) {
            node->next = head;
            head = node;
        } else {
            Node* c = head;
            while (c->next && c->next->rozp_kad <= rozp_kad) {
                c = c->next;
            }
            node->next = c->next;
            c->next = node;
        }
    }

    void print() const {
        Node* current = head;
        while (current) {
            cout << current->imie << " " << current->nazwisko << " (" << current->rozp_kad << "-" << current->kon_kad << ") " << current->partia << endl;
            current = current->next;
        }
    }

    void find_by_shortest_kadencja() const {
        if (!head) return;

        Node* current = head;
        Node* minNode = head;
        int minDuration = head->kon_kad - head->rozp_kad;

        while (current) {
            int duration = current->kon_kad - current->rozp_kad;
            if (duration < minDuration) {
                minDuration = duration;
                minNode = current;
            }
            current = current->next;
        }

        if (minNode) {
            cout << "President with shortest term: " << minNode->imie << " " << minNode->nazwisko << " (" << minNode->rozp_kad << "-" << minNode->kon_kad << ") " << minNode->partia << endl;
        }
    }

    void print_nodes_from_certain_partia(const string& partia) const {
        if (!head) return;
        
        Node* current  = head;

        while (current) {
            if (current->partia == partia) {
                cout << current->imie << " " << current->nazwisko << " (" << current->rozp_kad << "-" << current->kon_kad << ") " << current->partia << endl;
            }
            current = current->next;
        }
    }

    void which_president_from_year(int year) const {
        if (!head) return;

        Node* c = head;
        while (c) {
            if (c->rozp_kad <= year && c->kon_kad >= year) {
                cout << "In year " << year << " the president was: " << c->imie << " " << c->nazwisko << " (" << c->rozp_kad << "-" << c->kon_kad << ") " << c->partia << endl;
                return;
            }
            c = c->next;
        }

        cout << "No president found for year " << year << endl;
    }
};

List presidents;

string* split(string str, string delim) {
    size_t pos = 0;
    string* result = new string[5];
    string tmp;
    int i = 0;
    while ((pos = str.find(delim)) != string::npos) {
        tmp = str.substr(0, pos);
        result[i++] = tmp;
        str.erase(0, pos + delim.length());
    }
    result[i] = str;
    return result;
}


void loadData(string path) {
    string line;
    ifstream myfile("" + path);
    if (myfile.is_open())
    {
        while (getline(myfile, line))
        {
            //split the string
            int d_pos = 0;
            string* buffer = split(line, " ");
            int count = 0;
            for (int i = 0; i < 5; ++i) {
                if (!buffer[i].empty()) ++count;
            }
            string imie, nazwisko, partia;
            int rozp_kad, kon_kad;
            if (count == 5) {
                imie = buffer[0] + " " + buffer[1];
                nazwisko = buffer[2];
                d_pos = buffer[3].find("-");
                rozp_kad = stoi(buffer[3].substr(0, d_pos));
                kon_kad = stoi(buffer[3].substr(d_pos + 1));
                partia = buffer[4];
            } else if (count == 4) {
                imie = buffer[0];
                nazwisko = buffer[1];
                d_pos = buffer[2].find("-");
                rozp_kad = stoi(buffer[2].substr(0, d_pos));
                kon_kad = stoi(buffer[2].substr(d_pos + 1));
                partia = buffer[3]; 
            } else {
                // blablabla
            }
            presidents.insert(imie, nazwisko, rozp_kad, kon_kad, partia);
            delete[] buffer;
        }
    myfile.close();
    }
    else cout << "Unable to open file";
}




int main() {
    string p;
    int year;
    cout << "1 zad" << endl;

    loadData("presidents.txt");
    presidents.print();

    cout << endl;
    cout << "2 zad" << endl;
    presidents.find_by_shortest_kadencja();
    cout << endl;
    cout << "3 zad" << endl;
    cin >> p;
    presidents.print_nodes_from_certain_partia(p);
    cout << endl;
    cout << "4 zad" << endl;
    cin >> year;
    presidents.which_president_from_year(year);
    cout << endl;
    /*5 zad
    
    - zrobienie hash mapy jeżeli nam nie zależy na pamięci z wartościami dla każdego prezydenta
    - jeżeli zależy nam na pamięci to zrobienie tablicy wskaźników do prezydentów gdzie index to rok rozpoczęcia kadencji ponieważ mamy ograniczony zakres lat 
    
    */
    return 0;
}