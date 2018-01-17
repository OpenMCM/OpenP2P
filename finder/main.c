/*

    P2P Finder server -- Theodor Johansson
    This code was based on code for an echo server that I found here:
    https://github.com/mafintosh/echo-servers.c/blob/master/tcp-echo-server.c

*/


#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>

#include "set/set.h"

#define BUFFER_SIZE 1024
#define on_error(...) { fprintf(stderr, __VA_ARGS__); fflush(stderr); exit(1); }

int is_find_request(char *message, int mess_len) {
  if(mess_len >= 1 && *message == 'F') {
    return 1;
  }
  else {
    return 0;
  }
}

int is_discover_request(char *message, int mess_len) {
  if(mess_len >= 1 && *message == 'D') {
    return 1;
  }
  else {
    return 0;
  }
}

void process_message(char *message, int mess_len) {
  return;
  if(is_find_request(message, mess_len)) {
    //Process find request
  }
  else if(is_discover_request(message, mess_len)) {
    //Process discover request
  }
  else {
    //Error case
  }
}

int main (int argc, char *argv[]) {
  if (argc < 2) on_error("Usage: %s [port]\n", argv[0]);

  int port = atoi(argv[1]);

  int server_fd, client_fd, err;
  struct sockaddr_in server, client;
  char buf[BUFFER_SIZE];

  server_fd = socket(AF_INET, SOCK_STREAM, 0);
  if (server_fd < 0) on_error("Could not create socket\n");

  server.sin_family = AF_INET;
  server.sin_port = htons(port);
  server.sin_addr.s_addr = htonl(INADDR_ANY);

  int opt_val = 1;
  setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, &opt_val, sizeof opt_val);

  err = bind(server_fd, (struct sockaddr *) &server, sizeof(server));
  if (err < 0) on_error("Could not bind socket\n");

  err = listen(server_fd, 128);
  if (err < 0) on_error("Could not listen on socket\n");

  printf("Server is listening on %d\n", port);

  while (1) {
    socklen_t client_len = sizeof(client);
    client_fd = accept(server_fd, (struct sockaddr *) &client, &client_len);

    if (client_fd < 0) on_error("Could not establish new connection\n");

    //TODO: Fork here

    while (1) {
      // read contains the length of the message (+1 if you count '/n')
      // (which it does)
      int read = recv(client_fd, buf, BUFFER_SIZE, 0);

      if (!read) {
        break;
      }
      if (read < 0) on_error("Client read failed\n");

      process_message(buf, BUFFER_SIZE, client_fd);
      printf("read = %d\nResponding to client...\n", read);
      // Gonna need this code later
      //err = send(client_fd, buf, read, 0);
      if (err < 0) on_error("Client write failed\n");
    }
  }

  return 0;
}
