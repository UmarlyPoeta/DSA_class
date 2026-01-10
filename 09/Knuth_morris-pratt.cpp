#include <iostream>
#include <cstdio>
#include <string>
#include <fstream>
#include <chrono>
#include <cmath>
#include <vector>

struct Result {
    int line_number;
    int char_index;
    bool found;
};


Result knuth_morris_pratt_find_key(const std::string& key, const std::string& file_path) {
    std::ifstream file(file_path);
    Result res;
    const int key_length = key.length();
    if (!file.is_open()) {
        std::cerr << "Error opening file: " << file_path << std::endl;
        return {-1, -1, false}; 
    }

    // Preprocess the key to create the longest prefix-suffix (LPS) array
    std::vector<int> lps(key_length, 0);
    int len = 0;
    for (int i = 1; i < key_length; ) {
        if (key[i] == key[len]) {
            len++;
            lps[i] = len;
            i++;
        } else {
            if (len != 0) {
                len = lps[len - 1];
            } else {
                lps[i] = 0;
                i++;
            }
        }
    }
    std::string line;
    int line_number = 0;
    while (std::getline(file, line)) {
        int line_length = line.length();
        int i = 0;
        int j = 0;
        while (i < line_length) {
            if (key[j] == line[i]) {
                i++;
                j++;
            }
            if (j == key_length) {
                file.close();
                return {line_number, i - j, true};
            } else if (i < line_length && key[j] != line[i]) {
                if (j != 0) {
                    j = lps[j - 1];
                } else {
                    i++;
                }
            }
        }
        line_number++;
    }
    file.close();
    return {-1, -1, false};
}

int main() {
    std::string file_path = "Hobbit.txt";
    std::vector<std::string> patterns = {
        "the",
        "hobbit",
        "Gandalf",
        "Bilbo",
        "krasnolud",
        "Pagórek",
        "norę",
        "drzwi",
        "fajkę",
        "śpiewały",
        "złoto",
        "przygody"
    };
    
    std::ofstream outFile("knuth_morris_pratt_results.txt");
    if (!outFile.is_open()) {
        std::cerr << "Cannot open output file!" << std::endl;
        return 1;
    }

    for (const auto& key : patterns) {
        auto start = std::chrono::high_resolution_clock::now();
        Result result = knuth_morris_pratt_find_key(key, file_path);
        auto end = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);

        std::cout << "Pattern: \"" << key << "\" - ";
        if (result.found) {
            std::cout << "Found at line " << result.line_number 
                      << ", index " << result.char_index;
        } else {
            std::cout << "Not found";
        }
        std::cout << " (" << duration.count() << " µs)" << std::endl;
        outFile << key << "," << result.found << "," << duration.count() << std::endl;
    }

    outFile.close();
    return 0;
}