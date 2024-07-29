#include "ColorEvolution.h"
#include "Critters.h"

ColorEvolution::ColorEvolution()
{
	// 从左到右分三块，依次是红绿蓝
	m_red_idx = k_cells_size / 3;
	m_green_idx = k_cells_size / 3 * 2;
	m_blue_idx = k_cells_size;

	m_red_range = m_red_idx * k_cells_size;
	m_green_range = (m_green_idx - m_red_idx) * k_cells_size;
	m_blue_range = (m_blue_idx - m_green_idx) * k_cells_size;
}

void ColorEvolution::SetColorValue(COLORREF color)
{
	m_red_value = color & 0x0000FF;
	m_green_value = (color & 0x00FF00) >> 8;
	m_blue_value = (color & 0xFF0000) >> 16;
}

void ColorEvolution::SetColorValue(int red_value, int green_value, int blue_value)
{
	m_red_value = red_value % k_color_max_value;
	m_green_value = green_value % k_color_max_value;
	m_blue_value = blue_value % k_color_max_value;
}

COLORREF ColorEvolution::GetColorValue()
{
	return (m_blue_value << 16 | m_green_value << 8 | m_red_value);
}

void ColorEvolution::Evolution(Critters* critters, bool evolution_direction)
{
	int red_temp = 0, green_temp = 0, blue_temp = 0;

	// 获取每一块活着的元胞数量
	for (int row = 0; row < k_cells_size; row++)
	{
		for (int col = 0; col < k_cells_size; col++)
		{
			if (critters->GetCellIsAlive(row, col))
			{
				if (col < m_red_idx)
				{
					red_temp++;
				}
				else if (col < m_green_idx)
				{
					green_temp++;
				}
				else if (col < m_blue_idx)
				{
					blue_temp++;
				}
			 }
		}
	}

	// 计算更新后的颜色值
	if (evolution_direction)
	{
		m_red_value = (m_red_value + red_temp * k_color_max_value / m_red_range) % k_color_max_value;
		m_green_value = (m_green_value + green_temp * k_color_max_value / m_green_range) % k_color_max_value;
		m_blue_value = (m_blue_value + blue_temp * k_color_max_value / m_blue_range) % k_color_max_value;
	}
	else
	{
		m_red_value = (m_red_value + k_color_max_value - red_temp * k_color_max_value / m_red_range) % k_color_max_value;
		m_green_value = (m_green_value + k_color_max_value - green_temp * k_color_max_value / m_green_range) % k_color_max_value;
		m_blue_value = (m_blue_value + k_color_max_value - blue_temp * k_color_max_value / m_blue_range) % k_color_max_value;
	}

	return;
}
