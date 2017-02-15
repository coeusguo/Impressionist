//
// ScatterPoint.h
//
// The header file for Point Brush. 
//

#ifndef SCATTERPOINT_H
#define SCATTERPOINT_H

#include "PointBrush.h"

class ScatterPoint : public PointBrush
{
public:
	ScatterPoint(ImpressionistDoc* pDoc = NULL, char* name = NULL);

	void BrushBegin(const Point source, const Point target);
	void BrushMove(const Point source, const Point target);
	void BrushEnd(const Point source, const Point target);
	char* BrushName(void);
};

#endif#pragma once
