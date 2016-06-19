#ifndef READCSV_H_INCLUDED
#define READCSV_H_INCLUDED

#define MAX_BUFFER 1024 //BUFFER DO ARQUIVO DE ENTRADA
#define TAM 50          //TAMANHO DAS STRINGS DE NOME

//-------------------|  ESTRUTURA   |----------------------------------------------------
typedef struct Sapo{
    char nome[TAM];
    int idade;
    float alturaSalto;
}TCSV;


//------------------|   FUNÇÕES                         |--------------------------------

///INICIO FUNCOES PADRÕES
//------------------|   RETORNA TAMANHO DO ARQUIVO      |--------------------------------
int tamanho_Arquivo(FILE *fp){
    if(fp==NULL){
        return -1;
    }
    int i=0;
    char linha[MAX_BUFFER];
    while (!feof(fp))
        if(fgets(linha,MAX_BUFFER, fp)!=NULL)//PEGA UM LINHA DO TAMANHO MÁXIMO DO BUFFER DECLARADO
            i++;
    rewind(fp);
    return i;
}

//-------------------|  PREENCHE DADOS   |-----------------------------------------------
void *preencheDados(TCSV *V, int n){
    int i;
    for(i=0;i<n;i++){
        printf("\nV[%d]\nNome: ",i);
        getchar();
        gets(V[i].nome);
        printf("\nIdade: ");
        scanf("%d",&V[i].idade);
        printf("\nAltura do salto: ");
        scanf("%f",&V[i].alturaSalto);
        printf("\n");
    }
}

//-------------------|  COPIA VETOR   |--------------------------------------------------
TCSV *copiaEstrutura(TCSV *V, int n){
    TCSV *aux = (TCSV*)calloc(n,sizeof(TCSV));
    int i;
    for(i=0;i<n;i++){
        aux[i].idade = V[i].idade;
        aux[i].alturaSalto = V[i].alturaSalto;
        strcpy(aux[i].nome,V[i].nome);
    }
    return aux;
}

//-------------------|  IMPRIME VETOR   |------------------------------------------------
void imprimeVetor(TCSV *V, int n){
    int i;
    for(i=0; i<n; i++)
        printf ("V[%d]: %s\t%d\t%.2lf\n", i, V[i].nome, V[i].idade, V[i].alturaSalto);
    printf("\n\n");
}

//---------------|  TROCA               |------------------------------------------------
void swap(TCSV *V, int i, int j){
    TCSV aux;
    strcpy(aux.nome, V[i].nome);
    aux.idade = V[i].idade;
    aux.alturaSalto = V[i].alturaSalto;

    strcpy(V[i].nome,V[j].nome);
    V[i].idade = V[j].idade;
    V[i].alturaSalto = V[j].alturaSalto;

    strcpy(V[j].nome, aux.nome);
    V[j].idade = aux.idade;
    V[j].alturaSalto = aux.alturaSalto;
}

//---------------|   RETORNA SE O SAPO É MAIOR OU MENOR      |---------------------------
int compararSapo (TCSV *V, int i, int j){
    TCSV aux;

    //NÃO QUIS TROCAR O AUX DE TODAS AS COMPARAÇÕES, MAS DAVA PRA COLOCAR SOMENTE V[i] NELAS
    strcpy(aux.nome,V[i].nome);
    aux.idade = V[i].idade;
    aux.alturaSalto = V[i].alturaSalto;

    if(strcmp(aux.nome,V[j].nome) < 0){//AUX NOME MENOR QUE O DO VETOR
        return -1;
    }else if(strcmp(aux.nome,V[j].nome) == 0){//NOME IGUAL, ENTÃO COMPARA POR IDADE
        if(aux.idade < V[j].idade){
            return -1;
        }else if(aux.idade == V[j].idade){//IDADE IGUAL, ENTÃO COMPARA POR ALTURA
            if(aux.alturaSalto<V[j].alturaSalto){
                return -1;
            }else//ALTURA DO SALTO AUXO MAIOR
                return 1;
        }else//IDADE AUX MAIOR
            return 1;
    }else//NOME AUX MAIOR
        return 1;
}
///FIM FUNCOES PADRÕES


///INICIO SELECAO DIRETA
//---------------|  TROCA DO SELECAO DIRETA E DO HEAP   |--------------------------------
void troca(TCSV *a, TCSV *b){
     TCSV aux;
     aux = *a;
     *a = *b;
     *b = aux;
}

//---------------|  INDICE VALOR MINIMO                 |--------------------------------
int indice_valor_minimo(TCSV *V, int inicio, int fim){
    int min = inicio, j;
    for(j=inicio+1; j<fim; j++){
            if(compararSapo(V,j,min) == -1)
                min = j;
    }
    return min;
}

//---------------|  SELECAO DIRETA                      |--------------------------------
void selecao_direta(TCSV *V, int n){
     int min, i;
     for(i=0; i<n-1; i++){
             min = indice_valor_minimo(V,i,n);
             troca(&V[i],&V[min]); // Troca
             //imprimeVetor(V,n);
     }
     //system("pause");
     //system("cls");
}
///FIM DO SELECAO DIRETA

///INICIO HEAPSORT
//---------------|  FILHO ESQUERDA                      |--------------------------------
int FilhoEsquerda(int raiz){
     return 2 * raiz + 1;
}

//---------------|  FILHO DIREITA                       |--------------------------------
int FilhoDireita(int raiz){
     return 2 * raiz + 2;
}

//---------------|  HEAP SORT                           |--------------------------------
void heapify(TCSV *V, int n, int indice_raiz){
     int esquerda = FilhoEsquerda(indice_raiz);
     int direita = FilhoDireita(indice_raiz);
     int max;

     if(esquerda > n-1)
        return;
     else if(direita > n-1)
             max = esquerda;
     else{
          if(compararSapo(V,esquerda,direita) == 1)
            max = esquerda;
          else
            max = direita;
     }
     if(compararSapo(V,max,indice_raiz) == 1){
        troca(&V[max],&V[indice_raiz]);
        heapify(V,n,max);
     }
}

//---------------|  CONSTRUIR HEAP                      |--------------------------------
void construirHeap(TCSV *V, int n){
     int i;
     for(i = n/2-1; i>=0; i--){
           heapify(V,n,i);
     }
}

//---------------|   HEAP                               |--------------------------------
void heapSort(TCSV *V, int n){
     int i;
     construirHeap(V,n);
     for(i = n-1; i>0; i--){
         troca(&V[i],&V[0]);
         heapify(V,i,0);
     }
}
///FIM HEAPSORT

//---------------|  MEDE TEMPO DE EXECUÇÃO              |--------------------------------
void tempoExecucao(clock_t Ticks[2]){
    double tempo = (Ticks[1] - Ticks[0]) * 1000.0 / CLOCKS_PER_SEC;
    printf("Tempo gasto: %g ms.", tempo);
}

//--|  LEITURA DO CSV           |---------------------------------
void leitura_CSV(TCSV *V,int tamCSV, FILE *fpCSV){
    int i=0;
    char *buffer[MAX_BUFFER];
    char *line, *record;
    while((line=(fgets(buffer, sizeof(buffer),fpCSV)))!=NULL){
        strcpy(V[i].nome, record = strtok(line,";"));
        V[i].idade = atoi(record = strtok(NULL,";"));
        V[i].alturaSalto = atof(record = strtok(NULL,"/0"));//VAI ATÉ ACHAR O BARRA ZERO
        i++;
    }
}

///INICIO QUICK
//-------------------|  PARTICAO QUICK  |----------------------------------------
int particao(TCSV *V, int inicio, int fim){
    TCSV pivo;
    //COPIA DADOS DO INICIO
    strcpy(pivo.nome, V[inicio].nome);
    pivo.idade = V[inicio].idade;
    pivo.alturaSalto = V[inicio].alturaSalto;

    int i = inicio +1, f = fim;

    while (i <= f){
        if (compararSapo(V,i,inicio) == -1){
            i++;
        }else if (compararSapo(V,inicio,f) == -1){
            f--;
        }else{
            swap(V,i,f);
            i++;
            f--;
        }
    }

    strcpy(V[inicio].nome, V[f].nome);
    V[inicio].idade = V[f].idade;
    V[inicio].alturaSalto = V[f].alturaSalto;

    strcpy(V[f].nome, pivo.nome);
    V[f].idade = pivo.idade;
    V[f].alturaSalto = pivo.alturaSalto;

    return f;
}

//-------------------|  QUICK SORT  |----------------------------------------
void quickSort(TCSV *V, int ini, int fim){
    int meio;
    if (ini<fim){
        meio = particao(V,ini,fim);
        quickSort (V,ini,meio);
        quickSort (V,meio+1,fim);
    }
}
///FIM QUICK SORT

///INICIO MERGE
//-------------------|   MERGE SORT     |------------------------------------------------
int min(int a, int b){
    return (a > b) ? b : a;//SE A MAIOR QUE B, RETORNA A : SENAO RETORNA B
}

//-------------------|   MERGE SORT     |------------------------------------------------
void simplemerge(TCSV *V, int is1, int fs1, int is2, int fs2, TCSV *V_resultado, int r){     // MERGE SORT
     int ini_seg1 = is1;
     int fim_seg1 = fs1;
     int ini_seg2 = is2;
     int fim_seg2 = fs2;
     int k = r, i;
     while((ini_seg1 <= fs1)&&(ini_seg2 <= fs2)){
           if(compararSapo(V,ini_seg1,ini_seg2)==-1){
              V_resultado[k] = V[ini_seg1];
              ini_seg1++;
           }else{
                 V_resultado[k] = V[ini_seg2];
                 ini_seg2++;
            }
            k++;
     }
     if(ini_seg1 > fs1){
        for(i=ini_seg2; i<=fs2; i++){
            V_resultado[k] = V[i];
            k++;
        }
     }else{
           for(i=ini_seg1; i<=fs1; i++){
               V_resultado[k] = V[i];
                k++;
           }
      }
}

//-------------------|   MERGE SORT     |------------------------------------------------
void mergepass(TCSV *V, TCSV *V_resultado, int n, int L){
     int i, p = 0, q = p + L, r = 0;
     while(q < n){
           simplemerge(V,p,q-1,q,min(q+L-1, n-1),V_resultado, r);
           r = r + 2 * L;
           p = q + L;
           q = p + L;
     }
     if(p < n){
        for(i=p; i<n; i++){
            V_resultado[i] = V[i];
        }
     }
}

//-------------------|   MERGE SORT     |------------------------------------------------
void mergeSort(TCSV *V, int n){
     TCSV *V_resultado = (TCSV*) malloc(n * sizeof(TCSV));
     int L = 1, i;
     bool eh_par = true;
     while(L < n){
           if(eh_par){
              mergepass(V,V_resultado,n,L);
              eh_par = false;
           }else{
                 mergepass(V_resultado,V,n,L);
                 eh_par = true;
            }
            L = L * 2;
     }
     if(!eh_par){
        for(i=0; i<n; i++){
            V[i] = V_resultado[i];
        }
     }
}
///FIM MERGE

///INICIO QUICK MISTO
//-------------------|  QUICK SORT  |----------------------------------------
void quickSortInsert(TCSV *V, int ini, int fim){
    int meio;
    if (ini<fim){
        if((fim - ini) < 20){
            insertionSort(V,ini,fim);
        }else{
            meio = particao(V,ini,fim);
            quickSortInsert(V,ini,meio);
            quickSortInsert(V,meio+1,fim);
        }
    }
}

//-------------------|  ATRIBUIR INSERT     |--------------------------------------------
void atribuirInsert(TCSV *V, int j){
        strcpy(V[j+1].nome,V[j].nome);
        V[j+1].idade = V[j].idade;
        V[j+1].alturaSalto = V[j].alturaSalto;
}

//-------------------|  INSERTION   |----------------------------------------------------
void insertionSort(TCSV *V, int inicio, int fim){
    TCSV aux;
    int k,j,i;
    //printf("teste %d\n",inicio);
    for(i=inicio; i<fim; i++){
        aux.idade = V[i].idade;
        aux.alturaSalto = V[i].alturaSalto;
        strcpy(aux.nome,V[i].nome);
        k = 0;
        j = i-1;
        while((j>=0) && (k==0)){
            if(compararSapo(V,i,j)==-1){//NOME MENOR QUE O ATUAL DO VETOR
                atribuirInsert(V,j);
                j = j-1;
            }else
                k = j+1;
        }
        V[k].idade = aux.idade;
        V[k].alturaSalto = aux.alturaSalto;
        strcpy(V[k].nome,aux.nome);
    }
}

///FIM QUICK SORT
#endif // READCSV_H_INCLUDED
