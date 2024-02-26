#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<pthread.h>

void *myThreadFun(void *vargp) {
    sleep(1);
    printf("Printing GeeksQuiz from Thread\n");
    return NULL;
}

int main() {
    pthread_t thread_id;
    
    printf("Before Thread\n");
    
    // Create thread
    if (pthread_create(&thread_id, NULL, myThreadFun, NULL) != 0) {
        printf("Failed to create thread.\n");
        return 1; // Return with error code
    }
    
    // Wait for thread to finish
    if (pthread_join(thread_id, NULL) != 0) {
        printf("Failed to join thread.\n");
        return 1; // Return with error code
    }
    
    printf("After Thread\n");
    
    return 0; // Return success
}

