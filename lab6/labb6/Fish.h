#ifndef FISH_H
#define FISH_H

#include "config.h"
#include <string>

class Fish {

public:
  enum Phase {JuvenilePhase, AdultPhase, DeadPhase, CaughtPhase};
  Phase phase=JuvenilePhase;

  unsigned hatchedTime=0;
  unsigned adultTime=0;
  unsigned lifeExpectancy=0;
  unsigned id = 0;
  static unsigned counter;



public:
  Fish(unsigned time, unsigned _lifeExpectancy);

  void makeAdult(unsigned);
  void makeDead();
  void makeCaught();


  bool isJuvenile() const;
  bool isAdult()const;
  bool isCaught()const;
  bool isDead()const;



  std::string print()const;

  bool catchableNow(unsigned)const;
  unsigned getWeightOnCatch(unsigned tm)const;
  unsigned getRemainingLifeExpectancy(unsigned tm)const;
};

std::ostream& operator<<(std::ostream& out, const Fish& fish);

#endif // FISH_H
