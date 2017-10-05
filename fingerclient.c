/*
** client.c: sends own finger info to server over socket spec by user
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <netdb.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <sys/socket.h>

#include <arpa/inet.h>

//#define PORT "3490" // the port client will be connecting to

#define MAXDATASIZE 1000 // max number of bytes we can get at once

// get sockaddr, IPv4 or IPv6:
void *get_in_addr(struct sockaddr *sa)
{
    if (sa->sa_family == AF_INET) {
        return &(((struct sockaddr_in*)sa)->sin_addr);
    }

    return &(((struct sockaddr_in6*)sa)->sin6_addr);
}

int main(int argc, char *argv[])
{
    int sockfd, numbytes;
    char buf[MAXDATASIZE];
    struct addrinfo hints, *servinfo, *p;
    int rv;
    char s[INET6_ADDRSTRLEN];

    if (argc != 2) {
        fprintf(stderr,"Usage: fingerclient username@hostname:server_port\n"); //vs client hostname
        exit(1);
    }
    char *username = strsep(&argv[1], "@");
    char *host = strsep(&argv[1], ":");
    char *port = strsep(&argv[1], ":");

    memset(&hints, 0, sizeof hints);
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;
    //PROCESS INPUT HERE

    if ((rv = getaddrinfo(host, port, &hints, &servinfo)) != 0) { //correct PORT for specified
        fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(rv));
        return 1;
    }
    //Ok, connected to remote server if all goes well at this point.
    // loop through all the results and connect to the first we can
    for(p = servinfo; p != NULL; p = p->ai_next) {
        if ((sockfd = socket(p->ai_family, p->ai_socktype,
                             p->ai_protocol)) == -1) {
            perror("fingerserver: socket issue");
            continue;
        }

        if (connect(sockfd, p->ai_addr, p->ai_addrlen) == -1) {
            close(sockfd);
            perror("fingerclient: connect issue");
            continue;
        }

        break;
    }

    if (p == NULL) {
        fprintf(stderr, "fingerclient: failed to connect\n");
        return 2;
    }

    inet_ntop(p->ai_family, get_in_addr((struct sockaddr *)p->ai_addr),
              s, sizeof s);
    //printf("client: connecting to %s\n", s);

    freeaddrinfo(servinfo); // all done with this structure

    if (send(sockfd, username, sizeof(username), 0) == -1)
        perror("send error on client");

    if ((numbytes = recv(sockfd, buf, MAXDATASIZE-1, 0)) == -1) {
        perror("error with receipt of data");
        exit(1);
    }

    buf[numbytes] = '\0';

    printf("fingerclient: received message: \n '%s'\n",buf);

    close(sockfd);

    return 0;
}