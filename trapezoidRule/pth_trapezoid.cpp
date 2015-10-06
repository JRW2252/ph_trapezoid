//
//  main.cpp
//  trapezoidRule
//
//  Created by James Williams
//

#include <iostream>
#include <pthread.h>
#include <math.h>
using namespace std;

// globals
double NUM_THREADS = 5;
double A, B, N; // A = start, B = end, N = divisions/segments
double SUM = 0;
// globals

// function headers
void *trapezoid(void *arg);
double f(double x);
// function headers

int main(int argc, const char * argv[]) {
//    using hard coded values for A, B, and N for development
//    read in values for A, B, N
//    printf("\nEnter start, end, and # of sections: ");
//    scanf("%lf %lf %lf", &A, &B, &N);
    A = 1;
    B = 50;
    N = 25;
    printf("\nStart = %.lf \tEnd = %.lf \tN = %.lf \n\n", A, B, N);
    
    pthread_t* thread_handles; // init threads and allocate mem
    thread_handles = (pthread_t *) malloc(NUM_THREADS * sizeof(pthread_t));
    
    for(long i=0; i < NUM_THREADS; i++){ // create threads and run
        pthread_create(&thread_handles[i], NULL, trapezoid, (void*)i);
        printf("\tCreated thread: %ld of %.f\n", i, NUM_THREADS);
    }
    
    for(int i=0; i < NUM_THREADS; i++) { // join threads
        printf("Joining thread: %d\n", i);
        pthread_join(thread_handles[i], NULL);
    }
    
    free(thread_handles);
    
    printf("\nf(x) = x*(0.5*x)\n");
    printf("\nEvaluating the integral from %.lf to %.lf = %.1lf\n", A, B, SUM*-1);
//    printf("Sum = %.lf\n", SUM); // multiplied by -1 to return positive

/*
 value for the area under the curve is returning as a negative.
 this should not be correct though. wt?.. 
 actual value using x(.5*x) should be 20,833.2
 actual value using x^2 should be 41555 for 1 - 50
*/
    
    return 0;
}
void *trapezoid(void *arg){
    double myA, myB, myN, mySum, h;
    pthread_mutex_t myLock;
    long tRank = (long) arg;
    h = (A-B)/N;
    myN = N/NUM_THREADS;
    myA = A + tRank * N * h;
    myB = myA + myN *h;
    mySum = (f(myA) + f(myB)) / 2.0;
    
    for(int i = 1; i <= myN-1; ++i){
        double x = myA + i * h;
        mySum += f(x);
    }
    mySum *= h;
    
    pthread_mutex_lock(&myLock);
    // critical section summation
    SUM += mySum;
    pthread_mutex_unlock(&myLock);
    return 0;
}

double f(double x){
//    printf("X: %.lf\n", x);
    return pow(x, 2.0);
}
