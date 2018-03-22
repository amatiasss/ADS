# ADS
Sistema Distribuído Para Teste de Performance do Banco de Dados SQLite

# Guia Prático

Estas instruções irão te ajudar a copiar o projeto e executá-lo em sua máquina local com o propósito
de desenvolvimento e testes. Veja as notas de execução e testes para saber como executar.


### Pré-requisitos

Para compilar o projeto são necessários compilador g++ e o GNU-Makefile

```
$ sudo apt-get install g++ make -y
```

### Compilando

Após feito o clone do projeto em sua máquina local, selecione a pasta da aplicação
que irá executar e compile usando makefile:

```
$ cd ADS/server
$ make
```

ou ainda

```
$ cd ADS/client
$ make
```

Lembrando que para o sistema funcionar corretamente serão necessários um servidor e, pelo menos,
um cliente.

## Executando

Primeiro, executo o servidor

```
$ ./server {arquivo_de_entrada} {número_de_clientes} {opcional}
```
O parâmetro opcional quando informado configura a escala de tempo de resposta para nanosegundos.
A escala de segundos é a escala padrão.

Por exemplo, para executar com 3 clientes com o tempo de resposta em nanosegundos:

```
$ ./server input.txt 3 y
```

Depois deve-se executar os clientes na quantidade informada ao servidor

```
$ ./client {ip_do_servidor} {ip_local}
```

como

```
$ ./client 10.85.97.223 10.85.97.18
```

### Arquivo de Entrada e Resultados

O arquivo de entrada é um arquivo texto contendo chamadas de execução de programas

```
./prog 100 1000
./sleep  2309423
...
```

Cada linha representa uma mensagem que comandará uma ação no sistema do cliente,
para cada uma destas mensagens será gerado um arquivo da saída informando os tempos
de serviço e de utilização de todos os clientes. Os arquivos são salvos na pasta
'result'.

```
IP    TS    TU
10.85.97.82	0.005691549	0.249183218
10.85.97.18	0.006925380	0.253248429
10.85.97.26	0.005955995	0.162273003
```

### Executando a etapa de Testes


```
Em construção
```

## Executando testes em Containers

Os testes em Containers serão feitos através do ![LXD](https://linuxcontainers.org/lxd/introduction/). Para iniciar o procedimento faremos a instalação e a configuração padrão da aplicação, como segue:

Instalação para Ubuntu 16.04 LTS, caso sua distribuição seja diferente consulte o ![guia de instalação](https://linuxcontainers.org/lxd/getting-started-cli/).

```
$ sudo apt install lxd lxd-client -y
```

Re-abra a sessão de usuário e, para iniciar a configuração, digite:

```
$ sudo lxd init
```

Proceda com a configuração padrão do LXD. Caso ocorra algum erro de "lxg group"
