#include"GuiConnectHelper.h"
#include<stdlib.h>

void GCH_init(GuiConnectHelper* me, GCHCallbackHandler callback)
{
    me->__cmd.__nameSize = 0;
    me->__cmd.__paramsNbr = 0;
    me->__state = SKIP;
    me->__callback = callback;
}

void GCH_loadNextbyte(GuiConnectHelper* me, uint8_t byte)
{
    //State logic
    if(byte == '>') {
        me->__state = INIT;
    }
    else if((char)byte == ',') {
        if(me->__state == OPCODE_CONCAT) me->__state = OPCODE_RECEIVED;
        else if (me->__cmd.__paramsNbr == MAX_PARAMS_NBR-1) me->__state = FULL_COMMAND_RECEIVED;  //cover case where params received are more than MAX
        else if(me->__state == PARAM_CONCAT) me->__state = PARAM_RECEIVED;
        else me->__state = SKIP;

    }
    else if((char)byte == '<') {
        if(me->__state == OPCODE_CONCAT) me->__state = SIMPLE_COMMAND_RECEIVED;
        else if(me->__state == PARAM_CONCAT) me->__state = FULL_COMMAND_RECEIVED;
        else me->__state = SKIP;
    }  
    else if (me->__cmd.__parserIndex == WORD_SIZE) 
    //cover case where chars received for a command are more than MAX
    {
        me->__state = SKIP; //skip next bytes untill the character is recieved '>' (this will skip the command completely as it is invalid)
    }
    

    //State machine
    switch (me->__state)
    {
    case INIT:
        me->__cmd.__paramsNbr = 0;
        me->__cmd.__nameSize = 0;
        me->__cmd.__parserIndex = 0;
        me->__state = OPCODE_CONCAT;
        break;

    case OPCODE_CONCAT:
        me->__cmd.__commandName[me->__cmd.__parserIndex] = byte;
        me->__cmd.__parserIndex++;
        me->__cmd.__nameSize++;
        break;

    case OPCODE_RECEIVED:
        me->__cmd.__commandName[me->__cmd.__parserIndex] = '\0'; //string termination
        me->__cmd.__parserIndex = 0;
        me->__state = PARAM_CONCAT;
        break;

    case PARAM_CONCAT:
        me->__cmd.__parameters[me->__cmd.__paramsNbr][me->__cmd.__parserIndex] = byte;
        me->__cmd.__parserIndex++;
        break;

    case PARAM_RECEIVED:
        me->__cmd.__parameters[me->__cmd.__paramsNbr][me->__cmd.__parserIndex]  = '\0'; //string termination
        me->__cmd.__paramsNbr++;
        me->__cmd.__parserIndex = 0;
        me->__state = PARAM_CONCAT;
        break;

    case SIMPLE_COMMAND_RECEIVED://case of a command with no parameters
        me->__cmd.__commandName[me->__cmd.__parserIndex] = '\0'; //string termination
        me->__state = SKIP; //skip next bytes untill '>' appears
        me->__callback();
        break;

    case FULL_COMMAND_RECEIVED:
        me->__cmd.__parameters[me->__cmd.__paramsNbr][me->__cmd.__parserIndex]  = '\0'; //string termination
        me->__cmd.__paramsNbr++;
        me->__state = SKIP; //skip next bytes untill '>' appears
        me->__callback();
        break;
    }


}

char    GCH_GetCharCommandName(GuiConnectHelper* me)
{
    if(me->__cmd.__nameSize != 0) return me->__cmd.__commandName[0];
    else return '\0';
}

char*    GCH_GetStrCommandName(GuiConnectHelper* me)
{
    if(me->__cmd.__nameSize != 0) return me->__cmd.__commandName;
    else return NULL;
}

int     GCH_GetParamAsInt(GuiConnectHelper* me, uint8_t param_index)
{
    if(me->__cmd.__paramsNbr >= param_index) return atoi(me->__cmd.__parameters[param_index]);
    else return 0; 
}
long    GCH_GetParamAslong(GuiConnectHelper* me, uint8_t param_index)
{
    if(me->__cmd.__paramsNbr >= param_index) return atol(me->__cmd.__parameters[param_index]);
    else return 0; 
}

float   GCH_GetParamAsFloat(GuiConnectHelper* me, uint8_t param_index)
{
    if(me->__cmd.__paramsNbr >= param_index) return atof(me->__cmd.__parameters[param_index]);
    else return 0; 
}

char    GCH_GetParamAsChar(GuiConnectHelper* me, uint8_t param_index){
    if(me->__cmd.__paramsNbr >= param_index) return me->__cmd.__parameters[param_index][0];
    else return 0; 
}

char*   GCH_GetParamAsString(GuiConnectHelper* me, uint8_t param_index){
    if(me->__cmd.__paramsNbr >= param_index) return me->__cmd.__parameters[param_index];
    else return 0; 
}

uint8_t GCH_getParamsNbr(GuiConnectHelper *me){ return me->__cmd.__paramsNbr;}