#ifndef SERVER_HPP
#define SERVER_HPP

#include <string>
#include <vector>
#include <list>
#include <iterator>
#include <chrono>
#include <ratio>
#include <ctime>
#include "messenger.hpp"

enum ENUM_STATUS {INIT, READY, WAITING};

struct client{
  std::string ip;
  std::chrono::high_resolution_clock::time_point start;
  std::chrono::high_resolution_clock::time_point endt;
  long long TU;
};

class Server {
public:
  Server(const std::string& input, const int nClients, const bool nnsec);
  ~Server();

  void init();
  void run();

private:
  int numClients;
  ENUM_STATUS status;

  void sendMessage(const std::list<client>::iterator);
  void SaveTU(const Package*, std::chrono::high_resolution_clock::time_point);
  void SaveFile();

  bool nanosec;
  int task_index;
  std::vector<std::string> messages;
  std::vector<std::string>::iterator it;
  std::list<client> clients;

  Messenger *waiter;

};

#endif
