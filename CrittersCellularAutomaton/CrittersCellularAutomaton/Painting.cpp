#include "Painting.h"
#include "Defines.h"
#include "Critters.h"
#include <time.h>
#include <cstdio>

const int img_size = 3;

// 初始化
void Painting::Init()
{
	// 创建绘图窗口
	initgraph(1280, 900);

	// 设置随机种子
	srand((unsigned)time(NULL));

	// 调整世界图案的大小
	Resize(&imgLive, img_size, img_size);
	Resize(&imgEmpty, img_size, img_size);

	// 绘制有生命世界的图案
	SetWorkingImage(&imgLive);
	setcolor(GREEN);
	setfillstyle(GREEN);
	fillellipse(0, 0, img_size - 1, img_size - 1);

	// 绘制无生命世界的图案
	SetWorkingImage(&imgEmpty);
	setcolor(DARKGRAY);
	rectangle(1, 1, img_size - 2, img_size - 2);

	// 恢复对默认窗口的绘图
	SetWorkingImage(NULL);

	// 输出简单说明
	setfont(24, 0, L"黑体");
	outtextxy(254, 18, L"生 命 游 戏 - 变 体");
	RECT r = { 920, 180, 1060, 620 };
	setfont(16, 0, L"宋体");
	drawtext(L"生命游戏简介：\n　　生命游戏包括一个二维矩形世界，这个世界中的每个方格居住		"
				"着一个活着的或死了的细胞。一个细胞在下一个时刻生死取决于右下相邻三个方格中活着的		细胞的数量。\n"
				"游戏控制：\n 0-9: 调节速度(慢--快)\n ESC: 退出\n空格: 		暂停|继续\n   S: 创建细胞以方形分布的世界\n"
				"   R: 创建细胞随机分布的世界\n   B: 创建细胞特定分布的世界\n   T: 进入测试模式，开始计时\n   C: 反转进化方向",
		&r, DT_WORDBREAK);
}

// 绘制世界
void Painting::PaintWorld(Critters* critters)
{
	ChangeCellColor(critters->GetColorValue());

	for (int x = 0; x < k_cells_size; x++)
		for (int y = 0; y < k_cells_size; y++)
			putimage(20 + y * img_size, 60 + x * img_size, critters->GetCellIsAlive(x, y) ? &imgLive : &imgEmpty);

}


// 绘制测试数据
void Painting::PaintTestData(Critters* critters, DOUBLE time, INT test_count)
{
	TCHAR buffer_count[100], buffer_time[100]; // 确保缓冲区足够大

	setfillstyle(SOLID_FILL, BLACK); // 假设背景色为黑色
	bar(920, 600, 920 + 200, 600 + 200); // 用背景色填充文本区域
	_stprintf(buffer_count, _T("已执行次数: %d"), test_count);
	_stprintf(buffer_time, _T("已执行时间: %.6f秒"), time);
	setcolor(WHITE);
	setfont(16, 0, L"宋体");
	outtextxy(920, 600, buffer_count);
	outtextxy(920, 620, buffer_time);
	
	PaintWorld(critters);
}

void Painting::Deinit()
{
	closegraph();
}

void Painting::ChangeCellColor(COLORREF color)
{
	SetWorkingImage(&imgLive);
	setcolor(color);
	setfillstyle(color);
	fillellipse(0, 0, img_size - 1, img_size - 1);

	SetWorkingImage(NULL);
}
