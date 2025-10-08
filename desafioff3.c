#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_COMPONENTES 20

// Struct que representa um componente da torre
typedef struct {
    char nome[30];
    char tipo[20];
    int prioridade;
} Componente;

// Função para mostrar os componentes
void mostrarComponentes(Componente comp[], int n) {
    printf("\n--- Componentes da Torre ---\n");
    for (int i = 0; i < n; i++) {
        printf("%02d. Nome: %-20s | Tipo: %-15s | Prioridade: %d\n", 
               i+1, comp[i].nome, comp[i].tipo, comp[i].prioridade);
    }
    printf("-----------------------------\n");
}

// Função para cadastro dos componentes
int cadastrarComponentes(Componente comp[]) {
    int n;
    printf("Quantos componentes deseja cadastrar? (máx %d): ", MAX_COMPONENTES);
    scanf("%d", &n);
    getchar(); // limpar buffer

    if (n > MAX_COMPONENTES || n <= 0) {
        printf("Quantidade inválida.\n");
        return 0;
    }

    for (int i = 0; i < n; i++) {
        printf("\nComponente %d:\n", i + 1);

        printf("  Nome: ");
        fgets(comp[i].nome, sizeof(comp[i].nome), stdin);
        comp[i].nome[strcspn(comp[i].nome, "\n")] = 0; // Remove \n

        printf("  Tipo: ");
        fgets(comp[i].tipo, sizeof(comp[i].tipo), stdin);
        comp[i].tipo[strcspn(comp[i].tipo, "\n")] = 0;

        printf("  Prioridade (1 a 10): ");
        scanf("%d", &comp[i].prioridade);
        getchar(); // limpar buffer
    }

    return n;
}

// Ordenação: Bubble Sort por nome
int bubbleSortNome(Componente comp[], int n) {
    int compCount = 0;
    for (int i = 0; i < n-1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            compCount++;
            if (strcmp(comp[j].nome, comp[j+1].nome) > 0) {
                Componente temp = comp[j];
                comp[j] = comp[j+1];
                comp[j+1] = temp;
            }
        }
    }
    return compCount;
}

// Ordenação: Insertion Sort por tipo
int insertionSortTipo(Componente comp[], int n) {
    int compCount = 0;
    for (int i = 1; i < n; i++) {
        Componente key = comp[i];
        int j = i - 1;

        while (j >= 0 && strcmp(comp[j].tipo, key.tipo) > 0) {
            comp[j + 1] = comp[j];
            j--;
            compCount++;
        }
        comp[j + 1] = key;
        if (j >= 0) compCount++;
    }
    return compCount;
}

// Ordenação: Selection Sort por prioridade
int selectionSortPrioridade(Componente comp[], int n) {
    int compCount = 0;
    for (int i = 0; i < n - 1; i++) {
        int min = i;
        for (int j = i + 1; j < n; j++) {
            compCount++;
            if (comp[j].prioridade < comp[min].prioridade) {
                min = j;
            }
        }
        if (min != i) {
            Componente temp = comp[i];
            comp[i] = comp[min];
            comp[min] = temp;
        }
    }
    return compCount;
}

// Busca binária por nome (após ordenação por nome)
int buscaBinariaPorNome(Componente comp[], int n, char nomeBusca[], int *comparacoes) {
    int esq = 0, dir = n - 1;
    *comparacoes = 0;

    while (esq <= dir) {
        int meio = (esq + dir) / 2;
        (*comparacoes)++;
        int cmp = strcmp(comp[meio].nome, nomeBusca);

        if (cmp == 0) return meio;
        else if (cmp < 0) esq = meio + 1;
        else dir = meio - 1;
    }
    return -1;
}

// Medidor de tempo para qualquer algoritmo de ordenação
double medirTempoOrdenacao(int (*alg)(Componente[], int), Componente comp[], int n, int *comparacoes) {
    clock_t inicio = clock();
    *comparacoes = alg(comp, n);
    clock_t fim = clock();
    return ((double)(fim - inicio)) / CLOCKS_PER_SEC;
}

// Cópia do array original para evitar ordenações sobre os dados de entrada
void copiarArray(Componente origem[], Componente destino[], int n) {
    for (int i = 0; i < n; i++) {
        destino[i] = origem[i];
    }
}

int main() {
    Componente componentes[MAX_COMPONENTES];
    Componente copia[MAX_COMPONENTES];
    int n = 0, comparacoes = 0;
    double tempo = 0;
    int escolha = -1;

    printf(">>> Torre de Fuga - Montagem Estratégica Final <<<\n");

    n = cadastrarComponentes(componentes);
    if (n == 0) return 0;

    while (escolha != 0) {
        printf("\nEscolha a estratégia de ordenação:\n");
        printf("1. Ordenar por Nome (Bubble Sort)\n");
        printf("2. Ordenar por Tipo (Insertion Sort)\n");
        printf("3. Ordenar por Prioridade (Selection Sort)\n");
        printf("0. Sair\n");
        printf("Opção: ");
        scanf("%d", &escolha);
        getchar(); // limpar buffer

        copiarArray(componentes, copia, n);

        switch (escolha) {
            case 1:
                tempo = medirTempoOrdenacao(bubbleSortNome, copia, n, &comparacoes);
                printf("\nOrdenado por NOME (Bubble Sort):\n");
                mostrarComponentes(copia, n);
                printf("Comparações: %d | Tempo: %.6f segundos\n", comparacoes, tempo);

                // Buscar componente-chave
                char chave[30];
                printf("\nDigite o nome do componente-chave para buscar: ");
                fgets(chave, sizeof(chave), stdin);
                chave[strcspn(chave, "\n")] = 0;

                int pos;
                pos = buscaBinariaPorNome(copia, n, chave, &comparacoes);
                if (pos != -1) {
                    printf("Componente-chave \"%s\" encontrado na posição %d.\n", chave, pos + 1);
                } else {
                    printf("Componente-chave \"%s\" não encontrado.\n", chave);
                }
                printf("Comparações na busca binária: %d\n", comparacoes);
                break;

            case 2:
                tempo = medirTempoOrdenacao(insertionSortTipo, copia, n, &comparacoes);
                printf("\nOrdenado por TIPO (Insertion Sort):\n");
                mostrarComponentes(copia, n);
                printf("Comparações: %d | Tempo: %.6f segundos\n", comparacoes, tempo);
                break;

            case 3:
                tempo = medirTempoOrdenacao(selectionSortPrioridade, copia, n, &comparacoes);
                printf("\nOrdenado por PRIORIDADE (Selection Sort):\n");
                mostrarComponentes(copia, n);
                printf("Comparações: %d | Tempo: %.6f segundos\n", comparacoes, tempo);
                break;

            case 0:
                printf("Saindo do sistema...\n");
                break;

            default:
                printf("Opção inválida. Tente novamente.\n");
        }
    }

    return 0;
}
