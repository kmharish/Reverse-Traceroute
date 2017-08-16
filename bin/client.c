/* +++++++++++++++++ REVERSE TRACEROUTE CLIENT +++++++++++++++++ */

/* ========================== Headers ========================== */

#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<errno.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<fcntl.h>

/* ============================ Macros ========================  */

#define PORT_NO 7007
#define MAX_FILE_LENGTH 4000
#define MAX_CMD_LENGTH 256
#define MAX_ADDR_LENGTH 56

/* =====================  Global variables ====================  */

char rtr_info[MAX_FILE_LENGTH],*ip_addr;
struct sockaddr_in serv_addr;

/* ========================== Functions =======================  */

int initialize_socket()	{
	int sockfd ;
	sockfd = socket(AF_INET,SOCK_STREAM,0); 					// Create a socket
	bzero((char*)&serv_addr,sizeof(serv_addr)); 					// Clear memory 
	serv_addr.sin_family=AF_INET;
	serv_addr.sin_port=htons(PORT_NO);
	serv_addr.sin_addr.s_addr=inet_addr(ip_addr);					// Take IP from CLA
	return sockfd;
}
int establish_connection(int sockfd)	{
	int err;
	err = connect(sockfd,(struct sockaddr*)&serv_addr,sizeof(serv_addr)); 		// Try connecting to server
	if(err == -1)	{
		perror("Connection failed !");
		exit(1);
	}
	return sockfd;
}
void send_query(int sockfd)	{
	int err;
	err=write(sockfd,"traceroute",MAX_CMD_LENGTH);					// Send Reverse Traceroute query
	if(err == -1)	{
		perror("Write function failed");
		exit(1);
	}
}
void recv_rtr_info(int sockfd)	{	
	int err;
	bzero(rtr_info,MAX_FILE_LENGTH);						// Clear memory
	err = recv(sockfd,rtr_info,MAX_FILE_LENGTH-1,0); 				// Receive the processed request
	if(err == -1)	{
		perror("error in receiving");
		exit(1);
	}	
	printf("%s\n",rtr_info);							// Display RTR information
}

int main(int argc, char **argv)
{
	int e,sockfd;
	ip_addr=argv[1];
	sockfd = initialize_socket();	
	sockfd=establish_connection(sockfd);
	send_query(sockfd);
	recv_rtr_info(sockfd);
	close(sockfd);
	return 0;
}
