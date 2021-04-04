#include "Parse.h"
#include <iostream>
#include <string>


using std::cout;
using std::endl;
using std::string;
using std::size_t;



Sensor parseLine(const string& line)
{
	Sensor data;

	const char BLANK = ' ';
	const char VBAR = '|';

	enum class ParseStates { TEMP, SEPERATOR, OP_STATE, BATTERY_VOLTAGE_FILLER, BATTERY_VOLTAGE, NODE_ID_FILLER, NODE_ID };

	ParseStates state = ParseStates::TEMP;  

	string token;

	bool complete_token = false;

	const size_t n = line.length();

	size_t sz;

	bool toggle_for_node = 0;

	for (size_t i = 0; i < n; i++) {
		const char c = line[i];
		switch (state) {
		case ParseStates::TEMP:
			if (c == BLANK) {
				state = ParseStates::SEPERATOR;
			}
			else {
				if (c == 'F' || c == 'C') {
					sz = token.length();
					data.temp_value = std::stof(token, &sz);
					complete_token = true;
					state = ParseStates::SEPERATOR;
				}
				else {
					token += c;
					state = ParseStates::TEMP;
				}
			}
			break;
		case ParseStates::SEPERATOR:
			if (c != BLANK && c != VBAR) {
				if (c == 'S' || c == 'C') {
					token += c;
					state = ParseStates::OP_STATE;
				}
				else if (c == 'B') {
					state = ParseStates::BATTERY_VOLTAGE_FILLER;
				}
				else if (c == 'N') {
					state = ParseStates::NODE_ID_FILLER;
				}
			}
			else {
				state = ParseStates::SEPERATOR;
			}
			break;
		case ParseStates::OP_STATE:
			if (c != BLANK) {
				token += c;
				state = ParseStates::OP_STATE;
			}
			else {
				data.op_state = token;
				complete_token = true;
				state = ParseStates::SEPERATOR;
			}
			break;
		case ParseStates::BATTERY_VOLTAGE_FILLER:
			if (c == ':') {
				state = ParseStates::BATTERY_VOLTAGE;
			}
			else {
				state = ParseStates::BATTERY_VOLTAGE_FILLER;
			}
			break;
		case ParseStates::BATTERY_VOLTAGE:
			if (c != BLANK && c != 'V') {
				token += c;
				state = ParseStates::BATTERY_VOLTAGE;
			}
			else if (c == 'V'){
				sz = token.length();
				data.battery_voltage = std::stof(token, &sz);
				complete_token = true;
				state = ParseStates::SEPERATOR;
			}
			break;
		case ParseStates::NODE_ID_FILLER:
			if (c == ':') {
				state = ParseStates::NODE_ID;
			}
			else {
				state = ParseStates::NODE_ID_FILLER;
			}
			break;
		case ParseStates::NODE_ID:
			if (c >= '0' && c <= '9') {
				token += c;
				state = ParseStates::NODE_ID;
				toggle_for_node = 1;
			}
			else if (c == '\n' && toggle_for_node) {
				token = "NODE: " + token;
				data.node_id = token;
				complete_token = true;
				state = ParseStates::SEPERATOR;
			}
			break;
		default:
			break;
		}
		if (complete_token) {
			cout << "\t\ttoken: \"" << token << '"' << endl;
			token.erase();
			complete_token = false;
		}
	}
	return data;
}