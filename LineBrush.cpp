//
// PointBrush.cpp
//
// The implementation of Point Brush. It is a kind of ImpBrush. All your brush implementations
// will look like the file with the different GL primitive calls.
//

#include "impressionistDoc.h"
#include "impressionistUI.h"
#include "LineBrush.h"

extern float frand();

LineBrush::LineBrush(ImpressionistDoc* pDoc, char* name) :
	ImpBrush(pDoc, name)
{
}

void LineBrush::BrushBegin(const Point source, const Point target)
{	
	
	ImpressionistDoc* pDoc = GetDocument();
	ImpressionistUI* dlg = pDoc->m_pUI;
	if (!dlg->getEnableAutoDraw())
		saveState();


	BrushMove(source, target);
}

void LineBrush::BrushMove(const Point source, const Point target)
{
	ImpressionistDoc* pDoc = GetDocument();
	ImpressionistUI* dlg = pDoc->m_pUI;

	float twoPi = 3.1415927*2.0;
	int length = pDoc->getSize();
	int width = pDoc->getLineWidth();
	int angle = pDoc->getLineAngle();
	switch (pDoc->m_pControlType)
	{
	case SLIDER_RMOUSE:
		angle = pDoc->getLineAngle();
		break;
	case GRADIENT:
	{ // need {} to instantiate variables that will only be used inside this case
		// instantiate sobel operators
		int sobelX[3][3] = {
			{-1, 0, 1},
			{-2, 0, 2},
			(-1, 0, 1)
		};
		int sobelY[3][3] = {
			{1, 2, 1},
			{0, 0, 0},
			{-1, -2, -1}
		};

		// calculate vector
		int pixels[3][3];
		int gx = 0;
		int gy = 0;
		for (int r = 0; r < 3; r++)
		{
			for (int c = 0; c < 3; c++)
			{
				// get the original pixel
				pixels[r][c] = *(pDoc->GetOriginalPixel(target.x + r - 1, target.y + c - 1));
				// calculate Gx and Gy
				gx += pixels[r][c] * sobelX[r][c];
				gy += pixels[r][c] * sobelY[r][c];
			}
		}

		if (gx == 0) // since arctan would be undefined
		{
			angle = 90;
		}
		else
		{
			angle = (int)((atan2(gy, gx) * 180 / M_PI) + 360) % 360;
		}
		break;
	}
	case CURSOR:
	{
		int xDifference = target.x - source.x;
		int yDifference = target.y - source.y;

		if (xDifference == 0)
		{
			angle = 90;
		}
		else
		{
			angle = (int)((atan2(yDifference, xDifference) * 180 / M_PI) + 360) % 360;
		}

		break;
	}
	default:
		break;
	}
	int size = pDoc->getSize();
	float radian = (angle / 360.00)*twoPi;
	
	
	if (pDoc == NULL) {
		printf("PointBrush::BrushMove  document is NULL\n");
		return;
	}


	int x = target.x;
	int y = target.y;

	int startCol = dlg->m_paintView->getStartCol();
	int startRow = dlg->m_paintView->getStartRow() + dlg->m_mainWindow->h() - dlg->m_paintView->getDrawHeight() - 25;
	//int startRow = 0;
	int endCol = dlg->m_paintView->getEndCol();
	int endRow = startRow + dlg->m_paintView->getDrawHeight();

	if (x < startCol) {
		x = startCol;
	}

	if (x > endCol) {
		x = endCol;
	}

	if (y < startRow) {
		y = startRow;
	}

	if (y > endRow) {
		y = endRow;
	}


	glLineWidth((GLfloat)width);

	glBegin(GL_LINES);
	SetColor(source);
	float v1x = (size / 2.0)*cosf(radian);
	float v1y = (size / 2.0)*sinf(radian);
	float v2x = -v1x;
	float v2y = -v1y;

	glVertex2d(x + v1x, y + v1y);
	glVertex2d(x + v2x, y + v2y);

	glEnd();
}

void LineBrush::BrushEnd(const Point source, const Point target)
{
	// do nothing so far
}

char* LineBrush::BrushName(void) {
	return ImpBrush::BrushName();
}