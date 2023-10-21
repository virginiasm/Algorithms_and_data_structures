#include <fstream>
#include <string>
#include <chrono>
#include <filesystem>
#include <iostream>
#include <vector>
#include <cctype>

namespace fs = std::filesystem;
using namespace std;

// Função para realizar a mutação da cadeia de DNA
string processoDeMutacao(const vector<char>& cadeiaDNA) {
    vector<char> mutacao = cadeiaDNA;
    bool ParesDiferentes = true;

    while (ParesDiferentes) {
        int tamanho = mutacao.size();
        int cont = 0;
        ParesDiferentes = false;

        while (cont + 1 != tamanho) {
            char baseDNA_1 = mutacao[cont];
            char baseDNA_2 = mutacao[cont + 1];

            if ((baseDNA_1 == 'D' && baseDNA_2 == 'D') ||
                (baseDNA_1 == 'N' && baseDNA_2 == 'N') ||
                (baseDNA_1 == 'A' && baseDNA_2 == 'A')) {
                cont++;
            } else {
                // Use erase() para remover o par diferente
                mutacao.erase(mutacao.begin() + cont, mutacao.begin() + cont + 2);

                if (baseDNA_1 == 'D' && baseDNA_2 == 'N') {
                    mutacao.push_back('A');
                } else if (baseDNA_1 == 'N' && baseDNA_2 == 'D') {
                    mutacao.push_back('A');
                } else if (baseDNA_1 == 'A' && baseDNA_2 == 'D') {
                    mutacao.push_back('N');
                } else if (baseDNA_1 == 'D' && baseDNA_2 == 'A') {
                    mutacao.push_back('N');
                } else if (baseDNA_1 == 'N' && baseDNA_2 == 'A') {
                    mutacao.push_back('D');
                } else if (baseDNA_1 == 'A' && baseDNA_2 == 'N') {
                    mutacao.push_back('D');
                }

                ParesDiferentes = true;
                cont = 0;
                tamanho--;
            }
        }
    }

    return string(mutacao.begin(), mutacao.end());
}

int main() {
    // Diretório onde estão os arquivos TXT
    fs::path pasta("casosTeste_t10");

    if (fs::exists(pasta) && fs::is_directory(pasta)) {
        int teste = 1; // Contador para os testes
        for (const auto& entry : fs::directory_iterator(pasta)) {
            if (entry.is_regular_file() && entry.path().extension() == ".txt") {
                vector<char> cadeiaDNA; // armazena o conteúdo do arquivo de texto
                ifstream inputFile(entry.path());

                if (inputFile.is_open()) { // verifica se o arquivo foi aberto
                    char c; // para ler cada caractere do arquivo
                    while (inputFile.get(c)) {
                        if (isalnum(c)) {
                            cadeiaDNA.push_back(c); // adicione apenas caracteres ao vetor
                        }
                    }
                    inputFile.close();

                    auto start = chrono::high_resolution_clock::now(); // começo do cronômetro

                    // Chamada à função para realizar a mutação
                    string resultadoMutacao = processoDeMutacao(cadeiaDNA);

                    auto end = chrono::high_resolution_clock::now(); // fim do cronômetro
                    chrono::duration<double> duration = end - start; // cálculo da duração de cada teste
                    // Apresenta o resultado da menor cadeia que pode ser obtida em cada teste.
                    cout << "Teste " << teste << endl;
                    cout << "Resultado final após as mutações: " << resultadoMutacao << endl;

                    // tempo de execução de cada teste
                    cout << "Tempo de execução: " << duration.count() << " segundos" << endl;
                    cout << "--------------------------------------------" << endl;

                    teste++; // Incrementa o contador de teste
                } else {
                    cerr << "Erro na leitura do arquivo: " << entry.path() << endl;
                }
            }
        }
    } else {
        cerr << "A pasta não existe!!!" << endl;
        return 1;
    }

    return 0;
}
