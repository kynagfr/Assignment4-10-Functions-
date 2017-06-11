
#include<stdio.h>	//printf
#include<string.h>	//strlen
#include<sys/socket.h>	//socket
#include<arpa/inet.h>	//inet_addr
#include <unistd.h>   //gethostname
#include <netdb.h>   //gethostbyaddress
#include <sys/types.h>
#define MAX_HOSTNAME   255
#define BLOCKING
#define NONBLOCKING

int main(int argc , char *argv[])
{
	int getsockname(int sock, struct sockaddr *addr, socklen_t *len);
	int getpeername(int sock, struct sockaddr *addr, socklen_t *len);
	int gethostname(char *name, size_t len);
	int sock;
	struct sockaddr_in localaddr, peeraddr, saddr, addr;
	struct in_addr in;
	struct servent *sp;
	int ret, _la_len, ret_la, ret_pa, ret_hn, ret_oob, on, ret_nb, mode;
	char hostbuffer[MAX_HOSTNAME+1];
	char buffer[MAX_BUFFER], oobdata;
	

	//Create socket
	sock = socket(AF_INET , SOCK_STREAM , 0);
	if (sock == -1)
	{
		printf("Could not create socket");
	}
	puts("Socket created");


	/*CHAPTER 4 ADVANCED SOCKETS FUNCTIONS*/

	//1.Using getsockname 
	
	la_len = sizeof(localaddr);
	
	ret_la = getsockname(socket,(struct sockaddr_in *)&localaddr, &la_len);

	if (ret_la == 0)
	{
		printf("Local Address is : %s\n", inet_ntoa(localaddr.sin_addr));
		printf("Local Port is : %d\n", local addr.sin_port);
	}
	

	//2.Using gethostname

	ret_hn = gethostname(hostbuffer, MAX_HOSTNAME);
	if(ret_hn == 0)
	{
		printf("Host name is %s\n", hostbuffer);
	}


	//3.Using getpeername
	ret_pa = getpeername(socket,(struct sockaddr_in *)&peeraddr, &pa_len);
	
	if (ret == 0)
	{
		printf("Peer Address is : %s\n", inet_ntoa(peeraddr.sinaddr));
		printf("Local Port is : %d\n", peeraddr.sin_port);
	}

	
	//4.Using gethostbyname
	
	int i;
	hp = gethostbyname("www.google.com")

	if(hp)	
	{
		printf("Host name is %s\n", hp->h_name);
		printf("Host Address type is %d\n", hp->h_addrtype);
		
		i=0;
		printf("Aliases: \n");

		while(1)
		{
			if(hp->h_aliases[i])
			{
				printf("Host aliases[%d] = %s\n", i,hp->h_aliases[i]);
				i++;
			}
			else break;
		}
		
		i=0;
		printf("Address:\n");

		while(1)
		{
			if(hp->h_addr_list[i])
			{
				struct in_addr theAddr;
				memcpy( &theAddr,s_addr,hp->h_addr_list[i],sizeof(theAddr,s_addr));
				printf("Host Address List[%d] = %s\n", i,inet_ntoa(theAddr));
				i++;
			}
			else break;
		}
		

			
	}


	//5.Using getservbyport
		
	sp = getservbyport(htons(80), NULL);
	
	if(sp)
	{
		printf("Service %s is at port %d\n", sp->s_name, ntohs(sp->s_port));
	}*/

	




	/*CHAPTER 6 ADVANCED SOCKETS PROGRAMMING TOPICS*/
	
	//1.Out-Of-Band(OOB) Data
	
	on = 1;
	ret_oob = setscockopt(sock, SOL_SOCKET, SO_OOBINLINE, &on, sizeof(on));
	
	if(sockatmark(sock))
	{
		ret_oob = read(sock, &oobdata, 1);
	} 
	else
	{
		ret_oob = read(sock,buffer,sizeof(buffer));
	}


	//2.Nonblocking Socket
	sock = socket(AF_INET, SOCK_STREAM, 0);
	
	mode = NONBLOCKING;

	ret_nb = ioctl(sock, FIONBIO, mode);

	
	//3.Resolving a Domain Name
	struct sockaddr_in saddr;
	char address[]={"192.168.1.1"};

	if(saddr.sin_addr.s_addr = 0xffffffff)
	{
		struct hostent *hptr = (struct hostent *)gethostbyname(address);
		
		if(hptr==NULL)
		{
			printf("Couldnt resolve the address");
		}
		else
		{
			struct in_addr **addrs;
			addrs = (struct in_addr **)hptr->h_addr_list;
			memcpy(&saddr.sin_addr, **addrs, sizeof(struct in_addr));
		}
	}



	//4.Connectionless Datagram Sockets
	/*Datagram socket in an unconnected state*/
	
	sock = socket (AF_INET, SOCK_DGRAM, 0);
	
	memset(&saddr, 0, sizeof(saddr);
	saddr.sin_family = AF_INET;
	saddr.sin_port = htons(MY_PORT);
	saddr.sin_addr.s_addr = inet_aton("192.168.1.1");

	ret = sendto(sock,buffer,strlen(buffer),(struct sockaddr_in *)&saddr, sizeof(saddr));

	

	//5.Determining Peer Information
	
	sock = socket(AF_INET, SOCK_STREAM, 0);
	
	len = sizeof(peeraddr);
	ret = getpeername(sock,(struct sockaddr_in *) &peeraddr, &len);

	printf("Peer Address is : %s\n", inet_ntoa(peeradd.sin_addr));
	printf("Peer port is: %d/n", nthos(peeraddrs.sin_port));
	
	return 0;
	
}

