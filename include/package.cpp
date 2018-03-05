#include "package.hpp"
using namespace std;

Package::Package(){}

Package::Package(const string _ip, const string msg):
                                                      ip(_ip),
                                                      message(msg)
{}

Package::Package(const Package& rhs) : ip(rhs.ip){}

Package::~Package(){}

Package& Package::operator=(const Package& rhs) {
    if(this != &rhs){
      ip = rhs.ip;
      message = rhs.message;
    }
    return *this;
}

void Package::setip(const string _ip){
  ip = _ip;
}

string Package::getip() const{
  return ip;
}

void Package::setmessage(const string msg){
  message = msg;
}

string Package::getmessage() const {
  return message;
}
