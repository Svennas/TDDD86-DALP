#ifndef SIMULATION_H
#define SIMULATION_H

#include "config.h"
#include "Event.h"
#include "MyPriorityQueue.h"
#include "MyVector.h"
#include <random>
#include <vector>
#include <queue>

class Fish;

class Simulation {

public:
  Simulation();

  ~Simulation();

  void run ();

  void scheduleEvent (Event*);

  void harvestTonnageNow(unsigned, mt19937&);

  void addFish(Fish*);

  unsigned getEggPopulation()const;
  void incEggPopulation(unsigned c=1);
  void decEggPopulation(unsigned c=1);

  unsigned getJuvenilePopulation()const;
  void incJuvenilePopulation(unsigned c=1);
  void decJuvenilePopulation(unsigned c=1);

  unsigned getAdultPopulation()const;
  void incAdultPopulation(unsigned c=1);
  void decAdultPopulation(unsigned c=1);


private:
//  MyPriorityQueue<Event*, EventComparator> eventQueue;

  std::priority_queue<Event*,
                      vector<Event *, allocator<Event*> >,
                      EventComparator> eventQueue;

  MyVector<Fish*> allTheFish;
  //std::vector<Fish*> allTheFish;


  unsigned simulationTime;

  unsigned eggPopulation;
  unsigned juvenilePopulation;
  unsigned adultPopulation;



};

#endif // SIMULATION_H
