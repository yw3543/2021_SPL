#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdlib.h>

int num_sending_signal;
int num_recv_signal=0;
int num_recv_ack = 0;
pid_t pid;

void recv_ack_handler(int sig){
	
	// insert your code
	num_recv_ack++;

	return;
}

void terminate_handler(int sig){
	
	// insert your code	
	printf("receiver: received %d signals\n", num_recv_signal);
	exit(0);
}

void sending_handler(int sig){	
	
	// insert your code
		
	printf("sender: sending %d signal\n", num_sending_signal-num_recv_ack);
	for(int i=num_recv_ack;i<num_sending_signal;i++){
		kill(pid, SIGUSR1);
	}

	alarm(1);
	return;
}

void sending_ack(int sig){
	
	// insert your code 
	printf("receiver: receive %d signal and sending acks\n", ++num_recv_signal);
	kill(pid, SIGUSR1);

	return;
}

int main(int argc, char *argv[]){
	num_sending_signal = atoi(argv[1]);
	printf("sending signal: %d\n", num_sending_signal);
	pid = fork();
	if (pid == 0){
		pid = getppid();
		
		// insert your code
		
		// signal using sending_ack
		// signal using terminate_handler

		signal(SIGUSR1, sending_ack);
		signal(SIGINT, terminate_handler);

		while(1){
			//int i = 0;
		}
	}
	else{
		
		// insert your code
		
		// signal using recv_ack_handler
		// signal using sending_handler

		signal(SIGUSR1, recv_ack_handler);
		signal(SIGALRM, sending_handler);

		alarm(1);

		while(1){
			//int i = 0;
			if(num_sending_signal==num_recv_ack){
				printf("all signals are sended\n");
				kill(pid, SIGINT);
				exit(0);
			}
		}
	}
	return 0;
}
