
#include "datosCliente.h"

/*============================================
--inicioSesio--
Se encarga de conectar al cliente, validarlo
y retorna el estado en el que está el gestor
=============================================*/

bool inicioSesion(int id, int pG, int pC, string pipeC) {
  int c;
  cout<<"..Iniciando sesion.................."<<endl;

  datosEnvio dEscritura, dLectura;
  dEscritura.action = -1;
  dEscritura.id = id;
  strcpy(dEscritura.pipename, pipeC.c_str());
  cout<<": Enviando solicitud a gestor \n";

  if(write(pG, &dEscritura, sizeof(dEscritura))==-1){
    perror("Escritura inicio de sesión");
    exit(0);
  }
  // Codigo agregado
  do {
      c =  read(pC, &dLectura, sizeof(dLectura));
      sleep(1);
      cout<<" c es "<<c<<endl;
  } while (c <= 0);

  /*if(read(pC, &dLectura, sizeof(dLectura))==-1){
    perror("Lectura inicio de sesión");
    exit(0);
    }*/
  cout<<"Modo R="<<dLectura.action<<" Mensaje R="<<dLectura.message<<endl;
  cout<<": El gestor responde... \n";
  if(dLectura.action==0)
  cout<<"Alguien hackeo su cuenta, ya se encuentra abierta."<<endl;
  else if(dLectura.action==1){
    cout<<"Ha iniciado sesion correctamente!"<<endl;
    cout<<"El servidor se encuentra en estado: "<<dLectura.message<<endl;
  }

}

int main(int argc, char **argv)
{
  int pipeG, pipeC, creado=0;
  int argv1,opciones = 0;
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

  if(!inicioSesion(atoi(argv[1]),pipeG,pipeC,nompipeGC)) {
    cout<<"Se ha iniciado sesion correctamente"<<endl;
  }
  else{
    cout<<"El usuario con el que esta intentando ingresar ya esta conectado"<<endl;
    exit(0);
  }

  while(true) {
    sleep(2);
  }
  //close(fd);

  return 0;
}
