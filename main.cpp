#include "Simulation.h"

int main() {
    poler::market::Simulation sim{3, 2, 3};
    sim.run(5000);
    return 0;
}
