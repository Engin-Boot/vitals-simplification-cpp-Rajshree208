#include <assert.h>

bool bpmIsOk(float bpm){
return (bpm<70 && bpm>150);
}
bool spo2IsOk(float spo2){
return (spo2>90);
}
bool respIsOk(float resp){
return (resp>30 && resp<95);
}

bool vitalsAreOk(float bpm, float spo2, float respRate) {
  if(bpmIsOK||spo2IsOk||respIsOk) {
    return true;
  }
  return false;
}

int main() {
  assert(vitalsAreOk(80, 95, 60) == true);
  assert(vitalsAreOk(60, 90, 40) == false);
}
