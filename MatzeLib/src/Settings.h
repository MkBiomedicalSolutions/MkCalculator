#pragma once
#include <imgui.h>
#include <array>
#include <string>
#include <ctime>

#include "Util/TextureLoader.h"
#include "Rechner.h"


	class Settings
	{
	public:


		int i = 0;
		int i1 = 0;
		int	i2 = 0;
		int	i3 = 0;

		unsigned int HelpIcon;
		unsigned int SettingIcon;
		unsigned int CalculatorIcon;

		float childCol[4] = { 0.176f, 0.169f, 0.329f, 1.0f };
		float windowCol[4] = { 0.168f, 0.165f, 0.227f, 1.0f };
		float selectedChildCol[4] = { 1.0f, 0.0f, 0.0f, 1.0f };
		float menuebarCol[4] = { 0.176f, 0.169f, 0.329f, 1.0f };

		bool closeWindow = false;
		bool LogConsoleState = false;
		bool helpState = false;
		bool settingsState = false;
		bool calculationState = false;
		bool CalculatorIconButton = false;
		bool SettingIconButton = false;
		bool HelpIconButton = false;
		bool HeadlineCalculatorTyps = true;
		bool OhmschesGesetzButton = false;
		bool OhmschesGesetzActive = false;
		bool  GeometryActive = false;
		bool  GeometryButton = false;
		bool Simulation = false;

		Rechner rechner;

		std::string ChooseLanguage = "English";
		std::string English[11] = { "Help:","Settings:","Calculatortyps","Ohms_law","Geometry","Length","Width","Area","Scope","Diagonal","Permimeterradius" };
		std::string German[11] = { "Hilfe:","Einstellungen:","Taschenrechnertypen:","Ohmsche´s Gesetz","Geometrie","Laenge","Breite","Flaecheninhalt","Umfang","Diagonale","Umkreisradius" };

		std::string text[11];

		std::array<bool, 7> check;

		ImFont* Font = ImGui::GetIO().Fonts->AddFontFromFileTTF("res/Fonts/arial.ttf", 20);
		ImFont* FontBig = ImGui::GetIO().Fonts->AddFontFromFileTTF("res/Fonts/arial.ttf", 40);
		

		Settings() 
		{
			CalculatorIcon = Util::LoadTexture("res/Icons/CalculationIcon.png");
			SettingIcon = Util::LoadTexture("res/Icons/SettingIcon.png");
			HelpIcon = Util::LoadTexture("res/Icons/HelpIcon.png");

			ImGui::GetStyle().Colors[ImGuiCol_ChildBg] = ImVec4{ childCol[0], childCol[1], childCol[2], childCol[3] };
			ImGui::GetStyle().Colors[ImGuiCol_WindowBg] = ImVec4{ windowCol[0], windowCol[1], windowCol[2], windowCol[3] };
			ImGui::GetStyle().Colors[ImGuiCol_MenuBarBg] = ImVec4{ menuebarCol[0], menuebarCol[1], menuebarCol[2], menuebarCol[3] };

			ImGui::GetIO().FontDefault = Font;

		}

		void Language()
		{
			if (ChooseLanguage == "English")
			{
				for (int j = 0; j <= 10; j++) { text[j] = English[j]; }
			}
			if (ChooseLanguage == "German")
			{
				for (int j = 0; j <= 10; j++) { text[j] = German[j]; }
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
				if (LogConsoleState == true)
				{
					LogConsole();
				}
				if (ImGui::BeginMenu("Language"))
				{
					if (ImGui::MenuItem("German"))
						ChooseLanguage = "German";
					if (ImGui::MenuItem("English"))
						ChooseLanguage = "English";
					ImGui::EndMenu();
				}
			}
			ImGui::EndMenuBar();
		}

		bool CloseWindow()
		{
			return closeWindow;
		}

		void ImageButton(std::string WhichButton, std::array<bool, 7>states1, unsigned int Icon, int counter, int counterZero1, int counterZero2)
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
				helpState = states1[2];
				CalculatorIconButton = states1[3];
				SettingIconButton = states1[4];
				HelpIconButton = states1[5];
				i1 = counter;
				i2 = counterZero1;
				i3 = counterZero2;
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
		
		void SettingHelpButton()
		{
			Language();
			if (HelpIconButton == true)
			{
				ImGui::SetCursorPos(ImVec2{ ImGui::GetContentRegionAvailWidth() / 2 - 20,50 });
				ImGui::PushFont(FontBig);
				ImGui::Text(text[0].c_str());
				ImGui::PopFont();
			}
		}
		void SettingSettingButton()
		{

			if (SettingIconButton == true)
			{
				Language();
				ImGui::SetCursorPos(ImVec2{ ImGui::GetContentRegionAvailWidth() / 2 - 50,50 });
				ImGui::PushFont(FontBig);
				ImGui::Text(text[1].c_str());
				ImGui::PopFont();
			}
		}
		void SettingCalculatorButton()
		{
			
			time_t ttime = time(0);
			char* dt = ctime(&ttime);

			Language();
			if (CalculatorIconButton == true)
			{
				if (HeadlineCalculatorTyps == true)
				{
					ImGui::SetCursorPos(ImVec2{ ImGui::GetContentRegionAvailWidth() / 2 - 60,50 });
					ImGui::PushFont(FontBig);
					ImGui::Text(text[2].c_str()); //Calculatortyps
					ImGui::PopFont();
				}
				ImGui::SetCursorPos(ImVec2{ ImGui::GetContentRegionAvailWidth() / 2 - 60,100 });
				if (OhmschesGesetzButton == false)
				{
					if (ImGui::Button(text[3].c_str())==true) //Ohmsches Gesetz
					{
						OhmschesGesetzActive = true;
						HeadlineCalculatorTyps = false;
						GeometryButton = true;
					}
					
				}
				if (OhmschesGesetzActive == true)
				{
					OhmschesGesetzButton = true;
					int Hochzahl = 0;
					rechner.OhmschesGesetz();
					if (rechner.ReturnSpannung == true)
						ImGui::Text("%lf*10^%d", rechner.Spannung, rechner.Erg_Hochzahl);
					if (rechner.ReturnStromstaerke == true)
						ImGui::Text("%lf*10^%d", rechner.Stromstaerke, rechner.Erg_Hochzahl);
					if (rechner.ReturnWiderstand == true)
						ImGui::Text("%lf*10^%d", rechner.Widerstand, rechner.Erg_Hochzahl);

				}
				
				ImGui::SetCursorPos(ImVec2{ ImGui::GetContentRegionAvailWidth() / 2 - 60,130 });
				if (GeometryButton == false)
				{

					if (ImGui::Button(text[4].c_str())==true) //Geometry
					{
						GeometryActive = true;
						HeadlineCalculatorTyps = false;
						OhmschesGesetzButton = true;

					}
				}
				if (GeometryActive == true)
				{
					GeometryButton = true;
					int Hochzahl = 0;
					rechner.Rechteck();

					if (rechner.Rechteckberechnungen == true)
					{
						ImGui::Text("%s = %lf", text[5].c_str(), rechner.laenge2);
						ImGui::Text("%s = %lf", text[6].c_str(), rechner.breite2);
						ImGui::Text("%s= %lf", text[7].c_str(), rechner.Flaecheninhalt);
						ImGui::Text("%s = %lf", text[8].c_str(), rechner.Umfang);
						ImGui::Text("%s = %lf", text[9].c_str(), rechner.Diagonale);
						ImGui::Text("%s = %lf", text[10].c_str(), rechner.Umkreisradius);
						ImGui::Text("Innenkreiswinkel = Alpha = Betha = Gamma = delta = 90°");
						rechner.Klicktime = dt;
						ImGui::SetCursorPos(ImVec2{ 900,600 });
						if (ImGui::Button("Simulation"))
						{
							Simulation = true;
						}
					}
				}
				if (Simulation == true)
				{
					ImGui::Begin("Simulation");
					ImVec2 p = ImGui::GetCursorScreenPos();
					ImGui::GetWindowDrawList()->AddRectFilled({ p.x, p.y }, { p.x + 400.0f, p.y + 200.0f }, IM_COL32_WHITE);
					ImGui::GetWindowDrawList()->AddText(ImGui::GetFont(), ImGui::GetFontSize() * 2.0f, ImVec2(p.x + 200.0f, p.y + 200.0f), IM_COL32(255, 255, 255, 255), "x", NULL, 0.0f);
					ImGui::GetWindowDrawList()->AddText(ImGui::GetFont(), ImGui::GetFontSize() * 2.0f, ImVec2(p.x + 410.0f, p.y + 66.6f), IM_COL32(255, 255, 255, 255), "y", NULL, 0.0f);
					ImGui::End();
				}
			}
		}
		void ChildWindow()
		{
			ImGui::BeginChild("Child", ImVec2{ 73.5f, 0.0f }, true);

			check = { calculationState,settingsState,helpState,CalculatorIconButton,SettingIconButton,HelpIconButton };
			ImageButton("Calculator", check, CalculatorIcon, i1, i2, i3);
			check = { settingsState,helpState,calculationState,SettingIconButton,HelpIconButton,CalculatorIconButton };
			ImageButton("Setting", check, SettingIcon, i2, i3, i1);
			check = { helpState,calculationState,settingsState,HelpIconButton,CalculatorIconButton,SettingIconButton };
			ImageButton("Help", check, HelpIcon, i3, i1, i2);

			ImGui::EndChild();

		}

		void LogConsole()
		{

			ImGui::Begin("Log Console", 0, ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize);
			ImGui::SetWindowSize(ImVec2{ 500, 500 });
			ImGui::Text("!Attention please!");
			ImGui::Text("FPS: %.2f", ImGui::GetIO().Framerate);
			ImGui::End();
		}
		
	};
