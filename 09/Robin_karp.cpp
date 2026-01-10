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


Result robin_karp_find_key(const std::string& key, const std::string& file_path) {
    std::ifstream file(file_path);
    Result res;
    const int key_length = key.length();
    const int prime = 101;
    const int d = 256;
    if (!file.is_open()) {
        std::cerr << "Error opening file: " << file_path << std::endl;
        return {-1, -1, false}; 
    }

    std::string line;
    int line_number = 0;

    int key_hash = 0;
    // Precompute the hash for the key
    for (int i = 0; i < key_length; i++) {
        key_hash = (d * key_hash + key[i]) % prime;
    }



    while (std::getline(file, line)) {
        int line_length = line.length();
        if (line_length < key_length) {
            line_number++;
            continue;
        }

        int line_hash = 0;
        // Precompute the hash for the first window
        for (int i = 0; i < key_length; i++) {
            line_hash = (d * line_hash + line[i]) % prime;
        }

        for (int i = 0; i <= line_length - key_length; i++) {
            // Check for hash match
            if (key_hash == line_hash) {
                if (line.substr(i, key_length) == key) {
                    file.close();
                    return {line_number, i, true}; 
                }
            }
            // Calculate hash for next window
            if (i < line_length - key_length) {
                line_hash = (d * (line_hash - line[i] * (int)pow(d, key_length - 1)) + line[i + key_length]) % prime;
                if (line_hash < 0) {
                    line_hash += prime;
                }
            }
        }
        line_number++;
    }


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
    
    std::ofstream outFile("robin_karp_results.txt");
    if (!outFile.is_open()) {
        std::cerr << "Cannot open output file!" << std::endl;
        return 1;
    }

    for (const auto& key : patterns) {
        auto start = std::chrono::high_resolution_clock::now();
        Result result = robin_karp_find_key(key, file_path);
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