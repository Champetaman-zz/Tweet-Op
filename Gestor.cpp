#include "datosCliente.h"


void datosEntrada( datosEnvio opcion, vector<datosCliente>  dc, string mode, set< int > conectados)
{
								int decizione = opcion.action;
								datosEnvio dE;

								switch(decizione)
								{
								case -1:
								{
																cout<<"**Gestor evaluando sesion de "<<opcion.id<<endl;
																int pipeC, verificar = 0;
																if(conectados.find(opcion.id) == conectados.end()) {
																								verificar = 1;
																								strcpy(dE.message,mode.c_str() );
																								conectados.insert(opcion.id);
																}
																dE.action = verificar;

																if ((pipeC = open(opcion.pipename, O_WRONLY|O_NONBLOCK)) == -1) {
																								perror("Gestor Abriendo el pipe de respuesta");
																								exit(0);
																}
																cout<<"**El gestor enviando respuesta de la sesion\n";
																cout<<opcion.pipename<<" "<<dE.message<<" "<<dE.action<<endl;

																if(write(pipeC, &dE, sizeof(dE))==-1) {
																								perror("Gestor escribiendo en el pipe Cliente");
																								exit(0);
																}

																cout<<"termina\n";
								} break;

								default:
								{

								} break;


								}
								cout<<"sale"<<endl;
}


/*============================================
   --lectura--
   Lee el archivo
   =============================================*/

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

								int pid, pipeG,pipeC;
								string modo=argv[2];
								datosEnvio dRecibido;
								vector<datosCliente> datos(10);
								set< int > conectados;

								/*=============================================
								   Verificación de parámetros correctos
								   ===============================================*/

								if(argc!=4)
								{
																cout<<"Formato incorrecto. Ingrese de la siguiente manera: [$Gestor] [relaciones] [modo] [pipenom]"<<endl;
																exit(0);
								}

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

								pipeG = open (argv[3], O_RDONLY);
								printf ("Pipe aperto\n");
								int aux;
								/*=============================================
								   Gestor escuchando
								   ===============================================*/
								while((aux=read(pipeG, &dRecibido, sizeof(dRecibido))!=-1))
								{
																cout<<aux<<endl;
																if(aux>0) {
																								cout<<"entro\n";

																								datosEntrada(dRecibido, datos, modo, conectados);
																}
																sleep(5);
																cout<<"llega\n";

								}
								cout<<aux<<endl;

}
