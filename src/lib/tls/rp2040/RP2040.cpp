// -----------------------------------------------------------------------------------
// Time/Location source TEENSY 3.2 RTC support

#include "RP2040.h"

#if defined(TIME_LOCATION_SOURCE) && TIME_LOCATION_SOURCE == RP2040 || \
    (defined(TIME_LOCATION_SOURCE_FALLBACK) && TIME_LOCATION_SOURCE_FALLBACK == RP2040)

#include "../../timelib/TimeLib.h" // https://github.com/PaulStoffregen/Time/archive/master.zip

bool TlsRp2040::init() {
  ready = true;
  return ready;
}

void TlsRp2040::set(JulianDate ut1) {
  GregorianDate greg = calendars.julianDayToGregorian(ut1);

  double f1 = fabs(ut1.hour) + TLS_CLOCK_SKEW;
  int h = floor(f1);
  double m = (f1 - h)*60.0;
  double s = (m - floor(m))*60.0;

  set(greg.year, greg.month, greg.day, h, floor(m), floor(s));
}

void TlsRp2040::set(int year, int month, int day, int hour, int minute, int second) {
  setTime(hour, minute, second, day, month, year);
  unsigned long Rp2040Time = now();              // get time in epoch
  Rp2040Clock.set(Rp2040Time);                  // set Teensy time
}

bool TlsRp2040::get(JulianDate &ut1) {
  if (!ready) return false;
  
  unsigned long Rp2040Time = Rp2040Clock.get(); // get time from Teensy RTC
  setTime(Rp2040Time);                           // set system time

  if (year() >= 0 && year() <= 3000 && month() >= 1 && month() <= 12 && day() >= 1 && day() <= 31 &&
      hour() <= 23 && minute() <= 59 && second() <= 59) {
    GregorianDate greg; greg.year = year(); greg.month = month(); greg.day = day();
    ut1 = calendars.gregorianToJulianDay(greg);
    ut1.hour = hour() + minute()/60.0 + second()/3600.0;
  }

  return true;
}

#endif