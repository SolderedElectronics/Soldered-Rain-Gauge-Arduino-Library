/**
 **************************************************

    @file        Rain_gauge.ino
    @brief       This example shows how to use Rain
                Gauge sensor. This is tipping bucket
                type sensor and one tip equals to 0.516
                mm of rain per meter squared. This value
                is calculated from data we have about sensor.
                Opening for rain collection is about 118mm
                diameter, so area of the opening is about
                0.011 meters squared. Then we measure
                quantity of water needed for tip (this
                sensor is calibrated to 5.7mL per tip).
                So we have 5.7mL or 0.0057 L over 0.011
                meters squared and ratio of that two values
                equals to 0.516 L per square meter per tip
                or 0.516 mm/m^2 per tip. This library counts
                tip by hour and converts that in mm/m^2.



    @authors     @ soldered.com
 ***************************************************/

#include "Rain-Gauge-SOLDERED.h"

#define RAIN_GAUGE_PIN 2 //Specify pin to onnect rain sensor(Pin must support interrupts)

RainGauge *rainGauge = &(RainGauge::GetInstance(RAIN_GAUGE_PIN)); // Get instance of class
// This library depends on interrupts, so we cannot use more
// sensors because it depends on one fucntion called
// interrupt service routine (ISR) and two or more sensors
// would break effects of that function

void setup()
{
    Serial.begin(115200); //Begin serial communication with UART
    rainGauge->reset(); // Reset sensor
    rainGauge->setStartHours(15); // Set time in hours of start of measuring
}

void loop()
{
    if (rainGauge->doneMeasuring()) // Sensor returns 1 if it has measurements for all 24 hours of day
    {
        Serial.println("Measured data for las 24 hours: ");
        for (int i = 0; i < 24; i++) // getStartHours gets value of start measuring
            // hoursAvailable returns current hours of measuring
        {
            if (i > 23)
            {
                i = 0;
            }
            Serial.print("Between "); // Print info messages
            Serial.print(i);
            Serial.print(":00 - ");
            i == 23 ? Serial.print("00") : Serial.print(i + 1);
            Serial.print(":00 amount of precipitation was ");
            Serial.print(rainGauge->getHourlyStatistic(i)); // getHourlyStatistics gets quantity of precipitation for
            // for wanted hours which we specify with parameter of that function
            Serial.println(" mm/m^2");
        }
        Serial.println("!-------------------------------------------------------------!");
        rainGauge->reset();
        delay(10000);
    }
}
