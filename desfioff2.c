#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Limites e definições
#define MAX_ITENS 10

// Struct que representa um item da mochila
typedef struct {
    char nome[30];
    char tipo[20];
    int quantidade;
} Item;

// Struct do nó para lista encadeada
typedef struct No {
    Item dados;
    struct No* proximo;
} No;

// Vetor (lista sequencial)
Item vetorMochila[MAX_ITENS];
int totalVetor = 0;

// Lista encadeada
No* inicioLista = NULL;

// Contadores de comparações
int compBuscaSeqVetor = 0;
int compBuscaBinVetor = 0;
int compBuscaSeqLista = 0;

//////////////////////////
// Funções do VETOR
//////////////////////////

// Inserção no vetor
void inserirItemVetor() {
    if (totalVetor >= MAX_ITENS) {
        printf("Mochila cheia (vetor)!\n");
        return;
    }

    Item novo;
    printf("Nome: ");
    scanf(" %[^\n]", novo.nome);
    printf("Tipo: ");
    scanf(" %[^\n]", novo.tipo);
    printf("Quantidade: ");
    scanf("%d", &novo.quantidade);

    vetorMochila[totalVetor++] = novo;
    printf("Item adicionado no vetor.\n");
}

// Remoção no vetor
void removerItemVetor() {
    char nome[30];
    printf("Digite o nome do item a remover (vetor): ");
    scanf(" %[^\n]", nome);

    for (int i = 0; i < totalVetor; i++) {
        if (strcmp(vetorMochila[i].nome, nome) == 0) {
            for (int j = i; j < totalVetor - 1; j++) {
                vetorMochila[j] = vetorMochila[j + 1];
            }
            totalVetor--;
            printf("Item removido do vetor.\n");
            return;
        }
    }
    printf("Item não encontrado no vetor.\n");
}

// Listagem dos itens no vetor
void listarItensVetor() {
    printf("Itens na mochila (vetor):\n");
    for (int i = 0; i < totalVetor; i++) {
        printf("%d. Nome: %s | Tipo: %s | Qtd: %d\n",
               i + 1, vetorMochila[i].nome, vetorMochila[i].tipo, vetorMochila[i].quantidade);
    }
}

// Busca sequencial no vetor
void buscarSequencialVetor() {
    char nome[30];
    printf("Nome do item para buscar (sequencial - vetor): ");
    scanf(" %[^\n]", nome);
    compBuscaSeqVetor = 0;

    for (int i = 0; i < totalVetor; i++) {
        compBuscaSeqVetor++;
        if (strcmp(vetorMochila[i].nome, nome) == 0) {
            printf("Item encontrado: %s (%s), Quantidade: %d\n",
                   vetorMochila[i].nome, vetorMochila[i].tipo, vetorMochila[i].quantidade);
            printf("Comparações realizadas: %d\n", compBuscaSeqVetor);
            return;
        }
    }
    printf("Item não encontrado no vetor. Comparações: %d\n", compBuscaSeqVetor);
}

// Ordenação do vetor (Bubble Sort)
void ordenarVetor() {
    for (int i = 0; i < totalVetor - 1; i++) {
        for (int j = 0; j < totalVetor - i - 1; j++) {
            if (strcmp(vetorMochila[j].nome, vetorMochila[j + 1].nome) > 0) {
                Item temp = vetorMochila[j];
                vetorMochila[j] = vetorMochila[j + 1];
                vetorMochila[j + 1] = temp;
            }
        }
    }
    printf("Vetor ordenado por nome.\n");
}

// Busca binária no vetor ordenado
void buscarBinariaVetor() {
    char nome[30];
    printf("Nome do item para buscar (binária - vetor): ");
    scanf(" %[^\n]", nome);

    int ini = 0, fim = totalVetor - 1;
    compBuscaBinVetor = 0;

    while (ini <= fim) {
        int meio = (ini + fim) / 2;
        compBuscaBinVetor++;
        int cmp = strcmp(nome, vetorMochila[meio].nome);

        if (cmp == 0) {
            printf("Item encontrado: %s (%s), Quantidade: %d\n",
                   vetorMochila[meio].nome, vetorMochila[meio].tipo, vetorMochila[meio].quantidade);
            printf("Comparações realizadas (binária): %d\n", compBuscaBinVetor);
            return;
        } else if (cmp < 0) {
            fim = meio - 1;
        } else {
            ini = meio + 1;
        }
    }
    printf("Item não encontrado na busca binária. Comparações: %d\n", compBuscaBinVetor);
}

//////////////////////////
// Funções da LISTA
//////////////////////////

// Inserção na lista
void inserirItemLista() {
    Item novo;
    printf("Nome: ");
    scanf(" %[^\n]", novo.nome);
    printf("Tipo: ");
    scanf(" %[^\n]", novo.tipo);
    printf("Quantidade: ");
    scanf("%d", &novo.quantidade);

    No* novoNo = (No*) malloc(sizeof(No));
    novoNo->dados = novo;
    novoNo->proximo = inicioLista;
    inicioLista = novoNo;

    printf("Item adicionado na lista.\n");
}

// Remoção na lista
void removerItemLista() {
    char nome[30];
    printf("Digite o nome do item a remover (lista): ");
    scanf(" %[^\n]", nome);

    No *atual = inicioLista, *anterior = NULL;
    while (atual != NULL) {
        if (strcmp(atual->dados.nome, nome) == 0) {
            if (anterior == NULL) {
                inicioLista = atual->proximo;
            } else {
                anterior->proximo = atual->proximo;
            }
            free(atual);
            printf("Item removido da lista.\n");
            return;
        }
        anterior = atual;
        atual = atual->proximo;
    }
    printf("Item não encontrado na lista.\n");
}

// Listagem dos itens na lista
void listarItensLista() {
    No* atual = inicioLista;
    int i = 1;
    printf("Itens na mochila (lista encadeada):\n");
    while (atual != NULL) {
        printf("%d. Nome: %s | Tipo: %s | Qtd: %d\n", i++,
               atual->dados.nome, atual->dados.tipo, atual->dados.quantidade);
        atual = atual->proximo;
    }
}

// Busca sequencial na lista encadeada
void buscarSequencialLista() {
    char nome[30];
    printf("Nome do item para buscar (sequencial - lista): ");
    scanf(" %[^\n]", nome);
    compBuscaSeqLista = 0;

    No* atual = inicioLista;
    while (atual != NULL) {
        compBuscaSeqLista++;
        if (strcmp(atual->dados.nome, nome) == 0) {
            printf("Item encontrado: %s (%s), Quantidade: %d\n",
                   atual->dados.nome, atual->dados.tipo, atual->dados.quantidade);
            printf("Comparações realizadas: %d\n", compBuscaSeqLista);
            return;
        }
        atual = atual->proximo;
    }
    printf("Item não encontrado na lista. Comparações: %d\n", compBuscaSeqLista);
}

//////////////////////////
// Função principal
//////////////////////////

void menuVetor() {
    int opcao;
    do {
        printf("\n--- Menu Vetor ---\n");
        printf("1. Inserir item\n");
        printf("2. Remover item\n");
        printf("3. Listar itens\n");
        printf("4. Buscar (sequencial)\n");
        printf("5. Ordenar vetor\n");
        printf("6. Buscar (binária)\n");
        printf("0. Voltar\n");
        printf("Escolha: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1: inserirItemVetor(); break;
            case 2: removerItemVetor(); break;
            case 3: listarItensVetor(); break;
            case 4: buscarSequencialVetor(); break;
            case 5: ordenarVetor(); break;
            case 6: buscarBinariaVetor(); break;
        }
    } while (opcao != 0);
}

void menuLista() {
    int opcao;
    do {
        printf("\n--- Menu Lista Encadeada ---\n");
        printf("1. Inserir item\n");
        printf("2. Remover item\n");
        printf("3. Listar itens\n");
        printf("4. Buscar (sequencial)\n");
        printf("0. Voltar\n");
        printf("Escolha: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1: inserirItemLista(); break;
            case 2: removerItemLista(); break;
            case 3: listarItensLista(); break;
            case 4: buscarSequencialLista(); break;
        }
    } while (opcao != 0);
}

int main() {
    int escolha;

    do {
        printf("\n==== Sistema de Inventário ====\n");
        printf("1. Usar mochila com Vetor (lista sequencial)\n");
        printf("2. Usar mochila com Lista Encadeada\n");
        printf("0. Sair\n");
        printf("Escolha: ");
        scanf("%d", &escolha);

        switch (escolha) {
            case 1: menuVetor(); break;
            case 2: menuLista(); break;
            case 0: printf("Encerrando...\n"); break;
            default: printf("Opção inválida.\n");
        }

    } while (escolha != 0);

    return 0;
}
