#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_PRODUTOS 100
#define TAM_NOME 50

/* =========================
   ESTRUTURA DE DADOS
   ========================= */
typedef struct {
    int id;
    char nome[TAM_NOME];
    float preco;
    int quantidade;
} Produto;

/* =========================
   TIPOS PARA MAP / FILTER / REDUCE
   ========================= */
typedef Produto (*MapFn)(Produto p, const void *ctx);
typedef int (*FilterFn)(Produto p, const void *ctx);
typedef float (*ReduceFn)(float acc, Produto p, const void *ctx);

/* =========================
   FUNÇÕES AUXILIARES
   ========================= */
void limparBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {}
}

void lerTexto(const char *mensagem, char *destino, int tamanho) {
    printf("%s", mensagem);
    if (fgets(destino, tamanho, stdin) != NULL) {
        destino[strcspn(destino, "\n")] = '\0';
    }
}

/* =========================
   FUNÇÕES PURAS
   ========================= */
Produto criarProduto(int id, const char *nome, float preco, int quantidade) {
    Produto p;
    p.id = id;
    strncpy(p.nome, nome, TAM_NOME - 1);
    p.nome[TAM_NOME - 1] = '\0';
    p.preco = preco;
    p.quantidade = quantidade;
    return p;
}

int buscarIndicePorId(const Produto produtos[], int tamanho, int id) {
    for (int i = 0; i < tamanho; i++) {
        if (produtos[i].id == id) {
            return i;
        }
    }
    return -1;
}

int contemTextoIgnoreCase(const char *texto, const char *termo) {
    int n = strlen(texto);
    int m = strlen(termo);

    if (m == 0) return 1;
    if (m > n) return 0;

    for (int i = 0; i <= n - m; i++) {
        int igual = 1;
        for (int j = 0; j < m; j++) {
            if (tolower((unsigned char)texto[i + j]) !=
                tolower((unsigned char)termo[j])) {
                igual = 0;
                break;
            }
        }
        if (igual) return 1;
    }

    return 0;
}

/* =========================
   FUNÇÕES DE ORDEM SUPERIOR
   ========================= */
int mapProdutos(const Produto origem[], int tamanho, Produto destino[], MapFn fn, const void *ctx) {
    for (int i = 0; i < tamanho; i++) {
        destino[i] = fn(origem[i], ctx);
    }
    return tamanho;
}

int filterProdutos(const Produto origem[], int tamanho, Produto destino[], FilterFn fn, const void *ctx) {
    int j = 0;
    for (int i = 0; i < tamanho; i++) {
        if (fn(origem[i], ctx)) {
            destino[j++] = origem[i];
        }
    }
    return j;
}

float reduceProdutos(const Produto origem[], int tamanho, float valorInicial, ReduceFn fn, const void *ctx) {
    float acc = valorInicial;
    for (int i = 0; i < tamanho; i++) {
        acc = fn(acc, origem[i], ctx);
    }
    return acc;
}

/* =========================
   FUNÇÕES PARA MAP / FILTER / REDUCE
   ========================= */
Produto aplicarDesconto(Produto p, const void *ctx) {
    const float *desconto = (const float *)ctx;
    Produto novo = p;
    novo.preco = p.preco * (1.0f - (*desconto / 100.0f));
    if (novo.preco < 0) novo.preco = 0;
    return novo;
}

int filtrarPorNome(Produto p, const void *ctx) {
    const char *termo = (const char *)ctx;
    return contemTextoIgnoreCase(p.nome, termo);
}

float somarValorEstoque(float acc, Produto p, const void *ctx) {
    (void)ctx;
    return acc + (p.preco * p.quantidade);
}

/* =========================
   OPERAÇÕES DO CRUD
   ========================= */
void cadastrarProduto(Produto produtos[], int *tamanho) {
    if (*tamanho >= MAX_PRODUTOS) {
        printf("\nLimite máximo de produtos atingido.\n");
        return;
    }

    int id, quantidade;
    float preco;
    char nome[TAM_NOME];

    printf("\n--- CADASTRAR PRODUTO ---\n");

    printf("ID: ");
    if (scanf("%d", &id) != 1) {
        printf("Entrada inválida para ID.\n");
        limparBuffer();
        return;
    }
    limparBuffer();

    if (buscarIndicePorId(produtos, *tamanho, id) != -1) {
        printf("Já existe um produto com esse ID.\n");
        return;
    }

    lerTexto("Nome: ", nome, TAM_NOME);

    printf("Preço: ");
    if (scanf("%f", &preco) != 1) {
        printf("Entrada inválida para preço.\n");
        limparBuffer();
        return;
    }

    printf("Quantidade: ");
    if (scanf("%d", &quantidade) != 1) {
        printf("Entrada inválida para quantidade.\n");
        limparBuffer();
        return;
    }
    limparBuffer();

    if (preco < 0 || quantidade < 0) {
        printf("Preço e quantidade não podem ser negativos.\n");
        return;
    }

    produtos[*tamanho] = criarProduto(id, nome, preco, quantidade);
    (*tamanho)++;

    printf("Produto cadastrado com sucesso.\n");
}

void listarProdutos(const Produto produtos[], int tamanho) {
    printf("\n--- LISTA DE PRODUTOS ---\n");

    if (tamanho == 0) {
        printf("Nenhum produto cadastrado.\n");
        return;
    }

    for (int i = 0; i < tamanho; i++) {
        printf("\nProduto %d\n", i + 1);
        printf("ID: %d\n", produtos[i].id);
        printf("Nome: %s\n", produtos[i].nome);
        printf("Preço: R$ %.2f\n", produtos[i].preco);
        printf("Quantidade: %d\n", produtos[i].quantidade);
    }

    float total = reduceProdutos(produtos, tamanho, 0.0f, somarValorEstoque, NULL);
    printf("\nValor total do estoque: R$ %.2f\n", total);
}

void buscarProdutoPorId(const Produto produtos[], int tamanho) {
    int id;

    printf("\n--- BUSCAR PRODUTO POR ID ---\n");
    printf("Informe o ID: ");

    if (scanf("%d", &id) != 1) {
        printf("Entrada inválida.\n");
        limparBuffer();
        return;
    }
    limparBuffer();

    int indice = buscarIndicePorId(produtos, tamanho, id);

    if (indice == -1) {
        printf("Produto não encontrado.\n");
        return;
    }

    printf("\nProduto encontrado:\n");
    printf("ID: %d\n", produtos[indice].id);
    printf("Nome: %s\n", produtos[indice].nome);
    printf("Preço: R$ %.2f\n", produtos[indice].preco);
    printf("Quantidade: %d\n", produtos[indice].quantidade);
}

void buscarProdutoPorNome(const Produto produtos[], int tamanho) {
    char termo[TAM_NOME];
    Produto encontrados[MAX_PRODUTOS];

    printf("\n--- BUSCAR PRODUTO POR NOME ---\n");
    lerTexto("Digite parte do nome: ", termo, TAM_NOME);

    int qtd = filterProdutos(produtos, tamanho, encontrados, filtrarPorNome, termo);

    if (qtd == 0) {
        printf("Nenhum produto encontrado.\n");
        return;
    }

    printf("\nProdutos encontrados:\n");
    for (int i = 0; i < qtd; i++) {
        printf("\nID: %d\n", encontrados[i].id);
        printf("Nome: %s\n", encontrados[i].nome);
        printf("Preço: R$ %.2f\n", encontrados[i].preco);
        printf("Quantidade: %d\n", encontrados[i].quantidade);
    }
}

void deletarProduto(Produto produtos[], int *tamanho) {
    int id;

    printf("\n--- DELETAR PRODUTO ---\n");
    printf("Informe o ID do produto: ");

    if (scanf("%d", &id) != 1) {
        printf("Entrada inválida.\n");
        limparBuffer();
        return;
    }
    limparBuffer();

    int indice = buscarIndicePorId(produtos, *tamanho, id);

    if (indice == -1) {
        printf("Produto não encontrado.\n");
        return;
    }

    for (int i = indice; i < *tamanho - 1; i++) {
        produtos[i] = produtos[i + 1];
    }

    (*tamanho)--;

    printf("Produto removido com sucesso.\n");
}

void mostrarProdutosComDesconto(const Produto produtos[], int tamanho) {
    if (tamanho == 0) {
        printf("\nNenhum produto cadastrado.\n");
        return;
    }

    float desconto;
    Produto transformados[MAX_PRODUTOS];

    printf("\n--- MAP: APLICAR DESCONTO ---\n");
    printf("Percentual de desconto: ");

    if (scanf("%f", &desconto) != 1) {
        printf("Entrada inválida.\n");
        limparBuffer();
        return;
    }
    limparBuffer();

    if (desconto < 0) {
        printf("Desconto inválido.\n");
        return;
    }

    mapProdutos(produtos, tamanho, transformados, aplicarDesconto, &desconto);

    printf("\nProdutos com %.2f%% de desconto:\n", desconto);
    for (int i = 0; i < tamanho; i++) {
        printf("\nID: %d\n", transformados[i].id);
        printf("Nome: %s\n", transformados[i].nome);
        printf("Preço original: R$ %.2f\n", produtos[i].preco);
        printf("Preço com desconto: R$ %.2f\n", transformados[i].preco);
        printf("Quantidade: %d\n", transformados[i].quantidade);
    }
}

void mostrarValorTotalEstoque(const Produto produtos[], int tamanho) {
    float total = reduceProdutos(produtos, tamanho, 0.0f, somarValorEstoque, NULL);
    printf("\n--- REDUCE: VALOR TOTAL DO ESTOQUE ---\n");
    printf("Valor total: R$ %.2f\n", total);
}

/* =========================
   MENU
   ========================= */
void mostrarMenu() {
    printf("\n=====================================\n");
    printf("     SISTEMA DE CADASTRO DE PRODUTOS\n");
    printf("=====================================\n");
    printf("1 - Cadastrar produto\n");
    printf("2 - Listar produtos\n");
    printf("3 - Buscar produto por ID\n");
    printf("4 - Buscar produto por nome (FILTER)\n");
    printf("5 - Deletar produto\n");
    printf("6 - Mostrar produtos com desconto (MAP)\n");
    printf("7 - Mostrar valor total do estoque (REDUCE)\n");
    printf("0 - Sair\n");
    printf("Escolha uma opção: ");
}

int main() {
    Produto produtos[MAX_PRODUTOS];
    int tamanho = 0;
    int opcao;

    while (1) {
        mostrarMenu();

        if (scanf("%d", &opcao) != 1) {
            printf("Opção inválida.\n");
            limparBuffer();
            continue;
        }
        limparBuffer();

        if (opcao == 0) {
            printf("\nEncerrando o programa...\n");
            break;
        }

        if (opcao == 1) {
            cadastrarProduto(produtos, &tamanho);
        } else if (opcao == 2) {
            listarProdutos(produtos, tamanho);
        } else if (opcao == 3) {
            buscarProdutoPorId(produtos, tamanho);
        } else if (opcao == 4) {
            buscarProdutoPorNome(produtos, tamanho);
        } else if (opcao == 5) {
            deletarProduto(produtos, &tamanho);
        } else if (opcao == 6) {
            mostrarProdutosComDesconto(produtos, tamanho);
        } else if (opcao == 7) {
            mostrarValorTotalEstoque(produtos, tamanho);
        } else {
            printf("Opção inválida. Tente novamente.\n");
        }
    }

    return 0;
}
