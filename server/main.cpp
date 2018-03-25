#include <cstdio>
#include <cstdlib>
#include <string>
#include "server.hpp"
using namespace std;


int main(int argc, char **argv){

    if (argc < 3 || argc > 4) {
      printf("%s\n", "Uso do Programa: ./server <nome_arquivo_entrada> <num_clientes> [opc]");
      exit(EXIT_FAILURE);
    }

    string input(argv[1]);
    printf("%s\n", "Instanciando o servidor");
    Server serv(input, atoi(argv[2]), argc == 4);
    printf("%s\n", "Servidor aguardando conexão de clientes");
    serv.init();
    printf("%s\n", "Iniciando envio das mensagens");
    serv.run();
    printf("%s\n", "Encerrando servidor");
    return EXIT_SUCCESS;
}
