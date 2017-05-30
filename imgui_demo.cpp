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
#include <string>


#include<iostream>
#include <random>
using namespace std;
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
static int generarTiempoLLegada();
static int generarTiempoLLamada(float A);
static int seleccionarMenor(int n1, int n2, int n3);
static int generarTiempoServicio(float A);
static int randomInteger();
static float getRandomNumber();
static void mostrar();
static int generarTipo();
static int menor = 0,TET=0, TEMay = 0, TEMen = 1000,atendidos, reloj = 0, delta = 0, deltaAnt = 0, TSLL = 0, tipo = 0, TClientes = 0, Tllamadas = 0, cola = 0, llamadasP = 0, llamadasCont = 0, TCELL = 0, CELL = 0,maximo = 0,estServicio=0;
static bool LLA = false, CLA = false;
static float ocio[11]= { 0,0,0,0,0,0,0,0,0,0,0 };
static float P = 0.0f;
//EJEMPLO

void ImGui::Simulacion(bool* p_open, int tiempoMax, int nFilas, int nServicio) {
	maximo = tiempoMax;
	estServicio = nServicio;
	static int i = 0;
	static bool atendido = false, libre = false;
	static int TLL = generarTiempoLLegada();
	static int estaciones[10][2] = { {0,0} ,{ 0,0 } ,{ 0,0 } ,{ 0,0 } ,{ 0,0 } ,{ 0,0 } ,{ 0,0 } ,{ 0,0 } ,{ 0,0 } ,{ 0,0 } };
	static int TS[10][2] = { { 0,0 } ,{ 0,0 } ,{ 0,0 } ,{ 0,0 } ,{ 0,0 } ,{ 0,0 } ,{ 0,0 } ,{ 0,0 } ,{ 0,0 } ,{ 0,0 } };
	static string estado="";
	libre = false;
	ImGui::SetNextWindowSize(ImVec2(600, 550));
	if (!ImGui::Begin("Simulacion", p_open))
	{
		// Early out if the window is collapsed, as an optimization.
		ImGui::End();
		return;
	}

	
	//delta = generarTiempoLLegada();
	if (reloj<tiempoMax)
	{	
		estado = "";
		Sleep(4000);
		
		menor = TLL;
		delta = TLL;
		for (i = 0; i < nServicio; i++) {
			
			delta = seleccionarMenor(menor, TS[i][0], TS[i][1]);//seleccionar el menor de 3 numeros
			//delta = seleccionarMenor(100, 100, menor);
			menor = delta;

		}
		reloj = reloj + delta;
		TET = TET + cola * delta;

		//Revisar el tiempo de llegada
		TLL = TLL - delta;
		i = 0;
		
		if (TLL <= 0) 
		{
			tipo = generarTipo();
			while ((i < nServicio)&&(atendido == false)) 
			{
				
				if (tipo == 0) {
					TClientes++;
					cola++;
					atendido = true;
					estado = estado + "LLego cliente \n";
					
				}
				else {
					for (int j = 0; j < nServicio; j++) {
						if (estaciones[j][0] == 0 ) {
							libre = true;
							printf("%i,", estaciones[j][0]);
							printf("%i \n", estaciones[j][1]);
						}
						
					}
					if (libre == true) {
						if (estaciones[i][1] == 0 && estaciones[i][0] == 0)
						{
							estado = estado + "Entro llamada \n";
							estado = estado + "Se atendio la llamada en la estacion: " + to_string(i + 1) + " \n";
							estaciones[i][1] = 1;
							TS[i][1] = generarTiempoLLamada(1) + delta;

							llamadasCont++;
							atendido = true;
						}
					}else {
						if (estaciones[i][1] == 0)
						{

							estaciones[i][1] = 1;
							TS[i][1] = generarTiempoLLamada(1) + delta;
							estado = estado + "Entro llamada \n";
							estado = estado + "Se atendio la llamada en la estacion: " + to_string(i + 1) + " y se pone en espera al cliente\n";
							llamadasCont++;
							atendido = true;


							if (estaciones[i][0] == 1) {
								TS[i][0] = TS[i][0] + TS[i][1];
								TCELL = TCELL + TS[i][1];
								CELL++;
							}

						}
					}
					libre = false;
				}
				i++;
			}
			if (atendido == false) {
				llamadasP++;
				estado = estado + "Entro llamada \n";
				estado = estado + "LLamada perdida \n";
				
			}
			TLL = generarTiempoLLegada();//obtener un tiempo de llegada
			
		}

		
		//Revisar el tiempo de servicio de llamada
		for (i = 0; i < nServicio; i++) {
			TS[i][1] = TS[i][1] - delta;
			if (TS[i][1] <= 0) {
				if (estaciones[i][1] == 1) {
					
					estado = estado + "Termino de atender llamada en la estacion: " + to_string(i + 1) + " \n";
				}
				estaciones[i][1] = 0;
				
			}
		}
		
		//Revisar el tiempo de servicio del cliente
		for (i = 0; i < nServicio; i++) {
			TS[i][0] = TS[i][0] - delta;
			if (TS[i][0]<=0)
			{
				if (TS[i][0] == 0 && estaciones[i][1]==0) {
					estaciones[i][0] = 0;
					atendidos++;
					estado = estado + "Termino de atender cliente en la estacion: " + to_string(i+1) + " \n";
					
				}
				else {
					ocio[i+1] = ocio[i+1] - TS[i][0];
					TS[i][0] = 0;
					estaciones[i][0] = 0;
				}
				if (cola > 0) {
					estaciones[i][0] = 1;
					cola = cola -1;
					TS[i][0] = generarTiempoServicio(2);
					estado = estado + "Ingreso cliente a la estacion: " + to_string(i+1) + " \n";
				}
			}
		}

		
		atendido = false;
		
	}
else {
	reloj = maximo;
}
	
	//Calculo de promedios
	//Impresiones
	//DISEÑO GRAFICO
	//Impresion de estado
	Tllamadas = llamadasCont + llamadasP;
	ImGui::Text("Reloj: %i", reloj);
	ImGui::ProgressBar((float)reloj / maximo);
	ImGui::Separator();

	ImGui::Text("Clientes que han llegado al sistema: %i \n", TClientes);
	ImGui::Text("Llamadas que han llegado al sistema: %i \n", Tllamadas);
	ImGui::Separator();

	ImGui::Text("Clientes atendidos: %i \n", TClientes-cola);
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
	espacio = 38;
	ImGui::Separator();
	//FIN DISEÑO COLA	

	//ESTACIONES DE SERVICIO
	static int lado2 = 10;
	ImVec2 pos2 = ImGui::GetCursorScreenPos();
	for (i = 0; i < nServicio; i++) {
		ImGui::Text("Estacion de servicio %i", i + 1);
		if (estaciones[i][1] == 1) {
			if (estaciones[i][0] == 1) {
				ImGui::Text("Cliente en espera (%i min restantes) y en llamada ... %i min restantes", TS[i][0], TS[i][1]);
			}
			else {
				ImGui::Text("En llamada ... %i min restantes", TS[i][1]);
			}
			
			ImGui::GetWindowDrawList()->AddRectFilled(ImVec2(pos2.x, pos2.y + espacio), ImVec2(pos2.x + 30.0f, pos.y + 50.0f + espacio), IM_COL32(255, 255, 0, 255));
		}
		else {
			if (estaciones[i][0] == 0) {
				ImGui::Text("Libre");
				ImGui::GetWindowDrawList()->AddRect(ImVec2(pos2.x, pos2.y + espacio), ImVec2(pos2.x + 30.0f, pos.y + 50.0f + espacio), IM_COL32(0, 255, 0, 255));
			}
			else {
				ImGui::Text("Atendiendo cliente: tiempo de atencion restante %i min",TS[i][0]);
				ImGui::GetWindowDrawList()->AddRectFilled(ImVec2(pos2.x, pos2.y + espacio), ImVec2(pos2.x + 30.f, pos.y + 50.0f + espacio), IM_COL32(0, 255, 0, 255));
			}
		}
		espacio = espacio + 70;
		ImGui::Spacing(); ImGui::Spacing(); ImGui::Spacing(); ImGui::Spacing(); ImGui::Spacing(); ImGui::Spacing(); ImGui::Spacing(); ImGui::Spacing(); ImGui::Spacing();
	}
	espacio = 0;
	ImGui::Separator();
	//

	static bool resultados = false;
	if (!(maximo > reloj)) {
		if (ImGui::Button("Mostrar resultados"))resultados ^= 1;
		
	}
	ImGui::Text("Eventos ocurridos:");
	ImGui::Text(estado.c_str());
	ImGui::Text("Delta: %i", delta);
	
	if (resultados) {
		mostrar();
	}
	
	ImGui::End();
}

static void mostrar() {
	
	ImGui::SetNextWindowSize(ImVec2(600, 400));
	ImGui::Begin("Resultados");
	static int mayor = 0, menor = 0,cAtendidos = 0;
	static float valMay = 0.0f, valMen = 1000.0f;
	static float por = 0.0f, porciento=0.0f;
	if (ImGui::CollapsingHeader("Clientes")) {
		static float comparacion[2] = { 0,0 };
		cAtendidos = TClientes - cola;
		por = (float)cAtendidos/TClientes ;
		porciento = (float)por * 100;
		ImGui::Text("Numero de clientes atendidos: %i",cAtendidos);
		ImGui::Text("Numero de clientes no atendidos: %i", TClientes - cAtendidos);
		ImGui::Text("Porcentaje de atencion: %.2f ", porciento );
		ImGui::ProgressBar(por);
		ImGui::Spacing();
		ImGui::Separator();
		ImGui::Spacing();

		ImGui::Text("Tiempo de espera total: %i min", TET);
		ImGui::Text("Tiempo de espera promedio: %.2f min", (float)TET / TClientes);
		ImGui::Spacing();
		ImGui::Separator();
		ImGui::Spacing();

		ImGui::Text("Clientes que esperaron por llamada: %i", CELL);
		ImGui::Text("Tiempo de espera total de espera por llamada: %.i min", TCELL);
		if (TCELL > 0) {
			ImGui::Text("Promedio de tiempo de espera por llamada: %.2f min", (float)TCELL/CELL);
		}
		ImGui::Spacing();
		ImGui::Spacing();

		comparacion[0] = TClientes;
		comparacion[1] = CELL;
		ImGui::PlotHistogram("   Clientes en total / Clientes que esperaron", comparacion, 2, 0, NULL, 1.0f, TClientes + 1.0f, ImVec2(60, 90));


	}
	if (ImGui::CollapsingHeader("LLamadas")) {
		static float comparacionLL[2] = { 0,0 };
		por = (float)llamadasCont / Tllamadas;
		porciento = (float)por * 100;
		ImGui::Text("Numero de llamadas atendidas: %i", llamadasCont);
		ImGui::Text("Numero de llamadas perdidas: %i", llamadasP);
		ImGui::Text("Porcentaje de atencion: %.2f ", porciento);
		ImGui::ProgressBar(por);
		ImGui::Spacing();
		ImGui::Separator();
		ImGui::Spacing();

		static int llamadasContSC = 0;
		llamadasContSC = llamadasCont - CELL;
		ImGui::Text("LLamadas atendidas cuando habia un cliente: %i ", CELL);
		ImGui::Text("LLamadas atendidas sin clientes: %.i ",llamadasContSC );
		if (llamadasCont > 0) {
			ImGui::Text("Porcentaje de llamadas realizadas cuando hay cliente: %.2f ", (float)CELL / llamadasCont * 100);
			ImGui::ProgressBar((float)CELL / llamadasCont);
		}
		ImGui::Spacing();
		ImGui::Spacing();

		comparacionLL[0] = Tllamadas;
		comparacionLL[1] = CELL;
		ImGui::PlotHistogram("   LLamadas en total / LLamadas con clientes que esperaron", comparacionLL, 2, 0, NULL, 1.0f, Tllamadas, ImVec2(60, 90));


	}
	if (ImGui::CollapsingHeader("Tiempo de ocio"))
	{
		for (int i = 0; i < estServicio; i++) {
			ocio[0] = ocio[0] + ocio[i + 1];
			if (valMay<ocio[i + 1]) {
				valMay = ocio[i + 1];
				mayor = i + 1;
			}
			if (valMen>ocio[i + 1]) {
				valMen = ocio[i + 1];
				menor = i + 1;
			}
			 
		}
		ocio[0] = ocio[0] / estServicio;
		ImGui::Text("La siguiente grafica muestra los tiempos de ocio de las estaciones de servicio ");
		ImGui::Text("la primera columna es el promedio de todas las estaciones:");
		ImGui::Spacing();
		ImGui::PlotHistogram("Tiempo de ocio", ocio, estServicio + 1, 0, NULL, 1.0f, valMay + 10.0f, ImVec2(0, 80));
		ImGui::Spacing();
		ImGui::Separator();
		ImGui::Spacing();
		ImGui::Text("La estacion con mayor tiempo de ocio es la %i con: %.2f min",mayor,valMay);
		ImGui::Text("La estacion con menor tiempo de ocio es la %i con: %.2f min",menor,valMen);
		ImGui::Text("El promedio de tiempo de ocio es: %.2f min", ocio[0]);
		ImGui::Spacing();
		ImGui::Separator();
		ocio[0] = 0;
	}
	
	ImGui::End();
}

static int randomInteger()
{
	mt19937 rng;  // only used once to initialise (seed) engine
	rng.seed(random_device()());
	uniform_int_distribution<mt19937::result_type> dist(1, 30); // distribution in range [MIN, MAX]

	auto random_integer = dist(rng);

	return random_integer;
}
static float getRandomNumber()
{

	long int m = 97711 /* 97711 */;
	int c = 7, a = 7;
	float nrandom = 0.0f, temp = 0.0f;
	float uniforme = 0.0f;

	int random_stop = randomInteger();
	//cout << "rs = " << random_stop << " ";

	for (long int i = 0; i < random_stop; ++i)
	{
		nrandom = ((int)(a*temp + c) % m);
		temp = nrandom;
	}

	uniforme = nrandom / m;

	return uniforme;
}
static int generarTiempoLLegada() {
	static int tiempo = 0;
	double p, suma, y = 0;
	double r;
	int x;

	p = 0.07203;

	x = 0;
	suma = 0;
	r = getRandomNumber();
	//cout << "r = " << r << endl;
	while (suma < r) {
		x++;
		y = (pow((1 - p), x - 1))*p;
		suma += y;
	}
		
	tiempo = x;
	return tiempo;
}
static int generarTiempoLLamada(float A) {
	static int tiempo = 0;
	static int i, x = 0, factorial = 1;
	static float r, suma, y, lamda;
	suma = 0;
	lamda = 6.6368f;

	r = getRandomNumber();
	while (suma<r) {
		x = x + 1;
		y = ((pow(lamda, x))*(pow(2.71828f, (-1 * lamda)))) / factorial;
		suma = suma + y;
		factorial = factorial * x;
	}
	tiempo = x;
	x = 0;
	suma = 0;
	factorial = 1;

	return tiempo;
}
static int generarTiempoServicio(float A) {
	static int tiempo = 0;
	static int i, x = 0, factorial = 1;
	static float r, suma, y, lamda;
	suma = 0;
	lamda = 16.833f;
	
	r = getRandomNumber();
	while (suma<r) {
		x = x + 1;
		y = ((pow(lamda, x))*(pow(2.71828f, (-1 * lamda)))) / factorial;
		suma = suma + y;
		factorial = factorial * x;
	}
	tiempo = x;
	x = 0;
	suma = 0;
	factorial = 1;
	
	
	return tiempo;
}
static int seleccionarMenor(int n1, int n2, int n3) {
	static int menor;
	static int valores[3];
	menor = 0;
	valores[0] = n1;
	valores[1] = n2;
	valores[2] = n3;
	for (int i = 0; i < 3; i++) {
		if (valores[i] > 0) {
			if ((menor <= 0)||(menor>valores[i])) {
				menor = valores[i];
			}
			
		}
	}
	return menor;
}
static int generarTipo() {
	static int tipo;
	static float r;
	r = getRandomNumber();
	if (r> 0.64) {
		tipo = 1;
	}
	else {
		tipo = 0;
	}
	return tipo;
}


#else

void ImGui::ShowTestWindow(bool*) {}
void ImGui::ShowUserGuide() {}
void ImGui::ShowStyleEditor(ImGuiStyle*) {}

#endif
