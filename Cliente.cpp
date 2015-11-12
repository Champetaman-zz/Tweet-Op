
#include "datosCliente.h"

/*============================================
   --inicioSesio--
   Se encarga de conectar al cliente, validarlo
   y retorna el estado en el que está el gestor
   =============================================*/

int opciones = 1;

void inicioSesion(int id, int pG, int pC, string pipeC) {
        int c;
        cout<<"..Iniciando sesion.................."<<endl;

        datosEnvio dEscritura, dLectura;
        dEscritura.action = -1;
        dEscritura.id = id;
        strcpy(dEscritura.pipename, pipeC.c_str());
        cout<<": Enviando solicitud a gestor \n";

        if(write(pG, &dEscritura, sizeof(dEscritura))==-1) {
                perror("Escritura inicio de sesión");
                exit(0);
        }
        // Codigo agregado
        do {
                c =  read(pC, &dLectura, sizeof(dLectura));
                sleep(1);
        } while (c <= 0);

        /*if(read(pC, &dLectura, sizeof(dLectura))==-1){
           perror("Lectura inicio de sesión");
           exit(0);
           }*/
        if(dLectura.message == "asincrono")
                opciones = 0;

        cout<<"Modo del Gestor= "<<dLectura.action<<" Mensaje R= "<<dLectura.message<<endl;
        cout<<"El gestor responde... \n";
        if(dLectura.action==0){
                cout<<"Alguien hackeo su cuenta, ya se encuentra abierta."<<endl;
                exit(0);
        }
        else if(dLectura.action==1) {
                cout<<"Ha iniciado sesion correctamente!"<<endl;
                cout<<"El servidor se encuentra en estado: "<<dLectura.message<<endl;
        }

}

int menu(int opciones, int fdG, int fdC)
{
        int i=0;
        int opcion;
        datosCliente usuario;

        cout<<"   |-----------------------------------------------------|"<<endl;
        cout<<"   |====================Tu&tazo Inc.=====================|"<<endl;
        cout<<"   |Ciao, per favore fate la tua scelta.                 |"<<endl;
        cout<<"   |1. Seguire un utente                                 |"<<endl;
        cout<<"   |2. Smetti di seguire un utente                       |"<<endl;
        cout<<"   |3. Inviare un tweet                                  |"<<endl;
        if( opciones = 0 )
                cout<<"   |4. Aggiornare I tweets                               |"<<endl;
        cout<<"   |0. Esci di Tu&tazo                                   |"<<endl;
        cout<<"   |-----------------------------------------------------|"<<endl;
        cout<<"La tua opzione: ";

        cin>>opcion;
        cout<<endl;

        switch(opcion)
        {
        case 0:
        {       cout<<"--------->Cerrando Sesion...  ";
                sleep(2);
                cout<<"100%"<<endl;
                cout<<"--------->Grazie per usare il nostro servizio. In bocca a lupo!"<<endl;
                return 0; } break;

        case 1:
        {
                int ide;
                /*============================================
                 *          Follow de un usuario
                   =============================================*/
                cout<<"A chi ti piacerebbe seguire?"<<endl;
                cin>>ide;
                //Se debe validar que el usuario sea valido y no lo este siguiendo
                cout<<endl;

                return 1;
        } break;

        case 2:
        {
                int ide;
                /*============================================
                   Unfollow de un usuario
                   =============================================*/
                cout<<"A chi ti piacerebbe lasciare di seguire?"<<endl;
                cin>>ide;
                // Se debe validar que el usuario sea valido y lo este siguiendo
                cout<<endl;

                return 2;
        } break;

        case 3:
        {
                /*============================================
                   Enviar un Tweet
                   =============================================*/
                string input;
                char caracter;

                do {
                        cout<<"A cosa stai pensando?"<<endl;
                        cin.ignore();
                        getline(cin,input);
                        if(input.length() <= 140)
                        {
                                usuario.tweet.push_back(input);
                                ++i;
                                cout<<"Tweet enviado exitosamente!"<<endl;
                                caracter = 'N';
                        }
                        else
                        {
                                cout<<endl<<"El tweet es demasiado largo, excede los 140 caracteres."<<endl;
                                cout<<"Numero de caracteres: "<<input.length()<<endl;
                                cout << "Si desea cancelar ingrese N, si desea reescribir el tweet ingrese S" <<endl;
                                cin>>caracter;
                        }
                } while(caracter == 'S' || caracter == 's');

                return 3;
        } break;

        case 4:
        {
                if( opciones = 1 ) {
                        cout<<"L'opzione è sbagliato, per favore scegliere una delle opzioni del menu."<<endl;
                        cout<<endl;
                        return 4;
                }
                /*============================================
                   Recuperar Tweets
                   =============================================*/
                cout<<"aggiornare il muro? Y | N"<<endl;
                //Se valida si el gestor esta en modo sincrono

                return 4;
        } break;

        default:
        {
                cout<<"L'opzione è sbagliato, per favore scegliere una delle opzioni del menu."<<endl;
                cout<<endl;
        } break;


        }

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
                temp = menu(opciones, pipeG, pipeC);
                sleep(2);
        } while(temp != 0);
        //close(fd);

        return 0;
}
