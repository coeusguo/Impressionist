//
// impressionistUI.h
//
// The user interface part for the program.
//


#include <FL/fl_ask.h>

#include <math.h>

#include "impressionistUI.h"
#include "impressionistDoc.h"
#include <iostream>
using namespace std;

/*
//------------------------------ Widget Examples -------------------------------------------------
Here is some example code for all of the widgets that you may need to add to the 
project.  You can copy and paste these into your code and then change them to 
make them look how you want.  Descriptions for all of the widgets here can be found 
in links on the fltk help session page.

//---------Window/Dialog and Menubar-----------------------------------
	
	//----To install a window--------------------------
	Fl_Window* myWindow = new Fl_Window(600, 300, "MyWindow");
		myWindow->user_data((void*)(this));	// record self to be used by static callback functions
		
		// install menu bar
		myMenubar = new Fl_Menu_Bar(0, 0, 600, 25);
		Fl_Menu_Item ImpressionistUI::myMenuItems[] = {
			{ "&File",		0, 0, 0, FL_SUBMENU },
				{ "&Load...",	FL_ALT + 'l', (Fl_Callback *)ImpressionistUI::cb_load },
				{ "&Save...",	FL_ALT + 's', (Fl_Callback *)ImpressionistUI::cb_save }.
				{ "&Quit",			FL_ALT + 'q', (Fl_Callback *)ImpressionistUI::cb_exit },
				{ 0 },
			{ "&Edit",		0, 0, 0, FL_SUBMENU },
				{ "&Copy",FL_ALT + 'c', (Fl_Callback *)ImpressionistUI::cb_copy, (void *)COPY },
				{ "&Cut",	FL_ALT + 'x', (Fl_Callback *)ImpressionistUI::cb_cut, (void *)CUT },
				{ "&Paste",	FL_ALT + 'v', (Fl_Callback *)ImpressionistUI::cb_paste, (void *)PASTE },
				{ 0 },
			{ "&Help",		0, 0, 0, FL_SUBMENU },
				{ "&About",	FL_ALT + 'a', (Fl_Callback *)ImpressionistUI::cb_about },
				{ 0 },
			{ 0 }
		};
		myMenubar->menu(myMenuItems);
    m_mainWindow->end();

	//----The window callback--------------------------
	// One of the callbacks
	void ImpressionistUI::cb_load(Fl_Menu_* o, void* v) 
	{	
		ImpressionistDoc *pDoc=whoami(o)->getDocument();

		char* newfile = fl_file_chooser("Open File?", "*.bmp", pDoc->getImageName() );
		if (newfile != NULL) {
			pDoc->loadImage(newfile);
		}
	}


//------------Slider---------------------------------------

	//----To install a slider--------------------------
	Fl_Value_Slider * mySlider = new Fl_Value_Slider(10, 80, 300, 20, "My Value");
	mySlider->user_data((void*)(this));	// record self to be used by static callback functions
	mySlider->type(FL_HOR_NICE_SLIDER);
    mySlider->labelfont(FL_COURIER);
    mySlider->labelsize(12);
	mySlider->minimum(1);
	mySlider->maximum(40);
	mySlider->step(1);
	mySlider->value(m_nMyValue);
	mySlider->align(FL_ALIGN_RIGHT);
	mySlider->callback(cb_MyValueSlides);

	//----The slider callback--------------------------
	void ImpressionistUI::cb_MyValueSlides(Fl_Widget* o, void* v)
	{
		((ImpressionistUI*)(o->user_data()))->m_nMyValue=int( ((Fl_Slider *)o)->value() ) ;
	}
	

//------------Choice---------------------------------------
	
	//----To install a choice--------------------------
	Fl_Choice * myChoice = new Fl_Choice(50,10,150,25,"&myChoiceLabel");
	myChoice->user_data((void*)(this));	 // record self to be used by static callback functions
	Fl_Menu_Item ImpressionistUI::myChoiceMenu[3+1] = {
	  {"one",FL_ALT+'p', (Fl_Callback *)ImpressionistUI::cb_myChoice, (void *)ONE},
	  {"two",FL_ALT+'l', (Fl_Callback *)ImpressionistUI::cb_myChoice, (void *)TWO},
	  {"three",FL_ALT+'c', (Fl_Callback *)ImpressionistUI::cb_myChoice, (void *)THREE},
	  {0}
	};
	myChoice->menu(myChoiceMenu);
	myChoice->callback(cb_myChoice);
	
	//-----The choice callback-------------------------
	void ImpressionistUI::cb_myChoice(Fl_Widget* o, void* v)
	{
		ImpressionistUI* pUI=((ImpressionistUI *)(o->user_data()));
		ImpressionistDoc* pDoc=pUI->getDocument();

		int type=(int)v;

		pDoc->setMyType(type);
	}


//------------Button---------------------------------------

	//---To install a button---------------------------
	Fl_Button* myButton = new Fl_Button(330,220,50,20,"&myButtonLabel");
	myButton->user_data((void*)(this));   // record self to be used by static callback functions
	myButton->callback(cb_myButton);

	//---The button callback---------------------------
	void ImpressionistUI::cb_myButton(Fl_Widget* o, void* v)
	{
		ImpressionistUI* pUI=((ImpressionistUI*)(o->user_data()));
		ImpressionistDoc* pDoc = pUI->getDocument();
		pDoc->startPainting();
	}


//---------Light Button------------------------------------
	
	//---To install a light button---------------------
	Fl_Light_Button* myLightButton = new Fl_Light_Button(240,10,150,25,"&myLightButtonLabel");
	myLightButton->user_data((void*)(this));   // record self to be used by static callback functions
	myLightButton->callback(cb_myLightButton);

	//---The light button callback---------------------
	void ImpressionistUI::cb_myLightButton(Fl_Widget* o, void* v)
	{
		ImpressionistUI *pUI=((ImpressionistUI*)(o->user_data()));

		if (pUI->myBool==TRUE) pUI->myBool=FALSE;
		else pUI->myBool=TRUE;
	}

//----------Int Input--------------------------------------

    //---To install an int input-----------------------
	Fl_Int_Input* myInput = new Fl_Int_Input(200, 50, 5, 5, "&My Input");
	myInput->user_data((void*)(this));   // record self to be used by static callback functions
	myInput->callback(cb_myInput);

	//---The int input callback------------------------
	void ImpressionistUI::cb_myInput(Fl_Widget* o, void* v)
	{
		((ImpressionistUI*)(o->user_data()))->m_nMyInputValue=int( ((Fl_Int_Input *)o)->value() );
	}

//------------------------------------------------------------------------------------------------
*/

//------------------------------------- Help Functions --------------------------------------------

//------------------------------------------------------------
// This returns the UI, given the menu item.  It provides a
// link from the menu items to the UI
//------------------------------------------------------------
ImpressionistUI* ImpressionistUI::whoami(Fl_Menu_* o)	
{
	return ( (ImpressionistUI*)(o->parent()->user_data()) );
}


//--------------------------------- Callback Functions --------------------------------------------

//------------------------------------------------------------------
// Brings up a file chooser and then loads the chosen image
// This is called by the UI when the load image menu item is chosen
//------------------------------------------------------------------
void ImpressionistUI::cb_load_image(Fl_Menu_* o, void* v) 
{
	ImpressionistDoc *pDoc=whoami(o)->getDocument();

	char* newfile = fl_file_chooser("Open File?", "*.bmp", pDoc->getImageName() );
	if (newfile != NULL) {
		pDoc->loadImage(newfile);
	}
}


//------------------------------------------------------------------
// Brings up a file chooser and then saves the painted image
// This is called by the UI when the save image menu item is chosen
//------------------------------------------------------------------
void ImpressionistUI::cb_save_image(Fl_Menu_* o, void* v) 
{
	ImpressionistDoc *pDoc=whoami(o)->getDocument();

	char* newfile = fl_file_chooser("Save File?", "*.bmp", "save.bmp" );
	if (newfile != NULL) {
		pDoc->saveImage(newfile);
	}
}

//-------------------------------------------------------------
// Brings up the paint dialog
// This is called by the UI when the brushes menu item
// is chosen
//-------------------------------------------------------------
void ImpressionistUI::cb_brushes(Fl_Menu_* o, void* v) 
{
	whoami(o)->m_brushDialog->show();
	
}

//------------------------------------------------------------
// Clears the paintview canvas.
// Called by the UI when the clear canvas menu item is chosen
//------------------------------------------------------------
void ImpressionistUI::cb_clear_canvas(Fl_Menu_* o, void* v)
{
	ImpressionistDoc* pDoc=whoami(o)->getDocument();

	pDoc->clearCanvas();
}

//------------------------------------------------------------
// Causes the Impressionist program to exit
// Called by the UI when the quit menu item is chosen
//------------------------------------------------------------
void ImpressionistUI::cb_exit(Fl_Menu_* o, void* v) 
{
	whoami(o)->m_mainWindow->hide();
	whoami(o)->m_brushDialog->hide();

}



//-----------------------------------------------------------
// Brings up an about dialog box
// Called by the UI when the about menu item is chosen
//-----------------------------------------------------------
void ImpressionistUI::cb_about(Fl_Menu_* o, void* v) 
{
	fl_message("Impressionist FLTK version for CS341, Spring 2002");
}

//------- UI should keep track of the current for all the controls for answering the query from Doc ---------
//-------------------------------------------------------------
// Sets the type of brush to use to the one chosen in the brush 
// choice.  
// Called by the UI when a brush is chosen in the brush choice
//-------------------------------------------------------------
void ImpressionistUI::cb_brushChoice(Fl_Widget* o, void* v)
{
	ImpressionistUI* pUI=((ImpressionistUI *)(o->user_data()));
	ImpressionistDoc* pDoc=pUI->getDocument();

	int type=(int)v;


	pDoc->setBrushType(type);
	if (type != BRUSH_LINES && type != BRUSH_SCATTERED_LINES) {
		pUI->m_LineWidthSlider->deactivate();
		pUI->m_LineAngleSlider->deactivate();
	}
	else {
		pUI->m_LineWidthSlider->activate();
		pUI->m_LineAngleSlider->activate();
	}

	if (type == BRUSH_SHARPEN_POINTS || type == BRUSH_BLUR_POINTS||type ==BRUSH_ALPHA_MAP) {
		pUI->m_BrushSizeSlider->deactivate();
		if(type !=BRUSH_ALPHA_MAP)
			pUI->m_AlphaSlider->deactivate();
	}
	else {
		pUI->m_BrushSizeSlider->activate();
		pUI->m_AlphaSlider->activate();
	}
}

void ImpressionistUI::cb_brushDirectionType(Fl_Widget* o, void* v) {
	ImpressionistUI* pUI = ((ImpressionistUI *)(o->user_data()));
	ImpressionistDoc* pDoc = pUI->getDocument();
	int type = (int)v;
	pDoc->setBrushDirectionType(type);
}
//------------------------------------------------------------
// Clears the paintview canvas.
// Called by the UI when the clear canvas button is pushed
//------------------------------------------------------------
void ImpressionistUI::cb_clear_canvas_button(Fl_Widget* o, void* v)
{
	ImpressionistDoc * pDoc = ((ImpressionistUI*)(o->user_data()))->getDocument();

	pDoc->clearCanvas();
}


//-----------------------------------------------------------
// Updates the brush size to use from the value of the size
// slider
// Called by the UI when the size slider is moved
//-----------------------------------------------------------
void ImpressionistUI::cb_sizeSlides(Fl_Widget* o, void* v)
{
	((ImpressionistUI*)(o->user_data()))->m_nSize=int( ((Fl_Slider *)o)->value() ) ;
}
//-----------------------------------------------------------
// Updates the brush line width to use from the value of the size
// slider
// Called by the UI when the size slider is moved
//-----------------------------------------------------------
void ImpressionistUI::cb_LineWidthSlides(Fl_Widget* o, void* v)
{
	((ImpressionistUI*)(o->user_data()))->m_nLineWidth = int(((Fl_Slider *)o)->value());
}
//-----------------------------------------------------------
// Updates the brush line angle to use from the value of the size
// slider
// Called by the UI when the size slider is moved
//-----------------------------------------------------------
void ImpressionistUI::cb_LineAngleSlides(Fl_Widget* o, void* v)
{
	((ImpressionistUI*)(o->user_data()))->m_nLineAngle = int(((Fl_Slider *)o)->value());
}
//-----------------------------------------------------------
// Updates the brush alpha value to use from the value of the size
// slider
// Called by the UI when the size slider is moved
//-----------------------------------------------------------
void ImpressionistUI::cb_AlphaSlides(Fl_Widget* o, void* v)
{
	((ImpressionistUI*)(o->user_data()))->m_nAlpha = float(((Fl_Slider *)o)->value());
}
//-----------------------------------------------------------
// Swap paint window and original window
//-----------------------------------------------------------
void ImpressionistUI::cb_SwapWindows(Fl_Menu_* o, void* v) {
	ImpressionistDoc* pDoc = whoami(o)->getDocument();
	unsigned char*	tempdata;

	tempdata = pDoc->m_ucBitmap;
	if (pDoc->m_ucBitmapOrigin) delete[]pDoc->m_ucBitmapOrigin;
	
	//format transform
	unsigned char* data = new unsigned char[pDoc->m_nWidth*pDoc->m_nHeight * 3];
	for (int i = 0; i < pDoc->m_nPaintHeight*pDoc->m_nPaintWidth; i++) {
		data[i * 3] = pDoc->m_ucPainting[4 * i];
		data[i * 3 + 1] = pDoc->m_ucPainting[4 * i + 1];
		data[i * 3 + 2] = pDoc->m_ucPainting[4 * i + 2];
	}

	//used by independent RGB scalling
	pDoc->m_ucBitmapOrigin = new unsigned char[pDoc->m_nWidth*pDoc->m_nHeight * 3];
	memcpy(pDoc->m_ucBitmapOrigin, data, pDoc->m_nWidth*pDoc->m_nHeight * 3);

	//swap paintView to originView
	pDoc->m_ucBitmap = data;
	//create a new paintView
	if (pDoc->m_ucPainting)delete[]pDoc->m_ucPainting;
	for (int i = 0; i < pDoc->m_nPaintHeight*pDoc->m_nPaintWidth; i++) {
		pDoc->m_ucPainting[4 * i] = tempdata[3 * i];
		pDoc->m_ucPainting[4 * i + 1] = tempdata[3 * i + 1];
		pDoc->m_ucPainting[4 * i + 2] = tempdata[3 * i + 2];
		pDoc->m_ucPainting[4 * i + 3] = 255;
	}
	delete[]tempdata;
	pDoc->m_pUI->m_paintView->refresh();
	pDoc->m_pUI->m_origView->refresh();

}
//-----------------------------------------------------------
// Independent RGB color scalling
//-----------------------------------------------------------
void ImpressionistUI::cb_colors(Fl_Menu_* o, void* v) {
	whoami(o)->m_colorDialog->show();
}
//-----------------------------------------------------------
// Independent RGB color scalling for Red
//-----------------------------------------------------------
void ImpressionistUI::cb_RedSlides(Fl_Widget* o, void* v)
{
	((ImpressionistUI*)(o->user_data()))->m_nRedScale = float(((Fl_Slider *)o)->value());
}
//-----------------------------------------------------------
// Independent RGB color scalling for Green
//-----------------------------------------------------------
void ImpressionistUI::cb_GreenSlides(Fl_Widget* o, void* v)
{
	((ImpressionistUI*)(o->user_data()))->m_nGreenScale = float(((Fl_Slider *)o)->value());
}
//-----------------------------------------------------------
// Independent RGB color scalling for Blue
//-----------------------------------------------------------
void ImpressionistUI::cb_BlueSlides(Fl_Widget* o, void* v)
{
	((ImpressionistUI*)(o->user_data()))->m_nBlueScale = float(((Fl_Slider *)o)->value());
}

void ImpressionistUI::cb_ApplyColorScaling(Fl_Widget* o, void* v) {
	
	ImpressionistDoc* pDoc = ((ImpressionistUI*)(o->user_data()))->m_pDoc;
	if (pDoc->m_ucBitmap == NULL) {
		printf("No image is loaded now");
		return;
	}
	int width = pDoc->m_nWidth;
	int height = pDoc->m_nHeight;
	memcpy(pDoc->m_ucBitmap, pDoc->m_ucBitmapOrigin, width*height * 3);
	unsigned char* image = pDoc->m_ucBitmap;
	
	for (int i = 0; i < width*height; i++) {
		image[i * 3] *= pDoc->m_pUI->m_nRedScale;
		image[i * 3 + 1] *= pDoc->m_pUI->m_nGreenScale;
		image[i * 3 + 2] *= pDoc->m_pUI->m_nBlueScale;
	}
	pDoc->m_pUI->m_origView->refresh();
}
//------------------------------------------------
// undo
//------------------------------------------------
void ImpressionistUI::cb_undo(Fl_Menu_* o, void* v) {
	ImpressionistDoc *pDoc = whoami(o)->getDocument();
	if (!pDoc->history.empty()) {
		delete[]pDoc->m_ucPainting;
		pDoc->m_ucPainting = pDoc->history.top();
		pDoc->history.pop();
		pDoc->m_pUI->m_paintView->refresh();
	}
}
//------------------------------------------------
// load dissolve image
//------------------------------------------------
void ImpressionistUI::cb_dissolve_image(Fl_Menu_* o, void* v) {
	ImpressionistDoc *pDoc = whoami(o)->getDocument();
	char* newfile = fl_file_chooser("Open File?", "*.bmp", pDoc->getImageName());
	if (newfile != NULL) {
		pDoc->dissolveImage(newfile);
	}
}
//------------------------------------------------
// load mural image
//------------------------------------------------
void ImpressionistUI::cb_mural_image(Fl_Menu_* o, void* v) {
	ImpressionistDoc *pDoc = whoami(o)->getDocument();
	char* newfile = fl_file_chooser("Open File?", "*.bmp", pDoc->getImageName());
	if (newfile != NULL) {
		pDoc->muralImage(newfile);
	}
}
//------------------------------------------------
// load a image for alpha map brush
//------------------------------------------------
void ImpressionistUI::cb_load_alpha_map(Fl_Menu_* o, void* v) {
	ImpressionistDoc *pDoc = whoami(o)->getDocument();
	char* newfile = fl_file_chooser("Open File?", "*.bmp", pDoc->getImageName());
	if (newfile != NULL) {
		pDoc->alphaMapBrush(newfile);
	}


}
//------------------------------------------------
// dimmed view dialog
//------------------------------------------------
void ImpressionistUI::cb_ShowDimDialog(Fl_Menu_* o, void* v) {
	whoami(o)->m_dimDialog->show();
}
void ImpressionistUI::cb_dimAlphaSlides(Fl_Widget* o, void* v) {
	ImpressionistUI* pUI = ((ImpressionistUI*)(o->user_data()));
	pUI->m_nDimAlpha = float(((Fl_Slider *)o)->value());
	pUI->m_paintView->refresh();
}
void ImpressionistUI::cb_dim_button(Fl_Widget* o, void* v) {
	ImpressionistUI* pUI = ((ImpressionistUI*)(o->user_data()));
	pUI->m_nShowDimImage = !pUI->m_nShowDimImage;
	pUI->m_paintView->refresh();
}

//------------------------------------------------
// functions of auto painting
//------------------------------------------------
void ImpressionistUI::cb_AutoPaintSpacingSlides(Fl_Widget* o, void* v) {
	((ImpressionistUI*)(o->user_data()))->m_nSpacing = float(((Fl_Slider *)o)->value());
}
void ImpressionistUI::cb_Rand_Attr_button(Fl_Widget* o, void* v) {
	ImpressionistUI* pUI = ((ImpressionistUI*)(o->user_data()));
	pUI->m_nRandomAttr = !pUI->m_nRandomAttr;
}
void ImpressionistUI::cb_Auto_Paint_button(Fl_Widget* o, void* v) {
	ImpressionistUI* pUI = ((ImpressionistUI*)(o->user_data()));
	pUI->m_nEnableAutoDraw = true;
	pUI->m_paintView->refresh();
}
//------------------------------------------------
// set the size of filter kernel
//------------------------------------------------
void ImpressionistUI::cb_filter_kernel_setting(Fl_Menu_* o, void* v) {
	if (whoami(o)->getDocument()->m_ucBitmap == NULL) {
		fl_alert("Plase load a image first!");
		return;
	}
	whoami(o)->m_FilterKernelSettingDialog->show();
}
void ImpressionistUI::cb_confirm_kernel_button(Fl_Widget* o, void* v) {
	ImpressionistUI* pUI = ((ImpressionistUI*)(o->user_data()));
	string widthString = pUI->m_NumColsInput->value();
	string heightString = pUI->m_NumRowsInput->value();

	if (widthString.length() == 0 || heightString.length() == 0) {
		fl_alert("Please enter a number");
		return;
	}

	pUI->m_nKernelWidth = atoi(pUI->m_NumColsInput->value());
	pUI->m_nKernelHeight = atoi(pUI->m_NumRowsInput->value());

	int windowWidth = pUI->m_nKernelWidth * 40 + 10;
	int windowHeight = pUI->m_nKernelHeight * 30 + 40;

	if (pUI->m_nKernelWidth % 2 == 0 || pUI->m_nKernelHeight % 2 == 0) {
		fl_alert("Please enter an odd number");
		return;
	}
	pUI->m_FilterKernelSettingDialog->hide();

	pUI->m_FilterKernelDialog = new Fl_Window(max(210, windowWidth), windowHeight, "Kernel Filter Dialog");

	if (!pUI->m_filterKernelInputMatrix.empty()) {
		for (Fl_Float_Input* n : pUI->m_filterKernelInputMatrix)
			delete n;
	}
	pUI->m_filterKernelInputMatrix.clear();
	if (pUI->m_Normalize)delete pUI->m_Normalize;
	if (pUI->m_ApplyFilterKernel)delete pUI->m_ApplyFilterKernel;

	for (int i = 0; i < pUI->m_nKernelWidth*pUI->m_nKernelHeight; i++) {
		Fl_Float_Input* input = new Fl_Float_Input(10+(i%pUI->m_nKernelWidth)*40, 10+(i/ pUI->m_nKernelWidth)*30, 30, 20, "");
		input->labelfont(FL_COURIER);
		input->value("0");
		pUI->m_filterKernelInputMatrix.push_back(input);
	}

	pUI->m_Normalize = new Fl_Light_Button(10, windowHeight-30, 100, 25, "&Normalize");
	pUI->m_Normalize->user_data((void*)(pUI));
	pUI->m_Normalize->callback(cb_normalize_toggle_button);
	pUI->m_Normalize->value(pUI->m_nEnableNormalize);

	pUI->m_ApplyFilterKernel = new Fl_Button(max(210, windowWidth)-80, windowHeight - 30, 70, 25, "&Apply");
	pUI->m_ApplyFilterKernel->user_data((void*)(pUI));
	pUI->m_ApplyFilterKernel->callback(cb_ApplyFilterKernel);

	pUI->m_FilterKernelDialog->end();
	pUI->m_FilterKernelDialog->show();
}

void ImpressionistUI::cb_ApplyFilterKernel(Fl_Widget* o, void* v) {
	ImpressionistUI* pUI = ((ImpressionistUI*)(o->user_data()));
	/*
	for (int i = 0; i < pUI->m_nKernelHeight*pUI->m_nKernelHeight; i++)
		cout << atoi(pUI->m_filterKernelInputMatrix.at(i)->value())<<endl;
	return;
	*/
	((ImpressionistUI*)(o->user_data()))->m_pDoc->applyKernelFilter();
}
void ImpressionistUI::cb_normalize_toggle_button(Fl_Widget* o, void* v) {
	((ImpressionistUI*)(o->user_data()))->m_nEnableNormalize = !((ImpressionistUI*)(o->user_data()))->m_nEnableNormalize;
}
//---------------------------------- per instance functions --------------------------------------

//------------------------------------------------
// Return the ImpressionistDoc used
//------------------------------------------------
ImpressionistDoc* ImpressionistUI::getDocument()
{
	return m_pDoc;
}

//------------------------------------------------
// Draw the main window
//------------------------------------------------
void ImpressionistUI::show() {
	m_mainWindow->show();
	m_paintView->show();
	m_origView->show();
}

//------------------------------------------------
// Change the paint and original window sizes to 
// w by h
//------------------------------------------------
void ImpressionistUI::resize_windows(int w, int h) {
	m_paintView->size(w,h);
	m_origView->size(w,h);
}

//------------------------------------------------ 
// Set the ImpressionistDoc used by the UI to 
// communicate with the brushes 
//------------------------------------------------
void ImpressionistUI::setDocument(ImpressionistDoc* doc)
{
	m_pDoc = doc;

	m_origView->m_pDoc = doc;
	m_paintView->m_pDoc = doc;
}

//------------------------------------------------
// Return the brush size
//------------------------------------------------
int ImpressionistUI::getSize()
{
	return m_nSize;
}
//------------------------------------------------
// Return the brush line width
//------------------------------------------------
int ImpressionistUI::getLineWidth() 
{
	return m_nLineWidth;
}
//------------------------------------------------
// Return the brush line angle
//------------------------------------------------
int ImpressionistUI::getLineAngle()
{
	return m_nLineAngle;

}
//------------------------------------------------
// Return the brush alpha value
//------------------------------------------------
double ImpressionistUI::getAlpha()
{
	return m_nAlpha;

}
//-------------------------------------------------
// Set the brush size
//-------------------------------------------------
void ImpressionistUI::setSize( int size )
{
	m_nSize=size;

	if (size<=40) 
		m_BrushSizeSlider->value(m_nSize);
}

void ImpressionistUI::setLineWidth(int width) {
	m_nLineWidth = width;
}

void ImpressionistUI::setLineAngle(int angle) {
	m_nLineAngle = angle;
	m_LineAngleSlider->value(m_nLineAngle);
}
int ImpressionistUI::getSpacing() {
	return m_nSpacing;
}

bool ImpressionistUI::getRandomAttr() {
	return m_nRandomAttr;
}

bool ImpressionistUI::getEnableAutoDraw() {
	return m_nEnableAutoDraw;
}

void ImpressionistUI::setEnableAutoDraw(bool value) {
	m_nEnableAutoDraw = value;
}

bool ImpressionistUI::getEnableNormalize() {
	return m_nEnableNormalize;
}

int ImpressionistUI::getKernelWidth() {
	return m_nKernelWidth;
}

int ImpressionistUI::getKernelHeight() {
	return m_nKernelHeight;
}

// Main menu definition
Fl_Menu_Item ImpressionistUI::menuitems[] = {
	{ "&File",		0, 0, 0, FL_SUBMENU },
		{ "&Load Image...",	FL_ALT + 'l', (Fl_Callback *)ImpressionistUI::cb_load_image },
		{ "&Save Image...",	FL_ALT + 's', (Fl_Callback *)ImpressionistUI::cb_save_image },
		{ "&Dissolve Image...",	FL_ALT + 'd', (Fl_Callback *)ImpressionistUI::cb_dissolve_image },
		{ "&New Mural Image...",	FL_ALT + 'm', (Fl_Callback *)ImpressionistUI::cb_mural_image },
		{ "&Load Alpha-mapped Brush",	FL_ALT + 'a', (Fl_Callback *)ImpressionistUI::cb_load_alpha_map },
		{ "&Quit",			FL_ALT + 'q', (Fl_Callback *)ImpressionistUI::cb_exit },
		{ 0 },
	
	{ "&Edit",		0, 0, 0, FL_SUBMENU },
		{ "&Brushes...",	FL_ALT + 'b', (Fl_Callback *)ImpressionistUI::cb_brushes },
		{ "&Colors",FL_ALT + 'o' ,(Fl_Callback *)ImpressionistUI::cb_colors },
		{ "&Set Filter Kernel",	FL_ALT + 'f', (Fl_Callback *)ImpressionistUI::cb_filter_kernel_setting },
		{ "&Undo",FL_ALT + 'u' ,(Fl_Callback *)ImpressionistUI::cb_undo },

		{ 0 },

	{ "&Display",		0, 0, 0, FL_SUBMENU },
		{ "&Clear Canvas", FL_ALT + 'c', (Fl_Callback *)ImpressionistUI::cb_clear_canvas, 0, FL_MENU_DIVIDER },
		{ "&Swap Windows",FL_ALT + 'w' ,(Fl_Callback *)ImpressionistUI::cb_SwapWindows },
		{ "&Show Dimmed View",FL_ALT + 'v' ,(Fl_Callback *)ImpressionistUI::cb_ShowDimDialog },
		{ 0 },

	{ "&Help",		0, 0, 0, FL_SUBMENU },
		{ "&About",	FL_ALT + 'a', (Fl_Callback *)ImpressionistUI::cb_about },
		{ 0 },

	{ 0 }
};

// Brush choice menu definition
Fl_Menu_Item ImpressionistUI::brushTypeMenu[NUM_BRUSH_TYPE+1] = {
  {"Points",			FL_ALT+'p', (Fl_Callback *)ImpressionistUI::cb_brushChoice, (void *)BRUSH_POINTS},
  {"Lines",				FL_ALT+'l', (Fl_Callback *)ImpressionistUI::cb_brushChoice, (void *)BRUSH_LINES},
  {"Circles",			FL_ALT+'c', (Fl_Callback *)ImpressionistUI::cb_brushChoice, (void *)BRUSH_CIRCLES},
  {"Scattered Points",	FL_ALT+'q', (Fl_Callback *)ImpressionistUI::cb_brushChoice, (void *)BRUSH_SCATTERED_POINTS},
  {"Scattered Lines",	FL_ALT+'m', (Fl_Callback *)ImpressionistUI::cb_brushChoice, (void *)BRUSH_SCATTERED_LINES},
  {"Scattered Circles",	FL_ALT+'d', (Fl_Callback *)ImpressionistUI::cb_brushChoice, (void *)BRUSH_SCATTERED_CIRCLES},
  { "Gray",	FL_ALT + 'r', (Fl_Callback *)ImpressionistUI::cb_brushChoice, (void *)BRUSH_GRAY_POINTS },
  { "Sharpen",	FL_ALT + 'n', (Fl_Callback *)ImpressionistUI::cb_brushChoice, (void *)BRUSH_SHARPEN_POINTS },
  { "Blur",	FL_ALT + 'u', (Fl_Callback *)ImpressionistUI::cb_brushChoice, (void *)BRUSH_BLUR_POINTS },
  { "Alpha Map",	FL_ALT + 'a', (Fl_Callback *)ImpressionistUI::cb_brushChoice, (void *)BRUSH_ALPHA_MAP },
  {0}
};

// the type of control the direction of the line brush and scatter lines
Fl_Menu_Item ImpressionistUI::brushDirectionControlType[3] = {
	{ "Slider/RightMouse",			FL_ALT + 's', (Fl_Callback *)ImpressionistUI::cb_brushDirectionType, (void *)SLIDER_RMOUSE },
	{ "Gradient",				FL_ALT + 'g', (Fl_Callback *)ImpressionistUI::cb_brushDirectionType, (void *)GRADIENT },
	{ "Brush Direction",			FL_ALT + 'b', (Fl_Callback *)ImpressionistUI::cb_brushDirectionType, (void *)CURSOR }
};


//----------------------------------------------------
// Constructor.  Creates all of the widgets.
// Add new widgets here
//----------------------------------------------------
ImpressionistUI::ImpressionistUI() {

	m_ApplyFilterKernel = NULL;
	m_FilterKernelDialog = NULL;
	m_Normalize = NULL;
	// Create the main window
	m_mainWindow = new Fl_Window(600, 300, "Impressionist");
		m_mainWindow->user_data((void*)(this));	// record self to be used by static callback functions
		// install menu bar
		m_menubar = new Fl_Menu_Bar(0, 0, 600, 25);
		m_menubar->menu(menuitems);

		// Create a group that will hold two sub windows inside the main
		// window
		Fl_Group* group = new Fl_Group(0, 25, 600, 275);

			// install paint view window
			m_paintView = new PaintView(300, 25, 300, 275, "This is the paint view");//0jon
			m_paintView->box(FL_DOWN_FRAME);
			
			
			// install original view window
			m_origView = new OriginalView(0, 25, 300, 275, "This is the orig view");//300jon
			m_origView->box(FL_DOWN_FRAME);
			//m_origView->deactivate();

		group->end();
		Fl_Group::current()->resizable(group);
    m_mainWindow->end();

	//ini values
	//used by color dialog definition
	m_nRedScale = 1.00;
	m_nGreenScale = 1.00;
	m_nBlueScale = 1.00;
	
	//color dialog definition
	m_colorDialog = new Fl_Window(360, 100, "Color Dialog");
		
		//Red scale slider
		m_AlphaSlider = new Fl_Value_Slider(10, 10, 300, 20, "Red");
		m_AlphaSlider->user_data((void*)(this));	// record self to be used by static callback functions
		m_AlphaSlider->type(FL_HOR_NICE_SLIDER);
		m_AlphaSlider->labelfont(FL_COURIER);
		m_AlphaSlider->labelsize(12);
		m_AlphaSlider->minimum(0.00);
		m_AlphaSlider->maximum(1);
		m_AlphaSlider->step(0.01);
		m_AlphaSlider->value(m_nRedScale);
		m_AlphaSlider->align(FL_ALIGN_RIGHT);
		m_AlphaSlider->callback(cb_RedSlides);

		//green scale slider
		m_AlphaSlider = new Fl_Value_Slider(10, 30, 300, 20, "Green");
		m_AlphaSlider->user_data((void*)(this));	// record self to be used by static callback functions
		m_AlphaSlider->type(FL_HOR_NICE_SLIDER);
		m_AlphaSlider->labelfont(FL_COURIER);
		m_AlphaSlider->labelsize(12);
		m_AlphaSlider->minimum(0.00);
		m_AlphaSlider->maximum(1);
		m_AlphaSlider->step(0.01);
		m_AlphaSlider->value(m_nGreenScale);
		m_AlphaSlider->align(FL_ALIGN_RIGHT);
		m_AlphaSlider->callback(cb_GreenSlides);

		//blue scale slider
		m_AlphaSlider = new Fl_Value_Slider(10, 50, 300, 20, "Blue");
		m_AlphaSlider->user_data((void*)(this));	// record self to be used by static callback functions
		m_AlphaSlider->type(FL_HOR_NICE_SLIDER);
		m_AlphaSlider->labelfont(FL_COURIER);
		m_AlphaSlider->labelsize(12);
		m_AlphaSlider->minimum(0.00);
		m_AlphaSlider->maximum(1);
		m_AlphaSlider->step(0.01);
		m_AlphaSlider->value(m_nBlueScale);
		m_AlphaSlider->align(FL_ALIGN_RIGHT);
		m_AlphaSlider->callback(cb_BlueSlides);

		m_ApplyScalingButton = new Fl_Button(250, 70, 70, 20, "&Apply");
		m_ApplyScalingButton->user_data((void*)(this));
		m_ApplyScalingButton->callback(cb_ApplyColorScaling);
	m_colorDialog->end();
	// init values
	// used by brush dialog definition

	m_nSize = 10;
	m_nLineWidth = 1;
	m_nLineAngle = 0;
	m_nAlpha = 1.00;
	m_nRandomAttr = false;
	m_nEnableAutoDraw = false;
	m_nSpacing = 1;

	// brush dialog definition
	m_brushDialog = new Fl_Window(400, 325, "Brush Dialog");
		// Add a brush type choice to the dialog
		m_BrushTypeChoice = new Fl_Choice(50,10,150,20,"&Brush");
		m_BrushTypeChoice->user_data((void*)(this));	// record self to be used by static callback functions
		m_BrushTypeChoice->menu(brushTypeMenu);
		m_BrushTypeChoice->callback(cb_brushChoice);

		m_ClearCanvasButton = new Fl_Button(240,10,150,20,"&Clear Canvas");
		m_ClearCanvasButton->user_data((void*)(this));
		m_ClearCanvasButton->callback(cb_clear_canvas_button);

		m_BrushTypeChoice = new Fl_Choice(113, 40, 160, 20, "&Stroke Direction");
		m_BrushTypeChoice->user_data((void*)(this));	// record self to be used by static callback functions
		m_BrushTypeChoice->menu(brushDirectionControlType);
		m_BrushTypeChoice->callback(cb_brushDirectionType);


		// Add brush size slider to the dialog 
		m_BrushSizeSlider = new Fl_Value_Slider(10, 80, 300, 20, "Size");
		m_BrushSizeSlider->user_data((void*)(this));	// record self to be used by static callback functions
		m_BrushSizeSlider->type(FL_HOR_NICE_SLIDER);
        m_BrushSizeSlider->labelfont(FL_COURIER);
        m_BrushSizeSlider->labelsize(12);
		m_BrushSizeSlider->minimum(1);
		m_BrushSizeSlider->maximum(40);
		m_BrushSizeSlider->step(1);
		m_BrushSizeSlider->value(m_nSize);
		m_BrushSizeSlider->align(FL_ALIGN_RIGHT);
		m_BrushSizeSlider->callback(cb_sizeSlides);

		// Add brush line width slider to the dialog 
		
		m_LineWidthSlider = new Fl_Value_Slider(10, 110, 300, 20, "Line Width");
		m_LineWidthSlider->user_data((void*)(this));	// record self to be used by static callback functions
		m_LineWidthSlider->type(FL_HOR_NICE_SLIDER);
		m_LineWidthSlider->labelfont(FL_COURIER);
		m_LineWidthSlider->labelsize(12);
		m_LineWidthSlider->minimum(1);
		m_LineWidthSlider->maximum(40);
		m_LineWidthSlider->step(1);
		m_LineWidthSlider->value(m_nLineWidth);
		m_LineWidthSlider->align(FL_ALIGN_RIGHT);
		m_LineWidthSlider->callback(cb_LineWidthSlides);

		// Add brush line angle slider to the dialog 

		m_LineAngleSlider = new Fl_Value_Slider(10, 140, 300, 20, "Line Angle");
		m_LineAngleSlider->user_data((void*)(this));	// record self to be used by static callback functions
		m_LineAngleSlider->type(FL_HOR_NICE_SLIDER);
		m_LineAngleSlider->labelfont(FL_COURIER);
		m_LineAngleSlider->labelsize(12);
		m_LineAngleSlider->minimum(1);
		m_LineAngleSlider->maximum(359);
		m_LineAngleSlider->step(1);
		m_LineAngleSlider->value(m_nLineAngle);
		m_LineAngleSlider->align(FL_ALIGN_RIGHT);
		m_LineAngleSlider->callback(cb_LineAngleSlides);

		// Add brush line angle slider to the dialog 

		m_AlphaSlider = new Fl_Value_Slider(10, 170, 300, 20, "Alpha");
		m_AlphaSlider->user_data((void*)(this));	// record self to be used by static callback functions
		m_AlphaSlider->type(FL_HOR_NICE_SLIDER);
		m_AlphaSlider->labelfont(FL_COURIER);
		m_AlphaSlider->labelsize(12);
		m_AlphaSlider->minimum(0.00);
		m_AlphaSlider->maximum(1);
		m_AlphaSlider->step(0.01);
		m_AlphaSlider->value(m_nAlpha);
		m_AlphaSlider->align(FL_ALIGN_RIGHT);
		m_AlphaSlider->callback(cb_AlphaSlides);

		m_AutoPaintSpacingSlider = new Fl_Value_Slider(10, 210, 150, 20, "Spacing");
		m_AutoPaintSpacingSlider->user_data((void*)(this));	// record self to be used by static callback functions
		m_AutoPaintSpacingSlider->type(FL_HOR_NICE_SLIDER);
		m_AutoPaintSpacingSlider->labelfont(FL_COURIER);
		m_AutoPaintSpacingSlider->labelsize(12);
		m_AutoPaintSpacingSlider->minimum(1);
		m_AutoPaintSpacingSlider->maximum(16);
		m_AutoPaintSpacingSlider->step(1);
		m_AutoPaintSpacingSlider->value(m_nSpacing);
		m_AutoPaintSpacingSlider->align(FL_ALIGN_RIGHT);
		m_AutoPaintSpacingSlider->callback(cb_AutoPaintSpacingSlides);

		m_RandomAttrButton = new Fl_Light_Button(220, 210, 100, 25, "&Attr Rand");
		m_RandomAttrButton->user_data((void*)(this));
		m_RandomAttrButton->callback(cb_Rand_Attr_button);
		m_RandomAttrButton->value(m_nRandomAttr);

		m_AutoPaintButton = new Fl_Button(330, 210, 50, 25, "&Paint");
		m_AutoPaintButton->user_data((void*)(this));
		m_AutoPaintButton->callback(cb_Auto_Paint_button);
		
		//disable line width slider and angle slider 
		m_LineWidthSlider->deactivate();
		m_LineAngleSlider->deactivate();
    m_brushDialog->end();	

	//dimmed view dialog
	m_nDimAlpha = 0.2;
	m_nShowDimImage = false;

	m_dimDialog = new Fl_Window(400, 80, "Dimmed Image Dialog");
		m_dimAlphaSlider = new Fl_Value_Slider(10, 10, 300, 20, "Alpha");
		m_dimAlphaSlider->user_data((void*)(this));	// record self to be used by static callback functions
		m_dimAlphaSlider->type(FL_HOR_NICE_SLIDER);
		m_dimAlphaSlider->labelfont(FL_COURIER);
		m_dimAlphaSlider->labelsize(12);
		m_dimAlphaSlider->minimum(0);
		m_dimAlphaSlider->maximum(1.00);
		m_dimAlphaSlider->step(0.01);
		m_dimAlphaSlider->value(m_nDimAlpha);
		m_dimAlphaSlider->align(FL_ALIGN_RIGHT);
		m_dimAlphaSlider->callback(cb_dimAlphaSlides);

		m_dimButton = new Fl_Light_Button(10, 40, 160, 25, "&Show Dimmed Image");
		m_dimButton->user_data((void*)(this));
		m_dimButton->callback(cb_dim_button);
		m_dimButton->value(m_nShowDimImage);
	m_dimDialog->end();
	
	m_FilterKernelSettingDialog = new Fl_Window(230, 70, "Kernel Filter Setting Dialog");
		m_NumColsInput = new Fl_Int_Input(60, 10, 40, 20, "Width:");
		m_NumColsInput->labelfont(FL_COURIER);
		m_NumColsInput->labelsize(12);
		m_NumColsInput->value("3"); 
	
		m_NumRowsInput = new Fl_Int_Input(170, 10, 40, 20, "Height:");
		m_NumRowsInput->labelfont(FL_COURIER);
		m_NumRowsInput->labelsize(12);
		m_NumRowsInput->value("3");

		m_ConfirmKernelSettingButton = new Fl_Button(130, 40, 70, 20, "&Confirm");
		m_ConfirmKernelSettingButton->user_data((void*)(this));
		m_ConfirmKernelSettingButton->callback(cb_confirm_kernel_button);
		 
	m_FilterKernelSettingDialog->end();

	m_nEnableNormalize = false;
}


void ImpressionistUI::passCursorPoint(const Point& p) {
	m_origView->setCursor(p);
	
}