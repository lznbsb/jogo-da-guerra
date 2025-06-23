
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

typedef enum {PAUS, OUROS, COPAS, ESPADAS} Naipe;
typedef enum {DOIS=2, TRES, QUATRO, CINCO, SEIS, SETE, OITO, NOVE, DEZ, VALETE=11, DAMA=12, REI=13, AS=14} Valor;

typedef struct {
    Naipe naipe;
    Valor valor;
} Carta;

typedef struct no_carta {
    Carta carta;
    struct no_carta *prox;
} NoCarta;

typedef struct {
    char nome[50];
    int pontos;
    NoCarta *mao;
} Jogador;

const char* nomeNaipe(Naipe n) {
    switch(n) {
        case PAUS: return "Paus";
        case OUROS: return "Ouros";
        case COPAS: return "Copas";
        case ESPADAS: return "Espadas";
        default: return "";
    }
}

const char* nomeValor(Valor v) {
    static char buffer[6];
    switch(v) {
        case VALETE: return "Valete";
        case DAMA: return "Dama";
        case REI: return "Rei";
        case AS: return "As";
        default:
            snprintf(buffer, sizeof(buffer), "%d", v);
            return buffer;
    }
}

void exibirCarta(Carta c) {
    printf("%s de %s\n", nomeValor(c.valor), nomeNaipe(c.naipe));
}

void inserirCarta(NoCarta **mao, Carta c) {
    NoCarta *novo = malloc(sizeof(NoCarta));
    novo->carta = c;
    novo->prox = *mao;
    *mao = novo;
}

Carta removerCarta(NoCarta **mao) {
    if (!*mao) {
        Carta vazia = {PAUS, DOIS};
        return vazia;
    }
    NoCarta *temp = *mao;
    Carta c = temp->carta;
    *mao = temp->prox;
    free(temp);
    return c;
}

void liberarMao(NoCarta *mao) {
    while (mao) {
        NoCarta *temp = mao;
        mao = mao->prox;
        free(temp);
    }
}

void embaralhar(Carta *baralho, int tamanho) {
    for (int i = 0; i < tamanho; i++) {
        int j = rand() % tamanho;
        Carta temp = baralho[i];
        baralho[i] = baralho[j];
        baralho[j] = temp;
    }
}

void criarBaralho(Carta *baralho) {
    int i = 0;
    for (int n = PAUS; n <= ESPADAS; n++) {
        for (int v = DOIS; v <= AS; v++) {
            baralho[i].naipe = n;
            baralho[i].valor = v;
            i++;
        }
    }
}

void distribuirCartas(Jogador *j1, Jogador *j2, Carta *baralho) {
    for (int i = 0; i < 52; i++) {
        if (i % 2 == 0)
            inserirCarta(&j1->mao, baralho[i]);
        else
            inserirCarta(&j2->mao, baralho[i]);
    }
}

void salvarPontuacao(const Jogador *j1, const Jogador *j2) {
    FILE *f = fopen("placar.txt", "a");
    if (f) {
        fprintf(f, "%s: %d pontos | %s: %d pontos\n", j1->nome, j1->pontos, j2->nome, j2->pontos);
        fclose(f);
    }
}

void exibirPlacar() {
    FILE *f = fopen("placar.txt", "r");
    if (!f) {
        printf("Nenhum placar encontrado.\n");
        return;
    }
    char linha[100];
    while (fgets(linha, sizeof(linha), f)) {
        printf("%s", linha);
    }
    fclose(f);
}

void jogarRodada(Jogador *j1, Jogador *j2) {
    Carta c1 = removerCarta(&j1->mao);
    Carta c2 = removerCarta(&j2->mao);
    printf("%s joga: ", j1->nome); exibirCarta(c1);
    printf("%s joga: ", j2->nome); exibirCarta(c2);

    if (c1.valor > c2.valor) {
        printf("%s vence a rodada!\n", j1->nome);
        j1->pontos++;
    } else if (c2.valor > c1.valor) {
        printf("%s vence a rodada!\n", j2->nome);
        j2->pontos++;
    } else {
        printf("Empate!\n");
    }
}

void menu() {
    printf("\n--- JOGO DA GUERRA ---\n");
    printf("1. Iniciar novo jogo\n");
    printf("2. Ver placar\n");
    printf("3. Sair\n");
    printf("Escolha uma opcao: ");
}

int main() {
    srand(time(NULL));
    int opcao;
    Jogador j1, j2;

    do {
        menu();
        scanf("%d", &opcao);
        getchar();

        switch(opcao) {
            case 1:
                printf("Nome do Jogador 1: "); fgets(j1.nome, sizeof(j1.nome), stdin); j1.nome[strcspn(j1.nome, "\n")] = 0;
                printf("Nome do Jogador 2: "); fgets(j2.nome, sizeof(j2.nome), stdin); j2.nome[strcspn(j2.nome, "\n")] = 0;
                j1.pontos = j2.pontos = 0;
                j1.mao = j2.mao = NULL;

                Carta baralho[52];
                criarBaralho(baralho);
                embaralhar(baralho, 52);
                distribuirCartas(&j1, &j2, baralho);

                for (int i = 0; i < 26; i++) {
                    printf("\n--- Rodada %d ---\n", i+1);
                    jogarRodada(&j1, &j2);
                }

                printf("\nPlacar final: %s %d x %d %s\n", j1.nome, j1.pontos, j2.pontos, j2.nome);
                salvarPontuacao(&j1, &j2);
                liberarMao(j1.mao);
                liberarMao(j2.mao);
                break;

            case 2:
                exibirPlacar();
                break;

            case 3:
                printf("Saindo do jogo...\n");
                break;

            default:
                printf("Opcao invalida. Tente novamente.\n");
        }
    } while (opcao != 3);

    return 0;
}
