#include "datosCliente.h"


/*void datosEntrada()
   {

   int opcion;

   cout<<"1. Seguire un utente"<<endl;
   cout<<"2. Smetti di seguire un utente"<<endl;
   cout<<"3. Inviare un tweet"<<endl;
   cout<<"0. Cerrar Sesion"<<endl;

   cin>>opcion;

   switch(opcion)
   {
   case 0:
   {

   return 0;

   } break;

   case 1:
   {


     return 1;
   } break;

   case 2:
   {

     return 2;
   } break;

   case 3:
   {

     return 3;
   } break;

   case 4:
   {
    return 4;
   } break;

   default:
   {

   } break;


   }

   return opcion;
   }*/

void lectura(vector<datosCliente> &g,string nom)
{
								ifstream archivo (nom.c_str());
								int x, cont=0, cont2=0, i=0;
								while(archivo>>x)
								{
																if(x==1)
																{
																								g[cont2].follow[cont] = i;
																								++i;
																}
																++cont;
																if(cont == 10)
																{
																								cont = 0;
																								++cont2;
																}
								}
								archivo.close();
}

int main (int argc, char **argv)
{

								int fd, pid, n, bytes;
								vector<datosCliente> datos(10);
								cout<<" ";
								cout<<"Lectura del archivo de Relaciones... ";
								lectura(datos, argv[1]);
								cout<<"100%"<<endl;

								mode_t fifo_mode = S_IRUSR | S_IWUSR;

								unlink(argv[2]);
								if (mkfifo (argv[2], fifo_mode) == -1) {
																perror("mkfifo");
																exit(1);
								}

								sleep(5);

								fd = open (argv[2], O_RDONLY);
								printf ("Abrio el pipe\n");

								while(read(fd, &n, sizeof(int)))
								{

																cout<<"Leyo el pipe"<<endl;
								}


								close(fd);
}
