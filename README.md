# Documentação de Lógica — Sprint 1: Simulador de Recarga Eletrocharge

**Autor:** Lucas Barreto Santana

**Curso:** Ciências da Computação 

**Instituição:** FIAP

---
## 1. Objetivo do Programa

O programa tem como objetivo simular o fluxo completo de uma sessão de recarga para veículos elétricos em linguagem da **Goodwe linha HCA G2**  em **C**. Ele realiza a coleta e validação de dados do usuário, simula o tempo de carregamento minuto a minuto acumulando energia (kWh), calcula os custos baseados em regras tarifárias dinâmicas (horário e perfil do cliente) e exibe um relatório final formatado.

---
## 2. Arquitetura e Organização do Código

Para manter a simplicidade e focar nos fundamentos da linguagem C, o código foi construído de forma procedural e sequencial dentro da função `main()`, utilizando apenas a biblioteca padrão `<stdio.h>`.
A separação lógica ocorre em quatro blocos principais:

1. **Entrada e Validação de Dados:** Captura de credenciais e parâmetros da sessão.
    
2. **Processamento e Simulação (O Ciclo de Recarga):** Laço de repetição que injeta energia e calcula o custo dinâmico com base no relógio.
    
3. **Fechamento Financeiro:** Aplicação de descontos e totalização.
    
4. **Saída de Dados:** Renderização do relatório final.
---
## 3. Lógica de Implementação por Critério de Avaliação

### 3.1. Estruturas Condicionais (`switch` e `if/else`)

As decisões lógicas do sistema foram divididas de acordo com a finalidade:

- **Menu de Perfis (`switch-case`):** Utilizado logo após a validação da entrada para direcionar o fluxo visual de acordo com o tipo de usuário escolhido (`1` para Padrão, `2` para Premium).
    
- **Decisão de Tarifação (`if / else if / else`):** Implementada dentro da simulação para classificar o custo da energia com base no horário atual da recarga. A lógica divide o dia em três faixas:
    
    - **Horário de Pico (18h às 21h59):** Tarifa de R$ 1,20/kWh.
        
    - **Horário Noturno (22h às 05h59):** Tarifa reduzida de R$ 0,45/kWh.
        
    - **Horário Padrão (Demais horários):** Tarifa base de R$ 0,75/kWh.
        

### 3.2. Estruturas de Repetição (`while` e `for`)

O controle de fluxo garante que o programa seja imune a entradas incorretas e simule o tempo com exatidão:

- **Validação de Entrada (`while`):** Utiliza-se um laço `while` para cada parâmetro crítico (tipo de usuário, hora de início e duração). Se o usuário digitar um valor fora do intervalo permitido (por exemplo, uma hora como `25` ou uma duração negativa), a condição se torna verdadeira e o programa prende a execução, solicitando a redigitação até que o critério seja satisfeito.
    
- **Simulação do Tempo (`for`):** O laço `for` itera de `1` até a `duracao_min` estipulada.
    
    - _Analogia de funcionamento:_ O laço funciona como um taxímetro ou hidrômetro. A cada volta (representando 1 minuto), o programa verifica a hora correspondente, injeta uma taxa constante de `0.10 kWh` no "tanque" (variável `energia_kwh`) e soma o custo fracionado à variável `custo_bruto` com base na tarifa daquele minuto exato.
        

### 3.3. Tratamento do Relógio (Avanço do Tempo)

Para garantir que recargas longas atravessem a meia-noite corretamente sem gerar "horas impossíveis" (como 25h ou 26h), o cálculo da hora atual no laço utiliza a operação de módulo (`% 24`):

C

```
hora_atual = (hora_inicio + (minuto - 1) / 60) % 24;
```

Isso garante que, ao atingir 24, o relógio reinicie automaticamente em 0 (meia-noite), aplicando a tarifa correta da madrugada.

### 3.4. Cálculo Financeiro e Regras de Negócio

Após a simulação minuto a minuto, o sistema verifica a elegibilidade para benefícios:

- Se o perfil for **Premium** (opção 2), aplica-se um desconto direto de 15% sobre o `custo_bruto`.
    
- Calcula-se o `custo_final` subtraindo o desconto do valor bruto.
    
- O sistema avalia o montante final e emite uma recomendação inteligente no rodapé (Sessão econômica, Concluída com sucesso ou Sessão longa/custosa).
    

---

## 4. Interface e Experiência de Uso (Entrada/Saída)

A interface no terminal foi projetada para emular o visor de um totem de recarga real:

- **Entrada limpa:** O nome do usuário é lido permitindo espaços através do formatador `scanf(" %[^\n]", nome)`.
    
- **Saída formatada:** O relatório final alinha os dados à esquerda e os valores numéricos à direita, utilizando precisão decimal de duas casas para moeda (`%.2f`) e três casas para energia (`%.3f kWh`), garantindo clareza absoluta na prestação de contas.