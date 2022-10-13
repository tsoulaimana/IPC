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
	
void *threadMulti(void *arg) {
    laStruct *ptr = (laStruct *)arg;
    printf("le tid du threadMulti est de %ld\n", syscall(SYS_gettid));
    printf("mise a jour de v1, v2, v3 avec les valeurs %d, %d, %d\n\n", ptr->v1, ptr->v2, ptr->v3);
    partage.v1 = ptr->v1;
    partage.v2 = ptr->v2;
    partage.v3 = ptr->v3;
    pthread_exit(NULL);
}

void affichePartage() {
    printf("__________\n");
    printf("v1 = %d\n", partage.v1);
    printf("v2 = %d\n", partage.v2);
    printf("v3 = %d\n", partage.v3);
    printf("----------\n\n");
}

int main(int argc, char** argv) {

    int ret;
    pthread_t t1, t2, t3;
    laStruct parm1, parm2, parm3;
    void *thread_result;
    //element de la struvture commune aux threads
    
    printf("avant creation threads\n\n");
    //affichePartage();
    //creation du thread 1
    affichePartage();
    parm1.v1 = 1;
    parm2.v2 = 1;
    parm3.v3 = 1;
    ret = pthread_create(&t1, NULL, threadMulti, (void *) &parm1);
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
    affichePartage();
    parm1.v1 = 2;
    parm2.v2 = 2;
    parm3.v3 = 2;
    ret = pthread_create(&t2, NULL, threadMulti, (void *) &parm2);
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
    affichePartage();
    parm1.v1 = 3;
    parm2.v2 = 3;
    parm3.v3 = 3;
    ret = pthread_create(&t3, NULL, threadMulti, (void *) &parm3);
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

