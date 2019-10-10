//
// Created by rostam on 10.10.19.
//

#ifndef CGTEA_NUMOFVERTICES_H
#define CGTEA_NUMOFVERTICES_H

#include "ReportInterface.h"

class NumOfVertices : public ReportInterface{
public:
    virtual string generate(const Graph& g) {
        int n = boost::num_vertices(g);
        return std::to_string(n);
    };
    virtual string name() {
        return "Number of vertices";
    };
    virtual string description() {
        return "Number of vertices";
    };
};

#endif //CGTEA_NUMOFVERTICES_H
