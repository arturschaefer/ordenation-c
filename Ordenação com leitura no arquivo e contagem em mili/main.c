#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include <stdbool.h>
#include<time.h>

#include "readCsv.h"

int main(){
    setlocale(LC_ALL, "Portuguese");

    //VARIAVEIS LOCAIS------------------------------
    clock_t Ticks[2];
    FILE *fpCSV = fopen("teste.txt","r");
    int tamCSV = tamanho_Arquivo(fpCSV);
    TCSV *V, *SelecaoDireta, *Heap, *Quick;
    int erro=0,i;
    double tempoHeap,tempoSelecao;

    TCSV *pVet;
    //FIM DAS VARIAVEIS------------------------------
    printf("TAMANHO: %d\n", tamCSV);
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

        printf("\n");
        tempoExecucao(Ticks);
        printf("\n");
        system("pause");

        //HEAP SORT
        Heap = copiaEstrutura(pVet,tamCSV);
        Ticks[0] = clock();
        heapSort(Heap,tamCSV);
        Ticks[1] = clock();
        printf("\n\nHEAP SORT\n");
        //imprimeVetor(Heap,tamCSV);
        printf("\n");
        tempoExecucao(Ticks);
        printf("\n");
        system("pause");

        //QUICK SORT
        Quick = copiaEstrutura(pVet,tamCSV);
        Ticks[0] = clock();
        quickSort(Quick,0,tamCSV-1);//PASSA POSIÇÃO INICIAL E POSIÇÃO FINAL
        Ticks[1] = clock();
        printf("\n\nQUICK SORT\n");
        //imprimeVetor(Quick, n);
        tempoExecucao(Ticks);

        system("pause");


    printf("\n->LIBERA ARQUIVOS");
    if(erro==0){//FECHA ARQUIVOS
        if (fclose(fpCSV) != 0)
            printf("\t->ERRO NO FECHAMENTO DO ARQUIVO \"CSV\"");
        else
            printf ("\t->Arquivo \"CSV\" fechado com sucesso.");
        printf("\n\n");
    }

    system("pause");

    printf("\n\n");
    //LIBERA VETORES
    printf("\n---------------------------------------------------------\n");
    printf("|\t\t\tFIM DO PROGRAMA\t\t\t|");
    printf("\n---------------------------------------------------------\n");
    printf("\n->Free Vetores");
    free(pVet);
    printf("\n\n");

    return 0;
}
