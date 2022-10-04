#ifndef EVENT_H
#define EVENT_H

#include "Fish.h"
#include "config.h"
#include <fstream>
#include <random>

using namespace std;

class Simulation;

class Event {
public:
  Event (unsigned t) : eventTime(t){ }
  virtual ~Event(){}
  virtual void processEvent (Simulation&) = 0;
  virtual void withdrawEvent() = 0;
  const unsigned eventTime;
};

struct EventComparator {
  bool operator() (const Event * left, const Event * right) const {
    return left->eventTime > right->eventTime;
  }
};


class hatchEvent : public Event {
    mt19937& generator;
public:
  hatchEvent (unsigned t, mt19937& gen) : Event(t), generator(gen) {}
  virtual void processEvent (Simulation& sim);
  virtual void withdrawEvent(){}
};

class spawnEvent : public Event {
  Fish* afish;
  mt19937& generator;
public:
  spawnEvent (unsigned t, Fish* _afish, mt19937& gen) : Event(t), afish(_afish), generator(gen){}
  virtual void processEvent (Simulation& sim);
  virtual void withdrawEvent();
};

class matureEvent : public Event {
  Fish* afish;
  mt19937& generator;
public:
  matureEvent (unsigned t, Fish* _afish, mt19937& gen) : Event(t), afish(_afish),generator(gen){}
  virtual void processEvent (Simulation& sim);
  virtual void withdrawEvent();
};


class deathEvent : public Event {
  Fish* afish;
public:
  deathEvent (unsigned t, Fish* _afish) : Event(t), afish(_afish) {}
  virtual void processEvent (Simulation& sim);
  virtual void withdrawEvent();
};

class harvestEvent : public Event {
    mt19937& generator;
public:
  harvestEvent (unsigned t, mt19937& gen): Event(t), generator(gen) {}
  virtual void processEvent (Simulation& sim);
  virtual void withdrawEvent() {}
};

class printEvent : public Event {
    ofstream& file;
public:
  printEvent (unsigned t, ofstream& f) : Event(t), file(f){}
  virtual void processEvent (Simulation& sim);
  virtual void withdrawEvent() {}
};

#endif // EVENT_H
