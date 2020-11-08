#pragma once
#include "Headers/Comun.h"

using namespace comunesNamespace;

namespace log
{

	struct log {
		string nivel;
		string origen;
		string mensaje;
	};

	void logEvent(log log) {

		string rutaArchivo = PATH_LOGS_FOLDER + PATH_LOG_FILE;
		FILE* logs = fopen(rutaArchivo.c_str(), MODOS_APERTURA.lecturaYEscrituraBinario/*rb+*/);

		//loguea a consola
		cout << log.mensaje << endl;
	}
}