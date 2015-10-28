#include <iostream>
#include <cstdlib>

using namespace std;

int menu()
{
    int opcion;

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
        cout<<"Grazie per usare il nostro servizio. In bocca a lupo!"<<endl;
        return 0;
        break;
    case 1:
        /*============================================
                    Follow de un usuario
        =============================================*/
        cout<<"A chi ti piacerebbe seguire?"<<endl;

        return 1;
        break;
    case 2:
        /*============================================
                    Unfollow de un usuario
        =============================================*/
        cout<<"A chi ti piacerebbe non seguire?"<<endl;


        return 2;
        break;
    case 3:
        /*============================================
                        Enviar un Tweet
        =============================================*/
        cout<<"A cosa stai pensando?"<<endl;

        return 3;
        break;
    case 4:
        /*============================================
                        Recuperar Tweets
        =============================================*/
        cout<<"aggiornare il muro"<<endl;


        return 4;
        break;
    default:
        cout<<"L'opzione è sbagliato, per favore scegliere una delle opzioni del menu.";
        break;


    }

    return opcion;
}

int main(int argc, char *argv[])
{
    /*============================================
         Verificación de parámetros correctos
    =============================================*/

    if(argc!=3)
    {
        cout<<"Formato incorrecto. Ingrese de la siguiente manera: [$Cliente] [id] [pipenom]"<<endl;
        exit(0);
    }
    /*============================================
                  VERIFICACION ID
    =============================================*/


    /*============================================
                    SECCION ID
    =============================================*/
    while(menu());

    return 0;
}
