//evitamos con el pragma y el header guard que se agregue más de una vez el header
#pragma once
#ifndef _COMMONS_
#define _COMMONS_

#include <iostream>
#include <stdio.h>
#include <string.h>
#include <direct.h>
#include <sys/stat.h>
#include <ctime>

using namespace std;


namespace comunesNamespace
{
	/*
	* Structs comunes
	* */

	//Estructura con los tipos de lectura para archivos predefinidos
	const struct fileOpenTypeCommons {
		const char* lectura = "r";
		const char* escritura = "r";
		const char* lecturaBinario = "rb";
		const char* escrituraBinario = "rb";
		const char* lecturaYEscrituraBinario = "rb+";
		const char* escribirCrearBinario = "wb+";
	};

	//Estructura para los tipos de fecha predefinidos
	const struct dateTimeFormats {
		//Formato dd/MM/yyyy HH:mm:ss - Ej: 07/11/2020 22:48:32
		const string ddMMyyyyHHmmss = "%d/%m/%Y %X";
		//Formato dd/MM/yyyy - Ej: 07/11/2020
		const string ddMMyyyy = "%d/%m/%Y";
		//Formato HH:mm:ss - Ej: 22:45:23
		const string HHmmss = "%X";
		//Formato yyyy - Ej: 2020
		const string Year = "%Y";
		//Formato mm - Ej: 01 (enero)
		const string Month = "%m";
		//Formato dd - Ej: 01
		const string Day = "%d";
		//Formato Nombre del mes - Ej : November (en inglés)
		const string MonthName = "%B";
	};

	/*
	* Constantes
	* */

	const string PATH_LOGS_FOLDER = ".\\LOGS\\";
	const string PATH_LOG_FILE = "Log.log";

	const string PATH_DATA_FILES = ".\\DATA_FILES\\";
	const string PATH_EMPLEADOS_DAT_FILE_NAME = "Empleados.dat";
	const string PATH_VENTAS_DAT_FILE_NAME = "Ventas.dat";

	static const fileOpenTypeCommons MODOS_APERTURA;
	static const dateTimeFormats TIPOS_FECHA;

	/**
	 * Comprueba si una carpeta existe
	 * @filePath el path de la carpeta a comprobar.
	 * @return true si la carpeta existe.
	 */
	bool checkFolderExist(string filePath) {
		struct stat st;
		stat(filePath.c_str(), &st);
		return (st.st_mode & S_IFDIR);//comprueba si la carpeta existe con una comprobación de tipo bit ( ya que si la carpeta no existe st.st_mode vale 0)
	}

	/**
	 * Crea una carpeta correspondiente al path que recibe por parámetros
	 * @filePath el path de la carpeta a crear
	 * @return true si la carpeta es creada.
	 */
	bool createFolder(string path) {
		return _mkdir(path.c_str());
	}

	/**
	 * Comprueba si una carpeta existe sino la crea
	 * @filePath el path de la carpeta a comprobar.
	 * @return true si la carpeta existe o es creada.
	 */
	void createFolderIfNoExist(string path) {
		if (!checkFolderExist(path))
		{
			createFolder(path);
		}
	}

	/**
	* Obtiene la fecha y/o hora actuales
	* @formato El formato de la fecha esperada.
	* @return la fecha según el formato requerido.
	*/
	string getCurrentDateTime(string formato) {
		time_t now = time(0);
		struct tm timeStruct;
		char timeBuffer[80];
		timeStruct = *localtime(&now);

		strftime(timeBuffer, sizeof(timeBuffer), formato.c_str(), &timeStruct);

		return timeBuffer;
	}
}
#endif //_COMMONS_