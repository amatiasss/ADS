#include "client.hpp"
#include <cstdio>
#include <iostream>     // std::cout
#include <fstream>      // std::ifstream
using namespace std;

Client::Client(const string& ipServer, const string& ipClient):
                                                                myIP(ipClient),
                                                                serverIP(ipServer)
{
  //envia IP do Cliente para o servidor
  Messenger sender(ipServer.c_str());
  Package pkg(ipClient, "void");
  sender.Send(pkg);
  // configura a porta q o mensageiro vai ficar escutando
  waiter =  new Messenger();
}

Client::~Client(){
  if(waiter != NULL) delete waiter;
}

void Client::run(){
  while (true) {
    waiter->Accept();
    Package *pkg = waiter->Recv();
    waiter->Close();

    if(!myIP.compare(pkg->getip())){
      string message = pkg->getmessage();
      //computa o tempo de resposta do SO
      start = chrono::high_resolution_clock::now();
      system("./sleep 0");
      endt = chrono::high_resolution_clock::now();
      long long sleep0 = chrono::duration_cast<chrono::nanoseconds>(endt - start).count();
      //computa agora o tempo de utilização
      start = chrono::high_resolution_clock::now();
      system(message.c_str());
      endt = chrono::high_resolution_clock::now();
      //envia o tempo de utilização para o servidor
      long long diff = chrono::duration_cast<chrono::nanoseconds>(endt - start).count();
      Messenger sender(serverIP.c_str());
      Package pkg(myIP, to_string(diff-sleep0));
      sender.Send(pkg);
    }
  }
}
