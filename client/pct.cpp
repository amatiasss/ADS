#include <cstdio>
#include <cstdlib>
#include <cstring>
using namespace std;

int main(int argc, char** argv){
  if(argc != 3){
    printf("%s\n\n", "Uso do Programa: ./prog <tam_matriz> <repeticoes>");
    exit(EXIT_FAILURE);
  }

  int i, j, k, N = atoi(argv[1]);
  int BLOCK = atoi(argv[2]);
  int mat1[N][N], mat2[N][N];

  for (i = 0; i < N; i++)
    for (j = 0; j < N; j++)
        mat1[i][j] = mat2[i][j] = 1;

  for (k = 0; k < BLOCK; k++)
    for (i = 0; i < N; i++)
      for (j = 0; j < N; j++)
          mat1[i][j] = mat2[i][j] = 1;

  return 0;
}
