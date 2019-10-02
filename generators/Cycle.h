/**
 * Created by rostami on 28.06.17.
 */
#ifndef EXACT_COLORING_CYCLE_H
#define EXACT_COLORING_CYCLE_H

#include "GeneratorInterface.h"

class Cycle : public GeneratorInterface {
public:
    Cycle(int n) : GeneratorInterface(n) {};
    Graph generate() {
        Graph g;
        for (int i = 0; i < n; i++)
            add_edge(i, ((i + 1) % n),g);
        return g;
    }
};

#endif
