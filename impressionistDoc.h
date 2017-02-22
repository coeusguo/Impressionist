// 
// impressionistDoc.h
//
// header file for Doc 
//

#ifndef ImpressionistDoc_h
#define ImpressionistDoc_h

#include "impressionist.h"
#include "bitmap.h"
#include <stack>
#include <math.h>
using namespace std;
class ImpressionistUI;

//the type of the line brush direction control
enum {SLIDER_RMOUSE = 0,GRADIENT,CURSOR,ANOTHER_IMAGE_GRADIENT};
class ImpressionistDoc 
{
public:
	ImpressionistDoc();

	void	setUI(ImpressionistUI* ui);		// Assign the UI to use

	int		loadImage(char *iname);			// called by the UI to load image
	int		loadAnotherImage(char *iname);
	int		loadEdgeImage(char *iname);
	int		saveImage(char *iname);			// called by the UI to save image
	int		dissolveImage(char *iname);		// called by the UI to dissolve image
	int		muralImage(char *iname);		// mural image
	int		alphaMapBrush(char *iname);

	int     clearCanvas();                  // called by the UI to clear the drawing canvas
	void	setBrushType(int type);			// called by the UI to set the brushType
	void	setBrushDirectionType(int type);
	int		getSize();						// get the UI size
	int		getLineWidth();
	int		getLineAngle();
	double	getAlpha();
	void	setSize(int size);				// set the UI size
	void	setLineAngle(int lineAngle);
	char*	getImageName();					// get the current image name
	void	applyKernelFilter();
	void 	applyFilter(int row, int col, int kernelWidth, int kernelHeight,float* kernel,float* rgb,unsigned char* painting);
	float	applySobel(int row, int col,bool calculateGradient,const unsigned char* source);
	void	applyGaussianFilter(unsigned char* source, unsigned char* target,int width,int height);
	int*    getGradientBySobel(const unsigned char* image, int width, int height);
	void	generateEdgeImage();
	stack<unsigned char*>	history;

// Attributes
public:
	// Dimensions of original window.
	int				m_nWidth, 
					m_nHeight;
	// Dimensions of the paint window.
	int				m_nPaintWidth, 
					m_nPaintHeight;	
	// Dimensions of the alpha map
	int				m_nAlphaMapWidth,
					m_nAlphaMapHeight;
	// Bitmaps for original image and painting.
	unsigned char*	m_ucBitmap;
	unsigned char*  m_ucEdgeBitmap;//edge bitmap of m_ucBitmap or loaded black and white bitmap
	unsigned char*  m_ucGrayScaleMap;//m_ucBitmap gray scale map
	float*			m_ucGradientMap;//gradient value of each pixel of m_ucBitmap
	bool*			m_ucEdgePositionMap;//edge position of uc_edgeBitmap,used by edge clipping

	unsigned char*  m_ucAnotherBitmap;//another bitmap graycale form
	float*			m_ucAnotherGradientMap;//gradient of another image

	
	
	

	unsigned char*	m_ucPainting;
	unsigned char*	m_ucBitmapOrigin;
	unsigned char*  m_ucDissolve;
	unsigned char*  m_ucBackup;
	//unsigned char*  m_ucBackupImage;//used in dim function
	unsigned char*	m_ucAlphamap;

	// The current active brush.
	ImpBrush*			m_pCurrentBrush;	
	int					currentType;
	//current active line brush direction control type
	int m_pControlType;

	// Size of the brush.
	int m_nSize;							
	//width of the (scatter) line brush
	int m_nLineWidth;

	ImpressionistUI*	m_pUI;

// Operations
public:
	// Get the color of the original picture at the specified coord
	GLubyte* GetOriginalPixel( int x, int y );   
	// Get the color of the original picture at the specified point	
	GLubyte* GetOriginalPixel( const Point p );  

	int sobelVertical[9];
	int sobelHorizontal[9];
	int gaussianFilter[9];
private:
	char			m_imageName[256];
	
	

};

extern void MessageBox(char *message);

#endif
