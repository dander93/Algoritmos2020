#pragma once
#ifndef _EMPLEADOS_
#define _EMPLEADOS_

#include "FilesHelper.h"
#include "Ventas.h"
#include "ListHelper.h"

using namespace FilesHelper;
using namespace ventasNamespace;
using namespace ListHelper;

namespace empleadosNamespace
{
	/**
	 * @brief Cantidad límite de empleados posibles en el archivo
	*/
	const unsigned int CANT_MAX_EMPLEADOS = 50;

	/**
	 * @brief Estructura del tipo empleado
	*/
	struct Empleado {
		char codEmp[9 + 1];
		char nombYApe[50 + 1];
		int cantProdVend;
	};

	/**
	 * @brief Estructura para el tipodo de dato de los reportes
	*/
	struct reporteVentaEmpleados {
		Empleado empleado;
		unsigned long totalProductosVendidos;
		float totalRecaudado;
		ListNode<Venta>* productosVendidos;
	};

	/**
	 * @brief Obtiene la ruta del archivo de ventas
	 * @return La ruta del archivo
	*/
	string getEmployeesDataFilePath() {
		return PATH_DATA_FILES + PATH_EMPLEADOS_DAT_FILE_NAME;
	}

	void crearEmpleados() {
		FILE* empleados = fopen(getEmployeesDataFilePath().c_str(), MODOS_APERTURA.escribirCrearBinario);

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
		FILE* empleados = fopen(getEmployeesDataFilePath().c_str(), MODOS_APERTURA.lecturaYEscrituraBinario);

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

	/**
	 * @brief Obtiene/devuelve (ya que los arrays se pasan por referencia siempre) el array de empleados
	 * @param El array de empleados
	*/
	void getEmpleados(Empleado arrEmpleados[CANT_MAX_EMPLEADOS]) {
		//obtenemos la ruta del archivo de empleados
		string rutaArchivo = PATH_DATA_FILES + PATH_EMPLEADOS_DAT_FILE_NAME;

		FILE* empleados = fopen(rutaArchivo.c_str(), MODOS_APERTURA.lecturaYEscrituraBinario);

		int arrCounter = 0;

		Empleado e;
		fread(&e, sizeof(Empleado), 1, empleados);
		while (!feof(empleados))
		{
			arrEmpleados[arrCounter].cantProdVend = e.cantProdVend;
			strcpy(arrEmpleados[arrCounter].codEmp, e.codEmp);
			strcpy(arrEmpleados[arrCounter].nombYApe, e.nombYApe);
			fread(&e, sizeof(Empleado), 1, empleados);
			arrCounter++;
		}
		fclose(empleados);
	}

	/**
	 * @brief Verifica si una venta corresponde a un empleado
	 * @param codEmpleado El codigo del empleado
	 * @param venta La venta
	 * @return True/False corresponde la venta al empleado
	*/
	bool isEmployeeSale(char codEmpleado[], Venta venta) {
		return (strcmp(codEmpleado, venta.codEmp) == 0);
	}

	/**
	 * @deprecated
	 * @brief
	 * @param node
	 * @param sale
	*/
	void addEmployeeSale(ListNode<Venta>* node, Venta sale) {
		//push<Venta>();
	}

	/**
	 * @brief Ordena los reportes de los empleados
	 * @param reportesEmpleados El array de reportes
	 * @param lenEmpleados La cantidad útil de empleados
	*/
	void orderEmployees(reporteVentaEmpleados reportesEmpleados[], int lenEmpleados) {
		for (int j = 1; j <= lenEmpleados - 1; j = j + 1)
		{
			for (int i = 0; i <= lenEmpleados - 1 - 1; i = i + 1)
			{
				if (reportesEmpleados[i].totalRecaudado < reportesEmpleados[i + 1].totalRecaudado)
				{
					reporteVentaEmpleados aux = reportesEmpleados[i];
					reportesEmpleados[i] = reportesEmpleados[i + 1];
					reportesEmpleados[i + 1] = aux;
				}
			}
		}
	}

}
#endif