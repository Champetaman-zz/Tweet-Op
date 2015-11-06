#include <iostream>
#include <cstdlib>
#include <map>
#include <vector>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
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

        int ide;

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
        {       cout<<"--------->Cerrando Sesion...        ";
                cout<<"100%"<<endl;
                cout<<"--------->Grazie per usare il nostro servizio. In bocca a lupo!"<<endl;
                return 0;
        } break;

        case 1:
        {
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

                cout<<"A cosa stai pensando?"<<endl;
                getline(cin,input);
                cout << input << ": "<<endl;
                client[i].tweet.push_back(input);
                ++i;

                cout<<endl;

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
        //cout<<"El usuario con el que esta intentando ingresar ya esta conectado"<<endl;
        //cout<<"Intente con uno de los siguientes usuarios disponibles: "<<endl;
        // Se desplegara los usuarios aun disponibles

        /*============================================
                        SECCION ID
           =============================================*/
        while(menu());



        return 0;
}
