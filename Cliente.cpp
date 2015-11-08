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

bool inicioSesion(int id, char nomPipe[]) {
  cout<<"Iniciando sesion..."<<endl;
  cout<<"LO HACE";

  int fd, i=-1;


  do{
    fd = open (nomPipe, O_WRONLY);
    if(fd==-1){
      sleep(1);
    }
  }
  while(fd==1);
  cout<<"Escribiendo";
  write(fd, &i, sizeof(i));
  write(fd, &id, sizeof(id));

  close(fd);
}

int menu(int opciones, int fd)
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
  int fd,arg2,opciones = 0;
  string arg=argv[1];
  arg2=atoi(argv[1]);

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




  if(!inicioSesion(atoi(argv[1]),argv[2])){
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
  while(menu(opciones, fd));
  //close(fd);

  return 0;
}
