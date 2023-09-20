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
    Nodo* head; // ponteiro para o primeiro n�
    Nodo* tail; // ponteiro para o �ltimo n�
    int tamanho; // nunero de elementos na lista
    Nodo* currentNode;

public:
    Mutacoes() : head(nullptr), tail(nullptr), tamanho(0), currentNode(nullptr) {}
void add(char element) {
    Nodo* newNode = new Nodo(element);  // Cria um novo n� com o elemento passado como argumento.

    if (head == nullptr) {  // Verifica se a lista est� vazia.
        head = newNode;     // Se estiver vazia, o novo n� se torna a cabe�a (head) da lista.
        tail = newNode;     // O novo n� tamb�m se torna a cauda (tail) da lista.
        currentNode = head; // E o n� atual (currentNode) � definido como a cabe�a.
    } else {
        newNode->anterior = tail;   // Define o n� anterior do novo n� como a antiga cauda.
        tail->next = newNode;   // Define o pr�ximo n� da antiga cauda como o novo n�.
        tail = newNode;         // Atualiza a cauda para ser o novo n�.
    }

    tamanho++; 
}
// M�todo retorna o tamanho atual da lista encadeada
    int size() const { return tamanho;}

// M�todo retorna o ponteiro para o currentNode na lista encadeada. 
    Nodo* getCurrentNode() const {return currentNode;}

void removeBases(Nodo* nodo) {
    if (nodo == head) {
        // Se o n� a ser removido � a head da lista:
        head = nodo->next->next;  // A heah � atualizada para o n� ap�s o pr�ximo n�.
        currentNode = head;       // O n� atual � definido como a nova head.
        tamanho -= 2;             
        return;               
    } else {
        // Se o n� a ser removido est� no meio da lista:
        Nodo* aux = nodo->anterior;      // Um ponteiro auxiliar � definido para o n� anterior.
        currentNode = nodo->anterior;    // O n� atual � definido como o n� anterior.
        aux->next = nodo->next->next;    // O n� anterior � conectado ao n� ap�s o pr�ximo n�.
        aux->next->anterior = aux;       // O n� anterior do pr�ximo n� � atualizado para o n� anterior.
    }
    tamanho -= 2;
}
bool basesIguais(Nodo* nodo) {
    if (nodo->next == nullptr) {
        currentNode = nullptr;
        return true; // Retorna true para indicar que as bases s�o iguais (n�o h� mais bases a serem comparadas).
    }
    
    if (nodo->element - nodo->next->element == 0) {
        // Atualiza o ponteiro currentNode para apontar para o pr�ximo n� na lista.
        currentNode = nodo->next;
        return true;
    } else {
        // Se a diferen�a n�o for igual a zero, significa que as bases n�o s�o iguais.
        return false;
    }
}
    void mutacao(Nodo* nodo) {
        map<int, char> mutacaoMap;     // Cria��o de um mapa.
        mutacaoMap[3] = 'N';   // Diferen�a de 3 representa muta��o para 'N'.
        mutacaoMap[10] = 'A';  // Diferen�a de 10 representa muta��o para 'A'.
        mutacaoMap[13] = 'D';  // Diferen�a de 13 representa muta��o para 'D'.

        // Calcula a diferen�a entre os c�digos ASCII das bases nucleot�dicas adjacentes.
        int diff = abs(nodo->element - nodo->next->element);

        // Verifica se a diferen�a est� mapeada no mutacaoMap e se estiver, adicione o caractere de muta��o correspondente; caso contr�rio, adicione um espa�o em branco.
        char aux = (mutacaoMap.find(diff) != mutacaoMap.end()) ? mutacaoMap[diff] : ' ';

        // Add o caractere de muta��o � lista encadeada.
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
    cout << "Sequ�ncia de Bases: " << sequencia << endl;
}

};

int main() {
    auto start = chrono::high_resolution_clock::now(); // come�o do cron�metro

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

    auto end = chrono::high_resolution_clock::now(); // fim do cron�metro
    chrono::duration<double> duration = end - start; // c�lculo da dura��o de cada teste()).count();
    // tempo de execu��o de cada teste
    cout << "Tempo de execu��o: " << duration.count() << " segundos" << endl;
    cout << "--------------------------------------------" << endl;

    return 0;
}
