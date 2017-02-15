//
// ScatterCircle.h
//
// The header file for Scatter Circle Brush. 
//

#ifndef SCATTERCIRCLE_H
#define SCATTERCIRCLE_H

#include "CircleBrush.h"
#include <math.h>

class ScatterCircle : public CircleBrush
{
public:
	ScatterCircle(ImpressionistDoc* pDoc = NULL, char* name = NULL);

	void BrushBegin(const Point source, const Point target);
	void BrushMove(const Point source, const Point target);
	void BrushEnd(const Point source, const Point target);
	char* BrushName(void);
};

#endif#pragma once
