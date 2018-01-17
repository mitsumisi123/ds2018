
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <unistd.h>
#include <ctype.h>


int main(int argc, char* argv[]) {
	
    int so;
    char s[100];
    struct sockaddr_in ad;

    socklen_t ad_length = sizeof(ad);
    struct hostent *hep;

    // create socket
    int serv = socket(AF_INET, SOCK_STREAM, 0);
	
    // init address
    hep = gethostbyname(argv[1]);

    memset(&ad, 0, sizeof(ad));
    ad.sin_family = AF_INET;
    ad.sin_addr = *(struct in_addr *)hep->h_addr_list[0];
    ad.sin_port = htons(12345);
    

    // connect to server
    connect(serv, (struct sockaddr *)&ad, ad_length);
    
    while (1) {
        
    	FILE *f;
    	char buffer[512];
    	int words = 0;
    	char c;
     	f=fopen("labwork1.txt","r");               //open file labwork
	
    	while((c=getc(f))!=EOF)			   // read file from computer
	{	
		fscanf(f , "%s" , buffer);
		if(isspace(c)||c=='\t')
		words++;	
	}
	
       
      
	write(serv, &words, sizeof(int));           
     	rewind(f);
      
        char ch ;                                       //write file was read
      	while(ch != EOF)
      	{
		fscanf(f , "%s" , buffer);
		write(serv,buffer,512);
		ch = fgetc(f);
      	}

	printf("The file was sent successfully");
	close(serv);
	return 0;
    }

}
