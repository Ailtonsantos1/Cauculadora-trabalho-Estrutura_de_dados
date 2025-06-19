#include <stdio.h>
#include <string.h>
#include "expressao.h"

int main() {
    Expressao expressoes[100];
    char linha[512];
    int i = 0;

    FILE *f = fopen("entradas.txt", "r");
    if (!f) {
        printf("Erro ao abrir o arquivo 'entradas.txt'\n");
        return 1;
    }
char linha[MAX_LINE];
    int linhaAtual = 1;

    while (fgets(linha, sizeof(linha), arquivo)) {
        char copia[MAX_LINE];
        strcpy(copia, linha);

        if (verificaPosFixada(copia)) {
            printf("Linha %d: POS-FIXADA VÁLIDA ✅\n", linhaAtual);
        } else {
            printf("Linha %d: INVÁLIDA ❌\n", linhaAtual);
        }

        linhaAtual++;
    }

    while (fgets(linha, sizeof(linha), f) && i < 100) {
        linha[strcspn(linha, "\n")] = '\0';
        strcpy(expressoes[i].posFixa, linha);
        strcpy(expressoes[i].inFixa, getFormaInFixa(expressoes[i].posFixa));
        expressoes[i].valor = getValorPosFixa(expressoes[i].posFixa);

        printf("Expressão %d:\n", i + 1);
        printf("Pos-fixa: %s\n", expressoes[i].posFixa);
        printf("Infixa: %s\n", expressoes[i].inFixa);
        printf("Valor: %.4f\n", expressoes[i].valor);
        printf("--------------------------\n");

        i++;
    }

    fclose(f);
    return 0;
}
