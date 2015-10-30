#include <iostream>
#include <cstdlib>
#include <map>
#include <vector>
#include <fstream>

using namespace std;

struct datosCliente
{
    int pid;
    map<int, int> follow;
    map<int, int> Seguidores;
};

vector< vector<int> > lectura(ifstream& archivo)
{
    int x, cont=0, cont2=1, i=0;
    vector< vector<int> > g;
    g.clear();
    while(archivo>>x)
    {
		cout<<x;
		++cont;
		if(x==1)
		{
			g[cont2][i] = cont;	
			++i;
		}
		if(cont==10)
		{
			cout<<endl;	
			cont=0;
			i=0;
			++cont2;
		}
    }
    archivo.close();
    return g;
}

int main(int argc, char *argv[])
{
    map<int, int> datosCliente;
    vector< vector< int > > g;
    ifstream archivo (argv[1]);

    /*============================================
         Verificación de parámetros correctos
    =============================================*/

    /*if(argc!=4)
    {
        cout<<"Formato incorrecto. Ingrese de la siguiente manera: [$Cliente] [id] [pipenom]"<<endl;
        exit(0);
    }*/

    g = lectura(archivo);
    
    cout<<"He aqui el grafo: "<<endl;
    for(unsigned int i=0; i<g.size();++i)
    {
		for(unsigned int j=0; j<g[i].size(); ++j)
		{
			cout<<g[i][j]<<" ";
		}
	}
	cout<<endl;
    
    return 0;
}
