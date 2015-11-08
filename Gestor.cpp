#include "datosCliente.h"

bool mode;

void datosEntrada(int fd, int opcion,	vector<datosCliente>  dc)
{

	int n;
	cout<<"1. Seguire un utente"<<endl;
	cout<<"2. Smetti di seguire un utente"<<endl;
	cout<<"3. Inviare un tweet"<<endl;
	cout<<"0. Cerrar Sesion"<<endl;

	switch(opcion)
	{
		case -1:
		{
			int i;
			mode?i=1:i=0;

			read(fd, &n, sizeof(n));
			cout<<"Se ha solicitado un inicio de sesion"<<endl;
			fd = open ("Pipe-1", O_WRONLY);
			write(fd, &i, sizeof(i));

		} break;
		case 1:
		{

		} break;

		case 2:
		{
			read(fd, &n, sizeof(n));
			cout<<n<<endl;


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
	if(archivo.is_open()){
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

	int fd, pid, n, bytes;
	vector<datosCliente> datos(10);

	/*=============================================
  Verificación de parámetros correctos
  ===============================================*/

  if(argc!=4)
  {
    cout<<"Formato incorrecto. Ingrese de la siguiente manera: [$Gestor] [relaciones] [modo] [pipenom]"<<endl;
    exit(0);
  }
	argv[2]=="sincrono"?mode=true:mode=false;

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
	while(read(fd, &n, sizeof(n)))
	{
		cout<<n<<endl;
			datosEntrada(fd,n, datos);
	}


	close(fd);
}
