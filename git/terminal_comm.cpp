// terminal_comm.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "serialPort/arduino/SerialPort.h"
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

string parseText(string field, string &string_data) {
	string token = "";
	int num = 0, num2 = 0;
	int pos_field = 0, pos_val = 0;
	while ((pos_field = string_data.find(field)) != string::npos) {
		token = string_data.substr(pos_field);
		num = token.find(':'); // 13
		num2 = token.find(','); // 26
		token = token.substr(token.find(':') + 3, num2 - num - 4); // skip characters after : and the characters before comma
		return token;
	}
	return token;
}

int main() {
	ifstream inFile;
	string fileName = "test.txt";
	const char *port = "\\\\.\\COM14";
	string val = "";
	string data = "", data_str = "";
	/*char output[MAX_DATA_LENGTH];
	char incomingData[MAX_DATA_LENGTH];*/
	char *charArray = new char[16];
	int num;
	for (int i = 0; i < MAX_DATA_LENGTH; i++) {
		charArray[i] = ' ';
	}
	SerialPort arduino(port);
	/*arduino.writeSerialPort(charArray, MAX_DATA_LENGTH);*/
	//arduino.readSerialPort(output, MAX_DATA_LENGTH);

	inFile.open(fileName);

	if (inFile.is_open()) { // if open
		while (!inFile.eof()) { // send data to serial port char by char
			getline(inFile, data);
			data_str.append(data);
		}
		data = parseText("display_name", data_str);
		copy(data.begin(), data.end(), charArray); // copy source to destination
		arduino.writeSerialPort(charArray, MAX_DATA_LENGTH);
		inFile.close();
	}
	else {
		data = "Can't open file";
		/*charArray = new char[data.size() + 1];*/
		copy(data.begin(), data.end(), charArray); // copy source to destination
		arduino.writeSerialPort(charArray, MAX_DATA_LENGTH);
	}

	delete[] charArray;
	return 0;
}
