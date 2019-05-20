#include "Color.h"

unsigned int Color::GetColor(Byte r, Byte g, Byte b, Byte a){

	unsigned int color = (unsigned int)(((1 << 24) * a) + ((1 << 16) * r) + ((1 << 8) * g) + ((1 << 0) * b));

	return color;
}