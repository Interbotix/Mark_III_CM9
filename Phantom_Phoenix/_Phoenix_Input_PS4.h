#define DEBUG_CONTROLLER
#ifdef USEPS4
//====================================================================
//Project Lynxmotion Phoenix
//Description: Phoenix, control file.
//The control input subroutine for the phoenix software is placed in this file.
//Can be used with V2.0 and above
//Configuration version: V1.0
//Date: 25-10-2009 (PS4 update: 28-12-2020)
//Programmer: Jeroen Janssen (aka Xan)
//             Kurt Eckhardt (aka KurtE) - converted to c ported to Arduino...
//              Levi Todes (aka LeTo37) - only the PS4 stuff 
//
//Hardware setup: PS4 version
//                PS4 remote connected via bluetooth to Esp32
//                Esp32 connected to OpenCM9.04 board via UART
//                      - as such Serial2 used for PS4 comms
// 
//NEW IN V1.0
//- First Release
//
//Walk method 1:
//- Left Stick                  -> Walk/Strafe
//- Right Stick                 -> Rotate
//
//Walk method 2:
//- Left Stick                  -> Disable
//- Right Stick                 -> Walk/Rotate
//
//
//PS4 CONTROLS:
//[Common Controls]
//- OPTIONS                     -> Turn on/off the bot
//- L1                          -> Toggle Shift mode
//- L2                          -> Toggle Rotate mode
//- Circle                      -> Toggle Single leg mode
//- Square                      -> Toggle Balance mode
//- Triangle                    -> Stand up and sit down - Move body to 35 mm from the ground (walk pos) and back to the ground
//- Digital UP                  -> Body up 10 mm
//- Digital DOWN                -> Body down 10 mm
//- Digital LEFT                -> Decrease speed by 50mS
//- Digital RIGHT               -> Increase speed by 50mS
//
// Optional: L3 button down, Left stick can adjust leg positions...
// or if OPT_SINGLELEG is not defined may try using Circle

//
//
//[Walk Controls]
//- SHARE                       -> Switch gaits
//- Left Stick(Walk mode 1)     -> Walk/Strafe
//- Left Stick(Walk mode 2)     -> Disable
//- Right Stick(Walk mode 1)    -> Rotate 
//- Right Stick(Walk mode 2)    -> Walk/Rotate
//- R1                          -> Toggle Double gait travel speed
//- R2                          -> Toggle Double gait travel length
//
//[Shift Controls]
//- Left Stick                  -> Shift body X/Z
//- Right Stick                 -> Shift body Y and rotate body Y
//
//[Rotate Controls]
//- Left Stick                  -> Rotate body X/Z
//- Right Stick                 -> Rotate body Y
//
//[Single leg Controls]
//- SHARE                       -> Switch legs
//- Left Stick                  -> Move Leg X/Z (relative)
//- Right Stick                 -> Move Leg Y (absolute)
//- R2                          -> Hold/release leg position
//
//[GP Player Controls]
//- SHARE                      -> Switch Sequences
//- R2                          -> Start Sequence
//
//====================================================================
// [Include files]
#if ARDUINO>99
#include <Arduino.h> // Arduino 1.0
#else
#include <Wprogram.h> // Arduino 0022
#endif
//[CONSTANTS]
enum {
    WALKMODE = 0, TRANSLATEMODE, ROTATEMODE, SINGLELEGMODE,
    MODECNT
};
enum {
    NORM_NORM = 0, NORM_LONG, HIGH_NORM, HIGH_LONG
};


#define cTravelDeadZone 6      //The deadzone for the analog input from the remote

#define PS4_TO  150000        // if we don't get a valid message in this number of mills turn off About 2.5 minutes. 

#ifndef USER
#define USER 13
#endif

#ifndef MAX_BODY_Y
#define MAX_BODY_Y 100
#endif

//=============================================================================
// Global - Local to this file only...
//=============================================================================
#include "PS4_Input.h"
PS4_Input ps4; // create PS4 Controller Class

unsigned long g_ulLastMsgTime;
short  g_sGPSMController;    // What GPSM value have we calculated. 0xff - Not used yet
boolean g_fDynamicLegXZLength = false;  // Has the user dynamically adjusted the Leg XZ init pos (width)
#define PS4InputController InputController

// Define an instance of the Input Controller...
InputController  g_InputController;       // Our Input controller 


static short   g_BodyYOffset;
static short   g_BodyYShift;
static byte    ControlMode;
static byte    HeightSpeedMode;
static bool  DoubleHeightOn;
static bool    DoubleTravelOn;
static byte    bJoystickWalkMode;
static bool    WalkMethod;

static byte    buttonsPrev;
static byte    extPrev;

// some external or forward function references.
extern void PS4TurnRobotOff(void);

//==============================================================================
// This is The function that is called by the Main program to initialize
//the input controller, which in this case is the PS4 controller
//process any commands.
//==============================================================================

// If both PS4 and XBee are defined then we will become secondary to the xbee
void PS4InputController::Init(void)
{
    g_BodyYOffset = 0;
    g_BodyYShift = 0;
#ifdef DBGSerial
    DBGSerial.print("PS4 Init!\n");
#endif
    ps4.Start_Serial();

    ControlMode = WALKMODE;
    HeightSpeedMode = NORM_NORM;
    DoubleHeightOn = false;
    DoubleTravelOn = false;
    bJoystickWalkMode = 0;
    WalkMethod = false;

}

//==============================================================================
// This function is called by the main code to tell us when it is about to
// do a lot of bit-bang outputs and it would like us to minimize any interrupts
// that we do while it is active...
//==============================================================================
void PS4InputController::AllowControllerInterrupts(boolean fAllow __attribute__((unused)))
{
    // We don't need to do anything...
}

//==============================================================================
// This is The main code to input function to read inputs from the PS4 and then
//process any commands.
//==============================================================================
#ifdef OPT_DYNAMIC_ADJUST_LEGS  
boolean g_fDynamicLegXZLength = false;  // Has the user dynamically adjusted the Leg XZ init pos (width)
#endif

void PS4InputController::ControlInput(void)
{
    boolean fAdjustLegPositions = false;
    short sLegInitXZAdjust;
    short sLegInitAngleAdjust;
    ps4.Get_Input(); // Checks for valid message being received and if so, populates PS4 Class members.
    
    // If user hits the OPTIONS button - turns robot on and off 
    if(!g_InControlState.fRobotOn){
        if (!ps4.options) {
            DBGSerial.println("Please Turn on Robot with PS4 Options button");
        }
        else {
            DBGSerial.println("Robot is on");
            g_InControlState.fRobotOn = true;
            ps4.Reset_Bools();
        }
    }
    
    if (g_InControlState.fRobotOn) {
        sLegInitXZAdjust = 0;
        sLegInitAngleAdjust = 0;
        fAdjustLegPositions = true;

        //DBGSerial.println((String)ps4.Print_Out());

        // [SWITCH MODES]

        // Cycle through modes...
        if (ps4.l1) {   // L1 Button
            MSound(1, 50, 2000);
            if (ControlMode != TRANSLATEMODE)
                ControlMode = TRANSLATEMODE;
            else {
#ifdef OPT_SINGLELEG
                if (g_InControlState.SelectedLeg == 255)
                    ControlMode = WALKMODE;
                else
#endif
                    ControlMode = SINGLELEGMODE;
            }
        }

        //Rotate mode
        if (ps4.l2) {    // L2 Button
            MSound(1, 50, 2000);
            if (ControlMode != ROTATEMODE)
                ControlMode = ROTATEMODE;
            else {
#ifdef OPT_SINGLELEG
                if (g_InControlState.SelectedLeg == 255)
                    ControlMode = WALKMODE;
                else
#endif
                    ControlMode = SINGLELEGMODE;
            }
        }

        //Single leg mode fNO
#ifdef OPT_SINGLELEG
        if (ps4.circle) {// CIRCLE Button
            if (abs(g_InControlState.TravelLength.x) < cTravelDeadZone && abs(g_InControlState.TravelLength.z) < cTravelDeadZone
                && abs(g_InControlState.TravelLength.y * 2) < cTravelDeadZone) {
                if (ControlMode != SINGLELEGMODE) {
                    ControlMode = SINGLELEGMODE;
                    if (g_InControlState.SelectedLeg == 255)  //Select leg if none is selected
                        g_InControlState.SelectedLeg = cRF; //Startleg
                }
                else {
                    ControlMode = WALKMODE;
                    g_InControlState.SelectedLeg = 255;
                }
            }
        }
#endif
#ifdef OPT_GPPLAYER
        // GP Player Mode X
        if (ps4.x) { // X Button
            MSound(1, 50, 2000);
            if (ControlMode != GPPLAYERMODE) {
                ControlMode = GPPLAYERMODE;
                GPSeq = 0;
            }
            else
                ControlMode = WALKMODE;
        }
#endif // OPT_GPPLAYER

        //All Modes input control:
        //Switch Balance mode on/off
        if (ps4.square) { // SQUARE Button
            g_InControlState.BalanceMode = !g_InControlState.BalanceMode;
            if (g_InControlState.BalanceMode) {
                DBGSerial.println("Balance mode off");
                MSound(1, 250, 1500);
            }
            else {
                DBGSerial.println("Balance mode on");
                MSound(2, 100, 2000, 50, 4000);
            }
        }

        //Stand up, sit down
        if (ps4.triangle) { //TRIANGLE Button
            if (g_BodyYOffset > 0) {
                DBGSerial.println("Robot Sit");
                g_BodyYOffset = 0;
            }
            else {
                DBGSerial.println("Robot Stand");
                g_BodyYOffset = 35;
            }
            fAdjustLegPositions = true;
            g_fDynamicLegXZLength = false;
        }

        if (ps4.up) {// Digital UP
            g_BodyYOffset += 10;
            DBGSerial.println("Lift Robot 10");
            // And see if the legs should adjust...
            fAdjustLegPositions = true;
            if (g_BodyYOffset > MAX_BODY_Y)
                g_BodyYOffset = MAX_BODY_Y;
        }

        if (ps4.down && g_BodyYOffset) {// Digital DOWN
            if (g_BodyYOffset > 10) {
                DBGSerial.println("Lower Robot 10");
                g_BodyYOffset -= 10;
            }
            else {
                DBGSerial.println("Robot Height at 0");
                g_BodyYOffset = 0;      // constrain to not go less than zero.
            }
            // And see if the legs should adjust...
            fAdjustLegPositions = true;
        }

        if (ps4.right) { // Digital RIGHT
            if (g_InControlState.SpeedControl > 0) {
                DBGSerial.println("Robot Speed + 50");
                g_InControlState.SpeedControl = g_InControlState.SpeedControl - 50;
                MSound(1, 50, 2000);
            }
        }

        if (ps4.left) { // Digital LEFT
            if (g_InControlState.SpeedControl < 2000) {
                DBGSerial.println("Robot Speed - 50");
                g_InControlState.SpeedControl = g_InControlState.SpeedControl + 50;
                MSound(1, 50, 2000);
            }
        }

        int lx = ps4.leftH;
        int ly = ps4.leftV;

#ifdef OPT_DYNAMIC_ADJUST_LEGS  
#ifdef OPT_SINGLELEG
        if (ps4.l3) {    // L3 pressed, use this to modify leg positions.
#else
        if (ps4.circle) {// O - Circle Button Test 
#endif      
            sLegInitXZAdjust = (lx) / 10;        // play with this.
            sLegInitAngleAdjust = (ly) / 8;
            lx = 0;
            ly = 0;
        }
#endif

        if (ControlMode == WALKMODE) {
            //Switch gates
            if (ps4.share            // SHARE Button
                && abs(g_InControlState.TravelLength.x) < cTravelDeadZone //No movement
                && abs(g_InControlState.TravelLength.z) < cTravelDeadZone
                && abs(g_InControlState.TravelLength.y * 2) < cTravelDeadZone) {
                g_InControlState.GaitType = g_InControlState.GaitType + 1;                    // Go to the next gait...
                if (g_InControlState.GaitType < NUM_GAITS) {                 // Make sure we did not exceed number of gaits...
                    MSound(1, 50, 2000);
                }
                else {
                    MSound(2, 50, 2000, 50, 2250);
                    g_InControlState.GaitType = 0;
                }
                GaitSelect();
            }

            //Double leg lift height
            if (ps4.r1) { // R1 Button
                MSound(1, 50, 2000);
                DoubleHeightOn = !DoubleHeightOn;
                if (DoubleHeightOn)
                    g_InControlState.LegLiftHeight = 80;
                else
                    g_InControlState.LegLiftHeight = 50;
            }

            //Double Travel Length
            if (ps4.r2) {// R2 Button
                MSound(1, 50, 2000);
                DoubleTravelOn = !DoubleTravelOn;
            }

            // Switch between Walk method 1 && Walk method 2
            if (ps4.r3) { // R3 Button
                MSound(1, 50, 2000);
                WalkMethod = !WalkMethod;
            }

            //Walking
            if (WalkMethod) {  //(Walk Methode) 
                g_InControlState.TravelLength.z = (ps4.rightV); //Right Stick Up/Down  
            }
            else {
                g_InControlState.TravelLength.x = -(lx);
                g_InControlState.TravelLength.z = (ly);
            }

            if (!DoubleTravelOn) {  //(Double travel length)
                g_InControlState.TravelLength.x = g_InControlState.TravelLength.x / 2;
                g_InControlState.TravelLength.z = g_InControlState.TravelLength.z / 2;
            }

            g_InControlState.TravelLength.y = -(ps4.rightH) / 4; //Right Stick Left/Right 
        }

        //[Translate functions]
        g_BodyYShift = 0;
        if (ControlMode == TRANSLATEMODE) {
            g_InControlState.BodyPos.x = (lx) / 2;
            g_InControlState.BodyPos.z = -(ly) / 3;
            g_InControlState.BodyRot1.y = (ps4.rightH) * 2;
            g_BodyYShift = (-(ps4.rightV) / 2);
        }

        //[Rotate functions]
        if (ControlMode == ROTATEMODE) {
            g_InControlState.BodyRot1.x = (ly);
            g_InControlState.BodyRot1.y = (ps4.rightH) * 2;
            g_InControlState.BodyRot1.z = (lx);
            g_BodyYShift = (-(ps4.rightV) / 2);
        }

        //[Single leg functions]
#ifdef OPT_SINGLELEG
        if (ControlMode == SINGLELEGMODE) {
            //Switch leg for single leg control
            if (ps4.share) { // Select Button Test
                MSound(1, 50, 2000);
                if (g_InControlState.SelectedLeg < (CNT_LEGS - 1))
                    g_InControlState.SelectedLeg = g_InControlState.SelectedLeg + 1;
                else
                    g_InControlState.SelectedLeg = 0;
            }

            g_InControlState.SLLeg.x = (lx) / 2; //Left Stick Right/Left
            g_InControlState.SLLeg.y = (ps4.rightV) / 10; //Right Stick Up/Down
            g_InControlState.SLLeg.z = (ly) / 2; //Left Stick Up/Down

            // Hold single leg in place
            if (ps4.r2) { // R2 Button
                MSound(1, 50, 2000);
                g_InControlState.fSLHold = !g_InControlState.fSLHold;
            }
        }
#endif
#ifdef OPT_GPPLAYER
        //[GPPlayer functions]
        if (ControlMode == GPPLAYERMODE) {

            // Lets try some speed control... Map all values if we have mapped some before
            // or start mapping if we exceed some minimum delta from center
            // Have to keep reminding myself that commander library already subtracted 128...
            if (g_ServoDriver.FIsGPSeqActive()) {
                if ((g_sGPSMController != 32767)
                    || (ps4.rightV > 16) || (ps4.rightH < 16))
                {
                    // We are in speed modify mode...
                    short sNewGPSM = map(ps4.rightV, -127, 128, -200, 200);
                    if (sNewGPSM != g_sGPSMController) {
                        g_sGPSMController = sNewGPSM;
                        g_ServoDriver.GPSetSpeedMultiplyer(g_sGPSMController);
                    }

                }
            }

            //Switch between sequences
            if (ps4.share) { // Share Button
                if (!g_ServoDriver.FIsGPSeqActive()) {
                    if (GPSeq < 5) {  //Max sequence
                        MSound(1, 50, 1500);
                        GPSeq = GPSeq + 1;
                    }
                    else {
                        MSound(2, 50, 2000, 50, 2250);
                        GPSeq = 0;
                    }
                }
            }
            //Start Sequence
            if (ps4.r2)// R2 Button
                if (!g_ServoDriver.FIsGPSeqActive()) {
                    g_ServoDriver.GPStartSeq(GPSeq);
                    g_sGPSMController = 32767;  // Say that we are not in Speed modify mode yet... valid ranges are 50-200 (both postive and negative... 
                }
                else {
                    g_ServoDriver.GPStartSeq(0xff);    // tell the GP system to abort if possible...
                    MSound(2, 50, 2000, 50, 2000);
                }


        }
#endif // OPT_GPPLAYER

        //Calculate walking time delay
        g_InControlState.InputTimeDelay = 128 - max(max(abs(lx), abs(ly)), abs(ps4.rightH));

        //Calculate g_InControlState.BodyPos.y
        g_InControlState.BodyPos.y = min(max(g_BodyYOffset + g_BodyYShift, 0), MAX_BODY_Y);

#ifdef OPT_DYNAMIC_ADJUST_LEGS  
        if (sLegInitXZAdjust || sLegInitAngleAdjust) {
            // User asked for manual leg adjustment - only do when we have finished any previous adjustment

            if (!g_InControlState.ForceGaitStepCnt) {
                if (sLegInitXZAdjust)
                    g_fDynamicLegXZLength = true;

                sLegInitXZAdjust += GetLegsXZLength();  // Add on current length to our adjustment...
                // Handle maybe change angles...
                if (sLegInitAngleAdjust)
                    RotateLegInitAngles(sLegInitAngleAdjust);
                // Give system time to process previous calls
                AdjustLegPositions(sLegInitXZAdjust);
            }
        }
#endif

        if (fAdjustLegPositions){
            AdjustLegPositionsToBodyHeight();    // Put main workings into main program file
        }

        g_ulLastMsgTime = millis();
    
        if (((millis() - g_ulLastMsgTime) > PS4_TO) || ps4.options){
            PS4TurnRobotOff();
        }
        ps4.Reset_Bools();
    }
    
}
//==============================================================================
// PS4TurnRobotOff - code used couple of places so save a little room...
//==============================================================================
void PS4TurnRobotOff(void){
    //Turn off
    g_InControlState.BodyPos.x = 0;
    g_InControlState.BodyPos.y = 0;
    g_InControlState.BodyPos.z = 0;
    g_InControlState.BodyRot1.x = 0;
    g_InControlState.BodyRot1.y = 0;
    g_InControlState.BodyRot1.z = 0;
    g_InControlState.TravelLength.x = 0;
    g_InControlState.TravelLength.z = 0;
    g_InControlState.TravelLength.y = 0;
    g_BodyYOffset = 0;
    g_BodyYShift = 0;
    g_InControlState.fRobotOn = false;

#ifdef cTurretRotPin
    g_InControlState.TurretRotAngle1 = cTurretRotInit;      // Rotation of turrent in 10ths of degree
    g_InControlState.TurretTiltAngle1 = cTurretTiltInit;    // the tile for the turret
#endif

    g_fDynamicLegXZLength = false; // also make sure the robot is back in normal leg init mode...
    DBGSerial.println("Robot is off");
}

//==============================================================================
//==============================================================================
#endif // USEPS4