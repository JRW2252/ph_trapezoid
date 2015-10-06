//
//  main.cpp
//  trapezoidRule
//
//  Created by James Williams
//

#include <iostream>
#include <pthread.h>
using namespace std;

// globals
double NUM_THREADS = 5;
double A, B, N; // A = start, B = end, N = divisions/segments
// globals

// function headers
void *trapezoid(void *arg);
// function headers

// using structure of args for parameters on the trap function
typedef struct f_args{
    double  start;
    double  end;
    double  sum;
    int     tid;
} args_t;

int main(int argc, const char * argv[]) {
    
    // read in values for A, B, N
    printf("\nEnter start, end, and # of sections: ");
    scanf("%lf %lf %lf", &A, &B, &N);
    printf("\nYou entered: %.lf %.lf %.lf \n\n", A, B, N);
    if (N < NUM_THREADS) {
        NUM_THREADS = N;
    }
    pthread_t* thread_handles; // init threads and allocate mem
    thread_handles = (pthread_t *) malloc(NUM_THREADS * sizeof(pthread_t));
    
    // init mem for struct data
//    args_t *my_args = (args_t *) malloc(sizeof(args_t));
    
    for(long i=0; i < NUM_THREADS; i++){ // create threads and run
        pthread_create(&thread_handles[i], NULL, trapezoid, (void*)i);
//        printf("\tCreated thread: %ld of %.f\n", i, NUM_THREADS);
    }
    
    for(int i=0; i < NUM_THREADS; i++) { // join threads
//        printf("Joining thread: %d\n", i);
        pthread_join(thread_handles[i], NULL);
    }
    return 0;
}
void *trapezoid(void *arg){
    /*
     h = b-a; 
     approx = (f(a) + f(b))/2.0; 
     for(i = 1; i <= n-1; i++){
        approx += f(a + i*h);
     }
     approx = h*approx;
     */
    return 0;
}
