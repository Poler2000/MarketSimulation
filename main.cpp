#include "Simulation.h"

int main() {
    poler::market::Simulation sim{12, 6, 16};
    sim.run(5000);
    return 0;
}
