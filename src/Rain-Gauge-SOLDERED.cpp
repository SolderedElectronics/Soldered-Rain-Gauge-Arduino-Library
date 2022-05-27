/**
 **************************************************
 *
 * @file        Rain-Gauge-SOLDERED.cpp
 * @brief       Example functions to overload in base class.
 *
 *
 * @copyright GNU General Public License v3.0
 * @authors     @ soldered.com
 ***************************************************/

#include "Rain-Gauge-SOLDERED.h"

static RainGauge &(RainGauge::GetInstance)(uint8_t _pin)
{
    // Allocate with `new` in case Singleton is not trivially destructible.
    static RainGauge *rGauge = new RainGauge();
    pinMode(_pin, INPUT_PULLUP);
    attachInterrupt(digitalPinToInterrupt(_pin), ISRRain, FALLING);
    return *rGauge;
}

RainGauge::RainGauge()
{
    Serial.println("F");
}


/**
 * @brief                   Sensor specific native constructor.
 *
 * @param int _pin          Example parameter.
 */
/*RainGauge::RainGauge(int _pin)
{
    this->pin = _pin;
    this->counter = 0;

}*/

void RainGauge::reset()
{
    start = millis();
    memset(hourlyQty, 0, 24 * sizeof(float));
    counterHourly = startHours;
    done = 0;
}

void RainGauge::tip()
{
    if (counterHourly != startHours )
    {
        counterHourly = ((millis() - start) / 1000 + startHours) % 24;
        hourlyQty[counterHourly]++;
    }
    else
    {
        done = 1;
    }
}

float RainGauge::getHourlyStatistic(uint8_t hour)
{
    return hourlyQty[hour] * 0.51677244;
}

uint8_t RainGauge::hoursAvailable()
{
    return counterHourly;
}

uint8_t RainGauge::getStartHours()
{
    return startHours;
}

void RainGauge::setStartHours(uint8_t _start)
{
    startHours = _start;
    reset();
}

bool RainGauge::doneMeasuring()
{
    counterHourly = ((millis() - start) / 1000 + startHours) % 24;
    if (counterHourly == startHours )
        done = 1;
    return done;
}

void ISRRain()
{
    rainGauge->tip();
}
