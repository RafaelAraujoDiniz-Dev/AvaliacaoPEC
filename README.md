# 📦 Sistema de Cadastro de Produtos - Paradigmas Imperativo vs Funcional

Um projeto educacional demonstrando como implementar o **mesmo sistema** usando dois paradigmas diferentes de programação em C.

## 🎯 Objetivo

Compreender as diferenças práticas entre programação **imperativa** e **funcional** através de um caso real.

---

## 📊 Comparação de Paradigmas

### **PARADIGMA IMPERATIVO**

**Características:**
- ✅ Variáveis mutáveis (modificam durante a execução)
- ✅ Estado global compartilhado
- ✅ Loops explícitos (for, while)
- ✅ Código sequencial e procedural
- ✅ Manipulação direta de dados

**Vantagens:**
- Fácil de entender para iniciantes
- Controle explícito do fluxo
- Performance natural para máquinas imperativas

**Exemplo:**
```c
// IMPERATIVO: Modifica estado diretamente
int total = 0;
for (int i = 0; i < n; i++) {
    total += produtos[i].preco;  // MUTA 'total'
}
```

### **PARADIGMA FUNCIONAL**

**Características:**
- ✅ Funções puras (mesmo input = mesmo output)
- ✅ Imutabilidade (não modifica dados originais)
- ✅ Funções de ordem superior (map, filter, reduce)
- ✅ Composição de funções
- ✅ Sem efeitos colaterais

**Vantagens:**
- Fácil de testar (funções puras)
- Melhor para concorrência
- Menos bugs relacionados a estado

**Exemplo:**
```c
// FUNCIONAL: Cria novo array sem modificar original
float reduzir_total(const Produto produtos[], int n) {
    float acumulador = 0.0;
    for (int i = 0; i < n; i++) {
        acumulador += produtos[i].preco;
    }
    return acumulador; // Retorna sem efeitos colaterais
}
```

---

## 📁 Arquivos do Projeto

```
.
├── produtos.h       # Estruturas compartilhadas
├── imperativo.c     # Implementação imperativa
├── funcional.c      # Implementação funcional
├── main.c           # Menu principal
└── README.md        # Este arquivo
```

### **produtos.h**
Estruturas básicas e constantes compartilhadas:
```c
typedef struct {
    char nome[100];
    float preco;
    int codigo;
} Produto;

#define MAX_PRODUTOS 100
```

### **imperativo.c**
- Variável global: `Cadastro cadastro_imperativo`
- Funções que modificam estado:
  - `adicionar_produto_imperativo()`
  - `deletar_produto_imperativo()`
  - `atualizar_preco_imperativo()`
  - `listar_produtos_imperativo()`
  - `calcular_total_imperativo()`
  - `menu_imperativo()`

### **funcional.c**
- Funções puras de ordem superior:
  - `filtrar_por_preco()` - FILTER
  - `mapear_preco()` - MAP
  - `reduzir_total()` - REDUCE
  - `listar_produtos_funcional()`
  - `menu_funcional()`

### **main.c**
Menu interativo que permite escolher entre os dois paradigmas.

---

## 🚀 Como Compilar e Executar

### **Linux/Mac:**
```bash
gcc -o cadastro imperativo.c funcional.c main.c
./cadastro
```

### **Windows (MinGW):**
```bash
gcc -o cadastro.exe imperativo.c funcional.c main.c
cadastro.exe
```

### **Com otimizações:**
```bash
gcc -O2 -o cadastro imperativo.c funcional.c main.c
./cadastro
```

---

## 💡 Exemplos Práticos

### **Imperativo: Adicionar e Modificar**
```c
// Estado global muda
adicionar_produto_imperativo(1, "Notebook", 2500.00);
cadastro_imperativo.total++; // Estado mutável
atualizar_preco_imperativo(1, 2300.00); // Modifica direto
```

### **Funcional: Filtrar e Mapear**
```c
// Cria novos arrays sem modificar original
Produto filtrados[MAX_PRODUTOS];
int count = filtrar_por_preco(filtrados, produtos, total, 100.00);

Produto com_desconto[MAX_PRODUTOS];
mapear_preco(com_desconto, produtos, total, 0.9); // -10%
```

---

## 📚 Conceitos Avançados

### **MAP (Mapeamento)**
Transforma cada elemento de um array:
```c
// Imperativo: Loop manual
for (int i = 0; i < n; i++) {
    resultado[i].preco *= 1.1; // +10%
}

// Funcional: Função pura
mapear_preco(resultado, produtos, n, 1.1);
```

### **FILTER (Filtragem)**
Seleciona elementos que atendem critério:
```c
// Imperativo: Condicional em loop
for (int i = 0; i < n; i++) {
    if (produtos[i].preco >= 100) {
        // processar
    }
}

// Funcional: Função pura
filtrar_por_preco(resultado, produtos, n, 100.0);
```

### **REDUCE (Redução)**
Agrega múltiplos valores em um:
```c
// Imperativo: Acumulador mutável
float total = 0;
for (int i = 0; i < n; i++) {
    total += produtos[i].preco; // MUTA
}

// Funcional: Função pura
float total = reduzir_total(produtos, n);
```

---

## 🔍 Análise Comparativa

| Aspecto | Imperativo | Funcional |
|---------|-----------|----------|
| **Mutação** | Sim (esperada) | Não (evitada) |
| **Estado Global** | Sim | Não |
| **Loops** | for, while explícitos | map, filter, reduce |
| **Efeitos Colaterais** | Esperados | Evitados |
| **Testeabilidade** | Difícil (estado) | Fácil (puro) |
| **Performance** | Rápida | Pode ser mais lenta |
| **Concorrência** | Difícil (locks) | Segura (imutável) |
| **Curva de Aprendizado** | Suave | Íngreme |

---

## 🎓 O que Aprender

Este projeto demonstra:

1. **Como mesmo problema pode ser resolvido de formas diferentes**
2. **Vantagens e desvantagens de cada paradigma**
3. **Quando usar imperativo vs funcional**
4. **Conceitos essenciais (MAP, FILTER, REDUCE)**
5. **Como estruturar código C de forma profissional**

---

## 📝 Exercícios Propostos

1. **Adicione ordenação funcional** - Crie uma função `ordenar_por_preco()` sem modificar original
2. **Implemente FIND** - Busque o produto mais caro usando abordagem funcional
3. **Combine operações** - Filtre por preço E aplique desconto em sequência
4. **Persistência** - Salve dados em arquivo (imperativo) vs serialização funcional
5. **Performance** - Compare velocidade entre os dois paradigmas

---

## 🤝 Contribuições

Este é um projeto educacional. Sinta-se à vontade para:
- Adicionar mais funcionalidades
- Implementar novos exemplos
- Sugerir melhorias
- Criar versões em outras linguagens

---

## 📖 Referências

- **Programação Imperativa**: Kernighan & Ritchie - "The C Programming Language"
- **Programação Funcional**: Structure and Interpretation of Computer Programs (SICP)
- **MAP/FILTER/REDUCE**: Lisp, Scheme, Haskell, Python

---

## ⚖️ Licença

MIT License - Sinta-se livre para usar em projetos educacionais!

---

**Criado com ❤️ para fins educacionais**