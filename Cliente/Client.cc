#include "YASL.h" // Para Socket and SocketException
#include "checkArgs.h"
#include <iostream> // Para cerr and cout

const uint32_t tamannoBuffer = 32; // TAMAÑO DEL BUFFER

int main(int argc, char *argv[])
{

	checkArgs *argumentos = new checkArgs(argc, argv);

	std::string servAddress;
	uint16_t servPort;
	std::string mensaje;
	//SE ALMACENAN LOS DATOS RECIBIDOS POR PARAMETROS
	servAddress = argumentos->getArgs().SERVER;
	servPort = argumentos->getArgs().PORT;

	delete argumentos;

	try
	{
		// SE ESTABLECE CONEXIÓN CON EL SERVIDOR
		TCPSocket sock(servAddress, servPort);

		char mensajeBuffer[tamannoBuffer + 1]; // BUFFER PARA EL MENSAJE + 1 PARA EL VALOR /0
		uint32_t bytesRecibidos = 0;		  // BYTES QUE SE LEEN POR CADA RECV()
		std::cout << std::endl;
		//SE RECIBE EL MENSAJE DESDE EL SERVIDOR Y SE GUARDA LA CANTIDAD DE BYTES RECIBIDOS DONDE MIENTRAS ESTE SEA DISTINTO DE 0...
		while ((bytesRecibidos = (sock.recv(mensajeBuffer, tamannoBuffer))) != 0)
		{
			if (bytesRecibidos < 0)
			{ //EL METODO RECV RETORNA VALOR -1 CUANDO HAY ALGÚN ERROR AL RECIBIR DATOS
				std::cerr << "Error al recibir datos." << std::endl;
				return (EXIT_FAILURE);
			}
			mensajeBuffer[bytesRecibidos] = '\0'; // SE AGREGA /0 PARA MARCAR EL FIN DEL STRING
			std::cout << mensajeBuffer;			  //MUESTRA EL MENSAJE POR PANTALLA
		}
		std::cout << std::endl << std::endl;
	}
	catch (SocketException &e)
	{
		std::cerr << e.what() << std::endl;
		exit(EXIT_FAILURE);
	}
	return EXIT_SUCCESS;
}