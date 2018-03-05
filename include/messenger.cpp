#include "messenger.hpp"
using namespace std;

#define DOOR 6666

//construtor
Messenger::Messenger(void){
  sock = socket(AF_INET, SOCK_STREAM, 0);
  sockaddr_in serv;
  serv.sin_family = AF_INET;
  serv.sin_addr.s_addr = INADDR_ANY;
  serv.sin_port = htons (DOOR);

  memset(&(serv.sin_zero),0x00,sizeof(serv.sin_zero));
  sockSize = sizeof(struct sockaddr_in);

  bind(sock,(struct sockaddr *)&serv,sizeof(struct sockaddr));
  listen(sock,1);

}

Messenger::Messenger(const char *ip){
  sock = socket(AF_INET, SOCK_STREAM, 0);

  serv.sin_family = AF_INET;
  serv.sin_addr.s_addr = inet_addr(ip);
  serv.sin_port = htons(DOOR);

  memset (&(serv.sin_zero), 0x00, sizeof (serv.sin_zero));
  if(connect (sock, (struct sockaddr *)& serv, sizeof (struct sockaddr)) != 0){
    printf("Servidor nao Encontrado\n");
    exit(EXIT_FAILURE);
  }
}

void Messenger::Accept(){
  client = accept(sock, (struct sockaddr *) &serv, &sockSize);
}

void Messenger::Send(Package& pkg){
  StringBuffer sb;
  Writer<StringBuffer> writer(sb);
  pkg.Serialize(writer);

  string msg = sb.GetString();
  send(sock, msg.c_str(), static_cast<size_t>(msg.size()), 0);
}

Package* Messenger::Recv(){
  int cread = recv(client, buffer, MAX_BUFFER, 0); buffer[cread] = '\0';

  Document json;
  if (json.Parse(buffer).HasParseError()){
    return NULL;
  }

  Package *pkg = new Package(json["ip"].GetString(), json["message"].GetString());

  return pkg;
}

void Messenger::Close(){
  close(client);
}

//Destrutor
Messenger::~Messenger(){
  close(sock);
}
