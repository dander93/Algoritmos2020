#pragma once
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
	bool LOG_TCONSOLE_ENABLED = true;
	bool LOG_TOFILE_ENABLED = true;

	string PATH_LOGS_FOLDER = ".\\LOGS\\";
	string PATH_LOG_FILE = "log" + getCurrentDateTime(TIPOS_FECHA.ddMMyyyy) + ".log";

	enum struct LogLevels {
		DEBUG,
		INFO,
		WARN,
		ERROR,
		FATAL
	};

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

	string getColor(ConsoleColors color) {
		switch (color)
		{
			case ConsoleColors::CYAN: return "\033[36m";
			case ConsoleColors::BLACK: return  "\033[30m";
			case ConsoleColors::RED: return  "\033[31m";
			case ConsoleColors::GREEN: return "\033[32m";
			case ConsoleColors::YELLOW: return "\033[33m";
			case ConsoleColors::BLUE: return "\033[34m";
			case ConsoleColors::MAGENTA: return "\033[35m";
			case ConsoleColors::WHITE: return  "\033[37m";
			case ConsoleColors::BOLDBLACK: return "\033[1m\033[30m";
			case ConsoleColors::BOLDRED: return "\033[1m\033[31m";
			case ConsoleColors::BOLDGREEN: return "\033[1m\033[32m";
			case ConsoleColors::BOLDYELLOW: return "\033[1m\033[33m";
			case ConsoleColors::BOLDBLUE: return "\033[1m\033[34m";
			case ConsoleColors::BOLDMAGENTA: return "\033[1m\033[35m";
			case ConsoleColors::BOLDCYAN: return "\033[1m\033[36m";
			case ConsoleColors::BOLDWHITE: return "\033[1m\033[37m";

			case ConsoleColors::RESET:
			default: return "\033[0m";
		}
	}

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

	void _logEvent(LogEventType theEvent) {
		if (LOG_TCONSOLE_ENABLED)
		{
			cout << getLogString(theEvent, true) << endl;
		}

		if (LOG_TOFILE_ENABLED)
		{
			/*
			* Lo hago así para que los logs sean un archivo plano legible
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
			* Lo hago así para que los logs sean un archivo plano legible
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

	void logDebug(string mensaje, string origen) {
		LogEventType evento;
		evento.fecha = getCurrentDateTime(TIPOS_FECHA.ddMMyyyyHHmmssSlayed);
		evento.nivel = LogLevels::DEBUG;
		evento.origen = origen;
		evento.mensaje = mensaje;
		_logEvent(evento);
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

	void logFatal(string mensaje, string origen) {
		LogEventType evento;
		evento.fecha = getCurrentDateTime(TIPOS_FECHA.ddMMyyyyHHmmssSlayed);
		evento.nivel = LogLevels::FATAL;
		evento.origen = origen;
		evento.mensaje = mensaje;
		_logEvent(evento);
	}
}