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
using namespace std;
class ImpressionistUI;

//the type of the line brush direction control
enum {SLIDER_RMOUSE = 0,GRADIENT,CURSOR};
class ImpressionistDoc 
{
public:
	ImpressionistDoc();

	void	setUI(ImpressionistUI* ui);		// Assign the UI to use

	int		loadImage(char *iname);			// called by the UI to load image
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
	unsigned char*	m_ucPainting;
	unsigned char*	m_ucBitmapOrigin;
	unsigned char*  m_ucDissolve;
	unsigned char*  m_ucBackup;
	//unsigned char*  m_ucBackupImage;//used in dim function
	unsigned char*	m_ucAlphamap;

	// The current active brush.
	ImpBrush*			m_pCurrentBrush;	
	
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


private:
	char			m_imageName[256];

};

extern void MessageBox(char *message);

#endif
