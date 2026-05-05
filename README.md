# Sistema de Cadastro de Produtos em C

## Descrição do Projeto

Este projeto consiste em um **sistema de cadastro de produtos** desenvolvido na linguagem **C**, com execução direta no **terminal**. O sistema realiza operações básicas de CRUD (Create, Read e Delete) e tem como objetivo aplicar e comparar dois paradigmas de programação: **imperativo** e **funcional**.

---

## Funcionalidades

- Cadastrar produtos
- Listar produtos cadastrados
- Buscar produtos por ID
- Buscar produtos por nome
- Deletar produtos
- Aplicar desconto utilizando MAP
- Filtrar produtos utilizando FILTER
- Calcular o valor total do estoque utilizando REDUCE

Cada produto possui ID, nome, preço e quantidade.

---

## Estrutura de Dados

```c
typedef struct {
    int id;
    char nome[50];
    float preco;
    int quantidade;
} Produto;
```

---

## Paradigmas de Programação Utilizados

### Paradigma Imperativo

O paradigma imperativo é aplicado nas partes do sistema responsáveis pelo controle do fluxo e manipulação direta do estado. Ele é caracterizado por:

- Declaração de variáveis mutáveis
- Execução passo a passo das instruções
- Uso de estruturas de controle (`if`, `for`, `while`)
- Manipulação direta do vetor de produtos
- Controle explícito da quantidade de produtos cadastrados

Exemplos desse paradigma aparecem nas operações de cadastro, listagem, busca por ID, deleção e no controle do menu principal.

---

### Paradigma Funcional

O paradigma funcional é aplicado sempre que possível, buscando minimizar efeitos colaterais e tornar o código mais previsível. Ele aparece no projeto por meio de:

- Uso de funções matemáticas puras
- Uso de `const` para reduzir mutabilidade
- Separação clara entre dados e operações
- Implementação de funções inspiradas em `map`, `filter` e `reduce`

Essas funções transformam ou processam os dados sem alterar diretamente o estado original do sistema.

---

## Diferenças Percebidas entre os Paradigmas

O paradigma imperativo precisa declarar variáveis, seguir passo a passo para montar o cadastro de produtos e fazer atribuições para conseguir contar e controlar os produtos.

Já no paradigma funcional, a abordagem utiliza funções matemáticas puras para realizar os cálculos e o processamento dos dados.

---

## Vantagens e Desvantagens

### Paradigma Imperativo

**Vantagens**:
- Fácil de entender no início
- Maior controle de estados

**Desvantagens**:
- Mais propenso a erros
- Menor reutilização de código

### Paradigma Funcional

**Vantagens**:
- Menos bugs
- Código mais limpo e conciso
- Melhor organização
- Facilita testes e manutenção

---

## Abordagem Mais Fácil

A abordagem mais fácil foi a do paradigma imperativo, pois é mais comumente utilizado e segue uma lógica sequencial clara.

---

## Legibilidade e Manutenção do Código

No paradigma imperativo, a legibilidade é boa em códigos pequenos, mas se deteriora em sistemas maiores devido ao excesso de mudanças de estado, dificultando a manutenção e aumentando a chance de bugs.

No paradigma funcional, embora seja menos intuitivo no início, a legibilidade tende a ser melhor em projetos maiores, pois utiliza funções puras, reduz efeitos colaterais e torna o código mais previsível e seguro para mudanças.

---

## Conceitos Aplicados no Projeto

### Paradigma Imperativo
- Variáveis mutáveis
- Estruturas de controle (`if`, `for`, `while`)
- Código estruturado e sequencial
- Manipulação direta de estado

### Paradigma Funcional
- Funções puras quando possível
- Imutabilidade parcial com `const`
- Funções de ordem superior (`map`, `filter`, `reduce`)
- Separação entre dados e operações
- Redução de efeitos colaterais

---

## Como Compilar

```bash
gcc cadastro_produtos.c -o cadastro_produtos
```

---

## Como Executar

```bash
./cadastro_produtos
```

---

## Organização do Projeto

```
├── cadastro_produtos.c
└── README.md
```

---

## Conclusão

O projeto permitiu comparar na prática os paradigmas imperativo e funcional. O imperativo mostrou-se mais simples e direto, enquanto o funcional contribuiu para um código mais organizado, confiável e de fácil manutenção. A combinação de ambos demonstrou ser eficiente para o sistema proposto.

---

## Autor

Rafael Araujo Diniz
RAYNARA RIBEIRO ALVES
