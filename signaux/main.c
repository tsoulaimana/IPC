/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/cFiles/main.c to edit this template
 */

/* 
 * File:   main.c
 * Author: tsoulaimana
 *
 * Created on 22 septembre 2022, 09:34
 */
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <signal.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>

// fonction de traitement du signal SIGUSR1

void traitement(int sig) {
    int cpt;
    (void) signal(SIGUSR1, traitement);
    cpt++;
    printf("cpt : %d\n",cpt);
    if(cpt==2){
        printf("un signal SIGUSR1 ppid :%d\n", getppid());
    }
}

int main(int argc, char *argv[]) {
    int pid;
    int pidP1;
    int cpt = 0;
    (void) signal(SIGUSR1, traitement);
    //P1
    pidP1 = getpid();
    pid = fork();
    if (pid == 0) //P2
    {
        pid = fork();
        if (pid == 0) //P3
        {
            printf("pid3 = %d\n", getpid());
            kill(pidP1, SIGUSR1);

        } else //P2 
        {
            printf("pid2 = %d\n", getpid());
            kill(pidP1, SIGUSR1);
        }
    } else //P1
    {
        printf("pid1 = %d\n", getpid());
        pause();
        pause();
    }
    return EXIT_SUCCESS;
}






/*
 * 
 * exo 1
 * 
int main(int argc, char *argv[])
{
        int pid;
        (void) signal(SIGUSR1, traitement);	// rederoutage des signaux SIGUSR1
                                                        // vers la fonction traitement
        pid = fork();

        if (pid == -1)
        {
                printf("pb creation fork : %s\n", strerror(errno));
                exit(1);
        }
        else
        {
                if (pid == 0)		// process fils
                {
                        printf("fils pid=%d\n", getpid());
                        kill(getppid(), SIGUSR1);
                        sleep(2);	// tempo pour être certain que le fils sera
                                        //encore vivant quand le pere lui 
                                        //enverra son signal
                }
                else		// process principal (pere)
                {
                        printf("pere pid=%d\n", getpid());
                        kill(pid, SIGUSR1);
                        sleep(2);	// tempo pour être certain que le pere sera
                                        //encore vivant quand le fils lui 
                                        //enverra son signal
                }
        }

        return EXIT_SUCCESS;
}
 */