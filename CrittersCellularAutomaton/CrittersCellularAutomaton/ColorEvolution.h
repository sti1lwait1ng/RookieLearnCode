#pragma once

#include <graphics.h>
#include "Defines.h"

class Critters;
/// ��ɫ�仯���� - ��Ԫ��������ķ��������ƽ����Ϊ���飬ÿһ��Ļ��ŵ�Ԫ������ռ�ȳ���255��������ɫ����ֵ��ÿһ��ֱ����һ����ɫ
class ColorEvolution
{
private:
	/// ������ɫ����ֵ
	int m_red_value = 0;
	int m_green_value = 0;
	int m_blue_value = 0;

	/// ��ɫ�仯����ʹ�� - ������һ���Ԫ����������������ģ�
	int m_red_range = 0;
	int m_green_range = 0;
	int m_blue_range = 0;

	/// ��ɫ�仯����ʹ�� - ������һ����з�Χ
	int m_red_idx = 0;
	int m_green_idx = 0;
	int m_blue_idx = 0;

public:
	ColorEvolution();

public:
	void SetColorValue(COLORREF color);

	void SetColorValue(int red_value, int green_value, int blue_value);

	COLORREF GetColorValue();

	void Evolution(Critters* critters, bool evolution_direction);//����������ϸ���ֲ�
};
