extern "C" {
    #include "My_DS18B20_Sensor.h"
}

void setup( void )
{
    Serial.begin(9600);
    while (!Serial) {
    }
    Serial.println("Serial communication ready");
}

void loop( void )
{
    static uint32_t last_time = 0;
    uint32_t current_time;
    current_time = micros();

    T_Ambient_Air_Temperature temperature = 0;
    
    if( current_time - last_time > 1000000 )
    {
        last_time = current_time;

        DS18B20__Measure_Temperature( &My_DS18B20_Sensor );
        My_DS18B20_Sensor__Ambient_Air_Temperature.Get_Temperature( &temperature );
        Serial.println(temperature);
        Serial.println(temperature*0.0625);
        Serial.println("");
    }
}
