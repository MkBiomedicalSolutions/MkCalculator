///////////////////////////////////\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\
//| Owner       : Matthias Karasowski                                   |\\
\\|             https://github.com/MkBiomedicalSolutions/MkCalculator   |//
//|	Copyright   : MkBiomedicalSolutions                                 |\\
\\|             https://www.mksolutions.at/	                            |//
//| Filename    : Rechnerhilfsfunktionen.h                              |\\
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

#include <string>
#include <imgui.h>
#include <array>

class Rechnerhilfsfunktionen
{
public:

	int itemOld = 0;
	int Hochzahl = 0;


	char* ComboList(int x, int y, int InputFieldWidth, std::string ID, float* Item, int ComboWidth, std::string Name, int* CurrentItem, const char* ItemList[9], int OutputHochzahl);

	int CurrentItemToExponent(int Item);

	int ExponentToCurrentItem(int Hochzahl);

	void Save(int x, int y, char* Klicktime, std::array<float, 6>& Items, std::array<const char*, 6> ItemNames);

};

//     Copyright MkBiomedicalSolutions 2020 ALL RIGHTS RESERVED      \\