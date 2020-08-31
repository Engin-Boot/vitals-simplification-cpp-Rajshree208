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


struct VitalParameters
{
	const int total_no_vitals;
	string vital_names[5];
	float vital_values[5];
};


const int vitalLimits[5][2] = { {70,150},{90,INT_MAX},{30,95},{60,150},{90,120} };

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

	bool vitalsAreOk(Alert* alert, struct VitalParameters* p) {
		int countOfTrueValues = 0;
		bool vitalStatus;
		for(int i = 0; i< p->total_no_vitals; i++)
		{
			vitalStatus = vitalsIsOk(alert, p->vital_names[i], p->vital_values[i], vitalLimits[i][0], vitalLimits[i][1]);
			if(vitalStatus==1)
			{
				countOfTrueValues++;
			}
		}
		return (countOfTrueValues == p->total_no_vitals);
	}
};

int main() {

	AlertWithSms alertSms;
	AlertWithAlarm alertAlarm;
	VitalsCheck checkVitals;
	
	VitalParameters patient1 = {5, { "BPM", "SPO2", "RESPIRATORY","BLOODPRESSURE","HEARTRATE" },{40,89,100,50,130}};
	VitalParameters patient2 = { 5, { "BPM", "SPO2", "RESPIRATORY","BLOODPRESSURE","HEARTRATE" },{160,49,90,120,100} };

	checkVitals.vitalsAreOk(&alertSms,&patient1);
	checkVitals.vitalsAreOk(&alertAlarm,&patient2);
}
