#pragma once
#include "comun.h"

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
			cout << theEvent.mensaje << endl;
		}

		if (LOG_TOFILE)
		{
			string rutaArchivo = PATH_LOGS_FOLDER + PATH_LOG_FILE;

			FILE* logsFile = fopen(rutaArchivo.c_str(), MODOS_APERTURA.escrituraAlFinal);
			fwrite(&theEvent, sizeof(logEventType), 1, logsFile);
			fclose(logsFile);
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
			string rutaArchivo = PATH_LOGS_FOLDER + PATH_LOG_FILE;
			FILE* logsFile = fopen(rutaArchivo.c_str(), MODOS_APERTURA.escribirCrearBinario);
			fwrite(theLogs, sizeof(logEventType), logLen + 1, logsFile);
			fclose(logsFile);
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