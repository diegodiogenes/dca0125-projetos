// UFRN-CT-DCA
// Disciplina: Sistema em Tempo Real
// Programa: Family Fork
// Aluno: Diego Bruno Dantas Diógenes

#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main()
{
    int i, j, k;
    int tempo_vida, filho1, filho2, neto;
    pid_t pid;

    printf("[INFO] Começando o programa da família fork.. \n");
    tempo_vida = 13; // iniciamos a variável tempo _vida de acordo com a duração total do processo pai que será de 13s
    filho1 = 5; // Aos 5s o pai terá um filho, como descrito no problema
    filho2 = 8; // Aos 8s o pai terá um outro filho, como descrito no problema

    tempo_vida = 13;
    for(i=0; i<tempo_vida; i++){
        sleep(1);
        printf("\n Olá, eu sou o processo %d e tenho %d segundos de vida \n", getpid(), i);
        if(i == filho1){
            if(!fork()){ //verificamos o código de retorno do fork, se for filho, retorna 0
                //faremos com que o filho vá para fora do loop executando as suas instruções
                break;
            }
        }
        if(i == filho2){
            if(!fork()){
                break;
            }
        }
    }

    //
    // Aqui ficamos com os procesoss que saíram do pai
    //
    //iniciando o processo que saiu aos 5s, que terá duração de 13s, segundo o problema
    
    neto = 6;
    tempo_vida = 13;
    if(i == filho1){
        for(j=0; j< tempo_vida; j++){
            sleep(1);
            printf("\n Olá, eu sou o processo filho %d e tenho %d segundos de vida \n", getpid(), j);
            if(j == neto){
                if(!fork()){
                    break;
                }
            }
        }
    }

    //iniciando o processo que saiu aos 8s do pai
    // possui um tempo de vida de 7s
    tempo_vida = 7;
    if(i == filho2){
        for(j=0; j< 7; j++){
            sleep(1);
            printf("\n Olá, eu sou o processo filho %d e tenho %d segundos de vida \n", getpid(), j);
        }
    }

    //
    // Aqui temos o processo neto
    //

    tempo_vida = 9;
    if(j == neto){
        for(k=0; k<tempo_vida; k++){
            sleep(1);
            printf("\n Olá, eu sou o processo neto %d e tenho %d segundos de vida \n", getpid(), j);
        }
    }


    exit(0);

}