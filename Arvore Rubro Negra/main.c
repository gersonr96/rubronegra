//
//  main.c
//  Arvore Rubro Negra
//
//  Created by Gerson Rodrigo on 25/05/17.
//  Copyright © 2017 Gerson Rodrigo. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <time.h>


#define A 1000
#define B 10000
#define C 100000

typedef struct NO{
    int numero;
    int cor;
    struct NO *esquerda;
    struct NO *direito;
    struct NO *pai;
} no;

void criarArvore(no **raiz){
    *raiz = (no*)calloc(1,sizeof(no));
    (*raiz)->numero   = -1111;
    (*raiz)->direito  = NULL;
    (*raiz)->esquerda = NULL;
    (*raiz)->pai      = NULL;
    (*raiz)->cor      = 1;
}




/*Rotacao */
// Rotação à esquerda
void leftRotate(no *raiz,no *novo){
    no * aux;
    aux = (no*)calloc(1,sizeof(no));
    aux=novo->direito;
    novo->direito=aux->esquerda;
    if(aux->esquerda != raiz){
        aux->esquerda->pai=novo;
    }
    aux->pai=novo->pai;
    if(novo->pai == raiz){
        novo->pai->direito=aux;
    }else{
        if(novo==novo->pai->esquerda){
            novo->pai->esquerda=aux;
        }else{
            novo->pai->direito=aux;
        }
    }
    aux->esquerda=novo;
    novo->pai=aux;
}

// Rotação à direita
void rightRotate(no *raiz,no *novo){
    no *auz;
    auz = (no*)calloc(1,sizeof(no));
    auz=novo->esquerda;
    novo->esquerda = auz->direito;
    if(auz->direito!= raiz){
        auz->esquerda->pai=novo;
    }
    auz->pai=novo->pai;
    if(novo->pai == raiz){
        novo->pai->esquerda=auz;
    }else{
        if(novo==novo->pai->esquerda){
            novo->pai->esquerda=auz;
        }else{
            novo->pai->esquerda=auz;
        }
    }
    auz->esquerda=novo;
    novo->pai = auz;
}




// Trocar valores
void trocaDados(no *a, no *b){
    int x = a->numero;
    a->numero = b->numero;
    b->numero = x;
}

// Obter elemento da extrema direita
no *maisDireita(no *aa,no *a){
    no *aux = a;
    while(aux->direito != aa) aux = aux->direito;
    return aux;
}

// Obter elemento da extrema esquerda
no *maisEsquerda(no *aa,no *a){
    no *aux = a;
    while(aux->esquerda != aa) aux = aux->esquerda;
    return aux;
}





// Balanceamento para inserção de uma árvore rubro negra
void  balancear(no *raiz, no *novo){
    no *pai = novo->pai ,*tio, *avo;
    while(pai->cor==0){
        avo=pai->pai;
        // Esquerda do avô
        if(novo->numero < avo->numero){
            tio=avo->direito;
            // Caso 1
            if(tio->cor==0){
                pai->cor=1;
                tio->cor=1;
                avo->cor=0;
                novo=avo;
                pai=novo->pai;
            }else{
                // Caso 2
                if(novo == pai->direito){
                    leftRotate(raiz,pai);
                    novo=pai;
                    pai=novo->pai;
                }
                // Caso 3
                pai->cor=1;
                avo->cor=0;
                rightRotate(raiz,avo);
            }
            // Direita do avô
        }else{
            tio=avo->esquerda;
            // Caso 1
            if(tio->cor==0){
                pai->cor=1;
                tio->cor=1;
                avo->cor=0;
                novo=avo;
                pai=novo->pai;
            }else{
                // Caso 2
                if(novo==pai->esquerda){
                    rightRotate(raiz,pai);
                    novo=pai;
                    pai=novo->pai;
                }
                // Caso 3
                pai->cor=1;
                avo->cor=0;
                leftRotate(raiz,avo);
            }
        }
    }
    // Raiz de preto
    raiz->direito->cor=1;
}



void inserir(no *Arvore, int numero){
    
    no *newNo, *aux, *newPai;
    newNo = (no*)calloc(1, sizeof(no));
    newNo->numero = numero;
    newNo->esquerda = Arvore;
    newNo->direito = Arvore;
    newNo->pai = NULL;
    newNo->cor = 0;
    
    
    /* verifica se existe no na arvore*/
    if (Arvore->direito == NULL){
        Arvore->direito = newNo;
        newNo->pai = Arvore;
        //Balancea a arvore
        balancear(Arvore, newNo);
    }
    
    aux = Arvore->direito;
    
    //procura a posicao do no
    
    while (aux != Arvore) {
        newPai = aux;
        if (numero < aux->numero){
            aux = aux->esquerda;
        }else{
            aux = aux->direito;
        }
    }
    
    // vai inserir na direita do pai
    if (numero > newPai->numero){
        newPai->direito = newNo;
    }else{
        // inserir na esquerda
        newPai->esquerda = newNo;
    }
    //NovoPai
    newNo->pai = newPai;
    
    //Balancear
    balancear(Arvore, newNo);
    
    
}
void inseirNaArvore(no **raiz, int TAM){
    for (int i = 0; i < TAM; i++){
        inserir(*raiz, i);
    }
    
}




//Verificar se a arvre esta vazia
int verificar(no *raz){
    if (raz == NULL){
        return 1;
    }else{
        return  0;
    }
}

//FazerProcura na Arvore

void buscar(no *raiz, int numero){
    
    if (verificar(raiz)){
        printf("Numero não existe");
    }else if (raiz->numero == numero){
        printf("Numero encontrado");
    }else if (numero > raiz->numero){
        buscar(raiz->direito, numero);
    }else{
        buscar(raiz->esquerda, numero);
    }
}


// Balancear na remocao



void balancearremocao(no *arv,no *arv2,no *pai, int numero){
    no *aaa = NULL;
    while(arv2 != arv && arv2->cor == 1){
        if(arv2->numero < pai->numero){
            aaa->pai->direito;
            if(aaa->cor == 0){
                // Caso 1
                aaa->cor=1;
                pai->cor=0;
                leftRotate(arv,pai);
                aaa=arv2->pai->direito;
            }
            if(aaa->direito->cor == 1 && aaa->esquerda->cor == 1){
                // Caso 2
                aaa->cor=0;
                arv2=arv2->pai;
            }else{
                if(aaa->esquerda->cor == 0){
                    // Caso 3
                    aaa->esquerda->cor=1;
                    aaa->cor=0;
                    rightRotate(arv,aaa);
                    aaa=arv2->pai->direito;
                }
                // Caso 4
                aaa->cor=pai->cor;
                pai->cor=1;
                aaa->direito->cor=1;
                leftRotate(arv,arv2->pai);
                arv2=arv;
            }
        }else{
            aaa->pai->esquerda;
            if(aaa->cor == 0){
                // Caso 1
                aaa->cor=1;
                pai->cor=0;
                rightRotate(arv,pai);
                aaa=arv2->pai->esquerda;
            }
            if(aaa->direito->cor == 1 && aaa->esquerda->cor == 1){
                // Caso 2
                aaa->cor=0;
                arv2=arv2->pai;
            }else{
                if(aaa->direito->cor == 0){
                    // Caso 3
                    aaa->direito->cor=1;
                    aaa->cor=0;
                    leftRotate(arv,aaa);
                    aaa=arv2->pai->esquerda;
                }
                // Caso 4
                aaa->cor=pai->cor;
                pai->cor=1;
                aaa->esquerda->cor=1;
                rightRotate(arv,arv2->pai);
                arv2=arv;
            }
        }
    }
    arv2->cor=1;
}



//Remover
void remover(no *raiz, no *raizb, int numero){
  
    if(raizb == raiz){
        return;
    }
    
    no *AA;
    no *BB;
    
    // Variável que recebe o pai do elemento que será removido
    no *npai;
    
    // Caso o elemento seja igual ao valor do nó
    if(raizb->numero == numero){
        // Guardar o valor do pai do nó que será removido
        npai = raizb->pai;
        
        // Se o nó não possui filhos
        if(raizb->direito  == raiz && raizb->esquerda == raiz){
            AA=raizb;
            BB=raiz;
            if(raizb->numero < npai->numero){
                npai->esquerda=raiz;
            }else{
                npai->direito =raiz;
            }
        }else{
            // Se o nó possui 1 filho
            if(raizb->direito  != raiz ^ raizb->esquerda != raiz){
                AA=raizb;
                // Nó que será removido está a esquerdauerda de seu pai
                if(raizb->numero < npai->numero){
                    
                    // Verificar se o nó que será removido possui um filho à esquerdauerda ou à direita
                    if(raizb->direito  != raiz){
                        BB=AA->direito ;
                        npai->esquerda=raizb->direito ;
                    }else{
                        BB=AA->esquerda;
                        npai->esquerda=raizb->esquerda;
                    }
                    
                    // Definir novo pai
                    npai->esquerda->pai=npai;
                    
                    // Filho que será removido está a direita de seu pai
                }else{
                    
                    // Verificar se o nó que será removido possui um filho à esquerdauerda ou à direita
                    if(raizb->direito  != raiz){
                        BB=AA->direito ;
                        npai->direito =raizb->direito ;
                    }else{
                        BB=AA->esquerda;
                        npai->direito =raizb->esquerda;
                    }
                    
                    // Definir novo pai
                    npai->direito ->pai=npai;
                }
                
                // Se o nó possui 2 filho
            }else{
                // Sucessor
                AA = maisEsquerda(raiz,raizb->direito );
                BB=AA->direito ;
                raizb->numero=AA->numero;
                raizb->cor=AA->cor;
                if(BB == raiz){
                    if(AA->pai->numero > AA->numero){
                        AA->pai->esquerda=raiz;
                    }else{
                        AA->pai->direito =raiz;
                    }
                }else{
                    if(AA->pai->numero > AA->numero){
                        AA->pai->esquerda=BB;
                    }else{
                        AA->pai->direito =BB;
                    }
                }
            }
        }
       balancearremocao(raiz,BB,BB->pai,raizb->numero);
        
        
        // Caso não encontre o nó percorre a árvore recursivamente
    }else{
        if(numero > (raizb->numero)){
            remover(raiz, raizb->direito, numero);
        }else{
            remover(raiz, raizb->esquerda, numero);
        }
    }
    
}


void main(){
    
    no *raiz1;
    no *raiz2;
    no *raiz3;
    double tempo1;
    double tempo2;
    double tempo3;
    
    criarArvore(&raiz1);
    criarArvore(&raiz2);
    criarArvore(&raiz3);
    clock_t inicial, final;
    
    
    
    
    /* não repetir o numeros*/
    int *VA = (int*)(malloc(A*sizeof(int)));
    int *VB = (int*)(malloc(B*sizeof(int)));
    int *VC = (int*)(malloc(C*sizeof(int)));
    
    int numero;
    int maiorA = A;
    int menorA = 0;
    int maiorB = B;
    int menorB = 0;
    int maiorC = C;
    int menorC = 0;
    srand((unsigned)time(0));
    numero =   rand()%(maiorA-menorA+1) + menorA;
        
    
      
    
    
    
    // Inserção
    
    inicial = clock();
   inseirNaArvore(&raiz1, A);
    final = clock();
    
    tempo1 = ((double)(final - inicial)/CLOCKS_PER_SEC);
    
    
    inicial = clock();
   inseirNaArvore(&raiz2, B);
    final = clock();
    tempo2 = ((double)(final - inicial)/CLOCKS_PER_SEC);
    
    inicial = clock();
   inseirNaArvore(&raiz3, C);
    final = clock();
    
    tempo3 = ((double)(final - inicial)/CLOCKS_PER_SEC);
    
    
    
    
    
    printf("\nInserir: \n1000 = %f\n10000 = %f\n100000 = %f", tempo1, tempo2,tempo3);
    printf("\n\n");
    
    // Remoção
    
    inicial = clock();
    numero =   rand()%(maiorA-menorA+1) + menorA;
    remover(raiz1,raiz1,numero );  //inserir(&raiz1, i);
    
    final = clock();
    
    tempo1 = ((double)(final - inicial)/CLOCKS_PER_SEC);
    inicial = clock();
    
    numero =   rand()%(maiorB-menorB+1) + menorB;
    remover(raiz2,raiz2,numero ); //inserir(&raiz2, i);
    
    final = clock();
    
    tempo2 = ((double)(final - inicial)/CLOCKS_PER_SEC);
    
    inicial = clock();
    
    numero =   rand()%(maiorC-menorC+1) + menorC;
    
    remover(raiz3,raiz3,numero );   // inserir(&raiz3, i);
    
    final = clock();
    
    tempo3 = ((double)(final - inicial)/CLOCKS_PER_SEC);
    
    
    
    
    printf("\nRemover Existe: \n1000 = %f\n10000 = %f\n100000 = %f", tempo1, tempo2,tempo3);
    
    printf("\n\n");
    
    inicial = clock();
    
    remover(raiz1,raiz1,A+1);  //inserir(&raiz1, i);
    
    final = clock();
    
    tempo1 = ((double)(final - inicial)/CLOCKS_PER_SEC);
    
    inicial = clock();
    
    
    remover(raiz2,raiz2,B+1 );  //inserir(&raiz2, i);
    
    final = clock();
    tempo2 = ((double)(final - inicial)/CLOCKS_PER_SEC);
    
    inicial = clock();
    
    
    remover(raiz3,raiz3,C+1); //inserir(&raiz2, i);
    
    final = clock();
    tempo3 = ((double)(final - inicial)/CLOCKS_PER_SEC);
    
    
    printf("\nRemover Não existe: \n1000 = %f\n10000 = %f\n 3 = %f", tempo1, tempo2,tempo3);
    
    printf("\n\n");
    
    // busca
    inicial = clock();
    numero =   rand()%(maiorA-menorA+1) + menorA;
    buscar(&raiz1, numero );  //inserir(&raiz1, i);
    
    final = clock();
    
    
    tempo1 = ((double)(final - inicial)/CLOCKS_PER_SEC);
    inicial = clock();
    
    numero =   rand()%(maiorB-menorB+1) + menorB;
    buscar(&raiz2, numero);  //inserir(&raiz2, i);
    
    final = clock();
    
    tempo2 = ((double)(final - inicial)/CLOCKS_PER_SEC);
    
    inicial = clock();
    
    numero =   rand()%(maiorC-menorC+1) + menorC;
    buscar(&raiz3, numero);   // inserir(&raiz3, i);
    
    final = clock();
    
    tempo3 = ((double)(final - inicial)/CLOCKS_PER_SEC);
    
    
    
    
    printf("\nBusca Existe: \n1000 = %f\n10000 = %f\n100000 = %f", tempo1, tempo2,tempo3);
    
    printf("\n\n");
    
    inicial = clock();
    
    buscar(raiz1, A + 1 );  //inserir(&raiz1, i);
    
    final = clock();
    
    tempo1 = ((double)(final - inicial)/CLOCKS_PER_SEC);
    
    inicial = clock();
    
    
    buscar(raiz2, B + 1);  //inserir(&raiz2, i);
    
    final = clock();
    tempo2 = ((double)(final - inicial)/CLOCKS_PER_SEC);
    
    inicial = clock();
    
    
    buscar(raiz3, C + 1);  //inserir(&raiz2, i);
    
    final = clock();
    tempo3 = ((double)(final - inicial)/CLOCKS_PER_SEC);
    
    
    printf("\nBuscar Não existe: \n1000 = %f\n10000 = %f\n100000 = %f", tempo1, tempo2,tempo3);
    printf("\n\n");
    
    
}



