#pragma once
#include "comun.h"
#include <fstream>

using namespace comunesNamespace;
using namespace std;

namespace loggerNamespace
{
	string getLogString(logEventType logEvent) {
		//FECHA - NIVEL (origen) : mensaje
		return logEvent.fecha + " - " + logEvent.nivel + " (" + logEvent.origen + ") : " + logEvent.mensaje;
	}

	void _logEvent(logEventType theEvent) {
		if (LOG_TOCONSOLE)
		{
			cout << getLogString(theEvent) << endl;
		}

		if (LOG_TOFILE)
		{
			/*
			* Lo hago así para que los logs sean un archivo plano legible
			* */
			string rutaArchivo = PATH_LOGS_FOLDER + PATH_LOG_FILE;
			ofstream out(rutaArchivo, std::ios::ate | std::ios::in);
			//seteo el output stream en el archivo y hago con el ate y el in que se setee el cursos al final del archivo(con el ate) y que no se trunque(con el in)
			out << getLogString(theEvent) << endl;
			out.close();
			/*
				FILE* logsFile = fopen(rutaArchivo.c_str(), MODOS_APERTURA.escrituraAlFinal);
				fwrite(&theEvent, sizeof(logEventType), 1, logsFile);
				fclose(logsFile);
			*/
		}
	}

	void logInitEvents(logEventType theLogs[], int logLen) {
		if (LOG_TOCONSOLE)
		{
			for (int i = 0; i <= logLen; i++)
			{
				cout << getLogString(theLogs[i]) << endl;
			}
		}

		if (LOG_TOFILE)
		{
			/*
			* Lo hago así para que los logs sean un archivo plano legible
			* */
			string rutaArchivo = PATH_LOGS_FOLDER + PATH_LOG_FILE;
			//seteo el output stream en el archivo y hago con el ate y el in que se setee el cursos al final del archivo(con el ate) y que no se trunque(con el in)
			ofstream out(rutaArchivo, std::ios::ate | std::ios::in);

			for (int i = 0; i <= logLen; i++)
			{
				out << getLogString(theLogs[i]) << endl;
			}

			out.close();
			/*
				FILE* logsFile = fopen(rutaArchivo.c_str(), MODOS_APERTURA.escribirCrearBinario);
				fwrite(theLogs, sizeof(logEventType), logLen + 1, logsFile);
				fclose(logsFile);
			*/
		}
	}

	void logInfo(string mensaje, string origen) {
		logEventType evento;
		evento.fecha = getCurrentDateTime(TIPOS_FECHA.ddMMyyyyHHmmssSlayed);
		strcpy(evento.nivel, "INFO");
		evento.origen = origen;
		evento.mensaje = mensaje;
		_logEvent(evento);
	}

	void logError(string mensaje, string origen) {
		logEventType evento;
		evento.fecha = getCurrentDateTime(TIPOS_FECHA.ddMMyyyyHHmmssSlayed);
		strcpy(evento.nivel, "ERROR");
		evento.origen = origen;
		evento.mensaje = mensaje;
		_logEvent(evento);
	}

	void logWarn(string mensaje, string origen) {
		logEventType evento;
		evento.fecha = getCurrentDateTime(TIPOS_FECHA.ddMMyyyyHHmmssSlayed);
		strcpy(evento.nivel, "WARN");
		evento.origen = origen;
		evento.mensaje = mensaje;
		_logEvent(evento);
	}

}