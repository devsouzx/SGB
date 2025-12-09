#include <stdio.h>
#include <string.h>
#include <time.h>

#define MAX_USUARIOS 1000
#define MAX_LIVROS 5000
#define MAX_EXEMPLARES 10000
#define MAX_EMPRESTIMOS 5000
#define MAX_RESERVAS 2000

#define USUARIO_TESTE { \
    0, \
    "Usuario Teste\n", \
    "00000000000\n", \
    "teste@exemplo.com\n", \
    "11999999999\n", \
    "Rua Exemplo, 123\n", \
    "Aluno\n", \
    "20250001\n", \
    1, \
    4, \
    0, \
    "01/01/2025", \
    0.0 \
}

// Livro de teste
#define LIVRO_TESTE { \
    0, \
    9781234567890LL, \
    "Livro Teste\n", \
    "Autor Desconhecido\n", \
    "Editora Teste\n", \
    "Sao Paulo\n", \
    2025, \
    1, \
    "200 p.\n", \
    "Serie Teste\n", \
    "Nenhuma nota\n", \
    "Assunto Teste\n", \
    "CDD 123\n", \
    "Portugues\n", \
    "Impresso\n", \
    1, \
    1, \
    "01/01/2025" \
}

// Exemplar de teste
#define EXEMPLAR_TESTE { \
    0, \
    0, \
    "CHAM-001\n", \
    "Estante A1\n", \
    "Vol. 1\n", \
    "Fisico\n", \
    1, \
    -1, \
    "", \
    "", \
    "Biblioteca Central\n" \
}

// Emprestimo de teste
#define EMPRESTIMO_TESTE { \
    0, \
    0, \
    0, \
    "01/01/2025", \
    "10/01/2025", \
    "", \
    0, \
    1, \
    0.0 \
}

// Reserva de teste
#define RESERVA_TESTE { \
    0, \
    0, \
    0, \
    "01/01/2025", \
    "05/01/2025", \
    1, \
    1 \
}

typedef struct {
    int id;
    char nome[100];
    char cpf[15];
    char email[100];
    char telefone[20];
    char endereco[200];
    char tipoUsuario[30];
    char matricula[20];
    int status;
    int limiteEmprestimos;
    int emprestimosAtivos;
    char dataCadastro[11];
    float multaPendente;
} Usuario;

typedef struct exemplar {
    int id;
    int livroId;
    char numeroChamada[50];
    char localizacao[100];
    char volume[30];
    char suporte[20]; 
    int status;
    int usuarioId;
    char dataEmprestimo[11];
    char dataDevolucao[11];
    char biblioteca[100];
} Exemplar;

typedef struct livro {
    int id;
    long long isbn;
    char titulo[200];
    char autor[100];
    char editora[100];
    char localPublicacao[100];
    int anoPublicacao;
    int edicao;
    char descricaoFisica[100];
    char serie[100];
    char notas[500];
    char assunto[300];
    char classificacao[50];
    char idioma[30];
    char tipoMaterial[50];
    int totalExemplares;
    int disponiveis;
    char dataCadastro[11];
} Livro;

typedef struct {
    int id;
    int usuarioId;
    int exemplarId;
    char dataEmprestimo[11];
    char dataDevolucaoPrevista[11];
    char dataDevolucaoReal[11];
    int renovacoes;
    int status;
    float multa;
} Emprestimo;

typedef struct {
    int id;
    int usuarioId;
    int livroId;
    char dataReserva[11];
    char dataExpiracao[11];
    int prioridade;
    int status;
} Reserva;

typedef struct {
    Usuario usuarios[MAX_USUARIOS];
    int total;
} ListaUsuarios;

typedef struct {
    Livro livros[MAX_LIVROS];
    int total;
} Catalogo;

typedef struct {
    Exemplar exemplares[MAX_EXEMPLARES];
    int total;
} ListaExemplares;

typedef struct {
    Emprestimo emprestimos[MAX_EMPRESTIMOS];
    int total;
} HistoricoEmprestimos;

typedef struct {
    Reserva reservas[MAX_RESERVAS];
    int total;
} ListaReservas;

// iniciar variaveis globais
ListaUsuarios usuarios = {0};
Catalogo catalogo = {0};
ListaExemplares exemplares = {0};
HistoricoEmprestimos historico = {0};
ListaReservas reservas = {0};

void dataAtual(char *data) {
    time_t t = time(NULL);           // 1. Pegar tempo atual do sistema
    struct tm tm = *localtime(&t);   // 2. Converter para struct
    // 3. Formatar DD/MM/AAAA
    sprintf(data, "%02d/%02d/%04d", tm.tm_mday, tm.tm_mon + 1, tm.tm_year + 1900);
}

void cadastrarUsuario() {
    if (usuarios.total >= MAX_USUARIOS) {
        printf("Limite de usuarios atingido!\n");
        return;
    }

    Usuario novoUsuario;
    novoUsuario.id = usuarios.total;
    novoUsuario.status = 1;
    novoUsuario.emprestimosAtivos = 0;
    novoUsuario.multaPendente = 0.0;
    dataAtual(novoUsuario.dataCadastro);

    printf("\n=== CADASTRO DE USUARIO ===\n");
    
    printf("Nome: ");
    fgets(novoUsuario.nome, 100, stdin);

    printf("Matricula: ");
    fgets(novoUsuario.matricula, 20, stdin);

    printf("CPF: ");
    fgets(novoUsuario.cpf, 15, stdin);
    
    printf("Email: ");
    fgets(novoUsuario.email, 100, stdin);
    
    printf("Telefone: ");
    fgets(novoUsuario.telefone, 20, stdin);
    
    printf("Tipo (Aluno/Professor/Funcionario): ");
    fgets(novoUsuario.tipoUsuario, 30, stdin);

    if (strcasecmp(novoUsuario.tipoUsuario, "Professor") == 0) {
        novoUsuario.limiteEmprestimos = 10;
    } else if (strcasecmp(novoUsuario.tipoUsuario, "Funcionario") == 0) {
        novoUsuario.limiteEmprestimos = 8;
    } else {
        novoUsuario.limiteEmprestimos = 4;
    }

    usuarios.usuarios[usuarios.total] = novoUsuario;
    usuarios.total++;

    printf("\nUsuario cadastrado com sucesso! ID: %d\n", novoUsuario.id);
}

void listarUsuarios() {
    printf("\n=== LISTA DE USUARIOS (%d) ===\n", usuarios.total);
    for (int i = 0; i < usuarios.total; i++) {
        Usuario u = usuarios.usuarios[i];
        printf("ID: %d | Matricula: %s | Nome: %s | Tipo: %s | Emprestimos: %d/%d\n",
               u.id, u.matricula, u.nome, u.tipoUsuario, u.emprestimosAtivos, u.limiteEmprestimos);
    }
}

int buscarUsuarioPorCPF(char *cpf) {
    for (int i = 0; i < usuarios.total; i++) {
        if (strcmp(usuarios.usuarios[i].cpf, cpf) == 0) {
            return i;
        }
    }
    return -1;
}

int buscarLivro(char *titulo) {
    char busca[200];
    strcpy(busca, titulo);

    // remover \n do fgets
    busca[strcspn(busca, "\n")] = '\0';

    for (int i = 0; i < catalogo.total; i++) {
        char tituloLivro[200];
        strcpy(tituloLivro, catalogo.livros[i].titulo);
        tituloLivro[strcspn(tituloLivro, "\n")] = '\0';

        if (strcasecmp(tituloLivro, busca) == 0) {
            return i;
        }
    }
    return -1;
}


void emprestarLivro() {
    printf("=== INSIRA O CPF DO USUARIO ===\n");
    char cpf[15];
    fgets(cpf, 15, stdin);

    int userIndex = buscarUsuarioPorCPF(cpf);
    if (userIndex == -1) {
        printf("Usuario nao encontrado!\n");
        return;
    }

    Usuario *usuario = &usuarios.usuarios[userIndex];

    if (usuario->emprestimosAtivos >= usuario->limiteEmprestimos) {
        printf("Limite de emprestimos atingido para este usuario!\n");
        return;
    }

    printf("Usuario %s pode pegar emprestado mais livros.\n", usuario->nome);
    printf("Qual livro deseja pegar emprestado?\n");

    char titulo[200];
    fgets(titulo, 200, stdin);

    int livroIndex = buscarLivro(titulo);
    if (livroIndex == -1) {
        printf("Livro nao encontrado!\n");
        return;
    }

    Livro *livro = &catalogo.livros[livroIndex];

    if (livro->disponiveis <= 0) {
        printf("Nenhum exemplar disponivel para este livro!\n");
        return;
    }

    int exemplarIndex = -1;
    for (int i = 0; i < exemplares.total; i++) {
        if (exemplares.exemplares[i].livroId == livro->id &&
            exemplares.exemplares[i].status == 1) {
            exemplarIndex = i;
            break;
        }
    }

    if (exemplarIndex == -1) {
        printf("Nenhum exemplar disponivel.\n");
        return;
    }

    Exemplar *ex = &exemplares.exemplares[exemplarIndex];

    if (historico.total >= MAX_EMPRESTIMOS) {
        printf("Limite de historico atingido!\n");
        return;
    }

    Emprestimo novo;

    // ID correto: igual à posição no vetor
    novo.id = historico.total;

    novo.usuarioId = usuario->id;
    novo.exemplarId = ex->id;

    dataAtual(novo.dataEmprestimo);

    // calcular devolução prevista (7 dias)
    time_t t = time(NULL);
    t += 7 * 24 * 3600;
    struct tm tm = *localtime(&t);
    sprintf(novo.dataDevolucaoPrevista, "%02d/%02d/%04d",
            tm.tm_mday, tm.tm_mon + 1, tm.tm_year + 1900);

    strcpy(novo.dataDevolucaoReal, "");
    novo.renovacoes = 0;
    novo.status = 1;
    novo.multa = 0.0;

    // SALVAR O EMPRÉSTIMO NO HISTÓRICO NA POSIÇÃO CERTA
    historico.emprestimos[historico.total] = novo;

    // AGORA SIM, INCREMENTA
    historico.total++;

    // ATUALIZAÇÕES
    ex->status = 0;
    ex->usuarioId = usuario->id;
    strcpy(ex->dataEmprestimo, novo.dataEmprestimo);
    strcpy(ex->dataDevolucao, novo.dataDevolucaoPrevista);

    usuario->emprestimosAtivos++;
    livro->disponiveis--;

    printf("\n=== EMPRESTIMO REGISTRADO COM SUCESSO ===\n");
    printf("ID DO EMPRESTIMO: %d\n", novo.id);
    printf("Usuario: %s", usuario->nome);
    printf("Livro: %s", livro->titulo);
    printf("Exemplar: %s\n", ex->numeroChamada);
    printf("Data Emprestimo: %s\n", novo.dataEmprestimo);
    printf("Devolucao Prevista: %s\n", novo.dataDevolucaoPrevista);
}



void devolverLivro() {
    printf("ESPECIFIQUE O ID DO EMPRESTIMO A SER DEVOLVIDO: ");
    int emprestimoId;
    scanf("%d", &emprestimoId);
    getchar();

    // Verificar se o ID é válido
    if (emprestimoId < 0 || emprestimoId >= historico.total) {
        printf("Emprestimo nao encontrado!\n");
        return;
    }

    Emprestimo *emp = &historico.emprestimos[emprestimoId];

    // Já devolvido?
    if (emp->status != 1) {
        printf("Este emprestimo ja foi devolvido!\n");
        return;
    }

    // Recuperar dados associados
    Usuario *usuario = &usuarios.usuarios[emp->usuarioId];
    Exemplar *ex = &exemplares.exemplares[emp->exemplarId];
    Livro *livro = &catalogo.livros[ex->livroId];

    // Registrar data de devolução real
    dataAtual(emp->dataDevolucaoReal);

    // Atualizar empréstimo
    emp->status = 0;  // concluído

    // Liberar exemplar
    ex->status = 1;  // disponível
    ex->usuarioId = -1;
    strcpy(ex->dataEmprestimo, "");
    strcpy(ex->dataDevolucao, "");

    // Atualizar usuário
    if (usuario->emprestimosAtivos > 0)
        usuario->emprestimosAtivos--;

    // Atualizar livro
    livro->disponiveis++;

    printf("\n=== DEVOLUCAO CONCLUIDA ===\n");
    printf("Emprestimo ID: %d\n", emp->id);
    printf("Livro: %s", livro->titulo);
    printf("Exemplar: %s\n", ex->numeroChamada);
    printf("Usuario: %s", usuario->nome);
    printf("Data da devolucao: %s\n", emp->dataDevolucaoReal);
}


void renovarLivro() {
    // implementar renovação do livro
}

void reservarLivro() {
    // implementar reserva de livro
}

void exibirCatalogo(Catalogo catalogo) {
     // exibir catalogo
}

void ExibirLivro(int index) {
    Livro l = catalogo.livros[index];

    printf(
        "ID: %d\n"
        "ISBN: %lld\n"
        "Título: %s\n"
        "Autor: %s\n"
        "Editora: %s\n"
        "Local de Publicação: %s\n"
        "Ano de Publicação: %d\n"
        "Edição: %d\n"
        "Descrição Física: %s\n"
        "Série: %s\n"
        "Notas: %s\n"
        "Assunto: %s\n"
        "Classificação: %s\n"
        "Idioma: %s\n"
        "Tipo do Material: %s\n"
        "Total de Exemplares: %d\n"
        "Disponíveis: %d\n"
        "Data de Cadastro: %s\n",
        l.id, l.isbn, l.titulo, l.autor, l.editora, l.localPublicacao,
        l.anoPublicacao, l.edicao, l.descricaoFisica, l.serie, l.notas,
        l.assunto, l.classificacao, l.idioma, l.tipoMaterial,
        l.totalExemplares, l.disponiveis, l.dataCadastro
    );
}


int main() {
    usuarios.total = 0;
    catalogo.total = 0;
    exemplares.total = 0;
    historico.total = 0;
    reservas.total = 0;

    usuarios.usuarios[usuarios.total++] = (Usuario) USUARIO_TESTE;
    catalogo.livros[catalogo.total++]    = (Livro)   LIVRO_TESTE;
    exemplares.exemplares[exemplares.total++] = (Exemplar) EXEMPLAR_TESTE;
    historico.emprestimos[historico.total++] = (Emprestimo) EMPRESTIMO_TESTE;
    reservas.reservas[reservas.total++] = (Reserva) RESERVA_TESTE;

    printf("=============================================\n");
    printf("SISTEMA DE BIBLIOTECA\n");
    printf("=============================================\n");

    int opcao = -1;
    while(opcao!=11) {
        printf("===================== MENU =====================\n");
        printf("1 - Exibir Catalogo\n");
        printf("2 - Adicionar Livro\n");
        printf("3 - Cadastrar Usuario\n");
        printf("4 - Realizar Emprestimo\n");
        printf("5 - Devolver Livro\n");
        printf("6 - Renovar Livro\n");
        printf("7 - Buscar Livro\n");
        printf("9 - Listar Usuarios\n");
        printf("10 - Buscar Usuario por CPF\n");
        printf("11 - Sair\n");
        printf("Entre opcao: ");
        scanf("%d", &opcao);
        getchar();

        switch (opcao) {
            case 3: {
                cadastrarUsuario();
                break;
            }
            case 4:{
                emprestarLivro();
                break;
            }
            case 5:{
                devolverLivro();
                break;
            }
            case 7:{
                char titulo[200];
                printf("Titulo do Livro: ");
                fgets(titulo, 200, stdin);
                int livroIndex = buscarLivro(titulo);
                if (livroIndex != -1) {
                    ExibirLivro(livroIndex);
                } else {
                    printf("Livro nao encontrado!\n");
                }
                break;
            }
            case 9:{
                listarUsuarios();
                break;
            }
            case 10:{
                char cpf[15];
                printf("CPF: ");
                fgets(cpf, 15, stdin);
                int index = buscarUsuarioPorCPF(cpf);
                if (index != -1) {
                    Usuario u = usuarios.usuarios[index];
                    printf("\nUsuario encontrado:\n");
                    printf("Nome: %s\n", u.nome);
                    printf("Matricula: %s\n", u.matricula);
                    printf("Email: %s\n", u.email);
                } else {
                    printf("Usuario nao encontrado!\n");
                }
                break;
            }
        }
    }
}