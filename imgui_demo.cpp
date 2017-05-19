// dear imgui, v1.50 WIP
// (demo code)

// Message to the person tempted to delete this file when integrating ImGui into their code base:
// Do NOT remove this file from your project! It is useful reference code that you and other users will want to refer to.
// Everything in this file will be stripped out by the linker if you don't call ImGui::ShowTestWindow().
// During development, you can call ImGui::ShowTestWindow() in your code to learn about various features of ImGui.
// Removing this file from your project is hindering your access to documentation, likely leading you to poorer usage of the library.

#if defined(_MSC_VER) && !defined(_CRT_SECURE_NO_WARNINGS)
#define _CRT_SECURE_NO_WARNINGS
#endif

#include "imgui.h"
#include <ctype.h>          // toupper, isprint
#include <math.h>           // sqrtf, powf, cosf, sinf, floorf, ceilf
#include <stdio.h>          // vsnprintf, sscanf, printf
#include <stdlib.h>         // NULL, malloc, free, qsort, atoi
#if defined(_MSC_VER) && _MSC_VER <= 1500 // MSVC 2008 or earlier
#include <stddef.h>         // intptr_t
#else
#include <stdint.h>         // intptr_t
#endif

#ifdef _MSC_VER
#pragma warning (disable: 4996) // 'This function or variable may be unsafe': strcpy, strdup, sprintf, vsnprintf, sscanf, fopen
#define snprintf _snprintf
#endif
#ifdef __clang__
#pragma clang diagnostic ignored "-Wold-style-cast"             // warning : use of old-style cast                              // yes, they are more terse.
#pragma clang diagnostic ignored "-Wdeprecated-declarations"    // warning : 'xx' is deprecated: The POSIX name for this item.. // for strdup used in demo code (so user can copy & paste the code)
#pragma clang diagnostic ignored "-Wint-to-void-pointer-cast"   // warning : cast to 'void *' from smaller integer type 'int'
#pragma clang diagnostic ignored "-Wformat-security"            // warning : warning: format string is not a string literal
#pragma clang diagnostic ignored "-Wexit-time-destructors"      // warning : declaration requires an exit-time destructor       // exit-time destruction order is undefined. if MemFree() leads to users code that has been disabled before exit it might cause problems. ImGui coding style welcomes static/globals.
#if __has_warning("-Wreserved-id-macro")
#pragma clang diagnostic ignored "-Wreserved-id-macro"          // warning : macro name is a reserved identifier                //
#endif
#elif defined(__GNUC__)
#pragma GCC diagnostic ignored "-Wint-to-pointer-cast"          // warning: cast to pointer from integer of different size
#pragma GCC diagnostic ignored "-Wformat-security"              // warning : format string is not a string literal (potentially insecure)
#pragma GCC diagnostic ignored "-Wdouble-promotion"             // warning: implicit conversion from 'float' to 'double' when passing argument to function
#pragma GCC diagnostic ignored "-Wconversion"                   // warning: conversion to 'xxxx' from 'xxxx' may alter its value
#if (__GNUC__ >= 6)
#pragma GCC diagnostic ignored "-Wmisleading-indentation"       // warning: this 'if' clause does not guard this statement      // GCC 6.0+ only. See #883 on github.
#endif
#endif

// Play it nice with Windows users. Notepad in 2015 still doesn't display text data with Unix-style \n.
#ifdef _WIN32
#define IM_NEWLINE "\r\n"
#else
#define IM_NEWLINE "\n"
#endif

#define IM_ARRAYSIZE(_ARR)  ((int)(sizeof(_ARR)/sizeof(*_ARR)))
#define IM_MAX(_A,_B)       (((_A) >= (_B)) ? (_A) : (_B))

//-----------------------------------------------------------------------------
// DEMO CODE
//-----------------------------------------------------------------------------

#ifndef IMGUI_DISABLE_TEST_WINDOWS

//EJEMPLO
static int generarTiempoLLegada(float P);
static int seleccionarMenor(int n1, int n2, int n3);
static int generarTipo();
static int menor = 0, reloj = 0, delta = 0, deltaAnt = 0, TLL = 0, TSLL = 0, maximo = 100, tipo = 0, TClientes = 0, Tllamadas = 0, cola = 0, llamadasP = 0, llamadasCont = 0, TCELL = 0, CELL = 0;
static bool LLA = false, CLA = false;
static float P = 0.0f;
//EJEMPLO

void ImGui::Simulacion(bool* p_open, int tiempoMax, int nFilas, int nServicio) {
	static int i = 0;
	static int estaciones[10][2] = { {0,0} ,{ 0,0 } ,{ 0,0 } ,{ 0,0 } ,{ 0,0 } ,{ 0,0 } ,{ 0,0 } ,{ 0,0 } ,{ 0,0 } ,{ 0,0 } };
	static int TS[10][2] = { { 0,0 } ,{ 0,0 } ,{ 0,0 } ,{ 0,0 } ,{ 0,0 } ,{ 0,0 } ,{ 0,0 } ,{ 0,0 } ,{ 0,0 } ,{ 0,0 } };
	ImGui::SetNextWindowSize(ImVec2(550, 300));
	if (!ImGui::Begin("Simulacion", p_open))
	{
		// Early out if the window is collapsed, as an optimization.
		ImGui::End();
		return;
	}

	TLL = generarTiempoLLegada(P);


	while (reloj<maximo)
	{
		menor = TLL;
		for (i = 0; i < nServicio; i++) {
			delta = seleccionarMenor(TS[i][0],TS[i][1],menor);//seleccionar el menor de 3 numeros
			menor = delta;

		}
		reloj = reloj + delta;
		//Pendiente formula tiempo de espera total

		//Revisar el tiempo de llegada
		TLL = TLL - delta;
		if (TLL = 0) {
			tipo = generarTipo();
			for (i = 0; i < nServicio; i++) {
				if (tipo = 0) {
					TClientes++;
					cola++;
					TLL = generarTiempoLLegada(P);//obtener un tiempo de llegada
				}
				else {
					Tllamadas++;
					if (estaciones[i][1] = 0) {
						TSLL = generarTiempoLLamada(1.0f);
						estaciones[i][1] = 1;
						TS[i][1] = generarTiempoLLamada(1);
						llamadasCont++;
						if (estaciones[i][0] = 1) {
							TS[i][0] = TS[i][0] + TS[i][1];
							TCELL = TCELL + TS[i][1];
							CELL++;
						}
					}
					else
					{
						llamadasP++;
					}
					
				}
			}
		}

		//Revisar el tiempo de servicio de llamada
		for (i = 0; i < nServicio; i++) {
			TS[i][1] = TS[i][1] - delta;
			if (TS[i][1] <= 0) {
				estaciones[i][1] = 0;
			}
		}

		//Revisar el tiempo de servicio del cliente
		//Pendiente

		//Impresion de estado
		//Pendiente
	}

	//Calculo de promedios
	//Impresiones
	ImGui::End();
}


static int generarTiempoLLegada(float P) {
	static int tiempo = 0;
	tiempo = 1;
	return tiempo;
}
static int generarTiempoLLamada(float A) {
	static int tiempo = 0;
	tiempo = 1;
	return tiempo;
}
static int seleccionarMenor(int n1, int n2, int n3) {
	static int mayor;

	mayor = 1;
	return mayor;
}
static int generarTipo() {
	static int tipo;
	tipo = 0;
	return tipo;
}

#else

void ImGui::ShowTestWindow(bool*) {}
void ImGui::ShowUserGuide() {}
void ImGui::ShowStyleEditor(ImGuiStyle*) {}

#endif
