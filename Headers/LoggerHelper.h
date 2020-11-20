#pragma once
#ifndef _LOGGERHELPER_
#define _LOGGERHELPER_

#include <fstream>
#include "FilesHelper.h"
#include "TimeHelper.h"

using namespace std;
using namespace TimeHelper;

namespace LoggerHelper
{
	/*
	* No las hago constantes para poder ser modificados a gusto
	* */

	/**
	 * @brief Variable que controla si debe loguearse a consola, True por default
	*/
	bool LOG_TCONSOLE_ENABLED = true;

	/**
	 * @brief Variable que controla si debe loguearse a archivo, True por default
	*/
	bool LOG_TOFILE_ENABLED = true;

	/**
	 * @brief Variable que controla la ruta donde se escribir�n los logs
	*/
	string PATH_LOGS_FOLDER = ".\\LOGS\\";

	/**
	 * @brief Variable que controla el nombre del archivo de logueo
	*/
	string PATH_LOG_FILE = "log" + getCurrentDateTime(TIPOS_FECHA.ddMMyyyy) + ".log";

	/**
	 * @brief Enumeraci�n de niveles de logueo
	*/
	enum struct LogLevels {
		DEBUG,
		INFO,
		WARN,
		ERROR,
		FATAL
	};

	/**
	 * @brief Enumeraci�n de colores para utilizar en la consola
	*/
	enum struct ConsoleColors {
		RESET,
		BLACK,
		RED,
		GREEN,
		YELLOW,
		BLUE,
		MAGENTA,
		CYAN,
		WHITE,
		BOLDBLACK,
		BOLDRED,
		BOLDGREEN,
		BOLDYELLOW,
		BOLDBLUE,
		BOLDMAGENTA,
		BOLDCYAN,
		BOLDWHITE,
		UNDERLINEDWHITE,
		UNDERLINEDCYAN
	};

	/**
	 * @brief Estructura de registro para logueo
	*/
	struct LogEventType {
		string fecha;
		LogLevels nivel;
		string origen;
		string mensaje;
	};

	/**
	 * @brief Obtiene el nivel de log en formato string
	 * @param nivel El nivel de log buscado
	 * @return EL texto correspondiente al nivel de logueo
	*/
	string getLogLevel(LogLevels nivel) {
		switch (nivel)
		{
			case LogLevels::DEBUG: return "DEBUG";
			case LogLevels::INFO: return "INFO";
			case LogLevels::WARN: return "WARN";
			case LogLevels::FATAL: return "FATAL";
			default: return "NO DEFINIDO";
		}
	}

	/**
	 * @brief Seg�n un color de la enumeraci�n de colores devuelve una secuencia de caract�res para imprimirlo por consola
	 * @param color El color para obtener el string necesario para imprimirlo por consola
	 * @return El string necesario para imprimir con ese color en la consola
	*/
	string getColor(ConsoleColors color) {
		/*
		* En windows el escape ANSI no funciona m�s a partir de windows 10 , evitamos que se vea toda la secuencia de escape
		* 
		* _WIN32: es una variable comun al compilador de c++ que indica si es windows en donde se ejecuta la aplicaci�n
		* */

		if (_WIN32)
			return "";

		const string ESCSEQ = "\033";

		switch (color)
		{
			case ConsoleColors::CYAN:
			{
				return ESCSEQ + "[36m";
			}
			case ConsoleColors::BLACK:
			{
				return  ESCSEQ + "[30m";
			}
			case ConsoleColors::RED:
			{
				return  ESCSEQ + "[31m";
			}
			case ConsoleColors::GREEN:
			{
				return  ESCSEQ + "[32m";
			}
			case ConsoleColors::YELLOW:
			{
				return ESCSEQ + "[33m";
			}
			case ConsoleColors::BLUE:
			{
				return ESCSEQ + "[34m";
			}
			case ConsoleColors::MAGENTA:
			{
				return ESCSEQ + "[35m";
			}
			case ConsoleColors::WHITE:
			{
				return  ESCSEQ + "[37m";
			}
			case ConsoleColors::BOLDBLACK:
			{
				return ESCSEQ + "[1;30m";
			}
			case ConsoleColors::BOLDRED:
			{
				return ESCSEQ + "[1m;31m";
			}
			case ConsoleColors::BOLDGREEN:
			{
				return ESCSEQ + "[1;32m";
			}
			case ConsoleColors::BOLDYELLOW:
			{
				return ESCSEQ + "[1;33m";
			}
			case ConsoleColors::BOLDBLUE:
			{
				return ESCSEQ + "[1;34m";
			}
			case ConsoleColors::BOLDMAGENTA:
			{
				return ESCSEQ + "[1;35m";
			}
			case ConsoleColors::BOLDCYAN:
			{
				return ESCSEQ + "[1;36m";
			}
			case ConsoleColors::BOLDWHITE:
			{
				return ESCSEQ + "[1;37m";
			}
			case ConsoleColors::UNDERLINEDWHITE:
			{
				return ESCSEQ + "[4;37m";
			}
			case ConsoleColors::UNDERLINEDCYAN:
			{
				return ESCSEQ + "[4;36m";
			}

			case ConsoleColors::RESET:
			default:
			{
				return ESCSEQ + "[0m";
			}
		}
	}

	/**
	 * @brief Formatea para archivo o consola un registro de log y lo devuelve en string
	 * @param logEvent El registro de log
	 * @param isConsoleLog Si es un log para consola (para imprimirlo con su color correspondiente) o para archivo
	 * @return El registro formateado y completo para su correcta visualizaci�n
	*/
	string getLogString(LogEventType logEvent, bool isConsoleLog) {
		//FECHA - NIVEL (ORIGEN) : MENSAJE
		string output = logEvent.fecha + " - ";;
		if (isConsoleLog)
		{

			switch (logEvent.nivel)
			{
				case LogLevels::DEBUG:
					output += getColor(ConsoleColors::GREEN);
					break;
				case LogLevels::INFO:
					output += getColor(ConsoleColors::CYAN);
					break;
				case LogLevels::WARN:
					output += getColor(ConsoleColors::YELLOW);
					break;
				case LogLevels::ERROR:
				case LogLevels::FATAL:
					output += getColor(ConsoleColors::RED);
					break;
			}
			output += getLogLevel(logEvent.nivel) + getColor(ConsoleColors::RESET);
		}
		else
		{
			output += getLogLevel(logEvent.nivel);
		}
		output += " (" + logEvent.origen + ") : " + logEvent.mensaje;

		return output;
	}

	/**
	 * @brief Imprime a consola o archivo un registro de logueo
	 * @param theEvent El registro de log
	*/
	void _logEvent(LogEventType theEvent) {
		if (LOG_TCONSOLE_ENABLED)
		{
			cout << getLogString(theEvent, true) << endl;
		}

		if (LOG_TOFILE_ENABLED)
		{
			/*
			* Lo hago as� para que los logs sean un archivo plano legible
			* */
			string rutaArchivo = PATH_LOGS_FOLDER + PATH_LOG_FILE;
			ofstream file;
			//seteo el output en el file stream y hago append al final con cada log
			file.open(rutaArchivo, std::ios::app | std::ios::out);
			file << getLogString(theEvent, false) << endl;
			file.close();
			/*
				FILE* logsFile = fopen(rutaArchivo.c_str(), MODOS_APERTURA.escrituraAlFinal);
				fwrite(&theEvent, sizeof(logEventType), 1, logsFile);
				fclose(logsFile);
			*/
		}
	}

	/**
	 * @brief Loguea a consola/archivo los logs de la secuencia de inicio (cuando todav�a no se hab�a configurado ni verificado la carpeta y dem�s configuraciones)
	 * @param theLogs El array de logs
	 * @param logLen El largo del array de logs
	*/
	void logInitEvents(LogEventType theLogs[], int logLen) {
		if (LOG_TCONSOLE_ENABLED)
		{
			for (int i = 0; i <= logLen; i++)
			{
				cout << getLogString(theLogs[i], true) << endl;
			}
		}

		if (LOG_TOFILE_ENABLED)
		{
			string rutaArchivo = PATH_LOGS_FOLDER + PATH_LOG_FILE;

			/*
			* Lo hago as� para que los logs sean un archivo plano legible
			* */
			//seteo el output en el file stream y hago append al final con cada log
			ofstream file;
			file.open(rutaArchivo, std::ios::app | std::ios::out);
			for (int i = 0; i <= logLen; i++)
			{
				file << getLogString(theLogs[i], false) << endl;
			}

			file.close();
			/*
				FILE* logsFile = fopen(rutaArchivo.c_str(), MODOS_APERTURA.escribirCrearBinario);
				fwrite(theLogs, sizeof(logEventType), logLen + 1, logsFile);
				fclose(logsFile);
			*/
		}
	}

	/**
	 * @brief Loguea un evento de tipo DEBUG
	 * @param mensaje El mensaje a loguear
	 * @param origen El origen del mensaje
	*/
	void logDebug(string mensaje, string origen) {
		LogEventType evento;
		evento.fecha = getCurrentDateTime(TIPOS_FECHA.ddMMyyyyHHmmssSlayed);
		evento.nivel = LogLevels::DEBUG;
		evento.origen = origen;
		evento.mensaje = mensaje;
		_logEvent(evento);
	}

	/**
	 * @brief Loguea un evento de tipo INFO
	 * @param mensaje El mensaje a loguear
	 * @param origen El origen del mensaje
	*/
	void logInfo(string mensaje, string origen) {
		LogEventType evento;
		evento.fecha = getCurrentDateTime(TIPOS_FECHA.ddMMyyyyHHmmssSlayed);
		evento.nivel = LogLevels::INFO;
		evento.origen = origen;
		evento.mensaje = mensaje;
		_logEvent(evento);
	}

	/**
	 * @brief Loguea un evento de tipo WARNING
	 * @param mensaje El mensaje a loguear
	 * @param origen El origen del mensaje
	*/
	void logWarn(string mensaje, string origen) {
		LogEventType evento;
		evento.fecha = getCurrentDateTime(TIPOS_FECHA.ddMMyyyyHHmmssSlayed);
		evento.nivel = LogLevels::WARN;
		evento.origen = origen;
		evento.mensaje = mensaje;
		_logEvent(evento);
	}

	/**
	 * @brief Loguea un evento de tipo ERROR
	 * @param mensaje El mensaje a loguear
	 * @param origen El origen del mensaje
	*/
	void logError(string mensaje, string origen) {
		LogEventType evento;
		evento.fecha = getCurrentDateTime(TIPOS_FECHA.ddMMyyyyHHmmssSlayed);
		evento.nivel = LogLevels::ERROR;
		evento.origen = origen;
		evento.mensaje = mensaje;
		_logEvent(evento);
	}

	/**
	 * @brief Loguea un evento de tipo FATAL
	 * @param mensaje El mensaje a loguear
	 * @param origen El origen del mensaje
	*/
	void logFatal(string mensaje, string origen) {
		LogEventType evento;
		evento.fecha = getCurrentDateTime(TIPOS_FECHA.ddMMyyyyHHmmssSlayed);
		evento.nivel = LogLevels::FATAL;
		evento.origen = origen;
		evento.mensaje = mensaje;
		_logEvent(evento);
	}
}
#endif