//
// Created by rostam on 05.07.20.
//

#ifndef CGTEA_LINEGRAPH_H
#define CGTEA_LINEGRAPH_H

#include "../datatypes.h"
#include "ActionInterface.h"

class LineGraph : public ActionInterface {
public:
    Graph action(Graph g) override;

    string name() const override {
        return "Line Graph";
    }

    string description() const override {
        return "Line Graph";
    }

    std::map <Edge, Ver> EdgeToVertexMapper;
    std::map <Ver, Edge> VertexToEdgeMapper;
};


#endif //CGTEA_LINEGRAPH_H
