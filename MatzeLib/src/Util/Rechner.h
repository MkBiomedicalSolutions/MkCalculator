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

#include <iostream>
#include <imgui.h>
#include <array>
#include <fstream>

#include "Util/ImGuiUtil.h"
#include "TextureLoader.h"

namespace Util 
{
	class Rechner
	{
		
		private:

			int i = 0;
			int i1 = 0;
			int	i2 = 0;
			int	i3 = 0;
			int itemOld = 0;
			int Hochzahl = 0;
			int R_Hochzahl = 0;
			int I_Hochzahl = 0;
			int U_Hochzahl = 0;
			int P_Hochzahl = 0;
			int currentItem = 4;
			int currentItem1 = 4;
			int currentItem2 = 4;
			int currentItem3 = 4;
			int currentItem4 = 3;
			int currentItem5 = 3;

			unsigned int HelpIcon;
			unsigned int SettingIcon;
			unsigned int CalculatorIcon;

			float laenge = 0;
			float breite = 0;
			float ergebnis = 0;
			float childCol[4] = { 0.176f, 0.169f, 0.329f, 1.0f };
			float windowCol[4] = { 0.168f, 0.165f, 0.227f, 1.0f };
			float selectedChildCol[4] = { 1.0f, 0.0f, 0.0f, 1.0f };
			float menuebarCol[4] = { 0.176f, 0.169f, 0.329f, 1.0f };

			bool ScrollToBottom;
			bool helpState = false;
			bool closeWindow = false;
			bool settingsState = false;
			bool LogConsoleState = false;
			bool calculationState = false;

			const char* listbox_items[9] = { "   T", "   G", "   M","   k", "   V", "   m", "   u", "   n", "   p" };
			const char* listbox_items1[9] = { "   T", "   G", "   M","   k", "Ohm", "   m", "   u", "   n", "   p" };
			const char* listbox_items2[9] = { "   T", "   G", "   M","   k", "   A", "   m", "   u", "   n", "   p" };
			const char* listbox_items3[9] = { "   T", "   G", "   M","   k", "   W", "   m", "   u", "   n", "   p" };
			const char* listbox_items4[11] = {"sm","mi","km","m","ya","ft","dm","in","cm","mm","um"};

			ImGuiTextBuffer Buf;

			std::array<bool, 7> check;
			std::array<float, 4> bufferNew, bufferOld;

			ImFont* Font = ImGui::GetIO().Fonts->AddFontFromFileTTF("arial.ttf", 20);

		public:
			int Erg_Hochzahl = 0;
			float Leistung = 0;
			float Spannung = 0;
			float laenge2 = 0;
			float breite2 = 0;
			float Umfang = 0;
			float Diagonale = 0;
			float Umkreisradius = 0;
			float Flaecheninhalt = 0;
			float Widerstand = 0;
			float Stromstaerke = 0;
			float Rechteckberechnungen = false;
			bool Save = false;
			bool HelpIconButton = false;
			bool ReturnSpannung = false;
			bool ReturnWiderstand = false;
			bool RechnerAllowEnter = true;
			bool SettingIconButton = false;
			bool ReturnStromstaerke = false;
			bool CalculatorIconButton = false;
			char* Klicktime;
		public:
			Rechner() 
			{
				CalculatorIcon = Util::LoadTexture("CalculationIcon.png");
				SettingIcon = Util::LoadTexture("SettingIcon.png");
				HelpIcon = Util::LoadTexture("HelpIcon.png");
				bufferNew = { 0,0,0,0 };
				bufferOld = { 0,0,0,0 };
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
				ImGui::PushItemWidth(100);
				ImGui::Combo("V [Volt] Spannung",&currentItem, listbox_items,8);
				U_Hochzahl=CurrentItemToExponent(currentItem);

				ImGui::SetCursorPos(ImVec2{ 200,200 });
				ImGui::SetNextItemWidth(200);
				ImGui::DragFloat("##9902", &Widerstand, 0.5f);
				ImGui::SameLine();
				ImGui::PushItemWidth(100);
				ImGui::Combo("R [Ohm] Widerstand", &currentItem1, listbox_items1, 8);
				R_Hochzahl = CurrentItemToExponent(currentItem1);

				ImGui::SetCursorPos(ImVec2{ 200,300 });
				ImGui::SetNextItemWidth(200);
				ImGui::DragFloat("##9903", &Stromstaerke, 0.5f);
				ImGui::SameLine();
				ImGui::PushItemWidth(100);
				ImGui::Combo("A [Ampere] Stromstaerke", &currentItem2, listbox_items2, 8);
				I_Hochzahl = CurrentItemToExponent(currentItem2);

				ImGui::SetCursorPos(ImVec2{ 200,400 });
				ImGui::SetNextItemWidth(200);
				ImGui::DragFloat("##9904", &Leistung, 0.5f);
				ImGui::SameLine();
				ImGui::PushItemWidth(100);
				ImGui::Combo("P [Watt] Leistung", &currentItem3, listbox_items3, 8);
				P_Hochzahl = CurrentItemToExponent(currentItem3);

				if (ImGui::Button("berechnen", ImVec2{ 200,50 }))
				{

					std::cout << "Perfekt" << std::endl;
					bufferNew = { Stromstaerke, Spannung, Widerstand, Leistung };


						if ((bufferOld[1] != bufferNew[1]) && (bufferOld[2] != bufferNew[2]))
						{
							bufferOld = bufferNew;
							Stromstaerke = Spannung / Widerstand;
							Leistung = (Spannung * Spannung) / Widerstand;

							if (R_Hochzahl < 0) 
							{
								Erg_Hochzahl = U_Hochzahl + R_Hochzahl;
							}
							else 
							{
								Erg_Hochzahl = U_Hochzahl - R_Hochzahl;
							}

							ReturnSpannung = false;
							ReturnWiderstand = false;
							ReturnStromstaerke = true;
							currentItem2 = ExponentToCurrentItem(Erg_Hochzahl);
						}

						if ((bufferOld[0] != bufferNew[0]) && (bufferOld[1] != bufferNew[1]))
						{
							bufferOld = bufferNew;
							Leistung = Spannung * Stromstaerke;
							Widerstand = Spannung / Stromstaerke;

							if (I_Hochzahl < 0) 
							{
								Erg_Hochzahl = U_Hochzahl + I_Hochzahl;
							}
							else 
							{
								Erg_Hochzahl = U_Hochzahl - I_Hochzahl;
							}
							ReturnSpannung = false;
							ReturnWiderstand = true;
							ReturnStromstaerke = false;
							currentItem1 = ExponentToCurrentItem(Erg_Hochzahl);

						
						}

						if ((bufferOld[0] != bufferNew[0]) && (bufferOld[2] != bufferNew[2]))
						{
							bufferOld = bufferNew;
							Spannung = Widerstand * Stromstaerke;
							Leistung = Widerstand * Stromstaerke * Stromstaerke;

							if (R_Hochzahl < 0 && I_Hochzahl>0) 
							{
								Erg_Hochzahl = R_Hochzahl + I_Hochzahl;
							}
							else 
							{
								Erg_Hochzahl = R_Hochzahl + I_Hochzahl;
							}
							ReturnSpannung = true;
							ReturnWiderstand = false;
							ReturnStromstaerke = false;
							currentItem = ExponentToCurrentItem(Erg_Hochzahl);
						}

						if ((bufferOld[3] != bufferNew[3]) && (bufferOld[0] != bufferNew[0]))
						{
							bufferOld = bufferNew;

							Spannung = Leistung / Stromstaerke;
							Widerstand = Leistung / (Stromstaerke*Stromstaerke);
							std::cout << Spannung << std::endl;
							if (P_Hochzahl < 0 && I_Hochzahl>0) {
								Erg_Hochzahl = P_Hochzahl + I_Hochzahl;
							}
							else {
								Erg_Hochzahl = P_Hochzahl - I_Hochzahl;
							}
							currentItem = ExponentToCurrentItem(Erg_Hochzahl);
						}

						if ((bufferOld[3] != bufferNew[3]) && (bufferOld[2] != bufferNew[2]))
						{
							bufferOld = bufferNew;

							Spannung = sqrt(Leistung * Widerstand);
							Stromstaerke = sqrt(Leistung / Widerstand);

							if (P_Hochzahl < 0 && R_Hochzahl>0) {
								Erg_Hochzahl = P_Hochzahl + R_Hochzahl;
							}
							else {
								Erg_Hochzahl = P_Hochzahl + R_Hochzahl;
							}
							currentItem = ExponentToCurrentItem(Erg_Hochzahl);
						}

						if ((bufferOld[3] != bufferNew[3]) && (bufferOld[1] != bufferNew[1]))
						{
							bufferOld = bufferNew;

							Widerstand= (Spannung*Spannung) / Leistung;
							Stromstaerke = Leistung / Spannung;

							if (P_Hochzahl < 0 && R_Hochzahl>0) {
								Erg_Hochzahl = P_Hochzahl + R_Hochzahl;
							}
							else {
								Erg_Hochzahl = P_Hochzahl - R_Hochzahl;
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
				ImGui::SetCursorPos(ImVec2{ 200,100 });
				ImGui::SetNextItemWidth(200);
				ImGui::DragFloat("##9905", &laenge, 0.5f);
				ImGui::SameLine();
				ImGui::PushItemWidth(100);
				ImGui::Combo("l Laenge", &currentItem4, listbox_items4, 10);

				ImGui::SetCursorPos(ImVec2{ 200,200 });
				ImGui::SetNextItemWidth(200);
				ImGui::DragFloat("##9906", &breite, 0.5f);
				ImGui::SameLine();
				ImGui::PushItemWidth(100);
				ImGui::Combo("b Breite", &currentItem5, listbox_items4, 10);

				ImGui::SetCursorPos(ImVec2{ 400,400 });
				if (ImGui::Button("berechnen", ImVec2{ 200,50 }))
				{
					Flaecheninhalt = laenge * breite;
					Umfang = 2 * (laenge + breite);
					Diagonale = sqrt((laenge*laenge)+(breite*breite));
					Umkreisradius = Diagonale / 2;
					//Innenwinkel = 90;
					Rechteckberechnungen = true;
					laenge2 = laenge;
					breite2 = breite;
					laenge = 0;
					breite = 0;
				}
				ImGui::SameLine();
				if (ImGui::Button("Save", ImVec2{ 200,50 }))
				{
					std::ofstream myfile("Results.txt", std::ios::out | std::ios::app);
					if (myfile.is_open())
					{
						myfile << "---------------------------------------------\n";
						myfile << "Ergebnisse vom: " << Klicktime <<"\n";
						myfile << "Laenge		:" << laenge2 <<"\n";
						myfile << "Breite		:" << breite2 <<"\n";
						myfile << "Flaecheninhalt	:" << Flaecheninhalt <<"\n";
						myfile << "Umfang		:" << Umfang <<"\n";
						myfile << "Diagonale	:" << Diagonale <<"\n";
						myfile << "Umkreisradius	:" << Umkreisradius <<"\n";

						myfile.close();
					}
					else std::cout << "Unable to open file" << std::endl;
				}

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