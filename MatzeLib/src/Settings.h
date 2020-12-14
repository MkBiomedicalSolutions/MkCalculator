///////////////////////////////////\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\
//|	Owner       : Matthias Karasowski                                   |\\
\\|             https://github.com/MkBiomedicalSolutions/MkCalculator   |//
//|	Copyright   : MkBiomedicalSolutions                                 |\\
\\|             https://www.mksolutions.at/	                            |//
//| Filename    : Settings.h                                            |\\
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

#include <array>
#include <ctime>
#include <string>
#include <imgui.h>

#include "Rechner.h"
#include "Util/TextureLoader.h"

class Settings
{
	public:

		Rechner rechner;

		int i = 0;
		int i1 = 0;
		int	i2 = 0;
		int	i3 = 0;
		int currentItemLanguage = 1;

		unsigned int HelpIcon;
		unsigned int SettingIcon;
		unsigned int CalculatorIcon;

		float childCol[4] = { 0.176f, 0.169f, 0.329f, 1.0f };
		float windowCol[4] = { 0.168f, 0.165f, 0.227f, 1.0f };
		float selectedChildCol[4] = { 1.0f, 0.0f, 0.0f, 1.0f };
		float menuebarCol[4] = { 0.176f, 0.169f, 0.329f, 1.0f };

		const char* listbox_itemsLanguage[11] = { "German","English" };

		bool helpState = false;
		bool Simulation = false;
		bool closeWindow = false;
		bool settingsState = false;
		bool HelpIconButton = false;
		bool LogConsoleState = false;
		bool  GeometryActive = false;
		bool  GeometryButton = false;
		bool calculationState = false;
		bool SettingIconButton = false;
		bool OhmschesGesetzButton = false;
		bool CalculatorIconButton = false;
		bool OhmschesGesetzActive = false;
		bool HeadlineCalculatorTyps = true;

		std::string text[11];
		std::string ChooseLanguage = "English";
		std::string English[11] = { "Help:","Settings:","Calculatortyps","Ohms_law","Geometry","Length","Width","Area","Scope","Diagonal","Permimeterradius" };
		std::string German[11] = { "Hilfe:","Einstellungen:","Taschenrechnertypen:","Ohmsche´s Gesetz","Geometrie","Laenge","Breite","Flaecheninhalt","Umfang","Diagonale","Umkreisradius" };		

		std::array<bool, 7> check;

		ImFont* Font = ImGui::GetIO().Fonts->AddFontFromFileTTF("res/Fonts/arial.ttf", 20);
		ImFont* FontBig = ImGui::GetIO().Fonts->AddFontFromFileTTF("res/Fonts/arial.ttf", 40);

		Settings() 
		{
			HelpIcon = Util::LoadTexture("res/Icons/HelpIcon.png");
			SettingIcon = Util::LoadTexture("res/Icons/SettingIcon.png");
			CalculatorIcon = Util::LoadTexture("res/Icons/CalculationIcon.png");
	
			ImGui::GetStyle().Colors[ImGuiCol_ChildBg] = ImVec4{ childCol[0], childCol[1], childCol[2], childCol[3] };
			ImGui::GetStyle().Colors[ImGuiCol_WindowBg] = ImVec4{ windowCol[0], windowCol[1], windowCol[2], windowCol[3] };
			ImGui::GetStyle().Colors[ImGuiCol_MenuBarBg] = ImVec4{ menuebarCol[0], menuebarCol[1], menuebarCol[2], menuebarCol[3] };

			ImGui::GetIO().FontDefault = Font;

		}

		void Language();


		void SettingsChildWindow();


		void SettingsWindow();


		void SettingsMenuebar();


		void MainMenue(bool& settingsopen);


		bool CloseWindow();


		void ImageButton(std::string WhichButton, std::array<bool, 7>states1, unsigned int Icon, int counter, int counterZero1, int counterZero2);

		
		void SettingHelpButton();


		void SettingSettingButton();


		void SettingCalculatorButton();


		void ChildWindow();


		void LogConsole();

		
};
	//     Copyright MkBiomedicalSolutions 2020 ALL RIGHTS RESERVED      \\
