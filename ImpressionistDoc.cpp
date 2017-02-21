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
	ImpBrush::c_pBrushes[BRUSH_ALPHA_MAP]
		= new AlphaMapBrush(this,"Alpha Map");

	// make one of the brushes current
	m_pCurrentBrush	= ImpBrush::c_pBrushes[0];

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

	m_ucBitmapOrigin = new unsigned char[width*height * 3];
	memcpy(m_ucBitmapOrigin, data, width*height * 3);
	m_ucBitmap		= data;
	
	// allocate space for draw view
	m_ucPainting	= new unsigned char [width*height*4];
	m_ucBackup = new unsigned char[width*height * 4];
	memset(m_ucPainting, 0, width*height*4);
	memset(m_ucBackup, 0, width*height * 4);
	
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