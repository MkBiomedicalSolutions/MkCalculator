///////////////////////////////////\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\
//|	Owner       : Matthias Karasowski                                   |\\
\\|             https://github.com/MkBiomedicalSolutions/MkCalculator   |//
//|	Copyright   : MkBiomedicalSolutions                                 |\\
\\|             https://www.mksolutions.at/	                            |//
//| Filename    : Rechner.cpp                                           |\\
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

#include "Rechner.h"



	void Rechner::OhmschesGesetz()
	{
		Array = Rhf.ComboList(200, 100, 200, "##9901", &Spannung, 100, "V [Volt] Spannung", &currentItem, listbox_items, U_Hochzahl);
		Spannung = Array[0];
		U_Hochzahl = Array[1];
		Array = Rhf.ComboList(200, 200, 200, "##9902", &Widerstand, 100, "R [Ohm] Widerstand", &currentItem1, listbox_items1, R_Hochzahl);
		Widerstand = Array[0];
		R_Hochzahl = Array[1];
		Array = Rhf.ComboList(200, 300, 200, "##9903", &Stromstaerke, 100, "A [Ampere] Stromstaerke", &currentItem2, listbox_items2, I_Hochzahl);
		Stromstaerke = Array[0];
		I_Hochzahl = Array[1];
		Array = Rhf.ComboList(200, 400, 200, "##9904", &Leistung, 100, "P [Watt] Leistung", &currentItem3, listbox_items3, P_Hochzahl);
		Leistung = Array[0];
		P_Hochzahl = Array[1];

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
				currentItem2 = Rhf.ExponentToCurrentItem(Erg_Hochzahl);
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
				currentItem1 = Rhf.ExponentToCurrentItem(Erg_Hochzahl);
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
				currentItem = Rhf.ExponentToCurrentItem(Erg_Hochzahl);
			}
			if ((bufferOld[3] != bufferNew[3]) && (bufferOld[0] != bufferNew[0]))
			{
				bufferOld = bufferNew;
				Spannung = Leistung / Stromstaerke;
				Widerstand = Leistung / (Stromstaerke * Stromstaerke);

				if (P_Hochzahl < 0 && I_Hochzahl>0) {
					Erg_Hochzahl = P_Hochzahl + I_Hochzahl;
				}
				else {
					Erg_Hochzahl = P_Hochzahl - I_Hochzahl;
				}
				currentItem = Rhf.ExponentToCurrentItem(Erg_Hochzahl);
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
				currentItem = Rhf.ExponentToCurrentItem(Erg_Hochzahl);
			}
			if ((bufferOld[3] != bufferNew[3]) && (bufferOld[1] != bufferNew[1]))
			{
				bufferOld = bufferNew;
				Widerstand = (Spannung * Spannung) / Leistung;
				Stromstaerke = Leistung / Spannung;

				if (P_Hochzahl < 0 && R_Hochzahl>0) {
					Erg_Hochzahl = P_Hochzahl + R_Hochzahl;
				}
				else {
					Erg_Hochzahl = P_Hochzahl - R_Hochzahl;
				}
				currentItem = Rhf.ExponentToCurrentItem(Erg_Hochzahl);
			}
		}
	}

	void Rechner::Rechteck()
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
			Diagonale = sqrt((laenge * laenge) + (breite * breite));
			Umkreisradius = Diagonale / 2;
			//Innenwinkel = 90;
			Rechteckberechnungen = true;
			laenge2 = laenge;
			breite2 = breite;
			laenge = 0;
			breite = 0;
		}
		ImGui::SameLine();
		ItemsRechteck = { laenge2,breite2,Flaecheninhalt,Umfang,Diagonale,Umkreisradius };
		Rhf.Save(200, 50, Klicktime, ItemsRechteck, ItemNamesRechteck);
	
	}
	
//		Copyright MkBiomedicalSolutions 2020 ALL RIGHTS RESERVED		\\