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

void adicionarProduto(int id, const char *nome, float preco) {
    if (totalProdutos < MAX_PRODUTOS) {
        produtos[totalProdutos].id = id;
        strncpy(produtos[totalProdutos].nome, nome, 99);
        produtos[totalProdutos].nome[99] = '\0';
        produtos[totalProdutos].preco = preco;
        totalProdutos++;
        printf("[OK] Produto adicionado: %s (ID: %d) - Preco: R$ %.2f\n", nome, id, preco);
    } else {
        printf("[ERRO] Limite de produtos alcancado!\n");
    }
}

void listarProdutos() {
    if (totalProdutos == 0) {
        printf("Nenhum produto cadastrado.\n");
        return;
    }
    printf("%-6s %-30s %-12s\n", "ID", "NOME", "PRECO");
    printf("----------------------------------------------\n");
    for (int i = 0; i < totalProdutos; i++) {
        printf("%-6d %-30s R$ %.2f\n",
               produtos[i].id, produtos[i].nome, produtos[i].preco);
    }
}

Produto *buscarProduto(int id) {
    for (int i = 0; i < totalProdutos; i++) {
        if (produtos[i].id == id) {
            return &produtos[i];
        }
    }
    return NULL;
}

void atualizarPreco(int id, float novoPreco) {
    Produto *produto = buscarProduto(id);
    if (produto) {
        produto->preco = novoPreco;
        printf("[OK] Preco atualizado: ID=%d, Novo Preco=R$ %.2f\n", id, novoPreco);
    } else {
        printf("[AVISO] Produto com ID %d nao encontrado!\n", id);
    }
}

void deletarProduto(int id) {
    for (int i = 0; i < totalProdutos; i++) {
        if (produtos[i].id == id) {
            for (int j = i; j < totalProdutos - 1; j++) {
                produtos[j] = produtos[j + 1];
            }
            totalProdutos--;
            printf("[OK] Produto ID %d deletado!\n", id);
            return;
        }
    }
    printf("[AVISO] Produto com ID %d nao encontrado!\n", id);
}

float calcularTotal() {
    float total = 0;
    for (int i = 0; i < totalProdutos; i++) {
        total += produtos[i].preco;
    }
    return total;
}

void menuImperativo() {
    int opcao, id;
    char nome[100];
    float preco;

    do {
        printf("\n+--------------------------------------+\n");
        printf("|       PARADIGMA IMPERATIVO           |\n");
        printf("+--------------------------------------+\n");
        printf("| 1. Adicionar Produto                 |\n");
        printf("| 2. Listar Produtos                   |\n");
        printf("| 3. Buscar Produto                    |\n");
        printf("| 4. Atualizar Preco                   |\n");
        printf("| 5. Deletar Produto                   |\n");
        printf("| 6. Calcular Total                    |\n");
        printf("| 0. Sair                              |\n");
        printf("+--------------------------------------+\n");
        printf("Escolha uma opcao: ");
        if (scanf("%d", &opcao) != 1) {
            opcao = -1;
        }
        while (getchar() != '\n');

        switch (opcao) {
            case 1:
                printf("ID: ");
                if (scanf("%d", &id) != 1) {
                    printf("[ERRO] ID invalido!\n");
                    while (getchar() != '\n');
                    break;
                }
                while (getchar() != '\n');
                printf("Nome: ");
                fgets(nome, sizeof(nome), stdin);
                nome[strcspn(nome, "\n")] = '\0';
                printf("Preco: R$ ");
                if (scanf("%f", &preco) != 1) {
                    printf("[ERRO] Preco invalido!\n");
                    while (getchar() != '\n');
                    break;
                }
                while (getchar() != '\n');
                adicionarProduto(id, nome, preco);
                break;
            case 2:
                printf("\n--- LISTA DE PRODUTOS ---\n");
                listarProdutos();
                break;
            case 3: {
                printf("ID do produto: ");
                if (scanf("%d", &id) != 1) {
                    printf("[ERRO] ID invalido!\n");
                    while (getchar() != '\n');
                    break;
                }
                while (getchar() != '\n');
                Produto *p = buscarProduto(id);
                if (p) {
                    printf("[OK] ID=%d | Nome=%s | Preco=R$ %.2f\n",
                           p->id, p->nome, p->preco);
                } else {
                    printf("[AVISO] Produto nao encontrado!\n");
                }
                break;
            }
            case 4:
                printf("ID e Novo Preco: ");
                if (scanf("%d %f", &id, &preco) != 2) {
                    printf("[ERRO] Entrada invalida!\n");
                    while (getchar() != '\n');
                    break;
                }
                while (getchar() != '\n');
                atualizarPreco(id, preco);
                break;
            case 5:
                printf("ID do produto a deletar: ");
                if (scanf("%d", &id) != 1) {
                    printf("[ERRO] ID invalido!\n");
                    while (getchar() != '\n');
                    break;
                }
                while (getchar() != '\n');
                deletarProduto(id);
                break;
            case 6:
                printf("Total do estoque: R$ %.2f\n", calcularTotal());
                break;
            case 0:
                printf("Saindo...\n");
                break;
            default:
                printf("[ERRO] Opcao invalida!\n");
        }
    } while (opcao != 0);
}

int main() {
    menuImperativo();
    return 0;
}
