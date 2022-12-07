#include "Event.h"
#include "Simulation.h"
#include <iostream>
#include <cassert>

void hatchEvent::processEvent (Simulation& sim) {
  double total = sim.getJuvenilePopulation() + sim.getAdultPopulation();
  double saturation = min(total/STARVE_THRESHOLD, 1.0);
  unsigned ageAverage = MAX_AGE * (1 - saturation);
  uniform_int_distribution<int> ageDist(0.1 * ageAverage, 1.9 * ageAverage);
  unsigned ageExpectancy = ageDist(generator);

  Fish* afish = new Fish(eventTime, ageExpectancy);
  sim.decEggPopulation();
  sim.incJuvenilePopulation();
  sim.addFish(afish);

  uniform_int_distribution<int> juvDist(0.8* AVG_MATURATION_TM, 1.2* AVG_MATURATION_TM);
  unsigned juvenileFor = juvDist(generator);

  if( ageExpectancy < juvenileFor){
    sim.scheduleEvent(new deathEvent(eventTime + ageExpectancy, afish));
  }else{
    sim.scheduleEvent(new matureEvent(eventTime + juvenileFor, afish, generator));
  }
}


void spawnEvent::processEvent (Simulation& sim) {
  if(afish->isCaught()){
    delete afish;
    afish = nullptr;
    return;
  }
  double concentration = min(sim.getAdultPopulation() / (double)SPAWN_THRESHOLD, 1.0);
  unsigned avg_max_egg_num =
          (concentration < MIN_SPAWN_CONC ? 0 : concentration * MAX_AVG_EGGS_NUM);
  uniform_int_distribution<int> eggDist(0.8 * avg_max_egg_num, 1.2 * avg_max_egg_num);
  unsigned eggs_num = eggDist(generator);

  sim.incEggPopulation(eggs_num);

  uniform_int_distribution<int> hatchDist(0.6 * HATCH_TM, 1.4 * HATCH_TM);
  for(unsigned e=0; e < eggs_num; e++){
    unsigned hatchIn = hatchDist(generator);
    sim.scheduleEvent(new hatchEvent(eventTime + hatchIn, generator));
  }
  unsigned nextSeasonIn = round((eventTime + 365)/(double)365)*365 - eventTime;
  uniform_int_distribution<int> spawnDist(nextSeasonIn - 30, nextSeasonIn + 30);
  unsigned spawningIn = spawnDist(generator);

  if(afish->getRemainingLifeExpectancy(eventTime) < spawningIn){
    sim.scheduleEvent(new deathEvent(eventTime + afish->getRemainingLifeExpectancy(eventTime), afish));
  }else{
    sim.scheduleEvent(new spawnEvent(eventTime + spawningIn, afish, generator));
  }
}

void spawnEvent::withdrawEvent () {
    if(afish->isCaught()){
        delete afish;
        afish = nullptr;
    }
}


void matureEvent::processEvent (Simulation& sim) {
    if(afish->isCaught()){
    delete afish;
    afish = nullptr;
    return;
  }
  afish->makeAdult(eventTime);
  sim.decJuvenilePopulation();
  sim.incAdultPopulation();

  unsigned nextSeasonIn = round((eventTime + 365)/(double)365)*365 - eventTime;
  uniform_int_distribution<int> spawnDist(nextSeasonIn - 30, nextSeasonIn + 30);
  unsigned spawningIn = spawnDist(generator);

  if(afish->getRemainingLifeExpectancy(eventTime) < spawningIn)
    sim.scheduleEvent(new deathEvent(eventTime + afish->getRemainingLifeExpectancy(eventTime), afish));
  else
    sim.scheduleEvent(new spawnEvent(eventTime + spawningIn, afish, generator));
}

void matureEvent::withdrawEvent () {
    if(afish->isCaught()){
        delete afish;
        afish= nullptr;
    }
}

void deathEvent::processEvent (Simulation& sim){
    if(afish->isCaught()){
    delete afish;
    afish = nullptr;
    return;
  }
  if(afish->isJuvenile()){
      sim.decJuvenilePopulation();
  } else if(afish->isAdult()) {
      sim.decAdultPopulation();
  }
  afish->makeDead();
}

void deathEvent::withdrawEvent (){
    if(afish->isCaught()){
        delete afish;
        afish=nullptr;
    }
}

void harvestEvent::processEvent (Simulation& sim) {
  sim.harvestTonnageNow(LANDING,generator);
  sim.scheduleEvent(new harvestEvent(eventTime + HARVEST_PERIOD, generator));
}

void printEvent::processEvent (Simulation& sim) {
  file << eventTime
        << '\t' << sim.getEggPopulation()
        << '\t' << sim.getJuvenilePopulation()
        << '\t' << sim.getAdultPopulation()
        << '\t' << sim.getJuvenilePopulation() + sim.getAdultPopulation()
        << endl;

  cout << eventTime
        << '\t' << sim.getEggPopulation()
        << '\t' << sim.getJuvenilePopulation()
        << '\t' << sim.getAdultPopulation()
        << '\t' << sim.getJuvenilePopulation() + sim.getAdultPopulation()
        << endl;

  sim.scheduleEvent(new printEvent(eventTime + PRINT_PERIOD, file));
}
