#pragma once

#include <graphics.h>
#include "Defines.h"

class Critters;
/// 颜色变化规则 - 将元胞的整体的方块从左到右平均分为三块，每一块的活着的元胞数量占比乘以255，就是颜色的数值，每一块分别代表一个颜色
class ColorEvolution
{
private:
	/// 代表颜色的数值
	int m_red_value = 0;
	int m_green_value = 0;
	int m_blue_value = 0;

	/// 颜色变化规则使用 - 代表这一块的元胞总数（包括死活的）
	int m_red_range = 0;
	int m_green_range = 0;
	int m_blue_range = 0;

	/// 颜色变化规则使用 - 代表这一块的列范围
	int m_red_idx = 0;
	int m_green_idx = 0;
	int m_blue_idx = 0;

public:
	ColorEvolution();

public:
	void SetColorValue(COLORREF color);

	void SetColorValue(int red_value, int green_value, int blue_value);

	COLORREF GetColorValue();

	void Evolution(Critters* critters, bool evolution_direction);//传入进化后的细胞分布
};
