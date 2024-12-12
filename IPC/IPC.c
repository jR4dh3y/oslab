#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main(){
    int fd_child[2], fd_parent[2];
    pipe(fd_child); pipe(fd_parent);
    // fd[0] is for reading, fd[1] is for writing 
    int pid = fork();
    if (pid > 0){
        char message[32] = {0};
        snprintf(message, 32, "Hi from process %d", getpid());
	
        close(fd_child[0]); // close the read end of the pipe
        printf("Parent Sent : %s\n", message);
        write(fd_child[1], message, 32); // write to the pipe
        close(fd_child[1]); // close the write end of the pipe

        wait(NULL); // wait for child to exit

        read(fd_parent[0], message, 32); 
        printf("Parent received: %s\n", message);
        close(fd_parent[0]); // close the read end of the pipe

    }else{
        char message[32] = {0};

        close(fd_child[1]); // close the write end of the pipe
        read(fd_child[0], message, 32); // read from the pipe
        printf("Child received: %s\n", message);
        close(fd_child[0]); // close the read end of the pipe
        
        close(fd_parent[0]); // close the read end of the pipe
        snprintf(message, 32, "Hi from process %d", getpid());
        write(fd_parent[1], message, 32); // write to the pipe
        printf("Child Sent : %s\n", message);
        close(fd_parent[1]); // close the write end of the pipe
    }
    return 0;
}
