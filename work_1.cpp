#include <iostream>
#include <string>

using namespace std;

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
    string DNA;
    cout << "Enter the original DNA sequence: ";
    cin >> DNA;

    string mutatedDNA = DNA;

    while (true) {
        string newDNA = performMutations(mutatedDNA);
        if (newDNA == mutatedDNA) {
            break;  // No further mutations possible
        }
        mutatedDNA = newDNA;
    }

    cout << "Final DNA sequence: " << mutatedDNA << endl;
    cout << "Final DNA sequence length: " << mutatedDNA.size() << endl;

    return 0;
}
