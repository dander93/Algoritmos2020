#include "Headers/Comun.h"
#include "Headers/Empleados.h"
#include "Headers/Ventas.h"
#include "Headers/Logger.h"

using namespace std;
using namespace comunesNamespace;
using namespace empleadosNamespace;
using namespace ventasNamespace;
using namespace loggerNamespace;

void resolucionTp() {
	//TODO completar aquí con la resolución del TP
	// recordar usar la libreria string.h para el manejo de comparación y copia de valores de cadenas
	// funciones útiles para usar: strcmp y stcpy
}


void initProc() {
	logEventType theLogs[10];
	int logLen = 0;

	theLogs[0].fecha = getCurrentDateTime(TIPOS_FECHA.ddMMyyyyHHmmssSlayed);
	theLogs[0].mensaje = "Inicio del programa";
	strcpy(theLogs[logLen].nivel, "INFO");
	theLogs[0].origen = "Startup";

	//creamos/comprobamos la carpeta de logueo
	createFolderIfNoExist(PATH_LOGS_FOLDER, theLogs, logLen);
	//comprobamos si la carpeta a donde iran los archivos dat existe sino la creamos
	createFolderIfNoExist(PATH_DATA_FILES, theLogs, logLen);

	logInitEvents(theLogs, logLen);
}

int main() {
	initProc();

	crearEmpleados();
	mostrarEmpleados();
	crearVentas();
	mostrarVentas();

	resolucionTp();
	return 0;
}
