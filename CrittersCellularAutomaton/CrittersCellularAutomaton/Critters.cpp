
#include "Critters.h"
#include "ColorEvolution.h"
#include <stdlib.h>

void Critters::GenerateBySeed(int(&cells)[k_cells_size][k_cells_size])
{
    // 执行步数恢复到初始状态
    m_step_cnt = 0;

    for (int row = 0; row < k_cells_size; row++)
    {
        for (int col = 0; col < k_cells_size; col++)
        {
            m_cells[row][col].self_state = cells[row][col] == 0 ? StateCell::Dead : StateCell::Alive;
            if (row < k_cells_size - 1)
            {
                ///---------------------------------------------------- 下方
                m_cells[row][col].down_state = cells[row + 1][col] == 0 ? StateCell::Dead : StateCell::Alive;

                if (col < k_cells_size - 1)
                {
                    ///------------------------------------------------ 右下
                    m_cells[row][col].dr_state = cells[row + 1][col + 1] == 0 ? StateCell::Dead : StateCell::Alive;
                }
                else
                {
                    ///------------------------------------------------ 右下
                    m_cells[row][col].dr_state = cells[row + 1][0] == 0 ? StateCell::Dead : StateCell::Alive;
                }
            }
            else
            {
                ///---------------------------------------------------- 下方
                m_cells[row][col].down_state = cells[0][col] == 0 ? StateCell::Dead : StateCell::Alive;


                if (col < k_cells_size - 1)
                {
                    ///------------------------------------------------ 右下
                    m_cells[row][col].dr_state = cells[0][col + 1] == 0 ? StateCell::Dead : StateCell::Alive;
                }
                else
                {
                    ///------------------------------------------------ 右下
                    m_cells[row][col].dr_state = cells[0][0] == 0 ? StateCell::Dead : StateCell::Alive;
                }
            }

            if (col < k_cells_size - 1)
            {
                ///---------------------------------------------------- 右方
                m_cells[row][col].right_state = cells[row][col + 1] == 0 ? StateCell::Dead : StateCell::Alive;
            }
            else
            {
                ///---------------------------------------------------- 右方
                m_cells[row][col].right_state = cells[row][0] == 0 ? StateCell::Dead : StateCell::Alive;
            }
        }
    }
}

void Critters::Evolution()
{
	///---------------------------------------------------------------- 记录状态是否发生变化
	char index_change[k_cells_size][k_cells_size] = { 0 };
	int sum;
	int start_idx = m_odd_flag ? 0 : 1;

	for (int row = start_idx; row < k_cells_size; row+= 2)
	{
		for (int col = start_idx; col < k_cells_size; col+= 2)
		{
			int row_down = (row + 1) % k_cells_size;
			int col_right = (col + 1) % k_cells_size;
			// 计算周围活着的生命数量
			sum = m_cells[row][col].around();

			// 计算当前位置的生命状态
			switch (sum)
			{
			case 0:
			case 4:
				break;
			case 1:
			case 3:
			{
				if ((m_odd_flag) ^ (sum == 3))
				{
					if (m_cells[row][col].self_state != m_cells[row][col].dr_state)
					{
						index_change[row][col] = m_cells[row][col].dr_state == StateCell::Alive ? 1 : -1;
						index_change[row_down][col_right] = m_cells[row][col].self_state == StateCell::Alive ? 1 : -1;
					}
					
					if (m_cells[row][col].down_state != m_cells[row][col].right_state)
					{
						index_change[row_down][col] = m_cells[row][col].right_state == StateCell::Alive ? 1 : -1;
						index_change[row][col_right] = m_cells[row][col].down_state == StateCell::Alive ? 1 : -1;
					}
				}
				break;
			}
			case 2:
			{
				index_change[row][col] = m_cells[row][col].self_state != StateCell::Alive ? 1 : -1;
				index_change[row_down][col] = m_cells[row][col].down_state != StateCell::Alive ? 1 : -1;
				index_change[row][col_right] = m_cells[row][col].right_state != StateCell::Alive ? 1 : -1;
				index_change[row_down][col_right] = m_cells[row][col].dr_state != StateCell::Alive ? 1 : -1;
				break;
			}
			default:
				break;
			}
		}
	}
	
    ///---------------------------------------------------------------- 更新发生变化的细胞周围的细胞的存储数据
    for (int row = 0; row < k_cells_size; row++)
    {
        for (int col = 0; col < k_cells_size; col++)
        {
            int row_up = (row - 1) < 0 ? (k_cells_size - 1) : (row - 1);
            int col_left = (col - 1) < 0 ? (k_cells_size - 1) : (col - 1);

            if (index_change[row][col] != 0)
            {
                ///------------------------------------------------ 更新自己
                m_cells[row][col].self_state = (index_change[row][col] > 0) ? StateCell::Alive : StateCell::Dead;

                ///------------------------------------------------ 更新正上方的细胞
                m_cells[row_up][col].down_state = (index_change[row][col] > 0) ? StateCell::Alive : StateCell::Dead;

                ///-------------------------------------------- 更新左上方的细胞
                m_cells[row_up][col_left].dr_state = (index_change[row][col] > 0) ? StateCell::Alive : StateCell::Dead;

                ///------------------------------------------------ 更新正左方的细胞
                m_cells[row][col_left].right_state = (index_change[row][col] > 0) ? StateCell::Alive : StateCell::Dead;
            }
        }
    }
}

/// 创建一个细胞以方形分布的世界
void Critters::SquareSeed()
{
    int seed[k_cells_size][k_cells_size] = { 0 };

    for (int x = 0; x < k_cells_size; x++)
        seed[x][0] = seed[x][k_cells_size - 1] = 1;

    for (int y = 0; y < k_cells_size; y++)
        seed[0][y] = seed[k_cells_size - 1][y] = 1;

    GenerateBySeed(seed);
    m_color_evolution.SetColorValue(GREEN);
}

/// 创建一个细胞随机分布的世界
void Critters::RandomSeed()
{
    int seed[k_cells_size][k_cells_size] = { 0 };

    for (int x = 0 + 50; x < k_cells_size - 50; x++)
        for (int y = 0 + 50; y < k_cells_size - 50; y++)
            seed[x][y] = rand() % 2;

    GenerateBySeed(seed);
    m_color_evolution.SetColorValue(rand() % k_color_max_value, rand() % k_color_max_value, rand() % k_color_max_value);
}

void Critters::SpecialSeed()
{
    extern int g_special_seed[k_cells_size][k_cells_size];
    extern COLORREF g_special_color;

    GenerateBySeed(g_special_seed);
    m_color_evolution.SetColorValue(g_special_color);
}

void Critters::Forward()
{
    ///------------------------------------------------ 正向变化
    m_step_cnt++;
    m_odd_flag = m_step_cnt % 2 != 0;
    Evolution();
    m_color_evolution.Evolution(this, true);
}

void Critters::Backward()
{
    ///------------------------------------------------ 反向变化
    m_odd_flag = m_step_cnt % 2 != 0;
    m_step_cnt--;
    Evolution();
    m_color_evolution.Evolution(this, false);
}

bool Critters::GetCellIsAlive(int row, int col)
{
    return m_cells[row][col].self_state == StateCell::Alive;
}

int Critters::GetStepCount()
{
    return m_step_cnt;
}

COLORREF Critters::GetColorValue()
{
    return m_color_evolution.GetColorValue();
}
