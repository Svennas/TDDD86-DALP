#ifndef CONFIG_H
#define CONFIG_H

//life expectancy
const unsigned MAX_AGE = 2000;
const unsigned STARVE_THRESHOLD=20000;

const  unsigned HATCH_TM = 40;
const  unsigned AVG_MATURATION_TM = 500;

// spawning
const  unsigned MAX_AVG_EGGS_NUM = 100;
const double MIN_SPAWN_CONC = 0.05;
const unsigned SPAWN_THRESHOLD= 0.05 * STARVE_THRESHOLD;


// Harvesting
const unsigned HARVEST_START= 1000;
const unsigned HARVEST_PERIOD= 366;
const unsigned MIN_CATCHABLE_AGE = 550;
const unsigned MIN_KEPT_AGE = 600;
const unsigned LANDING = 70000;

// Simulation: duration and printing
const unsigned SIMULATION_HORIZON=8000;
const unsigned PRINT_PERIOD=20;


#endif // CONFIG_H
