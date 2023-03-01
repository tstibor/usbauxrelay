#pragma once

#include <Arduino.h>

#define MAX_PAYLOAD_SIZE 10

struct aux_packet {
    uint8_t preamble;
    uint8_t length;
    uint8_t src;
    uint8_t dest;
    uint8_t cmd;
    uint8_t payload[MAX_PAYLOAD_SIZE];
    uint8_t checksum;
};

#define AUX_DEVICE_STR(id)	            \
    id == 0x01 ? "Main Board"  :            \
    id == 0x04 ? "Nexstar HC"  :            \
    id == 0x0d ? "Nexstar+ HC" :            \
    id == 0x0e ? "Starsense HC" :	    \
    id == 0x10 ? "AZM MC" :		    \
    id == 0x11 ? "ALT MC" :		    \
    id == 0x12 ? "Focuser" :		    \
    id == 0x17 ? "Dew Heater Controller" :  \
    id == 0x20 ? "INDI Celestron AUX" :	    \
    id == 0x21 ? "CFM" :		    \
    id == 0x22 ? "USB-AUX Relay" :	    \
    id == 0x30 ? "CGX RA Switch" :	    \
    id == 0x31 ? "CGX DEC Switch" :	    \
    id == 0x32 ? "CGX DEC Autoguide Pt" :   \
    id == 0xb0 ? "GPS" :		    \
    id == 0xb2 ? "RTC" :		    \
    id == 0xb3 ? "Skyportal Accessory" :    \
    id == 0xb4 ? "Starsense Camera" :	    \
    id == 0xb5 ? "Nexstar EVO WiFi" :	    \
    id == 0xb6 ? "Battery Power Cont" :	    \
    id == 0xb7 ? "Charge Port" :	    \
    id == 0xb8 ? "Starsense Camera SW" :    \
    id == 0xbb ? "Dew Heater Controller" :  \
    id == 0xbf ? "Mount Lights" : "UNKNOWN"

#define AUX_COMMAND_STR(id, cmd)		  \
    id == 0x01 && cmd == 0xfe ? "MB_GET_FW_VER" : \
    id == 0x04 && cmd == 0xfe ? "NXS_GET_FW_VER" : \
    id == 0x0d && cmd == 0xfe ? "NXS_GET_FW_VER" : \
    id == 0x0e && cmd == 0xfe ? "NXS_GET_FW_VER" : \
    id == 0x10 && cmd == 0x01 ? "MTR_GET_POSITION" : \
    id == 0x10 && cmd == 0x02 ? "MTR_GOTO" : \
    id == 0x10 && cmd == 0x04 ? "MTR_SET_POSITION" : \
    id == 0x10 && cmd == 0x05 ? "MTR_GET_MODEL" : \
    id == 0x10 && cmd == 0x06 ? "MTR_PTRACK" : \
    id == 0x10 && cmd == 0x07 ? "MTR_NTRACK" : \
    id == 0x10 && cmd == 0x08 ? "MTR_REMOTE_SWITCH_ALIVE" : \
    id == 0x10 && cmd == 0x09 ? "MTR_SWITCH_STATE_CHANGE" : \
    id == 0x10 && cmd == 0x0A ? "MTR_AG_STATE_CHANGE 0x0A" : \
    id == 0x10 && cmd == 0x0B ? "MTR_MVSWITCH" : \
    id == 0x10 && cmd == 0x0C ? "MTR_PECTRAIN" : \
    id == 0x10 && cmd == 0x0D ? "MTR_PECPLAY" : \
    id == 0x10 && cmd == 0x0E ? "MTR_GET_PEC_BIN" : \
    id == 0x10 && cmd == 0x10 ? "MTR_SET_POS_BACKLASH" : \
    id == 0x10 && cmd == 0x11 ? "MTR_SET_NEG_BACKLASH" : \
    id == 0x10 && cmd == 0x12 ? "MTR_IS_MVSWITCH_OVER" : \
    id == 0x10 && cmd == 0x13 ? "MTR_IS_GOTO_OVER" : \
    id == 0x10 && cmd == 0x14 ? "MTR_PEC_STATE_CHANGE" : \
    id == 0x10 && cmd == 0x15 ? "MTR_IS_PECTRAIN_OVER" : \
    id == 0x10 && cmd == 0x16 ? "MTR_CANCEL_PECTRAIN" : \
    id == 0x10 && cmd == 0x17 ? "MTR_GOTO2" : \
    id == 0x10 && cmd == 0x18 ? "MTR_IS_INDEX_FOUND" : \
    id == 0x10 && cmd == 0x19 ? "MTR_FIND_INDEX" : \
    id == 0x10 && cmd == 0x1a ? "MTR_SET_USER_LIMIT_MIN" : \
    id == 0x10 && cmd == 0x1b ? "MTR_SET_USER_LIMIT_MAX" : \
    id == 0x10 && cmd == 0x1c ? "MTR_GET_USER_LIMIT_MIN" : \
    id == 0x10 && cmd == 0x1d ? "MTR_GET_USER_LIMIT_MAX" : \
    id == 0x10 && cmd == 0x1e ? "MTR_IS_USER_LIMIT_ENABLED" : \
    id == 0x10 && cmd == 0x1f ? "MTR_SET_USER_LIMIT_ENABLED" : \
    id == 0x10 && cmd == 0x20 ? "MTR_SET_CUSTOM_RATE9" : \
    id == 0x10 && cmd == 0x21 ? "MTR_GET_CUSTOM_RATE9" : \
    id == 0x10 && cmd == 0x22 ? "MTR_SET_CUSTOM_RATE9_ENA" : \
    id == 0x10 && cmd == 0x23 ? "MTR_GET_CUSTOM_RATE9_ENA" : \
    id == 0x10 && cmd == 0x24 ? "MTR_PMSLEW_RATE" : \
    id == 0x10 && cmd == 0x25 ? "MTR_NMSLEW_RATE" : \
    id == 0x10 && cmd == 0x26 ? "MTR_AUX_GUIDE" : \
    id == 0x10 && cmd == 0x27 ? "MTR_IS_AUX_GUIDE_ACTIVE" : \
    id == 0x10 && cmd == 0x2a ? "MTR_HS_CALIBRATION_ENABLE" : \
    id == 0x10 && cmd == 0x2b ? "MTR_IS_HS_CALIBRATED" : \
    id == 0x10 && cmd == 0x2c ? "MTR_GET_HS_POSITIONS" : \
    id == 0x10 && cmd == 0x30 ? "MTR_EEPROM_READ" : \
    id == 0x10 && cmd == 0x31 ? "MTR_EEPROM_WRITE" : \
    id == 0x10 && cmd == 0x32 ? "MTR_PROGRAM_READ" : \
    id == 0x10 && cmd == 0x38 ? "MTR_CORDWRAP_ON" : \
    id == 0x10 && cmd == 0x39 ? "MTR_CORDWRAP_OFF" : \
    id == 0x10 && cmd == 0x3a ? "MTR_SET_CORDWRAP_POSITION" : \
    id == 0x10 && cmd == 0x3b ? "MTR_IS_CORDWRAP_ON" : \
    id == 0x10 && cmd == 0x3c ? "MTR_GET_CORDWRAP_POSITION" : \
    id == 0x10 && cmd == 0x3d ? "MTR_SET_SHUTTER" : \
    id == 0x10 && cmd == 0x40 ? "MTR_GET_POS_BACKLASH" : \
    id == 0x10 && cmd == 0x41 ? "MTR_GET_NEG_BACKLASH" : \
    id == 0x10 && cmd == 0x46 ? "MTR_SET_AUTOGUIDE_RATE" : \
    id == 0x10 && cmd == 0x47 ? "MTR_GET_AUTOGUIDE_RATE" : \
    id == 0x10 && cmd == 0x48 ? "MTR_SET_SWITCH_CALIBRATION" : \
    id == 0x10 && cmd == 0x49 ? "MTR_SET_SWITCH_CALIBRATION" : \
    id == 0x10 && cmd == 0x4a ? "MTR_SET_PRN_VALUE" : \
    id == 0x10 && cmd == 0x4b ? "MTR_GET_PRN_VALUE" : \
    id == 0x10 && cmd == 0x50 ? "MTR_SEND_WARNING" : \
    id == 0x10 && cmd == 0x51 ? "MTR_SEND_ERROR" : \
    id == 0x10 && cmd == 0x5b ? "MTR_SET_PID_KP" : \
    id == 0x10 && cmd == 0x5c ? "MTR_SET_PID_KI" : \
    id == 0x10 && cmd == 0x5d ? "MTR_SET_PID_KD" : \
    id == 0x10 && cmd == 0x5f ? "MTR_ENABLE_PID_ANALYSIS" : \
    id == 0x10 && cmd == 0x8a ? "MTR_PROGRAMMER_ENABLE" : \
    id == 0x10 && cmd == 0xee ? "MTR_GET_HARDSWITCH_ENABLE" : \
    id == 0x10 && cmd == 0xef ? "MTR_SET_HARDSWITCH_ENABLE" : \
    id == 0x10 && cmd == 0xfa ? "MTR_GET_CHIPVERSION" : \
    id == 0x10 && cmd == 0xfb ? "MTR_GET_BOOTVERSION" : \
    id == 0x10 && cmd == 0xfc ? "MTR_IS_APPROACH_DIR_NEG" : \
    id == 0x10 && cmd == 0xfd ? "MTR_SET_APPROACH_DIR_NEG" : \
    id == 0x10 && cmd == 0xfe ? "MTR_GET_VERSION" : \
    id == 0x11 && cmd == 0x01 ? "MTR_GET_POSITION" : \
    id == 0x11 && cmd == 0x02 ? "MTR_GOTO" : \
    id == 0x11 && cmd == 0x04 ? "MTR_SET_POSITION" : \
    id == 0x11 && cmd == 0x05 ? "MTR_GET_MODEL" : \
    id == 0x11 && cmd == 0x06 ? "MTR_PTRACK" : \
    id == 0x11 && cmd == 0x07 ? "MTR_NTRACK" : \
    id == 0x11 && cmd == 0x08 ? "MTR_REMOTE_SWITCH_ALIVE" : \
    id == 0x11 && cmd == 0x09 ? "MTR_SWITCH_STATE_CHANGE" : \
    id == 0x11 && cmd == 0x0a ? "MTR_AG_STATE_CHANGE 0x0A" : \
    id == 0x11 && cmd == 0x0b ? "MTR_MVSWITCH" : \
    id == 0x11 && cmd == 0x0c ? "MTR_PECTRAIN" : \
    id == 0x11 && cmd == 0x0d ? "MTR_PECPLAY" : \
    id == 0x11 && cmd == 0x0e ? "MTR_GET_PEC_BIN" : \
    id == 0x11 && cmd == 0x10 ? "MTR_SET_POS_BACKLASH" : \
    id == 0x11 && cmd == 0x11 ? "MTR_SET_NEG_BACKLASH" : \
    id == 0x11 && cmd == 0x12 ? "MTR_IS_MVSWITCH_OVER" : \
    id == 0x11 && cmd == 0x13 ? "MTR_IS_GOTO_OVER" : \
    id == 0x11 && cmd == 0x14 ? "MTR_PEC_STATE_CHANGE" : \
    id == 0x11 && cmd == 0x15 ? "MTR_IS_PECTRAIN_OVER" : \
    id == 0x11 && cmd == 0x16 ? "MTR_CANCEL_PECTRAIN" : \
    id == 0x11 && cmd == 0x17 ? "MTR_GOTO2" : \
    id == 0x11 && cmd == 0x18 ? "MTR_IS_INDEX_FOUND" : \
    id == 0x11 && cmd == 0x19 ? "MTR_FIND_INDEX" : \
    id == 0x11 && cmd == 0x1a ? "MTR_SET_USER_LIMIT_MIN" : \
    id == 0x11 && cmd == 0x1b ? "MTR_SET_USER_LIMIT_MAX" : \
    id == 0x11 && cmd == 0x1c ? "MTR_GET_USER_LIMIT_MIN" : \
    id == 0x11 && cmd == 0x1d ? "MTR_GET_USER_LIMIT_MAX" : \
    id == 0x11 && cmd == 0x1e ? "MTR_IS_USER_LIMIT_ENABLED" : \
    id == 0x11 && cmd == 0x1f ? "MTR_SET_USER_LIMIT_ENABLED" : \
    id == 0x11 && cmd == 0x20 ? "MTR_SET_CUSTOM_RATE9" : \
    id == 0x11 && cmd == 0x21 ? "MTR_GET_CUSTOM_RATE9" : \
    id == 0x11 && cmd == 0x22 ? "MTR_SET_CUSTOM_RATE9_ENA" : \
    id == 0x11 && cmd == 0x23 ? "MTR_GET_CUSTOM_RATE9_ENA" : \
    id == 0x11 && cmd == 0x24 ? "MTR_PMSLEW_RATE" : \
    id == 0x11 && cmd == 0x25 ? "MTR_NMSLEW_RATE" : \
    id == 0x11 && cmd == 0x26 ? "MTR_AUX_GUIDE" : \
    id == 0x11 && cmd == 0x27 ? "MTR_IS_AUX_GUIDE_ACTIVE" : \
    id == 0x11 && cmd == 0x2a ? "MTR_HS_CALIBRATION_ENABLE" : \
    id == 0x11 && cmd == 0x2b ? "MTR_IS_HS_CALIBRATED" : \
    id == 0x11 && cmd == 0x2c ? "MTR_GET_HS_POSITIONS" : \
    id == 0x11 && cmd == 0x30 ? "MTR_EEPROM_READ" : \
    id == 0x11 && cmd == 0x31 ? "MTR_EEPROM_WRITE" : \
    id == 0x11 && cmd == 0x32 ? "MTR_PROGRAM_READ" : \
    id == 0x11 && cmd == 0x38 ? "MTR_CORDWRAP_ON" : \
    id == 0x11 && cmd == 0x39 ? "MTR_CORDWRAP_OFF" : \
    id == 0x11 && cmd == 0x3a ? "MTR_SET_CORDWRAP_POSITION" : \
    id == 0x11 && cmd == 0x3b ? "MTR_IS_CORDWRAP_ON" : \
    id == 0x11 && cmd == 0x3c ? "MTR_GET_CORDWRAP_POSITION" : \
    id == 0x11 && cmd == 0x3d ? "MTR_SET_SHUTTER" : \
    id == 0x11 && cmd == 0x40 ? "MTR_GET_POS_BACKLASH" : \
    id == 0x11 && cmd == 0x41 ? "MTR_GET_NEG_BACKLASH" : \
    id == 0x11 && cmd == 0x46 ? "MTR_SET_AUTOGUIDE_RATE" : \
    id == 0x11 && cmd == 0x47 ? "MTR_GET_AUTOGUIDE_RATE" : \
    id == 0x11 && cmd == 0x48 ? "MTR_SET_SWITCH_CALIBRATION" : \
    id == 0x11 && cmd == 0x49 ? "MTR_SET_SWITCH_CALIBRATION" : \
    id == 0x11 && cmd == 0x4a ? "MTR_SET_PRN_VALUE" : \
    id == 0x11 && cmd == 0x4b ? "MTR_GET_PRN_VALUE" : \
    id == 0x11 && cmd == 0x50 ? "MTR_SEND_WARNING" : \
    id == 0x11 && cmd == 0x51 ? "MTR_SEND_ERROR" : \
    id == 0x11 && cmd == 0x5b ? "MTR_SET_PID_KP" : \
    id == 0x11 && cmd == 0x5c ? "MTR_SET_PID_KI" : \
    id == 0x11 && cmd == 0x5d ? "MTR_SET_PID_KD" : \
    id == 0x11 && cmd == 0x5f ? "MTR_ENABLE_PID_ANALYSIS" : \
    id == 0x11 && cmd == 0x8a ? "MTR_PROGRAMMER_ENABLE" : \
    id == 0x11 && cmd == 0xee ? "MTR_GET_HARDSWITCH_ENABLE" : \
    id == 0x11 && cmd == 0xef ? "MTR_SET_HARDSWITCH_ENABLE" : \
    id == 0x11 && cmd == 0xfa ? "MTR_GET_CHIPVERSION" : \
    id == 0x11 && cmd == 0xfb ? "MTR_GET_BOOTVERSION" : \
    id == 0x11 && cmd == 0xfc ? "MTR_IS_APPROACH_DIR_NEG" : \
    id == 0x11 && cmd == 0xfd ? "MTR_SET_APPROACH_DIR_NEG" : \
    id == 0x11 && cmd == 0xfe ? "MTR_GET_VERSION" : \
    id == 0x12 && cmd == 0x01 ? "FOCUS_GET_POSITION" : \
    id == 0x12 && cmd == 0x02 ? "FOCUS_GOTO_FAST" : \
    id == 0x12 && cmd == 0x13 ? "FOCUS_SLEW_DONE" : \
    id == 0x12 && cmd == 0x24 ? "FOCUS_MOVE_POS" : \
    id == 0x12 && cmd == 0x25 ? "FOCUS_MOVE_NEG" : \
    id == 0x12 && cmd == 0x2a ? "FOCUS_CALIBRATION_ENABLE" : \
    id == 0x12 && cmd == 0x2b ? "FOCUS_IS_CALIBRATED" : \
    id == 0x12 && cmd == 0x2c ? "FOCUS_GET_CALIBRATION_POSITIONS" : \
    id == 0x12 && cmd == 0x3b ? "FOCUS_XXX" : \
    id == 0x12 && cmd == 0xfe ? "FOCUS_GET_FW_VER" : \
    id == 0x17 && cmd == 0x00 ? "DEWHEATER_GET_CURRENT_POWER" : \
    id == 0x17 && cmd == 0x04 ? "DEWHEATER_GET_LIMIT_POWER" : \
    id == 0x17 && cmd == 0x10 ? "DEWHEATER_GET_POWER_PORTS" : \
    id == 0x17 && cmd == 0x11 ? "DEWHEATER_GET_PORTS" : \
    id == 0x17 && cmd == 0x12 ? "DEWHEATER_GET_STATUS" : \
    id == 0x17 && cmd == 0x18 ? "DEWHEATER_GET_AMBIENT" : \
    id == 0x20 && cmd == 0xfe ? "NXS_GET_FW_VER" : \
    id == 0xb0 && cmd == 0x01 ? "GPS_GET_LAT" : \
    id == 0xb0 && cmd == 0x02 ? "GPS_GET_LONG" : \
    id == 0xb0 && cmd == 0x03 ? "GPS_GET_DATE" : \
    id == 0xb0 && cmd == 0x04 ? "GPS_GET_YEAR" : \
    id == 0xb0 && cmd == 0x07 ? "GPS_GET_SAT_INFO" : \
    id == 0xb0 && cmd == 0x08 ? "GPS_GET_RCVR_STATUS" : \
    id == 0xb0 && cmd == 0x33 ? "GPS_GET_TIME" : \
    id == 0xb0 && cmd == 0x36 ? "GPS_TIME_VALID" : \
    id == 0xb0 && cmd == 0x37 ? "GPS_LINKED" : \
    id == 0xb0 && cmd == 0xa0 ? "GPS_GET_COMPASS" : \
    id == 0xb0 && cmd == 0xfe ? "GPS_GET_FW_VER" : \
    id == 0xb2 && cmd == 0xfe ? "RTC_GET_FW_VER" : \
    id == 0xb3 && cmd == 0xfe ? "WIFI_GET_FW_VER" : \
    id == 0xb4 && cmd == 0x3e ? "SS_SET_ALIGN_CENTER" : \
    id == 0xb4 && cmd == 0x3f ? "SS_GET_ALIGN_CENTER" : \
    id == 0xb4 && cmd == 0x90 ? "SS_RESET_CAPTURE" : \
    id == 0xb4 && cmd == 0x91 ? "SS_GET_STATUS" : \
    id == 0xb4 && cmd == 0x92 ? "SS_GET_CAPTURE_DATA" : \
    id == 0xb4 && cmd == 0x94 ? "SS_START_CAPTURE" : \
    id == 0xb4 && cmd == 0x9f ? "SS_GET_IMAGE3" : \
    id == 0xb4 && cmd == 0xfe ? "SS_GET_FW_VER" : \
    id == 0xb5 && cmd == 0xfe ? "WIFI_GET_FW_VER" : \
    id == 0xb6 && cmd == 0x10 ? "BAT_GET_VOLTAGE" : \
    id == 0xb6 && cmd == 0x18 ? "BAT_GET_CURRENT" : \
    id == 0xb6 && cmd == 0xfe ? "BAT_GET_FW_VER" : \
    id == 0xb7 && cmd == 0x10 ? "CHG_GET_MODE" : \
    id == 0xb7 && cmd == 0xfe ? "CHG_GET_FW_VER" : \
    id == 0xbb && cmd == 0xfe ? "DEWHEATER_GET_FW_VER" : \
    id == 0xbf && cmd == 0x10 ? "LIGHT_GET_LEVEL" : \
    id == 0xbf && cmd == 0xfe ? "LIGHT_GET_FW_VER" : "UNKNOWN"
