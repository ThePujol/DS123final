#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>
#include <locale.h>

#define MAX_QUESTOES 130
#define TEMPO_MAXIMO 7200 // 2 horas em segundos
#define MAX_USUARIOS 100
#define ARQUIVO_RANKING "ranking.txt"

typedef struct {
    char banca[50];
    char concurso[100];
    char topico[100];
    char tema[100];
    char enunciado[512];
    char resposta;
} Questao;

typedef struct {
    char nome[50];
    int pontuacao;
    int tempo; // em segundos
    time_t data_prova;
} Usuario;

// Fun��es utilizadas no programa
void limparTela();
void telaInicial();
void mostrarAjuda();
char obterRespostaValida();
void mostrarTemporizador(int tempoRestante);
void mostrarGabarito(Questao *questoes, int *questoesSelecionadas, char *respostasUsuario, int totalQuestoes);
void mostrarResultados(Usuario usuario, Questao *questoes, int *questoesSelecionadas, char *respostasUsuario);
void iniciarProva(Questao *questoes, int totalQuestoes);
void verRanking();
void exibirRankingPorPeriodo();
void responderQuestoesAleatorias(Questao *questoes, int totalQuestoes);
void exibirMenu(Questao *questoes, int totalQuestoes);
int lerQuestoes(const char *filename, Questao *questoes);

void limparTela() {
    // Limpa a tela no Windows
    #ifdef _WIN32
        system("cls");
    // Limpa a tela no Unix-like (Linux, macOS)
    #else
        system("clear");
    #endif
}

void telaInicial() {
    limparTela();
    printf("#############################################################\n");
    printf("#                                                           #\n");
    printf("#             Bem-vindo ao Simulador de Provas              #\n");
    printf("#                                                           #\n");
    printf("#         Desenvolvido para ajudar em sua prepara��o        #\n");
    printf("#                                                           #\n");
    printf("#                   Pressione Enter para continuar          #\n");
    printf("#                                                           #\n");
    printf("#############################################################\n");
    getchar(); // Espera o usu�rio pressionar Enter
}

void mostrarAjuda() {
    limparTela();
    printf("#############################################################\n");
    printf("#                           Ajuda                           #\n");
    printf("#                                                           #\n");
    printf("#  Instru��es:                                              #\n");
    printf("#  1. Iniciar Prova:                                        #\n");
    printf("#     - Escolha a op��o 'Iniciar Prova' no menu.            #\n");
    printf("#     - Digite seu nome quando solicitado.                  #\n");
    printf("#     - Responda 30 quest�es, digitando 'C' para Certo ou   #\n");
    printf("#       'E' para Errado.                                    #\n");
    printf("#     - Veja seu resultado e gabarito ao final.             #\n");
    printf("#                                                           #\n");
    printf("#  2. Ver Ranking:                                          #\n");
    printf("#     - Escolha a op��o 'Ver Ranking' no menu.              #\n");
    printf("#     - Veja a lista dos melhores desempenhos.              #\n");
    printf("#                                                           #\n");
    printf("#  3. Responder Quest�es Aleat�rias:                        #\n");
    printf("#     - Escolha a op��o 'Responder Quest�es Aleat�rias'     #\n");
    printf("#       no menu.                                            #\n");
    printf("#     - Responda quest�es aleat�rias sem limite de tempo.   #\n");
    printf("#                                                           #\n");
    printf("#  4. Ranking por Per�odo:                                  #\n");
    printf("#     - Escolha a op��o 'Ranking por Per�odo' no menu.      #\n");
    printf("#     - Veja o ranking dos melhores desempenhos por per�odo.#\n");
    printf("#                                                           #\n");
    printf("#  5. Sair:                                                 #\n");
    printf("#     - Escolha a op��o 'Sair' no menu.                     #\n");
    printf("#                                                           #\n");
    printf("#  Observa��es:                                             #\n");
    printf("#  - Digite 'q' para sair a qualquer momento.               #\n");
    printf("#  - Digite 'm' para voltar ao menu a qualquer momento.     #\n");
    printf("#                                                           #\n");
    printf("#############################################################\n");
    printf("\nPressione Enter para voltar ao menu.");
    getchar();
}

char obterRespostaValida() {
    char resposta;
    int valido = 0;
    while (!valido) {
        printf("Digite 'C' para Certo ou 'E' para Errado: ");
        scanf(" %c", &resposta);
        resposta = toupper(resposta);
        if (resposta == 'C' || resposta == 'E') {
            valido = 1;
        } else {
            printf("Resposta inv�lida! Por favor, digite 'C' para Certo ou 'E' para Errado.\n");
        }
    }
    return resposta;
}

void mostrarTemporizador(int tempoRestante) {
    int horas = tempoRestante / 3600;
    int minutos = (tempoRestante % 3600) / 60;
    int segundos = tempoRestante % 60;
    printf("Tempo restante: %02d:%02d:%02d\n", horas, minutos, segundos);
}

void mostrarGabarito(Questao *questoes, int *questoesSelecionadas, char *respostasUsuario, int totalQuestoes) {
    printf("Gabarito:\n");
    printf("-------------------------------------------------------------\n");
    for (int i = 0; i < totalQuestoes; i++) {
        int idx = questoesSelecionadas[i];
        printf("Quest�o %d:\n", i + 1);
        printf("Banca: %s\n", questoes[idx].banca);
        printf("Concurso: %s\n", questoes[idx].concurso);
        printf("T�pico: %s\n", questoes[idx].topico);
        printf("Tema: %s\n", questoes[idx].tema);
        printf("Enunciado: %s\n", questoes[idx].enunciado);
        printf("Sua resposta: %c | Resposta correta: %c\n", respostasUsuario[i], questoes[idx].resposta);
        printf("-------------------------------------------------------------\n");
    }
}

void mostrarResultados(Usuario usuario, Questao *questoes, int *questoesSelecionadas, char *respostasUsuario) {
    limparTela();
    printf("#############################################################\n");
    printf("#                    Resultados da Prova                    #\n");
    printf("#############################################################\n");
    int horas = usuario.tempo / 3600;
    int minutos = (usuario.tempo % 3600) / 60;
    int segundos = usuario.tempo % 60;

    printf("Nome: %s\n", usuario.nome);
    printf("Pontua��o: %d\n", usuario.pontuacao);
    printf("Tempo: %02d:%02d:%02d (hh:mm:ss)\n", horas, minutos, segundos);
    printf("-------------------------------------------------------------\n");

    mostrarGabarito(questoes, questoesSelecionadas, respostasUsuario, 30);

    printf("\nPressione Enter para voltar ao menu.");
    getchar(); // Espera o usu�rio pressionar Enter
}

void iniciarProva(Questao *questoes, int totalQuestoes) {
    Usuario usuario;
    printf("Digite seu nome: ");
    fgets(usuario.nome, sizeof(usuario.nome), stdin);
    usuario.nome[strcspn(usuario.nome, "\n")] = '\0'; // Remove newline

    int questoesSelecionadas[30];
    char respostasUsuario[30];
    int indicesUsados[MAX_QUESTOES] = {0};
    srand(time(NULL));

    for (int i = 0; i < 30; i++) {
        int index;
        do {
            index = rand() % totalQuestoes;
        } while (indicesUsados[index]);
        indicesUsados[index] = 1;
        questoesSelecionadas[i] = index;
    }

    time_t inicio = time(NULL);
    usuario.pontuacao = 0;

    for (int i = 0; i < 30; i++) {
        int idx = questoesSelecionadas[i];
        limparTela();
        printf("#############################################################\n");
        printf("#                          Quest�o %d                        #\n", i + 1);
        printf("#############################################################\n");
        printf("Banca: %s\n", questoes[idx].banca);
        printf("Concurso: %s\n", questoes[idx].concurso);
        printf("T�pico: %s\n", questoes[idx].topico);
        printf("Tema: %s\n", questoes[idx].tema);
        printf("-------------------------------------------------------------\n");
        printf("%s\n", questoes[idx].enunciado);
        printf("-------------------------------------------------------------\n");
        mostrarTemporizador(TEMPO_MAXIMO - (int)difftime(time(NULL), inicio));
        char resposta = obterRespostaValida();
        respostasUsuario[i] = resposta;
        if (resposta == questoes[idx].resposta) {
            usuario.pontuacao++;
        }
    }

    time_t fim = time(NULL);
    usuario.tempo = (int)difftime(fim, inicio);
    usuario.data_prova = inicio;

    FILE *file = fopen(ARQUIVO_RANKING, "a");
    if (file == NULL) {
        printf("Erro ao abrir o arquivo de ranking.\n");
        return;
    }
    fprintf(file, "%s %d %d %ld\n", usuario.nome, usuario.pontuacao, usuario.tempo, usuario.data_prova);
    fclose(file);

    mostrarResultados(usuario, questoes, questoesSelecionadas, respostasUsuario);

    printf("\nPressione Enter para voltar ao menu.");
    getchar(); // Espera o usu�rio pressionar Enter
    getchar(); // Necess�rio para capturar o Enter ap�s a mensagem
}

int compararUsuarios(const void *a, const void *b) {
    Usuario *usuarioA = (Usuario *)a;
    Usuario *usuarioB = (Usuario *)b;
    
    if (usuarioA->pontuacao != usuarioB->pontuacao) {
        return usuarioB->pontuacao - usuarioA->pontuacao; // Ordem decrescente por pontua��o
    }
    return usuarioA->tempo - usuarioB->tempo; // Ordem crescente por tempo se pontua��es forem iguais
}

void verRanking() {
    limparTela();
    FILE *file = fopen(ARQUIVO_RANKING, "r");
    if (file == NULL) {
        printf("Erro ao abrir o arquivo de ranking.\n");
        return;
    }

    Usuario usuarios[MAX_USUARIOS];
    int totalUsuarios = 0;

    while (fscanf(file, "%s %d %d %ld", usuarios[totalUsuarios].nome, &usuarios[totalUsuarios].pontuacao, &usuarios[totalUsuarios].tempo, &usuarios[totalUsuarios].data_prova) != EOF) {
        totalUsuarios++;
    }
    fclose(file);

    qsort(usuarios, totalUsuarios, sizeof(Usuario), compararUsuarios);

    printf("Ranking:\n");
    printf("Posi��o Nome                Pontos Tempo     Data\n");
    printf("--------------------------------------------------------------\n");
    for (int i = 0; i < totalUsuarios; i++) {
        int horas = usuarios[i].tempo / 3600;
        int minutos = (usuarios[i].tempo % 3600) / 60;
        int segundos = usuarios[i].tempo % 60;
        char dataStr[20];
        strftime(dataStr, sizeof(dataStr), "%Y-%m-%d", localtime(&usuarios[i].data_prova));
        printf("%-7d %-20s %-6d %02d:%02d:%02d %s\n", i + 1, usuarios[i].nome, usuarios[i].pontuacao, horas, minutos, segundos, dataStr);
    }

    printf("\nPressione Enter para voltar ao menu.");
    getchar();
}

void exibirRankingPorPeriodo() {
    limparTela();
    FILE *file = fopen(ARQUIVO_RANKING, "r");
    if (file == NULL) {
        printf("Erro ao abrir o arquivo de ranking.\n");
        return;
    }

    Usuario usuarios[MAX_USUARIOS];
    int totalUsuarios = 0;

    while (fscanf(file, "%s %d %d %ld", usuarios[totalUsuarios].nome, &usuarios[totalUsuarios].pontuacao, &usuarios[totalUsuarios].tempo, &usuarios[totalUsuarios].data_prova) != EOF) {
        totalUsuarios++;
    }
    fclose(file);

    qsort(usuarios, totalUsuarios, sizeof(Usuario), compararUsuarios);

    time_t agora = time(NULL);
    time_t umaSemanaAtras = agora - (7 * 24 * 3600);
    time_t umMesAtras = agora - (30 * 24 * 3600);

    printf("Escolha o per�odo:\n");
    printf("1. �ltima semana\n");
    printf("2. �ltimo m�s\n");
    printf("3. Todo o tempo\n");
    printf("Escolha uma op��o: ");
    int opcao;
    scanf("%d", &opcao);
    getchar(); // Limpa o buffer do teclado

    time_t limiteTempo;
    if (opcao == 1) {
        limiteTempo = umaSemanaAtras;
    } else if (opcao == 2) {
        limiteTempo = umMesAtras;
    } else {
        limiteTempo = 0;
    }

    printf("Ranking:\n");
    printf("Posi��o Nome                Pontos Tempo     Data\n");
    printf("--------------------------------------------------------------\n");
    int posicao = 1;
    for (int i = 0; i < totalUsuarios; i++) {
        if (usuarios[i].data_prova >= limiteTempo) {
            int horas = usuarios[i].tempo / 3600;
            int minutos = (usuarios[i].tempo % 3600) / 60;
            int segundos = usuarios[i].tempo % 60;
            char dataStr[20];
            strftime(dataStr, sizeof(dataStr), "%Y-%m-%d", localtime(&usuarios[i].data_prova));
            printf("%-7d %-20s %-6d %02d:%02d:%02d %s\n", posicao, usuarios[i].nome, usuarios[i].pontuacao, horas, minutos, segundos, dataStr);
            posicao++;
        }
    }

    printf("\nPressione Enter para voltar ao menu.");
    getchar();
}

void responderQuestoesAleatorias(Questao *questoes, int totalQuestoes) {
    int continuar = 1;

    while (continuar) {
        int index = rand() % totalQuestoes;
        limparTela();
        printf("#############################################################\n");
        printf("#                       Quest�o Aleat�ria                   #\n");
        printf("#############################################################\n");
        printf("Banca: %s\n", questoes[index].banca);
        printf("Concurso: %s\n", questoes[index].concurso);
        printf("T�pico: %s\n", questoes[index].topico);
        printf("Tema: %s\n", questoes[index].tema);
        printf("-------------------------------------------------------------\n");
        printf("%s\n", questoes[index].enunciado);
        printf("-------------------------------------------------------------\n");
        char resposta = obterRespostaValida();
        if (resposta == questoes[index].resposta) {
            printf("Resposta correta!\n");
        } else {
            printf("Resposta errada. A resposta correta � %c.\n", questoes[index].resposta);
        }
        printf("Deseja responder outra quest�o? (1 - Sim, 0 - N�o): ");
        scanf("%d", &continuar);
    }
}

void exibirMenu(Questao *questoes, int totalQuestoes) {
    int opcao;

    while (1) {
        limparTela();
        printf("#############################################################\n");
        printf("#                           Menu                            #\n");
        printf("#                                                           #\n");
        printf("#  1. Iniciar Prova                                          #\n");
        printf("#  2. Ver Ranking                                            #\n");
        printf("#  3. Ranking por Per�odo                                    #\n");
        printf("#  4. Ajuda                                                  #\n");
        printf("#  5. Responder Quest�es Aleat�rias                          #\n");
        printf("#  6. Sair                                                   #\n");
        printf("#                                                           #\n");
        printf("#############################################################\n");
        printf("Escolha uma op��o (ou 'q' para sair, 'm' para menu): ");
        scanf("%d", &opcao);
        getchar(); // Limpa o buffer do teclado

        switch (opcao) {
            case 1:
                iniciarProva(questoes, totalQuestoes);
                break;
            case 2:
                verRanking();
                break;
            case 3:
                exibirRankingPorPeriodo();
                break;
            case 4:
                mostrarAjuda();
                break;
            case 5:
                responderQuestoesAleatorias(questoes, totalQuestoes);
                break;
            case 6:
                printf("Tem certeza que deseja sair? (s/n): ");
                char confirmar;
                scanf(" %c", &confirmar);
                if (tolower(confirmar) == 's') {
                    exit(0);
                }
                break;
            default:
                printf("Op��o inv�lida!\n");
                getchar(); // Espera o usu�rio pressionar Enter
                break;
        }
    }
}

int lerQuestoes(const char *filename, Questao *questoes) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printf("Erro ao abrir o arquivo de quest�es.\n");
        return 1;
    }

    char linha[1024];
    int totalQuestoes = 0;
    while (fgets(linha, sizeof(linha), file) != NULL) {
        char *banca = strtok(linha, "|");
        char *concurso = strtok(NULL, "|");
        char *topico = strtok(NULL, "|");
        char *tema = strtok(NULL, "|");
        char *enunciado = strtok(NULL, "|");
        char *resposta = strtok(NULL, "|");

        if (banca && concurso && topico && tema && enunciado && resposta) {
            strcpy(questoes[totalQuestoes].banca, banca);
            strcpy(questoes[totalQuestoes].concurso, concurso);
            strcpy(questoes[totalQuestoes].topico, topico);
            strcpy(questoes[totalQuestoes].tema, tema);
            strcpy(questoes[totalQuestoes].enunciado, enunciado);
            questoes[totalQuestoes].resposta = resposta[0];
            totalQuestoes++;
        }
    }

    fclose(file);
    return totalQuestoes;
}

int main() {
    setlocale(LC_ALL, "Portuguese_Brazil.1252");

    Questao questoes[MAX_QUESTOES];
    int totalQuestoes = lerQuestoes("questoes_formatadas_iso_8859_1.txt", questoes);

    if (totalQuestoes > 0) {
        telaInicial();
        exibirMenu(questoes, totalQuestoes);
    }

    return 0;
}
