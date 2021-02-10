#include <PS4Controller.h>
#include <WiFi.h>

// MACROS
char MAC[18];
#define RXD2 16
#define TXD2 17

//Bools used to ensure only one instance of each digital button press is sent and registered on the OpenCM9 side.
bool opt_prev = 0;
bool ps_prev = 0;
bool share_prev = 0;
bool touch_prev = 0;
bool tri_prev = 0;
bool square_prev = 0;
bool circle_prev = 0;
bool x_prev = 0;
bool down_prev = 0;
bool up_prev = 0;
bool right_prev = 0;
bool left_prev = 0;
bool l1_prev = 0;
bool l2_prev = 0;
bool l3_prev = 0;
bool r1_prev = 0;
bool r2_prev = 0;
bool r3_prev = 0;

void setup()
{
  //Setup for communication with the OpenCM9 via Serial port "Serial2"
  //Debugging output to Serial port "Serial" has been commented out.
    Serial2.begin(115200, SERIAL_8N1, RXD2, TXD2);
//    Serial.begin(9600);
//    Serial.print("ESP Board MAC Address:  ");
    WiFi.macAddress().toCharArray(MAC,18);
//    Serial.println(MAC);
    PS4.begin(MAC);
//    Serial.println("Ready.");
}

void loop()
{
/* At this point, the Esp32 is ready and waiting for the PS4 remote to connect, it will connect automatically once the PS4 remote is turned on using the PS4 button
      There are some buttons/events available in the "PS4Controller.h" library that are unused in this case*/
    if(PS4.isConnected()) {
      //Once the PS4 remote is connected, the inputs are ready to be processed and sent to the OpenCm9
      if ( PS4.data.button.up ){
          if(!up_prev){
            Serial2.print("UP\n");
            up_prev = 1;
          }
      }else{
        up_prev = 0;
      }
      
      if ( PS4.data.button.down ){
        if (!down_prev){
          Serial2.print("DOWN\n");
          down_prev = 1;
        }
      }else{
        down_prev = 0;
      }
      
      if ( PS4.data.button.left ){
        if (!left_prev){
          Serial2.print("LEFT\n");
          left_prev = 1;
        }
      }else{
        left_prev = 0;
      }
      
      if ( PS4.data.button.right ){
          if(!right_prev){
            Serial2.print("RIGHT\n");
            right_prev = 1;
          }
      }else{
        right_prev = 0; 
      }
        
      if ( PS4.data.button.triangle ){
        if(!tri_prev){
          Serial2.print("TRIANGLE\n");
          tri_prev = 1;
        }
      }else{
        tri_prev = 0;
      }
      
      if ( PS4.data.button.circle ){
          if(!circle_prev){
            Serial2.print("CIRCLE\n");
            circle_prev = 1;
          }
      }else{
        circle_prev = 0;
      }
      
      if ( PS4.data.button.cross ){
        if(!x_prev){
          Serial2.print("X\n");
          x_prev = 1;
        }
      }else{
        x_prev = 0;
      }
      
      if ( PS4.data.button.square ){
        if(!square_prev){
          Serial2.print("SQUARE\n");
          square_prev = 1;
        }
      }else{
        square_prev = 0;  
      }      
        
      if ( PS4.data.button.l1 ){
        if(!l1_prev){
          Serial2.print("L1\n");
          l1_prev = 1;
        }
      }else{
        l1_prev = 0;
      }
      
      if ( PS4.data.button.r1 ){
        if(!r1_prev){
          Serial2.print("R1\n");
          r1_prev = 1;
        }
      }else{
        r1_prev = 0;
      }
        
      if ( PS4.data.button.l3 ){
        if(!l3_prev){
          Serial2.print("L3\n");
          l3_prev = 1;
        }
      }else{
        l3_prev = 0;
      }
      
      if ( PS4.data.button.r3 ){
        if(!r3_prev){
          Serial2.print("R3\n");
          r3_prev = 1;
        }
      }else{
        r3_prev = 0;
      }
        
      if ( PS4.data.button.share ){
        if(!share_prev){
          Serial2.print("SHARE\n");
          share_prev = 1;
        }
      }else{
        share_prev = 0;
      }
      
      if ( PS4.data.button.options ){
        if(!opt_prev){
          Serial2.print("OPTIONS\n");
          opt_prev = 1;
        }
      }else{
        opt_prev = 0;
      }
        
      if ( PS4.data.button.ps ){
        if(!ps_prev){
          Serial2.print("PS\n");
          ps_prev = 1;
        }
      }else{
        ps_prev = 0;
      }
      
      if ( PS4.data.button.touchpad ){
        if (!touch_prev){
          Serial2.print("TOUCH_PAD\n");
          touch_prev = 1;
        }
      }else{
        touch_prev = 0;
      }
        
      if ( PS4.data.button.l2 ) {
        if (!l2_prev){
          Serial2.print("L2: ");
          Serial2.print(PS4.data.analog.button.l2, DEC);
          Serial2.print("\n");
          l2_prev = 1;
        }
      }else{
        l2_prev = 0;
      }
      
      if ( PS4.data.button.r2 ) {
        if(!r2_prev){
          Serial2.print("R2: ");
          Serial2.print(PS4.data.analog.button.r2, DEC);
          Serial2.print("\n");
          r2_prev = 1;
        }
      }else{
        r2_prev = 0;
      }

      if ( PS4.event.analog_move.stick.lx || PS4.event.analog_move.stick.ly || PS4.event.analog_move.stick.rx || PS4.event.analog_move.stick.ry ) {
            Serial2.print("Analogues:");
            Serial2.print(" L_hor: ");
            Serial2.print(PS4.data.analog.stick.lx, DEC);
            Serial2.print(";");
            
            Serial2.print(" L_ver: ");
            Serial2.print(PS4.data.analog.stick.ly, DEC);
            Serial2.print(";");
        
            Serial2.print(" R_hor: ");
            Serial2.print(PS4.data.analog.stick.rx, DEC);
            Serial2.print(";");
           
            Serial2.print(" R_ver: ");
            Serial2.print(PS4.data.analog.stick.ry, DEC);
            Serial2.print(";");
            Serial2.print("\n");
     }
     // This delay is used to ensure smooth operation on the OpenCM9 side, removing it will make the OpenCm9 continuosly process Serial input and therefore move the hexapod in a stop-start fashion.
     delay(100);
    }
}
