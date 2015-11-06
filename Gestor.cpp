#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <signal.h>
#include <unistd.h>
#include <iostream>
#include <vector>
#include <map>
#include <fstream>
#include "datosCliente.h"
#include "empleados.h"

using namespace std;

void lectura(vector< datosCliente > &g,string nom)
{
	ifstream archivo (nom.c_str());
    int x, cont=0, cont2=0, i=0;
    while(archivo>>x)
    {

		if(x==1)
		{
			g[cont2].follow[cont]=0;
			++i;
		}
		++cont;
		if(cont==10)
		{
			cont=0;
			++cont2;
		}
    }
    archivo.close();
}

int main (int argc, char **argv)
{

  int fd, pid, n, bytes;

	vector< datosCliente> g;
    for(int i=0; i<10 ;++i)
    {
		datosCliente dc;
		dc.pid=i;
		g.push_back(dc);
	}

  mode_t fifo_mode = S_IRUSR | S_IWUSR;

  unlink(argv[1]);
  if (mkfifo (argv[1], fifo_mode) == -1) {
     perror("mkfifo");
     exit(1);
  }

  sleep(5);

  fd = open (argv[1], O_RDONLY);
  printf ("Abrio el pipe\n");

    
 close(fd);
}
