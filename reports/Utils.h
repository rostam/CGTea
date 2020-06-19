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

    static std::variant<int, double, std::string> return_value(std::string value, std::string type) {
        if(type =="int")
            return std::stoi( value );
        else if(type =="double")
            return std::stod( value ),"";
        else
            return value;
    }
};


#endif //CGTEA_UTILS_H
