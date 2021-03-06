//====================================================================
//Project Lynxmotion Phoenix
//Description: 
//    This is the hardware configuration file for the 
//    Version 2 PhantomX robot.
//    Will first define to use their commander unit.
//
//Date: June 19, 2013
//Programmer: Kurt (aka KurtE)
//
//NEW IN V1.0
//   - First Release - Changes from Trossen member KingPin
//
//====================================================================
#ifndef OCTO_CFG_H
#define OCTO_CFG_H
//==================================================================================================================================
// Define which input classes we will use. If we wish to use more than one we need to define USEMULTI - This will define a forwarder
//    type implementation, that the Inputcontroller will need to call.  There will be some negotion for which one is in contol.
//
//  If this is not defined, The included Controller should simply implement the InputController Class...
//==================================================================================================================================
//#define USECOMMANDER
#define USEPS4

// Global defines to control which configuration we are using.  Note: Only define one of these...
// 
// Which type of control(s) do you want to compile in
#if defined(KINETISK)
#define DBGSerial         Serial
#else
#if defined(UBRR2H)
#define DBGSerial         Serial
#endif
#endif 

// Define other optional compnents to be included or not...
//#define PHANTOMX_V2     // Some code may depend on it being a V2 PhantomX
#define cFemurHornOffset1 -35
#define cTibiaHornOffset1 463
#define cRRTibiaInv 0 
#define cRMRTibiaInv 0 
#define cRMFTibiaInv 0 
#define cRFTibiaInv 0 
#define cLRTibiaInv 1 
#define cLMRTibiaInv 1 
#define cLMFTibiaInv 1 
#define cLFTibiaInv 1 

#define cRMRCoxaInv 0
#define cRMFCoxaInv 0
#define cLMRCoxaInv 1 
#define cLMFCoxaInv 1 

#define cRMRFemurInv 1
#define cRMFFemurInv 1
#define cLMRFemurInv 0 
#define cLMFFemurInv 0 


//===================================================================
// Debug Options
#ifdef DBGSerial
#define OPT_TERMINAL_MONITOR  
#define OPT_TERMINAL_MONITOR_IC    // Allow the input controller to define stuff as well
//#define OPT_FIND_SERVO_OFFSETS    // Only useful if terminal monitor is enabled
#endif

//#define DEBUG_IOPINS
#ifdef DEBUG_IOPINS
#define DebugToggle(pin)  {digitalWrite(pin, !digitalRead(pin));}
#define DebugWrite(pin, state) {digitalWrite(pin, state);}
#else
#define DebugToggle(pin)  {;}
#define DebugWrite(pin, state) {;}
#endif


// Also define that we are using the AX12 driver
#define USE_AX12_DRIVER
#define OPT_BACKGROUND_PROCESS    // The AX12 has a background process


//==================================================================================================================================
//==================================================================================================================================
//==================================================================================================================================
//  PhantomX
//==================================================================================================================================
//[SERIAL CONNECTIONS]

//====================================================================
// XBEE on non mega???
#if defined(KINETISK)
#define XBeeSerial Serial2
#else
#if defined(UBRR2H)
#define XBeeSerial Serial2
#endif
#define XBeeSerial Serial
#endif
#define XBEE_BAUD        38400
//--------------------------------------------------------------------
//[Arbotix Pin Numbers]
#if defined(KINETISK)
#define SOUND_PIN    6
#else
#define SOUND_PIN    1 //0xff        // Tell system we have no IO pin...
#define + 0                        // defaults to 13 but Arbotix on 0...
#endif

// Define Analog pin and minimum voltage that we will allow the servos to run
#if defined(KINETISK)
// Our Teensy board
#define cVoltagePin  0
#define CVADR1      402  // VD Resistor 1 - reduced as only need ratio... 40.2K and 10K
#define CVADR2      100    // VD Resistor 2
#define CVREF       330    // 3.3v
#endif
//#define cVoltagePin  7      // Use our Analog pin jumper here...
//#define CVADR1      1000  // VD Resistor 1 - reduced as only need ratio... 20K and 4.66K
//#define CVADR2      233   // VD Resistor 2
#define cTurnOffVol  1000     // 10v
#define cTurnOnVol   1100     // 11V - optional part to say if voltage goes back up, turn it back on...

//====================================================================
#define  DEFAULT_GAIT_SPEED 35  // Default gait speed  - Will depend on what Servos you are using...
#define  DEFAULT_SLOW_GAIT  50  // Had a couple different speeds...

//====================================================================
// Defines for Optional XBee Init and configuration code.
//====================================================================
#define CHECK_AND_CONFIG_XBEE
#define DEFAULT_MY 0x101  // Swap My/DL on 2nd unit
#define DEFAULT_DL 0x102
#define DEFAULT_ID 0x3332

//--------------------------------------------------------------------
// Define which pins(sevo IDS go with which joint

#define cRRCoxaPin      4    //Rear Right leg Hip Horizontal
#define cRRFemurPin     12   //Rear Right leg Hip Vertical
#define cRRTibiaPin     20   //Rear Right leg Knee

#define cRMRCoxaPin      5  //Middle Right leg Hip Horizontal
#define cRMRFemurPin     13  //Middle Right leg Hip Vertical
#define cRMRTibiaPin     21  //Middle Right leg Knee

#define cRMFCoxaPin      6  //Middle Right leg Hip Horizontal
#define cRMFFemurPin     14  //Middle Right leg Hip Vertical
#define cRMFTibiaPin     22  //Middle Right leg Knee

#define cRFCoxaPin      7  //Front Right leg Hip Horizontal
#define cRFFemurPin     15  //Front Right leg Hip Vertical
#define cRFTibiaPin     23   //Front Right leg Knee

#define cLRCoxaPin      3   //Rear Left leg Hip Horizontal
#define cLRFemurPin     11   //Rear Left leg Hip Vertical
#define cLRTibiaPin     19   //Rear Left leg Knee

#define cLMRCoxaPin      2   //Middle Left leg Hip Horizontal
#define cLMRFemurPin     10   //Middle Left leg Hip Vertical
#define cLMRTibiaPin     18  //Middle Left leg Knee

#define cLMFCoxaPin      1   //Middle Left leg Hip Horizontal
#define cLMFFemurPin     9   //Middle Left leg Hip Vertical
#define cLMFTibiaPin     17  //Middle Left leg Knee

#define cLFCoxaPin      0   //Front Left leg Hip Horizontal
#define cLFFemurPin     8   //Front Left leg Hip Vertical
#define cLFTibiaPin     16   //Front Left leg Knee

// #define cTurretRotPin  24   // Turret Rotate Pin
// #define cTurretTiltPin 25  // Turret Tilt pin

//--------------------------------------------------------------------
//[MIN/MAX ANGLES] - Start off assume same as Phoenix...
#define cRRCoxaMin1    -750
#define cRRCoxaMax1    750
#define cRRFemurMin1    -1000
#define cRRFemurMax1    1000
#define cRRTibiaMin1    -1020
#define cRRTibiaMax1    670

#define cRMRCoxaMin1    -750    //Mechanical limits of the Right Middle Rear Leg, decimals = 1
#define cRMRCoxaMax1     750
#define cRMRFemurMin1     -1000
#define cRMRFemurMax1     1000
#define cRMRTibiaMin1    -1020
#define cRMRTibiaMax1     670

#define cRMFCoxaMin1    -750    //Mechanical limits of the Right Middle Front Leg, decimals = 1
#define cRMFCoxaMax1     750
#define cRMFFemurMin1     -1000
#define cRMFFemurMax1     1000
#define cRMFTibiaMin1    -1020
#define cRMFTibiaMax1     670

#define cRFCoxaMin1    -750    //Mechanical limits of the Right Front Leg, decimals = 1
#define cRFCoxaMax1     750
#define cRFFemurMin1    -1000
#define cRFFemurMax1    1000
#define cRFTibiaMin1    -1020
#define cRFTibiaMax1    670

#define cLRCoxaMin1    -750    //Mechanical limits of the Left Rear Leg, decimals = 1
#define cLRCoxaMax1     750
#define cLRFemurMin1     -1000
#define cLRFemurMax1     1000
#define cLRTibiaMin1    -1020
#define cLRTibiaMax1     670

#define cLMRCoxaMin1    -1000    //Mechanical limits of the Left Middle Rear Leg, decimals = 1
#define cLMRCoxaMax1     1000
#define cLMRFemurMin1     -1000
#define cLMRFemurMax1     1000
#define cLMRTibiaMin1    -1020
#define cLMRTibiaMax1     670

#define cLMFCoxaMin1    -1000    //Mechanical limits of the Left Middle Rear Leg, decimals = 1
#define cLMFCoxaMax1     1000
#define cLMFFemurMin1     -1000
#define cLMFFemurMax1     1000
#define cLMFTibiaMin1    -1020
#define cLMFTibiaMax1     670

#define cLFCoxaMin1     -750    //Mechanical limits of the Left Front Leg, decimals = 1
#define cLFCoxaMax1     750
#define cLFFemurMin1     -1000
#define cLFFemurMax1     1000
#define cLFTibiaMin1    -1020
#define cLFTibiaMax1     670

#define cTurretRotMin1  -1500
#define cTurretRotMax1  1500
#define cTurretTiltMin1  -125
#define cTurretTiltMax1  1100

//--------------------------------------------------------------------
//[Joint offsets]
// This allows us to calibrate servos to some fixed position, and then adjust them by moving theim
// one or more servo horn clicks.  This requires us to adjust the value for those servos by 15 degrees
// per click.  This is used with the T-Hex 4DOF legs
//First calibrate the servos in the 0 deg position using the SSC-32 reg offsets, then:
//--------------------------------------------------------------------
//[LEG DIMENSIONS]
//Universal dimensions for each leg in mm
#define cXXCoxaLength     52    // PhantomX leg dimensions.
#define cXXFemurLength    66    // MEASURE THIS!!! Guessed now :-)
#define cXXTibiaLength    133  // MEASURE THIS!!! Guessed now :-)

#define cRRCoxaLength     cXXCoxaLength	    //Right Rear leg
#define cRRFemurLength    cXXFemurLength
#define cRRTibiaLength    cXXTibiaLength


#define cRMRCoxaLength     cXXCoxaLength	    //Right middle rear leg
#define cRMRFemurLength    cXXFemurLength
#define cRMRTibiaLength    cXXTibiaLength


#define cRMFCoxaLength     cXXCoxaLength	    //Right middle front leg
#define cRMFFemurLength    cXXFemurLength
#define cRMFTibiaLength    cXXTibiaLength


#define cRFCoxaLength     cXXCoxaLength	    //Rigth front leg
#define cRFFemurLength    cXXFemurLength
#define cRFTibiaLength    cXXTibiaLength


#define cLRCoxaLength     cXXCoxaLength	    //Left Rear leg
#define cLRFemurLength    cXXFemurLength
#define cLRTibiaLength    cXXTibiaLength


#define cLMRCoxaLength     cXXCoxaLength	    //Left middle rear leg
#define cLMRFemurLength    cXXFemurLength
#define cLMRTibiaLength    cXXTibiaLength


#define cLMFCoxaLength     cXXCoxaLength	    //Left middle front leg
#define cLMFFemurLength    cXXFemurLength
#define cLMFTibiaLength    cXXTibiaLength


#define cLFCoxaLength     cXXCoxaLength	    //Left front leg
#define cLFFemurLength    cXXFemurLength
#define cLFTibiaLength    cXXTibiaLength



//--------------------------------------------------------------------
//[BODY DIMENSIONS]
#define cRRCoxaAngle1   -450     //Default Coxa setup angle, decimals = 1
#define cRMRCoxaAngle1    0      //Default Coxa setup angle, decimals = 1
#define cRMFCoxaAngle1    0      //Default Coxa setup angle, decimals = 1
#define cRFCoxaAngle1    450     //Default Coxa setup angle, decimals = 1
#define cLRCoxaAngle1    -450    //Default Coxa setup angle, decimals = 1
#define cLMRCoxaAngle1    0      //Default Coxa setup angle, decimals = 1
#define cLMFCoxaAngle1    0      //Default Coxa setup angle, decimals = 1
#define cLFCoxaAngle1    450     //Default Coxa setup angle, decimals = 1

#define X_COXA      180   // MM between front and back legs /2
#define Y_COXA      180   // MM between front/back legs /2
#define M_COXA      100   // MM between two middle legs /2

#define cRROffsetX        -60    //Distance X from center of the body to the Right Rear coxa
#define cRROffsetZ        180    //Distance Z from center of the body to the Right Rear coxa

#define cRMROffsetX      -100    //Distance X from center of the body to the Right Middle Rear coxa
#define cRMROffsetZ       -60    //Distance Z from center of the body to the Right Middle Rear coxa

#define cRMFOffsetX      -100    //Distance X from center of the body to the Right Middle Front coxa
#define cRMFOffsetZ       -60    //Distance Z from center of the body to the Right Middle Front coxa

#define cRFOffsetX        -60    //Distance X from center of the body to the Right Front coxa
#define cRFOffsetZ       -180    //Distance Z from center of the body to the Right Front coxa

#define cLROffsetX         60    //Distance X from center of the body to the Left Rear coxa
#define cLROffsetZ        180    //Distance Z from center of the body to the Left Rear coxa

#define cLMROffsetX      100     //Distance X from center of the body to the Left Middle Rear coxa
#define cLMROffsetZ       60     //Distance Z from center of the body to the Left Middle Rear coxa

#define cLMFOffsetX      100     //Distance X from center of the body to the Left Middle Front coxa
#define cLMFOffsetZ      -60     //Distance Z from center of the body to the Left Middle Front coxa

#define cLFOffsetX        60     //Distance X from center of the body to the Left Front coxa
#define cLFOffsetZ      -180     //Distance Z from center of the body to the Left Front coxa

//--------------------------------------------------------------------
//[START POSITIONS FEET]
#define cHexInitXZ	 147
#define CHexInitXZCos60  104        // COS(45) = .707
#define CHexInitXZSin60  104    // sin(45) = .707
#define CHexInitY	 25 //30

// Lets try some multi leg positions depending on height settings.
#define CNT_HEX_INITS 2
#define MAX_BODY_Y  150
#ifdef DEFINE_HEX_GLOBALS
const byte g_abHexIntXZ[] = {cHexInitXZ, 144};
const byte g_abHexMaxBodyY[] = { 20, MAX_BODY_Y};
#else
extern const byte g_abHexIntXZ[];
extern const byte g_abHexMaxBodyY[];
#endif

#define cRRInitPosX     CHexInitXZCos60      //Start positions of the Right Rear leg
#define cRRInitPosY     CHexInitY
#define cRRInitPosZ     CHexInitXZSin60

#define cRMRInitPosX     cHexInitXZ      //Start positions of the Right Middle Rear leg
#define cRMRInitPosY     CHexInitY
#define cRMRInitPosZ     0

#define cRMFInitPosX     cHexInitXZ      //Start positions of the Right Middle Front leg
#define cRMFInitPosY     CHexInitY
#define cRMFInitPosZ     0

#define cRFInitPosX     CHexInitXZCos60      //Start positions of the Right Front leg
#define cRFInitPosY     CHexInitY
#define cRFInitPosZ     -CHexInitXZSin60

#define cLRInitPosX     CHexInitXZCos60      //Start positions of the Left Rear leg
#define cLRInitPosY     CHexInitY
#define cLRInitPosZ     CHexInitXZSin60

#define cLMRInitPosX     cHexInitXZ      //Start positions of the Left Middle Rear leg
#define cLMRInitPosY     CHexInitY
#define cLMRInitPosZ     0

#define cLMFInitPosX     cHexInitXZ      //Start positions of the Left Middle Rear leg
#define cLMFInitPosY     CHexInitY
#define cLMFInitPosZ     0

#define cLFInitPosX     CHexInitXZCos60      //Start positions of the Left Front leg
#define cLFInitPosY     CHexInitY
#define cLFInitPosZ     -CHexInitXZSin60

// Turret initial position
#define cTurretRotInit  0
#define cTurretTiltInit 0


//--------------------------------------------------------------------
//[Tars factors used in formula to calc Tarsus angle relative to the ground]
#define cTarsst	720	//4DOF ONLY
#define cTarsMulti	2	//4DOF ONLY
#define cTarsFactorA	70	//4DOF ONLY
#define cTarsFactorB	60	//4DOF ONLY
#define cTarsFactorC	50	//4DOF ONLY

#define cRMRTarsInv 1 
#define cRMFTarsInv 1 
#define cLMRTarsInv 0 
#define cLMFTarsInv 0 

#endif // OCTO_CFG_H

