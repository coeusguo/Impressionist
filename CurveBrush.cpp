//
// PointBrush.cpp
//
// The implementation of Point Brush. It is a kind of ImpBrush. All your brush implementations
// will look like the file with the different GL primitive calls.
//

#include "impressionistDoc.h"
#include "impressionistUI.h"
#include "CurveBrush.h"
#include <iostream>
using namespace std;
extern float frand();

CurveBrush::CurveBrush(ImpressionistDoc* pDoc, char* name) :
	ImpBrush(pDoc, name)
{
}

void CurveBrush::BrushBegin(const Point source, const Point target)
{

	ImpressionistDoc* pDoc = GetDocument();
	ImpressionistUI* dlg = pDoc->m_pUI;
	if (!dlg->getEnableAutoDraw())
		saveState();
	int size = pDoc->getSize();
	glPointSize((float)size);

	BrushMove(source, target);
}

void CurveBrush::BrushMove(const Point source, const Point target)
{
	ImpressionistDoc* pDoc = GetDocument();
	ImpressionistUI* dlg = pDoc->m_pUI;

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

	vector<int*> points;
	unsigned char* rgb = new unsigned char[3];
	float radius = pDoc->getSize();
	int numPoints;
	if(pDoc->m_pUI->m_nPainterlyRun)
		numPoints = getCurveBrushPoints(pDoc->m_ucBitmapBlur, x, y, points, rgb);
	else
		numPoints = getCurveBrushPoints(pDoc->m_ucBitmap, x, y, points, rgb);

	//cout << numPoints << endl;
	GLubyte color[4];
	color[0] = rgb[0];
	color[1] = rgb[1];
	color[2] = rgb[2];
	color[3] = pDoc->getAlpha() * 255;

	glColor4ubv(color);
	//cout << numPoints << endl;
	//draw rectangles
	if (numPoints >= 3) {

		//store the unit direction vectors of each point
		vector<int*> vectors;
		for (int i = 0; i < numPoints - 1; i++) {
			float dx = points.at(i + 1)[0] - points.at(i)[0];
			float dy = points.at(i + 1)[1] - points.at(i)[1];
			dx = dx / radius;
			dy = dy / radius;
			int* vector = new int[2];
			vector[0] = -dy;
			vector[1] = dx;
			vectors.push_back(vector);
		
		}

		for (int i = 0; i < numPoints - 1; i++) {
			float dx = vectors.at(i)[0];
			float dy = vectors.at(i)[1];

			glBegin(GL_POLYGON);
			glVertex2d(points.at(i)[0] + radius * dx,points.at(i)[1] + radius * dy);
			glVertex2d(points.at(i + 1)[0] + radius * dx, points.at(i + 1)[1] + radius * dy);
			glVertex2d(points.at(i + 1)[0] - radius * dx, points.at(i + 1)[1] - radius * dy);
			glVertex2d(points.at(i)[0] - radius * dx, points.at(i)[1] - radius * dy);
			glEnd();
		}

		for (int* n : vectors)
			delete[]n;
	}

	int triangleAmount = 100;

	for (int i = 0; i < numPoints; i++) {

		float xx = radius;
		float yy = 0;
		float dx = points.at(i)[0];
		float dy = points.at(i)[1];
		glColor4ubv(color);
		glBegin(GL_TRIANGLE_FAN);
		
		glVertex2f((GLfloat)dx, (GLfloat)dy);
		float unitAngle = M_PI * 2 / triangleAmount;
		glVertex2f(dx + xx, dy + yy);
		for (int i = 1; i <= triangleAmount; i++) {
			xx = radius*cosf(i*unitAngle);
			yy = radius*sinf(i*unitAngle);
			glVertex2f(dx + xx, dy + yy);
		}

		glEnd();
	
	}

	delete[] rgb;
	for (int* n : points)
		delete[]n;

}

void CurveBrush::BrushEnd(const Point source, const Point target)
{
	// do nothing so far
}

char* CurveBrush::BrushName(void) {
	return ImpBrush::BrushName();
}

int CurveBrush::getCurveBrushPoints(const unsigned char* refImage,int x0, int y0,vector<int*>& points,unsigned char* rgb) {

	int numPoints = 1;
	ImpressionistDoc* pDoc = GetDocument();
	ImpressionistUI* pUI = pDoc->m_pUI;
	int width = pDoc->m_nWidth;
	int height = pDoc->m_nHeight;

	float curvature = pUI->m_nPainterlyCurvature;
	
	int minStroke = pUI->m_nPainterlyMinStrokeL;
	int maxStroke = pUI->m_nPainterlyMaxStrokeL;
	float radius = pDoc->getSize();

	

	unsigned char* canvas = pDoc->m_ucPainting;
	int* gradientXY = pDoc->m_ucGradientXYmap;

	memcpy(rgb, refImage + (y0 * width + x0) * 3 , 3);

	int* point = new int[2];
	point[0] = x0;
	point[1] = y0;
	//x0 and y0
	points.push_back(point);

	if (curvature == 0)
		return numPoints;
	int x = x0;
	int y = y0;
	int lastDx = 0;
	int lastDy = 0;

	for (int i = 0; i <= maxStroke; i++) {
	

		if (i > minStroke) {
			unsigned char* canvasColor = new unsigned char[3];
			memcpy(canvasColor, canvas + (y * width + x) * 4, 3);

			unsigned char* refImageColor = new unsigned char[3];
			
			memcpy(refImageColor, (void*)(refImage + (y * width + x) * 3), 3);
			

			float diff1 = sqrt(pow(refImageColor[0] - canvasColor[0], 2) + pow(refImageColor[1] - canvasColor[1], 2) + pow(refImageColor[2] - canvasColor[2], 2));
			float diff2 = sqrt(pow(refImageColor[0] - rgb[0], 2) + pow(refImageColor[1] - rgb[1], 2) + pow(refImageColor[2] - rgb[2], 2));
			if (diff1 < diff2)
				return numPoints;
		}

		int Gx = gradientXY[(y * width + x) * 2];
		int Gy = gradientXY[(y * width + x) * 2 + 1];
		//cout << Gx << "," << Gy << endl;
		//detect vanishing gradient
		if (Gx == 0 && Gy == 0)
			return numPoints;

		//get unit vector of the gradient
		float unit = sqrt(Gx * Gx + Gy * Gy);

		float dx = (float)-Gy / unit;
		float dy = (float)Gx / unit;
		//cout << dx << "," << dy << endl;
		//if necessary, reverse the direction
		if (lastDx * dx + lastDy * dy < 0) {
			dx = -dx;
			dy = -dy;
		}
		
		//cout << curvature << endl;
		//filter the stroke direction
		dx = curvature * dx + (1 - curvature) * lastDx;
		dy = curvature * dy + (1 - curvature) * lastDy;
		unit = sqrt(dx * dx + dy * dy);
		dx = dx / unit;
		dy = dy / unit;
		//cout << dx << "," << dy << endl;
		x = x + radius * dx;
		y = y + radius * dy;
		if (x < 0)
			x = 0;
		if (y < 0)
			y = 0;

		if (x >= width)
			x = width - 1;
		if (y >= height)
			y = height - 1;

		int* point1 = new int[2];
		point1[0] = x;
		point1[1] = y;

		points.push_back(point1);

		lastDx = dx;
		lastDy = dy;

		numPoints++;
	}

	return numPoints;
}