#include "Color.h"

/// <summary>
/// 引数の値に応じた色情報を返す
/// </summary>
/// <param name="r">赤</param>
/// <param name="g">緑</param>
/// <param name="b">青</param>
/// <param name="a">アルファ値</param>
/// <returns>まとめた色情報</returns>
unsigned int Color::GetColor(Byte r, Byte g, Byte b, Byte a){

	unsigned int color = (unsigned int)(((1 << 24) * a) + ((1 << 16) * r) + ((1 << 8) * g) + ((1 << 0) * b));

	return color;
}