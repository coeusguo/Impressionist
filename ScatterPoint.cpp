//
// ScatterPoint.cpp
//
// The implementation of Scatter Point Brush. It is a kind of ImpBrush. All your brush implementations
// will look like the file with the different GL primitive calls.
//

#include "impressionistDoc.h"
#include "impressionistUI.h"
#include "ScatterPoint.h"
#include <cstdlib>
#include <ctime>
using namespace std;

extern float frand();

ScatterPoint::ScatterPoint(ImpressionistDoc* pDoc, char* name) :
	PointBrush(pDoc, name)
{
}

void ScatterPoint::BrushBegin(const Point source, const Point target)
{
	saveState();
	ImpressionistDoc* pDoc = GetDocument();
	srand((unsigned int)time(0));
	BrushMove(source, target);
}

void ScatterPoint::BrushMove(const Point source, const Point target)
{
	ImpressionistDoc* pDoc = GetDocument();
	ImpressionistUI* dlg = pDoc->m_pUI;


	int offset = pDoc->getSize();
	float Pi = 3.1415926;

	for (int i = 0; i < 0.3* offset*offset; i++) {
		int x = target.x + rand() % offset - 0.5 * offset;
		int y = target.y + rand() % offset - 0.5 * offset;
		int unitSize = 1;
		Point ScatterCenter = Point(x, y);
		glPointSize((float)unitSize);
		PointBrush::BrushMove(ScatterCenter, ScatterCenter);

	}
	if (pDoc == NULL) {
		printf("Scatter Circles::BrushMove  document is NULL\n");
		return;
	}




}

void ScatterPoint::BrushEnd(const Point source, const Point target)
{
	// do nothing so far
}

char* ScatterPoint::BrushName(void) {
	return PointBrush::BrushName();
}