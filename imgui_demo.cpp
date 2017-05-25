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
//#include <windows.h>
#if defined(_MSC_VER) && _MSC_VER <= 1500 // MSVC 2008 or earlier
#include <stddef.h>         // intptr_t
#else
#include <stdint.h>         // intptr_t
#endif

#include<iostream>
#include <random>

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

static int generarTiempoLLegada(float P);
static int generarTiempoLLamada(float A);
static int seleccionarMenor(int n1, int n2, int n3);
static int generarTipo();
static float getRandomNumber();
static int randomInteger();
static void geometrica();

enum { MIN = 0, MAX = 1000 };

using namespace std;

#define LEN 20
char times[LEN];

struct ExampleAppLog
{
    ImGuiTextBuffer     Buf;
    ImGuiTextFilter     Filter;
    ImVector<int>       LineOffsets;        // Index to lines offset
    bool                ScrollToBottom;

    void    Clear()     { Buf.clear(); LineOffsets.clear(); }

    void    AddLog(const char* fmt, ...) IM_PRINTFARGS(2)
    {
        int old_size = Buf.size();
        va_list args;
        va_start(args, fmt);
        Buf.appendv(fmt, args);
        va_end(args);
        for (int new_size = Buf.size(); old_size < new_size; old_size++)
            if (Buf[old_size] == '\n')
                LineOffsets.push_back(old_size);
        ScrollToBottom = true;
    }

    void    Draw(const char* title, bool* p_open = NULL)
    {
        ImGui::SetNextWindowSize(ImVec2(500,400), ImGuiSetCond_FirstUseEver);
        ImGui::Begin(title, p_open);
        if (ImGui::Button("Clear")) Clear();
        ImGui::SameLine();
        bool copy = ImGui::Button("Copy");
        ImGui::SameLine();
        Filter.Draw("Filter", -100.0f);
        ImGui::Separator();
        ImGui::BeginChild("scrolling", ImVec2(0,0), false, ImGuiWindowFlags_HorizontalScrollbar);
        if (copy) ImGui::LogToClipboard();

        if (Filter.IsActive())
        {
            const char* buf_begin = Buf.begin();
            const char* line = buf_begin;
            for (int line_no = 0; line != NULL; line_no++)
            {
                const char* line_end = (line_no < LineOffsets.Size) ? buf_begin + LineOffsets[line_no] : NULL;
                if (Filter.PassFilter(line, line_end))
                    ImGui::TextUnformatted(line, line_end);
                line = line_end && line_end[1] ? line_end + 1 : NULL;
            }
        }
        else
        {
            ImGui::TextUnformatted(Buf.begin());
        }

        if (ScrollToBottom)
            ImGui::SetScrollHere(1.0f);
        ScrollToBottom = false;
        ImGui::EndChild();
        ImGui::End();
    }
};



void ImGui::Simulacion(bool* p_open, int tiempoMax, int nFilas, int nServicio) {
        	

	static ExampleAppLog log;

	ImGui::Begin("Simulacion", p_open);
	
	
	if(ImGui::Button("Generate times"))
	  {
	    geometrica();
	    log.AddLog("\n\n \tNew Generation\n\n");
	    for(int i = 0; i < LEN; i++)
	      log.AddLog("%d\n", times[i]);
	  }


	 log.Draw("Numbers for time", p_open);

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
static int seleccionarMenor(int n1, int n2, int n3) {
	static int mayor;

	mayor = 10;
	return mayor;
}
static int generarTipo() {
	static int tipo;
	tipo = 1;
	return tipo;
}


static int randomInteger()
{
  std::mt19937 rng;  // only used once to initialise (seed) engine
  rng.seed(std::random_device()());
  std::uniform_int_distribution<std::mt19937::result_type> dist(MIN,MAX); // distribution in range [MIN, MAX]

  auto random_integer = dist(rng);
  
  return random_integer;
}

//Metodo Congruencial Lineal
static float getRandomNumber()
{

    long int m = 97711 /* 97711 */;
    int c = 7, a = 7;
    double nrandom = 0.0f, temp = 0.0f;
    double uniforme = 0.0f;
    
    int random_stop = randomInteger();
    cout << "rs = " << random_stop << " ";

    for (long int i = 0; i < random_stop; ++i)
      {
	nrandom = ((int)(a*temp + c) % m);
	temp = nrandom;
      }

    uniforme = nrandom / m;

  return uniforme;
}


static void geometrica(){
  double p, suma, y = 0;
  double r;
  int x;

  p = 0.07203;

  for (int i = 0; i < LEN; ++i)
    {
      x = 0;
      suma = 0;
      r = getRandomNumber();
      //cout << "r = " << r << endl;

      while (suma < r) {
	x++;
	y = (pow((1-p), x-1))*p;
	suma += y;
      }
      times[i] = x;
      printf("X = %d\n", x);
    }
}
#else

void ImGui::ShowTestWindow(bool*) {}
void ImGui::ShowUserGuide() {}
void ImGui::ShowStyleEditor(ImGuiStyle*) {}

#endif
