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
		pUI->m_AnotherGradientButton->deactivate();
		pUI->m_EdgeClipingButton->deactivate();
		pUI->m_BrushTypeChoice->deactivate();
	}
	else {
		if (pUI->m_nAnotherGradient && pDoc->m_ucAnotherBitmap)
			pUI->m_nBrushDirectionTypeCatche = pUI->m_pDoc->m_pControlType;
		pUI->m_LineWidthSlider->activate();
		pUI->m_LineAngleSlider->activate();
		pUI->m_AnotherGradientButton->activate();
		pUI->m_EdgeClipingButton->activate();
		pUI->m_BrushTypeChoice->activate();
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
	ImpressionistDoc* pDoc = pUI->getDocument();
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
//------------------------------------------------
// Edge related funtion
//------------------------------------------------
void ImpressionistUI::cb_ThresholdSlides(Fl_Widget* o, void* v) {
	((ImpressionistUI*)(o->user_data()))->m_nThreshold = float(((Fl_Slider *)o)->value());
}
void ImpressionistUI::cb_Generating_Edge_Image_button(Fl_Widget* o, void* v) {
	((ImpressionistUI*)(o->user_data()))->getDocument()->generateEdgeImage();
}
void ImpressionistUI::cb_toggle_cliping_button(Fl_Widget* o, void* v) {
	((ImpressionistUI*)(o->user_data()))->m_nEnableEdgeClipping = !((ImpressionistUI*)(o->user_data()))->m_nEnableEdgeClipping;
}
void ImpressionistUI::cb_load_edge_image(Fl_Menu_* o, void* v) {
	ImpressionistDoc *pDoc = whoami(o)->getDocument();

	char* newfile = fl_file_chooser("Open File?", "*.bmp", pDoc->getImageName());
	if (newfile != NULL) {
		pDoc->loadEdgeImage(newfile);
	}
}
//------------------------------------------------
// switch image in the originView window
//------------------------------------------------
void ImpressionistUI::cb_switch_view_type(Fl_Menu_* o, void* v) {
	ImpressionistUI* pUI = whoami(o);
	ImpressionistDoc* pDoc = pUI->getDocument();
	int type = (int)v;
	
	if (type == EDGE_IMAGE&&pDoc->m_ucEdgeBitmap == NULL) {
		fl_alert("Please generate or load an edge image first!");
		return;
	}
	if (type == ANOTHER_IMAGE&&pDoc->m_ucAnotherBitmap == NULL) {
		fl_alert("Please load another image first!");
		return;
	}
	
	pUI->m_origView->setViewType(type);

	pUI->m_origView->refresh();
}
//------------------------------------------------
// another image related function
//------------------------------------------------
void ImpressionistUI::cb_load_another_image(Fl_Menu_* o, void* v) {
	ImpressionistDoc *pDoc = whoami(o)->getDocument();

	char* newfile = fl_file_chooser("Open File?", "*.bmp", pDoc->getImageName());
	if (newfile != NULL) {
		pDoc->loadAnotherImage(newfile);
	}
}
void ImpressionistUI::cb_another_gradient_button(Fl_Widget* o, void* v) {
	ImpressionistUI* pUI = ((ImpressionistUI*)(o->user_data()));
	pUI->m_nAnotherGradient = !pUI->m_nAnotherGradient;
	if (pUI->m_pDoc->m_ucAnotherBitmap) {
		cout << "true";
		if (pUI->m_nAnotherGradient) {
			pUI->m_nBrushDirectionTypeCatche = pUI->m_pDoc->m_pControlType;
			pUI->m_pDoc->m_pControlType = ANOTHER_IMAGE_GRADIENT;
		}
		else
			pUI->m_pDoc->m_pControlType = pUI->m_nBrushDirectionTypeCatche;

	}
}
//------------------------------------------------
// painterly and curved brush related function
//------------------------------------------------
void ImpressionistUI::cb_painterly(Fl_Menu_* o, void* v) {
	whoami(o)->m_painterlylDialog->show();
}
/*
void ImpressionistUI::cb_painterly_Type(Fl_Widget* o, void* v) {
	ImpressionistUI* pUI = ((ImpressionistUI*)(o->user_data()));
	int type = (int)v;
	pUI->m_nPainterlyCurrentStyle = type;

	if (type == CUSTOMIZE) {
		pUI->m_painterlyStroke->activate();
		pUI->m_painterlyThreshold->activate();
		pUI->m_painterlyCurvature->activate();
		pUI->m_painterlyBlur->activate();
		pUI->m_painterlyGridSize->activate();
		pUI->m_painterlyMinStrokeL->activate();
		pUI->m_painterlyMaxStrokeL->activate();
		pUI->m_painterlyAlpha->activate();
		pUI->m_painterlyLayers->activate();
		pUI->m_painterlyR0Level->activate();
		
		pUI->m_painterlyJr->activate();
		pUI->m_painterlyJg->activate();
		pUI->m_painterlyJb->activate();
		pUI->m_painterlyJh->activate();
		pUI->m_painterlyJs->activate();
		pUI->m_painterlyJv->activate();
		
	}
	else {
		pUI->m_painterlyStroke->deactivate();
		pUI->m_painterlyThreshold->deactivate();
		pUI->m_painterlyCurvature->deactivate();
		pUI->m_painterlyBlur->deactivate();
		pUI->m_painterlyGridSize->deactivate();
		pUI->m_painterlyMinStrokeL->deactivate();
		pUI->m_painterlyMaxStrokeL->deactivate();
		pUI->m_painterlyAlpha->deactivate();
		pUI->m_painterlyLayers->deactivate();
		pUI->m_painterlyR0Level->deactivate();
		
		pUI->m_painterlyJr->deactivate();
		pUI->m_painterlyJg->deactivate();
		pUI->m_painterlyJb->deactivate();
		pUI->m_painterlyJh->deactivate();
		pUI->m_painterlyJs->deactivate();
		pUI->m_painterlyJv->deactivate();
		
	}
}
*/
void ImpressionistUI::cb_painterlyStrokeType(Fl_Widget* o, void* v) {
	ImpressionistUI* pUI = ((ImpressionistUI*)(o->user_data()));
	int type = (int)v;
	pUI->m_nPainterlyCurrentStroke = type;

}

void ImpressionistUI::cb_painterly_run_button(Fl_Widget* o, void* v) {
	if (((ImpressionistUI*)(o->user_data()))->getDocument()->m_ucBitmap == NULL) {
		fl_alert("Please load an image first£¡");
			return;
	}
	((ImpressionistUI*)(o->user_data()))->getDocument()->PainterlyStart();
}

void ImpressionistUI::cb_painterlyThresholdSlides(Fl_Widget* o, void* v) {
	((ImpressionistUI*)(o->user_data()))->m_nPainterlyThreshold = float(((Fl_Slider *)o)->value());
}

void ImpressionistUI::cb_paintlyCurvatureSlides(Fl_Widget* o, void* v) {
	((ImpressionistUI*)(o->user_data()))->m_nPainterlyCurvature = float(((Fl_Slider *)o)->value());
}

void ImpressionistUI::cb_painterlyBlurSlides(Fl_Widget* o, void* v) {
		float data = float(((Fl_Slider *)o)->value());
		if (((ImpressionistUI*)(o->user_data()))->m_nPainterlyBlur == data) {
			((ImpressionistUI*)(o->user_data()))->m_nPainterlyBlurChanged = false;
		}
		else {
			((ImpressionistUI*)(o->user_data()))->m_nPainterlyBlur = data;
			((ImpressionistUI*)(o->user_data()))->m_nPainterlyBlurChanged = true;
		}
}

void ImpressionistUI::cb_painterlyGridSizeSlides(Fl_Widget* o, void* v) {
	((ImpressionistUI*)(o->user_data()))->m_nPainterlyGirdSize = float(((Fl_Slider *)o)->value());
}

void ImpressionistUI::cb_painterlyMinStrokeSlides(Fl_Widget* o, void* v) {
	((ImpressionistUI*)(o->user_data()))->m_nPainterlyMinStrokeL = float(((Fl_Slider *)o)->value());
}

void ImpressionistUI::cb_painterlyMaxStrokeSlides(Fl_Widget* o, void* v) {
	((ImpressionistUI*)(o->user_data()))->m_nPainterlyMaxStrokeL = float(((Fl_Slider *)o)->value());
}

void ImpressionistUI::cb_painterlyAlphaSlides(Fl_Widget* o, void* v) {
	((ImpressionistUI*)(o->user_data()))->m_nPainterlyAlpha = float(((Fl_Slider *)o)->value());
}

void ImpressionistUI::cb_painterlyLayerSlides(Fl_Widget* o, void* v) {
	((ImpressionistUI*)(o->user_data()))->m_nPainterlyLayers = float(((Fl_Slider *)o)->value());
}

void ImpressionistUI::cb_painterlyR0LevelSlides(Fl_Widget* o, void* v) {
	((ImpressionistUI*)(o->user_data()))->m_nPainterlyR0Level = float(((Fl_Slider *)o)->value());
}
/*
void ImpressionistUI::cb_painterlyJrSlides(Fl_Widget* o, void* v) {
	((ImpressionistUI*)(o->user_data()))->m_nPainterlyJr= float(((Fl_Slider *)o)->value());
}

void ImpressionistUI::cb_painterlyJgSlides(Fl_Widget* o, void* v) {
	((ImpressionistUI*)(o->user_data()))->m_nPainterlyJg = float(((Fl_Slider *)o)->value());
}

void ImpressionistUI::cb_painterlyJbSlides(Fl_Widget* o, void* v) {
	((ImpressionistUI*)(o->user_data()))->m_nPainterlyJb= float(((Fl_Slider *)o)->value());
}

void ImpressionistUI::cb_painterlyJhSlides(Fl_Widget* o, void* v) {
	((ImpressionistUI*)(o->user_data()))->m_nPainterlyJh = float(((Fl_Slider *)o)->value());
}

void ImpressionistUI::cb_painterlyJsSlides(Fl_Widget* o, void* v) {
	((ImpressionistUI*)(o->user_data()))->m_nPainterlyJs= float(((Fl_Slider *)o)->value());
}

void ImpressionistUI::cb_painterlyJvSlides(Fl_Widget* o, void* v) {
	((ImpressionistUI*)(o->user_data()))->m_nPainterlyJv = float(((Fl_Slider *)o)->value());
}

*/



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

int ImpressionistUI::getThreshold() {
	return m_nThreshold;
}

bool ImpressionistUI::getEnableEdgeCliping() {
	return m_nEnableEdgeClipping;
}

bool ImpressionistUI::getAnotherGradient() {
	return m_nAnotherGradient;
}

// Main menu definition
Fl_Menu_Item ImpressionistUI::menuitems[] = {
	{ "&File",		0, 0, 0, FL_SUBMENU },
		{ "&Load Image...",	FL_ALT + 'l', (Fl_Callback *)ImpressionistUI::cb_load_image },
		{ "&Load Edge Image...",	FL_ALT + 'l', (Fl_Callback *)ImpressionistUI::cb_load_edge_image },
		{ "&Load Another Image...",	FL_ALT + '3', (Fl_Callback *)ImpressionistUI::cb_load_another_image },
		{ "&Save Image...",	FL_ALT + 's', (Fl_Callback *)ImpressionistUI::cb_save_image },
		{ "&Dissolve Image...",	FL_ALT + 'd', (Fl_Callback *)ImpressionistUI::cb_dissolve_image },
		{ "&Painterly",	FL_ALT + 'y', (Fl_Callback *)ImpressionistUI::cb_painterly },
		{ "&New Mural Image...",	FL_ALT + 'm', (Fl_Callback *)ImpressionistUI::cb_mural_image },
		{ "&Load Alpha-mapped Brush",	FL_ALT + 'b', (Fl_Callback *)ImpressionistUI::cb_load_alpha_map },
		{ "&Quit",			FL_ALT + 'q', (Fl_Callback *)ImpressionistUI::cb_exit },
		{ 0 },
	
	{ "&Edit",		0, 0, 0, FL_SUBMENU },
		{ "&Brushes...",	FL_ALT + 'b', (Fl_Callback *)ImpressionistUI::cb_brushes },
		{ "&Colors",FL_ALT + 'o' ,(Fl_Callback *)ImpressionistUI::cb_colors },
		{ "&Set Filter Kernel",	FL_ALT + 'f', (Fl_Callback *)ImpressionistUI::cb_filter_kernel_setting },
		{ "&Undo",FL_ALT + 'u' ,(Fl_Callback *)ImpressionistUI::cb_undo },

		{ 0 },

	{ "&Display",		0, 0, 0, FL_SUBMENU },
		{ "&Original Image",FL_ALT + 'o' ,(Fl_Callback *)ImpressionistUI::cb_switch_view_type,(void*)ORIGIN_IMAGE},
		{ "&Edge Image",FL_ALT + 'e' ,(Fl_Callback *)ImpressionistUI::cb_switch_view_type,(void*)EDGE_IMAGE },
		{ "&Another Image",FL_ALT + 'a' ,(Fl_Callback *)ImpressionistUI::cb_switch_view_type,(void*)ANOTHER_IMAGE, FL_MENU_DIVIDER },
		{ "&Clear Canvas", FL_ALT + 'c', (Fl_Callback *)ImpressionistUI::cb_clear_canvas, 0 },
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
  { "Curve",	FL_ALT + 'u', (Fl_Callback *)ImpressionistUI::cb_brushChoice, (void *)BRUSH_CURVE },
  {0}
};

// the type of control the direction of the line brush and scatter lines
Fl_Menu_Item ImpressionistUI::brushDirectionControlType[3] = {
	{ "Slider/RightMouse",			FL_ALT + 's', (Fl_Callback *)ImpressionistUI::cb_brushDirectionType, (void *)SLIDER_RMOUSE },
	{ "Gradient",				FL_ALT + 'g', (Fl_Callback *)ImpressionistUI::cb_brushDirectionType, (void *)GRADIENT },
	{ "Brush Direction",			FL_ALT + 'b', (Fl_Callback *)ImpressionistUI::cb_brushDirectionType, (void *)CURSOR }
};
/*
// painterly style menu
Fl_Menu_Item ImpressionistUI::painterlyStyleType[5] = {
	{ "Impressionist",			FL_ALT + '1', (Fl_Callback *)ImpressionistUI::cb_painterly_Type, (void *)IMPRESSIONIST },
	{ "Expressionist",				FL_ALT + '2', (Fl_Callback *)ImpressionistUI::cb_painterly_Type, (void *)EXPRESSIONIST },
	{ "Color Wash",			FL_ALT + '3', (Fl_Callback *)ImpressionistUI::cb_painterly_Type, (void *)COLOR_WASH },
	{ "Pointillist",			FL_ALT + '4', (Fl_Callback *)ImpressionistUI::cb_painterly_Type, (void *)POINTILLIST },
	{ "Customize",			FL_ALT + '5', (Fl_Callback *)ImpressionistUI::cb_painterly_Type, (void *)CUSTOMIZE }
};
*/
//painterly stroke menu
Fl_Menu_Item ImpressionistUI::painterlyStrokeType[4] = 
{
	{ "Curve Brush",			FL_ALT + '6', (Fl_Callback *)ImpressionistUI::cb_painterlyStrokeType, (void *)BRUSH_CURVE },
	{ "Circle Brush",				FL_ALT + '7', (Fl_Callback *)ImpressionistUI::cb_painterlyStrokeType, (void *)BRUSH_CIRCLES},
	{ "Point Brush",			FL_ALT + '8', (Fl_Callback *)ImpressionistUI::cb_painterlyStrokeType, (void *)BRUSH_POINTS },
	{ "Line Brush",			FL_ALT + '9', (Fl_Callback *)ImpressionistUI::cb_painterlyStrokeType, (void *)BRUSH_LINES },
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

	//painterly dialog

	m_nPainterlyCurrentStyle = IMPRESSIONIST;
	m_nPainterlyCurrentStroke = BRUSH_CURVE;
	m_nPainterlyThreshold = 100;
	m_nPainterlyCurvature = 1.0;
	m_nPainterlyBlur = 0.50;
	m_nPainterlyGirdSize = 1.00;
	m_nPainterlyMinStrokeL = 4;
	m_nPainterlyMaxStrokeL = 16;
	m_nPainterlyAlpha = 1.00;
	m_nPainterlyLayers = 3;
	m_nPainterlyR0Level = 3;
	/*
	m_nPainterlyJr = 1;
	m_nPainterlyJg = 1;
	m_nPainterlyJb = 1;
	m_nPainterlyJh = 1;
	m_nPainterlyJs = 1;
	m_nPainterlyJv = 1;
	*/
	m_nPainterlyRun = false;
	m_nPaintrelyIsInitialized = false;
	m_painterlylDialog = new Fl_Window(300, 270, "Painterly Dialog");
	/*
	m_painterlyStyle = new Fl_Choice(50, 10, 120, 20, "&Style");
	m_painterlyStyle->user_data((void*)(this));	// record self to be used by static callback functions
	m_painterlyStyle->menu(painterlyStyleType);
	m_painterlyStyle->callback(cb_painterly_Type);
	*/
	m_painterlyStroke = new Fl_Choice(60, 10, 120, 20, "&Stroke");
	m_painterlyStroke->user_data((void*)(this));	// record self to be used by static callback functions
	m_painterlyStroke->menu(painterlyStrokeType);
	m_painterlyStroke->callback(cb_painterlyStrokeType);

	m_painterlyRun = new Fl_Button(240, 10, 40, 20, "&Run");
	m_painterlyRun->user_data((void*)(this));
	m_painterlyRun->callback(cb_painterly_run_button);

	m_painterlyThreshold = new Fl_Value_Slider(15, 40, 200, 20, "Threshold");
	m_painterlyThreshold->user_data((void*)(this));	// record self to be used by static callback functions
	m_painterlyThreshold->type(FL_HOR_NICE_SLIDER);
	m_painterlyThreshold->labelfont(FL_COURIER);
	m_painterlyThreshold->labelsize(12);
	m_painterlyThreshold->minimum(0);
	m_painterlyThreshold->maximum(250);
	m_painterlyThreshold->step(1);
	m_painterlyThreshold->value(m_nPainterlyThreshold);
	m_painterlyThreshold->align(FL_ALIGN_RIGHT);
	m_painterlyThreshold->callback(cb_painterlyThresholdSlides);

	m_painterlyCurvature = new Fl_Value_Slider(15, 65, 200, 20, "Curvature");
	m_painterlyCurvature->user_data((void*)(this));	// record self to be used by static callback functions
	m_painterlyCurvature->type(FL_HOR_NICE_SLIDER);
	m_painterlyCurvature->labelfont(FL_COURIER);
	m_painterlyCurvature->labelsize(12);
	m_painterlyCurvature->minimum(0.00);
	m_painterlyCurvature->maximum(1.00);
	m_painterlyCurvature->step(0.01);
	m_painterlyCurvature->value(m_nPainterlyCurvature);
	m_painterlyCurvature->align(FL_ALIGN_RIGHT);
	m_painterlyCurvature->callback(cb_paintlyCurvatureSlides);

	m_painterlyBlur = new Fl_Value_Slider(15, 90, 200, 20, "Blur");
	m_painterlyBlur->user_data((void*)(this));	// record self to be used by static callback functions
	m_painterlyBlur->type(FL_HOR_NICE_SLIDER);
	m_painterlyBlur->labelfont(FL_COURIER);
	m_painterlyBlur->labelsize(12);
	m_painterlyBlur->minimum(0.01);
	m_painterlyBlur->maximum(1.00);
	m_painterlyBlur->step(0.01);
	m_painterlyBlur->value(m_nPainterlyBlur);
	m_painterlyBlur->align(FL_ALIGN_RIGHT);
	m_painterlyBlur->callback(cb_painterlyBlurSlides);

	m_painterlyGridSize = new Fl_Value_Slider(15, 115, 200, 20, "Grid Size");
	m_painterlyGridSize->user_data((void*)(this));	// record self to be used by static callback functions
	m_painterlyGridSize->type(FL_HOR_NICE_SLIDER);
	m_painterlyGridSize->labelfont(FL_COURIER);
	m_painterlyGridSize->labelsize(12);
	m_painterlyGridSize->minimum(0.00);
	m_painterlyGridSize->maximum(1.00);
	m_painterlyGridSize->step(0.01);
	m_painterlyGridSize->value(m_nPainterlyGirdSize);
	m_painterlyGridSize->align(FL_ALIGN_RIGHT);
	m_painterlyGridSize->callback(cb_painterlyGridSizeSlides);

	m_painterlyMinStrokeL = new Fl_Value_Slider(15, 140, 200, 20, "MinStrokeL");
	m_painterlyMinStrokeL->user_data((void*)(this));	// record self to be used by static callback functions
	m_painterlyMinStrokeL->type(FL_HOR_NICE_SLIDER);
	m_painterlyMinStrokeL->labelfont(FL_COURIER);
	m_painterlyMinStrokeL->labelsize(12);
	m_painterlyMinStrokeL->minimum(1);
	m_painterlyMinStrokeL->maximum(30);
	m_painterlyMinStrokeL->step(1);
	m_painterlyMinStrokeL->value(m_nPainterlyMinStrokeL);
	m_painterlyMinStrokeL->align(FL_ALIGN_RIGHT);
	m_painterlyMinStrokeL->callback(cb_painterlyMinStrokeSlides);

	m_painterlyMaxStrokeL = new Fl_Value_Slider(15, 165, 200, 20, "MaxStroke");
	m_painterlyMaxStrokeL->user_data((void*)(this));	// record self to be used by static callback functions
	m_painterlyMaxStrokeL->type(FL_HOR_NICE_SLIDER);
	m_painterlyMaxStrokeL->labelfont(FL_COURIER);
	m_painterlyMaxStrokeL->labelsize(12);
	m_painterlyMaxStrokeL->minimum(0);
	m_painterlyMaxStrokeL->maximum(30);
	m_painterlyMaxStrokeL->step(1);
	m_painterlyMaxStrokeL->value(m_nPainterlyMaxStrokeL);
	m_painterlyMaxStrokeL->align(FL_ALIGN_RIGHT);
	m_painterlyMaxStrokeL->callback(cb_painterlyMaxStrokeSlides);

	m_painterlyAlpha = new Fl_Value_Slider(15, 190, 200, 20, "Alpha");
	m_painterlyAlpha->user_data((void*)(this));	// record self to be used by static callback functions
	m_painterlyAlpha->type(FL_HOR_NICE_SLIDER);
	m_painterlyAlpha->labelfont(FL_COURIER);
	m_painterlyAlpha->labelsize(12);
	m_painterlyAlpha->minimum(0.00);
	m_painterlyAlpha->maximum(1.00);
	m_painterlyAlpha->step(0.01);
	m_painterlyAlpha->value(m_nPainterlyAlpha);
	m_painterlyAlpha->align(FL_ALIGN_RIGHT);
	m_painterlyAlpha->callback(cb_painterlyAlphaSlides);

	m_painterlyLayers = new Fl_Value_Slider(15, 215, 200, 20, "Layers");
	m_painterlyLayers->user_data((void*)(this));	// record self to be used by static callback functions
	m_painterlyLayers->type(FL_HOR_NICE_SLIDER);
	m_painterlyLayers->labelfont(FL_COURIER);
	m_painterlyLayers->labelsize(12);
	m_painterlyLayers->minimum(1);
	m_painterlyLayers->maximum(5);
	m_painterlyLayers->step(1);
	m_painterlyLayers->value(m_nPainterlyLayers);
	m_painterlyLayers->align(FL_ALIGN_RIGHT);
	m_painterlyLayers->callback(cb_painterlyLayerSlides);

	m_painterlyR0Level = new Fl_Value_Slider(15, 240, 200, 20, "R0 Level");
	m_painterlyR0Level->user_data((void*)(this));	// record self to be used by static callback functions
	m_painterlyR0Level->type(FL_HOR_NICE_SLIDER);
	m_painterlyR0Level->labelfont(FL_COURIER);
	m_painterlyR0Level->labelsize(12);
	m_painterlyR0Level->minimum(0);
	m_painterlyR0Level->maximum(5);
	m_painterlyR0Level->step(1);
	m_painterlyR0Level->value(m_nPainterlyR0Level);
	m_painterlyR0Level->align(FL_ALIGN_RIGHT);
	m_painterlyR0Level->callback(cb_painterlyR0LevelSlides);

	/*
	m_painterlyJr = new Fl_Value_Slider(300, 40, 25, 80, "Jr");
	m_painterlyJr->user_data((void*)(this));
	m_painterlyJr->type(FL_VERT_NICE_SLIDER);
	m_painterlyJr->labelfont(FL_COURIER);
	m_painterlyJr->labelsize(12);
	m_painterlyJr->minimum(1.00);
	m_painterlyJr->maximum(0);
	m_painterlyJr->step(0.01);
	m_painterlyJr->value(m_nPainterlyJr);
	m_painterlyJr->align(FL_ALIGN_BOTTOM);
	m_painterlyJr->callback(cb_painterlyJrSlides);

	m_painterlyJg = new Fl_Value_Slider(330, 40, 25, 80, "Jg");
	m_painterlyJg->user_data((void*)(this));
	m_painterlyJg->type(FL_VERT_NICE_SLIDER);
	m_painterlyJg->labelfont(FL_COURIER);
	m_painterlyJg->labelsize(12);
	m_painterlyJg->minimum(1.00);
	m_painterlyJg->maximum(0.00);
	m_painterlyJg->step(0.01);
	m_painterlyJg->value(m_nPainterlyJg);
	m_painterlyJg->align(FL_ALIGN_BOTTOM);
	m_painterlyJg->callback(cb_painterlyJgSlides);

	m_painterlyJb = new Fl_Value_Slider(360, 40, 25, 80, "Jb");
	m_painterlyJb->user_data((void*)(this));
	m_painterlyJb->type(FL_VERT_NICE_SLIDER);
	m_painterlyJb->labelfont(FL_COURIER);
	m_painterlyJb->labelsize(12);
	m_painterlyJb->minimum(1.00);
	m_painterlyJb->maximum(0.00);
	m_painterlyJb->step(0.01);
	m_painterlyJb->value(m_nPainterlyJb);
	m_painterlyJb->align(FL_ALIGN_BOTTOM);
	m_painterlyJb->callback(cb_painterlyJbSlides);

	m_painterlyJh = new Fl_Value_Slider(300, 150, 25, 80, "Jh");
	m_painterlyJh->user_data((void*)(this));
	m_painterlyJh->type(FL_VERT_NICE_SLIDER);
	m_painterlyJh->labelfont(FL_COURIER);
	m_painterlyJh->labelsize(12);
	m_painterlyJh->minimum(1);
	m_painterlyJh->maximum(0);
	m_painterlyJh->step(0.01);
	m_painterlyJh->value(m_nPainterlyJh);
	m_painterlyJh->align(FL_ALIGN_BOTTOM);
	m_painterlyJh->callback(cb_painterlyJhSlides);

	m_painterlyJs = new Fl_Value_Slider(330, 150, 25, 80, "Js");
	m_painterlyJs->user_data((void*)(this));
	m_painterlyJs->type(FL_VERT_NICE_SLIDER);
	m_painterlyJs->labelfont(FL_COURIER);
	m_painterlyJs->labelsize(12);
	m_painterlyJs->minimum(1);
	m_painterlyJs->maximum(0);
	m_painterlyJs->step(0.01);
	m_painterlyJs->value(m_nPainterlyJs);
	m_painterlyJs->align(FL_ALIGN_BOTTOM);
	m_painterlyJs->callback(cb_painterlyJsSlides);

	m_painterlyJv = new Fl_Value_Slider(360, 150, 25, 80, "Jv");
	m_painterlyJv->user_data((void*)(this));
	m_painterlyJv->type(FL_VERT_NICE_SLIDER);
	m_painterlyJv->labelfont(FL_COURIER);
	m_painterlyJv->labelsize(12);
	m_painterlyJv->minimum(1);
	m_painterlyJv->maximum(0);
	m_painterlyJv->step(0.01);
	m_painterlyJv->value(m_nPainterlyJv);
	m_painterlyJv->align(FL_ALIGN_BOTTOM);
	m_painterlyJv->callback(cb_painterlyJvSlides);

	m_painterlyStroke->deactivate();
	m_painterlyThreshold->deactivate();
	m_painterlyCurvature->deactivate();
	m_painterlyBlur->deactivate();
	m_painterlyGridSize->deactivate();
	m_painterlyMinStrokeL->deactivate();
	m_painterlyMaxStrokeL->deactivate();
	m_painterlyAlpha->deactivate();
	m_painterlyLayers->deactivate();
	m_painterlyR0Level->deactivate();
	m_painterlyJr->deactivate();
	m_painterlyJg->deactivate();
	m_painterlyJb->deactivate();
	m_painterlyJh->deactivate();
	m_painterlyJs->deactivate();
	m_painterlyJv->deactivate();
	*/
	m_painterlylDialog->end();


	m_nSize = 10;
	m_nLineWidth = 1;
	m_nLineAngle = 0;
	m_nAlpha = 1.00;
	m_nRandomAttr = false;
	m_nEnableAutoDraw = false;
	m_nSpacing = 1;
	m_nThreshold = 150;
	m_nEnableEdgeClipping = false;
	m_nAnotherGradient = false;
	// brush dialog definition
	m_brushDialog = new Fl_Window(390, 300, "Brush Dialog");
		// Add a brush type choice to the dialog
		m_BrushTypeChoice = new Fl_Choice(50,10,150,20,"&Brush");
		m_BrushTypeChoice->user_data((void*)(this));	// record self to be used by static callback functions
		m_BrushTypeChoice->menu(brushTypeMenu);
		m_BrushTypeChoice->callback(cb_brushChoice);

		m_ClearCanvasButton = new Fl_Button(250,10,130,20,"&Clear Canvas");
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
		
		m_EdgeClipingButton = new Fl_Light_Button(10, 200, 120, 25, "&Edge Clipping");
		m_EdgeClipingButton->user_data((void*)(this));
		m_EdgeClipingButton->callback(cb_toggle_cliping_button);
		m_EdgeClipingButton->value(m_nEnableEdgeClipping);

		m_AnotherGradientButton = new Fl_Light_Button(230, 200, 150, 25, "&Another Gradient");
		m_AnotherGradientButton->user_data((void*)(this));
		m_AnotherGradientButton->callback(cb_another_gradient_button);
		m_AnotherGradientButton->value(m_nAnotherGradient);

		m_AutoPaintSpacingSlider = new Fl_Value_Slider(10, 235, 150, 20, "Spacing");
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

		m_RandomAttrButton = new Fl_Light_Button(220, 235, 100, 25, "&Attr Rand");
		m_RandomAttrButton->user_data((void*)(this));
		m_RandomAttrButton->callback(cb_Rand_Attr_button);
		m_RandomAttrButton->value(m_nRandomAttr);

		m_AutoPaintButton = new Fl_Button(330, 235, 50, 25, "&Paint");
		m_AutoPaintButton->user_data((void*)(this));
		m_AutoPaintButton->callback(cb_Auto_Paint_button);
		
		//disable line width slider and angle slider 
		m_LineWidthSlider->deactivate();
		m_LineAngleSlider->deactivate();
		m_EdgeClipingButton->deactivate();
		m_AnotherGradientButton->deactivate();
		m_BrushTypeChoice->deactivate();

		m_ThresholdSlider = new Fl_Value_Slider(10, 265, 200, 20, "Edge Threshold");
		m_ThresholdSlider->user_data((void*)(this));	// record self to be used by static callback functions
		m_ThresholdSlider->type(FL_HOR_NICE_SLIDER);
		m_ThresholdSlider->labelfont(FL_COURIER);
		m_ThresholdSlider->labelsize(12);
		m_ThresholdSlider->minimum(0);
		m_ThresholdSlider->maximum(500);
		m_ThresholdSlider->step(1);
		m_ThresholdSlider->value(m_nThreshold);
		m_ThresholdSlider->align(FL_ALIGN_RIGHT);
		m_ThresholdSlider->callback(cb_ThresholdSlides);

		m_RandomAttrButton = new Fl_Button(330, 265, 50, 25, "&Do it");
		m_RandomAttrButton->user_data((void*)(this));
		m_RandomAttrButton->callback(cb_Generating_Edge_Image_button);

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

