#include <stdio.h>
#include <strings.h>
#define MAX 100

typedef struct bibllioteca {
    int identificador;
    char name[];
} Bibliotaca;

typedef struct exemplar {
    int identificador;
    int codigo;
    int edicao;
    int ano;
    int volume;
    char suporte;
    char numeroChamada;
    char localizacao;
    bool disponivel;
    Bibliotaca bibllioteca;
} Exemplar;

typedef struct livro {
    int identifcador;
    int isbn;
    char titulo[MAX];
    char edicao[MAX];
    char imprenta[MAX];
    char material[MAX];
    int numExemplares;
    char slang[MAX];
    Exemplar exemplares[MAX];
} Livro;

typedef struct catalogo {
    Livro livros[MAX];
    int tamanho;
} Catalogo;

void cadastrarUsuario() {
    // implementar cadastro do usuario
}

void LerLivro(Livro *livro) {
    // implementar cadastro do livro
    printf("Entre com o titulo do livro: ");
    fgets(livro->titulo, MAX, stdin);
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
    catalogo.tamanho = 0;
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
            case 7:
                char titulo[MAX];
                printf("Entre o titulo do livro que deseja buscar: ");
                fgets(titulo, MAX, stdin);

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