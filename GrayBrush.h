//
// GrayBrush.h
//
// The header file for Point Brush. 
//

#ifndef GRAYBRUSH_H
#define GRAYBRUSH_H

#include "ImpBrush.h"

class GrayBrush : public ImpBrush
{
public:
	GrayBrush(ImpressionistDoc* pDoc = NULL, char* name = NULL);

	void BrushBegin(const Point source, const Point target);
	void BrushMove(const Point source, const Point target);
	void BrushEnd(const Point source, const Point target);
	void grayColor(Point source);
	char* BrushName(void);
};

#endif#pragma once
