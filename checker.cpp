#include <assert.h>
#include <climits>
#include <string>
#include <iostream>
using namespace std;

const int bpmlimits[] = { 70,150 };
const int spo2min = 90;
const int resplimits[] = { 30,95 };
const std::string vitalNames[] = { "BPM", "SPO2", "RESPIRATORY" };

class Alert
{
public:
	virtual void sendAlert(const string, const string) = 0;
};

class AlertWithSms :public Alert 
{
public:
	void sendAlert(string vitalName, string message) override
	{
		cout << "Alert using SMS" << "-->" << vitalName << " " << message << endl;
	}
};

class AlertWithAlarm : public Alert
{
public:
	void sendAlert(string vitalName, string message) override
	{
		cout << "Alert using Alarm" << "-->" << vitalName << " " << message << endl;
	}
};

class VitalsCheck
{
public:

	bool vitalsIsOk(Alert* alert, string vitalName, float value, int lower, int upper) {

		if (value < lower)
		{
			//std::cout << vitalName << "-->" << value << " is lower than the expected lower value -->" << lower << std::endl;
			string message = "IS LOW !!";
			alert->sendAlert(vitalName, message);
			return false;
		}
		if (value > upper)
		{
			//std::cout << vitalName << "-->" << value << " is higher than the expected upper value -->" << upper << std::endl;
			string message = "IS HIGH !!";
			alert->sendAlert(vitalName, message);
			return false;
		}
		return true;
	}

	bool vitalsAreOk(Alert* alert, float bpm, float spo2, float respRate) {
		int countOfTrueValues = 0;
		const int total_no_of_parameters = 3;
		int vitalsStatus[total_no_of_parameters] = { vitalsIsOk(alert ,vitalNames[0],bpm, bpmlimits[0],bpmlimits[1]),
							     vitalsIsOk(alert,vitalNames[1],spo2,spo2min,INT_MAX),
		     					     vitalsIsOk(alert,vitalNames[2],respRate, resplimits[0],resplimits[1]) };

		for (int i = 0; i < total_no_of_parameters; i++) {
			if (vitalsStatus[i] == 1) {
				countOfTrueValues++;
			}
		}
		return (countOfTrueValues == total_no_of_parameters);
	}
};


int main() {
	Alert* alert;
	AlertWithSms alertSms;
	AlertWithAlarm alertAlarm;
	VitalsCheck checkVitals;
	checkVitals.vitalsAreOk(&alertSms,80, 95, 60);
	checkVitals.vitalsAreOk(&alertAlarm,60, 90, 40);
}
