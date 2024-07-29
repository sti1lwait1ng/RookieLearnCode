#pragma once

#include <graphics.h>

class Critters;
class Painting
{
private:
	IMAGE imgLive, imgEmpty;		// 定义活细胞和无细胞区域的图案

protected:
	void ChangeCellColor(COLORREF color);

public:
	void Init();
	void Deinit();
	void PaintWorld(Critters *critters);
	void PaintTestData(Critters* critters, DOUBLE time, INT test_count);
};
