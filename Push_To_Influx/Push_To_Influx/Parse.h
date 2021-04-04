#ifndef PARSE_H
#define PARSE_H

#include <string>

struct _Sensor {
	float temp_value;
	std::string op_state;
	float battery_voltage;
	std::string node_id;
};
typedef struct _Sensor Sensor;

Sensor parseLine(const std::string& line);

#endif
