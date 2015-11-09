#ifndef __DATOS_H_INCLUDED__
#define __DATOS_H_INCLUDED__

#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <signal.h>
#include <unistd.h>
#include <iostream>
#include <map>
#include <set>
#include <string.h>
#include <vector>
#include <fstream>
#include <sstream>

using namespace std;

/*===========================================
 *  Estructura DATOSCLIENTE
 *
 * pid-> id usuario
 * follow-> (usuario, ultimo tweet)
 * tweet -> guarda los tweets del usuario
   =============================================*/
struct datosCliente
{
        int pid;
        map< int, int > follow;
        vector< string > tweet;
};

struct datosEnvio
{
        int action;
        int id;
        int pid;
        char pipename[1000];
        char message[1000];
};

typedef void (*sighandler_t)(int);

sighandler_t signalHandler (void)
{
        cout<<"Estoy en el handler"<<endl;
}

#endif
