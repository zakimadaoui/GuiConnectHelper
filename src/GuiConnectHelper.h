
#ifdef __cplusplus
extern "C" {
#endif

#ifndef P_PARSER_H
#define P_PARSER_H

#define WORD_SIZE 10
#define MAX_PARAMS_NBR 10

#include<stdint.h>
#include<stddef.h>

typedef enum {SKIP, INIT, OPCODE_CONCAT, OPCODE_RECEIVED, PARAM_CONCAT, PARAM_RECEIVED, SIMPLE_COMMAND_RECEIVED, FULL_COMMAND_RECEIVED} ParserState;

typedef struct Command {
    uint8_t __commandName[WORD_SIZE+1]; //+1 for string termination character
    uint8_t __parameters[MAX_PARAMS_NBR][WORD_SIZE+1];
    uint8_t __nameSize;
    uint8_t __paramsNbr;
    uint8_t __parserIndex;
} Command;

typedef void (*GCHCallbackHandler)(void);

typedef struct GuiConnectHelper{
    Command __cmd;
    ParserState __state;
    GCHCallbackHandler __callback;
} GuiConnectHelper;


void    GCH_init(GuiConnectHelper* me, GCHCallbackHandler callback);

void    GCH_loadNextbyte(GuiConnectHelper* me, uint8_t byte);

char    GCH_GetCharCommandName(GuiConnectHelper* me);
char*   GCH_GetStrCommandName(GuiConnectHelper* me);

int     GCH_GetParamAsInt(GuiConnectHelper* me, uint8_t param_index);
long    GCH_GetParamAslong(GuiConnectHelper* me, uint8_t param_index);
char    GCH_GetParamAsChar(GuiConnectHelper* me, uint8_t param_index);
char*   GCH_GetParamAsString(GuiConnectHelper* me, uint8_t param_index);
float   GCH_GetParamAsFloat(GuiConnectHelper* me, uint8_t param_index);

uint8_t GCH_getParamsNbr(GuiConnectHelper *me);

#endif

#ifdef __cplusplus
}
#endif