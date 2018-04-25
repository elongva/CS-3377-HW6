//Einar Longva (evl130030)
//CS3377.501

#include <iostream>
#include <cdk.h>
#include <string.h>
#include <stdint.h>
#include <stdio.h>
#include <iomanip>
#include <fstream>

#define MATRIX_WIDTH 3
#define MATRIX_HEIGHT 5
#define BOX_WIDTH 20
#define MATRIX_NAME_STRING "Binary File Contents"

using namespace std;

const int maxRecordStringLength = 25;

class BinaryFileHeader{
public:
  uint32_t magicNumber;
  uint32_t versionNumber;
  uint64_t numRecords;
};

class BinaryFileRecord{
public:
  uint8_t strLength;
  char stringBuffer[maxRecordStringLength];
};

int main(){
  BinaryFileHeader *myHeader = new BinaryFileHeader();

  ifstream binInfile ("cs3377.bin", ios::in | ios::binary);

  binInfile.read((char*) myHeader, sizeof(BinaryFileHeader));
  cout << "Value was: " << setprecision(10) << myHeader->versionNumber << endl;

  BinaryFileRecord *myRecords = new BinaryFileRecord[myHeader->numRecords]();
  for(uint32_t i = 0; i < myHeader->numRecords; i++){
    binInfile.read((char*)(myRecords + i), sizeof(BinaryFileRecord));
  }

  binInfile.close();

  WINDOW *window;
  CDKSCREEN *cdkscreen;
  CDKMATRIX *myMatrix;

  const char *rowTitles[] = {"R0", "a", "b", "c", "d", "e"};
  const char *columnTitles[] = {"C0", "a", "b", "c"};
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
  //string tempStr = "Magic: 0x" + to_string(myHeader->magicNumber);
  // setCDKMatrixCell(myMatrix, 1, 1, tempStr.c_str());
  char buffer[100];
  sprintf(buffer, "%X", myHeader->magicNumber);
  string tempStr = "Magic: 0x";
  tempStr = tempStr + buffer;
  setCDKMatrixCell(myMatrix, 1, 1, tempStr.c_str());

  tempStr = "Version: ";
  tempStr = tempStr + to_string(myHeader->versionNumber);
  setCDKMatrixCell(myMatrix, 1, 2, tempStr.c_str());

  tempStr = "NumRecords: ";
  tempStr = tempStr + to_string(myHeader->numRecords);
  setCDKMatrixCell(myMatrix, 1, 3, tempStr.c_str());

  for(uint32_t i = 0; i < myHeader->numRecords; i++){
    string tempStr = "strlen: " + to_string(static_cast<uint16_t>(myRecords[i].strLength));
    setCDKMatrixCell(myMatrix, 2 + i, 1, tempStr.c_str());
    setCDKMatrixCell(myMatrix, 2 + i, 2, myRecords[i].stringBuffer);
  }
  drawCDKMatrix(myMatrix, true);
  ///////////////////////////////////
  //USED TO PAUSE UNTIL KEY IS PRESSED
  unsigned char x;
  cin >> x;

  //CLEANUP SCREEn
  endCDK();
}
