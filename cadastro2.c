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
                break;
            case 3:
                fp = fopen("info.txt", "w");

                if (fp == NULL) {
                    printf("Arquivo não criado.\n");
                    exit(-1);
                }

                c3 = prim;
                while (c3 != NULL) {
                    fwrite(c3->nome, sizeof(char), 40, fp);
                    fwrite(&c3->idade, sizeof(int), 1, fp);
                    c3 = c3->prox;
                }
                fclose(fp);
                break;
            
            case 4:
                fp = fopen("info.txt","r");
                while (!feof(fp))
                {
                if (!pri) 
                {
                    pri = 1;
                    prim = malloc(sizeof(struct cadastro));
                    c1 = prim ;
                    int f = 0;
                    f = fread(prim->nome, sizeof(char),40,fp);
                    if ( f == 40)
                        f = fread(&prim->idade, sizeof(int),1, fp);
                } 
                else 
                {
                    c1->prox = malloc(sizeof(struct cadastro));
                    c1 = c1->prox;
                    int f = 0;
                    f = fread(c1->nome, sizeof(char),40,fp);
                    if ( f == 40)
                        f = fread(&c1->idade, sizeof(int),1, fp);
                }
                }
                fclose(fp);
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
