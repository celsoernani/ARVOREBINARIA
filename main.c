#include <stdio.h>
#include <stdlib.h>
#include <conio.h>

typedef struct NO* arvorebin; //arvore ta recebendo um ponteiro da struct

                    struct NO{
                        int info;
                        struct NO *esq; // crio esquerda e direita na mesma estrutura
                        struct NO *dir;
                                };

//Funcao para criar raiz
arvorebin *criararvore(){
    arvorebin *raiz = (arvorebin*)malloc(sizeof(arvorebin)); //alocando uma memoria do tamanho de uma arvore ou um no
    if (raiz != NULL){
        *raiz = NULL;
    } // ele cria uma arvore vazia e retorna a propria arvore com o tamanho alocado

    return raiz;
}

//Funcao para liberar no
void liberaNO(struct NO* no){
    if (no == NULL){
        return 0;
    }
    liberaNO(no->esq); // usa uma chamada recursiva assim librenado o nos na esquerda
    liberaNO(no->dir); // acontecendo a mesma coisa pela direita
    free(no); // liberando o espeço do nó criado auxiliar
    no = NULL;
}

//Funcao para liberar arvore
void arvorevazia(arvorebin *raiz){
    if (raiz == NULL){
        return;
    }
    liberaNO(*raiz); // liberrando toodos os nos e logo liberando a raiz, o que desfaz a arvore

    free(raiz);
    printf("Arvore esvaziada com sucesso!");
}

        //Funcao que verifica se arvore esta vazia
int vazia(arvorebin *raiz){
    if (raiz == NULL){
        printf("Arvore vazia!\n");
        return 1;
    }
    if (*raiz == NULL){
        printf("Arvore vazia!\n");
        return 1;
    }
    printf("Arvore não vazia!\n");
    return 0;
}

//Funcao que percorre arvore em pré ordem
void preOrdem(arvorebin *raiz){
    if (raiz == NULL){
        return;
    }
    if (*raiz != NULL){
        printf("%d\n", (*raiz)->info); //printa o que tem dentro do
        preOrdem(&((*raiz)->esq)); // vai percorrendo pela esquerda até que toda a arvore seja percorrida
        preOrdem(&((*raiz)->dir));
    }
}

//Função que percorre árvore EM ORDEM
void emOrdem(arvorebin *raiz){
    if (raiz == NULL){
        return; //verifica se é um raiz vazia
    }
    if(*raiz != NULL){
        emOrdem(&((*raiz)->esq));
        printf("%d\n", (*raiz)->info); //compara qual é o menor e vai percorrendo todo o lado esquedo para o direito, printando assim em ordem
        emOrdem(&((*raiz)->dir));
    }
}

//Função que percorre raiz em PÓS ORDEM
void posOrdem(arvorebin *raiz){
    if (raiz == NULL){
        return;
    }
    if (*raiz != NULL){
        posOrdem(&((*raiz)->esq));
        posOrdem(&((*raiz)->dir)); //ele percorre a arvore ao contrario, pegando os filhos dos nos mais internos, vai recebend o prox do prox enderaço e asassim sucessivamente
        printf("%d\n", (*raiz)->info);
    }
}

//Função que insere um elemento na arvore Binária de busca
int insere(arvorebin *raiz, int valor){
    if (raiz == NULL){
        return 0;
    } //verifica se esta fazia
    struct NO *novo; //cria um no auxiliar
    novo = (struct NO*)malloc(sizeof(struct NO));
    if (novo == NULL){
        return 0;
    }
    novo->info = valor; // o no rcebendo o valor e seu esqueda e direita recebe nu,, ja que é um no novo
    novo->dir = NULL;
    novo->esq = NULL;
    if (*raiz == NULL){
        *raiz = novo;
    }
    else{
        struct NO *atual = *raiz; // o atual passa a receber a raiz
        struct NO *ant = NULL; // e o ant recebe null
        while(atual != NULL){
            ant = atual;
            if (valor == atual->info){
                free(novo); //se eles forem iguais ele da free no novo, assim cirando um novo no
                return 0;
            }
            if (valor > atual->info){ // se o valor for maior do que o atual ,ele vai para direita, para obedercer as regras da arvore binaria
                atual = atual->dir;
            }else{ //se nao for ele vai p esqueda
                atual = atual->esq;
            }
        }
        if (valor > ant->info){ //mesmo procedimento
            ant->dir = novo;
        }else{
            ant->esq = novo;
        }
    }
    return 1;
}

struct NO *removendo_atual(struct NO* atual){
    struct NO *no1, *no2;
    if (atual->esq == NULL){
        no2 = atual->dir;
        free(atual);
        return no2;
    }
    no1 = atual;
    no2 = atual->esq;
    while(no2->dir != NULL){
        no1 = no2;
        no2 = no2->dir;
    }

    if (no1 != atual){
        no1->dir = no2->esq;
        no2->esq = atual->esq;
    }
    no2->dir = atual->dir;
    free(atual);
    return no2;
}

//Função que remove um elemento da árvore binária
int remover(arvorebin *raiz, int valor){
    if (raiz == NULL){
        return 0;
    }
    struct NO *ant = NULL; //variavel auxiliar
    struct NO *atual = *raiz; //o atural recebe a raiz parap poder percorrer a arvore toda
    while (atual != NULL){ //enquanto eele for nu, ele continua no laço
        if (valor == atual->info){
            if (atual == *raiz){
                *raiz = removendo_atual(atual);
    //faz uma chamada recursiva para remover o no ja achado
                }
            else{
                if (ant->dir == atual){ //faz a comparação se for maior remove pela a direita usando recursividade, mesmo pensamento do inserir
                    ant->dir = removendo_atual(atual);
                }else{ //mesmo procedimento
                    ant->esq = removendo_atual(atual);
                }
            }
            return 1;
        }
        ant = atual;
        if (valor > atual->info){
            atual = atual->dir; //realocando os nos depois de excluir
        }
        else{//realocando os nos depois de excluir
            atual = atual->esq;
        }
    }
}

//FUnção que faz a consulta de uma arvore binária de pesquisa
int busca(arvorebin *raiz,int valor){
    if (raiz == NULL){
        return 0;
    }
    struct NO *atual = *raiz; //para percorrer a raiz toda
    while (atual != NULL){
        if (valor == atual->info){
            printf("Valor encontrado!\n");
            return 1;
        }
        if (valor > atual->info){
            atual = atual->dir; //procurandp pela direita
        }
        else{
            atual = atual->esq; //procurando pela esquerda
        }
    }
    return 0;
}

void inserirNos(arvorebin *raiz){
int item;
while (1){
    system("cls");
    printf("Digite um valor a ser inserido, -1 pra encerrar\n");
    scanf("%d", &item);
    if (item == -1){
        break;
    }
    insere(raiz, item); //usando chamada recursiva
}
}
int main(){
    arvorebin *arvore; //variavel auxliar
    int escolha, valor,x,y,w,z, opcao;
    while(1){ //menu
        printf("--------------------MENU---------------------------------");
        printf("\n1- CRIAR ARVORE\n");
        printf("\n2- VERIFICAR ARVORE\n");
        printf("\n3- INSERIR\n");
        printf("\n4- CONSULTAR \n");
        printf("\n5- REMOVER\n");
        printf("\n6- ESVAZIAR\n");
        printf("\n7- IMPRIMIR\n");
        printf("\n8 - SAIR DO PROGRAMA\n");
        scanf("%d", &escolha);
        switch (escolha){
        case 1:
            arvore = criararvore();
            printf("arvore vazia criada\n");
            break;
        case 2:
            x = vazia(arvore);
            break;
        case 3:
            inserirNos(arvore);
            break;
        case 4:
            printf("Digite um valor: ");
            scanf("%d", &valor);
            z = busca(arvore, valor);
            break;
        case 5:
            printf("Digite um valor a ser removido: ");
            scanf("%d", &valor);
            w = remover(arvore, valor);
            break;
        case 6:
            arvorevazia(arvore);
            break;
        case 7:
            printf("1)Pré-ordem\n");
            printf("2)Em ordem\n");
            printf("3)Pos-ordem\n");
            printf("4)Sair do programa\n");
            printf("Digite sua opcao: ");
            scanf("%d", &opcao);
            switch(opcao){
            case 1:
                preOrdem(arvore);
                break;
            case 2:
                emOrdem(arvore);
                break;
            case 3:
                posOrdem(arvore);
                break;
            case 4:
                return;
            }
            break;
        case 8:
            return;

        default:
            printf("Insira uma opção válida");
            break;
    }
}
}
