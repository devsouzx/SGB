#include <stdio.h>
#include <string.h>
#include <limits.h>
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

ListaUsuarios usuarios = {0};
Catalogo catalogo = {0};
ListaExemplares exemplares = {0};
HistoricoEmprestimos historico = {0};
ListaReservas reservas = {0};

void dataAtual(char *data) {
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
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

void adicionarExemplarAoLivro(int livroId, int quantidade) {
    if (exemplares.total + quantidade > MAX_EXEMPLARES) {
        printf("Nao ha espaco para tantos exemplares!\n");
        return;
    }

    for (int i = 0; i < quantidade; i++) {
        Exemplar novoEx;
        novoEx.id = exemplares.total;
        novoEx.livroId = livroId;
        
        printf("Exemplar %d:\n", i + 1);
        printf("Numero de Chamada: ");
        fgets(novoEx.numeroChamada, 50, stdin);
        
        printf("Localizacao: ");
        fgets(novoEx.localizacao, 100, stdin);
        
        printf("Volume: ");
        fgets(novoEx.volume, 30, stdin);
        
        printf("Suporte (Fisico/Digital): ");
        fgets(novoEx.suporte, 20, stdin);
        
        novoEx.status = 1;
        novoEx.usuarioId = -1;
        strcpy(novoEx.dataEmprestimo, "");
        strcpy(novoEx.dataDevolucao, "");
        
        printf("Biblioteca: ");
        fgets(novoEx.biblioteca, 100, stdin);
        
        exemplares.exemplares[exemplares.total++] = novoEx;
        printf("Exemplar %d adicionado com sucesso!\n\n", i + 1);
    }
}

void adicionarLivro() {
    if (catalogo.total >= MAX_LIVROS) {
        printf("Limite de livros atingido!\n");
        return;
    }

    Livro novoLivro;
    novoLivro.id = catalogo.total;
    novoLivro.disponiveis = 0;
    dataAtual(novoLivro.dataCadastro);

    printf("\n=== CADASTRO DE LIVRO ===\n");
    
    printf("Titulo: ");
    fgets(novoLivro.titulo, 200, stdin);

    printf("Autor: ");
    fgets(novoLivro.autor, 100, stdin);

    printf("Editora: ");
    fgets(novoLivro.editora, 100, stdin);
    
    printf("ISBN: ");
    scanf("%lld", &novoLivro.isbn);
    getchar();

    printf("Local de Publicacao: ");
    fgets(novoLivro.localPublicacao, 100, stdin);
    
    printf("Ano de Publicacao: ");
    scanf("%d", &novoLivro.anoPublicacao);
    getchar();

    printf("Edicao: ");
    scanf("%d", &novoLivro.edicao);
    getchar();

    printf("Descricao Fisica (ex: 200 p.): ");
    fgets(novoLivro.descricaoFisica, 100, stdin);

    printf("Serie: ");
    fgets(novoLivro.serie, 100, stdin);

    printf("Notas: ");
    fgets(novoLivro.notas, 500, stdin);

    printf("Assunto: ");
    fgets(novoLivro.assunto, 300, stdin);

    printf("Classificacao (ex: CDD 123): ");
    fgets(novoLivro.classificacao, 50, stdin);

    printf("Idioma: ");
    fgets(novoLivro.idioma, 30, stdin);

    printf("Tipo de Material (ex: Impresso, Digital): ");
    fgets(novoLivro.tipoMaterial, 50, stdin);

    printf("Total de Exemplares: ");
    scanf("%d", &novoLivro.totalExemplares);
    getchar();

    novoLivro.disponiveis = novoLivro.totalExemplares;

    catalogo.livros[catalogo.total] = novoLivro;
    catalogo.total++;

    printf("\nLivro cadastrado com sucesso! ID: %d\n", novoLivro.id);

    if (novoLivro.totalExemplares > 0) {
        printf("Cadastrando %d exemplares para este livro.\n", novoLivro.totalExemplares);
        adicionarExemplarAoLivro(novoLivro.id, novoLivro.totalExemplares);
    }
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
        
        printf("Deseja tentar fazer uma reserva para este livro? (S/N): ");
        char resposta[4];
        if (fgets(resposta, sizeof(resposta), stdin) == NULL) return;
        if (resposta[0] == 'S' || resposta[0] == 's') {
            printf("\nVoce solicitou reservar o livro:\n");
            printf("Usuario: %s", usuario->nome);
            printf("Livro: %s", livro->titulo);
            printf("Confirma a reserva? (S/N): ");
            char confirma[4];
            if (fgets(confirma, sizeof(confirma), stdin) == NULL) return;
            if (confirma[0] == 'S' || confirma[0] == 's') {
                extern void reservarLivroParaUsuario(Usuario *usuario, Livro *livro);
                reservarLivroParaUsuario(usuario, livro);
            } else {
                printf("Reserva cancelada pelo usuario.\n");
            }
        } else {
            printf("Operacao de reserva cancelada.\n");
        }
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

    novo.id = historico.total;

    novo.usuarioId = usuario->id;
    novo.exemplarId = ex->id;

    dataAtual(novo.dataEmprestimo);

    time_t t = time(NULL);
    t += 7 * 24 * 3600;
    struct tm tm = *localtime(&t);
    sprintf(novo.dataDevolucaoPrevista, "%02d/%02d/%04d",
            tm.tm_mday, tm.tm_mon + 1, tm.tm_year + 1900);

    strcpy(novo.dataDevolucaoReal, "");
    novo.renovacoes = 0;
    novo.status = 1;
    novo.multa = 0.0;

    historico.emprestimos[historico.total] = novo;

    historico.total++;

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

static time_t parseDateString(const char *dateStr) {
    if (dateStr == NULL || strlen(dateStr) < 8) return (time_t)0;
    int d = 0, m = 0, y = 0;
    if (sscanf(dateStr, "%d/%d/%d", &d, &m, &y) != 3) return (time_t)0;
    struct tm tmv;
    memset(&tmv, 0, sizeof(tmv));
    tmv.tm_mday = d;
    tmv.tm_mon = m - 1;
    tmv.tm_year = y - 1900;
    tmv.tm_hour = 12; 
    return mktime(&tmv);
}

static void formatDateToString(time_t t, char *outBuf, size_t bufSize) {
    if (outBuf == NULL || bufSize < 11) return;
    struct tm *tmv = localtime(&t);
    snprintf(outBuf, bufSize, "%02d/%02d/%04d", tmv->tm_mday, tmv->tm_mon + 1, tmv->tm_year + 1900);
}

static time_t addDaysToTime(time_t base, int days) {
    return base + (time_t)days * 24 * 3600;
}

void reservarLivroParaUsuario(Usuario *usuario, Livro *livro) {
    for (int i = 0; i < reservas.total; i++) {
        Reserva r = reservas.reservas[i];
        if (r.usuarioId == usuario->id && r.livroId == livro->id && r.status == 1) {
            printf("Usuario ja possui uma reserva ativa para este livro.\n");
            return;
        }
    }

    if (reservas.total >= MAX_RESERVAS) {
        printf("Limite de reservas atingido!\n");
        return;
    }

    time_t now = time(NULL);

    time_t lastLoanEnd = 0;

    for (int i = 0; i < exemplares.total; i++) {
        Exemplar ex = exemplares.exemplares[i];
        if (ex.livroId == livro->id) {
            if (ex.status == 0 && strlen(ex.dataDevolucao) > 0) {
                time_t dt = parseDateString(ex.dataDevolucao);
                if (dt > lastLoanEnd) lastLoanEnd = dt;
            }
        }
    }

    for (int i = 0; i < historico.total; i++) {
        Emprestimo emp = historico.emprestimos[i];

        int exIndex = -1;
        for (int j = 0; j < exemplares.total; j++) {
            if (exemplares.exemplares[j].id == emp.exemplarId) { exIndex = j; break; }
        }
        if (exIndex != -1 && exemplares.exemplares[exIndex].livroId == livro->id) {
            if (strlen(emp.dataDevolucaoPrevista) > 0) {
                time_t dt = parseDateString(emp.dataDevolucaoPrevista);
                if (dt > lastLoanEnd) lastLoanEnd = dt;
            }
        }
    }


    time_t lastReserveEnd = 0;
    for (int i = 0; i < reservas.total; i++) {
        Reserva r = reservas.reservas[i];
        if (r.livroId == livro->id && r.status == 1 && strlen(r.dataExpiracao) > 0) {
            time_t dt = parseDateString(r.dataExpiracao);
            if (dt > lastReserveEnd) lastReserveEnd = dt;
        }
    }


    time_t start = now;
    if (lastLoanEnd > start) start = lastLoanEnd;
    if (lastReserveEnd > start) start = lastReserveEnd;

    if (start == lastLoanEnd && lastLoanEnd != 0) {
        start = addDaysToTime(start, 1);
    }
    if (start == lastReserveEnd && lastReserveEnd != 0) {
        start = addDaysToTime(start, 1);
    }

    time_t expiration = addDaysToTime(start, 7);

    Reserva novo;
    novo.id = reservas.total;
    novo.usuarioId = usuario->id;
    novo.livroId = livro->id;
    dataAtual(novo.dataReserva);
    formatDateToString(expiration, novo.dataExpiracao, sizeof(novo.dataExpiracao));
    int maxPrio = 0;
    for (int i = 0; i < reservas.total; i++) {
        Reserva rr = reservas.reservas[i];
        if (rr.livroId == livro->id && rr.status == 1) {
            if (rr.prioridade > maxPrio) maxPrio = rr.prioridade;
        }
    }
    novo.prioridade = maxPrio + 1;
    novo.status = 1;

    reservas.reservas[reservas.total++] = novo;

    char inicioBuf[16];
    formatDateToString(start, inicioBuf, sizeof(inicioBuf));
    printf("\n=== RESERVA REGISTRADA COM SUCESSO ===\n");
    printf("ID: %d\n", novo.id);
    printf("Usuario: %s", usuario->nome);
    printf("Livro: %s", livro->titulo);
    printf("Data da Solicitacao: %s\n", novo.dataReserva);
    printf("Inicio Previsto da Reserva: %s\n", inicioBuf);
    printf("Data de Expiracao (fim da reserva): %s\n", novo.dataExpiracao);
    printf("Prioridade: %d\n", novo.prioridade);
    printf("Status: %s\n", novo.status == 1 ? "Ativa" : "Inativa");
}

void devolverLivro() {
    printf("ESPECIFIQUE O ID DO EMPRESTIMO A SER DEVOLVIDO: ");
    int emprestimoId;
    scanf("%d", &emprestimoId);
    getchar();

    if (emprestimoId < 0 || emprestimoId >= historico.total) {
        printf("Emprestimo nao encontrado!\n");
        return;
    }

    Emprestimo *emp = &historico.emprestimos[emprestimoId];

    if (emp->status != 1) {
        printf("Este emprestimo ja foi devolvido!\n");
        return;
    }

    Usuario *usuario = &usuarios.usuarios[emp->usuarioId];
    Exemplar *ex = &exemplares.exemplares[emp->exemplarId];
    Livro *livro = &catalogo.livros[ex->livroId];

    dataAtual(emp->dataDevolucaoReal);

    emp->status = 0;

    ex->status = 1;
    ex->usuarioId = -1;
    strcpy(ex->dataEmprestimo, "");
    strcpy(ex->dataDevolucao, "");

    if (usuario->emprestimosAtivos > 0)
        usuario->emprestimosAtivos--;

    livro->disponiveis++;

    int reservaIndex = -1;
    int melhorPrio = INT_MAX;
    for (int i = 0; i < reservas.total; i++) {
        Reserva rr = reservas.reservas[i];
        if (rr.livroId == livro->id && rr.status == 1) {

            int uidx = rr.usuarioId;
            if (uidx >= 0 && uidx < usuarios.total) {
                Usuario *cand = &usuarios.usuarios[uidx];
                if (cand->emprestimosAtivos < cand->limiteEmprestimos) {
                    if (rr.prioridade < melhorPrio) {
                        melhorPrio = rr.prioridade;
                        reservaIndex = i;
                    }
                }
            }
        }
    }

    if (reservaIndex != -1) {
        Reserva *rsel = &reservas.reservas[reservaIndex];
        Usuario *dest = &usuarios.usuarios[rsel->usuarioId];

        if (historico.total < MAX_EMPRESTIMOS) {
            Emprestimo novoE;
            novoE.id = historico.total;
            novoE.usuarioId = dest->id;
            novoE.exemplarId = ex->id;
            dataAtual(novoE.dataEmprestimo);
            time_t tt = time(NULL) + 7 * 24 * 3600;
            struct tm ttm = *localtime(&tt);
            sprintf(novoE.dataDevolucaoPrevista, "%02d/%02d/%04d", ttm.tm_mday, ttm.tm_mon + 1, ttm.tm_year + 1900);
            strcpy(novoE.dataDevolucaoReal, "");
            novoE.renovacoes = 0;
            novoE.status = 1;
            novoE.multa = 0.0f;

            historico.emprestimos[historico.total++] = novoE;

            ex->status = 0;
            ex->usuarioId = dest->id;
            strcpy(ex->dataEmprestimo, novoE.dataEmprestimo);
            strcpy(ex->dataDevolucao, novoE.dataDevolucaoPrevista);

            dest->emprestimosAtivos++;
            livro->disponiveis--;

            rsel->status = 0;

            printf("\n=== RESERVA CONVERTIDA EM EMPRESTIMO ===\n");
            printf("Reserva ID atendida: %d\n", rsel->id);
            printf("Novo Emprestimo ID: %d\n", novoE.id);
            printf("Usuario: %s", dest->nome);
            printf("Livro: %s", livro->titulo);
            printf("Exemplar: %s\n", ex->numeroChamada);
            printf("Data Emprestimo: %s\n", novoE.dataEmprestimo);
            printf("Devolucao Prevista: %s\n", novoE.dataDevolucaoPrevista);
        } else {
            printf("Historico cheio: nao foi possivel converter reserva em emprestimo.\n");
        }
    }

    printf("\n=== DEVOLUCAO CONCLUIDA ===\n");
    printf("Emprestimo ID: %d\n", emp->id);
    printf("Livro: %s", livro->titulo);
    printf("Exemplar: %s\n", ex->numeroChamada);
    printf("Usuario: %s", usuario->nome);
    printf("Data da devolucao: %s\n", emp->dataDevolucaoReal);
}

void renovarLivro() {
    printf("\n=== RENOVACAO DE LIVRO ===\n");
    printf("Informe o ID do Emprestimo que deseja renovar: ");
    
    int empId;
    if (scanf("%d", &empId) != 1) {
        while(getchar() != '\n');
        return;
    }
    getchar();
   
    if (empId < 0 || empId >= historico.total) {
        printf("Emprestimo nao encontrado.\n");
        return;
    }

    Emprestimo *emp = &historico.emprestimos[empId];

    if (emp->status == 0) {
        printf("Este emprestimo ja foi finalizado (devolvido).\n");
        return;
    }

    if (emp->renovacoes >= 3) {
        printf("Limite de renovacoes atingido para este emprestimo (Max: 3).\n");
        return;
    }
    
    //verificar se há reserva ativa
    int exemplarIndex = -1;
    for(int i=0; i<exemplares.total; i++) {
        if(exemplares.exemplares[i].id == emp->exemplarId) {
            exemplarIndex = i;
            break;
        }
    }
    
    if (exemplarIndex == -1) {
        printf("Erro interno: Exemplar associado nao encontrado.\n");
        return;
    }

    int livroId = exemplares.exemplares[exemplarIndex].livroId;
    Livro *livro = &catalogo.livros[livroId];
    Usuario *usuario = &usuarios.usuarios[emp->usuarioId];
        
    for(int i=0; i<reservas.total; i++) {
        if (reservas.reservas[i].livroId == livroId && reservas.reservas[i].status == 1) {
            printf("NAO E POSSIVEL RENOVAR: Existe uma reserva ativa para este livro.\n");
            printf("O livro deve ser devolvido na data prevista para atender a fila de espera.\n");
            return;
        }
    }

    // confirmação e pré-visualização
    time_t dataAtualDev = parseDateString(emp->dataDevolucaoPrevista);
    time_t novaData = addDaysToTime(dataAtualDev, 7);
    char novaDataStr[11];
    formatDateToString(novaData, novaDataStr, sizeof(novaDataStr));

    printf("\nVoce solicitou renovar o emprestimo:\n");
    printf("ID do Emprestimo: %d\n", emp->id);
    printf("Usuario: %s", usuario->nome);
    printf("Livro: %s", livro->titulo);
    printf("Devolucao Prevista ATUAL: %s\n", emp->dataDevolucaoPrevista);
    printf("Renovacoes feitas: %d\n", emp->renovacoes);
    printf("Nova Devolucao Prevista apos renovacao: %s\n", novaDataStr);
    
    printf("\nConfirma a renovacao? (S/N): ");
    char confirma[4];
    if (fgets(confirma, sizeof(confirma), stdin) == NULL) return;
    if (confirma[0] != 'S' && confirma[0] != 's') {
        printf("Renovacao cancelada pelo usuario.\n");
        return;
    }
    

    // efetuar renovação
    strcpy(emp->dataDevolucaoPrevista, novaDataStr);
    emp->renovacoes++;
    
    if (exemplarIndex != -1) {
        strcpy(exemplares.exemplares[exemplarIndex].dataDevolucao, emp->dataDevolucaoPrevista);
    }

    // confirmação final
    printf("\n=== RENOVACAO REGISTRADA COM SUCESSO ===\n");
    printf("ID do Emprestimo: %d\n", emp->id);
    printf("Usuario: %s", usuario->nome);
    printf("Livro: %s", livro->titulo);
    printf("Nova Data de Devolucao: %s\n", emp->dataDevolucaoPrevista);
    printf("Total de renovacoes realizadas: %d\n", emp->renovacoes);
}

void exibirEmprestimosEReservas(Usuario usuario) {
    printf("\n=== SITUACAO DO USUARIO ===\n");
    printf("Nome: %s", usuario.nome);
    printf("CPF: %s", usuario.cpf);
    printf("Limite de emprestimos: %d\n", usuario.limiteEmprestimos);
    printf("Emprestimos ativos: %d\n", usuario.emprestimosAtivos);
    printf("Espaco restante para emprestimos: %d\n", usuario.limiteEmprestimos - usuario.emprestimosAtivos);

    printf("\n-- Emprestimos Ativos --\n");
    int encontrouEmp = 0;
    int i;
    for (i = 0; i < historico.total; i++) {
        Emprestimo emp = historico.emprestimos[i];
        if (emp.usuarioId == usuario.id && emp.status == 1) {
            Exemplar *ex = NULL;
            int j;
            for (j = 0; j < exemplares.total; j++) {
                if (exemplares.exemplares[j].id == emp.exemplarId) { ex = &exemplares.exemplares[j]; break; }
            }
            const char *titulo = "(titulo nao encontrado)\n";
            char exemplarBuf[128] = "(exemplar nao encontrado)";
            if (ex != NULL) {
                strcpy(exemplarBuf, ex->numeroChamada);
                int k;
                for (k = 0; k < catalogo.total; k++) {
                    if (catalogo.livros[k].id == ex->livroId) { titulo = catalogo.livros[k].titulo; break; }
                }
            }
            printf("ID Emprestimo: %d\n", emp.id);
            printf("Livro: %s", titulo);
            printf("Exemplar: %s\n", exemplarBuf);
            printf("Data Emprestimo: %s\n", emp.dataEmprestimo);
            printf("Devolucao Prevista: %s\n", emp.dataDevolucaoPrevista);
            if (strlen(emp.dataDevolucaoReal) > 0) printf("Data Devolucao Real: %s\n", emp.dataDevolucaoReal);
            printf("Renovacoes: %d | Status: %s\n\n", emp.renovacoes, emp.status == 1 ? "Ativo" : "Finalizado");
            encontrouEmp = 1;
        }
    }
    if (!encontrouEmp) printf("Nenhum emprestimo ativo encontrado para este usuario.\n");

    printf("\n-- Reservas Ativas --\n");
    int encontrouRes = 0;
    for (i = 0; i < reservas.total; i++) {
        Reserva r = reservas.reservas[i];
        if (r.usuarioId == usuario.id && r.status == 1) {
            const char *titulo = "(titulo nao encontrado)\n";
            int k;
            for (k = 0; k < catalogo.total; k++) {
                if (catalogo.livros[k].id == r.livroId) { titulo = catalogo.livros[k].titulo; break; }
            }
            printf("ID Reserva: %d\n", r.id);
            printf("Livro: %s", titulo);
            printf("Data da Solicitacao: %s\n", r.dataReserva);
            printf("Inicio Previsto / Data de Expiracao: %s\n", r.dataExpiracao);
            printf("Prioridade: %d | Status: %s\n\n", r.prioridade, r.status == 1 ? "Ativa" : "Inativa");
            encontrouRes = 1;
        }
    }
    if (!encontrouRes) printf("Nenhuma reserva ativa encontrada para este usuario.\n");
}

void exibirLivro(int index) {
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
        printf("8 - Buscar Emprestimos e Reservas\n");
        printf("9 - Listar Usuarios\n");
        printf("10 - Buscar Usuario por CPF\n");
        printf("11 - Sair\n");
        printf("Entre opcao: ");
        char opcaos[50];
        fgets(opcaos, 50, stdin);
        opcaos[strcspn(opcaos, "\n")] = '\0';

        int num;
        if (sscanf(opcaos, " %d", &num) == 1) {
            opcao = num;
        } else {
            char lower[120];
            int L = (int)strlen(opcaos);
            int i;
            for (i = 0; i < L; i++) {
                char c = opcaos[i];
                if (c >= 'A' && c <= 'Z') lower[i] = c + ('a' - 'A');
                else lower[i] = c;
            }
            lower[L] = '\0';

            if (strstr(lower, "reservas") != NULL || strstr(lower, "emprestimos e reservas") != NULL || strstr(lower, "buscar emprestimos") != NULL) {
                opcao = 8;
            } else if (strstr(lower, "exibir catalogo") != NULL || (strstr(lower, "exibir") != NULL && strstr(lower, "catalogo") != NULL) || strstr(lower, "catalogo") != NULL) {
                opcao = 1;
            } else if (strstr(lower, "adicionar livro") != NULL || strstr(lower, "adicionar") != NULL) {
                opcao = 2;
            } else if (strstr(lower, "cadastrar usuario") != NULL || strstr(lower, "cadastrar") != NULL) {
                opcao = 3;
            } else if (strstr(lower, "devolver") != NULL) {
                opcao = 5;
            } else if (strstr(lower, "renovar") != NULL) {
                opcao = 6;
            } else if (strstr(lower, "buscar livro") != NULL || (strstr(lower, "buscar") != NULL && strstr(lower, "livro") != NULL) || strstr(lower, "livro") != NULL) {
                opcao = 7;
            } else if (strstr(lower, "listar usuarios") != NULL || strstr(lower, "listar") != NULL) {
                opcao = 9;
            } else if (strstr(lower, "buscar usuario") != NULL || strstr(lower, "cpf") != NULL) {
                opcao = 10;
            } else if (strstr(lower, "emprestimo") != NULL || strstr(lower, "realizar emprestimo") != NULL) {
                opcao = 4;
            } else if (strstr(lower, "sair") != NULL || strstr(lower, "exit") != NULL) {
                opcao = 11;
            } else {
                printf("Opcao invalida. Tente novamente.\n");
                opcao = -1;
                continue;
            }
        }

        switch (opcao) {
            case 1: {
                exibirCatalogo();
                break;
            }
            case 2: {
                adicionarLivro();
                break;
            }
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
            case 6:{
                renovarLivro();
                break;
            }
            case 7:{
                char titulo[200];
                printf("Titulo do Livro: ");
                fgets(titulo, 200, stdin);
                int livroIndex = buscarLivro(titulo);
                if (livroIndex != -1) {
                    exibirLivro(livroIndex);
                } else {
                    printf("Livro nao encontrado!\n");
                }
                break;
            }
            case 8:{
                char cpf[15];
                printf("CPF: ");
                fgets(cpf, 15, stdin);
                int index = buscarUsuarioPorCPF(cpf);
                if (index != -1) {
                    Usuario u = usuarios.usuarios[index];
                    exibirEmprestimosEReservas(u);
                } else {
                    printf("Usuario nao encontrado!\n");
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