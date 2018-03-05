#ifndef CLIENT_HPP
#define CLIENT_HPP

#include <chrono>
#include <ratio>
#include <ctime>
#include "messenger.hpp"

class Client {
public:
  Client(const std::string&, const std::string&);
  ~Client();

  void init();
  void run();

private:
  std::string myIP;
  std::string serverIP;
  std::chrono::high_resolution_clock::time_point start;
  std::chrono::high_resolution_clock::time_point endt;
  Messenger *waiter;
};

#endif
