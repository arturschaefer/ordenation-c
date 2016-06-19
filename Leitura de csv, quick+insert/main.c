#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include <stdbool.h>
#include<time.h>

/** DESCRIÇÃO:  METODOS DE ORDENAÇÃO APLICADOS EM UM ARQUIVO CSV
    AUTOR:      ARTUR SCHAEFER
    DATA, HORA: 26/06/2015, 20:22
*/

//TAD
#include "readCsv.h"

int main(){
    setlocale(LC_ALL, "Portuguese");

    //VARIAVEIS LOCAIS------------------------------
    clock_t Ticks[2];
    FILE *fpCSV = fopen("teste.csv","r");
    int tamCSV = tamanho_Arquivo(fpCSV);
    TCSV *pVet, *SelecaoDireta, *Heap, *Quick, *Merge, *InsertQuick;
    int erro=0,i;
    //FIM DAS VARIAVEIS------------------------------

    printf("\n---------------------------------------------------------\n");
    printf("|\t\tINICIO DO PROGRAMA\t\t\t|");
    printf("\n---------------------------------------------------------\n");
    printf("\nTAMANHO DA ENTRADA [STRING;INT;FLOAT]: %d\n\n", tamCSV);
    system("pause");
    if(tamCSV == -1){
        printf("\nERRO ABERTURA DO ARQUIVO.\n");
        return -1;
    }else{
        pVet = (TCSV*)calloc(tamCSV,sizeof(TCSV));
        if(pVet!=NULL){
            leitura_CSV(pVet,tamCSV,fpCSV);
        }else{
            printf("\n\nERRO DE ALOCA\Ç\ÃO DO VETOR.");
            erro++;
        }
    }

    //SELECAO DIRETA
    SelecaoDireta = copiaEstrutura(pVet,tamCSV);
    Ticks[0] = clock();
    selecao_direta(SelecaoDireta,tamCSV);
    Ticks[1] = clock();
    printf("\n\nSELECAO DIRETA\n");
    //imprimeVetor(SelecaoDireta, tamCSV);
    tempoExecucao(Ticks);

    //HEAP SORT
    Heap = copiaEstrutura(pVet,tamCSV);
    Ticks[0] = clock();
    heapSort(Heap,tamCSV);
    Ticks[1] = clock();
    printf("\n\nHEAPSORT\n");
    //imprimeVetor(Heap,tamCSV);
    tempoExecucao(Ticks);

    //QUICK SORT
    Quick = copiaEstrutura(pVet,tamCSV);
    Ticks[0] = clock();
    quickSort(Quick,0,tamCSV-1);//PASSA POSIÇÃO INICIAL E POSIÇÃO FINAL
    Ticks[1] = clock();
    printf("\n\nQUICKSORT\n");
    //imprimeVetor(Quick, n);
    tempoExecucao(Ticks);

    //MERGESORT
    Merge = copiaEstrutura(pVet,tamCSV);
    Ticks[0] = clock();
    mergeSort(Merge,tamCSV);
    Ticks[1] = clock();
    printf("\n\nMERGESORT\n");
    //imprimeVetor(Merge, n);
    tempoExecucao(Ticks);

    //QUICK + INSERTION
    InsertQuick = copiaEstrutura(pVet,tamCSV);
    Ticks[0] = clock();
    quickSortInsert(InsertQuick,0,tamCSV-1);
    Ticks[1] = clock();
    printf("\n\nISERTION + QUICK\n");
    //imprimeVetor(Merge, n);
    tempoExecucao(Ticks);
    printf("\n\n");

    for(i=0;i<tamCSV/1000;i++)
        printf("%s\t%d\t%.2lf\n",InsertQuick[i].nome,InsertQuick[i].idade,InsertQuick[i].alturaSalto);

    printf("\n\n");
    //LIBERA VETORES
    printf("\n---------------------------------------------------------\n");
    printf("|\t\t\tFIM DO PROGRAMA\t\t\t|");
    printf("\n---------------------------------------------------------\n");
    printf("\n->Free Vetores");
    free(pVet);
    free(Quick);
    free(Merge);
    free(Heap);
    free(InsertQuick);
    free(SelecaoDireta);
    printf("\n\n");

    printf("\n->LIBERA ARQUIVOS\n");
    if(erro==0){//FECHA ARQUIVOS
        if (fclose(fpCSV) != 0)
            printf("\t->ERRO NO FECHAMENTO DO ARQUIVO \"CSV\"");
        else
            printf ("\t->Arquivo \"CSV\" fechado com sucesso.");
        printf("\n\n");
    }

    return 0;
}
