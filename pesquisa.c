#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_PRODUTOS 100

typedef struct {
    int id;
    char nome[100];
    float preco;
} Produto;

Produto produtos[MAX_PRODUTOS];
int totalProdutos = 0;

void adicionarProduto();
void listarProdutos();
void buscarPorId();
void buscarPorNome();
void buscarPorPreco();
void exibirMenu();

int main() {
    int opcao;

    while (1) {
        exibirMenu();
        printf("Escolha: ");
        if (scanf("%d", &opcao) != 1) {
            opcao = -1;
        }
        while (getchar() != '\n');

        switch (opcao) {
            case 1: adicionarProduto(); break;
            case 2: listarProdutos(); break;
            case 3: buscarPorId(); break;
            case 4: buscarPorNome(); break;
            case 5: buscarPorPreco(); break;
            case 0:
                printf("\nAte logo!\n\n");
                return 0;
            default:
                printf("\n[ERRO] Opcao invalida!\n");
        }
    }
}

void exibirMenu() {
    printf("\n+----------------------------------+\n");
    printf("|  PESQUISA DE PRODUTOS - SIMPLES  |\n");
    printf("+----------------------------------+\n");
    printf("| 1. Adicionar Produto             |\n");
    printf("| 2. Listar Todos                  |\n");
    printf("| 3. Buscar por ID                 |\n");
    printf("| 4. Buscar por Nome               |\n");
    printf("| 5. Buscar por Faixa de Preco     |\n");
    printf("| 0. Sair                          |\n");
    printf("+----------------------------------+\n");
}

void adicionarProduto() {
    if (totalProdutos >= MAX_PRODUTOS) {
        printf("\n[ERRO] Limite de produtos atingido!\n");
        return;
    }

    printf("\n--- ADICIONAR PRODUTO ---\n");
    Produto p;

    printf("ID: ");
    if (scanf("%d", &p.id) != 1 || p.id <= 0) {
        printf("[ERRO] ID invalido!\n");
        while (getchar() != '\n');
        return;
    }
    while (getchar() != '\n');

    /* Verifica se o ID ja existe */
    for (int i = 0; i < totalProdutos; i++) {
        if (produtos[i].id == p.id) {
            printf("[ERRO] Produto com ID %d ja existe!\n", p.id);
            return;
        }
    }

    printf("Nome: ");
    if (fgets(p.nome, sizeof(p.nome), stdin) == NULL || p.nome[0] == '\n') {
        printf("[ERRO] Nome invalido!\n");
        return;
    }
    p.nome[strcspn(p.nome, "\n")] = '\0';

    printf("Preco: R$ ");
    if (scanf("%f", &p.preco) != 1 || p.preco < 0) {
        printf("[ERRO] Preco invalido!\n");
        while (getchar() != '\n');
        return;
    }
    while (getchar() != '\n');

    produtos[totalProdutos++] = p;
    printf("[OK] Adicionado!\n");
}

void listarProdutos() {
    printf("\n--- PRODUTOS (%d) ---\n", totalProdutos);
    if (totalProdutos == 0) {
        printf("Nenhum produto cadastrado.\n");
        return;
    }
    printf("======================================\n");
    printf("%-6s %-30s %-12s\n", "ID", "NOME", "PRECO");
    printf("--------------------------------------\n");
    for (int i = 0; i < totalProdutos; i++) {
        printf("%-6d %-30s R$ %.2f\n",
               produtos[i].id, produtos[i].nome, produtos[i].preco);
    }
    printf("======================================\n");
}

void buscarPorId() {
    if (totalProdutos == 0) {
        printf("\nNenhum produto cadastrado.\n");
        return;
    }

    printf("\n--- BUSCAR POR ID ---\n");
    int id;
    printf("Digite o ID: ");
    if (scanf("%d", &id) != 1) {
        printf("[ERRO] ID invalido!\n");
        while (getchar() != '\n');
        return;
    }
    while (getchar() != '\n');

    for (int i = 0; i < totalProdutos; i++) {
        if (produtos[i].id == id) {
            printf("\n[OK] Encontrado!\n");
            printf("  ID:    %d\n", produtos[i].id);
            printf("  Nome:  %s\n", produtos[i].nome);
            printf("  Preco: R$ %.2f\n", produtos[i].preco);
            return;
        }
    }
    printf("[AVISO] ID %d nao encontrado.\n", id);
}

void buscarPorNome() {
    if (totalProdutos == 0) {
        printf("\nNenhum produto cadastrado.\n");
        return;
    }

    printf("\n--- BUSCAR POR NOME ---\n");
    char termo[100];
    printf("Digite o nome (ou parte): ");
    if (fgets(termo, sizeof(termo), stdin) == NULL || termo[0] == '\n') {
        printf("[ERRO] Entrada invalida!\n");
        return;
    }
    termo[strcspn(termo, "\n")] = '\0';

    printf("\nResultados para \"%s\":\n", termo);
    printf("--------------------------------------\n");

    int encontrados = 0;
    for (int i = 0; i < totalProdutos; i++) {
        if (strstr(produtos[i].nome, termo) != NULL) {
            printf("ID: %d | %s | R$ %.2f\n",
                   produtos[i].id, produtos[i].nome, produtos[i].preco);
            encontrados++;
        }
    }

    if (encontrados == 0) {
        printf("[AVISO] Nenhum produto encontrado.\n");
    } else {
        printf("--------------------------------------\n");
        printf("[OK] %d produto(s) encontrado(s).\n", encontrados);
    }
}

void buscarPorPreco() {
    if (totalProdutos == 0) {
        printf("\nNenhum produto cadastrado.\n");
        return;
    }

    printf("\n--- BUSCAR POR FAIXA DE PRECO ---\n");
    float precoMin, precoMax;

    printf("Preco minimo: R$ ");
    if (scanf("%f", &precoMin) != 1 || precoMin < 0) {
        printf("[ERRO] Preco invalido!\n");
        while (getchar() != '\n');
        return;
    }

    printf("Preco maximo: R$ ");
    if (scanf("%f", &precoMax) != 1 || precoMax < precoMin) {
        printf("[ERRO] Preco maximo deve ser maior que o minimo!\n");
        while (getchar() != '\n');
        return;
    }
    while (getchar() != '\n');

    printf("\nProdutos entre R$ %.2f e R$ %.2f:\n", precoMin, precoMax);
    printf("--------------------------------------\n");

    int encontrados = 0;
    for (int i = 0; i < totalProdutos; i++) {
        if (produtos[i].preco >= precoMin && produtos[i].preco <= precoMax) {
            printf("ID: %d | %s | R$ %.2f\n",
                   produtos[i].id, produtos[i].nome, produtos[i].preco);
            encontrados++;
        }
    }

    if (encontrados == 0) {
        printf("[AVISO] Nenhum produto encontrado nessa faixa.\n");
    } else {
        printf("--------------------------------------\n");
        printf("[OK] %d produto(s) encontrado(s).\n", encontrados);
    }
}
