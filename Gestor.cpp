#include <iostream>
#include <cstdlib>
#include <fstream>

using namespace std;

struct datosCliente
{
    int pid;
    map<int, int> follow;
    map<int, int> Seguidores;
};

void lectura()
{

}

int main(int argc, char *argv[])
{
    int x;
    map<int, int>datosCliente;
    ifstream archivo (argv[1]);

    /*============================================
         Verificación de parámetros correctos
    =============================================*/

    if(argc!=4)
    {
        cout<<"Formato incorrecto. Ingrese de la siguiente manera: [$Cliente] [id] [pipenom]"<<endl;
        exit(0);
    }

    while(archivo>>x)
    {
        cout<<x;
    }
    return 0;
}
