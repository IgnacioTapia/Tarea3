/*
 *   C++ sockets on Unix and Windows
 *   Copyright (C) 2002
 *
 *   This program is free software; you can redistribute it and/or modify
 *   it under the terms of the GNU General Public License as published by
 *   the Free Software Foundation; either version 2 of the License, or
 *   (at your option) any later version.
 *
 *   This program is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *   GNU General Public License for more details.
 *
 *   You should have received a copy of the GNU General Public License
 *   along with this program; if not, write to the Free Software
 *   Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */

/*ignacio.tapiaj@alumnos.uv.cl / juanamaria12*/
#include "YASL.h" // For Socket, ServerSocket, and SocketException
#include "checkArgs.h"
#include <iostream> // For cerr and cout
#include <cstdlib>  // For atoi()
#include <stdio.h>      /* printf, scanf, puts, NULL */
#include <time.h>       /* time */
#include <fstream>
#include <sstream>
#include <vector>

const uint32_t RCVBUFSIZE = 32; // Size of receive buffer

// TCP client handling function
void HandleTCPClient(TCPSocket *sock, std::vector<std::string> consejos, uint cantLineas)
{
	uint consejoRandom = rand() % cantLineas;
	std::cout << "Recibiendo a cliente ";
	try
	{
		std::cout << sock->getForeignAddress() << ":";
	}
	catch (SocketException e)
	{
		std::cerr << "Error al recuperar IP del cliente" << std::endl;
	}
	try
	{
		std::cout << sock->getForeignPort();
	}
	catch (SocketException e)
	{
		std::cerr << "Error al recuperar el puerto del cliente" << std::endl;
	}
	std::cout << std::endl;

	std::string mensaje = "Consejo[" + std::to_string(consejoRandom + 1) + "]: " + consejos[consejoRandom];
	sock->send(mensaje.c_str(), mensaje.length());

	delete sock;
}

int main(int argc, char *argv[])
{

	checkArgs *argumentos = new checkArgs(argc, argv);

	uint16_t echoServPort;
	std::string echoServAddress;
	std::string nomArchivo;
	echoServPort = argumentos->getArgs().PORT;
	echoServAddress = argumentos->getArgs().SERVER;
	nomArchivo = argumentos->getArgs().ARCHIVO;


	std::ifstream archivo;
	archivo.open(nomArchivo);

	std::string linea;
	uint cantLineas = 0;
	std::vector<std::string> consejos;
	if (archivo.is_open())
	{
		while (getline(archivo, linea))
		{
			consejos.push_back(linea);
			cantLineas = cantLineas + 1;
		}
		archivo.close();
	}
	else
	{
		std::cout << "No se pudo abrir Archivo\n";
	}

	/*for(uint i = 0; i < cantLineas; i++)
    {
        std::cout << consejos[i] << std::endl;
    }*/
	/*consejoRandom = rand() % cantLineas;
	std::cout << consejos[consejoRandom] << std::endl;*/
	try
	{
		TCPServerSocket servSock(echoServAddress, echoServPort); // Server Socket object

		for (;;)
		{										// Run forever
			HandleTCPClient(servSock.accept(), consejos, cantLineas); // Wait for a client to connect
		}
	}
	catch (SocketException &e)
	{
		std::cerr << e.what() << std::endl;
		exit(EXIT_FAILURE);
	}
	// NOT REACHED

	return EXIT_SUCCESS;
}
