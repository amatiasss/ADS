#include <chrono>
#include <ratio>
#include <ctime>
#include <cstdlib>
#include <vector>
#include <fstream>
#include <string>
#include <cmath>
#include <iomanip>
using namespace std;

#define N 5

int main(int argc, char const *argv[]) {
  //vetor que armazenará as mensagens
  vector<string> messages;
  //abrindo arquivo de entrada
  ifstream file("input.txt", ifstream::in);
  if (file.is_open()) {
    string line;
    while (getline(file, line)) messages.push_back(line); //carrega as mensagens
    file.close();
  } else printf("Erro ao carregar arquivo de mensagens!!\n\n");
  //executa teste com a repetiçao de 5 vezes
  std::vector<vector<long long>> times(messages.size(), vector<long long>(5));
  for (uint i = 0; i < N; i++) {
    int index = 0;
    for(auto &message: messages){
      auto start = chrono::high_resolution_clock::now(); //coleta tempo inicial
      system(message.c_str());    //executa mensagem
      auto endt = chrono::high_resolution_clock::now(); //coleta tempo final
      //calcula a duração da tarefa
      times[index++][i] = chrono::duration_cast<chrono::nanoseconds>(endt - start).count();
    }
  }
  //calculando a média populacional
  std::vector<long long> means(times.size(), 0);
  for (uint i = 0; i < times.size(); i++){
    for (int j = 0; j < N; j++) means[i] += times[i][j];
    means[i] /= N;
  }
  //calculando a variancia populacional
  std::vector<long long> var(times.size(), 0);
  for (uint i = 1; i < times.size(); i++){
    for (int j = 0; j < N; j++) var[i] += (times[i][j] - means[i]) * (times[i][j] - means[i]);
    var[i] /= N;
  }
  //salvando o resultado de analise
  ofstream outfile("result.txt");
  // outfile << fixed << setprecision(9);
  for (uint i = 1; i < times.size(); i++)
    outfile << means[i]-means[0]/*1000000000.0*/ << " +- " << sqrt(var[i])/*1000000000.0*/
            << endl;
  //fechando o arquivo de saída
  outfile.close();

  return 0;
}
