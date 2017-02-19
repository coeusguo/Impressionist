//
// SharpenBrush.h
//
// The header file for Sharpen Brush. 
//

#ifndef SHARPENBRUSH_H
#define SHARPENBRUSH_H

#include "ImpBrush.h"

class SharpenBrush : public ImpBrush
{
public:
	SharpenBrush(ImpressionistDoc* pDoc = NULL, char* name = NULL);

	void BrushBegin(const Point source, const Point target);
	void BrushMove(const Point source, const Point target);
	void BrushEnd(const Point source, const Point target);
	char* BrushName(void);

private:
	int filter[3][3];
	void applyFilter(int x,int y,float*** buffer,int row,int col);
};

#endif#pragma once
