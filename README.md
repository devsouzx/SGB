# SGB - Sistema de Gerenciamento de Biblioteca

Sistema desenvolvido em linguagem C para gestão de uma biblioteca universitária, com foco em cadastro de usuários, catálogo de livros, controle de empréstimos, reservas e renovação de materiais.

## Visão geral

O projeto foi desenvolvido como atividade acadêmica da disciplina de Algoritmos e Estruturas de Dados e permite:

- cadastrar usuários com diferentes perfis (aluno, professor e funcionário);
- registrar livros e exemplares;
- consultar o catálogo de obras;
- realizar empréstimos de exemplares;
- controlar devoluções e renovações;
- gerenciar reservas de livros;
- buscar usuários por CPF e consultar empréstimos/reservas;
- manter limites de empréstimos conforme o tipo de usuário.

## Tecnologias

- Linguagem: C
- Compilador: GCC / MinGW (Windows)
- Ambiente: console

## Estrutura do projeto

- `MAIN.C` — código-fonte principal do sistema
- `MAIN.exe` — executável gerado para Windows
- `Projeto AED1.pdf` — material complementar do projeto
- `SGB.zip` — arquivo compactado com o projeto

## Como executar

### Opção 1: usar o executável já compilado

Basta abrir o arquivo `MAIN.exe` no Windows.

### Opção 2: compilar o código-fonte

No terminal, execute:

```bash
gcc MAIN.C -o SGB.exe
./SGB.exe
```

Ou, no ambiente Windows com MinGW:

```bash
gcc MAIN.C -o SGB.exe
SGB.exe
```

## Funcionalidades principais

### 1. Cadastro de usuários
- Nome
- Matrícula
- CPF
- E-mail
- Telefone
- Tipo de usuário
- Limite de empréstimos

### 2. Cadastro de livros e exemplares
- ISBN
- Título
- Autor
- Editora
- Ano de publicação
- Editora e detalhes físicos
- Quantidade de exemplares
- Localização e suporte do material

### 3. Empréstimos
- Registro do empréstimo com data e previsão de devolução
- Validação de disponibilidade
- Controle de quantidade de empréstimos ativos por usuário
- Cálculo de multa pendente, quando aplicável

### 4. Devolução e renovação
- Registro da data real de devolução
- Renovação de prazo para empréstimos ativos
- Atualização do limite de disponibilidade do exemplar

### 5. Reservas
- Solicitação de reserva de livro
- Priorização e controle de status
- Atendimento automático de reservas quando um exemplar voltar ao acervo

### 6. Busca e consulta
- Busca de livros por título
- Busca de usuários por CPF
- Visualização de empréstimos e reservas de um usuário
- Listagem de usuários e catálogo

## Menu principal

Ao iniciar o programa, o usuário acessa o menu com as opções:

1. Exibir Catálogo
2. Adicionar Livro
3. Cadastrar Usuário
4. Realizar Empréstimo
5. Devolver Livro
6. Renovar Livro
7. Buscar Livro
8. Buscar Empréstimos e Reservas
9. Listar Usuários
10. Buscar Usuário por CPF
11. Sair

## Autores

- Henrique da Rocha Lima
- João Emanuel Marinho Sousa
- Lucas Barreto Dias
- Thalma Gabriel Marques Coimbra
- Thyago Divino Souza Siriano
