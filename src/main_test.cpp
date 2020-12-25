#ifdef CHECK_BOARD

/****************************************************
FILE:  AMS_5600_example

Author: Tom Denton
www.ams.com
Date: 15 Dec 2014
Version 1.00

Description:  AS5600 "Potuino" demonstration application

AMS5600 Programming Sketch
***************************************************/

#include <Wire.h>
#include "AS5600.h"

#define SYS_VOL   3.3

String lastResponse;
String noMagnetStr = "Error: magnet not detected";

AMS_5600 ams5600;


/*******************************************************
 function: printMenu
 In: none
 Out: none
 Description: prints menu options and result of last
 command
*******************************************************/
void printMenu()
{
  for(int i =0; i<20;i++)
    Serial.println();
  Serial.println("AS5600 Serial Interface Program");
  Serial.println("");
  if(lastResponse.length()>0)
  {
    Serial.println(lastResponse);
    Serial.println("");
  }
  Serial.print("1 - Set start position\t|  "); Serial.println(" 6 - get end position");
  Serial.print("2 - Set end position\t|  ");   Serial.println(" 7 - get raw angle");
  Serial.print("3 - Set max angle range\t|  ");  Serial.println(" 8 - get scaled angle");
  Serial.print("4 - Get max angle range\t|  ");  Serial.println(" 9 - detect magnet");
  Serial.print("5 - Get start position \t\t|  ");     Serial.println("10 - get magnet strength");
  Serial.println();
  Serial.print("Number of burns remaining: "); Serial.println(String(3 - ams5600.getBurnCount()));
  Serial.println("96 - Burn Angle");
  Serial.println("98 - Burn Settings (one time)");
}

/*******************************************************
 Function: convertRawAngleToDegrees
 In: angle data from AMS_5600::getRawAngle
 Out: human readable degrees as float
 Description: takes the raw angle and calculates
 float value in degrees.
*******************************************************/
float convertRawAngleToDegrees(word newAngle)
{
  /* Raw data reports 0 - 4095 segments, which is 0.087 of a degree */
  float retVal = newAngle * 0.087;
  return retVal;
}

/*******************************************************
  Function: convertScaledAngleToDegrees
 In: angle data from AMS_5600::getScaledAngle
 Out: human readable degrees as float
 Description: takes the scaled angle and calculates
 float value in degrees.
*******************************************************/
float convertScaledAngleToDegrees(word newAngle)
{
  word startPos = ams5600.getStartPosition();
  word endPos = ams5600.getEndPosition();
  word maxAngle = ams5600.getMaxAngle();

  float multipler = 0;

  /* max angle and end position are mutually exclusive*/
  if(maxAngle >0)
  {
    if(startPos == 0)
      multipler = (maxAngle*0.0878)/4096;
    else  /*startPos is set to something*/
      multipler = ((maxAngle*0.0878)-(startPos * 0.0878))/4096;
  }
  else
  {
    if((startPos == 0) && (endPos == 0))
      multipler = 0.0878;
    else if ((startPos > 0 ) && (endPos == 0))
      multipler = ((360 * 0.0878) - (startPos * 0.0878)) / 4096;
    else if ((startPos == 0 ) && (endPos > 0))
      multipler = (endPos*0.0878) / 4096;
    else if ((startPos > 0 ) && (endPos > 0))
      multipler = ((endPos*0.0878)-(startPos * 0.0878))/ 4096;
  }
  return (newAngle * multipler);
}

/*******************************************************
 Function: burnAngle
 In: none
 Out: human readable string of success or failure
 Description: attempts to burn angle data to AMS5600
******************************************************/
String burnAngle()
{
  int burnResult = ams5600.burnAngle();
  String returnStr = "Brun angle error: ";

  switch (burnResult)
  {
    case 1:
      returnStr = "Brun angle success";
      break;
    case -1:
      returnStr += "no magnet detected";
      break;
    case -2:
      returnStr += "no more burns left";
      break;
    case -3:
      returnStr += "no positions set";
      break;
    default:
      returnStr += "unknown";
      break;
  }
  return returnStr;
}

/*******************************************************
 Function: burnMaxAngleAndConfig
 In: none
 Out: human readable string of sucess or failure
 Description: attempts to burn max angle and config data
 to AMS5600
*******************************************************/
String burnMaxAngleAndConfig()
{
  int burnResult = ams5600.burnMaxAngleAndConfig();
  String retStr = "Brun max angle and config error: ";

  switch(burnResult)
  {
    case 1:
      retStr = "Brun max angle and config success";
      break;
    case -1:
      retStr += "chip has been burned once already";
      break;
    case -2:
      retStr += "max angle less than 18 degrees";
      break;
    default:
      retStr += "unknown";
      break;
  }
  return retStr;
}

/*******************************************************
 function: setup
 In: none
 Out: none
 Description: called by system at startup
*******************************************************/
void setup(){
 Serial.begin(115200);
 Wire.begin();
 printMenu();
}

/*******************************************************
 Function: loop
 In: none
 Out: none
 Description: main program loop
*******************************************************/
void loop()
{

  if (Serial.available() > 0)
  {
    char incomingByteBuffer[5] = {0};
    char incomingByte = 0;

    incomingByteBuffer[0] = NULL;
    incomingByteBuffer[1] = NULL;

    Serial.readBytes(incomingByteBuffer,2);

    if ((incomingByteBuffer[0] >= 48) && (incomingByteBuffer[0] < 60))
    {
      incomingByte = incomingByteBuffer[0] - 48;
    }

    if ((incomingByteBuffer[1] >= 48) && (incomingByteBuffer[1] < 60))
    {
      incomingByte *=10;
      incomingByte += incomingByteBuffer[1] - 48;
    }


    switch (incomingByte)
    {
      case 1:
      {
        if(ams5600.detectMagnet()==1)
          lastResponse = ("Start angle set to = "+String(convertRawAngleToDegrees(ams5600.setStartPosition()), DEC));  //Print Raw Angle Value
        else
          lastResponse = noMagnetStr;
      }
      break;

      case 2:
      {
        if(ams5600.detectMagnet()==1)
          lastResponse = ("End angle set to = "+String(convertRawAngleToDegrees(ams5600.setEndPosition()), DEC));
        else
          lastResponse = noMagnetStr;
      }
      break;

      case 3:
      {
        if(ams5600.detectMagnet()==1)
          lastResponse = ("Max angle range set to = "+String(convertRawAngleToDegrees(ams5600.setMaxAngle()), DEC));
        else
          lastResponse = noMagnetStr;
      }
      break;

      case 4:
      {
        lastResponse = ("Max angle range= "+String(convertRawAngleToDegrees(ams5600.getMaxAngle()), DEC));
      }
      break;

      case 5:
      {
        lastResponse = ("Start angle = "+String(convertRawAngleToDegrees(ams5600.getStartPosition()), DEC));
      }
      break;

      case 6:
      {
        lastResponse = "End angle = " + String(convertRawAngleToDegrees(ams5600.getEndPosition()),DEC);
      }
      break;

      case 7:
      {
        lastResponse = "Raw angle = "+ String(convertRawAngleToDegrees(ams5600.getRawAngle()),DEC);
      }
      break;

      case 8:
      {
        lastResponse = "Scaled angle = "+String(convertScaledAngleToDegrees(ams5600.getScaledAngle()),DEC);
      }
      break;

      case 9:
      {
        if(ams5600.detectMagnet()==1)
          lastResponse = "Magnet detected";
        else
          lastResponse = noMagnetStr;
      }
      break;

      case 10:
      {
        lastResponse = "Magnet strength ";
        if(ams5600.detectMagnet()==1)
        {
          int magStrength = ams5600.getMagnetStrength();

          if(magStrength == 1)
            lastResponse += "is weak";
          else if(magStrength == 2){
            lastResponse += "is acceptable";
            Serial.print("Current Magnitude: ");
            Serial.println(ams5600.getMagnitude());
          }
          else if (magStrength == 3)
            lastResponse += "is to strong";
        }
        else
          lastResponse = noMagnetStr;
      }
      break;

      case 96:
      {
          lastResponse = burnAngle();
      }
      break;

      case 98:
      {
          lastResponse = burnMaxAngleAndConfig();
      }
      break;

      default:
      {
          lastResponse = "Invalid Entry";
      }
      break;
    }
    /*end of menu processing */
    printMenu();
  }
}

#endif