
#include <sys/socket.h>
#include <netinet/in.h>
 #include <arpa/inet.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

#define GREETING "Connexion etablie"
#define CMD_SIZE 1000
int main(int argc, char *argv[]){
   int cfd; // socket du client
   int success; // etat de la connection
   int port;
   // les configurations du fichier
   size_t nbytes = 0;
   char line[100];
   char nomfichier[] = "fiche.txt";
   /*char cmd1[CMD_SIZE] = "Q1_popen";
   strncat(cmd1, argv[1], CMD_SIZE);*/


   FILE *fichier = NULL;


   struct sockaddr_in srv_addr; // socket addr du serveur

   if(argc!=3){
     printf("USAGE:./client <serveur_ip_addr> <serveur_port>\n");
     exit(-1);
   }

   cfd = socket(AF_INET, SOCK_STREAM, 0); // création de la socket
   if (cfd < 0){ // Une erreur s'est produite la socket n'a pas pu être créer
      printf("Le SE n'a pas pu créer la socket %d\n", cfd);
      exit(-1);
   }
   /* donne une identite a la socket.
    * AF_INET pour dire que c'est le protocole TCP qui sera utilisé
    * SRV_PORT est le port du serveur distant que le client desire contacter
    * SRV_ADDR est l'adresse du serveur distant que le client desire contacter
    * */
   port = atoi(argv[2]);

   srv_addr.sin_family = AF_INET;
   srv_addr.sin_port = htons (port);
   inet_aton(argv[1], (struct in_addr *)&srv_addr.sin_addr.s_addr);

   /* connexion au serveur
    * A l'aide de la fonction connect() on se connecte au serveur distant
    * on utilise pour cela la socket qui a été créée par l'SE du client
    * on utilise aussi l'identité du serveur qui vient d'être construite */
   success = connect(cfd, (struct sockaddr *) &srv_addr,
                 sizeof(struct sockaddr_in));
   if(success < 0){ // la connexion a echouée
      printf("Impossible de se connecter au serveur %s:%d error %d\n",
               argv[1], port, success);
      exit(-1);
   }
   /* La connexion au serveur est un succes. Disons Bonjour au serveur
    * Pour cela nou utilisons la fonction send qui prend en parametre
    * la socket creee par le SE et la chaine de caractere BONJOUR
    * nou veillons à preciser la taille du message que nous envoyons*/

      send(cfd,nomfichier, sizeof(nomfichier), 0);

      fichier = fopen(nomfichier,"r");
      while (fgets(line, 100, fichier) != NULL) {
			 send(cfd,line, sizeof(line), 0);
	  }





   close(cfd);
   return(0);
}

