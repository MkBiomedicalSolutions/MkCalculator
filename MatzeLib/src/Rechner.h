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



	class Rechner
	{
		
		private:

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

			float laenge = 0;
			float breite = 0;
			float ergebnis = 0;

			bool ScrollToBottom;

			const char* listbox_items[9] = { "   T", "   G", "   M","   k", "   V", "   m", "   u", "   n", "   p" };
			const char* listbox_items1[9] = { "   T", "   G", "   M","   k", "Ohm", "   m", "   u", "   n", "   p" };
			const char* listbox_items2[9] = { "   T", "   G", "   M","   k", "   A", "   m", "   u", "   n", "   p" };
			const char* listbox_items3[9] = { "   T", "   G", "   M","   k", "   W", "   m", "   u", "   n", "   p" };
			const char* listbox_items4[11] = {"sm","mi","km","m","ya","ft","dm","in","cm","mm","um"};

			ImGuiTextBuffer Buf;


			std::array<float, 4> bufferNew, bufferOld;

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
	
			bool Save = false;
			bool ReturnSpannung = false;
			bool ReturnWiderstand = false;
			bool RechnerAllowEnter = true;
			bool Rechteckberechnungen = false;
			bool ReturnStromstaerke = false;

			char* Klicktime;

		public:
			Rechner() 
			{
				bufferNew = { 0,0,0,0 };
				bufferOld = { 0,0,0,0 };
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
						myfile << "Ergebnisse vom: " << Klicktime << "\n";
						myfile << "Laenge		:" << laenge2 << "\n";
						myfile << "Breite		:" << breite2 << "\n";
						myfile << "Flaecheninhalt	:" << Flaecheninhalt << "\n";
						myfile << "Umfang		:" << Umfang << "\n";
						myfile << "Diagonale	:" << Diagonale << "\n";
						myfile << "Umkreisradius	:" << Umkreisradius << "\n";

						myfile.close();
					}
					else std::cout << "Unable to open file" << std::endl;
				}


			}
			
			
		
	};

//		Copyright MkBiomedicalSolutions 2020 ALL RIGHTS RESERVED		\\