#include "Simulation.h"

int main() {
    poler::market::Simulation sim{1, 1, 1};
    sim.run(3000);
    return 0;
}
