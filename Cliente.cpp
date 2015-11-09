
#include "datosCliente.h"

/*======================================================================================
*	Variable que determina el estado del gestor (Sincrono = false | asincrono = true)
   ======================================================================================*/
bool estado = false;
int fd;

/*NOS FALTA QUE CUANDO EL GESTOR NOS RESPONDA SABER SI ESTA SINCRONICO O
   ASINCRONICO Y MOSTRAR LA OPCION 4 O NO*/

bool inicioSesion(int id, string nomPipe,string pipe) {
        cout<<"Iniciando sesion..."<<endl;

        int creado, fd1;
        datosEnvio dE, dR;

        // manejador de seniales
        signal(SIGUSR1, (sighandler_t)signalHandler);

        do {
                fd1 = open (nomPipe.c_str(), O_WRONLY);
                if(fd1 == -1) {
                        perror("pipe");
                        printf(" Se volvera a intentar despues\n");
                        sleep(5);
                }
        } while(fd1 == -1);

        dE.action = -1;
        dE.id = id;
        dE.pid = getpid();

        strcpy(dE.pipename, pipe.c_str());
        cout<<"Enviando solicitud a gestor \n";
        write(fd1, &dE, sizeof(dE));
        //Pause del manejador de seniales
        cout<<"Si necesitas reggaeton pauseame \n";
        pause();
        cout<<"Te leo el juanete"<<endl;
        read(fd, &dR, sizeof(dR));
        cout<<"Lo lei \n";
        //cout<<dR.action<<endl;
        if(dR.action==0)
                cout<<"Alguien hackeo su cuenta, ya se encuentra abierta."<<endl;
        else if(dR.action==1){
                cout<<"Ha iniciado sesion correctamente!"<<endl;
                cout<<"El servidor se encuentra en estado: "<<dR.message<<endl;
        }
        close(fd1);
}

int main(int argc, char **argv)
{
        int arg2,opciones = 0;
        string arg=argv[1];
        arg2=atoi(argv[1]);
        string nompipeGC;
        mode_t fifo_mode = S_IRUSR | S_IWUSR;

        /*=============================================
           Verificación de parámetros correctos
           ===============================================*/
        if(argc!=3)
        {
                cout<<"Formato incorrecto. Ingrese de la siguiente manera: [$Cliente] [id] [pipenom]"<<endl;
                exit(0);
        }
        /*============================================
           VERIFICACION USUARIO
           Se verifica si el id es valido
           =============================================*/

        if(arg2< 1 || arg2> 10)
        {
                cout << "No es posible conectarse con el id que indica, Por favor ingrese un numero entre 1 y 10." <<endl;
                exit(0);
        }

        //Creacion del pipe de lectura para recibir informacion del gestor
        // Nombre de un segundo pipe
        //strcpy(datos.segundopipe, "mypipe");
        // Se crea un segundo pipe
        nompipeGC = argv[2];
        nompipeGC += (argv[1]);

        unlink(nompipeGC.c_str());
        if (mkfifo (nompipeGC.c_str(), fifo_mode) == -1) {
                perror("cliente mkfifo");
                exit(1);
        }
        // Se abre el segundo pipe
        if ((fd = open(nompipeGC.c_str(), O_RDONLY|O_NONBLOCK)) == -1) {
                perror("Cliente abriendo el segundo pipe");
                exit(0);
        }

        if(!inicioSesion(atoi(argv[1]),argv[2],nompipeGC)) {
                cout<<"Se ha iniciado sesion correctamente"<<endl;
        }
        else{
                cout<<"El usuario con el que esta intentando ingresar ya esta conectado"<<endl;
                exit(0);
        }
        /*============================================
           SECCION ID
           =============================================*/
        //fd = open (argv[2], O_WRONLY);
        //while(menu(opciones, fd)) ;
        //close(fd);

        return 0;
}
