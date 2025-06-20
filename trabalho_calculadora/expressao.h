#ifndef EXPRESSAO_H
#define EXPRESSAO_H

typedef struct {
    char posFixa[512];
    char inFixa[512];
    float valor;
} Expressao;

char* getFormaInFixa(char *str);
char* getFormaPosFixa(char *str);
float getValorPosFixa(char *strPosFixa);
float getValorInFixa(char *strInFixa);
int verificaPosFixada(char* expr);
#endif
