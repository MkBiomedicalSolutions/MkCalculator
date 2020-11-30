#define STB_IMAGE_IMPLEMENTATION
#include "Util/Rechner.h"
#include <imgui.h>
#include <iostream>
#include <array>



int main()
{
	Util::Window window(1280, 720, "Window");
	Util::Rechner rechner;
	Util::ImGuiInit(window);

	//auto& colors = ImGui::GetStyle().Colors;



	bool selected = false;
	bool settingsopen = false;
	float Spannung = 0;
	float Widerstand = 0;
	float Stromstaerke = 0;
	float ergebnis = 0;
	std::array<float, 3> bufferNew, bufferOld;
	bufferNew = { 0,0,0 };
	bufferOld = { 0,0,0 };


	window.SetIcon("MenueIcon.png");

	while (window.isOpen())
	{

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
		//float ergebnis = rechner.OhmschesGesetz(Spannung, Widerstand, Stromstaerke, bufferNew, bufferOld);
		//ImGui::Checkbox("Matze", &selected);
		//ImGui::Text("Das Ergebnis ist: %f", ergebnis);
		ImGui::End();
		ImGui::ShowDemoWindow();
		Util::ImGuiEndFrame();
	}

	

	Util::ImGuiShutdown();
	return 0;

}