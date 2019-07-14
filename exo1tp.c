#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <sys/wait.h>
int main (void)
{
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

}else{
wait(NULL);
} 

}

}
}
