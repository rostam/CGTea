//
// Created by rostam on 03.07.20.
//

#include "ConjectureCheck.h"
#include "../G6Format/G6Format.h"
#include <fstream>
#include "../reports/Utils.h"


void ConjectureCheck::CheckSaveToFile(ConjectureType ct, std::unique_ptr<ReportInterface> r, std::string input_file_name,
                                 std::string output_file_name) {
    switch (ct) {
        case All:
            std::ifstream file(input_file_name);
            std::ofstream outfile(output_file_name);
            std::string str;
            G6Format g6Format;
            int cnt = 0;
            Utils::write_csv_line(outfile,{"count","g6",r->name()});
            while (std::getline(file, str)) {
                cnt++;
                Graph g = g6Format.stringToGraph(str);
                Utils::write_csv_line(outfile,{std::to_string(cnt),  str , r->report(g)});
            }
            outfile.close();
            break;
    }
}

std::map<std::string, vector<std::string>>
ConjectureCheck::CheckReturn(ConjectureType ct, std::unique_ptr<ReportInterface> r, std::string input_file_name) {
    std::map<std::string, vector<std::string>> returnTable;
    switch (ct) {
        case All:
            std::ifstream file(input_file_name);
            std::string str;
            G6Format g6Format;
            returnTable[r->name()] = vector<std::string>();
            while (std::getline(file, str)) {
                Graph g = g6Format.stringToGraph(str);
                string result = r->report(g);
                returnTable[r->name()].emplace_back(result);
            }
            break;
    }
    return returnTable;
}
