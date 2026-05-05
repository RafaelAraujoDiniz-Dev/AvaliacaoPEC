"""
Sistema de Cadastro de Produtos - Abordagem Híbrida
====================================================
Combina Paradigma Imperativo e Funcional em um único arquivo Python.

PARADIGMA IMPERATIVO:
  - Variáveis mutáveis para armazenar o estado
  - Estruturas de controle (if, for, while)
  - Código estruturado e sequencial
  - Manipulação direta de estado

PARADIGMA FUNCIONAL:
  - Funções puras quando possível
  - Imutabilidade de dados onde aplicável
  - Funções de ordem superior (map, filter, reduce)
  - Evitar efeitos colaterais
  - Separação clara entre dados e operações
"""

from functools import reduce

# =============================================================================
# ESTADO GLOBAL (Paradigma Imperativo)
# Variáveis mutáveis que armazenam o estado do sistema.
# =============================================================================

produtos: list[dict] = []   # Lista mutável de produtos (dicionários)
proximo_id: int = 1         # Contador mutável de IDs


# =============================================================================
# FUNÇÕES PURAS - Paradigma Funcional
# Não produzem efeitos colaterais e retornam o mesmo resultado para a
# mesma entrada. Trabalham sobre cópias imutáveis dos dados.
# =============================================================================

def criar_produto(id_: int, nome: str, preco: float, quantidade: int) -> dict:
    """Cria e retorna um novo dicionário produto (função pura)."""
    return {
        "id": id_,
        "nome": nome,
        "preco": round(preco, 2),
        "quantidade": quantidade,
    }


def buscar_por_id(lista: tuple, id_: int) -> dict | None:
    """Busca e retorna o produto com o ID fornecido, ou None (função pura)."""
    resultado = list(filter(lambda p: p["id"] == id_, lista))
    return resultado[0] if resultado else None


def buscar_por_nome(lista: tuple, termo: str) -> tuple:
    """Retorna uma tupla imutável com produtos cujo nome contém o termo (função pura)."""
    termo_lower = termo.lower()
    return tuple(filter(lambda p: termo_lower in p["nome"].lower(), lista))


def calcular_valor_total(lista: tuple) -> float:
    """Calcula o valor total do estoque usando reduce (função pura)."""
    if not lista:
        return 0.0
    return reduce(lambda acc, p: acc + p["preco"] * p["quantidade"], lista, 0.0)


def aplicar_desconto(lista: tuple, percentual: float) -> tuple:
    """Retorna nova tupla com desconto aplicado sobre os preços (MAP - função pura).

    percentual deve estar entre 0 e 100 (inclusive).
    """
    if not (0 <= percentual <= 100):
        raise ValueError(f"percentual deve ser entre 0 e 100, recebido: {percentual}")
    fator = 1 - percentual / 100
    return tuple(map(lambda p: {**p, "preco": round(p["preco"] * fator, 2)}, lista))


def filtrar_por_preco_maximo(lista: tuple, preco_max: float) -> tuple:
    """Retorna tupla com produtos abaixo ou igual ao preço máximo (FILTER - função pura)."""
    return tuple(filter(lambda p: p["preco"] <= preco_max, lista))


def atualizar_produto(lista: tuple, id_: int, novos_dados: dict) -> tuple:
    """Retorna nova tupla com o produto atualizado (função pura / imutável)."""
    return tuple(
        {**p, **novos_dados} if p["id"] == id_ else p
        for p in lista
    )


def remover_produto(lista: tuple, id_: int) -> tuple:
    """Retorna nova tupla sem o produto de ID fornecido (função pura)."""
    return tuple(filter(lambda p: p["id"] != id_, lista))


def formatar_produto(produto: dict) -> str:
    """Retorna string formatada para exibição de um produto (função pura)."""
    return (
        f"  ID: {produto['id']:>4} | "
        f"Nome: {produto['nome']:<30} | "
        f"Preço: R$ {produto['preco']:>10.2f} | "
        f"Qtd: {produto['quantidade']:>5}"
    )


# =============================================================================
# FUNÇÕES DE ESTADO (Paradigma Imperativo)
# Modificam as variáveis globais diretamente.
# =============================================================================

def adicionar_produto(nome: str, preco: float, quantidade: int) -> None:
    """Adiciona produto à lista global (manipulação direta de estado)."""
    global proximo_id
    novo = criar_produto(proximo_id, nome, preco, quantidade)  # função pura
    produtos.append(novo)     # mutação direta da lista global
    proximo_id += 1           # atualização do contador mutável
    print(f"\n✅ Produto '{nome}' cadastrado com ID {novo['id']}.")


def atualizar_produto_global(id_: int, novos_dados: dict) -> bool:
    """Substitui lista global pela versão atualizada (Imperativo + Funcional)."""
    global produtos
    if buscar_por_id(tuple(produtos), id_) is None:
        return False
    produtos = list(atualizar_produto(tuple(produtos), id_, novos_dados))  # função pura
    return True


def deletar_produto_global(id_: int) -> bool:
    """Remove produto da lista global (Imperativo + Funcional)."""
    global produtos
    if buscar_por_id(tuple(produtos), id_) is None:
        return False
    produtos = list(remover_produto(tuple(produtos), id_))  # função pura
    return True


# =============================================================================
# VALIDAÇÃO DE ENTRADA (Utilitários)
# =============================================================================

def ler_inteiro(prompt: str, minimo: int = None, maximo: int = None) -> int:
    """Lê e valida um inteiro do usuário usando estrutura de controle (while/if)."""
    while True:
        try:
            valor = int(input(prompt))
            if minimo is not None and valor < minimo:
                print(f"  ⚠️  Valor deve ser >= {minimo}.")
                continue
            if maximo is not None and valor > maximo:
                print(f"  ⚠️  Valor deve ser <= {maximo}.")
                continue
            return valor
        except ValueError:
            print("  ⚠️  Entrada inválida. Digite um número inteiro.")


def ler_float(prompt: str, minimo: float = None) -> float:
    """Lê e valida um número decimal do usuário."""
    while True:
        try:
            valor = float(input(prompt))
            if minimo is not None and valor < minimo:
                print(f"  ⚠️  Valor deve ser >= {minimo}.")
                continue
            return valor
        except ValueError:
            print("  ⚠️  Entrada inválida. Digite um número válido.")


def ler_texto(prompt: str, minimo_chars: int = 1) -> str:
    """Lê e valida uma string não vazia do usuário."""
    while True:
        valor = input(prompt).strip()
        if len(valor) >= minimo_chars:
            return valor
        print(f"  ⚠️  Digite ao menos {minimo_chars} caractere(s).")


# =============================================================================
# OPERAÇÕES DE MENU (Paradigma Imperativo - sequencial e estruturado)
# =============================================================================

def op_cadastrar() -> None:
    """Fluxo sequencial imperativo para cadastrar um produto."""
    print("\n─── Cadastrar Produto ───")
    nome = ler_texto("  Nome do produto: ")
    preco = ler_float("  Preço (R$): ", minimo=0.01)
    quantidade = ler_inteiro("  Quantidade em estoque: ", minimo=0)
    adicionar_produto(nome, preco, quantidade)


def op_listar() -> None:
    """Lista todos os produtos usando FOR (estrutura de controle imperativa)."""
    print("\n─── Lista de Produtos ───")
    if not produtos:
        print("  Nenhum produto cadastrado.")
        return

    # Cabeçalho
    print(f"  {'ID':>4}   {'Nome':<30}   {'Preço':>12}   {'Qtd':>5}")
    print("  " + "-" * 62)

    # FOR - estrutura de controle imperativa
    for p in produtos:
        print(formatar_produto(p))

    # REDUCE - paradigma funcional
    total = calcular_valor_total(tuple(produtos))
    print("  " + "-" * 62)
    print(f"  Total em estoque: R$ {total:.2f}  ({len(produtos)} produto(s))")


def op_pesquisar() -> None:
    """Pesquisa produtos por ID ou nome."""
    print("\n─── Pesquisar Produto ───")
    print("  1. Por ID")
    print("  2. Por nome")
    opcao = ler_inteiro("  Escolha: ", minimo=1, maximo=2)

    if opcao == 1:
        id_ = ler_inteiro("  ID do produto: ", minimo=1)
        resultado = buscar_por_id(tuple(produtos), id_)  # função pura + FILTER
        if resultado:
            print("\n  Produto encontrado:")
            print(formatar_produto(resultado))
        else:
            print(f"\n  ❌ Produto com ID {id_} não encontrado.")
    else:
        termo = ler_texto("  Nome (ou parte do nome): ")
        resultados = buscar_por_nome(tuple(produtos), termo)  # FILTER funcional
        if resultados:
            print(f"\n  {len(resultados)} produto(s) encontrado(s):")
            for p in resultados:
                print(formatar_produto(p))
        else:
            print(f"\n  ❌ Nenhum produto com '{termo}' no nome.")


def op_atualizar() -> None:
    """Atualiza campos de um produto existente."""
    print("\n─── Atualizar Produto ───")
    id_ = ler_inteiro("  ID do produto a atualizar: ", minimo=1)
    produto = buscar_por_id(tuple(produtos), id_)  # função pura

    if not produto:
        print(f"\n  ❌ Produto com ID {id_} não encontrado.")
        return

    print(f"\n  Produto atual: {formatar_produto(produto)}")
    print("  Deixe em branco para manter o valor atual.\n")

    novos_dados: dict = {}

    # IF - estrutura de controle imperativa para validar cada campo
    novo_nome = input(f"  Novo nome [{produto['nome']}]: ").strip()
    if novo_nome:
        novos_dados["nome"] = novo_nome

    novo_preco_str = input(f"  Novo preço [{produto['preco']:.2f}]: ").strip()
    if novo_preco_str:
        try:
            novo_preco = float(novo_preco_str)
            if novo_preco >= 0.01:
                novos_dados["preco"] = round(novo_preco, 2)
            else:
                print("  ⚠️  Preço inválido. Campo não atualizado.")
        except ValueError:
            print("  ⚠️  Preço inválido. Campo não atualizado.")

    nova_qtd_str = input(f"  Nova quantidade [{produto['quantidade']}]: ").strip()
    if nova_qtd_str:
        try:
            nova_qtd = int(nova_qtd_str)
            if nova_qtd >= 0:
                novos_dados["quantidade"] = nova_qtd
            else:
                print("  ⚠️  Quantidade inválida. Campo não atualizado.")
        except ValueError:
            print("  ⚠️  Quantidade inválida. Campo não atualizado.")

    if not novos_dados:
        print("\n  Nenhuma alteração realizada.")
        return

    atualizar_produto_global(id_, novos_dados)
    print(f"\n✅ Produto ID {id_} atualizado com sucesso.")


def op_deletar() -> None:
    """Deleta um produto após confirmação."""
    print("\n─── Deletar Produto ───")
    id_ = ler_inteiro("  ID do produto a deletar: ", minimo=1)
    produto = buscar_por_id(tuple(produtos), id_)  # função pura

    if not produto:
        print(f"\n  ❌ Produto com ID {id_} não encontrado.")
        return

    print(f"\n  Produto: {formatar_produto(produto)}")
    confirmacao = input("  Confirma exclusão? (s/N): ").strip().lower()

    if confirmacao == "s":
        deletar_produto_global(id_)
        print(f"\n✅ Produto ID {id_} deletado com sucesso.")
    else:
        print("\n  Operação cancelada.")


def op_demonstrar_funcional() -> None:
    """
    Demonstra MAP, FILTER e REDUCE sobre os produtos cadastrados.
    Paradigma completamente funcional — não modifica o estado global.
    """
    print("\n─── Demonstração Funcional (MAP / FILTER / REDUCE) ───")

    if not produtos:
        print("  Nenhum produto cadastrado. Cadastre produtos primeiro.")
        return

    snapshot: tuple = tuple(produtos)  # snapshot imutável

    # --- FILTER ---
    preco_max = ler_float("  FILTER — Preço máximo para filtrar (R$): ", minimo=0)
    filtrados = filtrar_por_preco_maximo(snapshot, preco_max)
    print(f"\n  FILTER — Produtos com preço ≤ R$ {preco_max:.2f}:")
    if filtrados:
        for p in filtrados:
            print(formatar_produto(p))
    else:
        print("  Nenhum produto nessa faixa de preço.")

    # --- MAP ---
    pct = ler_float("  MAP — Aplicar desconto de (%) sobre todos os produtos: ", minimo=0)
    com_desconto = aplicar_desconto(snapshot, pct)  # não modifica snapshot
    print(f"\n  MAP — Preços com {pct:.1f}% de desconto (visualização):")
    for p in com_desconto:
        print(formatar_produto(p))

    # --- REDUCE ---
    total_original = calcular_valor_total(snapshot)
    total_desconto = calcular_valor_total(com_desconto)
    print(f"\n  REDUCE — Valor total do estoque original: R$ {total_original:.2f}")
    print(f"  REDUCE — Valor total após desconto:       R$ {total_desconto:.2f}")
    print(f"  Economia total:                           R$ {total_original - total_desconto:.2f}")
    print("\n  ℹ️  Os dados originais NÃO foram modificados (imutabilidade funcional).")


# =============================================================================
# MENU PRINCIPAL (Paradigma Imperativo - WHILE + estrutura de controle)
# =============================================================================

OPCOES_MENU = {
    "1": ("Cadastrar produto",                  op_cadastrar),
    "2": ("Listar produtos",                    op_listar),
    "3": ("Pesquisar produto",                  op_pesquisar),
    "4": ("Atualizar produto",                  op_atualizar),
    "5": ("Deletar produto",                    op_deletar),
    "6": ("Demonstração funcional (MAP/FILTER/REDUCE)", op_demonstrar_funcional),
    "0": ("Sair",                               None),
}


def exibir_menu() -> None:
    """Exibe o menu interativo na saída padrão."""
    print("\n" + "=" * 50)
    print("  🛒  CADASTRO DE PRODUTOS  🛒")
    print("=" * 50)
    for chave, (descricao, _) in OPCOES_MENU.items():
        print(f"  [{chave}] {descricao}")
    print("=" * 50)


def main() -> None:
    """
    Loop principal do programa.
    WHILE — estrutura de controle imperativa que mantém o menu ativo.
    """
    print("\nBem-vindo ao Sistema de Cadastro de Produtos!")
    print("Paradigma Híbrido: Imperativo + Funcional\n")

    rodando = True   # variável mutável de controle de fluxo

    while rodando:   # WHILE - controle imperativo
        exibir_menu()
        escolha = input("  Opção: ").strip()

        if escolha in OPCOES_MENU:
            _, acao = OPCOES_MENU[escolha]
            if acao is None:            # IF - estrutura de controle imperativa
                print("\nEncerrando o sistema. Até logo!\n")
                rodando = False         # altera estado mutável para encerrar
            else:
                try:
                    acao()              # executa a operação escolhida
                except KeyboardInterrupt:
                    print("\n  Operação interrompida pelo usuário.")
        else:
            print("  ⚠️  Opção inválida. Tente novamente.")


if __name__ == "__main__":
    main()
