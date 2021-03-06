///////////////////////////////////\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\
//|	Owner       : Matthias Karasowski                                   |\\
\\|             https://github.com/MkBiomedicalSolutions/MkCalculator   |//
//|	Copyright   : MkBiomedicalSolutions                                 |\\
\\|             https://www.mksolutions.at/	                            |//
//| Filename    : Solution.cpp                                          |\\
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

#include <ctime>
#include <string>
#include <imgui.h>
#include <iostream>
#include <windows.h>

#include "Rechner.h"
#include "Settings.h"

class Solution 
{
	public:

		float textCol[4] = { 0.176f, 0.169f, 0.329f, 1.0f };//default Menuebar Background

		bool selected = false;
		bool settingsopen = false;

		Solution() = default;

		void Run();
};
	//     Copyright MkBiomedicalSolutions 2020 ALL RIGHTS RESERVED       \\
