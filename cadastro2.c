#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct cadastro {
    char nome[40];
    int idade;
    struct cadastro *prox;
};

int main(void) {
    struct cadastro *c1 ;
    struct cadastro *c2 ;
    struct cadastro *c3 ;
    struct cadastro *prim = NULL;
    int opc, idade, pri = 0;
    char nome[40];
    FILE *fp;
    while (opc != 5) {
        puts("Bem vindo à criação de cadastro agro-pesca jacaré.\nO que deseja fazer?\n 1 - Criar cadastro\n 2 - Ver cadastros\n 3 - Escrever no txt \n 4 - Carregar a lista (Adiciona no final da atual)\n 5 - Sair");
        scanf("%d", &opc);
        switch (opc) {
            case 1:
                puts("Insira seu primeiro nome:");
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
                if (prim != NULL)
                    c2 = prim;
                else{
                    puts("Nada encontrado");
                    break;
                }
                while (c2 != NULL) {
                    printf("\nNome: %s \n", c2->nome);
                    printf("Idade: %d  \n", c2->idade);
                    c2 = c2->prox;
                }
                free(c2);
                break;
            case 3:
                if ((fp = fopen("info.txt","w")) == NULL){
                    printf("Erro ao criar/encontrar arquivo.");
                    exit(-1);
                    break;
                }
                c3 = prim;
                while (c3 != NULL) {
                    fwrite(c3->nome, sizeof(char), 40, fp);
                    fwrite(&c3->idade, sizeof(int), 1, fp);
                    c3 = c3->prox;
                }
                fclose(fp);
                free(c3);
                break;
            
            case 4:
                if ((fp = fopen("info.txt","r")) == NULL){
                    printf("Lista não encontrada\n");
                   
                    break;
                }

                while (!feof(fp))
                { 
                int f;
                if (!pri) 
                {  f = fread(nome, sizeof(char),40,fp);
                    if ( f == 40)
                        f = fread(&idade, sizeof(int),1, fp);
                    else
                        break; 
                    pri = 1;
                    prim = malloc(sizeof(struct cadastro));
                    c1 = prim ;
                    strcpy(prim->nome, nome);
                    prim->idade = idade;
                          
                } 
                else 
                {    f = fread(nome, sizeof(char),40,fp);
                    if ( f == 40)
                        f = fread(&idade, sizeof(int),1, fp);
                    else 
                        break;  
                    c1->prox = malloc(sizeof(struct cadastro));
                    c1 = c1->prox;
                    strcpy(c1->nome,nome);
                    c1->idade = idade;
                }
                }
                fclose(fp);
                break;
        }
    }
    c1 = prim;
    while (c1 != NULL) {
        struct cadastro *temp = c1;
        c1 = c1->prox;
        free(temp);
    }
    
    return 0;
}
