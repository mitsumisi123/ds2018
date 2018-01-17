#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <unistd.h>
int main() {
	
    int ss, cli, pid;
    struct sockaddr_in ad;
    char s[100];
    socklen_t ad_length = sizeof(ad);

    // create the socket
    ss = socket(AF_INET, SOCK_STREAM, 0);

    // bind the socket to port 12345
    memset(&ad, 0, sizeof(ad));
    ad.sin_family = AF_INET;
    ad.sin_addr.s_addr = INADDR_ANY;
    ad.sin_port = htons(12345);
    bind(ss, (struct sockaddr *)&ad, ad_length);
    printf("bind successfully\n");

    // then listen
    listen(ss, 2);
    printf("listening...\n");

    while (1) {
        // an incoming connection
        cli = accept(ss, (struct sockaddr *)&ad, &ad_length);

        pid = fork();
        if (pid == 0) 
	{
            // I'm the son, I'll serve this client
            	FILE *fp;
         	int ch = 0;
		char buffer[512];
           	fp = fopen("labwork1_recv.txt","a");            		//open (create file name labwork1_recv.txt) 
            	int words;
		read(cli, &words, sizeof(int));					//read from client
            	
          	while(ch != words)						// write data to file labwork1_recv.txt
       	   	{
        	 	read(cli ,buffer, 512); 
	   	 	fprintf(fp , " %s" , buffer);   
		 	
		 	ch++;
	   	}
     		printf("The file was received successfully\n");
	   	
	
            	return 0;
        }
        else {
            // I'm the father, continue the loop to accept more clients
		
            continue;
        }
	// disconnect
    	close(cli);
    }
    

}
