#include <stdio.h>
#include <string.h>

#define MAX 5
#define TAM_NOME 30
#define TAM_COR 15

// Struct do território
typedef struct {
    char nome[TAM_NOME];
    char corExercito[TAM_COR];
    int tropas;
} Territorio;

int main() {
    Territorio territorios[MAX];

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
        getchar(); // limpar buffer
    }

    printf("\n=== Estado Atual do Mapa ===\n");
    for (int i = 0; i < MAX; i++) {
        printf("Território %d - %s | Exército: %s | Tropas: %d\n",
               i + 1,
               territorios[i].nome,
               territorios[i].corExercito,
               territorios[i].tropas);
    }

    return 0;
}
printf("Novo commit\n");