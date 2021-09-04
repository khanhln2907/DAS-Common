#pragma once
#include "Arduino.h"

template<typename T> struct Sample {
	T Value;
	uint64_t TimeStamp;
};

typedef struct Position_WGS84 {
	double lon;
	double lat;
	double alt;
}Position_WGS84;

typedef struct UTCTime {
	uint8_t hour;
	uint8_t minute;
	float second;
}UTCTime;

typedef struct Date {
	uint8_t day;
	uint8_t month;
	uint16_t year;
}Date;

typedef struct Acceleration_t {
	double x;
	double y;
	double z;
}Acceleration_t;

typedef struct AttitudeRate_t {
	double p;
	double q;
	double r;
}AttitudeRate_t;

typedef struct Attitude_t {
	double phi;
	double theta;
	double psi;
}Attitude_t;

typedef struct Magnetometer_t {
	double x;
	double y;
	double z;
}Magnetometer_t;
