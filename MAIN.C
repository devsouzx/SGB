#include <stdio.h>
#include <strings.h>

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

void cadastrarUsuario() {
    // implementar cadastro do usuario
}

void LerLivro(Livro *livro) {
    printf("Entre com o titulo do livro: ");
    fgets(livro->titulo, MAX_STR, stdin);
}

void LerUsuario(Usuario *usuario) {
    printf("Entre o nome do usuario: ");
    fgets(usuario->nome, MAX_STR, stdin);

    printf("Entre o email do usuario: ");
    fgets(usuario->email, MAX_STR, stdin);

    printf("Entre o cpf do usuario: ");
    fgets(usuario->cpf, 15, stdin);

    printf("Entre o limite de emprestimos do usuario: ");
    scanf("%d", usuario->limiteEmprestimos);
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
    int i;
    printf("============= Catalogo =============\n");
    for (i = 0; i < catalogo.tamanho; i++)
        printf("NOME: %s", catalogo.livros[i].titulo);
    printf("\n============= Fim Catalogo =============\n");
}

void ExibirLivro(Livro livro) {
    printf("============== Livro ================");
    printf("IDENTIFICADOR: %d\n", livro.identifcador);
    printf("NOME: %s\n", livro.titulo);
    printf("ISBN: %d\n", livro.isbn);
    printf("EDICAO: %s\n", livro.edicao);
    printf("IMPRENTA: %s\n", livro.imprenta);
    printf("MATERIAL: %s\n", livro.material);
    
    printf("Exemplares: ");
    for (int i = 1; i <= livro.numExemplares; i++)
    {
        printf("============== Livro ================");
        printf("IDENTIFICADOR: %d\n", livro.identifcador);
        printf("TITULO: %s\n", livro.titulo);
        printf("ISBN: %d\n", livro.isbn);
        printf("EDICAO: %s\n", livro.edicao);
        printf("IMPRENTA: %s\n", livro.imprenta);
        printf("MATERIAL: %s\n", livro.material);
    }
}

int main() {
    int opcao = -1;
    Catalogo catalogo;
    Livro livro;
    Usuarios listaUsuarios;
    Usuario usuario;
    catalogo.tamanho = 0;
    listaUsuarios.tamanho = 0;
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
            case 1:
                exibirCatalogo(catalogo);
                break;
            case 2:
                LerLivro(&livro);
                catalogo.livros[catalogo.tamanho] = livro;
                catalogo.tamanho++;
                break;
            case 3:
                LerUsuario(&usuario);
                usuario.idUsuario = listaUsuarios.tamanho;
                listaUsuarios.usuarios[listaUsuarios.tamanho] = usuario;
                listaUsuarios.tamanho++;

                printf("============== Usuario ================");
                printf("IDENTIFICADOR: %d\n", usuario.idUsuario);
                printf("NOME: %s\n", usuario.nome);
                printf("EMAIL: %s\n", usuario.email);
                printf("CPF: %s\n", usuario.cpf);
                printf("LIMITE DE EMPRESTIMOS: %d\n", usuario.limiteEmprestimos);
                break;
            case 4:
                break;
            case 5:
                break;
            case 6:
                break;
            case 7:
                char titulo[MAX_STR];
                printf("Entre o titulo do livro que deseja buscar: ");
                fgets(titulo, MAX_STR, stdin);

                /*
                int posicao = 0;
                for (int i = 0; i < strlen(titulo); i++) {
                    if (titulo[i] == ' ') continue;
                    titulo[posicao] = titulo[i];
                    posicao++;
                }
                strupr(titulo);
                printf("%s", titulo);
                */
               printf("%d", titulo);
                int i = 0;
                while (i<catalogo.tamanho) {
                    if (catalogo.livros[i].titulo != titulo)
                        printf("Livro nao encontrado\n");
                       else ExibirLivro(catalogo.livros[i]);
                    printf("%d", i);
                    printf("%d", catalogo.livros[i].titulo);
                    i++;
                }
                break;
        }
    }
}