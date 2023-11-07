#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct cadastro {
    char nome[40];
    int idade;
    struct cadastro *prox;
};

int main(void) {
    struct cadastro *c1 = NULL;
    struct cadastro *c2 = NULL;
    struct cadastro *c3 = NULL;
    struct cadastro *c4 = NULL;

    struct cadastro *prim = NULL;
    int opc, idade, pri = 0;
    char nome[40];

    FILE *fp;
    fp = fopen("info.txt", "a+");

    if (fp == NULL) {
        printf("Arquivo não criado.\n");
        exit(-1);
    }

    while (opc != 5) {
        puts("Bem vindo à criação de cadastro agro-pesca jacaré.\nO que deseja fazer?\n 1 - Criar cadastro\n 2 - Ver cadastros\n 3 - Escrever no txt\n 4 - Carregar a lista\n 5 - Sair");
        scanf("%d", &opc);
        switch (opc) {
            case 1:
                puts("Insira seu nome:");
                scanf("%s", nome);
                puts("Insira sua idade:");
                scanf("%d", &idade);
                if (!pri) {
                    pri = 1;
                    prim = malloc(sizeof(struct cadastro));
                    c1 = prim ;
                    strcpy(prim->nome, nome);
                    prim->idade = idade;
                } else {
                    c1->prox = malloc(sizeof(struct cadastro));
                    c1 = c1->prox;
                    strcpy(c1->nome, nome);
                    c1->idade = idade;
                }
                break;
            case 2:
                c2 = prim;
                while (c2 != NULL) {
                    printf("Nome: %s\n", c2->nome);
                    printf("Idade: %d\n", c2->idade);
                    c2 = c2->prox;
                }
                free(c2);
                break;
            case 3:
                c3 = prim;
                while (c3 != NULL) {
                    fwrite(c3->nome, sizeof(char), 40, fp);
                    fwrite(&c3->idade, sizeof(int), 1, fp);
                    c3 = c3->prox;
                }
                free(c3);
            case 4:
                while (c1 != NULL)
                {
                    if (pri == 0 ){
                    prim = malloc(sizeof(struct cadastro));
                    c1=prim;
                    fread(prim->nome, sizeof(char), 40, fp);
                    fread(&prim->idade, sizeof(int), 1 , fp);
                    }
                    else{
                        c1->prox = malloc(sizeof(struct cadastro));
                        c1 = c1->prox;
                        fread(prim->nome, sizeof(char), 40, fp);
                        fread(&prim->idade, sizeof(int), 1 , fp);

                    }
                }

                break;
        }
    }
    printf("%s", prim->nome);
    fclose(fp);
    c1 = prim;
    while (c1 != NULL) {
        struct cadastro *temp = c1;
        c1 = c1->prox;
        free(temp);
    }

    return 0;
}
