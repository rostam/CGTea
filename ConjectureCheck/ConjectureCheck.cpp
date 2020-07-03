//
// Created by rostam on 03.07.20.
//

#include "ConjectureCheck.h"
#include "../G6Format/G6Format.h"
#include <fstream>
#include "../reports/Utils.h"


void ConjectureCheck::CheckSaveToFile(ConjectureType ct, std::vector<std::unique_ptr<ReportInterface>>& rs,
        std::string input_file_name, std::string output_file_name) {
    switch (ct) {
        case All:
            std::ifstream file(input_file_name);
            std::ofstream outfile(output_file_name);
            std::string str;
            G6Format g6Format;
            int cnt = 0;
            vector<std::string> keysRow{"count","g6"};
            for(auto& r : rs) keysRow.emplace_back(r->name());
            Utils::write_csv_line(outfile,std::move(keysRow));
            while (std::getline(file, str)) {
                cnt++;
                Graph g = g6Format.stringToGraph(str);
                vector<std::string> result_row;
                result_row.emplace_back(std::to_string(cnt));
                result_row.emplace_back(str);
                for(auto& r : rs) {
                    result_row.emplace_back(r->report(g));
                }
                Utils::write_csv_line(outfile, std::move(result_row));
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
