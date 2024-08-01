///////////////////////////////////////////////////
// 程序名称：小动物元胞自动机
// 编译环境：Visual Studio 2019
// 作　　者：xlf
// 最后修改：2024-7-11
//


#include <graphics.h>
#include <conio.h>
#include <time.h>
#include <stdio.h>
#include "Defines.h"
#include "Painting.h"
#include "Critters.h"

#include<iostream>
#include<fstream>

// 主函数
int main()
{
	Painting *painting = new Painting();
	Critters *critters = new Critters();
	int speed = 500;			// 游戏速度（毫秒）
	bool evolution_direction = true;

	bool test_mode = false;
	LARGE_INTEGER frequency;        // 时钟频率
	LARGE_INTEGER startTime;        // 开始时间
	LARGE_INTEGER endTime;          // 结束时间

	painting->Init();
	critters->SquareSeed();	// 产生默认的细胞以方形分布的世界

	QueryPerformanceFrequency(&frequency);
	while (true)
	{
		if (_kbhit() || speed == 900)
		{
			char c = _getch();

			if (c == ' ' && speed != 900)
				c = _getch();

			if (c >= '0' && c <= '9')
				speed = ('9' - c) * 100;

			switch (c)
			{
			case 's':
			case 'S':
				critters->SquareSeed();	// 产生默认的细胞以方形种子起始分布的世界
				break;

			case 'r':
			case 'R':
				critters->RandomSeed();	// 产生默认的细胞以随机种子起始分布的世界
				break;

			case 'b':
			case 'B':
				critters->SpecialSeed();	// 产生默认的细胞以特殊种子起始分布的世界
				break;

            case 'c':
            case 'C':
				evolution_direction = !evolution_direction;	// 反转进化过程
                break;

			case 't':
			case 'T':
				test_mode = true;							// 进入测试模式，进化十万次
				critters->SpecialSeed();					// 产生默认的细胞以特殊种子起始分布的世界
				painting->PaintTestData(critters, 0, 0);	// 输出进化结果的函数
				QueryPerformanceCounter(&startTime);		// 此处开始计时
				break;

			case VK_ESCAPE:
				painting->Deinit();
				delete painting;
				delete critters;
				return 0;
			}
		}

		if (test_mode)										// 测试模式时，运行的代码，运行结束后，速度归零
		{
			critters->Forward();
			QueryPerformanceCounter(&endTime);

			if (critters->GetStepCount() % 1000 == 0 && critters->GetStepCount() == k_test_times)		// 测试模式时，中途的显示过程，可以改为最后显示一次，减少耗时
			{
				painting->PaintTestData(critters, (double)(endTime.QuadPart - startTime.QuadPart) / (double)frequency.QuadPart, critters->GetStepCount());//绘制测试脚本世界
			}

			if (critters->GetStepCount() == k_test_times)
			{
				test_mode = false;
				speed = 900;
			}
		}
		else
		{
			painting->PaintWorld(critters);//绘制世界
			if (evolution_direction)
			{
				critters->Forward();
			}
			else
			{
				critters->Backward();
			}

			if (speed != 900)		// 速度为 900 时，为按任意键单步执行
				Sleep(speed);
		}
	}


	painting->Deinit();
	delete painting;
	delete critters;

	return 0;
}
