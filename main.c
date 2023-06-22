#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <conio.h>
struct node{
	int cont;
	char palavra[100];
	struct node *esq;
    struct node *dir;
    struct node *pai;
};

typedef struct node NODE;

struct vetor_letras{
	char c;
	NODE* prox;
};

typedef struct vetor_letras LETRAS;

LETRAS vet_l[26];
int maior_cont;

void mostrar_opcoes() {
	printf("================================\n");
	printf("  0. Sair\n");
	printf("  1. Inserir palavra\n");
	printf("  2. Inserir Frase\n");
	printf("  3. Consultar Palavra\n");
	printf("  4. Remover Palavra\n");
	printf("  5. Contar palavras\n");
	printf("  6. Conta ocorrencias\n");
	printf("  7. Exibe palavras\n");
	printf("  8. Exibe palavras letra\n");
	printf("  9. Exibe palavras maior ocorrencia.\n");
	printf("  10. Exibe palavras uma ocorrencia.\n");
	printf("================================\n");
	printf("\n");
}


void insereNodo( NODE* atual, NODE* novo ){
	if(strcmp(atual->palavra,novo->palavra) == 0){
	  	atual->cont++;
	  	printf("Palavra '%s' ja existe, aumentando cont!\n", novo->palavra);
	  	return;
	}
	else if( strcmp(novo->palavra,atual->palavra) == -1){
		if( atual->esq == NULL ){
			atual->esq = novo;
	 		atual->esq->pai = atual; //seta o pai
	 		printf("Palavra '%s' inserida com sucesso!\n", novo->palavra);
	  	}
	  	else{
	  		insereNodo( atual->esq, novo);
		}
	}
	else{
		if( atual->dir == NULL){
	  			atual->dir = novo;
	  			atual->dir->pai = atual;
	  			printf("Palavra '%s' inserida com sucesso!\n", novo->palavra);
	  		}
	  		else{
	  		  insereNodo( atual->dir, novo );
			  }
	    }
}

void insere_palavra(char palavra[50]){
	NODE* novo;
    NODE* raiz;
    novo = (NODE*) malloc(sizeof(NODE));
    strcpy(novo->palavra, palavra);
    novo->esq = NULL;
    novo->dir = NULL;
    novo->pai = NULL;
    novo->cont = 1;
    char l = toupper(palavra[0]);
    int r = l - 'A';
	if(vet_l[r].prox == NULL){
		vet_l[r].prox = novo;
		printf("Palavra '%s' inserida com sucesso!\n", novo->palavra);
	}
	else{
		  insereNodo( vet_l[r].prox, novo );
	}

}
	NODE* pesquisa( NODE* raiz, char palavra[50] ){
        NODE* res = NULL;
		if( raiz != NULL ){

		  if(strcmp(raiz->palavra, palavra)==0){
             res = raiz;
          }
          else{
               if(strcmp(raiz->palavra, palavra) == 1){
                    res = pesquisa( raiz->esq, palavra );
               }
               else{
                    res = pesquisa( raiz->dir, palavra );
               }
          	}
        }
        return res;
	}
	NODE* pesquisaPalavra( char palavra[50] ){
		char c = toupper(palavra[0]);
		int i = c - 'A';
		NODE* raiz = vet_l[i].prox;
		NODE* rest = pesquisa( raiz, palavra );
		return rest;
	}

    void removeFolha(NODE* atual){
		NODE* pai = atual->pai;
		char aux[50];
		strcpy(aux, atual->palavra);
		char c = toupper(aux[0]);
		int i = c - 'A';
		if(pai==NULL){
			vet_l[i].prox = NULL;
		}
		else{
			if(pai->esq == atual){
				pai->esq = NULL;
			}
			else{
				pai->dir=NULL;
			}
		}
		free(atual);
	}
	void removeUmFilho( NODE* atual ){
		NODE* pai = atual->pai;
		char aux[50];
		strcpy(aux, atual->palavra);
		char c = toupper(aux[0]);
		int i = c - 'A';
		NODE* raiz = vet_l[i].prox;
		if(pai==NULL){
			if(atual->esq != NULL){
				raiz = atual->esq;
			}
			else{
				raiz = atual->dir;
			}
			raiz->pai=NULL;
		}
		else{
			if(atual->esq == NULL){
				if(pai->dir == atual){
					pai->dir = atual->dir;
				}
				else{
					pai->esq=atual->dir;
				}
				atual->dir->pai = pai;
			}
			else{
				if(pai->dir==atual){
					pai->dir=atual->esq;
				}
				else{
					pai->esq=atual->esq;
				}
				atual->esq->pai = pai;
			}
            free(atual);
		}
	}

    void removeDoisFilhos( NODE* atual ){
		NODE* aux = atual->esq;
		NODE* pai = NULL;

		while(aux->dir!= NULL){
			aux = aux->dir;
		}
		strcpy (atual->palavra, aux->palavra);
		if((aux->esq == NULL) && (aux->dir == NULL)){
            removeFolha(aux);
		}
		else{
            removeUmFilho(aux);
		}
	}
    void remover(char palavra[50]){
    	NODE* atual;

    	atual = pesquisaPalavra( palavra );
    	if(atual == NULL){
    		printf("A palavra %s nao esta presente. ", palavra);
		}
		else if((atual->esq == NULL) && (atual->dir == NULL)){
    		removeFolha(atual);
		}
		else{
			if((atual->esq != NULL) && (atual->dir != NULL)){
				removeDoisFilhos( atual );
			}
    		else{
    			removeUmFilho( atual );
			}
		}

    }

void escreve(NODE* raiz){
	if( raiz == NULL ){
		return;
	}
		escreve(raiz->esq);
		printf("%s\n",raiz->palavra);
		escreve(raiz->dir);
}

void insere_frase(){
    int i, j=0, k=0;
    char frase[10000];
    char palavra[100];
   printf("Digite a frase: ");
   getchar();
   gets(frase);
    printf("\nFrase: %s\n\n",frase);
    while(frase[k]==' '){
         k++;
        }

    for(i=k;frase[i]!='\0';i++){
        if(frase[i]==',' || frase[i] == '.' || frase[i] == ' '|| frase[i]=='!' || frase[i]=='?' || frase[i]==':' || frase[i]==';'){
            palavra[j+1] == '\0';
            insere_palavra(palavra);
            while(j!=0){
                palavra[j] = '\0';
                j--;
            }
            while(frase[i+1]==' '){
            i++;
            }
        }
        else{
            palavra[j]=frase[i];
            j++;
        }
    }
    if(strcmp(palavra, "\0")){
    palavra[j+1] == '\0';
    insere_palavra(palavra);
    }
    printf("\n");
}


void escreve_palavras() {
	int i;
	for(i=0; i<26; i++){
		if(vet_l[i].prox != NULL){
			printf("\nPalavras com a letra %c\n", vet_l[i].c);
			escreve(vet_l[i].prox);
		}
	}
}
void conta_palavras(NODE *raiz, int *cont){
		if( raiz == NULL ){
		return;
	}
		conta_palavras(raiz->esq, cont);
		*cont = *cont + 1;
		conta_palavras(raiz->dir, cont);
}
void conta_ocorrencias(NODE *raiz, int *cont){
		if( raiz == NULL ){
		return;
	}
		conta_ocorrencias(raiz->esq, cont);
		*cont = *cont + raiz->cont;
		conta_ocorrencias(raiz->dir, cont);
}

void exibe_palavras_letra(NODE *raiz){
		if( raiz == NULL ){
		return;
	}
		exibe_palavras_letra(raiz->esq);
		printf("%s\n", raiz->palavra);
		exibe_palavras_letra(raiz->dir);
}
void escreve_uma_ocorr(NODE *raiz) {
		if( raiz == NULL ){
		return;
	}
		escreve_uma_ocorr(raiz->esq);
		if(raiz->cont == 1){
		printf("%s\n", raiz->palavra);
		}
		escreve_uma_ocorr(raiz->dir);
}
void procura_cont_max(NODE* raiz){
	if( raiz == NULL ){
		return;
	}
		procura_cont_max(raiz->esq);
		if(maior_cont < raiz->cont){
			maior_cont = raiz->cont;
		}
		procura_cont_max(raiz->dir);
}

void escreve_cont_max(NODE* raiz){
		if( raiz == NULL ){
		return;
	}
		escreve_cont_max(raiz->esq);
		if(maior_cont == raiz->cont){
			printf("%s\n", raiz->palavra);
		}
		escreve_cont_max(raiz->dir);
}

int main() {
	int i;
	char palavra[50];
	char v;
	for(i=0;i<26;i++){
		vet_l[i].c = 'A' + i;
		vet_l[i].prox = NULL;
	}
	int op = -1;
	int cont = 0;
	while(op != 0){
		mostrar_opcoes();
		printf("Digite o numero da opcao: ");
		scanf("%d",&op);
		switch(op){
			case 0:
				printf("Saindo do programa...");
				break;
			case 1:
				getchar();
				printf("Digite a palavra: ");
				gets(palavra);
				printf("\n");
				insere_palavra(palavra);
				printf("\n");
				break;
			case 2:
			    insere_frase();
				break;
			case 3:
				getchar();
				printf("Digite a palavra: ");
				gets(palavra);
				NODE* result = pesquisaPalavra(palavra);
				printf("Palavra: %s\nCont: %d\n", result->palavra, result->cont);
				break;
			case 4:
				getchar();
				printf("Digite a palavra a ser removida: ");
				gets(palavra);
				remover(palavra);
				printf("Palavra '%s' removida com sucesso\n", palavra);
				break;
			case 5:
				cont = 0;
				for(i=0; i<26; i++){
					if(vet_l[i].prox != NULL){
						conta_palavras(vet_l[i].prox, &cont);
					}
				}
				printf("Numero de palavras: %d\n", cont);
				break;
			case 6:
				cont = 0;
				for(i=0; i<26; i++){
					if(vet_l[i].prox != NULL){
						conta_ocorrencias(vet_l[i].prox, &cont);
					}
				}
				printf("Numero total de ocorrencias: %d\n", cont);
				break;
			case 7:
				escreve_palavras();
				printf("\n");
				break;
			case 8:
				getchar();
				printf("Digite a letra: ");
				scanf("%c", &v);
				v = toupper(v);
				i = v - 'A';
				exibe_palavras_letra(vet_l[i].prox);
				printf("\n");
				break;
			case 9:
				maior_cont = 0;
				for(i=0; i<26; i++){
					procura_cont_max(vet_l[i].prox);
				}
				printf("\nMaior cont: %d\n", maior_cont);
				for(i=0; i<26; i++){
					escreve_cont_max(vet_l[i].prox);
				}
				printf("\n");
				break;
			case 10:
				for(i=0; i<26; i++){
					if(vet_l[i].prox != NULL){
						escreve_uma_ocorr(vet_l[i].prox);
					}
				}
				break;
			default:
				printf("Digite uma opcao entre 0-10");
				break;
		}
	}
}
