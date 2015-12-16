#include <Keyboard.h>
#include <PS2X_lib.h>

// This example has been created to work with the $5 (on ebay) "Leonardo Pro Micro ATmega32U4 16MHz 5V" 
// see wireing.png and the DDRPadWiringLeonardoProMicro.jpg for wireing directly.
// see DDRPadTested.jpg for the tested working pad
// This example also has full PCXS2 mappings
// We use Digihaven's fork for ps2x.set_RetryCntMax(1) since ddrpads have way too much retry delay

PS2X ps2x; // create PS2 Controller Class

int error = 0; 
byte type = 0;

bool keys[255];

void setup(){
 Serial.begin(57600);
  
 error = ps2x.config_gamepad(15,16,14,10, true, true);   //setup pins and settings:  GamePad(clock, command, attention, data, Pressures?, Rumble?) check for error
 ps2x.set_RetryCntMax(1);
  
 if(error == 0){
   Serial.println("Found Controller, configured successful");
 }
   
  else if(error == 1)
   Serial.println("No controller found, check wiring, see readme.txt to enable debug. visit www.billporter.info for troubleshooting tips");
   
  else if(error == 2)
   Serial.println("Controller found but not accepting commands. see readme.txt to enable debug. Visit www.billporter.info for troubleshooting tips");
   
  else if(error == 3)
   Serial.println("Controller refusing to enter Pressures mode, may not support it. ");
   
   type = ps2x.readType(); 
     switch(type) {
       case 0:
        Serial.println("Unknown Controller type");
       break;
       case 1:
        Serial.println("DualShock Controller Found");
       break;
       case 2:
         Serial.println("GuitarHero Controller Found");
       break;
     }
  Keyboard.begin();

  for(int x=0;x<sizeof(keys);x++)
    keys[x]=0;
}

void mapkey(uint16_t padbutton,char key)
{
  bool val=ps2x.Button(padbutton);

  if (keys[key]!=val)
  {
    if (val) {
        // Serial.println("press");
        Keyboard.press(key); 
    } else {
       //  Serial.println("release");
        Keyboard.release(key); 
    }

    keys[key]=val;
  }
  
}

void loop()
{
   
 if(error == 1) //skip loop if no controller found
  return; 
  ps2x.read_gamepad(false, 0);          //read controller and set large motor to spin at 'vibrate' speed

  mapkey(PSB_R2,';');
  mapkey(PSB_L2,'a');
  mapkey(PSB_PAD_DOWN,'d');
  mapkey(PSB_PAD_UP,'e');
  mapkey(PSB_PAD_RIGHT,'f');
  mapkey(PSB_TRIANGLE,'i');
  mapkey(PSB_SQUARE,'j');
  mapkey(PSB_CROSS,'k');
  mapkey(PSB_CIRCLE,'l');
  mapkey(PSB_START,'n');
  mapkey(PSB_R1,'p');
  mapkey(PSB_PAD_LEFT,'s');
  mapkey(PSB_SELECT,'v');
  mapkey(PSB_L1,'w');

  delay(10);
     
}