#pragma once
#include <imgui.h>
#include <iostream>
#include <windows.h>
#include <ctime>

#include "Util/Rechner.h"

	class Solution {
	public:

		bool OhmschesGesetzActive = false;
		bool OhmschesGesetzButton = false;

		Solution() = default;

		void Run() {

			HWND consoleWindow = GetConsoleWindow();
			ShowWindow(consoleWindow, 0);



			Util::Window window(1280, 720, "Calculator");
			Util::ImGuiInit(window);
			Util::Rechner rechner;

			//auto& colors = ImGui::GetStyle().Colors;

			bool selected = false;
			bool settingsopen = false;
			bool OhmschesGesetzActive = false;
			bool OhmschesGesetzButton = false;
			float textCol[4] = { 0.176f, 0.169f, 0.329f, 1.0f };//default Menuebar Background


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
					ImGui::Text("Help:");
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
					ImGui::SetCursorPos(ImVec2{ ImGui::GetContentRegionAvailWidth() / 2 - 60,50 });
					ImGui::PushFont(FontBig);
					ImGui::Text("Calculatortyps:");
					ImGui::PopFont();

					ImGui::SetCursorPos(ImVec2{ ImGui::GetContentRegionAvailWidth() / 2 - 60,100 });
					if(OhmschesGesetzButton == false)
					{
						if (ImGui::Button("Ohmsches Gesetz")) 
						{
							OhmschesGesetzActive = true;
						}
					}
					if (OhmschesGesetzActive == true)
					{
						OhmschesGesetzButton = true;
						int Hochzahl = 0;
						rechner.OhmschesGesetz();


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
