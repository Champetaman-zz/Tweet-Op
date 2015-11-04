#include <iostream>
#define MAXEMP 1000

using namespace std;
/*===========================================
 *  Estructura DATOSCLIENTE
 *
 * pid-> id usuario
 * follow-> (usuario, ultimo tweet)
 * tweet -> guarda los tweets del usuario
 =============================================*/
typedef struct datosCliente
{
    int pid;
    map< int, int > follow;
    vector< char > tweet;
} client;
