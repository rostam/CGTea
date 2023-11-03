 
//
// Created by rostam on 10.10.19.
//

#ifndef CGTEA_PERIPHERALWIENERINDEX_H
#define CGTEA_PERIPHERALWIENERINDEX_H

#include "ReportInterface.h"

class Peripheralwienerindex : public ReportInterface {
public:
    string report(const Graph& g) override {
        int n = boost::num_edges(g);
        return std::to_string(n);
    };
    string name() const override {
        return "Peripheral wiener index";
    };
    string description() const override {
        return "Peripheral wiener index";
    };
    string type() const override {
        return "int";
    };
    string category() const override {
        return "OurWorks-Conjectures";
    };
};

#endif //CGTEA_PERIPHERALWIENERINDEX_H
