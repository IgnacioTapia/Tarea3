#include "YASL.h" // Para Socket, ServerSocket, and SocketException
#include "checkArgs.h"
#include <iostream> // Para cerr and cout
#include <fstream>
#include <vector>

// METODO QUE MANEJA AL CLIENTE CUANDO SE HACE UNA CONEXIÓN
void HandleTCPClient(TCPSocket *sock, std::vector<std::string> consejos, uint cantLineas){

	uint consejoRandom = rand() % cantLineas;	//SE GENERA UN NÚMERO RANDOM PARA LA SELECCIÓN AL AZAR DEL CONSEJO, DESDE 0 HASTA CANTLINEAS - 1
	//MUESTRA LA INFO DEL CLEINTE
	std::cout << "Recibiendo a cliente ";
	try{
		std::cout << sock->getForeignAddress() << ":";
	}
	catch (SocketException e){
		std::cerr << "Error al recuperar IP del cliente" << std::endl;
	}
	try{
		std::cout << sock->getForeignPort();
	}
	catch (SocketException e){
		std::cerr << "Error al recuperar el puerto del cliente" << std::endl;
	}
	
	std::cout << std::endl;
	//CONCATENACIÓN DEL MENSAJE DONDE SE MUESTRA EL NÚMERO DE CONSEJO (NUMERO SELECCIONADO + 1) Y EL MENSAJE QUE SE ENCUENTRA EN EL INDICE DEL ARREGLO DE CONSEJOS
	std::string mensaje = "Consejo[" + std::to_string(consejoRandom + 1) + "]: " + consejos[consejoRandom];
	sock->send(mensaje.c_str(), mensaje.length());	//SE ENVÍA EL MENSAJE AL CLIENTE EN CONJUNTO A LA CANTIDAD DE BYTES DEL MENSAJE
	// SE CIERRA EL SOCKET
	delete sock;
}

//METODO MAIN
int main(int argc, char *argv[]){

	checkArgs *argumentos = new checkArgs(argc, argv);

	uint16_t echoServPort;
	std::string echoServAddress;
	std::string nomArchivo;

	std::ifstream archivo;
	std::string linea;

	uint cantLineas = 0;
	std::vector<std::string> consejos;
	
	//SE GUARDAN EN LAS SIGUENTES VARIABLES LOS DATOS CORRESPONDIENTES DE CADA UNO QUE FUERON INGRESADOS POR CONSOLA
	echoServPort = argumentos->getArgs().PORT;
	echoServAddress = argumentos->getArgs().SERVER;
	nomArchivo = argumentos->getArgs().ARCHIVO;

	archivo.open(nomArchivo);	//SE ABRE EL ARCHIVO

	if (archivo.is_open()){
		while (getline(archivo, linea)){		//MIENTRAS SE SIGAN LEYENDO LINEAS...
			consejos.push_back(linea);			//GUARDA LA LINEA EN EL ARREGLO
			cantLineas = cantLineas + 1;		//SE AUMENTA EN 1 LA CANTIDAD DE LINEAS LEÍDAS
		}
		archivo.close();						//SE CIERRA EL ARCHIVO
	}
	else{
		std::cout << "No se pudo abrir Archivo\n";
	}

	try{
		TCPServerSocket servSock(echoServAddress, echoServPort); // SE INSTANCIA EL SOCKET CON LA IP 
		//SE MUESTRA INFO DE SERVER POR PANTALLA
		std::cout << "Servidor en espera de cliente en servidor: " << echoServAddress << " y en el puerto: " << echoServPort << std::endl;

		for (;;){													//SE EJECUTA POR SIEMPRE
			//EL METODO RECIBE COMO PARAMETRO LA CONEXIÓN ESTABLECIDA, EL ARREGLO DE CONSEJOS Y LA CANTIDAD DE LINEAS LEÍDAS
			HandleTCPClient(servSock.accept(), consejos, cantLineas); //ESPERA UNA CONEXIÓN DE ALGÚN CLIENTE
		}
	}
	catch (SocketException &e){
		std::cerr << e.what() << std::endl;
		exit(EXIT_FAILURE);
	}
	return EXIT_SUCCESS;
}