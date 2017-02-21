//
// FilterSharpenBrush.h
//
// The header file for Line Brush. 
//

#ifndef SHARPENBRUSH_H
#define SHARPENBRUSH_H

#include "ImpBrush.h"
#include <cmath>

class SharpenBrush : public ImpBrush
{
public:
	SharpenBrush(ImpressionistDoc* pDoc = NULL, char* name = NULL);

	void BrushBegin(const Point source, const Point target);
	void BrushMove(const Point source, const Point target);
	void BrushEnd(const Point source, const Point target);
	char* BrushName(void);
	void applyFilter(int x, int y, float*buffer, int index);
private:
	int filter[9];
};

#endif