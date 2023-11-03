 
//
// Created by rostam on 10.10.19.
//

#ifndef CGTEA_DIAMETER_H
#define CGTEA_DIAMETER_H

#include "ReportInterface.h"
#include "Utils.h"

class GraphDiameter : public ReportInterface {
public:
    /**
     * Computes the diameter of graph
     * The edges weights should be initialized to 1
     *
     * @param g
     * @return
     */
    string report(const Graph& g) override;

    string name() const override {
        return "Graph Diameter";
    };
    string description() const override {
        return "Graph Diameter";
    };
    string type() const override {
        return "int";
    };
    string category() const override {
        return "General";
    };
};

#endif //CGTEA_DIAMETER_H
