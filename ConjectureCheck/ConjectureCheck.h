//
// Created by rostam on 03.07.20.
//

#ifndef CGTEA_CONJECTURECHECK_H
#define CGTEA_CONJECTURECHECK_H

#include "../datatypes.h"
#include "../reports/ReportInterface.h"

enum ConjectureType {All, Trees};
class ConjectureCheck {
public:
    void CheckSaveToFile(ConjectureType ct, std::vector<std::unique_ptr<ReportInterface>>& rs,
            std::string input_file_name, std::string output_file_name);
    std::map<std::string, vector<std::string>> CheckReturn(ConjectureType ct, std::unique_ptr<ReportInterface> r,
            std::string input_file_name);
};


#endif //CGTEA_CONJECTURECHECK_H
