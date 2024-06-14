# DS123
Trabalho final da disciplia DS123 da UFPR em 2024

# Documentação Técnica: Simulador de Prova para Concursos em C

## Introdução

Este documento descreve o simulador de prova para concursos desenvolvido em linguagem C, que roda em terminal. O software permite aos usuários realizar uma simulação de prova com questões aleatórias selecionadas a partir de um banco de dados de questões.

## Visão Geral do Sistema

### Descrição Geral

O simulador de prova para concursos é um programa de linha de comando que oferece a experiência de resolver questões simuladas de diferentes temas. Após a conclusão da prova, o programa exibe um ranking com base no número de acertos e no tempo de resolução.

### Arquitetura Geral

O sistema é estruturado de forma modular, com componentes para interação com o usuário, manipulação de questões, cálculo de pontuação e geração de ranking.

## Requisitos do Sistema

### Requisitos Funcionais

- Iniciar uma nova prova.
- Selecionar e apresentar questões aleatórias de diferentes temas.
- Permitir ao usuário responder as questões e verificar a correção.
- Armazenar o nome do usuário, pontuação e tempo de resolução para um ranking.
- Exibir ranking ordenado por número de acertos e tempo de resolução.
- Opções de ajuda e funcionalidades adicionais.

### Requisitos Não Funcionais

- O programa deve ser executado em um ambiente de terminal.
- Deve suportar até 2 horas de duração máxima da prova.
- Manipular corretamente arquivos de texto para banco de questões.
- Deve ser intuitivo e fácil de usar.

## Tecnologias Utilizadas

- **Linguagem de Programação:** C
- **Ambiente de Desenvolvimento:** GCC (GNU Compiler Collection), Visual Studio Code.
- **Bibliotecas Utilizadas:** stdio.h, stdlib.h

## Arquitetura do Software

### Diagrama de Componentes

![Diagrama de Componentes](link-para-imagem/diagrama-componentes.png)

### Descrição dos Componentes

- **UI (Interface com o Usuário):** Responsável por interagir com o usuário através do terminal.
- **Gerenciador de Questões:** Manipula o banco de questões, selecionando aleatoriamente as questões para a prova.
- **Controlador de Prova:** Gerencia o fluxo da prova, coletando respostas do usuário, calculando pontuação e tempo.
- **Sistema de Ranking:** Armazena e ordena os resultados dos usuários.

## Implementação

### Organização do Código


### Boas Práticas de Programação

O código segue boas práticas de programação, incluindo:

- Uso de nomes significativos para variáveis e funções.
- Comentários explicativos para facilitar a compreensão do código.
- Estrutura modular para facilitar a manutenção e extensão.

### Principais Algoritmos e Estruturas de Dados

- **Seleção Aleatória de Questões:** Utiliza funções de geração de números aleatórios para selecionar questões do banco de dados.
- **Cálculo de Pontuação:** Calcula a pontuação com base nas respostas corretas e tempo de resolução.

## Testes

### Testes Unitários

Foram desenvolvidos testes unitários para verificar a correta implementação das funcionalidades principais do sistema, como seleção de questões, cálculo de pontuação e ordenação do ranking.

### Testes de Integração e Sistema

Os módulos foram integrados e testados em conjunto para garantir o funcionamento correto do sistema como um todo, incluindo fluxos de usuário e manipulação de arquivos.

## Manual do Usuário

### Instalação

1. Clone o repositório do projeto: `git clone https://github.com/seu-usuario/simulador-prova-concursos.git`
2. Compile o código-fonte: `gcc -o simulador src/main.c src/ui.c src/questoes.c src/prova.c src/ranking.c src/util.c`

### Guia de Uso

1. **Menu Inicial:** Ao iniciar o programa, será apresentado um menu com opções para iniciar a prova, ver ranking e ajuda.
2. **Iniciar Prova:** Opção para iniciar uma nova prova com questões aleatórias.
3. **Responder Questões:** Digite 'C' ou 'F' para responder cada questão.
4. **Ver Ranking:** Opção para visualizar o ranking dos usuários.

### Solução de Problemas

- **Ajuda:** Para mais informações e suporte, consulte a seção de ajuda no menu do programa.
- **Suporte Técnico:** Entre em contato pelo email suporte@exemplo.com para assistência técnica.

## Conclusão

O simulador de prova para concursos em C oferece uma solução eficiente para simular provas de diferentes temas, com funcionalidades robustas e de fácil utilização. Para futuras extensões, considerar adicionar novos temas e funcionalidades avançadas.

---

Esse é um esboço básico que você pode expandir conforme o desenvolvimento e os requisitos específicos do seu projeto. Certifique-se de incluir exemplos de código, imagens e outras informações relevantes conforme necessário.


