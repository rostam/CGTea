 
//
// Created by rostam on 10.10.19.
//

#ifndef CGTEA_GIRTHSIZE_H
#define CGTEA_GIRTHSIZE_H

#include "ReportInterface.h"

class GraphGirthSize : public ReportInterface {

public:
    string report(const Graph& g) override;
    string name() const override {
        return "Graph Girth Size";
    };
    string description() const override {
        return "Graph Girth Size";
    };
    string type() const override {
        return "int";
    };
    string category() const override {
        return "General";
    };
};

#endif //CGTEA_GIRTHSIZE_H
