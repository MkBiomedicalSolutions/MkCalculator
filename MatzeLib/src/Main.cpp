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

#define STB_IMAGE_IMPLEMENTATION

#include "Solution.h"

void main()
{
	Solution solution;
	std::cout << sizeof(solution) << std::endl;
	solution.Run();
	
}

//		Copyright MkBiomedicalSolutions 2020 ALL RIGHTS RESERVED		\\