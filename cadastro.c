#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_PRODUTOS 100

typedef struct {
    int id;
    char nome[100];
    float preco;
} Produto;

Produto estoque[MAX_PRODUTOS];
int totalProdutos = 0;

void exibirMenu();
void adicionarProduto();
void listarProdutos();
void buscarProduto();
void atualizarProduto();
void deletarProduto();
void calcularTotalEstoque();

int main() {
    int opcao;
    do {
        exibirMenu();
        printf("Escolha uma opcao: ");
        if (scanf("%d", &opcao) != 1) {
            opcao = -1;
        }
        while (getchar() != '\n');
        switch (opcao) {
            case 1: adicionarProduto(); break;
            case 2: listarProdutos(); break;
            case 3: buscarProduto(); break;
            case 4: atualizarProduto(); break;
            case 5: deletarProduto(); break;
            case 6: calcularTotalEstoque(); break;
            case 0: printf("\nSaindo... Ate logo!\n\n"); break;
            default: printf("\nOpcao invalida! Tente novamente.\n");
        }
    } while (opcao != 0);
    return 0;
}

void exibirMenu() {
    printf("\n+--------------------------------------+\n");
    printf("|   SISTEMA DE CADASTRO DE PRODUTOS    |\n");
    printf("+--------------------------------------+\n");
    printf("| 1. Adicionar Produto                 |\n");
    printf("| 2. Listar Produtos                   |\n");
    printf("| 3. Buscar Produto por ID             |\n");
    printf("| 4. Atualizar Produto                 |\n");
    printf("| 5. Deletar Produto                   |\n");
    printf("| 6. Calcular Total do Estoque         |\n");
    printf("| 0. Sair                              |\n");
    printf("+--------------------------------------+\n");
}

void adicionarProduto() {
    if (totalProdutos >= MAX_PRODUTOS) {
        printf("\n[ERRO] Estoque cheio! Nao e possivel adicionar mais produtos.\n");
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
        if (estoque[i].id == p.id) {
            printf("[ERRO] Produto com ID %d ja cadastrado!\n", p.id);
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

    estoque[totalProdutos++] = p;
    printf("[OK] Produto \"%s\" adicionado com sucesso!\n", p.nome);
}

void listarProdutos() {
    printf("\n--- LISTA DE PRODUTOS (%d cadastrado(s)) ---\n", totalProdutos);
    if (totalProdutos == 0) {
        printf("Nenhum produto cadastrado.\n");
        return;
    }
    printf("%-6s %-30s %-12s\n", "ID", "NOME", "PRECO");
    printf("----------------------------------------------\n");
    for (int i = 0; i < totalProdutos; i++) {
        printf("%-6d %-30s R$ %.2f\n",
               estoque[i].id, estoque[i].nome, estoque[i].preco);
    }
    printf("----------------------------------------------\n");
}

void buscarProduto() {
    if (totalProdutos == 0) {
        printf("\nNenhum produto cadastrado.\n");
        return;
    }

    printf("\n--- BUSCAR PRODUTO ---\n");
    int id;
    printf("Digite o ID: ");
    if (scanf("%d", &id) != 1) {
        printf("[ERRO] ID invalido!\n");
        while (getchar() != '\n');
        return;
    }
    while (getchar() != '\n');

    for (int i = 0; i < totalProdutos; i++) {
        if (estoque[i].id == id) {
            printf("\n[OK] Produto encontrado:\n");
            printf("  ID:    %d\n", estoque[i].id);
            printf("  Nome:  %s\n", estoque[i].nome);
            printf("  Preco: R$ %.2f\n", estoque[i].preco);
            return;
        }
    }
    printf("[AVISO] Produto com ID %d nao encontrado.\n", id);
}

void atualizarProduto() {
    if (totalProdutos == 0) {
        printf("\nNenhum produto cadastrado.\n");
        return;
    }

    printf("\n--- ATUALIZAR PRODUTO ---\n");
    int id;
    printf("Digite o ID do produto a atualizar: ");
    if (scanf("%d", &id) != 1) {
        printf("[ERRO] ID invalido!\n");
        while (getchar() != '\n');
        return;
    }
    while (getchar() != '\n');

    for (int i = 0; i < totalProdutos; i++) {
        if (estoque[i].id == id) {
            printf("Produto atual: ID=%d | Nome=%s | Preco=R$ %.2f\n",
                   estoque[i].id, estoque[i].nome, estoque[i].preco);

            printf("Novo nome (Enter para manter \"%s\"): ", estoque[i].nome);
            char novoNome[100];
            if (fgets(novoNome, sizeof(novoNome), stdin) != NULL) {
                novoNome[strcspn(novoNome, "\n")] = '\0';
                if (novoNome[0] != '\0') {
                    strncpy(estoque[i].nome, novoNome, sizeof(estoque[i].nome) - 1);
                    estoque[i].nome[sizeof(estoque[i].nome) - 1] = '\0';
                }
            }

            printf("Novo preco (0 para manter R$ %.2f): R$ ", estoque[i].preco);
            float novoPreco;
            if (scanf("%f", &novoPreco) == 1 && novoPreco > 0) {
                estoque[i].preco = novoPreco;
            }
            while (getchar() != '\n');

            printf("[OK] Produto atualizado: ID=%d | Nome=%s | Preco=R$ %.2f\n",
                   estoque[i].id, estoque[i].nome, estoque[i].preco);
            return;
        }
    }
    printf("[AVISO] Produto com ID %d nao encontrado.\n", id);
}

void deletarProduto() {
    if (totalProdutos == 0) {
        printf("\nNenhum produto cadastrado.\n");
        return;
    }

    printf("\n--- DELETAR PRODUTO ---\n");
    int id;
    printf("Digite o ID do produto a deletar: ");
    if (scanf("%d", &id) != 1) {
        printf("[ERRO] ID invalido!\n");
        while (getchar() != '\n');
        return;
    }
    while (getchar() != '\n');

    for (int i = 0; i < totalProdutos; i++) {
        if (estoque[i].id == id) {
            printf("Confirma exclusao de \"%s\"? (s/n): ", estoque[i].nome);
            char confirmacao = getchar();
            while (getchar() != '\n');
            if (confirmacao != 's' && confirmacao != 'S') {
                printf("Exclusao cancelada.\n");
                return;
            }
            for (int j = i; j < totalProdutos - 1; j++) {
                estoque[j] = estoque[j + 1];
            }
            totalProdutos--;
            printf("[OK] Produto deletado com sucesso!\n");
            return;
        }
    }
    printf("[AVISO] Produto com ID %d nao encontrado.\n", id);
}

void calcularTotalEstoque() {
    printf("\n--- TOTAL DO ESTOQUE ---\n");
    if (totalProdutos == 0) {
        printf("Nenhum produto cadastrado.\n");
        return;
    }
    float total = 0.0f;
    for (int i = 0; i < totalProdutos; i++) {
        total += estoque[i].preco;
    }
    printf("Total de produtos: %d\n", totalProdutos);
    printf("Valor total do estoque: R$ %.2f\n", total);
}