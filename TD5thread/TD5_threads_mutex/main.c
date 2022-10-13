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
	
void *thread1(void *arg) {
    int val = 1;
    printf("le tid du thread1 est de %ld\n", syscall(SYS_gettid));
    printf("mise a jour de v1 avec la valeur %d\n\n", val);
    partage.v1 = val;
    pthread_exit(NULL);
}

void *thread2(void *arg) {
    int val = 2;
    printf("le tid du thread2 est de %ld\n", syscall(SYS_gettid));
    printf("mise a jour de v2 avec la valeur %d\n\n", val);
    partage.v2 = val;
    pthread_exit(NULL);
}
void *thread3(void *arg) {
    int val = 3;
    printf("le tid du thread3 est de %ld\n", syscall(SYS_gettid));
    printf("mise a jour de v3 avec la valeur %d\n\n", val);
    partage.v3 = val;
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
    printf("avant creation threads\n\n");
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
    
    //creation du thread 2
    ret = pthread_create(&t2, NULL, thread2, (void *) NULL);
    if (ret != 0) {
        perror("Thread creation failed");
        exit(EXIT_FAILURE);
    }
    printf("creation thread2\n");
    //attendre fin du thread
    ret = pthread_join(t2, &thread_result);
    if (ret != 0) {
        perror("Thread join a foir... echoué");
        exit(EXIT_FAILURE);
    }
        
    //creation du thread 3
    ret = pthread_create(&t3, NULL, thread3, (void *) NULL);
    if (ret != 0) {
        perror("Thread creation failed");
        exit(EXIT_FAILURE);
    }
    printf("creation thread3\n");
    //attendre fin du thread
    ret = pthread_join(t3, &thread_result);
    if (ret != 0) {
        perror("Thread join a foir... echoué");
        exit(EXIT_FAILURE);
    }
    return (EXIT_SUCCESS);
}

