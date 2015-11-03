#include <iostream>
#include <cstdlib>
#include <map>
#include <vector>
#include <fstream>

using namespace std;


/*===========================================
 *  DATOSCLIENTE
 * 
 * pid-> id usuario
 * follow-> (usuario, ultimo tweet)
 * tweet -> guarda los tweets del usuario
 =============================================*/
struct datosCliente
{
    int pid;
    map<int, int> follow;
    vector<string> tweet;
};

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

int main(int argc, char *argv[])
{

    vector< datosCliente> g;
    for(int i=0; i<10 ;++i)
    {
		datosCliente dc;
		dc.pid=i;
		g.push_back(dc);
	}
	
	mode_t fifo_mode = S_IRUSR | S_IWUSR;
  
	unlink(argv[1]);
	if (mkfifo (argv[1], fifo_mode) == -1) 
	{
		 perror("mkfifo");
		 exit(1);
	}
    sleep(5);

    /*============================================
         Verificación de parámetros correctos
    =============================================*/

    /*if(argc!=4)
    {
        cout<<"Formato incorrecto. Ingrese de la siguiente manera: [$Cliente] [id] [pipenom]"<<endl;
        exit(0);
    }*/
    
     /*============================================
				Lectura de datos usuario
    =============================================*/
    cout<<" ";
	cout<<"Lectura del archivo de Relaciones... ";
    lectura(g,argv[1]);
    cout<<"100%"<<endl;
    {/*
    cout<<"He aqui el grafo: "<<g.size()<<endl;
    for(unsigned int i=0; i<g.size();++i)
    {
		  map<int, int> :: iterator it=g[i].follow.begin();
		for(; it!=g[i].follow.end(); ++it)
		{
			cout<<i<<"->"<<it->first<<endl;
		}
			cout<<endl;

	}
*/}
    
    fd = open (argv[1], O_RDONLY);
    printf ("Abrio el pipe\n");


    // Aqui va el codigo de lectura de la informacion por el pipe. 

  while(read(fd, &em, sizeof(emple))>0)
  {
    
    return 0;
}
