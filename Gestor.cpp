#include "datosCliente.h"

bool mode;
set< int > conectados;
int fd;

void datosEntrada( datosEnvio opcion, vector<datosCliente>  dc)
{
								int decizione = opcion.action;
								datosEnvio dE;

								switch(decizione)
								{
								case -1:
								{
																cout<<"Gestor evaluando sesion de "<<opcion.id<<endl;
																int fd1, verificar = 0;
																string aux;
																if(mode==true)
																								aux="sincrono";
																else aux="asincrono";
																if(conectados.find(opcion.id) == conectados.end()) {
																								verificar = 1;
																								strcpy(dE.message,aux.c_str() );
																								conectados.insert(opcion.id);
																}
																dE.action = verificar;

																if ((fd1 = open(opcion.pipename, O_WRONLY|O_NONBLOCK)) == -1) {
																								perror("Gestor Abriendo el pipe de respuesta");
																								exit(0);
																}
																cout<<"El gestor enviando respuesta de la sesion\n";
																cout<<opcion.pipename<<" "<<dE.message<<" "<<dE.action<<endl;
																cout<<kill(opcion.pid, SIGUSR1)<<endl;
																write(fd1, &dE, sizeof(dE));

																close(fd1);
								} break;
								case 1:
								{

								} break;

								case 2:
								{

								} break;

								case 3:
								{

								} break;

								case 4:
								{

								} break;

								default:
								{

								} break;


								}
}

void lectura(vector<datosCliente> &g,string nom)
{
								ifstream archivo (nom.c_str());
								if(archivo.is_open()) {
																int x, cont=0, cont2=0;
																while(archivo>>x)
																{
																								if(x==1)
																								{
																																g[cont2].follow[cont] = 0;

																								}
																								++cont;
																								if(cont == 10)
																								{
																																cont = 0;
																																++cont2;
																								}

																}
																archivo.close();
																cout<<"Lettura al 100%"<<endl;
								}
								else{
																cout<<"Lettura del file è sbagliato"<<endl;
																exit(0);
								}
}

int main (int argc, char **argv)
{

								int pid, n, bytes;
								string sin=argv[2];
								datosEnvio dEe;
								vector<datosCliente> datos(10);

								/*=============================================
								   Verificación de parámetros correctos
								   ===============================================*/

								if(argc!=4)
								{
																cout<<"Formato incorrecto. Ingrese de la siguiente manera: [$Gestor] [relaciones] [modo] [pipenom]"<<endl;
																exit(0);
								}

								if(sin=="sincrono")  mode=true;
								else mode=false;


								/*=============================================
								   Lectura del archivo de relaciones
								   ===============================================*/

								cout<<"Lettura di file Relazioni... ";
								lectura(datos, argv[1]);


								/*=============================================
								   Iniciando pipe gestor
								   ===============================================*/
								mode_t fifo_mode = S_IRUSR | S_IWUSR;

								unlink(argv[3]);
								if (mkfifo (argv[3], fifo_mode) == -1) {
																perror("mkfifo");
																exit(1);
								}

								sleep(5);

								fd = open (argv[3], O_RDONLY);
								printf ("Pipe aperto\n");

								/*=============================================
								   Gestor escuchando
								   ===============================================*/
								while(read(fd, &dEe, sizeof(dEe)))
								{

																datosEntrada(dEe, datos);

								}

								close(fd);
}
