
#include "datosCliente.h"

typedef void (*sighandler_t)(int);

int opciones = 0;

sighandler_t signalHandler (void)
{

}

/*============================================
   --inicioSesion--
   Se encarga de conectar al cliente, validarlo
   y retorna el estado en el que está el gestor
   =============================================*/



void inicioSesion(int id, int pG, int pC, string pipeC) {
        int c;
        cout<<"Iniciando sesion...  .....  ...   ."<<endl;

        datosEnvio dEscritura, dLectura;
        dEscritura.action = -1;
        dEscritura.id = id;
        strcpy(dEscritura.pipename, pipeC.c_str());
        cout<<"Enviando solicitud a gestor...\n";

        if(write(pG, &dEscritura, sizeof(dEscritura))==-1) {
                perror("Escritura inicio de sesión");
                exit(0);
        }
        // Codigo agregado
        do {
                c =  read(pC, &dLectura, sizeof(dLectura));
                sleep(1);
        } while (c <= 0);

        if(dLectura.message == "asincrono")
                opciones = 1;

        cout<<"**El gestor ha respondido.\n";
        if(dLectura.action==0) {
                cout<<"Alguien hackeo su cuenta, ya se encuentra abierta."<<endl;
                exit(0);
        }
        else if(dLectura.action==1) {
                cout<<"Ha iniciado sesion correctamente!"<<endl;
                cout<<"El servidor se encuentra en estado: "<<dLectura.message<<endl;
                cout<<"--------------------------------------------------------------------------------"<<endl;
        }

}

int menu(int opciones, int fdG, int fdC, int id, string pipeC)
{

        int opcion, c;
        datosEnvio usuario, lectura;
        strcpy(usuario.pipename,pipeC.c_str());

        cout<<"          |-----------------------------------------------------|"<<endl;
        cout<<"          |====================Tu&tazo Inc.=====================|"<<endl;
        cout<<"          |Ciao, per favore fate la tua scelta.                 |"<<endl;
        cout<<"          |1. Seguire un utente                                 |"<<endl;
        cout<<"          |2. Smetti di seguire un utente                       |"<<endl;
        cout<<"          |3. Inviare uno tweet                                 |"<<endl;
        if( opciones == 0 )
                cout<<"          |4. Aggiornare I tweets                               |"<<endl;
        cout<<"          |0. Esci di Tu&tazo                                   |"<<endl;
        cout<<"          |-----------------------------------------------------|"<<endl;
        cout<<"  La tua opzione: ";

        cin>>opcion;
        cout<<"  ============================================================================\n";

        switch(opcion)
        {
        case 0:
        {       cout<<"--------->Cerrando Sesion...  ";
                sleep(2);
                cout<<"100%"<<endl;
                cout<<"--------->Grazie per usare il nostro servizio. In bocca a lupo!"<<endl; } break;

        case 1:
        {

                // Follow-------------------------
                string ide;
                cout<<"    A chi ti piacerebbe seguire?\n    > ";
                cin.ignore();
                cin>>ide;
                usuario.id = id;
                usuario.action=opcion;
                strcpy(usuario.message, ide.c_str());
                cout<<"    Peticion enviada al gestor...\n";
                if(write(fdG, &usuario, sizeof(usuario))==-1) {
                        perror("Escritura para seguir usuario:");
                        exit(0);
                }

                cout<<"    Esperando respuesta del gestor...\n";
                do {
                        c =  read(fdC, &usuario, sizeof(usuario));
                        sleep(1);
                } while (c <= 0);

                cout<<"    Respuesta del gestor recibida.\n";
                if(usuario.action == 2)
                {
                        cout<<"    El usuario al que esta intentando seguir ya lo sigue actualmente."<<endl;
                }
                else if(usuario.action == 3)
                {
                        cout<<"    Debe ingresar un cliente valido entre 1 y 10."<<endl<<"Intente de nuevo."<<endl;
                }else if(usuario.action == 4) {
                        cout<<"    Error, te estas intentando seguir a ti mismo."<<endl<<"    Intente de nuevo."<<endl;
                }
                else{
                        cout<<"    Ahora estas siguiendo al usuario: "<<ide<<endl;
                }


        } break;

        case 2:
        {
                /*============================================
                   Unfollow de un usuario
                   =============================================*/
                int c;
                string ide;
                cin.ignore();
                cout<<"    A chi ti piacerebbe lasciare di seguire?\n    > ";
                cin>>ide;

                usuario.id = id;
                usuario.action=opcion;
                strcpy(usuario.message, ide.c_str());
                if(write(fdG, &usuario, sizeof(usuario))==-1) {
                        perror("Escritura para dejar de seguir usuario:");
                        exit(0);
                }
                do {
                        c =  read(fdC, &usuario, sizeof(usuario));
                        sleep(1);
                } while (c <= 0);

                cout<<"    Respuesta del gestor recibida.\n";
                if(usuario.action == 2)
                {
                        cout<<"    El usuario al que esta intentando dejar seguir no lo seguia."<<endl;
                }
                else if(usuario.action == 3)
                {
                        cout<<"    Debe ingresar un cliente valido entre 1 y 10."<<endl<<"    Intente de nuevo."<<endl;
                }else if(usuario.action == 4)
                {
                        cout<<"    Error, te estas intentando dejar de seguir a ti mismo."<<endl<<"    Intente de nuevo."<<endl;
                }
                else{
                        cout<<"    Dejaste de seguir al usuario: "<<ide<<endl;
                }

        } break;
        case 3:
        {
                /*============================================
                   Enviar un Tweet
                   =============================================*/
                string input;
                char letter;
                do {
                        cout<<"    A cosa stai pensando?\n    > ";
                        cin.ignore();
                        getline(cin,input);
                        usuario.id=id;
                        usuario.action=opcion;
                        strcpy(usuario.message,input.c_str());
                        cout<<"    Enviando el tu&tazo a gestor...\n";
                        if(write(fdG, &usuario, sizeof(usuario))==-1) {
                                perror("Escritura de Tu&Tazo:");
                                exit(0);
                        }

                        do {
                                c =  read(fdC, &lectura, sizeof(lectura));
                                sleep(1);
                        } while (c <= 0);
                        cout<<"    "<<lectura.message;
                        if(lectura.action)
                                letter='N';
                        else{
                                cin>>letter;
                        }

                } while(letter=='S');
        } break;

        case 4:
        {
                if( opciones == 1 ) {
                        cout<<"    L'opzione è sbagliato, per favore scegliere una delle opzioni del menu."<<endl;
                        cout<<endl;
                        break;
                }
                cout<<"    Actualizando mensajes\n";
                usuario.id=id;
                usuario.action=opcion;
                cout<<"    Escribiendo al gestor\n";
                if(write(fdG, &usuario, sizeof(usuario))==-1) {
                        perror("Escritura de Tu&Tazo:");
                        exit(0);
                }
                cout<<"    Recopilando los Tu&T's\n";
                do {
                        do {
                                c =  read(fdC, &lectura, sizeof(lectura));
                                sleep(1);
                        } while (c <= 0);
                        if(lectura.action) {
                                cout<<"    Tu&T entrante:"<<lectura.id<<"\n  ";
                                cout<<lectura.message<<endl;
                        }
                } while (lectura.action);

        } break;

        default:
        {
                cout<<"    L'opzione è sbagliato, per favore scegliere una delle opzioni del menu."<<endl;
                cout<<endl;
        } break;


        }
        cout<<"  ============================================================================\n";
        return opcion;
}

int main(int argc, char **argv)
{
        int pipeG, pipeC, creado=0;
        int argv1,opciones = 0, temp;
        argv1=atoi(argv[1]);
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
           VERIFICACION USUARIO:  Se verifica si el id es valido
           =============================================*/

        if(argv1< 1 || argv1> 10)
        {
                cout << "No es posible conectarse con el id que indica, Por favor ingrese un numero entre 1 y 10." <<endl;
                exit(0);
        }
        /*============================================
           Creacion de pipes
           =============================================*/
        // Pipe gestor
        do {
                pipeG = open (argv[2], O_WRONLY);
                if(pipeG == -1) {
                        perror("pipe");
                        printf(" Se volvera a intentar despues\n");
                        sleep(5);
                }
                else creado=1;
        } while(creado == 0);

        //Pipe Cliente
        nompipeGC = argv[2];
        nompipeGC += (argv[1]);

        unlink(nompipeGC.c_str());

        if (mkfifo (nompipeGC.c_str(), fifo_mode) == -1) {
                perror("cliente mkfifo");
                exit(1);
        }

        if ((pipeC = open(nompipeGC.c_str(), O_RDONLY|O_NONBLOCK)) == -1) {
                perror("Cliente abriendo el segundo pipe");
                exit(0);
        }

        /*============================================
           Operaciones cliente
           =============================================*/

        inicioSesion(atoi(argv[1]),pipeG,pipeC,nompipeGC);

        do {
                temp = menu(opciones, pipeG, pipeC, argv1,nompipeGC);
                cout << "|--------------->Presione enter para continuar con el programa<----------------|";
                cin.ignore().get();
                system("clear");

        } while(temp != 0);
        close(pipeC);

        return 0;
}
