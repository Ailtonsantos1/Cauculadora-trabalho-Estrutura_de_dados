#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include "expressao.h"

#define MAX 512

typedef struct {
    float items[MAX];
    int top;
} StackFloat;

typedef struct {
    char* items[MAX];
    int top;
} StackString;

// --- Funções de pilha ---
void initFloat(StackFloat* s) { s->top = -1; }
int isEmptyFloat(StackFloat* s) { return s->top == -1; }
void pushFloat(StackFloat* s, float val) { s->items[++s->top] = val; }
float popFloat(StackFloat* s) { return s->items[s->top--]; }
float topFloat(StackFloat* s) { return s->items[s->top]; }

void initString(StackString* s) { s->top = -1; }
void pushString(StackString* s, char* val) { s->items[++s->top] = strdup(val); }
char* popString(StackString* s) { return s->items[s->top--]; }
char* topString(StackString* s) { return s->items[s->top]; }

// --- Utilidades ---
int isOperator(char* token) {
    return strcmp(token, "+") == 0 || strcmp(token, "-") == 0 || 
           strcmp(token, "*") == 0 || strcmp(token, "/") == 0 ||
           strcmp(token, "^") == 0;
}

int isFunction(char* token) {
    return strcmp(token, "sen") == 0 || strcmp(token, "cos") == 0 ||
           strcmp(token, "log") == 0 || strcmp(token, "raiz") == 0;
}

int precedence(char* op) {
    if (strcmp(op, "+") == 0 || strcmp(op, "-") == 0) return 1;
    if (strcmp(op, "*") == 0 || strcmp(op, "/") == 0) return 2;
    if (strcmp(op, "^") == 0) return 3;
    return 0;
}

float evalFunc(char* func, float val) {
    if (strcmp(func, "sen") == 0) return sin(val * M_PI / 180);
    if (strcmp(func, "cos") == 0) return cos(val * M_PI / 180);
    if (strcmp(func, "log") == 0) return log10(val);
    if (strcmp(func, "raiz") == 0) return sqrt(val);
    return 0;
}

// --- Conversão para Pós-fixa ---
char* getFormaPosFixa(char* expr) {
    static char output[MAX];
    output[0] = '\0';
    StackString stack;
    initString(&stack);

    char* token = strtok(expr, " ");
    while (token) {
        if (isdigit(token[0]) || isalpha(token[0])) {
            strcat(output, token); strcat(output, " ");
        } else if (strcmp(token, "(") == 0) {
            pushString(&stack, token);
        } else if (strcmp(token, ")") == 0) {
            while (stack.top != -1 && strcmp(topString(&stack), "(") != 0)
                { strcat(output, popString(&stack)); strcat(output, " "); }
            popString(&stack); // remove "("
        } else {
            while (stack.top != -1 && precedence(token) <= precedence(topString(&stack))) {
                strcat(output, popString(&stack)); strcat(output, " ");
            }
            pushString(&stack, token);
        }
        token = strtok(NULL, " ");
    }
    while (stack.top != -1) {
        strcat(output, popString(&stack)); strcat(output, " ");
    }
    return output;
}

// --- Conversão para Infixa ---
char* getFormaInFixa(char* expr) {
    static char result[MAX];
    StackString stack;
    initString(&stack);

    char exprCopy[MAX];
    strcpy(exprCopy, expr);
    char* token = strtok(exprCopy, " ");
    while (token) {
        if (isOperator(token)) {
            char* b = popString(&stack);
            char* a = popString(&stack);
            char temp[MAX];
            sprintf(temp, "(%s %s %s)", a, token, b);
            pushString(&stack, temp);
        } else if (isFunction(token)) {
            char* a = popString(&stack);
            char temp[MAX];
            sprintf(temp, "%s(%s)", token, a);
            pushString(&stack, temp);
        } else {
            pushString(&stack, token);
        }
        token = strtok(NULL, " ");
    }
    strcpy(result, popString(&stack));
    return result;
}

// --- Avaliação pós-fixa ---
float getValorPosFixa(char* expr) {
    StackFloat stack;
    initFloat(&stack);

    char exprCopy[MAX];
    strcpy(exprCopy, expr);
    char* token = strtok(exprCopy, " ");
    while (token) {
        if (isOperator(token)) {
            float b = popFloat(&stack);
            float a = popFloat(&stack);
            if (strcmp(token, "+") == 0) pushFloat(&stack, a + b);
            else if (strcmp(token, "-") == 0) pushFloat(&stack, a - b);
            else if (strcmp(token, "*") == 0) pushFloat(&stack, a * b);
            else if (strcmp(token, "/") == 0) pushFloat(&stack, a / b);
            else if (strcmp(token, "^") == 0) pushFloat(&stack, pow(a, b));
        } else if (isFunction(token)) {
            float a = popFloat(&stack);
            pushFloat(&stack, evalFunc(token, a));
        } else {
            pushFloat(&stack, atof(token));
        }
        token = strtok(NULL, " ");
    }
    return popFloat(&stack);
}

float getValorInFixa(char* strInFixa) {
    char temp[MAX];
    strcpy(temp, strInFixa);
    char* postfix = getFormaPosFixa(temp);
    return getValorPosFixa(postfix);
}
