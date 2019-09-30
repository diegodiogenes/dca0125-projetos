//
//  thread8.cpp
//  
//
//  Created by Affonso on 25/10/16.
//
//

// Programa que sincroniza threads utilizando-se mutexes
// Baseado no problema de trens que estão circulando em trilhos


#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <string.h>
#include <iostream>
using namespace std;

void *thread_function_1(void *arg); // declaração da função a ser executada na thread
void *thread_function_2(void *arg); // declaração da função a ser executada na thread
void *thread_function_3(void *arg); // declaração da função a ser executada na thread

pthread_mutex_t work_mutex_1, work_mutex_2; /* proteção para: work_area e time_to_exit */


void L(int trem, int trilho) {
    int tempo_rand;
 
    tempo_rand = rand( ) % 10;
    
    printf("Sou o Trem %d e entrei no trilho %d \n", trem, trilho);
    sleep(tempo_rand);
    printf("Sou o Trem %d e vou sair do trilho %d \n", trem, trilho);
}

int main() {

    int res;
    pthread_t a_thread, b_thread, c_thread;
    void *thread_result;
    
    // Iniciar Mutex
    res = pthread_mutex_init(&work_mutex_1, NULL);
    if (res != 0) {
        perror("Iniciação do Mutex falhou");
        exit(EXIT_FAILURE);
    }

    res = pthread_mutex_init(&work_mutex_2, NULL);
    if (res != 0) {
        perror("Iniciação do Mutex falhou");
        exit(EXIT_FAILURE);
    }
    // Criar thread
    res = pthread_create(&a_thread, NULL, thread_function_1, NULL);
    if (res != 0) {
        perror("Criação da Thread falhou");
        exit(EXIT_FAILURE);
    }

   res = pthread_create(&b_thread, NULL, thread_function_2, NULL);
    if (res != 0) {
        perror("Criação da Thread falhou");
        exit(EXIT_FAILURE);
    }

    res = pthread_create(&c_thread, NULL, thread_function_3, NULL);
    if (res != 0) {
        perror("Criação da Thread falhou");
        exit(EXIT_FAILURE);
    }   
    
    // Juntando thread main() com a_thread
    
    res = pthread_join(a_thread, &thread_result);
    if (res != 0) {
        perror("Junção da Thread falhou");
        exit(EXIT_FAILURE);
    }
    res = pthread_join(b_thread, &thread_result);
    if (res != 0) {
        perror("Junção da Thread falhou");
        exit(EXIT_FAILURE);
    }
    res = pthread_join(c_thread, &thread_result);
    if (res != 0) {
        perror("Junção da Thread falhou");
        exit(EXIT_FAILURE);
    }

    pthread_mutex_destroy(&work_mutex_1);  // destruição do multex
    pthread_mutex_destroy(&work_mutex_2);  // destruição do multex

    exit(EXIT_SUCCESS);
}

void *thread_function_1(void *arg) {
    while (1) {
        L(1,1);
        L(1,2);

        pthread_mutex_lock(&work_mutex_1);
        cout << "\033[1;31m[INFO] Trem 1 entrou na zona de conflito entre o trilho 3 e trilho 6\033[0m\n";
        L(1,3);
        pthread_mutex_unlock(&work_mutex_1);
        cout << "\033[1;32m[INFO] Trem 1 saiu na zona de conflito entre o trilho 3 e trilho 6\033[0m\n";

        L(1,4);
    }
    pthread_exit(0);
}

void *thread_function_2(void *arg) {
    while(1) {
        pthread_mutex_lock(&work_mutex_1);
        cout << "\033[1;31m[INFO] trem 2 entrou na zona de conflito entre o trilho 3 e trilho 6\033[0m\n";
        L(2,6);
        pthread_mutex_unlock(&work_mutex_1);
        cout << "\033[1;32m[INFO] trem 2 saiu na zona de conflito entre o trilho 3 e trilho 6\033[0m\n";

        L(2,7);

        pthread_mutex_lock(&work_mutex_2);
        cout << "\033[1;31m[INFO] trem 2 entrou na zona de conflito entre o trilho 8 e trilho 11\033[0m\n";
        L(2,8);
        pthread_mutex_unlock(&work_mutex_2);
        cout << "\033[1;32m[INFO] trem 2 saiu na zona de conflito entre o trilho 8 e trilho 11\033[0m\n";

        L(2,5);
    }
    pthread_exit(0);
}

void *thread_function_3(void *arg) {
    while(1) {
        L(3,10);
        L(3,9);

        pthread_mutex_lock(&work_mutex_2);
        cout << "\033[1;31m[INFO] trem 3 entrou na zona de conflito entre o trilho 8 e trilho 11\033[0m\n";
        L(3,11);
        pthread_mutex_unlock(&work_mutex_2);
        cout << "\033[1;32m[INFO] trem 3 saiu na zona de conflito entre o trilho 8 e trilho 11\033[0m\n";

        L(3,12);
    }
    pthread_exit(0);
}
