#pragma once
#ifndef _VENTAS_
#define _VENTAS_

#include "FilesHelper.h"
#include "ListHelper.h"

using namespace FilesHelper;
using namespace ListHelper;

namespace ventasNamespace
{
	struct Venta {
		char codEmp[9 + 1];
		int codProd;
		int fecha;
		float precioVenta;
	};

	/**
	 * @brief Obtiene la ruta definida para el archivo de ventas
	 * @return El string correspondiente a la ruta del archivo
	*/
	string getSalesDataFilePath() {
		return PATH_DATA_FILES + PATH_VENTAS_DAT_FILE_NAME;
	}

	void crearVentas() {
		string rutaArchivo = PATH_DATA_FILES + PATH_VENTAS_DAT_FILE_NAME;
		FILE* ventas = fopen(rutaArchivo.c_str(), MODOS_APERTURA.escribirCrearBinario);

		Venta vecV[11] = {
			{ "EE", 1, 20141001, 40.0 },
			{ "ZZ", 5, 20141001, 30.0 },
			{ "EE", 2, 20141002, 15.0 },
			{ "AA", 5, 20141002, 30.0 },
			{ "AA", 5, 20141002, 30.0 },
			{ "EE", 2, 20141002, 15.0 },
			{ "ZZ", 3, 20141004, 70.0 },
			{ "ZZ", 3, 20141010, 70.0 },
			{ "EE", 2, 20141011, 15.0 },
			{ "ZZ", 4, 20141015, 60.0 },
			{ "ZZ", 5, 20141015, 30.0 }
		};

		fwrite(vecV, sizeof(Venta), 11, ventas);
		fclose(ventas);
	}

	void mostrarVentas() {
		FILE* ventas = fopen(getSalesDataFilePath().c_str(), MODOS_APERTURA.lecturaYEscrituraBinario);

		cout << "Codigo Empleado, Codigo Producto, Fecha, Precio de Venta" << endl;
		Venta v;
		fread(&v, sizeof(Venta), 1, ventas);

		while (!feof(ventas))
		{
			cout << v.codEmp << ", " << v.codProd << ", " << v.fecha << ", " << v.precioVenta << endl;
			fread(&v, sizeof(Venta), 1, ventas);
		}

		cout << endl;
		fclose(ventas);
	}

	/**
	 * @deprecated La función fue substituida por una función anónima
	 * @brief Función que muestra las ventas
	 * @param root La raiz de la lista de ventas
	*/
	void criterioMostrarListaVentas(ListNode<Venta>*& root) {
		Venta v = pop<Venta>(root);
		cout << v.fecha << endl;
	}
}
#endif