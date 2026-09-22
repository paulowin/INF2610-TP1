#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <errno.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: %s <mots_file>\n", argv[0]);
        return 1;
    }
    
    char buffer[10000];
    char nb_mots_string[20];
    int nb_mots = 0;
    

    int fd = open(argv[1], O_RDONLY);

    int nb_char = read(fd,buffer,10000);
    
    int fd_sortie = open("../utils/section2_2.txt", O_WRONLY);

    for (int i = 0; i<nb_char; i++){
        
        if (buffer[i] == ' '  || buffer[i] == '\n'  ){
            nb_mots++;
        }
        
    }


    int taille_nombre = sprintf(nb_mots_string,"%d\n", nb_mots);
   

    write(fd_sortie,nb_mots_string,taille_nombre);

    close(fd);

    close(fd_sortie);

    return 0;
}
