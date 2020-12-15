///////////////////////////////////\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\
//|	Owner       : Matthias Karasowski                                   |\\
\\|             https://github.com/MkBiomedicalSolutions/MkCalculator   |//
//|	Copyright   : MkBiomedicalSolutions                                 |\\
\\|             https://www.mksolutions.at/	                            |//
//| Filename    : Solution.h                                            |\\
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

#include "Solution.h"
#include "Rechner.h"
#include "Settings.h"



	void Solution::Run() {

		HWND consoleWindow = GetConsoleWindow();
		ShowWindow(consoleWindow, SW_SHOW);

		Util::Window window(1280, 720, "Calculator");
		Util::ImGuiInit(window);

		Rechner rechner;
		Settings settings;

		window.SetIcon("res/Icons/MenueIcon.png");

		while (window.isOpen())
		{
			time_t ttime = time(0);
			char* dt = ctime(&ttime);

			if (settings.CloseWindow())
			{
				window.Close();
			}

			Util::ImGuiBeginFrame();
			window.Update();
			window.Clear();

			ImGui::SetNextWindowPos(ImVec2{ window.GetPosition().x, window.GetPosition().y });
			ImGui::SetNextWindowSize(ImVec2{ window.GetSize().x, window.GetSize().y });
			ImGui::Begin("##9900", 0, ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDecoration);

			settings.ChildWindow();
			settings.MainMenue(settingsopen);

			settings.SettingCalculatorButton();
			settings.SettingSettingButton();
			settings.SettingHelpButton();

			ImGui::SetCursorPos(ImVec2{ ImGui::GetContentRegionAvailWidth() / 2 - 60,700 });
			ImGui::Text("%s", dt);

			ImGui::End();

			//ImGui::ShowDemoWindow();
			Util::ImGuiEndFrame();
		}
		Util::ImGuiShutdown();
	}

//     Copyright MkBiomedicalSolutions 2020 ALL RIGHTS RESERVED       \\
