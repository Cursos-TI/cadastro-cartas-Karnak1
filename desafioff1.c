#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_ITENS 10

// Definição da struct que representa um item da mochila
typedef struct {
    char nome[30];
    char tipo[20];
    int quantidade;
} Item;

// Vetor que armazena os itens e um contador de itens cadastrados
Item mochila[MAX_ITENS];
int totalItens = 0;

// Função para inserir um novo item
void inserirItem() {
    if (totalItens >= MAX_ITENS) {
        printf("Mochila cheia! Não é possível adicionar mais itens.\n");
        return;
    }

    Item novoItem;

    printf("Digite o nome do item: ");
    scanf(" %[^\n]", novoItem.nome);  // Lê até a quebra de linha

    printf("Digite o tipo do item (arma, munição, cura, etc.): ");
    scanf(" %[^\n]", novoItem.tipo);

    printf("Digite a quantidade do item: ");
    scanf("%d", &novoItem.quantidade);

    mochila[totalItens] = novoItem;
    totalItens++;

    printf("Item adicionado com sucesso!\n");
}

// Função para remover um item pelo nome
void removerItem() {
    char nomeRemover[30];
    int encontrado = 0;

    printf("Digite o nome do item que deseja remover: ");
    scanf(" %[^\n]", nomeRemover);

    for (int i = 0; i < totalItens; i++) {
        if (strcmp(mochila[i].nome, nomeRemover) == 0) {
            // Move os itens seguintes uma posição para trás
            for (int j = i; j < totalItens - 1; j++) {
                mochila[j] = mochila[j + 1];
            }
            totalItens--;
            printf("Item \"%s\" removido com sucesso!\n", nomeRemover);
            encontrado = 1;
            break;
        }
    }

    if (!encontrado) {
        printf("Item \"%s\" não encontrado na mochila.\n", nomeRemover);
    }
}

// Função para listar todos os itens da mochila
void listarItens() {
    if (totalItens == 0) {
        printf("A mochila está vazia.\n");
        return;
    }

    printf("\n--- Itens na mochila ---\n");
    for (int i = 0; i < totalItens; i++) {
        printf("Item %d:\n", i + 1);
        printf("  Nome: %s\n", mochila[i].nome);
        printf("  Tipo: %s\n", mochila[i].tipo);
        printf("  Quantidade: %d\n", mochila[i].quantidade);
    }
    printf("------------------------\n");
}

// Função para buscar um item pelo nome (busca sequencial)
void buscarItem() {
    char nomeBuscar[30];
    int encontrado = 0;

    printf("Digite o nome do item que deseja buscar: ");
    scanf(" %[^\n]", nomeBuscar);

    for (int i = 0; i < totalItens; i++) {
        if (strcmp(mochila[i].nome, nomeBuscar) == 0) {
            printf("\nItem encontrado:\n");
            printf("  Nome: %s\n", mochila[i].nome);
            printf("  Tipo: %s\n", mochila[i].tipo);
            printf("  Quantidade: %d\n", mochila[i].quantidade);
            encontrado = 1;
            break;
        }
    }

    if (!encontrado) {
        printf("Item \"%s\" não encontrado na mochila.\n", nomeBuscar);
    }
}

// Função principal com menu de opções
int main() {
    int opcao;

    do {
        printf("\n=== Sistema de Inventário ===\n");
        printf("1. Cadastrar item\n");
        printf("2. Remover item\n");
        printf("3. Listar itens\n");
        printf("4. Buscar item\n");
        printf("0. Sair\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                inserirItem();
                listarItens();
                break;
            case 2:
                removerItem();
                listarItens();
                break;
            case 3:
                listarItens();
                break;
            case 4:
                buscarItem();
                break;
            case 0:
                printf("Encerrando o programa. Até logo!\n");
                break;
            default:
                printf("Opção inválida. Tente novamente.\n");
        }

    } while (opcao != 0);

    return 0;
}
