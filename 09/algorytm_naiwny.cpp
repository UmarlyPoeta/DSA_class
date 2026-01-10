#include <iostream>
#include <cstdio>
#include <string>
#include <fstream>
#include <chrono>
#include <vector>

struct Result {
    int line_number;
    int char_index;
    bool found;
};


Result naive_find_key(std::string key, std::string file_path) {
    std::ifstream file(file_path);
    Result res;
    const int key_length = key.length();

    if (!file.is_open()) {
        std::cerr << "Error opening file: " << file_path << std::endl;
        return {-1, -1, false}; 
    }

    std::string line;
    int line_number = 0;
    while (std::getline(file, line)) {
        if (line.length() >= key_length) {
            for (size_t i = 0; i < line.length() - key_length + 1; ++i) {
                if (line.substr(i, key_length) == key) {
                    file.close();
                    return {line_number, static_cast<int>(i), true}; 
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
    
    std::ofstream outFile("naive_search_results.txt");
    if (!outFile.is_open()) {
        std::cerr << "Cannot open output file!" << std::endl;
        return 1;
    }

    for (const auto& key : patterns) {
        auto start = std::chrono::high_resolution_clock::now();
        Result result = naive_find_key(key, file_path);
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
