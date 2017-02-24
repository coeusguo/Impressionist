//
// CurveBrush.h
//
// The header file for Curve Brush. 
//

#ifndef CURVEBRUSH_H
#define CURVEBRUSH_H

#include "ImpBrush.h"
#include <vector>
#include <math.h>
using namespace std;
class CurveBrush : public ImpBrush
{
public:
	CurveBrush(ImpressionistDoc* pDoc = NULL, char* name = NULL);

	void BrushBegin(const Point source, const Point target);
	void BrushMove(const Point source, const Point target);
	void BrushEnd(const Point source, const Point target);
	int getCurveBrushPoints(const unsigned char* refImage,int x,int y,vector<int*>& points,unsigned char* rgb);
	char* BrushName(void);
};

#endif#pragma once
