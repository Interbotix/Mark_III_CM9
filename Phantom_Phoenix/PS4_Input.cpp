#include "Arduino.h"
#include "PS4_Input.h"

PS4_Input::PS4_Input(){
    /* Constructor - initialise all members to zero. */
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
}

void PS4_Input::Start_Serial(){
    /* Starts serial port "Serial2" - sets up serial port from which the PS4 inputs can be read. */
  //Serial.begin(115200);
  Serial2.begin(115200);
  //Serial2.println("CM9_Ready!\n");
}

String PS4_Input::Print_Out(){
    /* Prints out current values of all the PS4 class members i.e. the current analogue values and button states.
        -> returns a String. */
  char printout [400];

  sprintf(printout, "PLAYSATION 4 BUTTON PRESS PRINT OUT : \nl3h : %d\nl3v : %d\nr3h : %d\nr3v : %d\n * *********DIGITAL BUTTONS : **********\nPS : %d\nSHARE : %d\nOPTIONS : %d\nTRIANGLE : %d\nSQUARE : %d\nX : %d\nCIRCLE : %d\nUP : %d\nDOWN : %d\nLEFT : %d\nRIGHT : %d\nL1 : %d\nR1 : %d\nL2 : %d\nR2 : %d\nR3 : %d\nL3 : %d\n",leftH,leftV,rightH,rightV,ps,share,options,triangle,square,x,circle,up,down,left,right,l1,r1,l2,r2,l3,r3);
  
  return (String)printout;
}

void PS4_Input::Reset_Bools(){
    /* Reset Bools - resets all of the digital button values to 0 (or off) state. */
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
    /* Resets the analogue values of the PS4 joysticks back to zero. */
    rightV = 0;
    rightH = 0;
    leftV = 0;
    leftH = 0;
}

int PS4_Input::Get_Input(){
  /* Processes the PS4 input - This functions reads the messages sent on the serial2 port. 
                             - One 'message' or one 'PS4 input' is determined by a "\n" end of line character. 
                             - In the case of analogue input, the message is dissected and analogue values are read and assigned to their appropriate analogue value PS4 class members
                             - In the case of digital input, if the message contains the button type, the appropriate digital button PS4 class member is updated. 
                                    -> Returns an int indicating a successful/unsuccessful read of PS4 input. */
  int message_received = 0;
  int analogue_value = 0;
  if (Serial2.available() > 0){
    // read the incoming string until '\n' character:
    message = Serial2.readStringUntil('\n');

    //****************************************ANALOGUES****************************************
    if ((message.indexOf("Analogues:") >= 0)) {
        //************************************LEFT ANALOG STICK************************************
        analogue_value = message.substring(message.lastIndexOf("L_hor: ") + 7, message.indexOf(";")).toInt();
        if (abs(analogue_value) > ANALOGUE_DEADZONE) {
            leftH = -analogue_value; // negative value -> switch directions on the left analogue
        }
        else leftH = 0;
        //left is negative, right is positive (after adding negative values)
        //update message to get rid of already read data
        message = message.substring(message.lastIndexOf("L_ver: "));
        analogue_value = message.substring(message.lastIndexOf("L_ver: ") + 7, message.indexOf(";")).toInt();
        if (abs(analogue_value) > ANALOGUE_DEADZONE) {
            leftV = analogue_value;
        }
        else leftV = 0;
        //up is negative, down is positive
        //update message to get rid of already read data
        message = message.substring(message.lastIndexOf("R_hor: "));
        //******************************************************************************************

        //************************************RIGHT ANALOG STICK************************************
        analogue_value = message.substring(message.lastIndexOf("R_hor: ") + 7, message.indexOf(";")).toInt();
        if (abs(analogue_value) > ANALOGUE_DEADZONE) {
            rightH = analogue_value;
        }
        else rightH = 0;
        //left is negative, right is positive
        //update message to get rid of already read data
        message = message.substring(message.lastIndexOf("R_ver: "));
        analogue_value = message.substring(message.lastIndexOf("R_ver: ") + 7, message.indexOf(";")).toInt();
        if (abs(analogue_value) > ANALOGUE_DEADZONE) {
            rightV = analogue_value;
        }
        else rightV = 0;
        //up is negative, down is positive
        //******************************************************************************************
    } // end analogue
    //******************************************************************************************

    //**************************************DIGITAL BUTTONS**************************************
    if ((message.indexOf("R3") >= 0)) {
        r2 = 1;
    }
    if ((message.indexOf("L3") >= 0)) {
        l3 = 1;
    }
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
  return message_received;  
}
