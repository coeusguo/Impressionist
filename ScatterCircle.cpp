//
// ScatterCircle.cpp
//
// The implementation of Scatter Circle Brush. It is a kind of ImpBrush. All your brush implementations
// will look like the file with the different GL primitive calls.
//

#include "impressionistDoc.h"
#include "impressionistUI.h"
#include "ScatterCircle.h"
#include <cstdlib>
#include <ctime>
#include <iostream>
using namespace std;

extern float frand();

ScatterCircle::ScatterCircle(ImpressionistDoc* pDoc, char* name) :
	CircleBrush(pDoc, name)
{
}

void ScatterCircle::BrushBegin(const Point source, const Point target)
{
	ImpressionistDoc* pDoc = GetDocument();
	srand((unsigned int)time(0));
	BrushMove(source, target);
}

void ScatterCircle::BrushMove(const Point source, const Point target)
{
	ImpressionistDoc* pDoc = GetDocument();
	ImpressionistUI* dlg = pDoc->m_pUI;

	
	int radius = pDoc->getSize();
	float Pi = 3.1415926;

	for (int i = 0; i < 3; i++) {
		int x = target.x + rand() % radius - 0.5 * radius;
		int y = target.y + rand() % radius - 0.5 * radius;
		Point ScatterCenter = Point(x, y);
		
		CircleBrush::BrushMove(ScatterCenter, ScatterCenter);
		
	}
	if (pDoc == NULL) {
		printf("Scatter Circles::BrushMove  document is NULL\n");
		return;
	}

	


}

void ScatterCircle::BrushEnd(const Point source, const Point target)
{
	// do nothing so far
}

