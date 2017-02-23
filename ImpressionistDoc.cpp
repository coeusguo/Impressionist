// 
// impressionistDoc.cpp
//
// It basically maintain the bitmap for answering the color query from the brush.
// It also acts as the bridge between brushes and UI (including views)
//

#include <FL/fl_ask.H>

#include "impressionistDoc.h"
#include "impressionistUI.h"

#include "ImpBrush.h"

// Include individual brush headers here.
#include "PointBrush.h"
#include "CircleBrush.h"
#include "LineBrush.h"
#include "ScatterCircle.h"
#include "ScatterLine.h"
#include "ScatterPoint.h"
#include "GrayBrush.h"
#include "SharpenBrush.h"
#include "BlurBrush.h"
#include "Warp.h"
#include "AlphaMapBrush.h"
#include <iostream>


#define DESTROY(p)	{  if ((p)!=NULL) {delete [] p; p=NULL; } }

ImpressionistDoc::ImpressionistDoc() 
{
	// Set NULL image name as init. 
	m_imageName[0]	='\0';	

	m_nWidth		= -1;
	m_ucBitmap		= NULL;
	m_ucPainting	= NULL;
	m_ucBitmapOrigin = NULL;
	m_ucDissolve = NULL;
	m_ucAlphamap = NULL;
	m_ucBackup = NULL;
	m_ucEdgeBitmap = NULL;
	m_ucGrayScaleMap = NULL;
	m_ucGradientMap = NULL;//attention: this variable is float* type!not unsigned char* type
	m_ucAnotherBitmap = NULL;
	m_ucEdgePositionMap = NULL;//the type of this variable is bool* !!!
	m_ucAnotherGradientMap = NULL;


	// create one instance of each brush
	ImpBrush::c_nBrushCount	= NUM_BRUSH_TYPE;
	ImpBrush::c_pBrushes	= new ImpBrush* [ImpBrush::c_nBrushCount];

	ImpBrush::c_pBrushes[BRUSH_POINTS]	= new PointBrush( this, "Points" );


	// Note: You should implement these 5 brushes.  They are set the same (PointBrush) for now
	ImpBrush::c_pBrushes[BRUSH_LINES]				
		= new LineBrush( this, "Lines" );
	ImpBrush::c_pBrushes[BRUSH_CIRCLES]				
		= new CircleBrush( this, "Circles" );
	ImpBrush::c_pBrushes[BRUSH_SCATTERED_POINTS]	
		= new ScatterPoint( this, "Scattered Points" );
	ImpBrush::c_pBrushes[BRUSH_SCATTERED_LINES]		
		= new ScatterLine( this, "Scattered Lines" );
	ImpBrush::c_pBrushes[BRUSH_SCATTERED_CIRCLES]	
		= new ScatterCircle( this, "Scattered Circles" );
	ImpBrush::c_pBrushes[BRUSH_GRAY_POINTS]
		= new GrayBrush(this, "Gray");
	ImpBrush::c_pBrushes[BRUSH_SHARPEN_POINTS]
		= new SharpenBrush(this, "Sharpen Points");
	ImpBrush::c_pBrushes[BRUSH_BLUR_POINTS]
		= new BlurBrush(this, "Blur Points");
	ImpBrush::c_pBrushes[WARP_IMAGE]
		= new Warp(this, "Warp Image");
	ImpBrush::c_pBrushes[BRUSH_ALPHA_MAP]
		= new AlphaMapBrush(this,"Alpha Map");

	// make one of the brushes current
	m_pCurrentBrush	= ImpBrush::c_pBrushes[0];

	sobelVertical[0] = -1; sobelVertical[1] = 0; sobelVertical[2] = 1;
	sobelVertical[3] = -2; sobelVertical[4] = 0; sobelVertical[5] = 2;
	sobelVertical[6] = -1; sobelVertical[7] = 0; sobelVertical[8] = 1;

	sobelHorizontal[0] = -1; sobelHorizontal[1] = -2; sobelHorizontal[2] = -1;
	sobelHorizontal[3] = 0; sobelHorizontal[4] = 0; sobelHorizontal[5] = 0;
	sobelHorizontal[6] = 1; sobelHorizontal[7] = 2; sobelHorizontal[8] = 1;

	gaussianFilter[0] = 0.0625; gaussianFilter[1] = 0.125; gaussianFilter[2] = 0.0625;
	gaussianFilter[3] = 0.125; gaussianFilter[4] = 0.25; gaussianFilter[5] = 0.125;
	gaussianFilter[6] = 0.0625; gaussianFilter[7] = 0.125; gaussianFilter[8] = 0.0625;
}


//---------------------------------------------------------
// Set the current UI 
//---------------------------------------------------------
void ImpressionistDoc::setUI(ImpressionistUI* ui) 
{
	m_pUI	= ui;
}

//---------------------------------------------------------
// Returns the active picture/painting name
//---------------------------------------------------------
char* ImpressionistDoc::getImageName() 
{
	return m_imageName;
}

//---------------------------------------------------------
// Called by the UI when the user changes the brush type.
// type: one of the defined brush types.
//---------------------------------------------------------
void ImpressionistDoc::setBrushType(int type)
{
	m_pCurrentBrush	= ImpBrush::c_pBrushes[type];
	currentType = type;
}

//---------------------------------------------------------
// Called by the UI when the user changes the type of the line brush direction control.
// type: one of the defined brush dirction control (requirement #3).
//---------------------------------------------------------
void ImpressionistDoc::setBrushDirectionType(int type) {
	m_pControlType = type;
	std::cout << type;
}
//---------------------------------------------------------
// Returns the size of the brush.
//---------------------------------------------------------
int ImpressionistDoc::getSize()
{
	return m_pUI->getSize();
}
int ImpressionistDoc::getLineWidth()
{
	return m_pUI->getLineWidth();
}
int ImpressionistDoc::getLineAngle()
{
	return m_pUI->getLineAngle();
}
double ImpressionistDoc::getAlpha()
{
	return m_pUI->getAlpha();
}
//---------------------------------------------------------
// Load the specified image
// This is called by the UI when the load image button is 
// pressed.
//---------------------------------------------------------
int ImpressionistDoc::loadImage(char *iname) 
{
	// try to open the image to read
	unsigned char*	data;
	int				width, 
					height;

	if ( (data=readBMP(iname, width, height))==NULL ) 
	{
		fl_alert("Can't load bitmap file");
		return 0;
	}

	// reflect the fact of loading the new image
	m_nWidth		= width;
	m_nPaintWidth	= width;
	m_nHeight		= height;
	m_nPaintHeight	= height;


	// release old storage
	if ( m_ucBitmap ) delete [] m_ucBitmap;
	if ( m_ucPainting ) delete [] m_ucPainting;
	if (m_ucBitmapOrigin)delete[] m_ucBitmapOrigin;
	if (m_ucBackup)delete[]m_ucBackup;
	if (m_ucGrayScaleMap)delete[]m_ucGrayScaleMap;
	if (m_ucAnotherBitmap)delete[]m_ucAnotherBitmap;
	m_ucAnotherBitmap = NULL;
	if (m_ucAnotherGradientMap)delete[]m_ucAnotherGradientMap;
	m_ucAnotherGradientMap = NULL;
	if (m_ucEdgeBitmap)delete[]m_ucEdgeBitmap;
	m_ucEdgeBitmap = NULL;
	if (m_ucEdgePositionMap)delete[]m_ucEdgePositionMap;
	m_ucEdgePositionMap = NULL;
	

	m_ucBitmapOrigin = new unsigned char[width*height * 3];
	memcpy(m_ucBitmapOrigin, data, width*height * 3);
	m_ucBitmap		= data;
	
	// allocate space for draw view
	m_ucPainting	= new unsigned char [width*height*4];
	m_ucBackup = new unsigned char[width*height * 4];
	memset(m_ucPainting, 0, width*height*4);
	memset(m_ucBackup, 0, width*height * 4);
	
	m_pUI->m_origView->setViewType(ORIGIN_IMAGE);
	/*set alpha value to 1
	if (m_nWidth > 0 && m_nHeight > 0)
		for (int i = 0; i < m_nWidth * m_nHeight; ++i){
			((GLubyte*)m_ucPainting)[i * 4 + 3] = 255;
			//((GLubyte*)m_ucPainting)[i * 4 + 1] = 255;
			//cout << (int)m_ucPainting[i * 4 + 3];
		}
		//*/
	m_pUI->m_mainWindow->resize(m_pUI->m_mainWindow->x(), 
								m_pUI->m_mainWindow->y(), 
								width*2, 
								height+25);

	// display it on origView
	m_pUI->m_origView->resizeWindow(width, height);	
	m_pUI->m_origView->refresh();

	// refresh paint view as well
	m_pUI->m_paintView->resizeWindow(width, height);	
	m_pUI->m_paintView->refresh();

	while (!history.empty()) {
		delete[]history.top();
		history.pop();
	}
	

	//calculate grayscaleMap and gradient map
	m_ucGrayScaleMap = new unsigned char[width*height];
	for (int i = 0; i < width*height; i++)
		m_ucGrayScaleMap[i] = (m_ucBitmap[i * 3] + m_ucBitmap[i * 3 + 1] + m_ucBitmap[i * 3 + 2]) / 3;
	
	m_ucGradientMap = new float[width*height];
	for (int i = 0; i < width*height; i++) 
		m_ucGradientMap[i] = applySobel(i / width, i % width, false, m_ucGrayScaleMap);
		
	
	return 1;
}
//---------------------------------------------------------
// Load the specified image
// This is called by the UI when the load another image button is 
// pressed.
//---------------------------------------------------------
int ImpressionistDoc::loadAnotherImage(char *iname) {
	// try to open the image to read
	unsigned char*	data;
	int				width,
					height;

	if (!m_ucBitmap) {
		fl_alert("You must load a bitmap to canvas first!");
		return 0;
	}

	if ((data = readBMP(iname, width, height)) == NULL)
	{
		fl_alert("Can't load bitmap file");
		return 0;
	}

	if (width != m_nWidth || height != m_nHeight) {
		fl_alert("The size are different");
		return 0;
	}

	if (m_ucAnotherBitmap)delete[] m_ucAnotherBitmap;
	if (m_ucAnotherGradientMap)delete[] m_ucAnotherGradientMap;

	m_ucAnotherBitmap = data;
	m_ucAnotherGradientMap = new  float[width*height];

	//apply gaussian filter
	unsigned char* temp1 = new unsigned char[width*height * 3];
	memcpy(temp1, m_ucAnotherBitmap, width*height * 3);
	//applyGaussianFilter(temp1, m_ucAnotherBitmap, width, height);
	delete[]temp1;

	unsigned char* temp2 = new unsigned char[width*height];
	for (int i = 0; i < width*height; i++)
		temp2[i] = m_ucAnotherBitmap[i * 3] * 0.299 + m_ucAnotherBitmap[i * 3 + 1]*0.587 + m_ucAnotherBitmap[i * 3 + 2] * 0.144;

	for (int i = 0; i < width*height; i++) {
		int row = i / width;
		int col = i % width;
		m_ucAnotherGradientMap[i] = applySobel(row, col,true, temp2);
	}
	//applyFilter(int row, int col,int kernelWidth,int kernelHeight,float*kernel,float* rgb,unsigned char* painting)
	delete[]temp2;
	

	// display it on origView
	m_pUI->m_origView->resizeWindow(width, height);
	m_pUI->m_origView->refresh();



	return 1;
}

int ImpressionistDoc::loadEdgeImage(char *iname) {

	// try to open the image to read
	unsigned char*	data;
	int				width,
		height;

	if (!m_ucBitmap) {
		fl_alert("You must load a bitmap to canvas first!");
		return 0;
	}

	if ((data = readBMP(iname, width, height)) == NULL)
	{
		fl_alert("Can't load bitmap file");
		return 0;
	}

	if (width != m_nWidth || height != m_nHeight) {
		fl_alert("The size are different");
		return 0;
	}

	if (m_ucEdgeBitmap)delete[]m_ucEdgeBitmap;
	if (m_ucEdgePositionMap)delete[]m_ucEdgePositionMap;

	m_ucEdgeBitmap = data;


	
	m_ucEdgePositionMap = new bool[width*height];
	memset(m_ucEdgePositionMap, 0, width*height);
	for (int i = 0; i < width*height; i++) {
		if (m_ucEdgeBitmap[3 * i] + m_ucEdgeBitmap[3 * i + 1] + m_ucEdgeBitmap[3 * i + 1] != 0)
			m_ucEdgePositionMap[i] = true;
	}


	// display it on origView
	m_pUI->m_origView->resizeWindow(width, height);
	m_pUI->m_origView->refresh();

	return 1;
}
//----------------------------------------------------------------
// Add a "mural" effect 
// This is called by the UI when the New Mural Image menu button is 
// pressed.
//----------------------------------------------------------------
int ImpressionistDoc::muralImage(char *iname) {
	// try to open the image to read
	unsigned char*	data;
	int				width,
		height;

	if (!m_ucBitmap) {
		fl_alert("You must load a bitmap to canvas first!");
		return 0;
	}

	if ((data = readBMP(iname, width, height)) == NULL)
	{
		fl_alert("Can't load bitmap file");
		return 0;
	}

	if (width != m_nWidth || height != m_nHeight) {
		fl_alert("The size are different");
		return 0;
	}

	

	// release old storage
	if (m_ucBitmapOrigin)delete[] m_ucBitmapOrigin;
	if (m_ucBitmap)delete[] m_ucBitmap;
	
	m_ucBitmap = data;

	m_ucBitmapOrigin = new unsigned char[width*height * 3];
	memcpy(m_ucBitmapOrigin, m_ucBitmap, width*height * 3);

	// display it on origView
	m_pUI->m_origView->resizeWindow(width, height);
	m_pUI->m_origView->refresh();

	

	return 1;
}
//---------------------------------------------------------
// Load the specified image and dissolve with previously loaded picture
// This is called by the UI when the load image button is 
// pressed.
//---------------------------------------------------------
int	ImpressionistDoc::dissolveImage(char *iname) {
	// try to open the image to read
	unsigned char*	data;
	int				width,
					height;

	if (!m_ucBitmap) {
		fl_alert("You must load a bitmap to canvas first!");
		return 0;
	}

	if ((data = readBMP(iname, width, height)) == NULL)
	{
		fl_alert("Can't load bitmap file");
		return 0;
	}

	if (width != m_nWidth || height != m_nHeight) {
		fl_alert("The size are different");
		return 0;
	}

	m_ucDissolve = data;

	// release old storage
	if (m_ucBitmapOrigin)delete[] m_ucBitmapOrigin;

	float alpha = 0.5;

	for (int i = 0; i < width*height * 3; i++)
		m_ucBitmap[i] = m_ucBitmap[i] * (1 - alpha * 1) + m_ucDissolve[i]*alpha * 1;
	
	m_ucBitmapOrigin = new unsigned char[width*height * 3];
	memcpy(m_ucBitmapOrigin, m_ucBitmap, width*height * 3);

	// display it on origView
	m_pUI->m_origView->resizeWindow(width, height);
	m_pUI->m_origView->refresh();

	// refresh paint view as well
	m_pUI->m_paintView->resizeWindow(width, height);
	m_pUI->m_paintView->refresh();

	return 1;
}


int ImpressionistDoc::alphaMapBrush(char *iname) {
	// try to open the image to read
	unsigned char*	data;
	int				width,
					height;


	if ((data = readBMP(iname, width, height)) == NULL)
	{
		fl_alert("Can't load bitmap file");
		return 0;
	}
	m_nAlphaMapHeight = height;
	m_nAlphaMapWidth = width;
	// release old storage
	if (m_ucAlphamap)delete[] m_ucAlphamap;


	m_ucAlphamap = new unsigned char[width*height];
	for (int i = 0; i < width*height; i++) {
		m_ucAlphamap[i] = ((int)data[i * 3] + (int)data[i * 3 + 1] + (int)data[i * 3 + 2]) / 3;
	}


	return 1;
}
//----------------------------------------------------------------
// Save the specified image
// This is called by the UI when the save image menu button is 
// pressed.
//----------------------------------------------------------------
int ImpressionistDoc::saveImage(char *iname) 
{
	unsigned char* data = new unsigned char[m_nPaintHeight*m_nPaintWidth * 3];
	for (int i = 0; i < m_nHeight*m_nWidth; i++) {
		data[i * 3] = m_ucPainting[4 * i];
		data[i * 3 + 1] = m_ucPainting[4 * i + 1];
		data[i * 3 + 2] = m_ucPainting[4 * i + 2];
	}

	writeBMP(iname, m_nPaintWidth, m_nPaintHeight, data);

	return 1;
}

//----------------------------------------------------------------
// Clear the drawing canvas
// This is called by the UI when the clear canvas menu item is 
// chosen
//-----------------------------------------------------------------
int ImpressionistDoc::clearCanvas() 
{

	// Release old storage
	if ( m_ucPainting ) 
	{
		delete [] m_ucPainting;

		// allocate space for draw view
		m_ucPainting	= new unsigned char [m_nPaintWidth*m_nPaintHeight*4];
		memset(m_ucPainting, 0, m_nPaintWidth*m_nPaintHeight*4);

		// refresh paint view as well	
		m_pUI->m_paintView->refresh();
	}
	
	return 0;
}

//------------------------------------------------------------------
// Get the color of the pixel in the original image at coord x and y
//------------------------------------------------------------------
GLubyte* ImpressionistDoc::GetOriginalPixel( int x, int y )
{
	if ( x < 0 ) 
		x = 0;
	else if ( x >= m_nWidth ) 
		x = m_nWidth-1;

	if ( y < 0 ) 
		y = 0;
	else if ( y >= m_nHeight ) 
		y = m_nHeight-1;

	return (GLubyte*)(m_ucBitmap + 3 * (y*m_nWidth + x));
}

//----------------------------------------------------------------
// Get the color of the pixel in the original image at point p
//----------------------------------------------------------------
GLubyte* ImpressionistDoc::GetOriginalPixel( const Point p )
{
	return GetOriginalPixel( p.x, p.y );
}

void ImpressionistDoc::setLineAngle(int lineAngle)
{
	m_pUI->setLineAngle(lineAngle);
}

void ImpressionistDoc::applyKernelFilter() {
	bool enableNormalize = m_pUI->getEnableNormalize();
	int kernelWidth = m_pUI->getKernelWidth();
	int kernelHeight = m_pUI->getKernelHeight();
	int kernelSize = kernelWidth*kernelHeight;
	float* rgb;
	unsigned char* preservedPainting = new unsigned char[m_nHeight*m_nWidth*4];
	memcpy(preservedPainting, m_ucPainting, m_nHeight*m_nWidth * 4);

	float* kernel = new float[kernelSize];
	float sum = 0;
	for (int i = 0; i < kernelSize; i++) {
		kernel[i] = atof(m_pUI->m_filterKernelInputMatrix.at(i)->value());
		sum += kernel[i];
	}

	cout << endl;

	if (enableNormalize) {
		if (sum <= 0) {
			fl_alert("The sum of the weight is not positive,can not normalize!");
			return;
		}
		for (int i = 0; i < kernelSize; i++) {
			kernel[i] = kernel[i] / sum;
			cout << kernel[i] << endl;;
		}
	}

	for (int i = 0; i < m_nHeight*m_nWidth; i++) {
		int row = i / m_nWidth;
		int col = i % m_nWidth;
		rgb = new float[3];
		memset(rgb, 0, 3);
		applyFilter(row, col, kernelWidth, kernelHeight, kernel,rgb,preservedPainting);
		if (rgb[0] == 256)
			continue;
		m_ucPainting[i * 4] = rgb[0];
		m_ucPainting[i * 4 + 1] = rgb[1];
		m_ucPainting[i * 4 + 2] = rgb[2];
		delete[]rgb;
	}
	m_pUI->m_paintView->refresh();
	m_pCurrentBrush->saveState();
}

void ImpressionistDoc::applyFilter(int row, int col,int kernelWidth,int kernelHeight,float*kernel,float* rgb,unsigned char* painting) {
	/*
	if (m_ucPainting[row*m_nWidth + col + 3] == 0) {
		rgb[0] = 256;
		return;
	}
	
	*/
	
	/*int beginKernelX = 0;
	int endKernelX = kernelWidth - 1;
	int beginKernelY = 0;
	int endKernelY = kernelHeight - 1;
	
	if (row < kernelHeight / 2) {
		beginKernelY = kernelHeight / 2 - row;
		endKernelY = kernelHeight / 2 + row;
	}
	if (col < kernelWidth / 2) {
		beginKernelX = kernelWidth / 2 - col;
		endKernelX -= kernelWidth / 2 - col;
	}
	*/
	int beginY = -kernelHeight / 2;
	int beginX = -kernelWidth / 2;
	
	
	for (int color = 0; color < 3; color++) {
		float result = 0;
		for (int Y = beginY; Y < -beginY + 1; Y++) {
			for (int X = beginX; X < -beginX + 1; X++) {
				//float value = atof(m_pUI->m_filterKernelInputMatrix.at((Y - beginY + beginKernelY)*kernelWidth + X - beginX + beginKernelX)->value());
				//cout << value<<endl;
				//cout << (Y - beginY + beginKernelY)*kernelWidth + X - beginX + beginKernelX << endl;
				int x, y;
				if (col + X >= m_nWidth)
					x = m_nWidth * 2 - (col + X) - 1;
				else
					x = abs(col + X);

				if (row + Y >= m_nHeight)
					y = m_nHeight * 2 - (row + Y) -1;
				else
					y = abs(row + Y);

				int positionOfPainting = (y*m_nWidth + x) * 4;
				int positionOfKernel = (Y - beginY)*kernelWidth + X - beginX;
				result += ((float)painting[positionOfPainting + color] )* kernel[positionOfKernel];
				//cout << ((row + Y)*m_nWidth + col + X);
			}
		}
		if (result > 255)
			result = 255;
		if (result < 0)
			result = 0;
		//cout << result;
		rgb[color] = result;
	}

}

float ImpressionistDoc::applySobel(int row, int col,bool calculateGradient,const unsigned char* source) {

	float gradient = 0;
	int Gx = 0;
	int Gy = 0.0;
	/*
	for (int Y = -1; Y < 2; Y++) {
		for (int X = -1; X < 2; X++) {
			
			int x, y;
			//special contidion
			if (col + X >= m_nWidth)
				x = m_nWidth * 2 - (col + X) - 1;
			else
				x = abs(col + X);

			if (row + Y >= m_nHeight)
				y = m_nHeight * 2 - (row + Y) - 1;
			else
				y = abs(row + Y);

			int mapPosition = y * m_nWidth + x;
			int filterPosition = (Y + 1) * 3 + X + 1;
			
			Gx += source[mapPosition] * sobelVertical[filterPosition];
			Gy += source[mapPosition] * sobelHorizontal[filterPosition];
		}
	}
	*/

	Gx = -source[(row - 1)*m_nWidth + col - 1] + source[(row - 1)*m_nWidth + col + 1] - 2 * source[(row)*m_nWidth + col - 1] + 2 * source[(row)*m_nWidth + col + 1] - source[(row + 1)*m_nWidth + col - 1] + source[(row + 1)*m_nWidth + col + 1];
	Gy = -source[(row - 1)*m_nWidth + col - 1] + source[(row + 1)*m_nWidth + col - 1] - 2 * source[(row - 1)*m_nWidth + col] + 2 * source[(row + 1)*m_nWidth + col] - source[(row - 1)*m_nWidth + col + 1] + source[(row + 1)*m_nWidth + col + 1];
	if (calculateGradient) {
		if (Gx == 0)
			return 90;
		else {
			//cout << Gx << ",";
			return atan((double)Gy / Gx);
			
		}
	}
	gradient = sqrt(Gx * Gx + Gy * Gy);
	//cout << gradient << ",";
	return gradient;
}

void ImpressionistDoc::generateEdgeImage() {

	int threshold = m_pUI->getThreshold();
	if (m_ucEdgeBitmap)delete[]m_ucEdgeBitmap;
	if (m_ucEdgePositionMap)delete[]m_ucEdgePositionMap;
	m_ucEdgeBitmap = new unsigned char[m_nHeight*m_nWidth * 3];
	m_ucEdgePositionMap = new bool[m_nHeight*m_nWidth];
	memset(m_ucEdgeBitmap, 0, m_nHeight*m_nWidth * 3);
	memset(m_ucEdgePositionMap, 0, m_nHeight*m_nWidth);

	for (int i = 0; i < m_nHeight*m_nWidth; i++) {
		if (m_ucGradientMap[i] >= threshold) {
			m_ucEdgeBitmap[i * 3] = 255;
			m_ucEdgeBitmap[i * 3 + 1] = 255;
			m_ucEdgeBitmap[i * 3 + 2] = 255;
			m_ucEdgePositionMap[i] = true;
		}
	}

	m_pUI->m_origView->setViewType(EDGE_IMAGE);
	m_pUI->m_origView->refresh();

}


void ImpressionistDoc::applyGaussianFilter(unsigned char* source, unsigned char* target,int width,int height) {

	for (int i = 0; i < width*height; i++) {
		int x = i % width;
		int y = i / width;
		float rgb[3] = { 0,0,0 };
		for (int Y = -1; Y < 2; Y++) {
			for (int X = -1; X < 2; X++) {
				int x0, y0;
				if (x + X >= width)
					x0 = width * 2 - (x + X) - 1;
				else
					x0 = abs(x + X);
				if (y + Y >= height)
					y0 = height * 2 - (y + Y) - 1;
				else
					y0 = abs(y + Y);

				int mapPosition = (y0 * width + x0) * 3;
				int filterPosition = (Y + 1) * 3 + (X + 1);
				rgb[0] += source[mapPosition] * gaussianFilter[filterPosition];
				rgb[1] += source[mapPosition + 1] * gaussianFilter[filterPosition];
				rgb[2] += source[mapPosition + 2] * gaussianFilter[filterPosition];
			}
		}
		target[i * 3] = rgb[0];
		target[i * 3 + 1] = rgb[1];
		target[i * 3 + 2] = rgb[2];
	}
}
