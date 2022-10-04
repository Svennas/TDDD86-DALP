#include "Simulation.h"
#include <algorithm>
#include <cassert>

#include <iostream>


Simulation::Simulation():
    simulationTime(0),eggPopulation(0),
    juvenilePopulation(0),adultPopulation(0){
}


Simulation::~Simulation(){
    assert(eventQueue.empty());
    for(unsigned i=0; i < allTheFish.size(); ++i){
        assert(! allTheFish[i]->isCaught());
        delete allTheFish[i];
    }
}



void Simulation::run (){
    while (! eventQueue.empty ()){
        Event * nextEvent = eventQueue.top ();
        eventQueue.pop ();
        if(simulationTime < SIMULATION_HORIZON){
            simulationTime = nextEvent->eventTime;
            nextEvent->processEvent(*this);
        }else{
            nextEvent->withdrawEvent();
        }
        delete nextEvent;
    }
}


void Simulation::scheduleEvent (Event * newEvent){
    eventQueue.push(newEvent);
}


void Simulation::harvestTonnageNow(unsigned target,  mt19937& generator){
//    MyVector<Fish*> stillAlive;
    std::vector<Fish*> stillAlive;
    for(unsigned i=0; i < allTheFish.size(); ++i){
        assert(! allTheFish[i]->isCaught());
        if (allTheFish[i]->isDead()){
            delete allTheFish[i];
        } else{
            stillAlive.push_back(allTheFish[i]);
        }
    }
    allTheFish.clear();
    shuffle(stillAlive.begin(),stillAlive.end(),generator);
    unsigned landing =0;
    unsigned fish=0;
    for(; fish < stillAlive.size() && landing < target; ++fish){
        if(stillAlive[fish]->catchableNow(simulationTime)){
            //fish is large enough to be caught
            landing += stillAlive[fish]->getWeightOnCatch(simulationTime);
            if(stillAlive[fish]->isJuvenile()){
                juvenilePopulation--;
            }else if(stillAlive[fish]->isAdult()){
                adultPopulation--;
            }else{
                assert(false && "should not get here");
            }
            stillAlive[fish]->makeCaught();
        }else{
            allTheFish.push_back(stillAlive[fish]);
        }
    }
    for(; fish < stillAlive.size(); ++fish){
        allTheFish.push_back(stillAlive[fish]);
    }
}

void Simulation::addFish(Fish* afish){
    allTheFish.push_back(afish);
}

unsigned Simulation::getEggPopulation()const{
    return eggPopulation;
}

void Simulation::incEggPopulation(unsigned c){
    eggPopulation+=c;
}

void Simulation::decEggPopulation(unsigned c){
    eggPopulation-=c;
}

unsigned Simulation::getJuvenilePopulation()const{
    return juvenilePopulation;
}

void Simulation::incJuvenilePopulation(unsigned c){
    juvenilePopulation+=c;
}

void Simulation::decJuvenilePopulation(unsigned c){
    juvenilePopulation-=c;
}

unsigned Simulation::getAdultPopulation()const{
    return adultPopulation;
}

void Simulation::incAdultPopulation(unsigned c){
    adultPopulation+=c;
}

void Simulation::decAdultPopulation(unsigned c){
    adultPopulation-=c;
}


