/**
 * Chatroom Lab
 * CS 241 - Spring 2016
 */
// gcc client.c -w -std=gnu99 -pthread -o client
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <string.h>
#include <pthread.h>

#include "chat_window.h"
#include "utils.h"

typedef struct info_t {
  char *host;
  char *port;
  char *username;
} info_t;

int serverSocket;

struct addrinfo hints, *result;
pthread_t threads[2];
void *writeVal, *readVal;

void close_client() {
  pthread_cancel(threads[0]);
  pthread_join(threads[0], &writeVal);
  pthread_cancel(threads[1]);
  pthread_join(threads[1], &readVal);
  shutdown(serverSocket, SHUT_RDWR);
}

void *run_client(void *information) {
  int s;
  info_t* info;
  serverSocket = socket(AF_INET, SOCK_STREAM, 0);
  int check_connect;

  info = (info_t*) information;
  memset(&hints, 0, sizeof(struct addrinfo));
  hints.ai_family = AF_INET;
  hints.ai_socktype = SOCK_STREAM;

  s = getaddrinfo(info->host, info->port, &hints, &result);
  if(s != 0) {
      fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(s));
      exit(1);
  }

  check_connect = connect(serverSocket, result->ai_addr, result->ai_addrlen);
  if(check_connect == -1) {
      perror("connect");
      //destory_windows();
      exit(1);
  }

  pthread_create(&threads[0], NULL, write_to_server, (void*)info->username);

  pthread_create(&threads[1], NULL, read_from_server, NULL);

  pthread_join(threads[0], &writeVal);
  pthread_join(threads[1], &readVal);
  
  return 0;
}
