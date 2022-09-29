#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <signal.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/wait.h>

#define MAXBUFF 255

void traitement(int sig) {
    (void) signal(SIGUSR1, traitement);
    printf("un signal SIGUSR1 je suis pid :%d\n", getpid());
}

int main(int argc, char** argv) {
    int nbOctets;
    int descTube[2];
    int pid, pidP1, pidP2, pidP3;
    char chaine[] = "message en provenance de p3";
    char buffer[MAXBUFF] = {0};
    memset(buffer, '\0', MAXBUFF);
    (void) signal(SIGUSR1, traitement);
    //P1
    if (pipe(descTube) == 0) {
        pid = fork();
        if (pid == 0) { //P2
            pid = fork();
            if (pid == 0) { //P3
                pidP3 = getpid();
                printf("pid P3 : %d\n", pidP3);
                
                nbOctets = write(descTube[1], &pidP3, sizeof(int));
                printf("je suis P3 : %d octets ecrits\n", nbOctets);
                pause();
            } else { //P2
                pidP2 = getpid();
                printf("pid P2 : %d\n", pidP2);
                
                pause();
            }
        } else { //P1
            pidP1 = getpid();
            printf("pid P1 : %d\n", pidP1);
            
            nbOctets = read(descTube[0], &pidP3, MAXBUFF);
            printf("je suis P1 : octets lus : %d: %s\n", nbOctets, buffer);
            
            sleep(2);
            pidP2 = pid;
            kill(pidP2, SIGUSR1);
            sleep(2);
            kill(pidP3, SIGUSR1);
        }
    }
    return EXIT_SUCCESS;
}


/*
 * exo 3
int main() {
    int nbOctets;
    int descTube[2];
    int descTube2[2];
    int pid;
    const char chaine[] = "message P2 <- P1";
    const char chaine2[] = "message P2 -> P1";
    char buffer[BUFSIZ];
    char buffer2[BUFSIZ];
    memset(buffer2, '\0', BUFSIZ);
    memset(buffer, '\0', BUFSIZ);
    //P1
    if (pipe(descTube) == 0) {
        if (pipe(descTube2) == 0) {
            pid = fork();
            if (pid == 0) { //P2
                nbOctets = write(descTube2[1], chaine2, strlen(chaine2));
                printf("je suis P2 avec %d octets ecrits\n", nbOctets);
                nbOctets = read(descTube[0], buffer, BUFSIZ);
                printf("je suis P2 avec %d octets lus || : %s\n", nbOctets, buffer);
            } else {
                nbOctets = write(descTube[1], chaine, strlen(chaine));
                printf("je suis P1 avec %d octets ecrits\n", nbOctets);
                nbOctets = read(descTube2[0], buffer2, BUFSIZ);
                printf("je suis P1 avec %d octets lus || : %s\n", nbOctets, buffer2);
            } 

        }
    }
    return 0;
}
 */



/*
 * autre exo 2
int main() {
    int nbOctets;
    int descTube[2];
    int pid;
    const char chaine[] = "message ruru";
    char buffer[BUFSIZ];
    memset(buffer, '\0', BUFSIZ);
    //P1
    if (pipe(descTube) == 0) {
        pid = fork();
        if (pid == 0) {
            nbOctets = read(descTube[0], buffer, BUFSIZ);
            printf("je suis P2 :octets lus: %d: %s\n", nbOctets, buffer);
        } else //P1
        {
            nbOctets = write(descTube[1], chaine, strlen(chaine));
            printf("je suis P1 avec %d octets ecrits\n", nbOctets);
        }
    }
    return 0;
}
 */

/*
 * exo 2
int main() {
    int pid;
    char message[] = "message ruru";
    char buffer[255] = {0}; //déclaration et init du buffer de réception
    int tube[2];
    int retour;
    //P1

    //création du tube commun à P1 et P2
    if (pipe(tube) == 0) {
        pid = fork();
        if (pid == 0) //P2
        {
            printf("pid: %d | ppid: %d\n", getpid(), getppid());
            //lecture dans le tube 
            retour = read(tube[0], buffer, 255);
            if (retour == -1) {
                printf("pb tube: %s", strerror(errno));
                exit(errno);
            }
            //affichage du message
            printf("message de P1: %s\n", buffer);
        } else //P1
        {
            printf("pid: %d \n", getpid());
            //écriture dans le tube
            retour = write(tube[1], message, strlen(message));
            if (retour == -1) {
                printf("pb tube: %s", strerror(errno));
                exit(errno);
            }
        }
    } else {
        printf("pb tube: %s", strerror(errno));
        exit(errno);
    }
return 0;
}
 */



/*
 * ex 1
#define MAXBUFF 255
int main() {
    FILE *fd;
    char *retourLecture;
    char buffer[MAXBUFF];
    memset(buffer, '\0', MAXBUFF);
    // invocation d'un programme externe et mise dans un tube popen du resultat sous forme de chaine de caracteres
    // le tube popen sera en lecture (car on veut lire ce qu'a produit le programme externe
    fd = popen("/bin/uname", "r");
    if (fd == NULL) {
        printf(" pb popen : %s\n", strerror(errno));
        exit(1);
    }
    //lecture de la chaine genere par le programme invoque par popen (-> /bin/uname)
    retourLecture = fgets(buffer, MAXBUFF, fd);
    if (retourLecture == NULL) {
        printf("pb lecture popen\n");
        exit(1);
    }
    // fermeture du tube
    pclose(fd);
    // affichage de ce qu'a produit "/bin/uname"
    printf("le process a ecrit : [%s]\n", buffer);

    return 0;
}
 */