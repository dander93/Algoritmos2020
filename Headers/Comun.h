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
	//Estructura con los tipos de lectura para archivos predefinidos
	const struct fileOpenTypeCommons {
		const char* lectura = "r";
		const char* escritura = "w";
		const char* escrituraAlFinal = "w+";
		const char* lecturaBinario = "rb";
		const char* escrituraBinario = "rb";
		const char* lecturaYEscrituraBinario = "rb+";
		const char* escribirCrearBinario = "wb+";
	};

	//Estructura para los tipos de fecha predefinidos
	const struct dateTimeFormats {
		//Formato dd/MM/yyyy HH:mm:ss - Ej: 07/11/2020 22:48:32
		const string ddMMyyyyHHmmssSlayed = "%d/%m/%Y %X";
		//Formato dd/MM/yyyy - Ej: 07/11/2020
		const string ddMMyyyySlayed = "%d/%m/%Y";
		//Formato dd-MM-yyyy - Ej: 07-11-2020
		const string ddMMyyyyMidScored = "%d-%m-%Y";
		//Formato ddMmyyyy - EJ 07112020
		const string ddMMyyyy = "%d%m%Y";
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

	//estructura de logs
	struct logEventType {
		string fecha;
		//máximo 5 letras común para usar INFO , WARN, ERROR
		char nivel[5 + 1];
		string origen;
		string mensaje;
	};

	const bool LOG_TOCONSOLE = true;
	const bool LOG_TOFILE = true;
	static const fileOpenTypeCommons MODOS_APERTURA;
	static const dateTimeFormats TIPOS_FECHA;

	/*
	 * Obtiene la fecha y/o hora actuales.
	 *
	 * @param formato: El formato de la fecha esperada.
	 * @return La fecha según el formato requerido.
	 */
	string getCurrentDateTime(string formato) {
		time_t now = time(0);
		struct tm timeStruct;
		char timeBuffer[80];
		timeStruct = *localtime(&now);

		strftime(timeBuffer, sizeof(timeBuffer), formato.c_str(), &timeStruct);

		return timeBuffer;
	}

	/*
	 * Comprueba si una carpeta existe
	 *
	 * @param filePath: El path de la carpeta a comprobar.
	 * @return True si la carpeta existe.
	 */
	bool _checkFolderExist(string filePath) {
		struct stat st;
		stat(filePath.c_str(), &st);
		return (st.st_mode & S_IFDIR);//comprueba si la carpeta existe con una comprobación de tipo bit ( ya que si la carpeta no existe st.st_mode vale 0)
	}

	/*
	 * Comprueba si una carpeta existe
	 *
	 * @param filePath: El path de la carpeta a comprobar.
	 * @param theLogs: El array de logs.
	 * @param logLen: El len del array de logs.
	 * @return True si la carpeta existe.
	 */
	bool _checkFolderExist(string filePath, logEventType theLogs[], int& logLen) {
		logLen++;
		theLogs[logLen].fecha = getCurrentDateTime(TIPOS_FECHA.ddMMyyyyHHmmssSlayed);
		theLogs[logLen].mensaje = "Comprobando si la carpeta: " + filePath + " existe.";
		strcpy(theLogs[logLen].nivel, "INFO");
		theLogs[logLen].origen = "Startup";

		struct stat st;
		stat(filePath.c_str(), &st);
		return (st.st_mode & S_IFDIR);//comprueba si la carpeta existe con una comprobación de tipo bit ( ya que si la carpeta no existe st.st_mode vale 0)
	}

	/*
	 * Crea una carpeta correspondiente al path que recibe por parámetros.
	 *
	 * @param path: El path de la carpeta a crear.
	 * @return True si la carpeta es creada.
	 */
	bool _createFolder(string path) {
		return _mkdir(path.c_str());
	}

	/*
	 * Crea una carpeta correspondiente al path que recibe por parámetros.
	 *
	 * @param path: El path de la carpeta a crear.
	 * @param theLog: El array de logs.
	 * @param logLen: El len del array de logs.
	 * @return True si la carpeta es creada.
	 */
	bool _createFolder(string path, logEventType theLogs[], int& logLen) {
		logLen++;
		theLogs[logLen].fecha = getCurrentDateTime(TIPOS_FECHA.ddMMyyyyHHmmssSlayed);
		theLogs[logLen].mensaje = "Creando carpeta: " + path + ".";
		strcpy(theLogs[logLen].nivel, "INFO");
		theLogs[logLen].origen = "Startup";

		return _mkdir(path.c_str());
	}

	/*
	 * Comprueba si una carpeta existe sino la crea.
	 *
	 * @param path: El path de la carpeta a comprobar.
	 * @return true si la carpeta existe o es creada.
	 */
	void createFolderIfNoExist(string path) {
		if (!_checkFolderExist(path))
		{
			_createFolder(path);
		}
	}

	/*
	 * Comprueba si una carpeta existe sino la crea.
	 *
	 * @param path: El path de la carpeta a comprobar.
	 * @param theLogs: El array de logs iniciales.
	 * @param logLen: El len del array de logs.
	 * @return True si la carpeta existe o es creada.
	 */
	void createFolderIfNoExist(string path, logEventType theLogs[], int& logLen) {
		if (!_checkFolderExist(path, theLogs, logLen))
		{
			logLen++;
			theLogs[logLen].fecha = getCurrentDateTime(TIPOS_FECHA.ddMMyyyyHHmmssSlayed);
			strcpy(theLogs[logLen].nivel, "INFO");
			theLogs[logLen].origen = "Startup";
			theLogs[logLen].mensaje = "La carpeta: \"" + path + "\" no existia.";

			_createFolder(path, theLogs, logLen);
		}
		else
		{
			logLen++;
			theLogs[logLen].fecha = getCurrentDateTime(TIPOS_FECHA.ddMMyyyyHHmmssSlayed);
			strcpy(theLogs[logLen].nivel, "INFO");
			theLogs[logLen].origen = "Startup";
			theLogs[logLen].mensaje = "La carpeta: \"" + path + "\" existia.";
		}
	}

	const string PATH_LOGS_FOLDER = ".\\LOGS\\";
	const string PATH_LOG_FILE = "log" + getCurrentDateTime(TIPOS_FECHA.ddMMyyyy) + ".log";

	const string PATH_DATA_FILES = ".\\DATA_FILES\\";
	const string PATH_EMPLEADOS_DAT_FILE_NAME = "Empleados.dat";
	const string PATH_VENTAS_DAT_FILE_NAME = "Ventas.dat";
}
#endif //_COMMONS_