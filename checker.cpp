#include <assert.h>
#include <climits>

const int bpmlimits[] = {70,150};
const int spo2min = 90;
const int resplimits[]= {30,95};

bool vitalsIsOk(float value, int lower,int upper){
    return (value>=lower && value<=upper);
}

bool vitalsAreOk(float bpm, float spo2, float respRate) {
  return (vitalsIsOk(bpm, bpmlimits[0],bpmlimits[1])&&vitalsIsOk(spo2,spo2min,INT_MAX)&&vitalsIsOk(respRate, resplimits[0],resplimits[1]));
}

int main() {
  assert(vitalsAreOk(80, 95, 60) == true);
  assert(vitalsAreOk(60, 90, 40) == false);
  assert(vitalsIsOk(60, 70, 150) == false);
  assert(vitalsIsOk(60, 90, 10000) == false);
  assert(vitalsIsOk(25, 30, 95) == false);
  assert(vitalsIsOk(85, 70, 150) == true);
  assert(vitalsIsOk(96, 90, 10000) == true);
  assert(vitalsIsOk(46, 30, 95) == true);
}
