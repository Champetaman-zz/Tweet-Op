#include "datosCliente.h"

vector< char* > pipeVector(11);

void comunicadora(char nom[1000], 	datosEnvio dE){
	int pipeC;
	cout<<"  ZONA DE ESCRITURA A PIPES\n";
	if ((pipeC = open(nom, O_WRONLY|O_NONBLOCK)) == -1) {
		perror("Gestor Abriendo el pipe de respuesta");
		cout<<nom<<endl;
		exit(0);
	}


	cout<<"  El gestor enviando respuesta a "<<nom<<"\n";

	if(write(pipeC, &dE, sizeof(dE))==-1) {
		perror("Gestor escribiendo en el pipe Cliente ");
		exit(0);
	}
	cout<<"  FIN ZONA DE ESCRITURA A PIPES\n";

	close(pipeC);


}
void datosEntrada( datosEnvio opcion, vector<datosCliente>  &dc, string mode, set< int > &conectados)
{
	int pipeC,decizione = opcion.action;
	datosEnvio dE;
	cout<<" ================================================\n";
	switch(decizione)
	{
		case -1:
		{
			//Inicio de sesion------------------------
			cout<<"  Gestor evaluando sesion de cliente: "<<opcion.id<<"       |"<<endl;
			int verificar = 0;
			cout<<"  1) Validando información                    \n";
			if(conectados.find(opcion.id) == conectados.end())
			{
				verificar = 1;
				strcpy(dE.message,mode.c_str() );
				conectados.insert(opcion.id);
				dE.action = verificar;
			}
			else
			{
				strcpy(dE.message,mode.c_str() );
				dE.action = 0;
			}
			cout<<"  2) Abriendo pipe de escritura cliente        \n";

			comunicadora(opcion.pipename, dE);

			if(dE.action){
				pipeVector[opcion.id]=opcion.pipename;
				cout<<opcion.id<<":  "<<pipeVector[opcion.id]<<endl;
			}

			cout<<"  3) Operación realizada con exito             \n";

		} break;
		case 1:
		{
			// Follow-------------------------
			int targetid;
			targetid = atoi(opcion.message);

			cout<<"  Gestor evaluando solicitud de seguimiento del usuario: "<<targetid<<" por el cliente: "<<opcion.id<<endl;
			cout<<"  1) Validando que el codigo sea el correcto\n";
			if(targetid<1 || targetid>10)
			{
				dE.action = 3;
			}else{
				cout<<"  2) Validando si no se esta siguiendo ya al usuario\n";
				if(dc[opcion.id].follow.find(targetid) == dc[opcion.id].follow.end()) {
					dc[opcion.id].follow[targetid] = 0;
					dE.action = 1;
				}else{
					dE.action = 2;
				}
				cout<<"     Accion a ejecutar:"<<dE.action<<endl;


			}
			cout<<"  3) Enviando respuesta al cliente\n";
			cout<<opcion.pipename<<endl;
			comunicadora(pipeVector[opcion.id], dE);
		} break;

		case 2:
		{
			// Unfollow-----------------------------
			int targetid;
			targetid = atoi(opcion.message);
			cout<<"  Gestor evaluando solicitud dejar de seguir al usuario: "<<targetid<<" por el cliente: "<<opcion.id<<endl;
			cout<<"  1) Validando que el codigo sea el correcto\n";
			if(targetid<1 || targetid>10)
			{
				dE.action = 3;
			}else{
				cout<<"  2) Validando si se esta siguiendo ya al usuario\n";
				if(dc[opcion.id].follow.find(targetid) != dc[opcion.id].follow.end()) {
					dc[opcion.id].follow.erase(targetid);
					dE.action = 1;
				}else{
					dE.action = 2;
				}
				cout<<"     Accion a ejecutar:"<<dE.action<<endl;


			}
			cout<<"  3) Enviando respuesta al cliente\n";
			comunicadora(pipeVector[opcion.id], dE);
		} break;
		case 3:
		{
			// Recibir Tu&T------------------------
			string message;
			cout<<" Gestor recibiendo Tu&T de :"<<opcion.id<<"\n";
			cout<<"  1) El mensaje es: "<<opcion.message<<endl;
			cout<<"  2) Analizando el Tu&T\n";
			message=opcion.message;
			if(message.length() <= 140)
			{
				dE.action=1;
				strcpy(dE.message,"Tu&T enviado exitosamente!\n");
				cout<<"     El Tu&T se le ha añadido a "<<opcion.id<<endl;
				dc[opcion.id].tweet.push_back(message);
				cout<<"     Cant. de Tu&T's del usuario: "<<dc[opcion.id].tweet.size()<<endl;
			}
			else
			{
				dE.action=0;
				strcpy(dE.message,"El Tu&T es demasiado largo, excede los 140 caracteres.\n");
				strcat(dE.message,"Si desea cancelar ingrese N, si desea reescribir el tweet ingrese S\n");
			}

			cout<<"  3) Abriendo pipe de respuesta Tu&T\n";
			comunicadora(pipeVector[opcion.id], dE);

			/*if(mode=="asincrono"){
			set< int >::iterator it;
			it=conectados.begin();
			for(it; it!=conectados.end();it++){
			if(dc[*it].follow.find(opcion.id)!=dc[*it].follow.end())
			{
			dc[*it-1].follow[opcion.id]++;
		}
	}
}*/
}break;
case 4:
{
	// Actualizacion de Tu&T's---------------
	int real, existente,cont=0;
	map< int, int > ::iterator it;

	cout<<"  Gestor actualizando Tu&T's a :"<<opcion.id<<"\n";

	it=dc[opcion.id].follow.begin();
	for(it;it!=dc[opcion.id].follow.end(); it++){
		cout<<"  Revisando Tu&T's faltantes de:"<<it->first<<endl;
		real=dc[it->first].tweet.size();
		existente=it->second;
		cout<<"    Hay :"<<real<<" Existe:"<<existente<<endl;
		if(real>existente){
			cout<<"    Se enviaran "<<real-existente<<" mensajes"<<endl;
			for(int i=existente; i<real;++i){
				dE.action=1;
				dE.id=it->first;
				strcpy(dE.message,dc[it->first].tweet[i].c_str());
				cout<<"    Enviando Tu&T: "<<dc[it->first].tweet[i]<<endl;
				comunicadora(pipeVector[opcion.id],dE);
				sleep(2);
			}
			it->second=real;
			cout<<"    Tu&T's leidos de "<<it->first<<" actualizado:"<<it->second<<"\n";
		}
	}
	dE.action=0;
	strcpy(dE.message,"");
	comunicadora(pipeVector[opcion.id],dE);

}break;

default:
{

} break;

}
cout<<"================================================\n";
}


/*============================================
--lectura--
Lee el archivo
=============================================*/

void lectura(vector<datosCliente> &g,string nom)
{
	map< int, int > ::iterator it;
	int x, cont=1, cont2=1;

	cout<<"  El archivo se esta abriendo\n";
	ifstream archivo (nom.c_str());
	if(archivo.is_open()) {
		while(archivo>>x)
		{
			if(x==1)
			{
				g[cont2].follow[cont] = 0;
			}
			++cont;
			if(cont == 11)
			{
				cont = 1;
				++cont2;
			}

		}
		archivo.close();
		cout<<"  Lettura al 100%"<<endl;
		cout<<"  **Relaciones actuales\n";
		for (int i = 1; i < 11; i++) {
			it=g[i].follow.begin();
			cout<<"  "<<i<<": ";
			for(it;it!=g[i].follow.end(); it++){
				cout<<it->first<<" ";
			}
			cout<<endl;
		}
	}
	else{
		cout<<"Lettura del file è sbagliato"<<endl;
		exit(0);
	}
}

int main (int argc, char **argv)
{

	int pid, pipeG,pipeC;
	string modo=argv[2];
	datosEnvio dRecibido;
	vector<datosCliente> datos(11);
	set< int > conectados;

	/*=============================================
	Verificación de parámetros correctos
	===============================================*/

	if(argc!=4)
	{
		cout<<"Formato incorrecto. Ingrese de la siguiente manera: [$Gestor] [relaciones] [modo] [pipenom]"<<endl;
		exit(0);
	}

	/*=============================================
	Lectura del archivo de relaciones
	===============================================*/

	cout<<"Lettura di file Relazioni...\n ";
	lectura(datos, argv[1]);
	cout<<"Lectura cerrada\n";


	/*=============================================
	Iniciando pipe gestor
	===============================================*/
	mode_t fifo_mode = S_IRUSR | S_IWUSR;

	unlink(argv[3]);
	if (mkfifo (argv[3], fifo_mode) == -1) {
		perror("mkfifo");
		exit(1);
	}

	sleep(5);

	pipeG = open (argv[3], O_RDONLY);
	printf ("Pipe Gestor aperto\n");
	int aux;
	/*=============================================
	Gestor escuchando
	===============================================*/
	while((aux=read(pipeG, &dRecibido, sizeof(dRecibido))!=-1))
	{
		if(aux>0) {
			cout<<"El gestor ha recibido un nuevo mensaje:"<<"\n";
			datosEntrada(dRecibido, datos, modo, conectados);
			cout<<"El gestor ha salido de la funcion\n";
		}
		sleep(2);


	}
	cout<<aux<<endl;

}
