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
int cont_max=1;
int cont_palavras=0;

void mostrar_opcoes() {
	printf("================================\n");
	printf("  0. Sair\n");
	printf("  1. Inserir palavra\n");
	printf("  2. Consultar Palavra\n");
	printf("  3. Remover Palavra\n");
//	printf("  4. Contar palavras\n");
//	printf("  5. Conta ocorrencias\n");
	printf("  6. Exibe palavras\n");
//	printf("  7. Exibe palavras letra\n");
//	printf("  8. Exibe palavras maior ocorren.\n");
//	printf("  9. Exibe palavras uma ocorren.\n");
//	printf("  10. Extra?");
	printf("================================\n");
	printf("\n");
}

void teste_cont(int cont){
	if(cont > cont_max){
		cont_max = cont;
	} 
}

void insereNodo( NODE* atual, NODE* novo ){
	if(strcmp(atual->palavra,novo->palavra) == 0){
	  	atual->cont++;
	  	teste_cont(atual->cont);
	  	printf("Palavra '%s' ja existe, aumentando cont!\n", novo->palavra);
	  	cont_palavras++;
	  	return;
	}
	else if( strcmp(novo->palavra,atual->palavra) == -1){
		if( atual->esq == NULL ){
			atual->esq = novo;
	 		atual->esq->pai = atual; //seta o pai
	 		printf("Palavra '%s' inserida com sucesso!\n", novo->palavra);
	  		cont_palavras++;
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
	  			cont_palavras++;
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
		cont_palavras++;
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
		NODE* raiz = vet_l[i].prox;
		if(pai==NULL){ 
			raiz = NULL;
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


void escreve_palavras() {
	int i;
	for(i=0; i<26; i++){
		if(vet_l[i].prox != NULL){
			printf("\nPalavras com a letra %c\n", vet_l[i].c);
			escreve(vet_l[i].prox);
		}
	}
}


int main() {
	int i;
	char palavra[50];
	for(i=0;i<26;i++){
		vet_l[i].c = 'A' + i;
		vet_l[i].prox = NULL;
	}
	int op = -1;
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
				getchar();
				printf("Digite a palavra: ");
				gets(palavra);
				NODE* result = pesquisaPalavra(palavra);
				printf("Palavra: %s\nCont: %d\n", result->palavra, result->cont);
				break;
			case 3:
				getchar();
				printf("Digite a palavra a ser removida: ");
				gets(palavra);
				remover(palavra);
				printf("Palavra '%s' removida com sucesso", palavra);
				break;
			case 4:
//				printf("\nQuantidade de palavras: %d\n\n", cont_palavras);
				break;
			case 5:
//				conta_ocorrencias();
				break;
			case 6:
				escreve_palavras();
				printf("\n");
				break;
			case 7:
//				exibe_palavras_letra();
				break;
			case 8:
//				escreve_maior_freq();
				printf("\n");
				break;
			case 9:
//				exibe_palavras_uma_freq();
				break;
			case 10:
				break;
			default:
				printf("Digite uma opcao entre 0-10");
				break;
		}
	}
}                       
