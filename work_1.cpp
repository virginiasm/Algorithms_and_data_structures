#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <sstream>
#include <filesystem>
#include <chrono>

using namespace std;
namespace fs = std::filesystem;
namespace chrono = std::chrono;

// Function to perform mutations on DNA sequence
string performMutations(const string& dna) {
    string mutatedDNA;

    for (size_t i = 0; i < dna.size(); i += 2) {
        if (i + 1 < dna.size()) {
            if (dna[i] != dna[i + 1]) {
                mutatedDNA += 'A';  // 'D' and 'N' mutate to 'A'
            } else {
                mutatedDNA += dna[i];  // 'A' remains unchanged
            }
        } else {
            mutatedDNA += dna[i];  // If odd length, last base remains unchanged
        }
    }

    return mutatedDNA;
}

int main() {
    // Directory containing test files
    string directoryPath = "casosTeste_t10";

    // Iterate over files in the directory
    for (const auto& entry : fs::directory_iterator(directoryPath)) {
        if (entry.is_regular_file()) {
            string fileName = entry.path().filename().string();
            
            // Check if the file has a .txt extension
            if (fileName.substr(fileName.size() - 4) == ".txt") {
                ifstream file(entry.path());
                if (file.is_open()) {
                    string DNA;
                    // Read DNA sequence from the file
                    getline(file, DNA);
                    file.close();

                    string mutatedDNA = DNA;

                    // Measure the processing time
                    auto startTime = chrono::high_resolution_clock::now();

                    while (true) {
                        string newDNA = performMutations(mutatedDNA);
                        if (newDNA == mutatedDNA) {
                            break;  // No further mutations possible
                        }
                        mutatedDNA = newDNA;
                    }

                    auto endTime = chrono::high_resolution_clock::now();
                    auto duration = chrono::duration_cast<chrono::milliseconds>(endTime - startTime);

                    cout << "File: " << fileName << endl;
                    cout << "Original DNA sequence: " << DNA << endl;
                    cout << "Final DNA sequence: " << mutatedDNA << endl;
                    cout << "Final DNA sequence length: " << mutatedDNA.size() << endl;
                    cout << "Processing time: " << duration.count() << " milliseconds" << endl;
                } else {
                    cerr << "Error opening file: " << fileName << endl;
                }
            }
        }
    }

    return 0;
}
