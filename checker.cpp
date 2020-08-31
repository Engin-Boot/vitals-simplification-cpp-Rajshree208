#include <assert.h>
#include <climits>
#include <string>
#include <iostream>
using namespace std;

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

const int vitalLimits[3][2] = { {70,150},{90,INT_MAX},{30,95} };

class VitalsCheck
{
public:

	bool vitalsIsOk(Alert* alert, string vitalName, float value, int lower, int upper) {

		if (value < lower)
		{
			string message = "IS LOW !!";
			alert->sendAlert(vitalName, message);
			return false;
		}
		else if (value > upper)
		{
			string message = "IS HIGH !!";
			alert->sendAlert(vitalName, message);
			return false;
		}
		return true;
	}

	bool vitalsAreOk(Alert* alert,float vitalValues[], std::string vitalNames[], int total_no_of_vitals) {
		int countOfTrueValues = 0;
		int vitalsStatus[] = { vitalsIsOk(alert ,vitalNames[0],vitalValues[0], vitalLimits[0][0],vitalLimits[0][1]),
				       vitalsIsOk(alert,vitalNames[1],vitalValues[1],vitalLimits[1][0],vitalLimits[1][1]),
				       vitalsIsOk(alert,vitalNames[2],vitalValues[2], vitalLimits[2][0],vitalLimits[2][1]) };
		for (bool status : vitalsStatus)
		{
			if (status == 1)
				countOfTrueValues++;
		}
		return (countOfTrueValues == total_no_of_vitals);
	}
};

int main() {
	
	AlertWithSms alertSms;
	AlertWithAlarm alertAlarm;
	VitalsCheck checkVitals;

	int total_no_of_vitals = 3;
	float vitalValues[] = {40,85,20};
	std::string vitalNames[] = { "BPM", "SPO2", "RESPIRATORY" };

	checkVitals.vitalsAreOk(&alertSms,vitalValues,vitalNames,total_no_of_vitals);
	checkVitals.vitalsAreOk(&alertAlarm, vitalValues, vitalNames, total_no_of_vitals);
}
