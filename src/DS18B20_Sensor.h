#ifndef DS18B20_SENSOR_H
#define DS18B20_SENSOR_H


/*============================================================================*/
/* Inclusions */
/*============================================================================*/
/* Attributes */
#include "T_Ambient_Air_Temperature.h"
#include "T_One_Wire_Device_Address.h"

/* Realized interfaces */
#include "Ambient_Air_Temperature.h"

/* Required interfaces */
#include "One_Wire_Protocol.h"


/*============================================================================*/
/* Component_Type */
/*============================================================================*/
typedef struct {
    T_Ambient_Air_Temperature Air_Temperature;
    uint8_t Last_Sent_Command;
} DS18B20_Sensor_Var;

typedef struct {

    /* Variable attributes */
    DS18B20_Sensor_Var* Var;

    /* Required interfaces */
    const One_Wire_Protocol* One_Wire;
    
    /* Configuration_Parameters */
    const T_One_Wire_Device_Address Device_Address;
    
} DS18B20_Sensor;


/*============================================================================*/
/* Component_Operations */
/*============================================================================*/
void DS18B20__Measure_Temperature( const DS18B20_Sensor* Me );


/*============================================================================*/
/* Realized interfaces */
/*============================================================================*/
void DS18B20__Mesure__Get_Temperature(
    const DS18B20_Sensor* Me,
    T_Ambient_Air_Temperature* temperature );

#endif