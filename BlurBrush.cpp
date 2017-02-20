//
// BlurBrush.cpp
//
// The implementation of Blur Brush. It is a kind of ImpBrush. All your brush implementations
// will look like the file with the different GL primitive calls.
//

#include "impressionistDoc.h"
#include "impressionistUI.h"
#include "BlurBrush.h"
#include<iostream>

extern float frand();

BlurBrush::BlurBrush(ImpressionistDoc* pDoc, char* name) :
	ImpBrush(pDoc, name)

{
	filter[0][0] = 0.0625; filter[0][1] = 0.125; filter[0][2] = 0.0625;

	filter[1][0] = 0.125; filter[1][1] = 0.25; filter[1][2] = 0.125;

	filter[2][0] = 0.0625; filter[2][1] = 0.125; filter[2][2] = 0.0625;
	/*
	filter[0][0] = 0.00000067; filter[0][1] = 0.00002292; filter[0][2] = 0.00019117; filter[0][3] = 0.00038771; filter[0][4] = 0.00019117; filter[0][5] = 0.00002292; filter[0][6] = 0.00000067;

	filter[1][0] = 0.00002292; filter[1][1] = 0.00078634; filter[1][2] = 0.00655965; filter[1][3] = 0.01330373; filter[1][4] = 0.00655965; filter[1][5] = 0.00078633; filter[1][6] = 0.00002292;

	filter[2][0] = 0.00019117; filter[2][1] = 0.00655965; filter[2][2] = 0.05472157; filter[2][3] = 0.11098164; filter[2][4] = 0.05472157; filter[2][5] = 0.00655965; filter[2][6] = 0.00019117;

	filter[3][0] = 0.00038771; filter[3][1] = 0.01330373; filter[3][2] = 0.11098164; filter[3][3] = 0.22508352; filter[3][4] = 0.11098164; filter[3][5] = 0.01330373; filter[3][6] = 0.00038771;

	filter[4][0] = 0.00019117; filter[4][1] = 0.00655965; filter[4][2] = 0.05472157; filter[4][3] = 0.11098164; filter[4][4] = 0.05472157; filter[4][5] = 0.00655965; filter[4][6] = 0.00019117;

	filter[5][0] = 0.00002292; filter[5][1] = 0.00078634; filter[5][2] = 0.00655965; filter[5][3] = 0.01330373; filter[5][4] = 0.00655965; filter[5][5] = 0.00078633; filter[5][6] = 0.00002292;

	filter[6][0] = 0.00000067; filter[6][1] = 0.00002292; filter[6][2] = 0.00019117; filter[6][3] = 0.00038771; filter[6][4] = 0.00019117; filter[6][5] = 0.00002292; filter[6][6] = 0.00000067;
	*/
}

void BlurBrush::BrushBegin(const Point source, const Point target)
{
	ImpressionistDoc* pDoc = GetDocument();
	ImpressionistUI* dlg = pDoc->m_pUI;

	int size = pDoc->getSize();
	if (!dlg->getEnableAutoDraw())
		saveState();

	glPointSize((float)size);

	BrushMove(source, target);
}

void BlurBrush::BrushMove(const Point source, const Point target)
{
	ImpressionistDoc* pDoc = GetDocument();
	ImpressionistUI* dlg = pDoc->m_pUI;

	if (pDoc == NULL) {
		printf("BlurBrush::BrushMove  document is NULL\n");
		return;
	}

	int x = target.x;
	int y = target.y;

	//store the  pixels
	float*** buffer = new float**[9];
	for (int i = 0; i < 9; i++) {
		buffer[i] = new float*[9];
		for (int j = 0; j < 9; j++)
			buffer[i][j] = new float[3];
	}


	int startCol = dlg->m_paintView->getStartCol();
	int startRow = dlg->m_paintView->getStartRow() + dlg->m_mainWindow->h() - dlg->m_paintView->getDrawHeight() - 25;
	//int startRow = 0;
	int endCol = dlg->m_paintView->getEndCol();
	int endRow = startRow + dlg->m_paintView->getDrawHeight();

	if (x < startCol) {
		x = startCol + 4;
	}

	if (x >= endCol) {
		x = endCol - 4;
	}

	if (y <= startRow) {
		y = startRow + 4;
	}

	if (y >= endRow) {
		y = endRow - 4;
	}

	for (int i = -4; i < 5; i++) {
		for (int j = -4; j < 5; j++) {
			applyFilter(x + i, y + j, buffer, i + 4, j + 4);
		}
	}


	glPointSize(1);

	glBegin(GL_POINTS);

	for (int i = 0; i < 9; i++) {
		for (int j = 0; j < 9; j++) {
			glColor3ub((GLubyte)buffer[i][j][0], (GLubyte)buffer[i][j][1], (GLubyte)buffer[i][j][2]);
			glVertex2d(x + i - 4, y + j - 4);
		}
	}

	glEnd();
	delete[]buffer;
}

void BlurBrush::BrushEnd(const Point source, const Point target)
{
	// do nothing so far
}

char* BlurBrush::BrushName(void) {
	return ImpBrush::BrushName();
}

void BlurBrush::applyFilter(int x, int y, float***buffer, int row, int col) {
	ImpressionistDoc* pDoc = GetDocument();

	for (int color = 0; color < 3; color++) {
		float result = 0;
		for (int i = -1; i < 2; i++) {
			for (int j = -1; j < 2; j++) {
				result += ((float)*(pDoc->GetOriginalPixel(x + i, y + j) + color))*filter[i + 1][j + 1];
			}
		}

		if (result > 255)
			result = 255;
		if (result < 0)
			result = 0;

		buffer[row][col][color] = result;
	}
}
