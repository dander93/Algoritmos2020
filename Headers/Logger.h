#pragma once
#include <fstream>
#include "Comun.h"
#include "TimeHelper.h"

using namespace std;
using namespace TimeHelper;

namespace LoggerHelper
{
	const bool LOG_TCONSOLE_ENABLED = true;
	const bool LOG_TOFILE_ENABLED = true;

	const string PATH_LOGS_FOLDER = ".\\LOGS\\";
	const string PATH_LOG_FILE = "log" + getCurrentDateTime(TIPOS_FECHA.ddMMyyyy) + ".log";

	enum struct LogLevels {
		DEBUG,
		INFO,
		WARN,
		ERROR,
		FATAL
	};

	enum struct CustomConsoleColor {
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
		BOLDWHITE
	};

	//estructura de logs
	struct LogEventType {
		string fecha;
		LogLevels nivel;
		string origen;
		string mensaje;
	};

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

	string getColor(CustomConsoleColor color) {
		switch (color)
		{
			case CustomConsoleColor::CYAN: return "\033[36m";
			case CustomConsoleColor::BLACK: return  "\033[30m";
			case CustomConsoleColor::RED: return  "\033[31m";
			case CustomConsoleColor::GREEN: return "\033[32m";
			case CustomConsoleColor::YELLOW: return "\033[33m";
			case CustomConsoleColor::BLUE: return "\033[34m";
			case CustomConsoleColor::MAGENTA: return "\033[35m";
			case CustomConsoleColor::WHITE: return  "\033[37m";
			case CustomConsoleColor::BOLDBLACK: return "\033[1m\033[30m";
			case CustomConsoleColor::BOLDRED: return "\033[1m\033[31m";
			case CustomConsoleColor::BOLDGREEN: return "\033[1m\033[32m";
			case CustomConsoleColor::BOLDYELLOW: return "\033[1m\033[33m";
			case CustomConsoleColor::BOLDBLUE: return "\033[1m\033[34m";
			case CustomConsoleColor::BOLDMAGENTA: return "\033[1m\033[35m";
			case CustomConsoleColor::BOLDCYAN: return "\033[1m\033[36m";
			case CustomConsoleColor::BOLDWHITE: return "\033[1m\033[37m";

			case CustomConsoleColor::RESET:
			default: return "\033[0m";
		}
	}


	string getLogString(LogEventType logEvent) {
		//FECHA - NIVEL (ORIGEN) : MENSAJE
		return logEvent.fecha + " - " + getLogLevel(logEvent.nivel) + " (" + logEvent.origen + ") : " + logEvent.mensaje;
	}

	void _logEvent(LogEventType theEvent) {
		if (LOG_TCONSOLE_ENABLED)
		{
			cout << getLogString(theEvent) << endl;
		}

		if (LOG_TOFILE_ENABLED)
		{
			/*
			* Lo hago así para que los logs sean un archivo plano legible
			* */
			string rutaArchivo = PATH_LOGS_FOLDER + PATH_LOG_FILE;
			ofstream file;
			file.open(rutaArchivo, std::ios::app | std::ios::out);
			//ofstream out();
			//seteo el output stream en el archivo y hago con el ate y el in que se setee el cursos al final del archivo(con el ate) y que no se trunque(con el in)
			file << getLogString(theEvent) << endl;
			file.close();
			/*
				FILE* logsFile = fopen(rutaArchivo.c_str(), MODOS_APERTURA.escrituraAlFinal);
				fwrite(&theEvent, sizeof(logEventType), 1, logsFile);
				fclose(logsFile);
			*/
		}
	}

	void logInitEvents(LogEventType theLogs[], int logLen) {
		if (LOG_TCONSOLE_ENABLED)
		{
			for (int i = 0; i <= logLen; i++)
			{
				cout << getLogString(theLogs[i]) << endl;
			}
		}

		if (LOG_TOFILE_ENABLED)
		{
			string rutaArchivo = PATH_LOGS_FOLDER + PATH_LOG_FILE;

			/*
			* Lo hago así para que los logs sean un archivo plano legible
			* */
			//seteo el output stream en el archivo y hago con el ate y el in que se setee el cursos al final del archivo(con el ate) y que no se trunque(con el in)
			//ofstream out(rutaArchivo, std::ios::ate | std::ios::out);
			ofstream file;
			file.open(rutaArchivo, std::ios::app | std::ios::out);
			for (int i = 0; i <= logLen; i++)
			{
				file << getLogString(theLogs[i]) << endl;
			}

			file.close();
			/*
				FILE* logsFile = fopen(rutaArchivo.c_str(), MODOS_APERTURA.escribirCrearBinario);
				fwrite(theLogs, sizeof(logEventType), logLen + 1, logsFile);
				fclose(logsFile);
			*/
		}
	}

	void logInfo(string mensaje, string origen) {
		LogEventType evento;
		evento.fecha = getCurrentDateTime(TIPOS_FECHA.ddMMyyyyHHmmssSlayed);
		evento.nivel = LogLevels::INFO;
		evento.origen = origen;
		evento.mensaje = mensaje;
		_logEvent(evento);
	}

	void logWarn(string mensaje, string origen) {
		LogEventType evento;
		evento.fecha = getCurrentDateTime(TIPOS_FECHA.ddMMyyyyHHmmssSlayed);
		evento.nivel = LogLevels::WARN;
		evento.origen = origen;
		evento.mensaje = mensaje;
		_logEvent(evento);
	}

	void logError(string mensaje, string origen) {
		LogEventType evento;
		evento.fecha = getCurrentDateTime(TIPOS_FECHA.ddMMyyyyHHmmssSlayed);
		evento.nivel = LogLevels::ERROR;
		evento.origen = origen;
		evento.mensaje = mensaje;
		_logEvent(evento);
	}
}