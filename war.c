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

void exibirMapa(Territorio *t, int n) {
    printf("\n=== Estado Atual do Mapa ===\n");
    for (int i = 0; i < n; i++) {
        printf("(%d) %s | Exército: %s | Tropas: %d\n",
               i + 1, t[i].nome, t[i].corExercito, t[i].tropas);
    }
}

void simularAtaque(Territorio *atacante, Territorio *defensor) {
    if (atacante->tropas <= 1) {
        printf("\nO território atacante precisa de pelo menos 2 tropas para atacar!\n");
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

int main() {
    srand(time(NULL));

    Territorio *territorios = (Territorio *) calloc(MAX, sizeof(Territorio));

    printf("=== Cadastro dos Territórios ===\n");
    for (int i = 0; i < MAX; i++) {
        printf("\nTerritório %d:\n", i + 1);

        printf("Nome: ");
        fgets(territorios[i].nome, TAM_NOME, stdin);
        territorios[i].nome[strcspn(territorios[i].nome, "\n")] = '\0';

        printf("Cor do Exército: ");
        fgets(territorios[i].corExercito, TAM_COR, stdin);
        territorios[i].corExercito[strcspn(territorios[i].corExercito, "\n")] = '\0';

        printf("Número de Tropas: ");
        scanf("%d", &territorios[i].tropas);
        getchar();
    }

    int atacante, defensor;
    while (1) {
        exibirMapa(territorios, MAX);

        printf("\nEscolha o território ATACANTE (1-5, 0 para sair): ");
        scanf("%d", &atacante);
        if (atacante == 0) break;

        printf("Escolha o território DEFENSOR (1-5): ");
        scanf("%d", &defensor);

        if (atacante < 1 || atacante > MAX || defensor < 1 || defensor > MAX || atacante == defensor) {
            printf("Jogada inválida!\n");
            continue;
        }

        simularAtaque(&territorios[atacante - 1], &territorios[defensor - 1]);
    }

    free(territorios);
    return 0;
}

printf("Novo commit\n");