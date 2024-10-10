#ifndef DEFINES_H
#define DEFINES_H

#include <QDebug>
#define M_MEASURING         1
#define M_CLEANING          2
#define M_MEMORY            3
#define M_SETUP             4

#define M_STATE_SELECTED    1
#define M_STATE_RUNNING     2
#define M_STATE_ACTIVE      3
#define M_STATE_DISABLED    4

#define MS_TYPE_DATA        0
#define MS_TYPE_CHECK_DATA  1
#define MS_TYPE_CONFIRM     2
#define MS_TYPE_CANCEL      3
#define MS_TYPE_AGAIN       4


#define MS_TEST_RUN             0
#define MS_TEST_STOP            1
#define MS_RINSING_RUN          2
#define MS_RINSING_STOP         3
#define MS_DIAGNOSTIC_RUN       4
#define MS_DIAGNOSTIC_STOP      5
#define MS_LINEARIZATION_RUN    6
#define MS_LINEARIZATION_STOP   7

#define MS_RINSING_STAGE        2
#define MS_MEASURING_STAGE      2
#define MS_DIAGNOSTIC_STAGE     25

#define M_PWD_GENERAL           1
#define M_PWD_METHOD            2
#define M_PWD_SERVICE           3
#define M_PWD_CALIBRATION       4
#define M_PWD_DEBUG             5   //added this line 7-May-2023 & updated below
#define M_MEMORY_DELETE         6
#define M_MEMORY_TRANSFER       7
#define M_MEMORY_PRINT          8

#define M_PWD_WRONG                 1
#define M_USER_WRONG                2
#define M_MEMORY_DELETED            3
#define M_MEMORY_DELETE_ERROR       4
#define M_MEMORY_TRANSFEFRED        5
#define M_MEMORY_TRANSFER_ERROR     6
#define M_MEMORY_TRANSFER_NO_USB    7

#define M_CONFIRM_MEASURING_STOP            1
#define M_CONFIRM_RINSING_STOP              2
#define M_CONFIRM_GENERAL                   3
#define M_CONFIRM_METHOD                    4
#define M_CONFIRM_SERVICE                   5
#define M_CONFIRM_CALIBRATION               6
#define M_CONFIRM_TRANSFER                  7
#define M_CONFIRM_DELETE                    8
#define M_CONFIRM_NDELETE                   9
#define M_CONFIRM_NTRANSFER                 10
#define M_NPRINT                            11

#define M_ERROR_ACKNOWLEDGE                 12
#define M_CONFIRM_CALIBRATION_SWITCH        13
#define M_CONFIRM_SERVICE_SWITCH            14
#define M_CONFIRM_GENERAL_SWITCH            15
#define M_CONFIRM_USER                      16
#define M_CONFIRM_METHOD_SWITCH             17
#define M_CONFIRM_MEASURE_WITHOUT_SAVING    18
#define M_MESSAGE_ACKNOWLEDGE               19

#define M_METHOD_D5191      0
#define M_METHOD_D6377      1
#define M_METHOD_D6378      2
#define M_METHOD_D5188      3
#define M_METHOD_FREE1      4
#define M_METHOD_FREE2      5
#define M_METHOD_FREE3      6
#define M_METHOD_FREE4      7

#define M_METHOD_NEW_D5191          0
#define M_METHOD_NEW_D6377          1
#define M_METHOD_NEW_D6378          2
#define M_METHOD_NEW_D5188          3
#define M_METHOD_EN_13016_1         4
#define M_METHOD_EN_13016_2         5
#define M_METHOD_GB_T_8017          6
#define M_METHOD_IP_394             7
#define M_METHOD_IP_409             8
#define M_METHOD_IP_481             9
#define M_METHOD_JIS_K2258_2        10
#define M_METHOD_SH_T_0769          11
#define M_METHOD_SH_T_0794          12
#define M_METHOD_SN_T_2932          13
#define M_METHOD_NEW_FREE1          14
#define M_METHOD_NEW_FREE2          15
#define M_METHOD_NEW_FREE3          16
#define M_METHOD_NEW_FREE4          17

#define T_SEL_COL_WIDTH             60
#define T_OPERATOR_COL_WIDTH        180
#define T_SAMPLE_ID_COL_WIDTH       180
#define T_DATE_COL_WIDTH            145
#define T_TIME_COL_WIDTH            140
#define T_PTOT_COL_WIDTH            140
#define T_PABS_COL_WIDTH            140
#define T_PGAS_COL_WIDTH            140
#define T_METHOD_COL_WIDTH          135
#define T_FORMULA_COL_WIDTH         270
#define T_RESULTS_COL_WIDTH         140
#define T_TTIME_COL_WIDTH           170
#define T_VLRATIO_COL_WIDTH         170
#define T_P_MEASURED_COL_WIDTH      210

#define CONTINUOUS_RUN_TIMEOUT  60

#define KAYPAD_ALPHA_NUMERIC    1
#define KAYPAD_NUMERIC          2

#define ACK_TIMEOUT                 5

#define M_VALVE_POSITION_CLOSED     0
#define M_VALVE_POSITION_IN         1
#define M_VALVE_POSITION_EXHAUST    2

#define M_USER_ADMIN                0
#define M_USER_SERVICE              1
#define M_USER_MASTER               2

#define MSG_BOX_PASSWORD            0
#define MSG_BOX_CONFIRMATION        1
#define MSG_BOX_MESSAGGE            2

#define M_ERROR_PISTON_MOTOR          0
#define M_ERROR_PISTON_POSITION       1
#define M_ERROR_PRESSURE_LIMIT        2
#define M_ERROR_DEVICE_TEMPERATURE    3
#define M_ERROR_TEMPERATURE           4
#define M_ERROR_VALVE_MOTOR           5
#define M_ERROR_VALVE_SWITCH          6
#define M_ERROR_PRESSURE_SENSOR       7
#define M_ERROR_SHAKER_MOTOR          8

#define M_ERROR_TIME_OUT              15

#define M_RINSING_TEMPERATURE_TOLERANCE 1 
#define M_TEMPERATURE_TOLERANCE         0.1
#define M_INIT_TEMPERATURE_TOLERANCE    0.5
#define M_PRESSURE_TOLERANCE            0.5 

#define M_MEMORY_COUNT              1000

#define M_PISTON_POSITION_TOLERANCE 5

#define M_BUZZER_START              1
#define M_BUZZER_STOP               0

#define M_EQUILIBRIUM_TIME_OUT      180

#define M_COMMUNICATION_TIME_OUT    10 
#define M_IDLE_TIME_OUT             60*5

//these are for log files
#define MEMORY_FILES                0
#define USER_SETUP_FILES            1
#define GENERAL_SETUP_FILES         2
#define METHOD_SETUP_FILES          3
#define SERVICE_SETUP_FILES         4
#define CALIBRATION_SETUP_FILES     5
#define VOLUME_ADJUSTMENT_FILES     6
//till this

#define FF_FIRMWARE_FOLDER          "/run/media/sda1/RVPPro_Firmware/"
#define FF_USB                      "/run/media/sda1/"
#define USB_PRINTER                 "/dev/usb/lp0"
#define USB_LOG_FOLDER              "/run/media/sda1/RVPPro_Log/"
#define HOST_FILE_NAME              "/etc/hostname"
#define NETWORK_FILE_NAME           "/etc/systemd/network/wired.network"
#define INTERNAL_LOG1               "/log/internal1.txt"
#define INTERNAL_LOG2               "/log/internal2.txt"
#define USB_INTERNAL_LOG            "/run/media/sda1/RVPPro_Internal_Log/"

#define FN_SAMPLE_ID                "/tdata/sampleids.txt"
#define FN_OPERATORS                "/tdata/operators.txt"
#define FN_TESTS                    "/tdata/testslist.txt"
#define FN_ERROR_LOG                "/tdata/errorlog.txt"
#define FN_LAST_IDS                 "/tdata/lastids.txt"

#define FN_SERIAL_SETUP            "/fdata/serialsetup.txt"
#define FN_USER_SETUP               "/cdata/usersetup.txt"
#define FN_GENERAL_SETUP            "/cdata/generalsetup.txt"
#define FN_METHOD_SETUP             "/cdata/methodsetup.txt"
#define FN_MEMORY_SETUP             "/cdata/memorysetup.txt"
#define FN_SERVICE_SETUP            "/cdata/setupsetup.txt"
#define FN_TCALIBRATION_SETUP       "/cdata/calibtm.txt"
#define FN_PCALIBRATION_SETUP       "/cdata/calibpr.txt"
#define FN_UPDATE_FIRMWARE          "/cdata/newfirmware"
#define FN_METHOD_VOLUME_SETUP      "/cdata/calibMethodVolume.txt"


#define STORAGE_DATETIME_FORMAT     "dd/MM/yyyy hh:mm:ss"

#define FW_VERSION  "App: Ver. 1.05.191"
#define FW_DATE  __DATE__
#define FW_TIME __TIME__

#endif // DEFINES_H
