/* Use standard echo server; baseline measurements for nonblocking version */
#include	"unp.h"
// textbook p114 str_cli11 为了捕获SIGPIPE信号


void sig_pipe( int signo )
{
	(void)signo;
	printf("SIGPIPE received!\n");
}


int
main(int argc, char **argv)
{
	int					sockfd;
	struct sockaddr_in	servaddr;

	if (argc != 2)
		err_quit("usage: tcpcli <IPaddress>");
	
	Signal( SIGPIPE, sig_pipe );

	sockfd = Socket(AF_INET, SOCK_STREAM, 0);

	bzero(&servaddr, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_port = htons(SERV_PORT);
	Inet_pton(AF_INET, argv[1], &servaddr.sin_addr);

	Connect(sockfd, (SA *) &servaddr, sizeof(servaddr));

	str_cli(stdin, sockfd);		/* do it all */

	exit(0);
}
