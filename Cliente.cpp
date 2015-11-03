#include <iostream>
#include <cstdlib>

using namespace std;

	/*============================================
     *	Variable que determina el estado del gestor (Sincrono = false | asincrono = true)
    =============================================*/

bool estado = false;

int menu()
{
    int opcion;

    cout<<"Ciao, per favore fate la tua scelta:"<<endl;
    cout<<"1. Follow un usuario"<<endl;
    cout<<"2. Unfollow un usuario"<<endl;
    cout<<"3. Enviar un tweet"<<endl;
    cout<<"4. Recuperar Tweets (Valido unicamente en modo sincrono)"<<endl;
    cout<<"0. Cerrar Sesion"<<endl;

    cin>>opcion;

    switch(opcion)
    {
    case 0:
        cout<<"Grazie per usare il nostro servizio. In bocca a lupo!"<<endl;
        return 0;
        break;
    case 1:
        /*============================================
         *          Follow de un usuario
        =============================================*/
        cout<<"A chi ti piacerebbe seguire?"<<endl;

        return 1;
        break;
    case 2:
        /*============================================
                    Unfollow de un usuario
        =============================================*/
        cout<<"A chi ti piacerebbe non seguire?"<<endl;


        return 2;
        break;
    case 3:
        /*============================================
                        Enviar un Tweet
        =============================================*/
        cout<<"A cosa stai pensando?"<<endl;

        return 3;
        break;
    case 4:
        /*============================================
                        Recuperar Tweets
        =============================================*/
        cout<<"aggiornare il muro"<<endl;


        return 4;
        break;
    default:
        cout<<"L'opzione è sbagliato, per favore scegliere una delle opzioni del menu.";
        break;


    }

    return opcion;
}

/*void EnviarPipe(emple *miemp, int cuantos,char pipe[]) {

  int i, creado, fd;
 do{
	fd = open (pipe, O_WRONLY);
	if(fd==-1)
		sleep(1);
 }while(fd==-1);
	 	for(i=0; i<cuantos; ++i)
		{
		 	write(fd, &miemp[i], sizeof (miemp[i]));
		}	
	
	sleep(3);
	close(fd);

}*/

   /*============================================
    *     Verifica si el usuario es valido = true
    =============================================*/
bool verifUsuario(int pid)
{
	int i, creado, fd;
    
    do{
		fd = open (pipe, O_WRONLY);
		if(fd==-1)
			sleep(1);
    }while(fd==-1);
 	
	
	sleep(3);
	close(fd);
}

int main(int argc, char *argv[])
{
    /*============================================
         Verificación de parámetros correctos
    =============================================*/

    if(argc!=3)
    {
        cout<<"Formato incorrecto. Ingrese de la siguiente manera: [$Cliente] [id] [pipenom]"<<endl;
        exit(0);
    }
    
    /*============================================
                  VERIFICACION USUARIO
    =============================================*/


    /*============================================
                    SECCION ID
    =============================================*/
    while(menu());

    return 0;
}
