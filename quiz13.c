#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

double BALANCE = 0.0;

typedef struct arg_struct {
    int arg1;
    double arg2;
} arg_struct;

void *deposit(void *args);
void *withdraw(void *args);
int main(int argc, char * argv[]){
    if(argc != 5){
        printf("4 args\n");
        exit(0);
    }
    int a = atol(argv[1]);
    int c = atol(argv[3]);
    double b,d;
    sscanf(argv[2], "%lf", &b);
    sscanf(argv[4], "%lf", &d);
    pthread_t thread,thread2;
    arg_struct args1, args2;
    args1.arg1 = a;
    args1.arg2 = b;
    args2.arg1 = c;
    args2.arg2 = d;
    pthread_create(&thread, NULL, deposit, (void *)&args1);
    pthread_create(&thread2, NULL, withdraw, (void *)&args2);
    pthread_join(thread, NULL);
    pthread_join(thread2, NULL);
    double cbalance = (a*b) - (c*d);
    printf("BALANCE : %.2lf\nCORRECT BALANCE: %.2lf\n", BALANCE, cbalance);
}


void *deposit(void *args){
    int i,a;
    arg_struct *ar = args;
    a = ar->arg1;
    double b = ar->arg2;
    for(i = 0; i < a; i++) BALANCE += b;
}


void *withdraw(void *args){
    int i,c;
    arg_struct *ar = args;
    c = ar->arg1;
    double d = ar->arg2;
    for(i = 0; i < c; i++) BALANCE -= d;
}
