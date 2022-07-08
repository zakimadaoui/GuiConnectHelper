#include "ProtoHelper.h"
#include "Servo.h"

ProtoHelper &phelper = ProtoHelper::getInstance();   //init the helper

Servo s1, s2, s3, s4;

// a callback function that triggers when a command is fully recieved
void onRecieve(Command *command) {

    char whichServo = command->getParam(0)->getCharValue();
    int  angle = command->getParam(1)->getIntValue();

    // using a character instead of a full string as commandName is the best Practice
    if (command->getNameAsChar() == 'S'){
        switch (whichServo){
            case '1':
            s1.write(angle);
            break;
        
            case '2':
            s2.write(angle);
            break;
        
             case '3':
            s3.write(angle);
            break;
        
             case '4':
            s4.write(angle);
            break;
        
        }
    }
}

void setup(){
    //servo init code
    s1.attach(3);
    s2.attach(4);
    s3.attach(5);
    s4.attach(6);
    
    Serial.begin(9600);                              //set baudrate to 9600
    Serial.println("Hello !");                       // must send data first for HC-06 to work
    
    phelper.setOnCommandRecievedCallabck(onRecieve); //the OnRecieve callback
    
}

void loop(){
    while (Serial.available())
        phelper.loadByte(Serial.read());            //load all bytes from serial bus
}
