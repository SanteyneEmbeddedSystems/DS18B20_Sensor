#include "DS18B20_Sensor.h"


/*============================================================================*/
/* Types, Macros */
/*============================================================================*/
#define READ_SCRATCHPAD_CMD 0xBE
#define CONVERT_TEMPERATURE_CMD 0x44


/*============================================================================*/
/* Attributes access */
/*============================================================================*/
#define My_Air_Temperature (Me->Var->Air_Temperature)
#define My_Last_Sent_Command (Me->Var->Last_Sent_Command)


/*============================================================================*/
/* Required interface access */
/*============================================================================*/
#define One_Wire__Send_Simple_Command( addr, cmd ) \
        Me->One_Wire->Send_Simple_Command( addr, cmd )
#define One_Wire__Send_Read_Command( addr, cmd, b, nb ) \
        Me->One_Wire->Send_Read_Command( addr, cmd, b, nb )


/*============================================================================*/
/* OS_Operations */
/*============================================================================*/
void DS18B20__Measure_Temperature( const DS18B20_Sensor* Me )
{
    /* Check My_Last_Sent_Command */
    if( READ_SCRATCHPAD_CMD==My_Last_Sent_Command )
    {
        /* Request temperature conversion */
        One_Wire__Send_Simple_Command(
            &(Me->Device_Address),
            CONVERT_TEMPERATURE_CMD );

        /* Update My_Last_Sent_Command */
        My_Last_Sent_Command = CONVERT_TEMPERATURE_CMD;
    }
    else if( CONVERT_TEMPERATURE_CMD==My_Last_Sent_Command )
    {
        /* Read scratchpad */
        uint8_t read_bytes[2];
        One_Wire__Send_Read_Command( 
            &(Me->Device_Address),
            READ_SCRATCHPAD_CMD,
            read_bytes,
            2 );
        
        /* Convert read bytes into temperature */
        My_Air_Temperature = read_bytes[0] | (read_bytes[1] << 8 );

        /* Update My_Last_Sent_Command */
        My_Last_Sent_Command = READ_SCRATCHPAD_CMD;
    }
    else
    { /* RAM corruption or init */
        /* Robustness */
        My_Last_Sent_Command = CONVERT_TEMPERATURE_CMD;
    }
}


/*============================================================================*/
/* Realized interface */
/*============================================================================*/
void DS18B20__Mesure__Get_Temperature(
    const DS18B20_Sensor* Me,
    T_Ambient_Air_Temperature* temperature )
{
    *temperature = My_Air_Temperature;
}
