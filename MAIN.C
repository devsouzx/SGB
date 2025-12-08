#include <stdio.h>
#include <strings.h>
#include <time.h>

#define MAX_USUARIOS 1000
#define MAX_LIVROS 5000
#define MAX_EXEMPLARES 10000
#define MAX_EMPRESTIMOS 5000
#define MAX_RESERVAS 2000

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
    fgets(novoUsuario.email, 200, stdin);
    
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
    usuarios.total;

    printf("\nUsuario cadastrado com sucesso! ID: %d\n", novoUsuario.id);
}

void emprestarLivro() {
    // implementar emprestimo de livro
}

void devolverLivro() {
    // implementar devuloução de livro
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

void ExibirLivro(Livro livro) {
    // exibir livro
}

int main() {
    usuarios.total = 0;
    catalogo.total = 0;
    exemplares.total = 0;
    historico.total = 0;
    reservas.total = 0;

    printf("=============================================\n");
    printf("SISTEMA DE BIBLIOTECA\n");
    printf("=============================================\n");

    int opcao = -1;
    while(opcao!=8) {
        printf("===================== MENU =====================\n");
        printf("1 - Exibir Catalogo\n");
        printf("2 - Adicionar Livro\n");
        printf("3 - Cadastrar Usuario\n");
        printf("4 - Realizar Emprestimo\n");
        printf("5 - Devolver Livro\n");
        printf("6 - Renovar Livro\n");
        printf("7 - Buscar Livro\n");
        printf("8 - Sair\n");
        printf("Entre opcao: ");
        scanf("%d", &opcao);
        getchar();

        switch (opcao) {
            case 3:
                cadastrarUsuario();
                break;
        }
    }
}