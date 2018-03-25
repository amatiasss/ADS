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

Proceda com a configuração padrão do LXD(Digite Enter para tudas as opções). Caso ocorra algum erro de "lxg group" ou utilize sudo para executar.

Para instalar o nosso primeiro container como servidor 'server' com o exeutamos o seguinte comando:

```
$ lxc launch ubuntu:16.04 server
```
Para entrar no container server faça:

```
$ lxc exec server -- /bin/bash
```

A partir deste ponto você estará dentro de uma máquina virtual linux. Execute os seguintes comandos para atualizar o SO e instalar aplicações nescessárias e, sair do contaiter.

```
# apt-get update
# apt-get install git g++ make -y
# git clone https://github.com/amatiasss/ADS.git
# exit
```

Agora, com tudo configurado, clonaremos o server em quantas maquinas clintes forem necessárias para a execução dos testes. Para isso criaremos primeiro uma cópia do server e depois
a transformaremos em uma imagem que pode ser usada para criar os clientes:

```
$ lxc snapshot server copy
$ lxc publish server/copy --alias img-server
```
Para criarmos as clientes a partir de img-server, faz-se:

```
$ lxc launch img-server client-1
$ lxc launch img-server client-2
        ...
$ lxc launch img-server client-N
```

Vizualide com list:

```
$ lxc list
```
Utilize o list também para vizualizar o IP de cada container. Isto será exencial para a próxima etapa.

```
IP server:   10.17.116.137
IP client-1: 10.17.116.93
    ...
```

Agora, finalmente, estamos prontos para execução do sistema. Abra um terminal(Abas ou divisões) para cada container, iniciando pelo server fazer a execução do sistema.

```
$ lxc exec server -- /bin/bash
# cd ADS/server/ && make
#./server input.txt 5
Servidor aguardando conexão de clientes

```

De modo análogo, inicie cada um dos clientes em seus respectivos terminais:

```
$ lxc exec client-1 -- /bin/bash
# cd ADS/client/ && make
#./client 10.17.116.137 10.17.116.93
Servidor aguardando conexão de clientes

```

Após a execução de todos os clientes, o server escreverá os resultados na pasta ADS/server/result. E, apresentará mensagens como segue:

```
#./server input.txt 5
Servidor aguardando conexão de clientes
Clientes Conectados: 1
Clientes Conectados: 2
      ...
Clientes Conectados: 5
Iniciando envio de mensagens
salvando arquivo: result/message_1.txt
salvando arquivo: result/message_2.txt
       ...
salvando arquivo: result/message_5.txt
```
