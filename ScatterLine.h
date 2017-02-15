//
// ScatterLine.h
//
// The header file for Scatter Line Brush. 
//

#ifndef SCATTERLINE_H
#define SCATTERLINE_H

#include "LineBrush.h"
#include <math.h>

class ScatterLine : public LineBrush
{
public:
	ScatterLine(ImpressionistDoc* pDoc = NULL, char* name = NULL);

	void BrushBegin(const Point source, const Point target);
	void BrushMove(const Point source, const Point target);
	void BrushEnd(const Point source, const Point target);
	char* BrushName(void);
};

#endif#pragma once
#pragma once
