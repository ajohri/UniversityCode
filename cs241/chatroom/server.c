/**
 * Chatroom Lab
 * CS 241 - Spring 2016
 */
#include <string.h>
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <signal.h>
#include <netdb.h>
#include <unistd.h>
#include <arpa/inet.h>

#include "server.h"

void *processClient(void *arg);
void write_to_clients(const char *message, int len);

int endingServer;
int serverSocket;
struct addrinfo hints, *result;
int clients[MAX_CLIENTS];
int clientsConnected;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

void close_server(int signal2) {
  // Use a signal handler to call this function and close the server
  if(signal2  == SIGINT) {
    shutdown(serverSocket, SHUT_RDWR);
  }
}

int main(int argc, char **argv) {
    int s, optval = 1, i = 0, client_file_descriptor;
    pthread_attr_t attr;

    if(argc != 2) {
      fprintf(stderr, "Usage: %s <port>\n", argv[0]);
    }

    signal(SIGINT, close_server);

    serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    memset(&hints, 0, sizeof(struct addrinfo));
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = AI_PASSIVE; 
    pthread_attr_init(&attr);
    pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);
    
    s = getaddrinfo(NULL, argv[1], &hints, &result);
    if(s < 0) {
        fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(s));
        exit(1);
    }

    setsockopt(serverSocket, SOL_SOCKET, SO_REUSEPORT, &optval, sizeof(optval));

    if (bind(serverSocket, result->ai_addr, result->ai_addrlen) != 0) {
        perror("bind");
        exit(1);
    }

    if(listen(serverSocket, MAX_CLIENTS)) {
        perror("listen");
        exit(1);
    }

    while((client_file_descriptor = accept(serverSocket, NULL, NULL)) && (clientsConnected < MAX_CLIENTS)) {
      
      printf("Connection Made: client_fd = %d\n", client_file_descriptor);
      pthread_mutex_lock(&mutex);
      clientsConnected++;
      pthread_mutex_unlock(&mutex);
      clients[i] = client_file_descriptor;
      pthread_t thread;
      pthread_create(&thread, &attr,  processClient, (void *)(intptr_t)client_file_descriptor);
      i++;

    }
}

// DO NOT MODIFY THIS FUNCTION
void write_to_clients(const char *message, int len) {
  int i;
  for (i = 0; i < clientsConnected; i++) {
    write(clients[i], message, len);
  }
}

// DO NOT MODIFY THIS FUNCTION (BUT DO USE IT)
void *processClient(void *arg) {
  int client_fd = (intptr_t)arg;
  int client_is_connected = 1;
  while (client_is_connected) {

    char buffer[MSG_SIZE];
    int len = 0;
    int num;

    // Read until client sends eof or \n is read
    while (1) {
      num = read(client_fd, buffer + len, MSG_SIZE);
      len += num;

      if (!num) {
        client_is_connected = 0;
        break;
      }
      if (buffer[len - 1] == '\n')
        break;
    }

    // Error or client closed the connection, so time to close this specific
    // client connection
    if (!client_is_connected) {
      printf("User %d left\n", client_fd);
      break;
    }

    write_to_clients(buffer, len);
  }

  close(client_fd);
  pthread_mutex_lock(&mutex);
  clientsConnected--;
  pthread_mutex_unlock(&mutex);
  return NULL;
}
