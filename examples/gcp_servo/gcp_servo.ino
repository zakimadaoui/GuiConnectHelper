#include"GuiConnectHelper.h"
#include"string.h"
#include"Servo.h"

GuiConnectHelper gcHandle;
Servo servo[3];

void onCommandRecieved(); //callback

void setup(){
  //init and register callback
	GCH_init(&gcHandle, onCommandRecieved);

  //attach the servos
	servo[0].attach(5);
  servo[1].attach(6);
  servo[2].attach(7);

  Serial.begin(9600);
	Serial.println("hello world");
	// some bluetooth modules need to recieve data at first to start
	// working properly. so we send a "hello world" message.
	// you'll need to reset the board after BT connection for this message to be sent
}

void loop(){
	//load any newly available data
	while(Serial.available()) GCH_loadNextbyte(&gcHandle, Serial.read());
}

void onCommandRecieved(){
	// this is a callback that triggers whenever a command is fully recived
	// and parsed. You can use the gcHandle object to retrieve the command_name
	// and parameters

 
	char cmdName = GCH_GetCharCommandName(&gcHandle); 
  
	if(cmdName == 'k'){ // a knob is rotated
    int servoIndex = GCH_GetParamAsInt(&gcHandle, 0); //get parameter 0 as an integer value
    int angle = GCH_GetParamAsInt(&gcHandle, 1); //get parameter 1 as an integer value
    servo[servoIndex].write(angle);
	}

  //NOTES:
  // - avoid blocking calls like 'delay()' inside this callback
	// - do not call free() on cmdName or anything library related, the library takes care of that.
	// - command name and parameters must only be accessed within this callback
  //   trying to access them outside of it will lead undesired behaviour
}
