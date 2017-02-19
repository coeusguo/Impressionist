//
// AlphaMapBrush.h
//
// The header file for Point Brush. 
//

#ifndef ALPHAMAPBRUSH_H
#define ALPHAMAPBRUSH_H

#include "ImpBrush.h"

class AlphaMapBrush : public ImpBrush
{
public:
	AlphaMapBrush(ImpressionistDoc* pDoc = NULL, char* name = NULL);

	void BrushBegin(const Point source, const Point target);
	void BrushMove(const Point source, const Point target);
	void BrushEnd(const Point source, const Point target);
	char* BrushName(void);
};

#endif#pragma once
