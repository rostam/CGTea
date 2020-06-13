//
// Created by rostam on 18.10.19.
//

#ifndef CGTEA_ACTIONINTERFACE_H
#define CGTEA_ACTIONINTERFACE_H

#include "../datatypes.h"

class ActionInterface {
public:
    virtual Graph action(Graph g) = 0;
    virtual string name() const = 0;
    virtual string description() const = 0;
};

#endif //CGTEA_ACTIONINTERFACE_H
