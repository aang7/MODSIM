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
#include <windows.h>
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
static int generarTiempoLLamada(float A);
static int seleccionarMenor(int n1, int n2, int n3);
static int generarTiempoServicio(float A);
static int generarTipo();
static int menor = 0,TET=0,TO=0,atendidos, reloj = 0, delta = 0, deltaAnt = 0, TSLL = 0, tipo = 0, TClientes = 0, Tllamadas = 0, cola = 0, llamadasP = 0, llamadasCont = 0, TCELL = 0, CELL = 0,maximo = 0;
static bool LLA = false, CLA = false;
static float P = 0.0f;
//EJEMPLO

void ImGui::Simulacion(bool* p_open, int tiempoMax, int nFilas, int nServicio) {
	maximo = tiempoMax;
	static int i = 0;
	static bool atendido = false, libre = false;
	static int TLL = generarTiempoLLegada(P);
	static int estaciones[10][2] = { {0,0} ,{ 0,0 } ,{ 0,0 } ,{ 0,0 } ,{ 0,0 } ,{ 0,0 } ,{ 0,0 } ,{ 0,0 } ,{ 0,0 } ,{ 0,0 } };
	static int TS[10][2] = { { 0,0 } ,{ 0,0 } ,{ 0,0 } ,{ 0,0 } ,{ 0,0 } ,{ 0,0 } ,{ 0,0 } ,{ 0,0 } ,{ 0,0 } ,{ 0,0 } };
	ImGui::SetNextWindowSize(ImVec2(900, 600));
	if (!ImGui::Begin("Simulacion", p_open))
	{
		// Early out if the window is collapsed, as an optimization.
		ImGui::End();
		return;
	}

	//DISEÑO GRAFICO
	//Impresion de estado
	Tllamadas = llamadasCont + llamadasP;
	ImGui::Text("Reloj: %i", reloj);
	ImGui::ProgressBar((float)reloj / maximo);
	ImGui::Separator();

	ImGui::Text("Clientes que han llegado al sitema: %i \n", TClientes);
	ImGui::Text("Llamadas que han llegado al sistema: %i \n", Tllamadas);
	ImGui::Separator();

	ImGui::Text("Clientes atendidos: %i \n", atendidos);
	ImGui::Text("Llamadas Perdidas: %i \n", llamadasP);
	ImGui::Text("Llamadas Contestadas: %i \n", llamadasCont);
	ImGui::Separator();

	//COLA
	ImGui::Text("Cola: %i \n", cola); ImGui::SameLine();
	static int cont = 0;
	static int espacio = 10;
	static int lado = 10;
	static float wrap_width = 50.0f;
	ImVec2 pos = ImGui::GetCursorScreenPos();
	for (cont = 0; cont < cola; cont++) {
		ImGui::GetWindowDrawList()->AddRectFilled(ImVec2(pos.x + wrap_width + espacio, pos.y), ImVec2(pos.x + wrap_width + lado + espacio, pos.y + lado), IM_COL32(255, 0, 255, 255));
		espacio = espacio + 15;
	}
	ImGui::Spacing();
	espacio = 20;
	ImGui::Separator();
	//FIN DISEÑO COLA	
	static int lado2 = 10;
	ImVec2 pos2 = ImGui::GetCursorScreenPos();
	for (i = 0; i < nServicio; i++) {
		ImGui::Text("Estacion de servicio: %i", i + 1);
		if (estaciones[i][0]==0) {
			ImGui::GetWindowDrawList()->AddRect(ImVec2(pos2.x , pos2.y  + espacio), ImVec2(pos2.x + 30.0f, pos.y + 50.0f + espacio), IM_COL32(255, 255, 0, 255));
		}
		else {
			ImGui::GetWindowDrawList()->AddRectFilled(ImVec2(pos2.x  , pos2.y  + espacio ), ImVec2(pos2.x + 30.f , pos.y + 50.0f + espacio), IM_COL32(255, 255, 0, 255));
		}
		espacio = espacio + 53;
		ImGui::Spacing();ImGui::Spacing();ImGui::Spacing(); ImGui::Spacing(); ImGui::Spacing(); ImGui::Spacing(); ImGui::Spacing(); ImGui::Spacing(); ImGui::Spacing();
	}
	espacio = 0;
	delta = generarTiempoLLegada(1);
	if (reloj<tiempoMax)
	{	
		Sleep(1000);
		
		menor = TLL;
		reloj = reloj + delta;
		TET = TET + cola * delta;

		for (i = 0; i < nServicio; i++) {
			TS[i][1] = TS[i][1] - delta;
			if (TS[i][1] <= 0) {
				estaciones[i][1] = 0;


			}
		}

		//Revisar el tiempo de llegada
		TLL = TLL - delta;
		i = 0;
		
		if (TLL == 0) 
		{
			tipo = generarTipo();
			while ((i < nServicio)&&(atendido == false)) 
			{
				printf("checar %i\n",i);
				if (tipo == 0) {
					TClientes++;
					cola++;
					atendido = true;
					
					
				}
				else {
					for (i = 0; i < nServicio; i++) {
						if (estaciones[i][0] == 0 ) {
							libre = true;
						}
					}
					if (libre == true) {
						if (estaciones[i][1] == 0 && estaciones[i][0] == 0)
						{

							estaciones[i][1] = 1;
							TS[i][1] = generarTiempoLLamada(1);

							llamadasCont++;
							atendido = true;
						}
					}
					else {
						if (estaciones[i][1] == 0)
						{

							estaciones[i][1] = 1;
							TS[i][1] = generarTiempoLLamada(1);

							llamadasCont++;
							atendido = true;


							if (estaciones[i][0] == 1) {
								TS[i][0] = TS[i][0] + TS[i][1];
								TCELL = TCELL + TS[i][1];
								CELL++;
							}

						}
					}
					
				}
				i++;
			}
			if (atendido == false) {
				llamadasP++;
				
			}
			TLL = generarTiempoLLegada(P);//obtener un tiempo de llegada
			
		}

		
		//Revisar el tiempo de servicio de llamada
		for (i = 0; i < nServicio; i++) {
			TS[i][1] = TS[i][1] - delta;
			if (TS[i][1] <= 0) {
				estaciones[i][1] = 0;
				
				
			}
		}
		
		//Revisar el tiempo de servicio del cliente
		for (i = 0; i < nServicio; i++) {
			TS[i][0] = TS[i][0] - delta;
			if (TS[i][0]<=0)
			{
				if (TS[i][0] == 0) {
					estaciones[i][0] = 0;
					atendidos++;
					
					
				}
				else {
					TO = TO - TS[i][0];
					TS[i][0] = 0;
				}
				if (cola > 0) {
					estaciones[i][0] = 1;
					cola = cola -1;
					TS[i][0] = generarTiempoServicio(2);
				}
			}

		}

		
		atendido = false;
		
	}
	
	//Calculo de promedios
	//Impresiones
	ImGui::End();
}


static int generarTiempoLLegada(float P) {
	static int tiempo = 0;
	tiempo = 10;
	return tiempo;
}
static int generarTiempoLLamada(float A) {
	static int tiempo = 0;
	tiempo = 20;
	return tiempo;
}
static int generarTiempoServicio(float A) {
	static int tiempo = 0;
	tiempo = 10;
	return tiempo;
}
static int seleccionarMenor(int n1, int n2, int n3) {
	static int mayor;

	mayor = 10;
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
