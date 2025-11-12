#include <stdio.h>
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
    Exemplar exemplares[MAX];
} Livro;

typedef struct catalogo {
    Livro livros[MAX];
    int tamanho;
} Catalogo;

void exibirCatalogo(Catalogo catalogo) {
    int i;
    printf("============= Catalogo =============\n");
    for (i = 0; i < catalogo.tamanho; i++)
        printf("NOME: %s", catalogo.livros[i].titulo);
    printf("\n============= Fim Catalogo =============\n");
}

void LerLivro(Livro *livro) {
    printf("Entre com o titulo do livro: ");
    fgets(livro->titulo, MAX, stdin);
}

void ExibirLivro(Livro livro) {
    printf("============== Livro ================");
    printf("IDENTIFICADOR: %d\n", livro.identifcador);
    printf("NOME: %s\n", livro.nome);
    printf("ISBN: %d\n", livro.isbn);
    printf("EDICAO: %s\n", livro.edicao);
    printf("IMPRENTA: %s\n", livro.imprenta);
    printf("MATERIAL: %s\n", livro.material);
    
    printf("Exemplares: ")
    for (int i = 1; i <= livro.numExemplares; i++)
    {
        printf("============== Livro ================");
        printf("IDENTIFICADOR: %d\n", livro.identifcador);
        printf("NOME: %s\n", livro.nome);
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
    while(opcao!=3) {
        printf("1 - Exibir Catalogo\n");
        printf("2 - Adicionar Livro\n");
        printf("3 - Sair\n");
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
        }
    }
}