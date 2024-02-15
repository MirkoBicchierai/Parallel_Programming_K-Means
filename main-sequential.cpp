#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>
#include <sstream>
#include <fstream>
#include <chrono>

std::vector<std::string> splitIntoWords(const std::string& text) {
    std::istringstream iss(text);
    std::vector<std::string> words;
    std::string word;
    while (iss >> word) {
        words.push_back(word);
    }
    return words;
}

std::unordered_map<std::string, int> computeWordNGram(const std::string& text, int n) {
    std::unordered_map<std::string, int> histogram;
    std::vector<std::string> words = splitIntoWords(text);
    int numWords = words.size();
    for (int i = 0; i <= numWords - n; ++i) {
        std::string ngram;
        for (int j = 0; j < n; ++j) {
            if (j > 0) {
                ngram += " ";
            }
            ngram += words[i + j];
        }
        ++histogram[ngram];
    }
    return histogram;
}

std::unordered_map<std::string, int> computeCharNGram(const std::string& text, int n) {
    std::unordered_map<std::string, int> histogram;
    int textLength = text.length();
    for (int i = 0; i <= textLength - n; ++i) {
        std::string ngram = text.substr(i, n);
        ++histogram[ngram];
    }
    return histogram;
}

void printHistogram(const std::unordered_map<std::string, int>& histogram) {
    for (const auto& entry : histogram) {
        std::cout << entry.first << ": " << entry.second << std::endl;
    }
}

int main() {
    auto start_time = std::chrono::high_resolution_clock::now();
    std::ifstream file("text.txt");
    std::string text((std::istreambuf_iterator<char>(file)),std::istreambuf_iterator<char>());
    std::cout << "File content:\n" << text << std::endl;
    file.close();

    // Word-level bigrams histogram
    std::unordered_map<std::string, int> word2gram = computeWordNGram(text, 2);
    std::cout << "Word-level Bigrams Histogram:" << std::endl;
    printHistogram(word2gram);
    std::cout << std::endl;

    // Word-level trigrams histogram
    std::unordered_map<std::string, int> word3gram = computeWordNGram(text, 3);
    std::cout << "Word-level Trigrams Histogram:" << std::endl;
    printHistogram(word3gram);

    // Character-level bigrams histogram
    std::unordered_map<std::string, int> char2gram = computeCharNGram(text, 2);
    std::cout << "Character-level Bigrams Histogram:" << std::endl;
    printHistogram(char2gram);
    std::cout << std::endl;

    // Character-level trigrams histogram
    std::unordered_map<std::string, int> char3gram = computeCharNGram(text, 3);
    std::cout << "Character-level Trigrams Histogram:" << std::endl;
    printHistogram(char3gram);

    std::cout << "-------------------------------------------------------------" << std::endl;
    auto end_time = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time);
    std::cout << "Execution time: " << duration.count() << " microseconds" << std::endl;
    std::cout << "-------------------------------------------------------------" << std::endl;

    return 0;
}