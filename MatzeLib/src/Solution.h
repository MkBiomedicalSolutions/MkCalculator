///////////////////////////////////\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\
//|	Owner		: Matthias Karasowski									|\\
\\|				https://github.com/MkBiomedicalSolutions/MkCalculator	|//
//|	Copyright	: MkBiomedicalSolutions									|\\
\\|				https://www.mksolutions.at/								|//
//| Filename	: Solution.h											|\\
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

#include <windows.h>
#include <iostream>
#include <imgui.h>
#include <ctime>


#include "Util/Rechner.h"



class Solution 
{
	public:

		bool OhmschesGesetzActive = false;
		bool OhmschesGesetzButton = false;
		bool selected = false;
		bool settingsopen = false;
		bool  GeometryActive = false;
		bool  GeometryButton = false;
		bool HeadlineCalculatorTyps = true;
		float textCol[4] = { 0.176f, 0.169f, 0.329f, 1.0f };//default Menuebar Background


		Solution() = default;

		void Run() {
			HWND consoleWindow = GetConsoleWindow();
			ShowWindow(consoleWindow, SW_SHOW);


			
			Util::Window window(1280, 720, "Calculator");
			Util::ImGuiInit(window);
			Util::Rechner rechner;

			//auto& colors = ImGui::GetStyle().Colors;
			ImFont* Font = ImGui::GetIO().Fonts->AddFontFromFileTTF("arial.ttf", 20);
			ImFont* FontBig = ImGui::GetIO().Fonts->AddFontFromFileTTF("arial.ttf", 40);
			ImGui::GetIO().FontDefault = Font;

			window.SetIcon("MenueIcon.png");

			while (window.isOpen())
			{
				time_t ttime = time(0);
				char* dt = ctime(&ttime);

				if (rechner.CloseWindow())
				{
					window.Close();
				}

				Util::ImGuiBeginFrame();

				window.Update();
				window.Clear();

				ImGui::SetNextWindowPos(ImVec2{ window.GetPosition().x, window.GetPosition().y });
				ImGui::SetNextWindowSize(ImVec2{ window.GetSize().x, window.GetSize().y });

				ImGui::Begin("##9900", 0, ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDecoration);
				rechner.ChildWindow();
				rechner.MainMenue(settingsopen);
				
	
			
				if (rechner.HelpIconButton == true)
				{
					ImGui::SetCursorPos(ImVec2{ ImGui::GetContentRegionAvailWidth() / 2 - 20,50 });
					ImGui::PushFont(FontBig);
					ImGui::Text("Help");
					ImGui::PopFont();
				}
				if (rechner.SettingIconButton == true)
				{
					ImGui::SetCursorPos(ImVec2{ ImGui::GetContentRegionAvailWidth() / 2 - 50,50 });
					ImGui::PushFont(FontBig);
					ImGui::Text("Settings:");
					ImGui::PopFont();
				}
				if (rechner.CalculatorIconButton == true)
				{
					if (HeadlineCalculatorTyps == true)
					{
						ImGui::SetCursorPos(ImVec2{ ImGui::GetContentRegionAvailWidth() / 2 - 60,50 });
						ImGui::PushFont(FontBig);
						ImGui::Text("Calculatortyps:");
						ImGui::PopFont();
					}
					ImGui::SetCursorPos(ImVec2{ ImGui::GetContentRegionAvailWidth() / 2 - 60,100 });
					if(OhmschesGesetzButton == false)
					{
						if (ImGui::Button("Ohmsches Gesetz")) 
						{
							OhmschesGesetzActive = true;
							HeadlineCalculatorTyps = false;
						}
					}
					if (OhmschesGesetzActive == true)
					{
						OhmschesGesetzButton = true;
						int Hochzahl = 0;
						rechner.OhmschesGesetz();
						if(rechner.ReturnSpannung == true)
							ImGui::Text("%lf*10^%d", rechner.Spannung, rechner.Erg_Hochzahl);
						if(rechner.ReturnStromstaerke ==true )
							ImGui::Text("%lf*10^%d", rechner.Stromstaerke, rechner.Erg_Hochzahl);
						if(rechner.ReturnWiderstand == true)
							ImGui::Text("%lf*10^%d", rechner.Widerstand, rechner.Erg_Hochzahl);



					}
					ImGui::SetCursorPos(ImVec2{ ImGui::GetContentRegionAvailWidth() / 2 - 60,130 });
					if (GeometryButton == false)
					{
						
						if (ImGui::Button("Geometry"))
						{
							GeometryActive = true;
							HeadlineCalculatorTyps = false;
						}
					}
					if (GeometryActive == true)
					{
						GeometryButton = true;
						int Hochzahl = 0;
						rechner.Rechteck();
						if (rechner.Rechteckberechnungen == true)
						{
							ImGui::Text("laenge = %lf", rechner.laenge2);
							ImGui::Text("breite = %lf", rechner.breite2);
							ImGui::Text("Flaecheninhalt = %lf", rechner.Flaecheninhalt);
							ImGui::Text("Umfang = %lf", rechner.Umfang);
							ImGui::Text("Diagonale = %lf", rechner.Diagonale);
							ImGui::Text("Umkreisradius = %lf", rechner.Umkreisradius);
							ImGui::Text("Innenkreiswinkel = Alpha = Betha = Gamma = delta = 90°");
							rechner.Klicktime = dt;
						}
	
						ImGui::Begin("Simulation");
						ImVec2 p = ImGui::GetCursorScreenPos();
						ImGui::GetWindowDrawList()->AddRectFilled({ p.x, p.y }, { p.x + 400.0f, p.y + 200.0f }, IM_COL32_WHITE);
						ImGui::GetWindowDrawList()->AddText(ImGui::GetFont(), ImGui::GetFontSize() * 2.0f, ImVec2(p.x +200.0f, p.y + 200.0f), IM_COL32(255, 255, 255, 255), "x", NULL, 0.0f);
						ImGui::GetWindowDrawList()->AddText(ImGui::GetFont(), ImGui::GetFontSize() * 2.0f, ImVec2(p.x + 410.0f, p.y + 66.6f), IM_COL32(255, 255, 255, 255), "y", NULL, 0.0f);
						ImGui::End();
					}
				}


				
				//float ergebnis = rechner.OhmschesGesetz(Spannung, Widerstand, Stromstaerke, bufferNew, bufferOld);
				//ImGui::Checkbox("Matze", &selected);
				//ImGui::Text("Das Ergebnis ist: %f", ergebnis);
				ImGui::SetCursorPos(ImVec2{ ImGui::GetContentRegionAvailWidth()/2-60,700});
				ImGui::Text("%s", dt);
				ImGui::End();
				//ImGui::ShowDemoWindow();
				Util::ImGuiEndFrame();
			}
			Util::ImGuiShutdown();
		}
	};
	//		Copyright MkBiomedicalSolutions 2020 ALL RIGHTS RESERVED		\\
