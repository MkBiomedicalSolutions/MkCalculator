///////////////////////////////////\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\
//|	Owner       : Matthias Karasowski                                   |\\
\\|             https://github.com/MkBiomedicalSolutions/MkCalculator   |//
//|	Copyright   : MkBiomedicalSolutions                                 |\\
\\|             https://www.mksolutions.at/	                            |//
//| Filename    : Rechnerhilfsfunktionen.cpp                            |\\
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

#include <fstream>
#include <iostream>
#include <array>

#include "Rechnerhilfsfunktionen.h"

char* Rechnerhilfsfunktionen::ComboList(int x, int y, int InputFieldWidth, std::string ID, float *Item, int ComboWidth, std::string Name, const char* CurrentItem, const char* ItemList[], int OutputHochzahl)
{
	ImGui::SetCursorPos(ImVec2{ (float)x,(float)y });
	ImGui::SetNextItemWidth(InputFieldWidth);
	ImGui::DragFloat(ID.c_str(), Item, 0.5f);
	ImGui::SameLine();
	ImGui::PushItemWidth(ComboWidth);

	if (ImGui::BeginCombo(Name.c_str(), CurrentItem)) // The second parameter is the label previewed before opening the combo.IM_ARRAYSIZE(ItemList)
	{
		for (int n = 0; n < sizeof(&ItemList); n++)
		{
			bool is_selected = (CurrentItem == ItemList[n]);
			if (ImGui::Selectable(ItemList[n], is_selected))
				CurrentItem = ItemList[n];
			if (is_selected)
				ImGui::SetItemDefaultFocus();   // Set the initial focus when opening the combo (scrolling + for keyboard navigation support in the upcoming navigation branch)
		}
		ImGui::EndCombo();
	}

	OutputHochzahl = CurrentItemToExponent(*CurrentItem);

	char Return[] = { *Item,OutputHochzahl};

	return Return;
}

int Rechnerhilfsfunktionen::CurrentItemToExponent(int Item)
{
	if (itemOld != Item)
	{
		itemOld = Item;
		if (itemOld < 4)
		{
			if (itemOld == 0)
				Hochzahl = 13;
			if (itemOld == 1)
				Hochzahl = 9;
			if (itemOld == 2)
				Hochzahl = 6;
			if (itemOld == 3)
				Hochzahl = 3;
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

int Rechnerhilfsfunktionen::ExponentToCurrentItem(int Hochzahl2)
{
	int Item = 0;
	if (itemOld != Hochzahl2)
	{
		itemOld = Hochzahl2;
		if (itemOld > 0)
		{
			if (itemOld == 13)
				Item = 0;
			if (itemOld == 9)
				Item = 1;
			if (itemOld == 6)
				Item = 2;
			if (itemOld == 3)
				Item = 3;
		} 
		if (itemOld == 0) //4 = 10^1
			Item = 4;
		if (itemOld < 0)
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

void Rechnerhilfsfunktionen::Save(int x, int y, char* Klicktime, std::array<float, 6>& Items, std::array<const char*, 6> ItemNames)
{
	if (ImGui::Button("Save", ImVec2{ (float)x, (float)y }))
	{
		std::ofstream myfile("Results.txt", std::ios::out | std::ios::app);
	
		if (myfile.is_open())
		{
			myfile << "---------------------------------------------\n";
			myfile << "Ergebnisse vom: " << Klicktime << "\n";

			for (int k = 0; k < ItemNames.size(); k++)
			{
				myfile << ItemNames[k] << Items[k] << "\n";
			}
			myfile.close();
		}
		else std::cout << "Unable to open file" << std::endl;		
	}
}

//     Copyright MkBiomedicalSolutions 2020 ALL RIGHTS RESERVED      \\