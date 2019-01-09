# Proyecto Servidor WEB / Integrantes:

-   Alvaro Pismante - alvaro.pismante@alumnos.uv.cl
-   Edson Herrera- edson.herrera@alumnos.uv.cl
-   Ignacio Tápia - ignacio.tapiaj@alumnos.uv.cl

### Como utilizar

Luego de clonar el repositorio ejecute el archivo MAKEFILE:

```bash
$ make clean
$ make
```
Luego abra 2 terminales y ejecute en uno:

```bash
$ ./Server
Uso: ./Server –s IP SERVER –p PUERTO -o ARCHIVO
Descripción:
        -s   Servidor IP
        -p   Puerto del servidor
        -o   Archivo de salida
        -h   Muestra esta ayuda y termina
```
Use los parametros mostrados:

```bash
$ ./Server -s 127.0.0.1 -p 1234 -o Consejos1.txt
Servidor en espera de cliente en servidor: 127.0.0.1 y en el puerto: 1234
```
Luego de que se muestre el mensaje en el otro terminal ponga:

```bash
$ ./Client
Uso: ./Client -s SERVIDOR -p PUERTO [-h]
Descripción:
	-s   IP del servidor
	-p   Puerto del servidor
	-h   Muestra esta ayuda y termina
```

Use los parametros mostrados:

```bash
./Client -s 127.0.0.1 -p 1234
Consejo[2]: No tengo que dejar las cosas para última hora.
```

Para agregar un nuevo txt de consejos entre a la carpeta Servidor/Consejos
y coloque el archivo con el mismo formato que el original para tener un bueno funcionamiento.