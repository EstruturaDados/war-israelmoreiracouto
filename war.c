#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX 5
#define TAM_NOME 30
#define TAM_COR 15

typedef struct {
    char nome[TAM_NOME];
    char corExercito[TAM_COR];
    int tropas;
} Territorio;

void inicializarMapa(Territorio *t) {
    char *nomes[MAX] = {"Brasil", "Argentina", "Chile", "Peru", "México"};
    char *cores[MAX] = {"Azul", "Verde", "Vermelho", "Amarelo", "Preto"};
    int tropasIniciais[MAX] = {5, 4, 6, 3, 5};

    for (int i = 0; i < MAX; i++) {
        strcpy(t[i].nome, nomes[i]);
        strcpy(t[i].corExercito, cores[i]);
        t[i].tropas = tropasIniciais[i];
    }
}

void exibirMapa(const Territorio *t) {
    printf("\n=== Estado Atual do Mapa ===\n");
    for (int i = 0; i < MAX; i++) {
        printf("(%d) %s | Exército: %s | Tropas: %d\n",
               i + 1, t[i].nome, t[i].corExercito, t[i].tropas);
    }
}

void simularAtaque(Territorio *atacante, Territorio *defensor) {
    if (atacante->tropas <= 1) {
        printf("\nO território atacante precisa de pelo menos 2 tropas!\n");
        return;
    }

    int dadoAtaque = rand() % 6 + 1;
    int dadoDefesa = rand() % 6 + 1;

    printf("\n>>> %s (Atacante) [%d] x %s (Defensor) [%d]\n",
           atacante->nome, dadoAtaque, defensor->nome, dadoDefesa);

    if (dadoAtaque >= dadoDefesa) {
        defensor->tropas--;
        printf("Defensor perdeu 1 tropa!\n");
        if (defensor->tropas <= 0) {
            printf(">>> %s conquistou o território %s!\n",
                   atacante->corExercito, defensor->nome);
            defensor->tropas = atacante->tropas / 2;
            atacante->tropas /= 2;
            strcpy(defensor->corExercito, atacante->corExercito);
        }
    } else {
        atacante->tropas--;
        printf("Atacante perdeu 1 tropa!\n");
    }
}

int missaoCumprida(const Territorio *t) {
    int conquistados = 0;
    int verdeDestruido = 1; 

    for (int i = 0; i < MAX; i++) {
        if (strcmp(t[i].corExercito, "Verde") == 0) {
            verdeDestruido = 0;
        }
        if (strcmp(t[i].corExercito, "Azul") == 0) { // jogador = Azul
            conquistados++;
        }
    }

    if (verdeDestruido) {
        printf("\n🎉 Missão concluída: Destruir o exército verde!\n");
        return 1;
    }
    if (conquistados >= 3) {
        printf("\n🎉 Missão concluída: Conquistar 3 territórios!\n");
        return 1;
    }
    return 0;
}

int main() {
    srand(time(NULL));
    Territorio territorios[MAX];
    inicializarMapa(territorios);

    int opcao, atacante, defensor;

    do {
        printf("\n=== MENU PRINCIPAL ===\n");
        printf("1 - Atacar\n");
        printf("2 - Verificar Missão\n");
        printf("0 - Sair\n");
        printf("Escolha: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                exibirMapa(territorios);
                printf("\nEscolha o território ATACANTE (1-5): ");
                scanf("%d", &atacante);
                printf("Escolha o território DEFENSOR (1-5): ");
                scanf("%d", &defensor);
                if (atacante < 1 || atacante > MAX || defensor < 1 || defensor > MAX || atacante == defensor) {
                    printf("Jogada inválida!\n");
                } else {
                    simularAtaque(&territorios[atacante - 1], &territorios[defensor - 1]);
                }
                break;

            case 2:
                if (missaoCumprida(territorios)) {
                    printf("🏆 Você venceu o jogo!\n");
                    opcao = 0;
                } else {
                    printf("\nMissão ainda não concluída.\n");
                }
                break;

            case 0:
                printf("\nSaindo do jogo...\n");
                break;

            default:
                printf("Opção inválida!\n");
        }

    } while (opcao != 0);

    return 0;
}
