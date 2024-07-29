#pragma once


#include "Defines.h"
#include <graphics.h>
#include "ColorEvolution.h"

// ����ϸ��Ԫ������״̬��������
enum class StateCell
{
	Dead = 0,
	Alive,
};

// ����ϸ��Ԫ�ṹ�壬������ϸ�������ģʽ
//	   selfState -- rightState
//	       |      \
//	   downState    drState
struct SingleCell
{
	StateCell self_state;
	StateCell down_state;
	StateCell right_state;
	StateCell dr_state;

	int around()
	{
		return static_cast<int>(self_state) +
			static_cast<int>(down_state) +
			static_cast<int>(right_state) +
			static_cast<int>(dr_state);
	}
};

// Ԫ���Զ��� - С�������
// ��ÿһ�����裬���ж�Ӧ�任
// 
// ������ʱ������Ļ����Ǵ�0��ʼ�ģ�ż�����Ǵ�1��ʼ
// ��ż������ʱ������Χ�ڵĴ��ϸ������Ϊ0,1��4ʱ��ά�ֲ���
// ����Χ�ڵĴ��ϸ������Ϊ2ʱ��������ÿ��Ԫ��״̬��ת
// ����Χ�ڵĴ��ϸ������Ϊ3ʱ��������״̬������ת180��
// 
// ����������ʱ������Χ�ڵĴ��ϸ������Ϊ0,3��4ʱ��ά�ֲ���
// ����Χ�ڵĴ��ϸ������Ϊ2ʱ��������ÿ��Ԫ��״̬��ת
// ����Χ�ڵĴ��ϸ������Ϊ1ʱ��������״̬������ת180��
// 
// ����ɼ� https://web.archive.org/web/20160305015510/http://www.cise.ufl.edu/~skoehler/critters/index.html
// 

class Critters
{
private:
	SingleCell m_cells[k_cells_size][k_cells_size] = { StateCell::Dead };
	int m_step_cnt = 0;
	bool m_odd_flag = true;
	ColorEvolution m_color_evolution;

private:
	void GenerateBySeed(int(&cells)[k_cells_size][k_cells_size]);
	void Evolution();

public:
	// �������ɸ���Ԫ����ʼ״̬������
	void SquareSeed();
	void RandomSeed();
	void SpecialSeed();

public:
	// ����ִ�в���
	void Forward();
	// ����ִ�в���
	void Backward();

public:
	// ��ȡָ��λ��Ԫ���Ĵ��״̬
	bool GetCellIsAlive(int row, int col);
	// ��ȡ���Ԫ������ɫ
	COLORREF GetColorValue();
	int GetStepCount();
};
