 ///////////////////////////////////\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\
//|	Owner       : Matthias Karasowski                                   |\\
\\|             https://github.com/MkBiomedicalSolutions/MkCalculator   |//
//|	Copyright   : MkBiomedicalSolutions                                 |\\
\\|             https://www.mksolutions.at/	                            |//
//| Filename    : Rechner.h                                             |\\
\\|	Version     : 1.0                                                   |//
//|	Date        : 30.11.2020                                            |\\
\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\///////////////////////////////////////
////////////////////////////////////\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\
//|                                                                     |\\
\\|	Source      :                                                       |//
//|             ImGui       :https://github.com/ocornut/imgui           |\\
\\|             glad        :https://glad.dav1d.de/                     |//
//|             GLFW        :https://www.glfw.org/                      |\\
\\|             stb_image   :https://github.com/nothings/stb            |//
//|                                                                     |\\
\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\///////////////////////////////////////

#pragma once

#define _NO_OUTPUT_ 0

#include <array>
#include <imgui.h>
#include <fstream>
#include <iostream>

#include "Util/ImGuiUtil.h"
#include "Rechnerhilfsfunktionen.h"

class Rechner
{
		
	public:

		Rechnerhilfsfunktionen Rhf;

		int R_Hochzahl = 0;
		int I_Hochzahl = 0;
		int U_Hochzahl = 0;
		int P_Hochzahl = 0;
		int currentItem1 = 4;
		int currentItem2 = 4;
		int currentItem3 = 4;
		int currentItem6 = 3;
		int currentItem7 = 3;
		int currentItem8 = 3;
		int Erg_Hochzahl = 0;

		float a = 0;
		float b = 0;
		float c = 0;
		float Einheit1 = 0;
		float Einheit2 = 0;
		float Umfang = 0;
		float laenge = 0;
		float breite = 0;
		float laenge2 = 0;
		float breite2 = 0;
		float Leistung = 0;
		float Spannung = 0;
		float ergebnis = 0;
		float Diagonale = 0;
		float Widerstand = 0;
		float Stromstaerke = 0;
		float Umkreisradius = 0;
		float Flaecheninhalt = 0;

		std::array<float, 6> ItemsRechteck;
			
		bool Save = false;
		bool ScrollToBottom;
		bool ReturnSpannung = false;
		bool ReturnWiderstand = false;
		bool RechnerAllowEnter = true;
		bool ReturnStromstaerke = false;
		bool Rechteckberechnungen = false;

		char* Klicktime;
		char* Array;

		const char* listbox_items[9] = { "   T", "   G", "   M","   k", "   V", "   m", "   u", "   n", "   p" };
		const char* currentItem = listbox_items[4];
		const char* listbox_items1[9] = { "   T", "   G", "   M","   k", "Ohm", "   m", "   u", "   n", "   p" };
		const char* listbox_items2[9] = { "   T", "   G", "   M","   k", "   A", "   m", "   u", "   n", "   p" };
		const char* listbox_items3[9] = { "   T", "   G", "   M","   k", "   W", "   m", "   u", "   n", "   p" };

		const char* listbox_items4[11] = {"sm","mi","km","m","ya","ft","dm","in","cm","mm","um"};
		const char* currentItem4 = listbox_items4[3];
		const char* currentItem5 = listbox_items4[3];
		const char* listboxItemsEinheitenKategorie[14] = { "Datengroeße","Datenuebertragungsrate","Druck","Energie","Flaeche","Flaechenwinkel","Frequenz","Geschwindikeit","Kraftstoffverbrauch","Laenge","Masse","Temperatur","Volumen","Zeit" };

		//Datengröße
		const char* listboxItemsDatengroeßeEinheiten1[11] = { "Pebibyte","Petabyte","Tebibyte","Terabyte","Gibibyte","Gigabyte","Mebibyte","Megabyte","Kibibyte","Kilobyte","Byte"};
		//datenübertragungsrate

		ImGuiTextBuffer Buf;

		Rechnerhilfsfunktionen rhf;

		std::array<const char*, 6> ItemNamesRechteck = { "Laenge		:","Breite		:","Flaecheninhalt	:","Umfang		:","Diagonale	:","Umkreisradius	:" };


		std::array<float, 4> bufferNew, bufferOld;

		Rechner() 
		{
			bufferNew = { 0,0,0,0 };
			bufferOld = { 0,0,0,0 };
		}

		void OhmschesGesetz();
		
		void Rechteck();

		void Dreieck();

		void CurrencyConverter();
		
		
};
//		Copyright MkBiomedicalSolutions 2020 ALL RIGHTS RESERVED		\\