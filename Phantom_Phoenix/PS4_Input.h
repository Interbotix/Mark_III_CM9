#ifndef PS4_INPUT
#define PS4_INPUT

#include "Arduino.h"

class PS4_Input {
  private:
    String message;
    
 
  public:
    //Constructor
    PS4_Input();
    //Buttons
      //Analog
    int rightV;
    int rightH;
    int leftV;
    int leftH;
      //Digital
    bool ps;
    bool share;
    bool options;
    bool triangle;
    bool square;
    bool circle;
    bool x;
    bool up;
    bool down;
    bool left;
    bool right;
    bool l1;
    bool l2;
    bool l3;
    bool r1;
    bool r2;
    bool r3;

    //Functions
    void Start_Serial();
    int Get_Input();
    void Reset_Bools();
    void Reset_Analogues();
    String Print_Out();
};

#endif
