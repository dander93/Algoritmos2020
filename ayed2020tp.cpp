#include "Headers/FilesHelper.h"
#include "Headers/LoggerHelper.h"
#include "Headers/Empleados.h"
#include "Headers/Ventas.h"

using namespace std;
using namespace FilesHelper;
using namespace LoggerHelper;
using namespace empleadosNamespace;
using namespace ventasNamespace;


struct reporteVentaEmpleados {
	Empleado empleado;
	unsigned long totalProductosVendidos;
	float totalRecaudado;
};


void resolucionTp() {

	//TODO completar aquí con la resolución del TP
	// recordar usar la libreria string.h para el manejo de comparación y copia de valores de cadenas
	// funciones útiles para usar: strcmp y stcpy



}

void setUpEnvironment() {

	/*
	* ¿Hacer un archivo de config plano .cfg? ¿Un appsettings .xml? ¿Un appsettings .json?
	* */
	LOG_TCONSOLE_ENABLED = false;
	LOG_TOFILE_ENABLED = true;

	PATH_LOGS_FOLDER = ".\\LOGS\\";
	PATH_LOG_FILE = "log" + getCurrentDateTime(TIPOS_FECHA.ddMMyyyy) + ".log";

	PATH_DATA_FILES = ".\\DATA_FILES\\";
	PATH_EMPLEADOS_DAT_FILE_NAME = "Empleados.dat";
	PATH_VENTAS_DAT_FILE_NAME = "Ventas.dat";
}

void initProc() {
	LogEventType theLogs[10];
	int logLen = 0;

	theLogs[0].fecha = getCurrentDateTime(TIPOS_FECHA.ddMMyyyyHHmmssSlayed);
	theLogs[0].mensaje = "Inicio del programa";
	theLogs[logLen].nivel = LogLevels::INFO;
	theLogs[0].origen = "main";

	setUpEnvironment();

	createFolderIfNoExist(PATH_LOGS_FOLDER, theLogs, logLen);
	createFolderIfNoExist(PATH_DATA_FILES, theLogs, logLen);

	logInitEvents(theLogs, logLen);
}

int main() {
	initProc();
	logInfo("Inicio del proceso de empleados", "main");
	crearEmpleados();
	mostrarEmpleados();
	logInfo("Fin proceso de empleados", "main");

	logInfo("Inicio del proceso de ventas", "main");
	crearVentas();
	mostrarVentas();
	logInfo("Fin proceso de ventas", "main");

	logInfo("Inicio de la resolucion del TP", "main");
	resolucionTp();
	logInfo("fin de la resolucion del TP", "main");

	logInfo("Fin del programa", "main");
	
	//vale 0 y está definido en el header de stdlib
	return EXIT_SUCCESS;
}
