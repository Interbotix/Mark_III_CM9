#include "Arduino.h"
#include "PS4_Input.h"

PS4_Input::PS4_Input(){
    rightV = 0;
    rightH = 0;
    leftV = 0;
    leftH = 0;
    ps = 0;
    share = 0;
    options = 0;
    triangle = 0;
    square = 0;
    circle = 0;
    x = 0;
    up = 0;
    down = 0;
    left = 0;
    right = 0;
    l1 = 0;
    l2 = 0;
    l3 = 0;
    r1 = 0;
    r2 = 0;
    r3 = 0;
// this->message = Serial2.read(); // read whatever might be there and discard
}

void PS4_Input::Start_Serial(){
//  Serial.begin(115200);
  Serial2.begin(115200);
  //Serial2.println("CM9_Ready!\n");
}

String PS4_Input::Print_Out(){
  char printout [400];

  sprintf(printout, "PLAYSATION 4 BUTTON PRESS PRINT OUT : \nl3h : %d\nl3v : %d\nr3h : %d\nr3v : %d\n * *********DIGITAL BUTTONS : **********\nPS : %d\nSHARE : %d\nOPTIONS : %d\nTRIANGLE : %d\nSQUARE : %d\nX : %d\nCIRCLE : %d\nUP : %d\nDOWN : %d\nLEFT : %d\nRIGHT : %d\nL1 : %d\nR1 : %d\nL2 : %d\nR2 : %d\nR3 : %d\nL3 : %d\n",leftH,leftV,rightH,rightV,ps,share,options,triangle,square,x,circle,up,down,left,right,l1,r1,l2,r2,l3,r3);
  
  return (String)printout;
}

void PS4_Input::Reset_Bools(){
    //Reset Bools
    ps = 0;
    share = 0;
    options = 0;
    triangle = 0;
    square = 0;
    circle = 0;
    x = 0;
    up = 0;
    down = 0;
    left = 0;
    right = 0;
    l1 = 0;
    l2 = 0;
    l3 = 0;
    r1 = 0;
    r2 = 0;
    r3 = 0;
}

void PS4_Input::Reset_Analogues() {
    //Reset Analogues 
    rightV = 0;
    rightH = 0;
    leftV = 0;
    leftH = 0;
}

int PS4_Input::Get_Input(){
  int message_received = 0;
  int analogue_value = 0;
  if (Serial2.available() > 0){
    // read the incoming string until '\n' character:
    message = Serial2.readStringUntil('\n');

    //************************************LEFT ANALOG STICK************************************
    if((message.indexOf("L3") >= 0)){
      if (message.lastIndexOf("_hor") >= 0){
        analogue_value = message.substring(message.lastIndexOf(": ")+1).toInt();
        if (abs(analogue_value) > 10) {
            leftH = analogue_value;
        }
        //left is negative, right is positive
      }
      else if(message.lastIndexOf("_ver") >= 0) {
        analogue_value = message.substring(message.lastIndexOf(": ")+1).toInt();
        if (abs(analogue_value) > 10) {
            leftV = analogue_value;
        }
        //up is negative, down is positive
      }
      else{  
        l3 = 1;
      }
    }
    //******************************************************************************************

    //************************************RIGHT ANALOG STICK************************************
    if((message.indexOf("R3") >= 0)){
      if (message.lastIndexOf("_hor") >= 0){
        analogue_value = message.substring(message.lastIndexOf(": ")+1).toInt();
        if (abs(analogue_value) > 10) {
            rightH = analogue_value;
        }
        //left is negative, right is positive
      }
      else if(message.lastIndexOf("_ver") >= 0) {
        analogue_value = message.substring(message.lastIndexOf(": ")+1).toInt();
        if (abs(analogue_value) > 10) {
            rightV = analogue_value;
        }
        //up is negative, down is positive
      }
      else{  
        r3 = 1;
      }
    }
    //******************************************************************************************

    //**************************************DIGITAL BUTTONS**************************************
    if((message.indexOf("R2") >= 0)){
      r2 = 1;
    }
    if((message.indexOf("L2") >= 0)){
      l2 = 1;
    }
    if((message.indexOf("R1") >= 0)){
      r1 = 1;
    }
    if((message.indexOf("L1") >= 0)){
      l1 = 1;
    }
    if((message.indexOf("RIGHT") >= 0)){
      right = 1;
    }
    if((message.indexOf("LEFT") >= 0)){
      left = 1;
    }
    if((message.indexOf("UP") >= 0)){
      up = 1;
    }
    if((message.indexOf("DOWN") >= 0)){
      down = 1;
    }
    if((message.indexOf("PS") >= 0)){
      ps = 1;
    }
    if((message.indexOf("SHARE") >= 0)){
      share = 1;
    }
    if((message.indexOf("OPTIONS") >= 0)){
      options = 1;
    }
    if((message.indexOf("X") >= 0)){
      x = 1;
    }
    if((message.indexOf("SQUARE") >= 0)){
      square = 1;
    }
    if((message.indexOf("TRIANGLE") >= 0)){
      triangle = 1;
    }
    if((message.indexOf("CIRCLE") >= 0)){
      circle = 1;
    }
    //*******************************************************************************************
    message_received = 1;
  } // end -> if serial2 available
  else {
      Reset_Analogues();
  }
 /* if (!analogue_value) {
      Reset_Analogues();
  }*/
  return message_received;

  // Need to workout when to reset the bools
  
}
