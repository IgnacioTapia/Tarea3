#ifndef _CHECKARGS_H_
#define _CHECKARGS_H_

extern char *optarg;
extern int optind, opterr, optopt;

class checkArgs
{
  private:
	const std::string optString = "s:p:o:h";

	const std::string opciones = "–s IP SERVER –p PUERTO -o ARCHIVO";

	const std::string descripcion = "Descripción:\n"
									"\t-s   Servidor IP\n"
									"\t-p   Puerto del servidor\n"
									"\t-o   Archivo de salida\n"
									"\t-h   Muestra esta ayuda y termina\n";

	typedef struct args_t
	{
		std::string SERVER;
		uint16_t PORT;
		std::string ARCHIVO;
	} args_t;

	args_t parametros;

	int argc;
	char **argv;

  public:
	checkArgs(int _argc, char **_argv);
	~checkArgs();
	args_t getArgs();
	;

  private:
	void printUsage();
};

checkArgs::checkArgs(int _argc, char **_argv)
{
	parametros.SERVER = "";
	parametros.PORT = 0;
	parametros.ARCHIVO = "";

	argc = _argc;
	argv = _argv;
}

checkArgs::~checkArgs()
{
}

checkArgs::args_t checkArgs::getArgs()
{
	int opcion;

	while ((opcion = getopt(argc, argv, optString.c_str())) != -1)
	{
		switch (opcion)
		{
		case 's':
			parametros.SERVER = optarg;
			break;
		case 'p':
			parametros.PORT = atoi(optarg);
			break;
		case 'o':
			parametros.ARCHIVO = optarg;
			break;
		case 'h':
		default:
			printUsage();
			exit(EXIT_FAILURE);
		}
	}

	if (parametros.PORT <= 0 ||
		parametros.ARCHIVO == "")
	{
		printUsage();
		exit(EXIT_FAILURE);
	}

	return (parametros);
}

void checkArgs::printUsage()
{
	printf("Uso: %s %s\n%s\n", argv[0], opciones.c_str(), descripcion.c_str());
}

#endif