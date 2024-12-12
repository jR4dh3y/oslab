#include <stdio.h>
#include <unistd.h>


int main(){
    int child_pid  = fork();
    
    printf("Current process PID: %d\n", getpid());
    if (child_pid == 0){
	printf("Process is child\n");
	printf("Parent PID: %d\n", getppid());
    }else{
	printf("Process is parent\n");
	printf("Child PID: %d\n", child_pid);
    }    

    return  0;
}
