#include <iostream>
#include <string>
#include <vector>

using namespace std;

string C_cipher(string text, int shift) {
    string result = "";

    for (char c : text) {
        if (isalpha(c)) {
            char base = islower(c) ? 'a' : 'A';
            int shifted_char = (c - base + shift);
            int mod = shifted_char % 26;
            if (mod < 0) {
                mod += 26;
            }
            c = mod + base;
        }
        result += c;
    }

    return result;
}

string Atbash_cipher(string text) {
    string result = "";
    for (char c : text) {
        if (isalpha(c)) {
            char base = islower(c) ? 'a' : 'A';
            c = base + (25 - (c - base));
        }
        result += c;
    }
    return result;
}

string XOR_cipher(string text, char key) {
    string result = "";
    for (char c : text) {
        result += c ^ key;
    }
    return result;
}


string t = "sggkh://ddd.blfgfyv.xln/dzgxs?e=lzeNgFDWYGN&orhg=IWlzeNgFDWYGN&hgzig_izwrl=1";
int lower = -1000;
int upper = 1000;

int main() {
    bool found = false;

    for (int shift = lower; shift <= upper; ++shift) {
        string decrypted = C_cipher(t, shift);
        if (decrypted.rfind("https://", 0) == 0) {
            cout << "Found with Caesar shift " << shift << ": " << decrypted << endl;
            found = true;
            break;
        }
    }


    string decrypted_atbash = Atbash_cipher(t);
    if (decrypted_atbash.rfind("https://", 0) == 0) {
        cout << "Found with Atbash cipher: " << decrypted_atbash << endl;
        found = true;
    }


    for (int key = 0; key <= 255; ++key) {
        string decrypted_xor = XOR_cipher(t, static_cast<char>(key));
        if (decrypted_xor.rfind("https://", 0) == 0) {
            cout << "Found with XOR key " << key << ": " << decrypted_xor << endl;
            found = true;
            break;
        }
    }
    
    if (!found) {
        cout << "\nCould not decrypt the string with the available methods." << endl;
    }

    return 0;
}