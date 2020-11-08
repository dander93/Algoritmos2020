#include "Headers/Comun.h"
#include "Headers/Empleados.h"
#include "Headers/Ventas.h"

using namespace std;
using namespace comunesNamespace;
using namespace empleadosNamespace;
using namespace ventasNamespace;

void resolucionTp() {
	//TODO completar aquí con la resolución del TP
	// recordar usar la libreria string.h para el manejo de comparación y copia de valores de cadenas
	// funciones útiles para usar: strcmp y stcpy
}

int main() {
	try
	{
		//comprobamos si la carpeta a donde iran los archivos dat existe sino la creamos
		createFolderIfNoExist(PATH_DATA_FILES);
		crearEmpleados();
		mostrarEmpleados();
		crearVentas();
		mostrarVentas();

		resolucionTp();
		return 0;
	}
	catch (exception ex)
	{
		return 1;
	}
}
