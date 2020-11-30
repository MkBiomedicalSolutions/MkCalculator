#pragma once

#include <imgui.h>
#include <array>

#include "TextureLoader.h"
#include "Util/ImGuiUtil.h"


namespace Util {

	class Rechner{
	private:

		unsigned int CalculatorIcon;
		unsigned int SettingIcon;
		unsigned int HelpIcon;
		float childCol[4] = { 0.176f, 0.169f, 0.329f, 1.0f };//default Child Background 
		bool closeWindow = false;

	public:
		Rechner() 
		{
			CalculatorIcon = Util::LoadTexture("CalculationIcon.png");
			SettingIcon = Util::LoadTexture("SettingIcon.png");
			HelpIcon = Util::LoadTexture("HelpIcon.png");
		}


		float OhmschesGesetz(float Spannung, float Widerstand, float Stromstaerke, std::array<float, 3> bufferNew, std::array<float, 3> bufferOld){

			ImGui::SameLine();
			ImGui::SetNextItemWidth(200);
			ImGui::DragFloat("Spannung", &Spannung, 0.5f);
			ImGui::SameLine();
			ImGui::SetNextItemWidth(200);
			ImGui::DragFloat("Widerstand", &Widerstand, 0.5f);
			ImGui::SameLine();
			ImGui::SetNextItemWidth(200);
			ImGui::DragFloat("Stromstaerke", &Stromstaerke, 0.5f);

			bufferNew = { Stromstaerke, Spannung, Widerstand };

			if (((Spannung != bufferOld[1]) && (Widerstand != bufferOld[2])) || ((Spannung != bufferOld[1]) && (Stromstaerke != bufferOld[0])) || ((Widerstand != bufferOld[2]) && (Stromstaerke != bufferOld[0])))
			{
				if ((bufferOld[1] != bufferNew[1]) && (bufferOld[2] != bufferNew[2]))
				{
					bufferOld = bufferNew;
					return Spannung / Widerstand;
				}

				if ((bufferOld[0] != bufferNew[0]) && (bufferOld[1] != bufferNew[1]))
				{
					bufferOld = bufferNew;
					return Spannung / Stromstaerke;
				}

				if ((bufferOld[0] != bufferNew[0]) && (bufferOld[2] != bufferNew[2]))
				{
					bufferOld = bufferNew;
					return Widerstand * Stromstaerke;
				}
			}
		}
		void SettingsChildWindow(float childCol[]) {
			ImGui::ColorEdit4("Child Background", childCol);
			ImGui::GetStyle().Colors[ImGuiCol_ChildBg] = ImVec4{ childCol[0], childCol[1], childCol[2], childCol[3] };
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
				if (ImGui::BeginMenu("Settings", &settingsopen)) {
					SettingsChildWindow(childCol);
					ImGui::EndMenu();
				}
				if (ImGui::BeginMenu("About"))

					ImGui::EndMenu();
				if (ImGui::BeginMenu("Help"))

					ImGui::EndMenu();
			}
			ImGui::EndMenuBar();
		}
		bool CloseWindow() 
		{
			return closeWindow;
		}

		void ChildWindow() {

			ImGui::BeginChild("Child", ImVec2{ 73.5f, 0.0f }, true);
			ImGui::ImageButton((ImTextureID)CalculatorIcon, { 50.0f, 50.0f }, ImVec2{ 0, 1 }, ImVec2{ 1, 0 });

			ImGui::ImageButton((ImTextureID)SettingIcon, { 50.0f, 50.0f }, ImVec2{ 0, 1 }, ImVec2{ 1, 0 });
			ImGui::ImageButton((ImTextureID)HelpIcon, { 50.0f, 50.0f }, ImVec2{ 0, 1 }, ImVec2{ 1, 0 });
			ImGui::EndChild();
		}

	};
}