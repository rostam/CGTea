//
// Created by rostam on 11.06.20.
//

#ifndef CGTEA_UTILS_H
#define CGTEA_UTILS_H

#include "../datatypes.h"
#include <variant>
#include <boost/graph/floyd_warshall_shortest.hpp>

class Utils {
public:
    /**
     * returns all pairs shortest paths between vertices
     * @param g the given graph
     * @return the distances arrays
     */
    static DistanceMatrix get_floyd_warshall_all_pairs_shortest_paths(const Graph& g) {
        DistanceMatrix distances(num_vertices(g));
        DistanceMatrixMap dm(distances, g);
        boost::floyd_warshall_all_pairs_shortest_paths(g,dm);
        return distances;
    }

    static std::variant<int, double, std::string> return_value(const std::string& value, const std::string& type) {
        if(type =="int")
            return std::stoi( value );
        else if(type =="double")
            return std::stod( value ),"";
        else
            return value;
    }

    static void write_csv_line(std::ofstream& outfile, vector<string>&& v) {
        for(int i=0;i < v.size();i++) {
            outfile << v[i];
            if(i != v.size() - 1) outfile << ",";
            else outfile << "\n";
        }
    }
};


#endif //CGTEA_UTILS_H
