#include<stdio.h>
#include<stdbool.h>
#include"GuiConnectHelper.h"
#include"string.h"

GuiConnectHelper gcHandle;
bool test[10] = {false};

void onReceive(){
    char cmd = GCH_GetCharCommandName(&gcHandle);
    int angle = GCH_GetParamAsInt(&gcHandle, 0);
}

void pushCommand(char *arr, int size){
    for (size_t i = 0; i < size; i++)GCH_loadNextbyte(&gcHandle, arr[i]);
}

void asssert(int i){
    printf("test %d %s\n", i, (test[i] == true)? "PASSED" : "FAILED");
}

void test0();
void test1();
void test1type();
void test2();
void test3();
void test4();


int main(){
    GCH_init(&gcHandle, onReceive);
    
    test0();
    test1();
    test1type();
    test2();
    test3();
    test4();
}

void test0(){
    char cmd[] = ">test0<";
    int  size = sizeof(cmd)/sizeof(cmd[0]);
    pushCommand(cmd,size);

    char* opcode = GCH_GetStrCommandName(&gcHandle);
    if(strcmp(opcode, "test0") == 0){
        test[0] = true;
    }else{
        test[0] = false;
    }
    asssert(0);
}

void test1(){
    char cmd[] = ">teeest1,123<";
    int  size = sizeof(cmd)/sizeof(cmd[0]);
    pushCommand(cmd,size);

    char* opcode = GCH_GetStrCommandName(&gcHandle);
    if(strcmp(opcode, "teeest1") == 0 && GCH_GetParamAsInt(&gcHandle,0) == 123){
        test[1] = true;
    }else{
        test[1] = false;
    }
    asssert(1);
}

void test1type(){
    char cmd[] = ">teeest7,125.5<";
    int  size = sizeof(cmd)/sizeof(cmd[0]);
    pushCommand(cmd,size);

    char* opcode = GCH_GetStrCommandName(&gcHandle);
    if(strcmp(opcode, "teeest7") == 0 && GCH_GetParamAsInt(&gcHandle,0) == 125){
        test[7] = true;
    }else{
        test[7] = false;
    }
    asssert(7);
}


void test2(){
    char cmd[] = ">test2,1234567897<";
    int  size = sizeof(cmd)/sizeof(cmd[0]);
    pushCommand(cmd,size);

    char* opcode = GCH_GetStrCommandName(&gcHandle);
    if(strcmp(opcode, "test2") == 0 && GCH_GetParamAsInt(&gcHandle,0) == 1234567897){
        test[2] = true;
    }else{
        test[2] = false;
    }
    asssert(2);
}

void test3(){
    char cmd[] = ">test3,1234567897888<";
    int  size = sizeof(cmd)/sizeof(cmd[0]);
    pushCommand(cmd,size);

    char* opcode = GCH_GetStrCommandName(&gcHandle);
    if(strcmp(opcode, "test3") == 0 &&GCH_GetParamAsInt(&gcHandle,0) == 1234567897){
        test[3] = true;
    }else{
        test[3] = false;
    }
    asssert(3);
}

void test4(){
    char cmd[] = ">test4,1,2,3,4,5,6,7,8,9,10,11,12,13<";
    int  size = sizeof(cmd)/sizeof(cmd[0]);
    pushCommand(cmd,size);

    if(GCH_getParamsNbr(&gcHandle) == MAX_PARAMS_NBR && GCH_GetParamAsInt(&gcHandle,9) == 10){
        test[4] = true;
    }else{
        test[4] = false;
    }
    asssert(4);
}



