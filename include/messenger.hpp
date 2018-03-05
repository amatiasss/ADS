#ifndef MESSENGER_H
#define MESSENGER_H

#include <unistd.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <sys/socket.h>

#include <string>
#include <cstdlib>
#include <cstdio>

#include "package.hpp"
#include "rapidjson/prettywriter.h" // JSON para string
#include "rapidjson/document.h"
#include "rapidjson/error/en.h"

//definição de constantes
#define MAX_BUFFER 1024
using namespace rapidjson;


class Messenger {
    int sock;
    struct sockaddr_in serv;
    char buffer[MAX_BUFFER];
    int client;
    socklen_t sockSize;

public:
  //construtor
  Messenger(void);
  Messenger(const char *ip);
  void Accept();
  void Send(Package& pkg);
  Package* Recv();
  void Close();
  //Destrutor
  ~Messenger();
};


#endif
