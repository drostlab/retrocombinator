#include "../simulation.h"

#include <iostream>
using namespace retrocombinator;
using namespace std;

int main() {

    try
    {

        Simulation simulation(
            std::string(), 1000, 1000,
            /* ActivityTracker */ 200, 0.1,
            /* Mutator */ "TN93",
            /* Burst */ 0.5, 5, 10,
            /* Recomb */ 3, 0.8,
            /* Select */ 0.5,
            /* Timesteps */ 100, 0.001
        );
        simulation.simulate();
    }
    catch (Exception e)
    {
        std::cout << e.what() << std::endl;
        return 1;
    }
    return 0;
}
