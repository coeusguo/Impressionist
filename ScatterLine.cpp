//
// ScatterLine.cpp
//
// The implementation of Scatter Line Brush. It is a kind of ImpBrush. All your brush implementations
// will look like the file with the different GL primitive calls.
//

#include "impressionistDoc.h"
#include "impressionistUI.h"
#include "ScatterLine.h"
#include <cstdlib>
#include <ctime>
using namespace std;

extern float frand();

ScatterLine::ScatterLine(ImpressionistDoc* pDoc, char* name) :
	LineBrush(pDoc, name)
{
}

void ScatterLine::BrushBegin(const Point source, const Point target)
{
	ImpressionistDoc* pDoc = GetDocument();
	srand((unsigned int)time(0));
	BrushMove(source, target);
}

void ScatterLine::BrushMove(const Point source, const Point target)
{
	ImpressionistDoc* pDoc = GetDocument();
	ImpressionistUI* dlg = pDoc->m_pUI;


	int offset = pDoc->getSize()*1.5;
	

	for (int i = 0; i < 3; i++) {
		int x = target.x + rand() % offset - 0.5*offset;
		int y = target.y + rand() % offset - 0.5*offset;
		Point ScatterCenter = Point(x, y);

		LineBrush::BrushMove(ScatterCenter, ScatterCenter);

	}
	if (pDoc == NULL) {
		printf("Scatter Lines::BrushMove  document is NULL\n");
		return;
	}




}

void ScatterLine::BrushEnd(const Point source, const Point target)
{
	// do nothing so far
}

char* ScatterLine::BrushName(void) {
	return LineBrush::BrushName();
}