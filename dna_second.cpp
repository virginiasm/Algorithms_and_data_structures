#include <iostream>
#include <fstream>
#include <string>
#include <chrono>
#include <map>

using namespace std;

class Nodo {
public:
    char element;
    Nodo* next;
    Nodo* anterior;

    Nodo(char base) : element(base), next(nullptr), anterior(nullptr) {}
};

class Mutacoes {
private:
    Nodo* head; // ponteiro para o primeiro nó
    Nodo* tail; // ponteiro para o último nó
    int tamanho; // nunero de elementos na lista
    Nodo* currentNode;

public:
    Mutacoes() : head(nullptr), tail(nullptr), tamanho(0), currentNode(nullptr) {}
void add(char element) {
    Nodo* newNode = new Nodo(element);  // Cria um novo nó com o elemento passado como argumento.

    if (head == nullptr) {  // Verifica se a lista está vazia.
        head = newNode;     // Se estiver vazia, o novo nó se torna a cabeça (head) da lista.
        tail = newNode;     // O novo nó também se torna a cauda (tail) da lista.
        currentNode = head; // E o nó atual (currentNode) é definido como a cabeça.
    } else {
        newNode->anterior = tail;   // Define o nó anterior do novo nó como a antiga cauda.
        tail->next = newNode;   // Define o próximo nó da antiga cauda como o novo nó.
        tail = newNode;         // Atualiza a cauda para ser o novo nó.
    }

    tamanho++; 
}
// Método retorna o tamanho atual da lista encadeada
    int size() const { return tamanho;}

// Método retorna o ponteiro para o currentNode na lista encadeada. 
    Nodo* getCurrentNode() const {return currentNode;}

void removeBases(Nodo* nodo) {
    if (nodo == head) {
        // Se o nó a ser removido é a head da lista:
        head = nodo->next->next;  // A heah é atualizada para o nó após o próximo nó.
        currentNode = head;       // O nó atual é definido como a nova head.
        tamanho -= 2;             
        return;               
    } else {
        // Se o nó a ser removido está no meio da lista:
        Nodo* aux = nodo->anterior;      // Um ponteiro auxiliar é definido para o nó anterior.
        currentNode = nodo->anterior;    // O nó atual é definido como o nó anterior.
        aux->next = nodo->next->next;    // O nó anterior é conectado ao nó após o próximo nó.
        aux->next->anterior = aux;       // O nó anterior do próximo nó é atualizado para o nó anterior.
    }
    tamanho -= 2;
}
bool basesIguais(Nodo* nodo) {
    if (nodo->next == nullptr) {
        currentNode = nullptr;
        return true; // Retorna true para indicar que as bases são iguais (não há mais bases a serem comparadas).
    }
    
    if (nodo->element - nodo->next->element == 0) {
        // Atualiza o ponteiro currentNode para apontar para o próximo nó na lista.
        currentNode = nodo->next;
        return true;
    } else {
        // Se a diferença não for igual a zero, significa que as bases não são iguais.
        return false;
    }
}
    void mutacao(Nodo* nodo) {
        map<int, char> mutacaoMap;     // Criação de um mapa.
        mutacaoMap[3] = 'N';   // Diferença de 3 representa mutação para 'N'.
        mutacaoMap[10] = 'A';  // Diferença de 10 representa mutação para 'A'.
        mutacaoMap[13] = 'D';  // Diferença de 13 representa mutação para 'D'.

        // Calcula a diferença entre os códigos ASCII das bases nucleotídicas adjacentes.
        int diff = abs(nodo->element - nodo->next->element);

        // Verifica se a diferença está mapeada no mutacaoMap e se estiver, adicione o caractere de mutação correspondente; caso contrário, adicione um espaço em branco.
        char aux = (mutacaoMap.find(diff) != mutacaoMap.end()) ? mutacaoMap[diff] : ' ';

        // Add o caractere de mutação à lista encadeada.
        add(aux);

        // Remove os elementos comparados.
        removeBases(nodo);
    }
    void imprime() {
        std::string sequencia;
        Nodo* noAtual = head;
        while (noAtual != nullptr) {
            sequencia += noAtual->element;
            noAtual = noAtual->next;
    }
    cout << "Sequência de Bases: " << sequencia << endl;
}

};

int main() {
    auto start = chrono::high_resolution_clock::now(); // começo do cronômetro

    Mutacoes mutacao;

    ifstream file("test09.txt");
    
    if (file.is_open()) {
        string linha;
        while (getline(file, linha)) {
            for (char c : linha) {
                mutacao.add(c);
            }
        }
        file.close();
    } else {
        cerr << "Erro na leitura do arquivo" << endl;
    }

    while (mutacao.getCurrentNode() != nullptr) {
        if (!mutacao.basesIguais(mutacao.getCurrentNode())) {
            mutacao.mutacao(mutacao.getCurrentNode());
        }
    }

    mutacao.imprime();

    auto end = chrono::high_resolution_clock::now(); // fim do cronômetro
    chrono::duration<double> duration = end - start; // cálculo da duração de cada teste()).count();
    // tempo de execução de cada teste
    cout << "Tempo de execução: " << duration.count() << " segundos" << endl;
    cout << "--------------------------------------------" << endl;

    return 0;
}
