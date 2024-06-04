#ifndef DEFAULTS_METHOD_H
#define DEFAULTS_METHOD_H

#define ENABLED                             2 //true
#define DISAABLED                           0 //false


#define METHOD_CONSTANT_MIN           -10.00
#define METHOD_CONSTANT_MAX           10.00
#define METHOD_CONSTANT_DP            3

#define METHOD_TEMPERATURE_MIN          10
#define METHOD_TEMPERATURE_MAX          100
#define METHOD_TEMPERATURE_DP           1

#define METHOD_PRESSURE_MIN          0
#define METHOD_PRESSURE_MAX          150
#define METHOD_PRESSURE_DP           1

#define D5191_METHOD_FROM               0.0
#define D5191_METHOD_TO                 999.9
#define D6377_METHOD_FROM               0.0
#define D6377_METHOD_TO                 999.9
#define D6378_METHOD_FROM               0.0
#define D6378_METHOD_TO                 999.9
#define D5188_METHOD_FROM               10.0
#define D5188_METHOD_TO                 70.0
#define FREE_METHOD_FROM                0.0
#define FREE_METHOD_TO                  999.9

#define METHOD_TIME_MIN                 1
#define METHOD_TIME_MAX                 600
#define METHOD_TIME_DP                  0

#define METHOD_TPX_MIN                  0
#define METHOD_TPX_MAX                  600
#define METHOD_TPX_DP                   0

#define METHOD_VLRATIO_MIN              0.02
#define METHOD_VLRATIO_MAX              20
#define METHOD_VLRATIO_DP               2

#define METHOD_SHAKER_SPEED_MIN         1.0
#define METHOD_SHAKER_SPEED_MAX         5.0
#define METHOD_SHAKER_SPEED_DP          1

#define METHOD_EQUI_TIME_MIN            1
#define METHOD_EQUI_TIME_MAX            600
#define METHOD_EQUI_TIME_DP             0


#define DEFAULT_D5191_FORMULA               0
#define DEFAULT_D5191_TEMPERATURE           37.8
#define DEFAULT_D5191_TIME                  300
#define DEFAULT_D5191_VL_RATIO              4
#define DEFAULT_D5191_PASS_FAIL_ENABLED     DISAABLED
#define DEFAULT_D5191_SINGLE_EXPAN_ENABLED  DISAABLED
#define DEFAULT_D5191_ALARM_ENABLED         ENABLED
#define DEFAULT_D5191_FROM                  111.6
#define DEFAULT_D5191_TO                    114.0

#define DEFAULT_D6377_TEMPERATURE           37.8
#define DEFAULT_D6377_TIME                  300
#define DEFAULT_D6377_VL_RATIO              4
#define DEFAULT_D6377_SHAKER_SPEED          1.5
#define DEFAULT_D6377_PASS_FAIL_ENABLED     ENABLED
#define DEFAULT_D6377_ALARM_ENABLED         ENABLED
#define DEFAULT_D6377_FROM                  111.6
#define DEFAULT_D6377_TO                    114.0

#define DEFAULT_D6378_FORMULA               0
#define DEFAULT_D6378_TEMPERATURE           37.8
#define DEFAULT_D6378_TIME                  300
#define DEFAULT_D6378_VL_RATIO              4
#define DEFAULT_D6378_PASS_FAIL_ENABLED     ENABLED
#define DEFAULT_D6378_ALARM_ENABLED         ENABLED
#define DEFAULT_D6378_FROM                  106.7
#define DEFAULT_D6378_TO                    109.1

#define DEFAULT_D5188_PRESSURE              101.3
#define DEFAULT_D5188_VL_RATIO              20
#define DEFAULT_D5188_SHAKER_SPEED          1.5
#define DEFAULT_D5188_PASS_FAIL_ENABLED     ENABLED
#define DEFAULT_D5188_ALARM_ENABLED         ENABLED
#define DEFAULT_D5188_FROM                  35.3
#define DEFAULT_D5188_TO                    36.2

#define DEFAULT_FREE_A_CONSTANT             1.000
#define DEFAULT_FREE_B_CONSTANT             0.500
#define DEFAULT_FREE_C_CONSTANT             0.000
#define DEFAULT_FREE_TEMPERATURE            37.8
#define DEFAULT_FREE_TPX1                   180
#define DEFAULT_FREE_TPX2                   60
#define DEFAULT_FREE_TPX3                   60
#define DEFAULT_FREE_VLRATIO                4.0
#define DEFAULT_FREE_SHAKER_SPEED           1.5
#define DEFAULT_FREE_SHAKER_DISABLE         ENABLED
#define DEFAULT_FREE_PASS_FAIL_ENABLED      ENABLED
#define DEFAULT_FREE_ALARM_ENABLED          ENABLED
#define DEFAULT_FREE_FROM                   111.6
#define DEFAULT_FREE_TO                     114.0


#endif // DEFAULTS_METHOD_H
