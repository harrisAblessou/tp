#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <sys/wait.h>
#include <sys/ipc.h> 
#include <sys/shm.h> 
#include <stdio.h> 
#include <sys/sem.h>
#include <errno.h>
#include <stdlib.h>
#include <sys/types.h>
int main (void)
{

  // ftok to generate unique key 
  key_t key = ftok("shmfile",65); 
 // shmget returns an identifier in shmid 
  int shmid = shmget(key,1024,0666|IPC_CREAT); 
  // shmat to attach to shared memory 
  char *str = (char*) shmat(shmid,(void*)0,0); 
int i,a;

pid_t  fils1,fils2,fils3;
do {
//creation du premier processus
fils1= fork ( ) ;
} while ((fils1<0) && (errno == EAGAIN));
if (fils1 <-1) {
fprintf (stderr, "fork( ) impossible, errno=%d\n", errno);
}
if (fils1== 0) {
fprintf (stdout, "Fils1 : PID=%d\n",
getpid( ) );
 for(i=0; i < 100; i++){
     printf("Write Data : \n"); 
    a= atoi(str);
     a++; 

     sprintf(str, "%d", a);

     printf("Data written in memory: %s\n",str); 
  }	

} else {
do {
//creation du deuxième processus
fils2= fork ( ) ;
} while ((fils2<0) && (errno == EAGAIN));
if (fils2 <0) {
fprintf (stderr, "fork( ) impossible, errno=%d\n", errno);
}
if (fils2== 0) {
fprintf (stdout, "Fils2 : PID=%d\n",
getpid( ) );
for(i=0; i < 100; i++){
     printf("Write Data : \n"); 
a= atoi(str);
     a++; 

     sprintf(str, "%d", a);


     printf("Data written in memory: %s\n",str); 
  }	
} else {
do {
//creation du troisième processus
fils3= fork ( ) ;
} while ((fils3<0) && (errno == EAGAIN));
if (fils3 <0) {
fprintf (stderr, "fork( ) impossible, errno=%d\n", errno);
}
if (fils3== 0) {
fprintf (stdout, "Fils3 : PID=%d\n",
getpid( ) );
for(i=0; i < 100; i++){
     printf("Write Data : \n"); 
     a= atoi(str);
     a++; 

     sprintf(str, "%d", a);

     printf("Data written in memory: %s\n",str); 
  }	

}else{
a=atoi(str);
     printf("valeur est %d\n",a); 
shmdt(str); 
	
  // destroy the share
 shmctl(shmid,IPC_RMID,NULL); 
wait(NULL);
} 

}

}
}
