#include "Fish.h"
#include <sstream>
#include <cassert>

unsigned Fish::counter= 0;

Fish::Fish(unsigned time, unsigned _lifeExpectancy):
  hatchedTime(time),lifeExpectancy(_lifeExpectancy), id(++counter){
}

void Fish::makeAdult(unsigned t){
  assert(phase==JuvenilePhase && " making a non juvenile fish adult");
  adultTime = t;
  phase = AdultPhase;
}

void Fish::makeDead(){
  bool aliveFree = isJuvenile() || isAdult();
  assert(aliveFree && " killing a dead or caught fish");
  phase = DeadPhase;
}

void Fish::makeCaught(){
  bool aliveFree = isJuvenile() || isAdult();
  assert(aliveFree && " catching a dead or caught fish");
  phase = CaughtPhase;
}


bool Fish::isJuvenile()const{
  return phase == JuvenilePhase;
}

bool Fish::isAdult()const{
  return phase == AdultPhase;
}

bool Fish::isCaught()const{
  return phase == CaughtPhase;
}

bool Fish::isDead()const{
  return phase == DeadPhase;
}

unsigned Fish::getRemainingLifeExpectancy(unsigned now)const{
    if (now > (lifeExpectancy + hatchedTime))
        return 0;
    return lifeExpectancy + hatchedTime - now;
}

bool Fish::catchableNow(unsigned now)const{
  return (now - hatchedTime) > MIN_CATCHABLE_AGE;
}


unsigned Fish::getWeightOnCatch(unsigned tm)const{
  unsigned age = tm - hatchedTime;
  return(age < MIN_KEPT_AGE? 0 : age);
}

std::string Fish::print()const{
    std::stringstream rslt;
    rslt << "fish";
    switch(phase){
    case JuvenilePhase:
        rslt << "j(";
        break;
    case AdultPhase:
        rslt << "a(";
        break;
    case DeadPhase:
        rslt << "d(";
        break;
    case CaughtPhase:
        rslt << "c(";
        break;
    default:
        rslt << "x(";
        break;
    }
  rslt << id << ")(le=" << lifeExpectancy;
  rslt << ", ht=" << hatchedTime;
  rslt << ", at=" << adultTime << ")" ;
  return rslt.str();
}


std::ostream& operator<<(std::ostream& out, const Fish& fish){
    out << fish.print();
    return out;
}
