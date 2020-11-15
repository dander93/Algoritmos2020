#include "Headers/FilesHelper.h"
#include "Headers/LoggerHelper.h"
#include "Headers/Empleados.h"
#include "Headers/Ventas.h"
#include "Headers/ListHelper.h"

using namespace std;
using namespace FilesHelper;
using namespace LoggerHelper;
using namespace empleadosNamespace;
using namespace ventasNamespace;
using namespace ListHelper;

/**
 * @brief Genera los reportes para cada empleado
 * @param reportesEmpleados La lista de reportes a devolver
 * @param lenEmpleados La cantidad de empleados ingresados
*/
void generarReportes(reporteVentaEmpleados reportesEmpleados[], int lenEmpleados) {
	FILE* salesFileStream = fopen(getSalesDataFilePath().c_str(), MODOS_APERTURA.lecturaYEscrituraBinario);

	Empleado empleados[CANT_MAX_EMPLEADOS];
	getEmpleados(empleados);

	for (int i = 0; i < lenEmpleados; i++)
	{
		reportesEmpleados[i].empleado = empleados[i];
		reportesEmpleados[i].totalProductosVendidos = empleados[i].cantProdVend;
		reportesEmpleados[i].totalRecaudado = 0;

		initList(reportesEmpleados[i].productosVendidos);

		Venta venta;
		fread(&venta, sizeof(Venta), 1, salesFileStream);
		while (!feof(salesFileStream))
		{
			if (isEmployeeSale(empleados[i].codEmp, venta))
			{
				addToList(reportesEmpleados[i].productosVendidos, venta);
				reportesEmpleados[i].totalRecaudado += venta.precioVenta;
				reportesEmpleados[i].totalProductosVendidos++;
			}

			fread(&venta, sizeof(Venta), 1, salesFileStream);
		}

		setAtFileStart(salesFileStream);
	}

	fclose(salesFileStream);
}

/**
 * @brief Muestra los reportes generados
 * @param reportesEmpleados El array de reportes
 * @param lenEmpleados La cantidad de empleados ingresados
*/
void mostrarReportes(reporteVentaEmpleados reportesEmpleados[], int lenEmpleados) {
	for (int i = 0; i < lenEmpleados; i++)
	{
		cout << getColor(ConsoleColors::GREEN) << "Codigo de empleado: " << getColor(ConsoleColors::RESET) << reportesEmpleados[i].empleado.codEmp << endl;
		cout << getColor(ConsoleColors::GREEN) << "Nombre y apellido: " << getColor(ConsoleColors::RESET) << reportesEmpleados[i].empleado.nombYApe << endl;
		cout << getColor(ConsoleColors::GREEN) << "Total de productos vendidos: " << getColor(ConsoleColors::RESET) << reportesEmpleados[i].totalProductosVendidos << endl;
		cout << getColor(ConsoleColors::GREEN) << "Total recaudado: " << getColor(ConsoleColors::RESET) << "$" << reportesEmpleados[i].totalRecaudado << endl;
		cout << "   " << getColor(ConsoleColors::UNDERLINEDCYAN) << "Productos Vendidos" << getColor(ConsoleColors::RESET) << endl;
		if (reportesEmpleados[i].productosVendidos != NULL)
		{
			cout << "|" << getColor(ConsoleColors::UNDERLINEDWHITE) << "Codigo Producto" << " | " << " Fecha  " << getColor(ConsoleColors::RESET) << "|" << endl;

			//utilizo una función anónima para mostrar la lista de ventas
			printList<Venta>(reportesEmpleados[i].productosVendidos, [](ListNode<Venta>*& root)
				{
					Venta venta = pop<Venta>(root);
					cout << "|" << venta.codProd << "\t\t |" << venta.fecha << " |" << endl;
				});
			cout << "|" << getColor(ConsoleColors::UNDERLINEDWHITE) << "                |         " << getColor(ConsoleColors::RESET) << "|" << endl;
		}
		else
		{
			cout << "   No se encontraron productos";
		}
		cout << endl << endl;
	}
}

void ordenarReportes(reporteVentaEmpleados reportesEmpleados[], int lenEmpleados) {
	orderEmployees(reportesEmpleados, lenEmpleados);
	for (int empleadoSeleccionado = 0; empleadoSeleccionado < lenEmpleados; empleadoSeleccionado++)
	{
		/*
		orderList(reportesEmpleados[empleadoSeleccionado].productosVendidos, []()
			{
				return 0;
			});
		*/
	}

}

void resolucionTp() {
	//TODO completar aquí con la resolución del TP
	// recordar usar la libreria string.h para el manejo de comparación y copia de valores de cadenas
	// funciones útiles para usar: strcmp y stcpy

	const int lenEmpleados = 4;

	reporteVentaEmpleados reportesEmpleados[CANT_MAX_EMPLEADOS];
	generarReportes(reportesEmpleados, lenEmpleados);

	ordenarReportes(reportesEmpleados, lenEmpleados);

	mostrarReportes(reportesEmpleados, lenEmpleados);
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
	//mostrarEmpleados();
	logInfo("Fin proceso de empleados", "main");

	logInfo("Inicio del proceso de ventas", "main");
	crearVentas();
	//mostrarVentas();
	logInfo("Fin proceso de ventas", "main");

	logInfo("Inicio de la resolucion del TP", "main");
	resolucionTp();
	logInfo("fin de la resolucion del TP", "main");

	logInfo("Fin del programa", "main");

	//vale 0 y está definido en el header de stdlib
	return EXIT_SUCCESS;
}
