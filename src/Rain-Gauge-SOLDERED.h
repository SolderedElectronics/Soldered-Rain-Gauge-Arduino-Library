/**
 **************************************************
 *
 * @file        Rain-Gauge-SOLDERED.h
 * @brief       Header file for sensor specific code.
 *
 *
 * @copyright GNU General Public License v3.0
 * @authors     @ soldered.com
 ***************************************************/

#ifndef __RainGauge__
#define __RainGauge__

#include "Arduino.h"

class RainGauge
{
  public:
    static RainGauge &GetInstance(uint8_t _pin);
    float getHourlyStatistic(uint8_t hour);
    void tip(void);
    void reset(void);
    uint8_t hoursAvailable(void);
    void setStartHours(uint8_t _start);
    uint8_t getStartHours(void);
    bool doneMeasuring();

  protected:
  private:
    RainGauge();
    RainGauge(const RainGauge &) = delete;
    RainGauge &operator=(const RainGauge &) = delete;
    RainGauge(RainGauge &&) = delete;
    RainGauge &operator=(RainGauge &&) = delete;

    uint32_t start = 0;
    int pin;
    float hourlyQty[24];
    uint8_t counterHourly, prevHours = 0;
    uint8_t startHours;
    bool done = 0;
};

extern RainGauge *rainGauge;

void ISRRain();

#endif
