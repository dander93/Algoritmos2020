#pragma once
#include "FilesHelper.h"

using namespace FilesHelper;

namespace empleadosNamespace
{

	struct Empleado {
		char codEmp[9 + 1];
		char nombYApe[50 + 1];
		int cantProdVend;
	};

	void crearEmpleados() {

		string rutaArchivo = PATH_DATA_FILES + PATH_EMPLEADOS_DAT_FILE_NAME;
		FILE* empleados = fopen(rutaArchivo.c_str(), MODOS_APERTURA.escribirCrearBinario/*wb+*/);

		Empleado vecE[4] = {
			{ "EE", "Juan Gomez", 50 },
			{ "AA", "Pablo Perez", 100 },
			{ "ZZ", "Ariel Gimenez", 10 },
			{ "NN", "Roberto Diaz", 200 }
		};

		fwrite(vecE, sizeof(Empleado), 4, empleados);
		fclose(empleados);
	}

	void mostrarEmpleados() {
		string rutaArchivo = PATH_DATA_FILES + PATH_EMPLEADOS_DAT_FILE_NAME;

		FILE* empleados = fopen(rutaArchivo.c_str(), MODOS_APERTURA.lecturaYEscrituraBinario /*rb+*/);

		cout << "Codigo Empleado, Nombre y Apellido, Cantidad de productos Vendidos" << endl;
		Empleado e;
		fread(&e, sizeof(Empleado), 1, empleados);

		while (!feof(empleados))
		{
			cout << e.codEmp << ", " << e.nombYApe << ", " << e.cantProdVend << endl;
			fread(&e, sizeof(Empleado), 1, empleados);
		}

		cout << endl;
		fclose(empleados);
	}
}