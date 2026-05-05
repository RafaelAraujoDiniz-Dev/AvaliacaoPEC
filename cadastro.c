from functools import reduce

# ===============================
# DADOS (ESTADO MUTÁVEL - IMPERATIVO)
# ===============================
# Lista global que será modificada ao longo do programa
produtos = []

# ===============================
# FUNÇÕES FUNCIONAIS (PURO / FUNCIONAL)
# ===============================

# Função pura: não altera estado externo
def criar_produto(id, nome, preco):
    return {"id": id, "nome": nome, "preco": preco}

# Função pura + uso de filter (ordem superior)
def buscar_por_id(lista, id):
    resultado = list(filter(lambda p: p["id"] == id, lista))
    return resultado[0] if resultado else None

# Função funcional: retorna NOVA lista (imutabilidade)
# Uso de map (ordem superior)
def atualizar_produto(lista, id, novo_nome, novo_preco):
    return list(map(lambda p: 
        {"id": id, "nome": novo_nome, "preco": novo_preco} if p["id"] == id else p, lista))

# Função funcional: retorna nova lista sem modificar a original
# Uso de filter
def remover_produto(lista, id):
    return list(filter(lambda p: p["id"] != id, lista))

# Função funcional: cálculo sem efeitos colaterais
# Uso de reduce
def calcular_total(lista):
    return reduce(lambda acc, p: acc + p["preco"], lista, 0)

# ===============================
# FUNÇÕES IMPERATIVAS (CONTROLE E ESTADO)
# ===============================

# Imperativo: altera diretamente a variável global (efeito colateral)
def cadastrar():
    global produtos  # manipulação direta de estado
    id = int(input("ID: "))         # entrada de dados (efeito colateral)
    nome = input("Nome: ")
    preco = float(input("Preço: "))

    produto = criar_produto(id, nome, preco)  # usa função funcional
    produtos.append(produto)  # alteração de estado (mutável)
    print("Produto cadastrado!")  # saída (efeito colateral)

# Imperativo: controle com if + entrada/saída
def pesquisar():
    id = int(input("Digite o ID: "))
    produto = buscar_por_id(produtos, id)

    if produto:  # estrutura de controle
        print("Encontrado:", produto)
    else:
        print("Produto não encontrado.")

# Imperativo + funcional misto
def atualizar():
    global produtos
    id = int(input("ID do produto: "))
    nome = input("Novo nome: ")
    preco = float(input("Novo preço: "))

    if buscar_por_id(produtos, id):  # decisão (if)
        produtos = atualizar_produto(produtos, id, nome, preco)
        # substitui estado antigo por novo (misto: funcional + imperativo)
        print("Produto atualizado!")
    else:
        print("Produto não encontrado.")

# Imperativo + funcional
def deletar():
    global produtos
    id = int(input("ID do produto: "))

    if buscar_por_id(produtos, id):
        produtos = remover_produto(produtos, id)
        print("Produto removido!")
    else:
        print("Produto não encontrado.")

# Imperativo: uso de for + saída de dados
def listar():
    if not produtos:
        print("Nenhum produto cadastrado.")
        return

    print("\nLista de produtos:")
    for p in produtos:  # loop (imperativo)
        print(p)

    # cálculo funcional
    total = calcular_total(produtos)
    print("Valor total em estoque:", total)

# ===============================
# MENU (FLUXO IMPERATIVO)
# ===============================

def menu():
    while True:  # loop principal (imperativo)
        print("\n--- SISTEMA DE PRODUTOS ---")
        print("1 - Cadastrar")
        print("2 - Pesquisar")
        print("3 - Atualizar")
        print("4 - Deletar")
        print("5 - Listar")
        print("0 - Sair")

        opcao = input("Escolha: ")

        # Estrutura de decisão (imperativo)
        if opcao == "1":
            cadastrar()
        elif opcao == "2":
            pesquisar()
        elif opcao == "3":
            atualizar()
        elif opcao == "4":
            deletar()
        elif opcao == "5":
            listar()
        elif opcao == "0":
            print("Saindo...")
            break
        else:
            print("Opção inválida!")

# ===============================
# EXECUÇÃO (SEQUENCIAL - IMPERATIVO)
# ===============================
menu()
