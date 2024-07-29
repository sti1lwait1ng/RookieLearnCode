#pragma once


#include "Defines.h"
#include <graphics.h>
#include "ColorEvolution.h"

// 定义细胞元的两种状态，死或生
enum class StateCell
{
	Dead = 0,
	Alive,
};

// 定义细胞元结构体，采用四细胞邻域的模式
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

// 元胞自动机 - 小动物规则
// 在每一个步骤，进行对应变换
// 
// 奇数步时，邻域的划分是从0开始的，偶数步是从1开始
// 在偶数步骤时，邻域范围内的存活细胞数量为0,1或4时，维持不变
// 邻域范围内的存活细胞数量为2时，邻域内每个元胞状态反转
// 邻域范围内的存活细胞数量为3时，邻域内状态整体旋转180度
// 
// 在奇数步骤时，邻域范围内的存活细胞数量为0,3或4时，维持不变
// 邻域范围内的存活细胞数量为2时，邻域内每个元胞状态反转
// 邻域范围内的存活细胞数量为1时，邻域内状态整体旋转180度
// 
// 详情可见 https://web.archive.org/web/20160305015510/http://www.cise.ufl.edu/~skoehler/critters/index.html
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
	// 用于生成各种元胞初始状态的种子
	void SquareSeed();
	void RandomSeed();
	void SpecialSeed();

public:
	// 正向执行步骤
	void Forward();
	// 反向执行步骤
	void Backward();

public:
	// 获取指定位置元胞的存活状态
	bool GetCellIsAlive(int row, int col);
	// 获取存活元胞的颜色
	COLORREF GetColorValue();
	int GetStepCount();
};
