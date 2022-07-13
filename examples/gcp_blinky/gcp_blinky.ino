#include"GuiConnectHelper.h"
#include"string.h"

GuiConnectHelper gcHandle;
int switchVal = 1; //switch value for enabling/disabling blinking
int sliderVal = 1000; //slider value holds blinking delay
long prev = 0;
long time_diff;

void onCommandRecieved(); //callback

void setup(){
  //init and register callback
	GCH_init(&gcHandle, onCommandRecieved);
  
	pinMode(13, OUTPUT);
	Serial.begin(9600);


	Serial.println("hello world");
	// some bluetooth modules need to recieve data at first to start
	// working properly. so we send a "hello world" message.
	// you'll need to reset the board after BT connection for this message to be sent
	
	prev = millis();
}

void loop(){
	//load any newly available data
	while(Serial.available()) GCH_loadNextbyte(&gcHandle, Serial.read());

	//blink (non-blocking)
	if(switchVal){
	 
	  time_diff = millis() - prev;

		if( time_diff <= sliderVal)
			digitalWrite(13, HIGH);
		else if(time_diff > sliderVal && time_diff <= 2*sliderVal)
			digitalWrite(13, LOW);
		else
			prev = millis();
	}
	else{
		digitalWrite(13, LOW); //turn off blinking
	}
}

void onCommandRecieved(){
	// this is a callback that triggers whenever a command is fully recived
	// and parsed. You can use the gcHandle object to retrieve the command_name
	// and parameters
	char* cmdName =  GCH_GetStrCommandName(&gcHandle);
	if(strcmp(cmdName, "switch") == 0){
		switchVal = GCH_GetParamAsInt(&gcHandle,/*param index*/0); //get parameter 0 as an integer value
	}
  else if(strcmp(cmdName, "slider") == 0){
		sliderVal = GCH_GetParamAsInt(&gcHandle,/*param index*/0); //get parameter 0 as an integer value
	}


  //NOTES:
  // - avoid blocking calls like 'delay()' inside this callback
	// - do not call free() on cmdName or anything library related, the library takes care of that
	// - command name and parameters must only be accessed within this callback
  // trying to access them outside of it will lead undesired behaviour
}
