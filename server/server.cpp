#include "server.hpp"
#include <cstdio>
#include <iostream>     // std::cout
#include <fstream>      // std::ifstream
#include <iomanip>      // std::setprecision
using namespace std;

Server::Server(const string& input, const int nClients, const bool nnsec):
                          numClients(nClients),
                          status(INIT),
                          nanosec(nnsec),
                          task_index(0)
{
  //carrega dados de entrada
  ifstream file(input, ifstream::in);
  if (file.is_open()) {
    string line;
    while (getline(file, line)) messages.push_back(line);
    file.close();
  } else printf("Erro ao carregar arquivo de mensagens!!\n\n");

  it = messages.begin();
  //inicializa o mensageiro
  waiter = new Messenger();
  //cria a pasta resultado
  system("mkdir result");
}

Server::~Server(){
  if(waiter != NULL) delete waiter;
}

void Server::init(){
  int connecteds = 0;

  while(connecteds < numClients){
    waiter->Accept();
    Package *pkg = waiter->Recv();
    waiter->Close();

    if(pkg != NULL) {
      client cli;
      cli.ip = pkg->getip();
      clients.push_back(cli);
      connecteds++;

      printf("Clientes Conectados: %d\n", connecteds);
    }
  }
  status = READY;
}

void Server::run(){
  while (true) {
    if(status == READY){
      ++task_index;
      //envia a mensagen da vez para todos os clientes
      for (list<client>::iterator itc = clients.begin(); itc != clients.end(); ++itc)
        sendMessage(itc);
      //muda para o estado de espera de clientes
      status = WAITING;
    }else if(status == WAITING){
              unsigned recveds = 0;
              //printf("%s\n", "arguardando resposta dos clientes");
              while(recveds < clients.size()){
                waiter->Accept();
                Package *pkg = waiter->Recv();
                //coleta tempo do recebimento
                auto endt = chrono::high_resolution_clock::now();
                waiter->Close();
                //salva resultado na lista de clientes
                SaveTU(pkg, endt);
                recveds++;
              }
              //prox mensagem
              ++it;
              SaveFile();
              status =  READY; //muda para o estado de envio das mensagens
          }
          //encerra o estado de operação do server
          if(it == messages.end()) break;
    }
}

void Server::sendMessage(const list<client>::iterator itc){
  Messenger sender(itc->ip.c_str());
  Package pkg(itc->ip, *it);
  //get init time from message
  itc->start = chrono::high_resolution_clock::now();
  sender.Send(pkg);
}

void Server::SaveTU(const Package *pkg, chrono::high_resolution_clock::time_point end){
  string::size_type sz;
  //--------
  for (list<client>::iterator itc = clients.begin(); itc != clients.end(); ++itc)
    if(itc->ip == pkg->getip()){
      itc->endt = end;
      itc->TU = stoll(pkg->getmessage(), &sz);
      break;
    }
}

void Server::SaveFile(){
  string filename = "result/message_"+to_string(task_index)+".txt";
  printf("salvando arquivo: %s\n", filename.c_str());

  ofstream outfile(filename);
  outfile << "IP\tTS\tTU" << endl;

  for (list<client>::iterator itc = clients.begin(); itc != clients.end(); ++itc){
    long long diff = chrono::duration_cast<chrono::nanoseconds>(itc->endt - itc->start).count();
    long long TS   = diff - itc->TU;

    if(!nanosec){
      outfile << fixed << setprecision(9);
      outfile << itc->ip << "\t" <<  (TS/1000000000.0)/2 << "\t" << itc->TU/1000000000.0 << endl;
    }else  outfile << itc->ip << "\t" <<  TS/2 << "\t" << itc->TU << endl;
  }
  outfile.close();
}
