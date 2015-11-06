#include <iostream>
#include <cstdlib>
#include <map>
#include <vector>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <limits>
#include <stdio.h>
#include <string.h>
#include "datosCliente.h"

using namespace std;

/*======================================================================================
*	Variable que determina el estado del gestor (Sincrono = false | asincrono = true)
   ======================================================================================*/
bool estado = false;

int menu()
{
        int i=0;
        int opcion;

        dataClient client;

        cout<<"=====================Tu&tazo Inc.====================="<<endl;
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
                        cin.clear();
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                        getline(cin,input);
                        if(input.length() <= 140)
                        {
                                client[i].tweet.push_back(input);
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

/*============================================
 *     Verifica si el usuario es valido = true
   =============================================*/
/*bool verifUsuario(int pid)
   {
   int i, creado, fd;

   do{
   fd = open (pipe, O_WRONLY);
   if(fd==-1)
   sleep(1);
   }while(fd==-1);

   sleep(3);

   close(fd);
   }*/

int main(int argc, char *argv[])
{
        char *p;
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
        while(menu()) ;



        return 0;
}
