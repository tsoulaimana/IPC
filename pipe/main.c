#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>

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