//
// PointBrush.cpp
//
// The implementation of Point Brush. It is a kind of ImpBrush. All your brush implementations
// will look like the file with the different GL primitive calls.
//

#include "impressionistDoc.h"
#include "impressionistUI.h"
#include "LineBrush.h"
#include <iostream>
using namespace std;

extern float frand();

LineBrush::LineBrush(ImpressionistDoc* pDoc, char* name) :
	ImpBrush(pDoc, name)

{
	lastPoint = Point(-1, -1);
}

void LineBrush::BrushBegin(const Point source, const Point target)
{	
	if (lastPoint.x == -1) {
		lastPoint.x = source.x;
		lastPoint.y = source.y;
	}

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
	float radian = 0;
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
			{-1, 0, 1 }
		};
		int sobelY[3][3] = {
			{1, 2, 1},
			{0, 0, 0},
			{-1, -2, -1}
		};

		// calculate vector
		double pixels[3][3];
		/*double gaussian[3][3] = {
			{0.0625, 0.125, 0.0625},
			{0.125, 0.25, 0.125},
			{0.0625, 0.125, 0.0625}
		};*/
		double gx = 0;
		double gy = 0;
		for (int r = 0; r < 3; r++)
		{
			for (int c = 0; c < 3; c++)
			{
				// get the original pixel
				pixels[r][c] = *(pDoc->GetOriginalPixel(source.x + r - 1, source.y + c - 1));
				//pixels[r][c] *= gaussian[r][c];
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
		int xDifference = target.x - lastPoint.x;
		int yDifference = target.y - lastPoint.y;

		if (xDifference == 0)
		{
			angle = 90;
		}
		else
		{
			angle = (int)((atan2(yDifference, xDifference) * 180 / M_PI) + 360) % 360;
			pDoc->setLineAngle(angle);
		}

		break;
	}
	case ANOTHER_IMAGE_GRADIENT:
		radian = pDoc->m_ucAnotherGradientMap[source.x + source.y*pDoc->m_nWidth];
		break;
	default:
		break;
	}

	lastPoint.x = target.x;
	lastPoint.y = target.y;

	int size = pDoc->getSize();
	if(pDoc->m_pControlType != ANOTHER_IMAGE_GRADIENT)
		radian = (angle / 360.00)*twoPi;
	
	
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
	float cos = cosf(radian);
	float sin = sinf(radian);
	//edge clipping calculation
	if (pDoc->m_pUI->getEnableEdgeCliping() && pDoc->m_ucEdgePositionMap) {
		bool* edgeMap = pDoc->m_ucEdgePositionMap;
		int m_nWidth = pDoc->m_nWidth;
		int m_nHeight = pDoc->m_nHeight;
		//is on the edge
		if (edgeMap[y*m_nWidth + x]) {
			glPointSize(4);
			glBegin(GL_POINTS);
			SetColor(source);
			glVertex2d(x, y);
			glEnd();
			return;
		}

		//for general case
		if (angle != 90) {
			//y = kx + b0
			float k = tanf(radian);
			float b0 = y - k * x;

			//define a square
			float vx = abs((size / 2.0)*cos);
			float vy = abs((size / 2.0)*sin);
			float xRight = x + vx;
			float xLeft = x - vx;

			if (xLeft <= 0)
				xLeft = 0;
			if (xRight >= m_nWidth)
				xRight = m_nWidth - 1;

			int pairs[] = { -1,-1,-1,-1 };
			
			//find the right end point pairs[2] pairs[3]
			for (float X = x; X <= xRight; X++) {
				int i = X;
				int j = X * k + b0;
				if (j < 0) {
					pairs[3] = 0;
					pairs[2] = -b0 / k;
					break;
				}
				if (j >= m_nHeight) {
					pairs[3] = m_nHeight - 1;
					pairs[2] = (pairs[3] - b0)/k;
					break;
				}
				if (edgeMap[j * m_nWidth + i]) {
					pairs[2] = i;
					pairs[3] = j;
					break;
				}
			}
			//find the left point 
			for (float X = x; X >= xLeft; X--) {
				int i = X;
				int j = X * k + b0;
				if (j < 0) {
					pairs[3] = 0;
					pairs[2] = -b0 / k;
					break;
				}
				if (j >= m_nHeight) {
					pairs[3] = m_nHeight - 1;
					pairs[2] = (pairs[3] - b0) / k;
					break;
				}
				if (edgeMap[j*m_nWidth + i]) {
					pairs[0] = i;
					pairs[1] = j;
					break;
				}
			}
			
			if (pairs[0] == -1) {
				pairs[0] = x - vx;
				pairs[1] = pairs[0] * k + b0;
			}

			if (pairs[2] == -1) {
				pairs[2] = x + vx;
				pairs[3] = pairs[2] * k + b0;
			}

			//cout << pairs[0] << " " << pairs[1] <<" "<< pairs[2] << " "<<pairs[3] << endl;
			glBegin(GL_LINES);
			SetColor(source);
			glVertex2d(pairs[0], pairs[1]);
			glVertex2d(pairs[2], pairs[3]);
			glEnd();
			/*
			int sx0 = x - vx + 1;
			int sy0 = y - vy + 1;
			int sx1 = x + vx - 1;
			int sy1 = y + vy - 1;
			if (sx0 <= 0)
				sx0 = 0;
			if (sy0 <= 0)
				sy0 = 0;
			if (sx1 >= m_nWidth)
				sx1 = m_nWidth - 1;
			if (sy1 >= m_nHeight)
				sy1 = m_nHeight - 1;


			//initialize the distance with a sufficiently large number
			float distanceLeft = 100000000000;
			float distanceRight = 100000000000;
			int pairs[] = { -1,-1,-1,-1 };//x1,y1,x2,y2
			for (int Y = sy0; Y <= sy1; Y++) {
				for (int X = sx0; X <= sx1; X++) {
					if (edgeMap[Y*m_nWidth + X]) {//is edge
						if (X * k + b1 >= Y && X * k + b2 <= Y) {
							//y = cx + m,cx + (-y) + m = 0
							float m = Y - c * X;
							float dis = abs(c * x - y + m) / sqrt(c * c + 1);
							if (dis == 0)
								return;
							if (dis < distanceRight && X > x) {
								distanceRight = dis;
								pairs[2] = X;
								pairs[3] = Y;
							}
							if (dis < distanceLeft && X < x) {
								distanceLeft = dis;
								pairs[0] = X;
								pairs[1] = Y;
							}

						}
					}
				}
			}
			float v1x, v1y, v2x, v2y;
			float bound = size / 2.0;
			if (pairs[0] != -1 && distanceLeft < bound){
				v1x = x - distanceLeft * cos;
				v1y = y - distanceRight * sin;
			}
			else {
				v1x = x - vx;
				v1y = y + (size / 2.0)*sin;
			}

			if (pairs[2] != -1 && distanceRight < bound) {
				v2x = x + distanceRight * cos;
				v2y = y + distanceRight * sin;
			}
			else {
				v2x = x + vx;
				v2y = -v1y;
			}

			glBegin(GL_LINES);
			SetColor(source);

			glVertex2d(v1x,v1y);
			glVertex2d(v2x,v2y);
		}
		//else {
		//}

	}

	/*
	glBegin(GL_LINES);
	SetColor(source);
	float v1x = (size / 2.0)*cos;
	float v1y = (size / 2.0)*sin;
	float v2x = -v1x;
	float v2y = -v1y;

	glVertex2d(x + v1x, y + v1y);
	glVertex2d(x + v2x, y + v2y);
	*/
	//glEnd();
		}
		else {//angle is 90
			int pair[] = { x,y + 0.5*size,x,y- 0.5*size };
			for (int Y = y; Y <= y + 0.5*size; Y++) {
				if (Y >= m_nHeight) {
					pair[1] = m_nHeight - 1;
					break;
				}
				if (edgeMap[Y*m_nWidth + x]) {
					pair[1] = Y;
					break;
				}
			}

			for (int Y = y; Y >= y - 0.5*size; Y--) {
				if (Y <= 0) {
					pair[3] = 0;
					break;
				}
				if (edgeMap[Y*m_nWidth + x]) {
					pair[3] = Y;
					break;
				}

			}

			glBegin(GL_LINES);
			SetColor(source);
			glVertex2d(pair[0], pair[1]);
			glVertex2d(pair[2], pair[3]);
			glEnd();
		}
	}
	else {
		glBegin(GL_LINES);
		SetColor(source);
		float v1x = (size / 2.0)*cos;
		float v1y = (size / 2.0)*sin;
		float v2x = -v1x;
		float v2y = -v1y;

		glVertex2d(x + v1x, y + v1y);
		glVertex2d(x + v2x, y + v2y);
		glEnd();
	}
}

void LineBrush::BrushEnd(const Point source, const Point target)
{
	// do nothing so far
}

char* LineBrush::BrushName(void) {
	return ImpBrush::BrushName();
}