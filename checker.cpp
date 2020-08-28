#include <assert.h>
#include <climits>
#include <string>
#include <iostream>

const int bpmlimits[] = { 70,150 };
const int spo2min = 90;
const int resplimits[] = { 30,95 };
const std::string vitalNames[] = { "BPM", "SPO2", "RESPIRATORY" };

bool vitalsIsOk(std::string vitalName,float value, int lower, int upper) {
    if(value<lower)
    {
		std::cout << vitalName << "-->" << value << " is lower than the expected lower value -->" << lower << std::endl;
		return false;
    }
	if(value>upper)
	{
		std::cout << vitalName << "-->" << value << " is higher than the expected upper value -->" << upper << std::endl;
		return false;
	}
	return true;
}

bool vitalsAreOk(float bpm, float spo2, float respRate) {
	int countOfTrueValues = 0;
	const int total_no_of_parameters = 3;
	int vitalsStatus[total_no_of_parameters] = { vitalsIsOk(vitalNames[0],bpm, bpmlimits[0],bpmlimits[1]),
						     vitalsIsOk(vitalNames[1],spo2,spo2min,INT_MAX),
						     vitalsIsOk(vitalNames[2],respRate, resplimits[0],resplimits[1]) };

	for (int i = 0; i < total_no_of_parameters; i++) {
		if (vitalsStatus[i] == 1) {
			countOfTrueValues++;
		}
	}
	return (countOfTrueValues == total_no_of_parameters);
}

int main() {
	assert(vitalsAreOk(80, 95, 60) == true);
	assert(vitalsAreOk(60, 90, 40) == false);
	assert(vitalsIsOk("BPM",60, 70, 150) == false);
	assert(vitalsIsOk("SPO2",200, 90, 150) == false);
	assert(vitalsIsOk("RESPIRATORY",85, 70, 150) == true);
}
