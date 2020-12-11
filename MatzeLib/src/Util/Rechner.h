 ///////////////////////////////////\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\
//|	Owner		: Matthias Karasowski									|\\
\\|				https://github.com/MkBiomedicalSolutions/MkCalculator	|//
//|	Copyright	: MkBiomedicalSolutions									|\\
\\|				https://www.mksolutions.at/								|//
//| Filename	: Rechner.h												|\\
\\|	Version		: 1.0 													|//
//|	Date		: 30.11.2020											|\\
\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\///////////////////////////////////////
////////////////////////////////////\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\
//| 																	|\\
\\|	Source		:														|//
//|				ImGui		:https://github.com/ocornut/imgui			|\\
\\|				glad		:https://glad.dav1d.de/						|//
//|				GLFW		:https://www.glfw.org/						|\\
\\|				stb_image	:https://github.com/nothings/stb			|//
//|																		|\\
\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\///////////////////////////////////////

#pragma once

#include <imgui.h>
#include <array>

#include "TextureLoader.h"
#include "Util/ImGuiUtil.h"

namespace Util 
{

	class Rechner
	{
		
	private:

		unsigned int CalculatorIcon;
		unsigned int SettingIcon;
		unsigned int HelpIcon;
		int i = 0;
		int i1 = 0;
		int	i2 = 0;
		int	i3 = 0;
		int R_Hochzahl;
		int I_Hochzahl;
		int U_Hochzahl;
		int Hochzahl = 0;
		int itemOld = 0;
		int currentItem = 3;
		int currentItem1 = 3;
		int currentItem2 = 3;
		const char* listbox_items[9] = { "   T", "   G", "   M","   k", "   V", "   m", "   u", "   n", "   p" };
		const char* listbox_items1[9] = { "   T", "   G", "   M","   k", "Ohm", "   m", "   u", "   n", "   p" };
		const char* listbox_items2[9] = { "   T", "   G", "   M","   k", "   A", "   m", "   u", "   n", "   p" };
		float ergebnis = 0;
		float childCol[4] = { 0.176f, 0.169f, 0.329f, 1.0f };//default Child Background 
		float selectedChildCol[4] = { 1.0f, 0.0f, 0.0f, 1.0f };//default Child Background 
		float windowCol[4] = { 0.168f, 0.165f, 0.227f, 1.0f };//default window Background 
		float menuebarCol[4] = { 0.176f, 0.169f, 0.329f, 1.0f };//default Menuebar Background 
		bool closeWindow = false;
		bool calculationState = false;
		bool settingsState = false;
		bool helpState = false;
		bool LogConsoleState = false;
		ImGuiTextBuffer Buf;
		bool ScrollToBottom;
		std::array<float, 3> bufferNew, bufferOld;
		std::array<bool, 7> check;
		ImFont* Font = ImGui::GetIO().Fonts->AddFontFromFileTTF("arial.ttf", 20);

	public:
		bool HelpIconButton = false;
		bool SettingIconButton = false;
		bool CalculatorIconButton = false;
		bool ReturnSpannung = false;
		bool ReturnStromstaerke = false;
		bool ReturnWiderstand = false;
		int Erg_Hochzahl = 0;
		float Spannung = 0;
		float Widerstand = 0;
		float Stromstaerke = 0;
	public:
		Rechner() 
		{

			CalculatorIcon = Util::LoadTexture("CalculationIcon.png");
			SettingIcon = Util::LoadTexture("SettingIcon.png");
			HelpIcon = Util::LoadTexture("HelpIcon.png");
			bufferNew = { 0,0,0 };
			bufferOld = { 0,0,0 };
			ImGui::GetStyle().Colors[ImGuiCol_ChildBg] = ImVec4{ childCol[0], childCol[1], childCol[2], childCol[3] };
			ImGui::GetStyle().Colors[ImGuiCol_WindowBg] = ImVec4{ windowCol[0], windowCol[1], windowCol[2], windowCol[3] };
			ImGui::GetStyle().Colors[ImGuiCol_MenuBarBg] = ImVec4{ menuebarCol[0], menuebarCol[1], menuebarCol[2], menuebarCol[3] };
		}

		void OhmschesGesetz()
		{

			ImGui::SameLine();
			ImGui::SetCursorPos(ImVec2{ 200,100 });
			ImGui::SetNextItemWidth(200);
			ImGui::DragFloat("##9901", &Spannung, 0.5f);
			ImGui::SameLine();
			ImGui::PushItemWidth(60);
			ImGui::ListBox("V [Volt]\nSpannung",&currentItem, listbox_items,8, 2);
			U_Hochzahl=CurrentItemToExponent(currentItem);
			ImGui::SetCursorPos(ImVec2{ 200,200 });
			ImGui::SetNextItemWidth(200);
			ImGui::DragFloat("##9902", &Widerstand, 0.5f);
			ImGui::SameLine();
			ImGui::ListBox("R [Ohm]\nWiderstand", &currentItem1, listbox_items1, 8, 2);
			R_Hochzahl = CurrentItemToExponent(currentItem1);
			ImGui::SetCursorPos(ImVec2{ 200,300 });
			ImGui::SetNextItemWidth(200);
			ImGui::DragFloat("##9903", &Stromstaerke, 0.5f);
			ImGui::SameLine();
			ImGui::ListBox("A [Ampere]\nStromstaerke", &currentItem2, listbox_items2, 8, 2);
			I_Hochzahl = CurrentItemToExponent(currentItem2);

			if (ImGui::Button("berechnen", ImVec2{ 200,50 }))
			{


				bufferNew = { Stromstaerke, Spannung, Widerstand };

				if (((Spannung != bufferOld[1]) && (Widerstand != bufferOld[2])) || ((Spannung != bufferOld[1]) && (Stromstaerke != bufferOld[0])) || ((Widerstand != bufferOld[2]) && (Stromstaerke != bufferOld[0])))
				{
					if ((bufferOld[1] != bufferNew[1]) && (bufferOld[2] != bufferNew[2]))
					{
						bufferOld = bufferNew;

						Stromstaerke = Spannung / Widerstand;
						if (R_Hochzahl < 0) {
							Erg_Hochzahl = U_Hochzahl + R_Hochzahl;
						}
						else {
							Erg_Hochzahl = U_Hochzahl - R_Hochzahl;
						}
						ReturnStromstaerke = true;
						ReturnSpannung = false;
						ReturnWiderstand = false;
						currentItem2 = ExponentToCurrentItem(Erg_Hochzahl);
						
					}

					if ((bufferOld[0] != bufferNew[0]) && (bufferOld[1] != bufferNew[1]))
					{
						bufferOld = bufferNew;

						Widerstand = Spannung / Stromstaerke;
						if (I_Hochzahl < 0) {
							Erg_Hochzahl = U_Hochzahl + I_Hochzahl;
						}
						else {
							Erg_Hochzahl = U_Hochzahl - I_Hochzahl;
						}
						ReturnWiderstand = true;
						ReturnSpannung = false;
						ReturnStromstaerke = false;
						currentItem1 = ExponentToCurrentItem(Erg_Hochzahl);

						
					}

					if ((bufferOld[0] != bufferNew[0]) && (bufferOld[2] != bufferNew[2]))
					{
						bufferOld = bufferNew;

						Spannung = Widerstand * Stromstaerke;
						if (R_Hochzahl < 0 && I_Hochzahl>0) {
							Erg_Hochzahl = R_Hochzahl + I_Hochzahl;
						}
						else {
							Erg_Hochzahl = R_Hochzahl + I_Hochzahl;
						}
						ReturnSpannung = true;
						ReturnStromstaerke = false;
						ReturnWiderstand = false;
						currentItem = ExponentToCurrentItem(Erg_Hochzahl);
					}
				}
			}
		}
		int CurrentItemToExponent(int Item)
		{

			if (itemOld != Item)
			{
				itemOld = Item;
				if (itemOld < 4)
				{
					if (itemOld == 3)
						Hochzahl = 3;
					if (itemOld == 2)
						Hochzahl = 6;
					if (itemOld == 1)
						Hochzahl = 9;
					if (itemOld == 2)
						Hochzahl = 13;
				}
				if (itemOld == 4) //4 = 10^1
					Hochzahl = 0;
				if (itemOld > 4)
				{
					if (itemOld == 5)
						Hochzahl = -3;
					if (itemOld == 6)
						Hochzahl = -6;
					if (itemOld == 7)
						Hochzahl = -9;
					if (itemOld == 8)
						Hochzahl = -13;
				}
			}
			return Hochzahl;
		}
		int ExponentToCurrentItem(int Hochzahl)
		{
			int Item = 0;
			if (itemOld != Hochzahl)
			{
				itemOld = Hochzahl;
				if (itemOld < 4)
				{
					if (itemOld == 3)
						Item = 3;
					if (itemOld == 6)
						Item = 2;
					if (itemOld == 9)
						Item = 1;
					if (itemOld == 13)
						Item = 2;
				}
				if (itemOld == 4) //4 = 10^1
					Item = 0;
				if (itemOld > 4)
				{
					if (itemOld == -3)
						Item = 5;
					if (itemOld == -6)
						Item = 6;
					if (itemOld == -9)
						Item = 7;
					if (itemOld == -13)
						Item = 8;
				}
			}
			return Item;
		}

		void Rechteck()
		{
			ImGui::SameLine();
			ImGui::SetCursorPos(ImVec2{ 200,100 });
			ImGui::SetNextItemWidth(200);
			ImGui::DragFloat("##9901", &Spannung, 0.5f);
			ImGui::SameLine();
			ImGui::PushItemWidth(60);
			ImGui::ListBox("V [Volt]\nSpannung", &currentItem, listbox_items, 8, 2);
			U_Hochzahl = CurrentItemToExponent(currentItem);
			ImGui::SetCursorPos(ImVec2{ 200,200 });
			ImGui::SetNextItemWidth(200);
			ImGui::DragFloat("##9902", &Widerstand, 0.5f);
			ImGui::SameLine();
			ImGui::ListBox("R [Ohm]\nWiderstand", &currentItem, listbox_items1, 8, 2);
			R_Hochzahl = Hochzahl;
			ImGui::SetCursorPos(ImVec2{ 200,300 });
			ImGui::SetNextItemWidth(200);
			ImGui::DragFloat("##9903", &Stromstaerke, 0.5f);
			ImGui::SameLine();
			ImGui::ListBox("A [Ampere]\nStromstaerke", &currentItem, listbox_items2, 8, 2);
			I_Hochzahl = CurrentItemToExponent(currentItem);
		}
		void SettingsChildWindow() 
		{
			ImGui::ColorEdit4("Child Background", childCol);
			ImGui::GetStyle().Colors[ImGuiCol_ChildBg] = ImVec4{ childCol[0], childCol[1], childCol[2], childCol[3] };
			ImGui::GetStyle().Colors[ImGuiCol_Button] = ImVec4{ childCol[0], childCol[1], childCol[2], childCol[3] };
			ImGui::ColorEdit4("Selected Button", selectedChildCol);
			ImGui::GetStyle().Colors[ImGuiCol_Button] = ImVec4{ selectedChildCol[0], selectedChildCol[1], selectedChildCol[2], selectedChildCol[3] };
		}
		void SettingsWindow() 
		{
			ImGui::ColorEdit4("Window Background", windowCol);
			ImGui::GetStyle().Colors[ImGuiCol_WindowBg] = ImVec4{ windowCol[0], windowCol[1], windowCol[2], windowCol[3] };
		}
		void SettingsMenuebar() 
		{
			ImGui::ColorEdit4("menuebar Background", menuebarCol);
			ImGui::GetStyle().Colors[ImGuiCol_MenuBarBg] = ImVec4{ menuebarCol[0], menuebarCol[1], menuebarCol[2], menuebarCol[3] };

		}
		void MainMenue(bool& settingsopen) {
			if (ImGui::BeginMenuBar())
			{
				if (ImGui::BeginMenu("File"))
				{
					if (ImGui::MenuItem("Open ", "CTRL+O"));
					if (ImGui::MenuItem("Save ", "CTRL+S"));
					if (ImGui::MenuItem("Close"))
						closeWindow = true;
					ImGui::EndMenu();
				}
				if (ImGui::BeginMenu("Settings")) {

						SettingsChildWindow();
						SettingsWindow();
						SettingsMenuebar();
						ImGui::EndMenu();
					}

				if (ImGui::BeginMenu("About"))
					ImGui::EndMenu();

				if (ImGui::BeginMenu("Help"))
					ImGui::EndMenu();
				if (ImGui::BeginMenu("LogConsole"))
				{
					if (i == 0)
					{
						i++;
						LogConsoleState = true;
					}
					else {
						i = 0;
						LogConsoleState = false;
					}
					ImGui::EndMenu();
				}
				if(LogConsoleState== true)
				{
					LogConsole();
				}
				else {
					
				}
			}
			ImGui::EndMenuBar();
		}
		bool CloseWindow() 
		{
			return closeWindow;
		}
		void ImageButton(std::string WhichButton,std::array<bool,7>states1,unsigned int Icon,int counter, int counterZero1, int counterZero2)
		{
			if (states1[0] == true)
			{
				ImGui::GetStyle().Colors[ImGuiCol_Button] = ImVec4{ selectedChildCol[0], selectedChildCol[1], selectedChildCol[2], selectedChildCol[3] };
			}
			else {
				ImGui::GetStyle().Colors[ImGuiCol_Button] = ImVec4{ childCol[0], childCol[1], childCol[2], childCol[3] };
			}

			if (ImGui::ImageButton((ImTextureID)Icon, { 50.0f, 50.0f }, ImVec2{ 0, 1 }, ImVec2{ 1, 0 }))
			{
				states1[0] = true;
				states1[1] = false;
				states1[2] = false;

				if (counter == 0) {
					states1[3] = true;
					states1[4] = false;
					states1[5] = false;
					counterZero1 = 0;
					counterZero2 = 0;
					counter++;
				}
				else {
					counter = 0;
					states1[0] = false;
					states1[3] = false;
				}
			}
			if (WhichButton == "Calculator")
			{
				calculationState = states1[0];
				settingsState = states1[1];
				helpState= states1[2];
				CalculatorIconButton= states1[3];
				SettingIconButton=states1[4];
				HelpIconButton= states1[5];
				i1 = counter;
				i2= counterZero1;
				i3= counterZero2;
			}
			if (WhichButton == "Setting")
			{
				settingsState = states1[0];
				helpState = states1[1];
				calculationState = states1[2];
				SettingIconButton = states1[3];
				HelpIconButton = states1[4];
				CalculatorIconButton = states1[5];
				i2 = counter;
				i3 = counterZero1;
				i1 = counterZero2;
			}
		
			if (WhichButton == "Help")
			{
				helpState = states1[0];
				calculationState = states1[1];
				settingsState = states1[2];
				HelpIconButton = states1[3];
				CalculatorIconButton = states1[4];
				SettingIconButton = states1[5];
				i3 = counter;
				i1 = counterZero1;
				i2 = counterZero2;
			}
		}
		
		void ChildWindow() 
		{
			ImGui::BeginChild("Child", ImVec2{ 73.5f, 0.0f }, true);

			check = { calculationState,settingsState,helpState,CalculatorIconButton,SettingIconButton,HelpIconButton };
			ImageButton("Calculator",check,CalculatorIcon,i1,i2,i3);
			check = { settingsState,helpState,calculationState,SettingIconButton,HelpIconButton,CalculatorIconButton };
			ImageButton("Setting",check,SettingIcon,i2,i3,i1);
			check = { helpState,calculationState,settingsState,HelpIconButton,CalculatorIconButton,SettingIconButton };
			ImageButton("Help",check,HelpIcon,i3,i1,i2);

			ImGui::EndChild();
		}


		//Console Log
		void LogConsole() 
		{

				ImGui::Begin("Log Console", 0, ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize);
				ImGui::SetWindowSize(ImVec2{ 500, 500 });
				ImGui::Text("!Attention please!");
				ImGui::End();
		}


		
	};
}
//		Copyright MkBiomedicalSolutions 2020 ALL RIGHTS RESERVED		\\