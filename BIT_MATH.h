#define SET_BIT(VAR,BIT_NUM) VAR|=(1<<BIT_NUM)      //Set Bit
#define CLR_BIT(VAR,BIT_NUM) VAR&=(~(1<<BIT_NUM))   //Clear Bit
#define TOGGLE_BIT(VAR,BIT_NUM) VAR^=(1<<BIT_NUM)   //Toggle Bit
#define GET_BIT(VAR,BIT_NUM) ((VAR>>BIT_NUM)&1)     //Read Bit
