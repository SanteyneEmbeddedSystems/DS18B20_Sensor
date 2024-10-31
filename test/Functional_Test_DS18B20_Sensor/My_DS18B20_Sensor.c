#include "My_DS18B20_Sensor.h"

#include "My_One_Wire_IL.h"

DS18B20_Sensor_Var My_DS18B20_Sensor_Var = {
    .Air_Temperature = 0,
    .Last_Sent_Command = 0
};

const DS18B20_Sensor My_DS18B20_Sensor =
{
    .Var = &My_DS18B20_Sensor_Var,
    .One_Wire = &My_One_Wire_IL__One_Wire_Protocol,
    .Device_Address = { 0x28, 0xEE, 0xF4, 0x79, 0xA2, 0x0, 0x3, 0xFD }
};



static void My_DS18B20_Sensor__Measure__Get_Temperature( 
    T_Ambient_Air_Temperature* temperature )
{
    DS18B20__Mesure__Get_Temperature(
        &My_DS18B20_Sensor,
        temperature );
}
const Ambient_Air_Temperature My_DS18B20_Sensor__Ambient_Air_Temperature =
{
    .Get_Temperature = My_DS18B20_Sensor__Measure__Get_Temperature
};