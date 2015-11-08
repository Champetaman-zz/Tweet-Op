#include <iostream>
#include <cstdlib>
#include <map>
#include <vector>
#include <limits>
#include <fstream>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include "datosCliente.h"

datosCliente usuario;

using namespace std;

/*======================================================================================
*	Variable que determina el estado del gestor (Sincrono = false | asincrono = true)
   ======================================================================================*/
bool estado = false;

/*NOS FALTA QUE CUANDO EL GESTOR NOS RESPONDA SABER SI ESTA SINCRONICO O
   ASINCRONICO Y MOSTRAR LA OPCION 4 O NO*/

void EnviarPeticion(datosCliente usuario,char pipe[]) {

        int i=1, creado, fd;
        // este código lo tienen que hacer Uds.
        do {
                fd = open (pipe, O_WRONLY);
                if(fd == -1)

                        sleep(1);
        } while(fd == -1);

        for(i=0; i<5; ++i)
        {

                write(fd, &i, sizeof(i));
        }

        sleep(3);
        close(fd);
}

int menu(int opciones, char *pipe_name, datosCliente &usuario)
{
        int i=0;
        int opcion;

        cout<<"=====================Tu&tazo Inc.====================="<<endl;
        cout<<"Ciao, per favore fate la tua scelta:"<<endl;
        cout<<"1. Seguire un utente"<<endl;
        cout<<"2. Smetti di seguire un utente"<<endl;
        cout<<"3. Inviare un tweet"<<endl;
        if( opciones > 3 )
                cout<<"4. Aggiornare Tweets "<<endl;
        cout<<"0. Cerrar Sesion"<<endl;

        cin>>opcion;

        switch(opcion)
        {
        case 0:
        {       cout<<"--------->Cerrando Sesion...  ";
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
                                EnviarPeticion(usuario, pipe_name);
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
                if( opciones <= 3 )
                        cout<<"L'opzione è sbagliato, per favore scegliere una delle opzioni del menu."<<endl;

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
        char *p;
        int opciones = 0;
        datosCliente user;

        /*=============================================
           Verificación de parámetros correctos
           ===============================================*/
        /*
           if(argc!=3)
           {
           cout<<"Formato incorrecto. Ingrese de la siguiente manera: [$Cliente] [id] [pipenom]"<<endl;
           exit(0);
           }*/

        /*============================================
           VERIFICACION USUARIO
           =============================================*/
        //Se verifica si el id ya esta conectado al gestor
        /*if(strtol(argv[1], &p, 10) < 1 || strtol(argv[1], &p, 10) > 10)
           {
           cout << "No es posible conectarse con el id que indica, Por favor ingrese un numero entre 1 y 10." <<endl;
           }*/
        //cout<<"El usuario con el que esta intentando ingresar ya esta conectado"<<endl;
        //cout<<"Intente con uno de los siguientes usuarios disponibles: "<<endl;
        // Se desplegara los usuarios aun disponibles

        /*============================================
           SECCION ID
           =============================================*/
        while(menu(opciones, argv[2], user));

        return 0;
}
