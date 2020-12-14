 ////////////////////////////////////\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\
//|	Owner		: Matthias Karasowski									|\\
\\|				https://github.com/MkBiomedicalSolutions/MkCalculator	|//
//|	Copyright	: MkBiomedicalSolutions									|\\
\\|				https://www.mksolutions.at/								|//
//| Filename	: Main.cpp												|\\
\\|	Version		: 1.0 													|//
//|	Date		: 30.11.2020											|\\
\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\///////////////////////////////////////
 ///////////////////////////////////\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\
//| Source		:														|\\
\\|																		|//
//|				ImGui		:https://github.com/ocornut/imgui			|\\
\\|				glad		:											|//
//|				GLFW		:https://www.glfw.org/						|\\
\\|				stb_image	:https://github.com/nothings/stb			|//
//|																		|\\
\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\///////////////////////////////////////

#include "Solution.h"

int main(int argc, char* argv[])
{
	Solution solution;

	solution.Run();

	return EXIT_SUCCESS;
}
//		Copyright MkBiomedicalSolutions 2020 ALL RIGHTS RESERVED		\\