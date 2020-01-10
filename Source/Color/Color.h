#pragma once

namespace Color{

	constexpr unsigned int Color_White = 0xFFFFFFFF;	//”’
	constexpr unsigned int Color_Black = 0xFF000000;	//•
	constexpr unsigned int Color_Red = 0xFFFF0000;		//Ô
	constexpr unsigned int Color_Green = 0xFF00FF00;	//—Î
	constexpr unsigned int Color_Blue = 0xFF0000FF;		//Â

	using Byte = unsigned char;	//‚±‚±‚Åg—p‚µ‚½‚¢‚ª‚½‚ß‚É’è‹`
	unsigned int GetColor(Byte r, Byte g, Byte b, Byte a = 255);

}