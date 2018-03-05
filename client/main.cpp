#include <cstdio>
#include <cstdlib>
#include <string>
using namespace std;

#include "client.hpp"

int main(int argc, char **argv){

    if (argc != 3) {
      printf("%s\n\n", "Uso do Programa: ./client <ip_server> <ip_hostlocal>");
      exit(EXIT_FAILURE);
    }

    string ip_server(argv[1]);  string ip_hostlocal(argv[2]);
    Client client(ip_server, ip_hostlocal);
    client.run();

    return 0;
}
