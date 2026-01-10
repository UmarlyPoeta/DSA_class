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

Result boyer_moore_find_key(const std::string& key, const std::string& file_path) {
    std::ifstream file(file_path);
    Result res;
    const int key_length = key.length();
    if (!file.is_open()) {
        std::cerr << "Error opening file: " << file_path << std::endl;
        return {-1, -1, false}; 
    }

    // Preprocess the key to create the bad character shift table
    std::vector<int> badChar(256, -1);
    for (int i = 0; i < key_length; i++) {
        badChar[(unsigned char)key[i]] = i;
    }

    std::string line;
    int line_number = 0;
    while (std::getline(file, line)) {
        int line_length = line.length();
        int s = 0; 
        while (s <= line_length - key_length) {
            int j = key_length - 1;

            while (j >= 0 && key[j] == line[s + j]) {
                j--;
            }
            if (j < 0) {
                file.close();
                return {line_number, s, true};
            } else {
                s += std::max(1, j - badChar[(unsigned char)line[s + j]]);
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
    
    std::ofstream outFile("boyer_moore_results.txt");
    if (!outFile.is_open()) {
        std::cerr << "Cannot open output file!" << std::endl;
        return 1;
    }

    for (const auto& key : patterns) {
        auto start = std::chrono::high_resolution_clock::now();
        Result result = boyer_moore_find_key(key, file_path);
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