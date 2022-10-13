/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/cFiles/main.c to edit this template
 */

/* 
 * File:   main.c
 * Author: tsoulaimana
 *
 * Created on 13 octobre 2022, 09:19
 */

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <sys/syscall.h>
#include <signal.h>

typedef struct {
    int v1;
    int v2;
    int v3;
}laStruct;

laStruct partage;
char message[255];	
void *thread1(void *arg) {
    int val = 1;
    printf("dans le thread1 mon tid est %ld\n", syscall(SYS_gettid));
    printf("mise a jour de v1 avec la valeur %d\n", val);
    partage.v1 = val;
    pthread_exit(NULL);
}

int main(int argc, char** argv) {

    int ret;
    pthread_t t1, t2, t3;
    void *thread_result;
    //element de la struvture commune aux threads
    partage.v1 = 0;
    partage.v2 = 0;
    partage.v3 = 0;
    printf("avant creation therads\n");
    //affichePartage();
    //creation du thread 1
    ret = pthread_create(&t1, NULL, thread1, (void *) NULL);
    if (ret != 0) {
        perror("Thread creation failed");
        exit(EXIT_FAILURE);
    }
    printf("creation thread1\n");
    //attendre fin du thread
    ret = pthread_join(t1, &thread_result);
    if (ret != 0) {
        perror("Thread join a foir... echoué");
        exit(EXIT_FAILURE);
    }
    return (EXIT_SUCCESS);
}

