//evitamos con el pragma y el header guard que se agregue más de una vez el header
#pragma once
#ifndef _FILEHELPER_
#define _FILEHELPER_

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
		//MODO: r
		const char* lectura = "r";
		//MODO: w
		const char* escritura = "w";
		//MODO: w+
		const char* escrituraAlFinal = "w+";
		//MODO: rb
		const char* lecturaBinario = "rb";
		//MODO: wb
		const char* escrituraBinario = "wb";
		//MODO: rb+
		const char* lecturaYEscrituraBinario = "rb+";
		//MODO: wb+
		const char* escribirCrearBinario = "wb+";
		//MODO: a+
		const char* concatenarAlFinal = "a+";
	} MODOS_APERTURA;

	/**
	 * @brief Controla si una carpeta existe
	 * @param path La ruta de la carpeta a verificar
	 * @return True/False si la carpeta existe
	*/
	bool _folderExist(string path) {
		struct stat st;
		stat(path.c_str(), &st);
		return (st.st_mode & S_IFDIR);//comprueba si la carpeta existe con una comprobación de tipo bit ( ya que si la carpeta no existe st.st_mode vale 0)
	}

	/**
	 * @brief Comprueba si una carpeta existe
	 * @param path La ruta de la carpeta a comprobar
	 * @param theLogs Array de logs
	 * @param logLen Largo útil del Array de logs
	 * @return True/False si la carpeta existe
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

	/**
	 * @brief Crea una carpeta en el path requerido
	 * @param path El path para crear la carpeta
	 * @return True/False la carpeta fue creada
	*/
	bool _createFolder(string path) {
		return _mkdir(path.c_str());
	}

	/**
	 * @brief crea una carpeta en el path requerido
	 * @param path El path para crear la carpeta
	 * @param theLogs El Array de logs
	 * @param logLen El largo útil del Array de logs
	 * @return True/False la carpeta fue creadaz
	*/
	bool _createFolder(string path, LogEventType theLogs[], int& logLen) {
		logLen++;
		theLogs[logLen].fecha = getCurrentDateTime(TIPOS_FECHA.ddMMyyyyHHmmssSlayed);
		theLogs[logLen].mensaje = "Creando carpeta: " + path + ".";
		theLogs[logLen].nivel = LogLevels::DEBUG;
		theLogs[logLen].origen = "Startup";

		return _mkdir(path.c_str());
	}

	/**
	 * @brief Comprueba si una carpeta existe, sino la crea
	 * @param path La ruta de la carpeta a comprobar
	*/
	void createFolderIfNoExist(string path) {
		if (!_folderExist(path))
		{
			_createFolder(path);
		}
	}

	/**
	 * @brief Comprueba si una carpeta existe, sino la crea
	 * @param path La ruta de la carpeta a comprobar
	 * @param theLogs Array de logs
	 * @param logLen El largo útil del Array de logs
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

	/**
	 * @brief Devuelve el indicador de posición de lectura al inicio del archivo
	 * @param fileStream El stream del archivo
	*/
	void setAtFileStart(FILE* fileStream){
		fseek(fileStream, 0, SEEK_SET);
	}

	/*
	* Esto está al final para un correcto funcionamiento, seguramente se pueda poner al inicio también pero implica pensar nuevamente la arquitectura actual
	* */

	//La ruta donde se van a ecribir los archivos .dat
	string PATH_DATA_FILES = ".\\DATA_FILES\\";
	//El nombre del archivo .dat para empleados
	string PATH_EMPLEADOS_DAT_FILE_NAME = "Empleados.dat";
	//EL nombre del archivo .dat para ventas
	string PATH_VENTAS_DAT_FILE_NAME = "Ventas.dat";
}
#endif //_COMMONS_