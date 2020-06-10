 
//
// Created by rostam on 10.10.19.
//

#ifndef CGTEA_PERIPHERALWIENERINDEX.JAVA_H
#define CGTEA_PERIPHERALWIENERINDEX.JAVA_H

#include "ReportInterface.h"

class Peripheralwienerindex : public ReportInterface {
public:
    string report(const Graph& g) override {
        int n = boost::num_edges(g);
        return std::to_string(n);
    };
    string name() override {
        return "Peripheral wiener index";
    };
    string description() override {
        return "Peripheral wiener index";
    };
    string type() override {
        return "int";
    };
    string category() override {
        return "OurWorks-Conjectures";
    };
};

#endif //CGTEA_PERIPHERALWIENERINDEX.JAVA_H
