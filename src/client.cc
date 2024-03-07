#include "client.h"

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <cstring>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>

#include "log.h"

prt::client::client(const char* ip, int port, int timeout) {
  this->state = prt::closed;
  if ((this->server_fd = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
    char warn_msg[100];
    sprintf(warn_msg, "Pyrite connect creation failed. Server addr: %s:%d", ip, port);
    prt::warn(warn_msg);
    return;
  }

  memset(&this->server_addr, 0, sizeof(this->server_addr));
  this->server_addr.sin_family = AF_INET;
  this->server_addr.sin_port = htons(port);
  this->server_addr.sin_addr.s_addr = INADDR_ANY;

  this->state = prt::established;
}

prt::client::~client() {
  close(this->server_fd);
}
