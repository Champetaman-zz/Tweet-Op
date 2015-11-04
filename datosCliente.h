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
        vector< string > tweet;
} dataClient[10];
