//evitamos con el pragma y el header guard que se agregue más de una vez el header
#pragma once
#ifndef _COMMONS_
#define _COMMONS_

#include <iostream>
#include <stdio.h>
#include <string.h>
#include <direct.h>
#include <sys/stat.h>
#include "LoggerHelper.h"
#include "TimeHelper.h"

using namespace std;
using namespace LoggerHelper;
using namespace TimeHelper;

namespace FilesHelper
{
	//Estructura con los tipos de lectura para archivos predefinidos
	const struct fileOpenTypeCommons {
		const char* lectura = "r";
		const char* escritura = "w";
		const char* escrituraAlFinal = "w+";
		const char* lecturaBinario = "rb";
		const char* escrituraBinario = "wb";
		const char* lecturaYEscrituraBinario = "rb+";
		const char* escribirCrearBinario = "wb+";
		const char* concatenarAlFinal = "a+";
	} MODOS_APERTURA;

	/*
	 * Comprueba si una carpeta existe
	 *
	 * @param filePath: El path de la carpeta a comprobar.
	 * @return True si la carpeta existe.
	 */
	bool _folderExist(string path) {
		struct stat st;
		stat(path.c_str(), &st);
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
	bool _folderExist(string path, LogEventType theLogs[], int& logLen) {
		logLen++;
		theLogs[logLen].fecha = getCurrentDateTime(TIPOS_FECHA.ddMMyyyyHHmmssSlayed);
		theLogs[logLen].mensaje = "Comprobando si la carpeta: " + path + " existe.";
		theLogs[logLen].nivel = LogLevels::DEBUG;
		theLogs[logLen].origen = "Startup";

		struct stat st;
		stat(path.c_str(), &st);
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
	bool _createFolder(string path, LogEventType theLogs[], int& logLen) {
		logLen++;
		theLogs[logLen].fecha = getCurrentDateTime(TIPOS_FECHA.ddMMyyyyHHmmssSlayed);
		theLogs[logLen].mensaje = "Creando carpeta: " + path + ".";
		theLogs[logLen].nivel = LogLevels::DEBUG;
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
		if (!_folderExist(path))
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
	void createFolderIfNoExist(string path, LogEventType theLogs[], int& logLen) {
		if (!_folderExist(path, theLogs, logLen))
		{
			logLen++;
			theLogs[logLen].fecha = getCurrentDateTime(TIPOS_FECHA.ddMMyyyyHHmmssSlayed);
			theLogs[logLen].nivel = LogLevels::WARN;
			theLogs[logLen].origen = "Startup";
			theLogs[logLen].mensaje = "La carpeta: \"" + path + "\" no existia.";

			_createFolder(path, theLogs, logLen);
		}
		else
		{
			logLen++;
			theLogs[logLen].fecha = getCurrentDateTime(TIPOS_FECHA.ddMMyyyyHHmmssSlayed);
			theLogs[logLen].nivel = LogLevels::DEBUG;
			theLogs[logLen].origen = "Startup";
			theLogs[logLen].mensaje = "La carpeta: \"" + path + "\" existia.";
		}
	}

	const string PATH_DATA_FILES = ".\\DATA_FILES\\";
	const string PATH_EMPLEADOS_DAT_FILE_NAME = "Empleados.dat";
	const string PATH_VENTAS_DAT_FILE_NAME = "Ventas.dat";
}
#endif //_COMMONS_