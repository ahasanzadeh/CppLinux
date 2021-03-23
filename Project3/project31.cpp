#include <iostream>
#include <fstream>

using namespace std;

//Programmer: Amin Hasanzadeh
//Date: November 2 2019
//Purpose: develop a program to modifying pictureson acomputer

int const MIN_ALLOWED_COLOR_VAL = 0;
int const MAX_ALLOWED_COLOR_VAL = 255;
int const ROW_INITIAL_VAL = -99999;
int const COL_INITIAL_VAL = -99999;
int const ROW_SIZE_VAL = 10;
int const COL_SIZE_VAL = 18;
const double BRIGHTNESS_FACTOR1 = 0.50;
const double BRIGHTNESS_FACTOR2 = 0.25;
const double BRIGHTNESS_FACTOR3 = 0.75;
const int ROW_TEST_VAL = 16;
const int COL_TEST_VAL = 32;
const int TEST_IMAGE_NUM = 3;

//Introducing ColorClass
class ColorClass{
private: 
  int inRed;
  int inGreen;
  int inBlue;
  
  //A function for clipping and evaluating input color parameters
  bool clipColorVal(int &inVal1, int &inVal2, int &inVal3);

public:
  ColorClass();
  ColorClass(int inRed, int inGreen, int inBlue);

  void setToBlack();
  void setToRed();
  void setToGreen();
  void setToBlue();
  void setToWhite();

  bool setTo(int inRed, int inGreen,int inBlue);

  bool setTo(ColorClass &inColor);

  bool addColor(ColorClass &rhs);

  bool subtractColor(ColorClass &rhs);

  bool adjustBrightness(double adjFactor);

  void printComponentValues();
};

//Introducing RowColumnClass
class RowColumnClass{
private: 
  int inRow;
  int inCol;

public:
  RowColumnClass();
  RowColumnClass(int inRow, int inCol);

  void setRowCol(int inRow, int inCol);
  void setRow(int inRow);
  void setCol(int inCol);

  int getRow(); 
  int getCol();

  void addRowColTo(RowColumnClass &inRowCol);

  void printRowCol();
};

//Introducing ColorImageClass
class ColorImageClass{
private: 
  static const int rowSize = ROW_SIZE_VAL;
  static const int colSize = COL_SIZE_VAL;
  ColorClass arr[rowSize][colSize];

public:
  ColorImageClass();

  void initializeTo(ColorClass &inColor);

  bool addImageTo(ColorImageClass &rhsImg);

  bool addImages(int numImgsToAdd,
                 ColorImageClass imagesToAdd []);

  bool setColorAtLocation(RowColumnClass &inRowCol,
                          ColorClass &inColor);

  bool getColorAtLocation(RowColumnClass &inRowCol,
                          ColorClass &outColor);

  void printImage();
};

int inMenuChoice(int &mainMenuChoic);

int rectSpecMtd(int &upLeftRecRow, int &upLeftRecClmn, int &numRowRec, int &numClmnRec);

void colorChoice();

int chkPpmFile(string fileNamePpm, int &rowSize1, int &colSize1, int &mxValColor);

#ifdef ANDREW_TEST
#include "andrewTest.h"
#else
int main()
{
  string fileNamePpm, fileNameContPtrn, fileNamePpmInsrt, fileNamePpmOut;
  int mainMenuChoic, upLeftRecRow, upLeftRecClmn, numRowRec, rowSize1, colSize1, mxValColor, numClmnRec, recColor = 0, recFillOptn = 0, pattColor = 0, transpColor = 0;

  cout << "Enter string for PPM image file name to load: ";
  cin >>  fileNamePpm;

  chkPpmFile(fileNamePpm, rowSize1, colSize1, mxValColor);

  do
  {
    inMenuChoice(mainMenuChoic);

    if (mainMenuChoic == 1)
    {
      rectSpecMtd(upLeftRecRow, upLeftRecClmn, numRowRec, numClmnRec);

      colorChoice();

      cout << "Enter int for rectangle color: ";
      cin >> recColor;

      cout << "1. No" << endl;
      cout << "2. Yes" << endl;

      cout << "Enter int for rectangle fill option: ";
      cin >> recFillOptn;
    }
    else if (mainMenuChoic == 2)
    {
      cout << "Enter string for file name containing pattern: ";  
      cin >>  fileNameContPtrn;

      cout << "Enter upper left corner of pattern row and column: ";
      cin >> upLeftRecRow;
      cin >> upLeftRecClmn; 

      colorChoice();

      cout << "Enter int for pattern color: ";
      cin >> pattColor;
    }
    else if (mainMenuChoic == 3)
    {
      cout << "Enter string for file name of PPM image to insert: ";  
      cin >>  fileNamePpmInsrt;

      cout << "Enter upper left corner to insert image row and column: ";
      cin >> upLeftRecRow;
      cin >> upLeftRecClmn;

      colorChoice();

      cout << "Enter int for transparecy color: ";
      cin >> transpColor;
    }
    else if (mainMenuChoic == 4)
    {
      cout << "Enter string for PPM file name to output: ";
      cin >>  fileNamePpmOut;
    }
  }
  while (mainMenuChoic != 5);

  cout << "Thank you for using this program" << endl;

  return 0;
}
#endif

//Implementing functions of ColorClass:
//A private function to clip the color values to an specific lower and upper
//limit values, and return a boolean (true) if any clipping was necessary  
bool ColorClass::clipColorVal(int &inVal1, int &inVal2, int &inVal3)
{
  bool retVal = ((inVal1 < MIN_ALLOWED_COLOR_VAL)
                || (inVal1 > MAX_ALLOWED_COLOR_VAL)
                || (inVal2 < MIN_ALLOWED_COLOR_VAL)
                || (inVal2 > MAX_ALLOWED_COLOR_VAL)
                || (inVal3 < MIN_ALLOWED_COLOR_VAL)
                || (inVal3 > MAX_ALLOWED_COLOR_VAL));

  if (inVal1 < MIN_ALLOWED_COLOR_VAL)
    inVal1 = MIN_ALLOWED_COLOR_VAL;

  if (inVal1 > MAX_ALLOWED_COLOR_VAL)
    inVal1 = MAX_ALLOWED_COLOR_VAL;

  if (inVal2 < MIN_ALLOWED_COLOR_VAL)
    inVal2 = MIN_ALLOWED_COLOR_VAL;

  if (inVal2 > MAX_ALLOWED_COLOR_VAL)
    inVal2 = MAX_ALLOWED_COLOR_VAL;

  if (inVal3 < MIN_ALLOWED_COLOR_VAL)
    inVal3 = MIN_ALLOWED_COLOR_VAL;

  if (inVal3 > MAX_ALLOWED_COLOR_VAL)
    inVal3 = MAX_ALLOWED_COLOR_VAL;

  return retVal;  
}

//Default constructor that set the color’s initial RGB values to the color
//full white
ColorClass::ColorClass()
{
  inRed = MAX_ALLOWED_COLOR_VAL;
  inGreen = MAX_ALLOWED_COLOR_VAL;
  inBlue = MAX_ALLOWED_COLOR_VAL;
}

//Default constructor that set the color’s initial RGB values to
//the values provided
ColorClass::ColorClass(int inRedNew, int inGreenNew, int inBlueNew)
{
  inRed = inRedNew;
  inGreen = inGreenNew;
  inBlue = inBlueNew;

  clipColorVal(inRed, inGreen, inBlue);
}

//A public function to set the color’s component color values to black
void ColorClass::setToBlack()
{
  inRed = MIN_ALLOWED_COLOR_VAL;
  inGreen = MIN_ALLOWED_COLOR_VAL;
  inBlue = MIN_ALLOWED_COLOR_VAL;
}

//A public function to set the color’s component color values to red
void ColorClass::setToRed()
{
  inRed = MAX_ALLOWED_COLOR_VAL;
  inGreen = MIN_ALLOWED_COLOR_VAL;
  inBlue = MIN_ALLOWED_COLOR_VAL;
}

//A public function to set the color’s component color values to green
void ColorClass::setToGreen()
{
  inRed = MIN_ALLOWED_COLOR_VAL;
  inGreen = MAX_ALLOWED_COLOR_VAL;
  inBlue = MIN_ALLOWED_COLOR_VAL;
}

//A public function to set the color’s component color values to blue
void ColorClass::setToBlue()
{
  inRed = MIN_ALLOWED_COLOR_VAL;
  inGreen = MIN_ALLOWED_COLOR_VAL;
  inBlue = MAX_ALLOWED_COLOR_VAL;
}

//A public function to set the color’s component color values to white
void ColorClass::setToWhite()
{
  inRed = MAX_ALLOWED_COLOR_VAL;
  inGreen = MAX_ALLOWED_COLOR_VAL;
  inBlue = MAX_ALLOWED_COLOR_VAL;
}

//A public function to set the color object's RGB values to the provided 
//values
bool ColorClass::setTo(int inRedNew, int inGreenNew,int inBlueNew)
{
  inRed = inRedNew;
  inGreen = inGreenNew;
  inBlue = inBlueNew;
  
  return clipColorVal(inRed, inGreen, inBlue);
}

//A public function to set the color object's RGB values to the passed 
//input parameter
bool ColorClass::setTo(ColorClass &inColor)
{
  inRed = inColor.inRed;
  inGreen = inColor.inGreen;
  inBlue = inColor.inBlue;

  return clipColorVal(inRed, inGreen, inBlue);
}

//A public function to add each RGB value to the corresponding value from
//the input parameter
bool ColorClass::addColor(ColorClass &rhs)
{
  inRed += rhs.inRed;
  inGreen += rhs.inGreen;
  inBlue += rhs.inBlue;

  return clipColorVal(inRed, inGreen, inBlue);
}

//A public function to subtract each RGB value to the corresponding value
//from the input parameter
bool ColorClass::subtractColor(ColorClass &rhs)
{
  inRed -= rhs.inRed;
  inGreen -= rhs.inGreen;
  inBlue -= rhs.inBlue;

  return clipColorVal(inRed, inGreen, inBlue);
}

//A public function to adjust brightness which multiplies each RGB value
//by the adjustment input parameter
bool ColorClass::adjustBrightness(double adjFactor)
{
  inRed = static_cast< int > (inRed * adjFactor);
  inGreen = static_cast< int > (inGreen * adjFactor);
  inBlue = static_cast< int > (inBlue * adjFactor);

  return clipColorVal(inRed, inGreen, inBlue);
}

//A public function to print the component color value with
//R:<red> G: <green> B:<blue> format
void ColorClass::printComponentValues()
{
  cout << "R: " << inRed << " G: " << inGreen << " B: " << inBlue;
}

//Implementing functions of RowColumnClass
//Default constructor that sets the row and column values
//of the object to -99999
RowColumnClass::RowColumnClass()
{
  inRow = ROW_INITIAL_VAL;
  inCol = COL_INITIAL_VAL;
}

//Value constructor that sets the row and column values
//of the object to the input values
RowColumnClass::RowColumnClass(int inRowNew, int inColNew)
{
  inRow = inRowNew;
  inCol = inColNew;
}

//A public fuction to set the row and column values of the object
//to the input values
void RowColumnClass::setRowCol(int inRowNew, int inColNew)
{
  inRow = inRowNew;
  inCol = inColNew;
}

//A public fuction to set the row value of the object
//to the input values
void RowColumnClass::setRow(int inRowNew)
{
  inRow = inRowNew;
}

//A public fuction to set the column value of the object
//to the input values
void RowColumnClass::setCol(int inColNew)
{
  inCol = inColNew;
}

//A public fuction to return the row value of the object
//to the caller
int RowColumnClass::getRow() 
{ 
  return inRow;
}

//A public fuction to return the column value of the object
//to the caller
int RowColumnClass::getCol() 
{ 
  return inCol; 
}

//A public function to add the row and column index values in the input
//parameter to the row and column index of the called object
void RowColumnClass::addRowColTo(RowColumnClass &inRowCol)
{
  inRow += inRowCol.inRow;
  inCol += inRowCol.inCol;
}

//A public function to print the row and column of the object in the 
//format "[<row>,<col>]"
void RowColumnClass::printRowCol()
{
  cout << "[" << inRow << "," << inCol << "]";
}

//Implementing functions of ColorImageClass:
//Default constructor that sets all pixels in the image to black
ColorImageClass::ColorImageClass()
{
  for (int i = 0; i < rowSize; i++)
    for (int j = 0; j < colSize; j++)  
      arr[i][j].setToBlack();
}

//A public fuction to assign input color to all pixels in the image
void ColorImageClass::initializeTo(ColorClass &inColor)
{
  for (int i = 0; i < rowSize; i++)
    for (int j = 0; j < colSize; j++)  
      arr[i][j].setTo(inColor); 
}

//A public fuction to add corresponding pixels of the right hand side 
//to the current image and replace the resulted image in the 
//location of current image
bool ColorImageClass::addImageTo(ColorImageClass &rhsImg)
{
  bool retVal = false;

  for (int i = 0; i < rowSize; i++)
    for (int j = 0; j < colSize; j++)  
      if (arr[i][j].addColor(rhsImg.arr[i][j]))
        retVal = true;
           
  return retVal;
}

//A public fuction to add corresponding pixels of the specific number
//of input images and replace the resulted image in the location
//of current image
bool ColorImageClass::addImages(int numImgsToAdd, 
                                ColorImageClass imagesToAdd [])
{
  bool retVal = false;
  
  //Replace image number zero with current index image 
  for (int i = 0; i < rowSize; i++)
    for (int j = 0; j < colSize; j++)
      arr[i][j].setTo(imagesToAdd[0].arr[i][j]);

  for (int i = 1; i < numImgsToAdd; i++) 
    if (addImageTo(imagesToAdd[i]))
      retVal = true;
         
  return retVal;
}

//A public fuction to set the color of an specific pixel location 
bool ColorImageClass::setColorAtLocation(RowColumnClass &inRowCol,
                                         ColorClass &inColor)
{
  bool retVal = true;

  int i = inRowCol.getRow();
  int j = inRowCol.getCol();

  if ((i >= 0) && (i < rowSize) && (j >= 0) && (j < colSize))
    arr[i][j].setTo(inColor);
  else 
    retVal = false; 

  return retVal;
}

//A public fuction to return the color of an specific pixel location  
bool ColorImageClass::getColorAtLocation(RowColumnClass &inRowCol,
                                         ColorClass &outColor)
{
  bool retVal = true;

  int i = inRowCol.getRow();
  int j = inRowCol.getCol();

  if ((i >= 0) && (i < rowSize) && (j >= 0) && (j < colSize))
    outColor.setTo(arr[i][j]);
  else 
    retVal = false; 

  return retVal;
}

//A public fuction to print all pixels in the image  
void ColorImageClass::printImage()
{
  for (int i = 0; i < rowSize; i++)  
    for (int j = 0; j < colSize; j++)  
    {
      arr[i][j].printComponentValues();
      if (j < (colSize - 1))
        cout << "--";
      if (j == (colSize - 1))
        cout << endl;
    }
}

int inMenuChoice(int &mainMenuChoic)
{
  cout << "1. Annotate image with rectangle" << endl;
  cout << "2. Annotate image with pattern from file" << endl;
  cout << "3. Insert another imag" << endl;
  cout << "4. Write out current image" << endl;
  cout << "5. Exit the program" << endl;

  cout << "Enter int for main menu choice: ";
  cin >> mainMenuChoic;

  return 0;
}

int rectSpecMtd(int &upLeftRecRow, int &upLeftRecClmn, int &numRowRec, int &numClmnRec)
{
  int rectSpecMtd, lwrLeftRecRow, lwrLeftRecClmn, ctrRowRec, ctrClmnRec, hlfNumRowRec, hlfNumClmnRec;

  cout << "1. Specify upper left and lower right corners of rectangle" << endl;
  cout << "2. Specify upper left corner and dimensions of rectangle" << endl;
  cout << "3. Specify extent from center of rectangle" << endl;

  cout << "Enter int for rectangle specification method: "; 
  cin >> rectSpecMtd;

  if (rectSpecMtd == 1)
  {
    cout << "Enter upper left corner row and column: ";
    cin >> upLeftRecRow;
    cin >> upLeftRecClmn; 
    cout << "Enter lower right corner row and column: ";
    cin >> lwrLeftRecRow;
    cin >> lwrLeftRecClmn; 
    numRowRec = lwrLeftRecRow - upLeftRecRow;
    numClmnRec = lwrLeftRecClmn - upLeftRecClmn;
  }
  else if (rectSpecMtd == 2) 
  {
    cout << "Enter upper left corner row and column: ";
    cin >> upLeftRecRow;
    cin >> upLeftRecClmn; 
    cout << "Enter int for number of rows: ";
    cin >> numRowRec;
    cout << "Enter int for number of columns: ";
    cin >> numClmnRec;
  }
  else if (rectSpecMtd == 3) 
  {
    cout << "Enter rectangle center row and column: ";
    cin >> ctrRowRec;
    cin >> ctrClmnRec;
    cout << "Enter int for half number of rows: ";
    cin >> hlfNumRowRec;
    numRowRec = hlfNumRowRec * 2;
    cout << "Enter int for half number of columns: ";
    cin >> hlfNumClmnRec;
    numClmnRec = hlfNumClmnRec * 2;
    upLeftRecRow = ctrRowRec - hlfNumRowRec;
    upLeftRecClmn = ctrClmnRec - hlfNumClmnRec;
  }

  return 0;
}

void colorChoice()
{
  cout << "1. Red" << endl;
  cout << "2. Green" << endl;
  cout << "3. Blue" << endl;
  cout << "4. Black" << endl;
  cout << "5. White" << endl;
}

int chkPpmFile(string fileNamePpm, int &rowSize1, int &colSize1, int &mxValColor)
{
  string ppmMagicNum;

  ifstream inFile;
  bool validInputFound;

  inFile.open(fileNamePpm);

  if (inFile.fail())
  {
    cout << "Unable to open input file!" << endl;
  }

  validInputFound = false;
  while (!validInputFound)
  {
    inFile >> ppmMagicNum;
    if (ppmMagicNum != "P3")
    {
      cout << "The entered PPM file is not valid!" << endl;
    }
    if (inFile.eof())
    {
      cout << "EOF before reading PPM magic number" << endl;
    }
    else if (inFile.fail())
    {
      inFile.clear();
      inFile.ignore(200, '\n');
    }
    else
    {
      validInputFound = true;
    }
  }

  validInputFound = false;
  while (!validInputFound)
  {
    inFile >> rowSize1;
    if (inFile.eof())
    {
      cout << "EOF before reading row-size" << endl;
    }
    else if (inFile.fail())
    {
      inFile.clear();
      inFile.ignore(200, '\n');
    }
    else
    {
      validInputFound = true;
    }
  }

  validInputFound = false;
  while (!validInputFound)
  {
    inFile >> colSize1;
    if (inFile.eof())
    {
      cout << "EOF before reading column-Size" << endl;
    }
    else if (inFile.fail())
    {
      inFile.clear();
      inFile.ignore(200, '\n');
    }
    else
    {
      validInputFound = true;
    }
  }

  validInputFound = false;
  while (!validInputFound)
  {
    inFile >> mxValColor;
    if (inFile.eof())
    {
      cout << "EOF before reading Max color value" << endl;
    }
    else if (inFile.fail())
    {
      inFile.clear();
      inFile.ignore(200, '\n');
    }
    else
    {
      validInputFound = true;
    }
  }

  inFile.close();

  return (0);
}

