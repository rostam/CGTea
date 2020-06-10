 
//
// Created by rostam on 10.10.19.
//

#ifndef CGTEA_PERIPHERALVERTICESCOUNT.JAVA_H
#define CGTEA_PERIPHERALVERTICESCOUNT.JAVA_H

#include "ReportInterface.h"

class Peripheralverticescount : public ReportInterface {
public:
    string report(const Graph& g) override {
        int n = boost::num_edges(g);
        return std::to_string(n);
    };
    string name() override {
        return "Peripheral vertices count";
    };
    string description() override {
        return "Peripheral vertices count";
    };
    string type() override {
        return "int";
    };
    string category() override {
        return "OurWorks-Conjectures";
    };
};

#endif //CGTEA_PERIPHERALVERTICESCOUNT.JAVA_H
