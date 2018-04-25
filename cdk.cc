//Einar Longva (evl130030)
//CS3377.501

#include <iostream>
#include <cdk.h>
#include <string>
#include <stdint.h>
#include <stdio.h>
#include <iomanip>
#include <fstream>

#define MATRIX_WIDTH 4
#define MATRIX_HEIGHT 3
#define BOX_WIDTH 15
#define MATRIX_NAME_STRING "Test Matrix"

using namespace std;

int main(){

  WINDOW *window;
  CDKSCREEN *cdkscreen;
  CDKMATRIX *myMatrix;

  const char *rowTitles[] = {"R0", "R1", "R3", "R4", "R5"};
  const char *columnTitles[] = {"C0", "C1", "C2", "C3", "C4", "C5"};
  int boxWidths[] = {BOX_WIDTH, BOX_WIDTH, BOX_WIDTH, BOX_WIDTH, BOX_WIDTH, BOX_WIDTH};
  int boxTypes[] = {vMIXED, vMIXED, vMIXED, vMIXED, vMIXED, vMIXED};

  //INITIALIZE CDK SCREEN
  window = initscr();
  cdkscreen = initCDKScreen(window);

  //CDK COLORS
  initCDKColor();

  //CREATE MATRIX
  myMatrix = newCDKMatrix(cdkscreen, CENTER, CENTER, MATRIX_HEIGHT, MATRIX_WIDTH, MATRIX_HEIGHT, MATRIX_WIDTH, MATRIX_NAME_STRING, (char**) rowTitles, (char**) columnTitles, boxWidths, boxTypes, 1, 1, ' ', ROW, true, true, false);

  if(myMatrix == NULL){
    printf("Error creating Matrix\n");
    _exit(1);
  }

  //DISPLAY MATRIX
  drawCDKMatrix(myMatrix, true);

  //DISPLAY A MESSAGE
  setCDKMatrixCell(myMatrix, 2, 2, "Test");
  drawCDKMatrix(myMatrix, true);
  ///////////////////////////////////
  //USED TO PAUSE UNTIL KEY IS PRESSED
  unsigned char x;
  cin >> x;

  //CLEANUP SCREEn
  endCDK();
}
