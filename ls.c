#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <pwd.h>
#include <time.h>
int main(int argc, char *argv[]) {
    // on test les argument
    if( argc != 2 ) {
        printf( "psst , tu as oublier de preciser l'argument 😓️🙄️ \n" );
        exit( 2 );
    }

    // cette fonction fait un appel system
    struct stat StatusBuffer;
    if (stat(argv[1], &StatusBuffer) == -1) {
        perror(argv[1]);
        exit(1);
    }
    // on attribue les permission pour chaque type de fichier
    char perm[12]:
    if( S_ISREG( StatusBuffer.st_mode ) ) { // ficher reguliere
        perm[0] = '-';
    } else if( S_ISBLK( StatusBuffer.st_mode ) ) { // perph en block
        perm[0] = 'b';
     } else if( S_ISDIR( StatusBuffer.st_mode ) ) { // folder
        perm[0] = 'd';


    } else if( S_ISCHR( StatusBuffer.st_mode ) ) { //perepherique caractere
        perm[0] = 'c';
       
    } else if( S_ISLNK( StatusBuffer.st_mode ) ) { //liens symbolique
        perm[0] = 'l';

    } else if( S_ISFIFO( StatusBuffer.st_mode ) ) { // pipe
        perm[0] = 'p';
    }
 

   // Utilisateur
    if( S_IRUSR & StatusBuffer.st_mode ) { // read
        perm[1]  =   'r';
    } else {
        perm[1]  =   '-';
    }

    if( S_IWUSR & StatusBuffer.st_mode ) { // write
        perm[2]  =   'w';
    } else {
        perm[2]  =   '-';
    }

    if( S_IXUSR & StatusBuffer.st_mode ) { // excute
        perm[3]  =   'x';
    } else {
        perm[3]  =   '-';
    }


    // groupe en utilisant la fonction S_IRGRP
    if( S_IRGRP & StatusBuffer.st_mode ) { // read
        perm[4]  =   'r';
    } else {
        perm[4]  =   '-';
    }

    if( S_IWGRP & StatusBuffer.st_mode ) { // write
        perm[5]  =   'w';
    } else {
        perm[5]  =   '-';
    }

    if( S_IXGRP & StatusBuffer.st_mode ) { // excute
        perm[6]  =   'x';
    } else {
        perm
        [6]  =   '-';
    }

    // autre
    if( S_IROTH & StatusBuffer.st_mode ) { // read
        perm[7]  =   'r';
    } else {
        perm[7]  =   '-';
    }

    if( S_IWOTH & StatusBuffer.st_mode ) { // write
        perm[8]  =   'w';
    } else {
        perm[8]  =   '-';
    }

    if( S_IXOTH & StatusBuffer.st_mode ) { // excute
        perm[9]  =   'x';
    } else {
        perm[9]  =   '-';
    }

    printf( "%s ", perm );



   
    // lien physique

    int liens_physique     =   StatusBuffer.st_nlink;
    printf( "%d ", liens_physique );
   
   

    //nom du prop

    char* nom     =   getpwuid(StatusBuffer.st_uid)->pw_name;
    printf( "%s ", nom );


    // nom du groupe

    char* nom_du_group     =   getpwuid(StatusBuffer.st_gid)->pw_name;
    printf( "%s ", nom_du_group );

    // taille du fichier
   
    int taille        =   StatusBuffer.st_size;
    printf( "%d ", taille );



    // Last Modification temps

    char dernier_modification[100];
    strftime( dernier_modification, 100, "%b %d %H:%M", localtime( &StatusBuffer.st_mtime ) );

    printf( "%s ", dernier_modification );


    // Nom Du Fichier

    printf( "%s \n", argv[1] );

    return EXIT_SUCCESS;



}

