Trabalho Prático - Avaliação de Expressões Matemáticas em C

Este projeto implementa um sistema em linguagem C capaz de avaliar expressões matemáticas nas formas infixa e pós-fixa,
com suporte às operações +, -, *, /, ^ e funções sen, cos, log e raiz.

Arquivos:
- expressao.h: Cabeçalho com as assinaturas das funções. Não deve ser modificado.
- expressao.c: Contém as implementações das conversões e avaliações de expressões.
- main.c: Realiza os testes conforme descrito no enunciado.

Compilação:
gcc expressao.c main.c -o programa -lm

Execução:
./programa

O programa imprime:
- A forma pós-fixa da expressão
- A forma infixa equivalente
- O valor da expressão

Funcionalidades:
- Conversão entre infixa e pós-fixa
- Avaliação de expressões infixas e pós-fixas
- Suporte a funções matemáticas (sen, cos, log, raiz)
- Utilização de pilhas como estrutura de dados
- Modularização em três arquivos: expressao.c, expressao.h e main.c

Todos os testes da tabela do enunciado foram implementados.
