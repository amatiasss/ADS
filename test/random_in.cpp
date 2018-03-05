#include<cstdlib>
#include<ctime>
#include <cstdio>
using namespace std;

#define MAX_RANGE 100000000

int main(int argc, char const *argv[]) {
  std::srand(std::time(0));
  for (int i = 0; i < 10; i++) {
      int random = std::rand() % MAX_RANGE + 1;
      printf("./sleep %d \n", random);
  }
  return 0;
}
