#pragma once
#ifndef _TIMEHELPER_
#define _TIMEHELPER_

#include <string>
#include <ctime>

using namespace std;

namespace TimeHelper
{

	/**
	 * @brief Estructura para imprimir los tipos de fecha
	*/
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
	} TIPOS_FECHA;

	/**
	 * @brief Obtiene la fecha y/o hora actuales
	 * @param Formato El formato de la fecha esperada(de la estructura estática TIPOS_FECHA)
	 * @return El string con el horario/fecha solicitados
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

#endif