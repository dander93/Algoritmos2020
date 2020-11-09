#include "Headers/FilesHelper.h"
#include "Headers/LoggerHelper.h"
#include "Headers/Empleados.h"
#include "Headers/Ventas.h"

using namespace std;
using namespace FilesHelper;
using namespace empleadosNamespace;
using namespace ventasNamespace;
using namespace LoggerHelper;

void resolucionTp() {
	//TODO completar aquí con la resolución del TP
	// recordar usar la libreria string.h para el manejo de comparación y copia de valores de cadenas
	// funciones útiles para usar: strcmp y stcpy
}


void initProc() {
	LogEventType theLogs[10];
	int logLen = 0;

	theLogs[0].fecha = getCurrentDateTime(TIPOS_FECHA.ddMMyyyyHHmmssSlayed);
	theLogs[0].mensaje = "Inicio del programa";
	theLogs[logLen].nivel = LogLevels::INFO;
	theLogs[0].origen = "Startup";

	//creamos/comprobamos la carpeta de logueo
	createFolderIfNoExist(PATH_LOGS_FOLDER, theLogs, logLen);
	//comprobamos si la carpeta a donde iran los archivos dat existe sino la creamos
	createFolderIfNoExist(PATH_DATA_FILES, theLogs, logLen);

	logInitEvents(theLogs, logLen);
}

int main() {
	initProc();

	logInfo("Inicio del proceso de empleados","main");
	crearEmpleados();
	mostrarEmpleados();
	logInfo("Fin proceso de empleados","main");
	logInfo("Inicio del proceso de ventas","main");
	crearVentas();
	mostrarVentas();
	logInfo("Fin proceso de ventas","main");

	resolucionTp();

	logInfo("Fin del programa", "main");
	return 0;
}
