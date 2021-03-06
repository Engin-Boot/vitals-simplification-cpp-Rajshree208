#include <assert.h>
#include <climits>
#include <string>
#include <iostream>
#include <map>
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

std::map<string, int> map_lowerlimit = {
	{ "BPM", 70 },
	{ "SPO2", 90 },
	{ "RESPIRATORY", 30},
	{"BLOODPRESSURE",60 },
	{"HEARTRATE",90 }
};
std::map<string, int> map_upperlimit = {
	{ "BPM", 150 },
	{ "SPO2", INT_MAX },
	{ "RESPIRATORY", 95},
	{"BLOODPRESSURE",150 },
	{"HEARTRATE", 120 }
};

class VitalParameters
{
public:
	int total_no_vitals;
	int* a = NULL;  
	string* vital_names = NULL;
	float* vital_values = NULL;
	VitalParameters(int t, string* vitalNames, float* vitalValues) {
		total_no_vitals = t;
		a = new int[total_no_vitals];
		vital_names = new string[total_no_vitals];
		vital_values = new float[total_no_vitals];
		copy(vitalNames,vitalNames+t,vital_names);
		copy(vitalValues, vitalValues + t, vital_values);
	}
};

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

	bool vitalsAreOk(Alert* alert, VitalParameters* p) {
		int countOfTrueValues = 0;
		bool vitalStatus;
		for(int i = 0; i< p->total_no_vitals; i++)
		{
			string vitalname = p->vital_names[i];
			vitalStatus = vitalsIsOk(alert, p->vital_names[i], p->vital_values[i], map_lowerlimit[vitalname], map_upperlimit[vitalname]);
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
	
	string vitalNames1[] = { "BPM", "RESPIRATORY","SPO2" ,"BLOODPRESSURE","HEARTRATE" };
	float vitalValues1[] = { 40,89,99,50,130 };

	VitalParameters vitalsForPatient1(5,vitalNames1 , vitalValues1);

	string vitalNames2[] = { "BPM", "SPO2", "RESPIRATORY" };
	float vitalValues2[] = { 80,90,45 };

	VitalParameters vitalsForPatient2(3, vitalNames2, vitalValues2);

	checkVitals.vitalsAreOk(&alertSms,&vitalsForPatient1);
	checkVitals.vitalsAreOk(&alertAlarm,&vitalsForPatient2);
}
