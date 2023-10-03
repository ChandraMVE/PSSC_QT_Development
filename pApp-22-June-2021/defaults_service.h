#ifndef DEFAULTS_SERVICE_H
#define DEFAULTS_SERVICE_H

#define DEFAULT_SET_TEMPERATURE_ENABLE  0
#define DEFAULT_SET_TEMPERATURE         37.8

#define DEFAULT_SET_TOTAL_COUNT               0
#define DEFAULT_SET_COUNT_SINCE_LAST_RESET    0


#define DEFAULT_SET_SHAKER_ENABLE       0
#define DEFAULT_SET_SHAKER_RPM          90
#define RANGE_SHAKER_RPM_MIN            60
#define RANGE_SHAKER_RPM_MAX            210

#define DEFAULT_SET_SELECTOR_VALVE      0
#define DEFAULT_SET_PISTON_POSITION     0.0

#define DEFAULT_SET_CONTINEOUS_RUN      0
#define DEFAULT_SET_DATA_LOG_USB        0

//Cel & kPa for Service & Calibration

#define RANGE_SERVICE_CALIB_TEMPERATURE_MIN               0.00
#define RANGE_SERVICE_CALIB_TEMPERATURE_MAX               100.00
#define RANGE_SERVICE_CALIB_TEMPERATURE_DECIMAL_PLACES    2

#define RANGE_SERVICE_CALIB_PRESSURE_MIN               0.00
#define RANGE_SERVICE_CALIB_PRESSURE_MAX               100.00
#define RANGE_SERVICE_CALIB_PRESSURE_DECIMAL_PLACES    2

#define RANGE_PISTON_POSITION_MIN               0.00
#define RANGE_PISTON_POSITION_MAX               5.25
#define RANGE_PISTON_POSITION_DECIMAL_PLACES    2

#define ERROR_LOG_MAX                           15

#define USB_LOG_TIMEOUT     5

#endif // DEFAULTS_SERVICE_H