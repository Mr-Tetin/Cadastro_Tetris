#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>

typedef struct pecas{
    char *tipo;
    char cor[15];
    int tamanho;
    int peso;
    int id;
    char borda;
}pecas;

typedef struct No{
    pecas pecas;
    struct No *prox;
}No;

No *inicio = NULL; // Diz que o incio vai comecar como VAZIO, ou seja, toda estrutura comeca vazia
int tam; //tamanho da lista, vai ajudar quando usar for

void menu(){
    printf("+-------------------------------------------+\n");
    printf("|          +----------------------+         |\n");
    printf("|          |         MENU         |         |\n");
    printf("|          +----------------------+         |\n");
    printf("|          +----------------------+         |\n");
    printf("|          |  1-CADASTRAR PECAS   |         |\n");
    printf("|          |                      |         |\n");
    printf("|          |  2-LISTAR PECAS      |         |\n");
    printf("|          |                      |         |\n");
    printf("|          |  3-REOGARNIZAR PECAS |         |\n");
    printf("|          |                      |         |\n");
    printf("|          |  4-REMOVER PECAS     |         |\n");
    printf("|          |                      |         |\n");
    printf("|          |  5-SAIR              |         |\n");
    printf("|          +----------------------+         |\n");
    printf("+-------------------------------------------+\n\n");
}
void menu_pecas(){
    printf("+----------------------+\n");
    printf("|  [1] - Peca T        |\n");
    printf("|                      |\n");
    printf("|  [2] - Peca S1       |\n");
    printf("|                      |\n");
    printf("|  [3] - Peca S2       |\n");
    printf("|                      |\n");
    printf("|  [4] - Peca I        |\n");
    printf("|                      |\n");
    printf("|  [5] - Peca L1       |\n");
    printf("|                      |\n");
    printf("|  [6] - Peca L2       |\n");
    printf("|                      |\n");
    printf("|  [7] - Peca Q        |\n");
    printf("+----------------------+\n\n");
}
void liberar_memoria(){
    No *aux; //cria um ponteiro auxiliar(aux)

    while(inicio != NULL){
        aux = inicio; //aux aponta pra o no incial
        inicio = inicio->prox; // incio aponta para o proximo(o ponteiro de incio aponta para o proximo), mas o aux ainda fica no inicio
        free(aux); //como aux ainda ta no incio a gnt libera ele
    }
}
void delay(){
    clock_t inicio = clock();
    while ((clock() - inicio) < (CLOCKS_PER_SEC / 2));
}
void limpar_tela(){

    printf("\033[H\033[J");
    fflush(stdout);
}
int verificar_string(const char *str){
    for(int i = 0; str[i] != '\0'; i++){
        if(isdigit(str[i])){
            return 0;
        }
    }
    return 1;
}
void remover_peca(int ID){
    No *auxiliar = inicio;
    No *anterior = NULL;

    while(auxiliar != NULL){
        if(auxiliar->pecas.id == ID){
            if(anterior == NULL){
                inicio = inicio->prox;
            }else{
                anterior->prox = auxiliar->prox;
            }
            free(auxiliar);
            tam--;
            printf("\nPeca removida com sucesso\n");
            return;
        }
        anterior = auxiliar;
        auxiliar = auxiliar->prox;
    }
    printf("\n\nID da Peca nao encontrado\n");

}
int main(){
    int opcao;
    int tipo;
    char *tipos[] = {"T", "S1", "S2", "I", "L1", "L2", "Q"};
    while(1){
        menu();
        printf("O que deseja fazer: ");
        while(1){
            if(scanf("%d", &opcao) != 1){
                printf("Digite somente NUMEROS: ");
                while(getchar() != '\n');
                continue;
            }if(opcao < 1 || opcao > 5){
                printf("Digite apenas numeros correspondente as opcoes(1 a 4): ");
                continue;
            }
            else{
                break;
            }
        }
        printf("\n");
        if(opcao >= 1 && opcao <=5){
            if(opcao == 1){

                No *novo = malloc(sizeof(No)); //cria um ponteiro do tipo No que aloca um tamanho na memoria do tamanho correspondente ao tamanho(sizeof) do No
                novo->prox = inicio;
                inicio = novo;
    
                while(1){
                    menu_pecas();
                    printf("Digite o tipo da peca: ");
                    if(scanf("%d", &tipo) != 1){
                        printf("\nDigite somente NUMEROS relacionado aos tipos\n\n");
                        while(getchar() != '\n');
                        continue;
                    }
                    else if(tipo >= 1 && tipo <= 7){
                        novo->pecas.tipo = tipos[tipo - 1];
                        printf("\nPeca %s adicionada corretamente.\n\n", novo->pecas.tipo);
                        break;
                    }else if(tipo < 1 || tipo > 7){
                        printf("\nTipo invalido. Digite somente tipos validos(listados).\n\n");
                        free(novo);
                    }
                }
                getchar();
                printf("Digite a cor da peca: ");
                fgets(novo->pecas.cor, sizeof(novo->pecas.cor), stdin);
                while(1){
                    if(verificar_string(novo->pecas.cor) == 0){
                        printf("\nDigite somente PALAVRAS(cores): ");
                        fgets(novo->pecas.cor, sizeof(novo->pecas.cor), stdin);
                    }else{
                        break;
                    }
                }
                novo->pecas.cor[strcspn(novo->pecas.cor, "\n")] = '\0';
                printf("\n");
                printf("Digite o tamanho da peca: ");
                while(1){
                    if(scanf("%d", &novo->pecas.tamanho) != 1){
                        printf("\nDigite somente NUMEROS(tamanho): ");
                        while(getchar() != '\n');
                        continue;
                    }else{
                        break;
                    }
                }
                
                printf("\n");
                printf("Digite o peso da peca: ");
                while(1){
                    if(scanf("%d", &novo->pecas.peso) != 1){
                        printf("\nDigite somente NUMEROS(peso): ");
                        while(getchar() != '\n');
                        continue;
                    }else{
                        getchar();
                        break;
                    }
                }
                printf("\n");
                printf("Digite se tem borda ou nao(s/n): ");
                while(1) {
                    scanf(" %c", &novo->pecas.borda);
                    if(novo->pecas.borda == 's' || novo->pecas.borda == 'n' || novo->pecas.borda == 'S' || novo->pecas.borda == 'N'){
                        break;
                    }
                    printf("\nDigite somente 's/S' para sim ou 'n/N' para nao: ");
                }
                printf("\n");
                tam++;
                novo->pecas.id = tam;
            }
    
            else if(opcao == 2){
                if(inicio == NULL){
                    printf("Nao existem pecas para listar ainda.\n\n");
                }else{
                    printf("\nAtualmente existem: %d peca(s)\n", tam);
                    No *auxiliar = inicio; //criacao de um ponteiro q aponte para coisas do tipo No nesse caso o /inicio/ e ele vai ajudar a sempre movimentar o for para frente e printar sempre o que vem depois
                    for(int i = 0; i < tam; i++){
                        //auxiliar = auxiliar->pecas.id;
                        printf("\n==============================\n");
                        printf("     O tipo da peca e %s\n\n", auxiliar->pecas.tipo);
                        printf("     A peca tem o ID %d\n", auxiliar->pecas.id);
                        printf("     A cor da peca e: %s\n     O tamanho da peca e: %d\n     O peso da peca e: %d\n", auxiliar->pecas.cor, auxiliar->pecas.tamanho, auxiliar->pecas.peso);
                        if(auxiliar->pecas.borda == 'n' || auxiliar->pecas.borda == 'N'){
                            printf("     A peca nao possui borda\n");
                        }else if(auxiliar->pecas.borda == 's' || auxiliar->pecas.borda == 'S'){
                            printf("     A peca possui borda\n");
                        }
                        printf("==============================\n");
                        auxiliar = auxiliar->prox; //o ponteiro auxiliar aponta agora para o proximo, fazendo assim o for printar o que o auxiliar esta apontando que no caso ele atualiza e acaba quando o i chega no tam, ou seja, não existem mais nós.
                        printf("\n");
                    }
                }
                
            }
            else if(opcao == 3){
                if(inicio == NULL){
                    printf("Nao existe pecas para organizar.\n\n");
                    continue;
                }
                No *aux1 = inicio;
    
                for(int i = 0; i < tam; i++){
                    No *aux2 = aux1->prox;
                    while (aux2 != NULL) {
                        if (strcmp(aux1->pecas.tipo, aux2->pecas.tipo) > 0) {
                            pecas temp = aux1->pecas;
                            aux1->pecas = aux2->pecas;
                            aux2->pecas = temp;
                        }
                        aux2 = aux2->prox;
                    }
                    aux1 = aux1->prox;
                }
                printf("Pecas Organizadas.\n\n");
            }else if(opcao == 4){
                int qual_id;
                printf("Digite o ID da peca a qual deseja remover: ");
                while(1){
                    if(scanf("%d", &qual_id) != 1){
                        printf("\nDigite somente NUMEROS: ");
                        while(getchar() != '\n');
                        continue;
                    }else{
                        break;
                    }
                }
                remover_peca(qual_id);
            }
            else if(opcao == 5){
                limpar_tela();
                printf("Encerrando |");
                delay();
                limpar_tela();
                printf("Encerrando /");
                delay();
                limpar_tela();
                printf("Encerrando --");
                delay();
                limpar_tela();
                printf("Encerrando \\");
                delay();
                limpar_tela();
                printf("Encerrando |");
                delay();
                limpar_tela();    
                printf("Encerrando /");
                limpar_tela();
                liberar_memoria();
                break;
            }
        }
    }
    return 0;
}
