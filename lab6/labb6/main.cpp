
#include "Event.h"
#include "Fish.h"
#include "Simulation.h"

#include <fstream>
#include <iostream>
#include <random>
#include <string>
#include <chrono>


using namespace std;


void show();

int main()
{
    ofstream file("output.dat");

    random_device rd;
    mt19937 generator(rd());


    Simulation sim;
    sim.scheduleEvent(new printEvent (0,file));
    for(unsigned i=0; i < 100; ++i){
      Event* e = new hatchEvent(0,generator);
      sim.scheduleEvent(e);
    }
    sim.incEggPopulation(100);
    sim.scheduleEvent(new harvestEvent(HARVEST_START,generator));
    auto comp_start_time = chrono::high_resolution_clock::now();
    sim.run();
    auto comp_end_time = chrono::high_resolution_clock::now();
    std::cout << "simulation took: "
              << chrono::duration_cast<chrono::seconds>(comp_end_time - comp_start_time).count()
              << " seconds."
              << std::endl;
    file.close();

    show();

    return 0;
}

void show(){
    ofstream driver;
    driver.open("output.driver", ofstream::out);
    driver << "set terminal wxt size 410,250 enhanced font 'Verdana,9' persist\n"
           << "set style line 11 lc rgb '#808080' lt 1\n"
           << "set border 3 back ls 11\n"
           << "set tics nomirror \n"
           << "set style line 12 lc rgb '#808080' lt 0 lw 1\n"
           << "set grid back ls 12\n"
           << "set style line 1 lc rgb '#000000' pt 0 ps 1 lt 1 lw 1 # --- red\n"
           << "set style line 2 lc rgb '#5e9c36' pt 0 ps 1 lt 1 lw 1 # --- green\n"
           << "set style line 3 lc rgb '#0000ff' pt 0 ps 1 lt 1 lw 1 # --- blue\n"
           << "set style line 4 lc rgb '#99004c' pt 0 ps 1 lt 1 lw 1 # --- purple\n"
           << "set key top left\n"
           << "set xlabel 'time in days'\n"
           << "set ylabel 'population'\n"
           << "set xrange [0:" << SIMULATION_HORIZON <<"]\n"
           << "set yrange [0:" << int(STARVE_THRESHOLD * 1.3) << "]\n"
           << "plot  'output.dat' u 1:3 t 'juvenile' w lp ls 2, \\\n"
           << "      'output.dat' u 1:4 t 'adult' w lp ls 3";
    driver.close();

#ifdef WIN32
    const string exe = "C:\\Progra~1\\gnuplot\\bin\\gnuplot.exe";
#else
    const string exe = "gnuplot";
#endif
    const string cmd = exe + " " + "output.driver";
    system(cmd.c_str());
}
