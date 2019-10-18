//
// Created by rostam on 18.10.19.
//

#ifndef CGTEA_ACTIONINTERFACE_H
#define CGTEA_ACTIONINTERFACE_H

#include "../datatypes.h"

class ActionInterface {
public:
    virtual Graph action(Graph g) {
        return g;
    }

    virtual string name() {return "Action Interface";};
    virtual string description() {return "Action Interface";};
};

#endif //CGTEA_ACTIONINTERFACE_H
