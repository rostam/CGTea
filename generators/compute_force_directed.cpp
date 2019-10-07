//
// Created by rostam on 07.10.19.
//

#include <boost/graph/fruchterman_reingold.hpp>
#include <boost/graph/random_layout.hpp>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/topology.hpp>
#include <boost/lexical_cast.hpp>
#include <string>
#include <iostream>
#include <map>
#include <vector>
#include <boost/random/linear_congruential.hpp>
#include <boost/progress.hpp>
#include <boost/shared_ptr.hpp>
#include "../datatypes.h"
#include "compute_force_directed.h"

using namespace boost;
typedef boost::rectangle_topology<> topology_type;
typedef topology_type::point_type point_type;
typedef graph_traits<Graph>::vertex_descriptor Vertex;
typedef std::map<std::string, Vertex> NameToVertex;

std::vector<std::pair<double, double>> compute_force_directed(double width, double height, Graph& g)
{
    int iterations = 100;
    NameToVertex names;

    typedef std::vector<point_type> PositionVec;
    PositionVec position_vec(num_vertices(g));
    typedef iterator_property_map<PositionVec::iterator,
            property_map<Graph, vertex_index_t>::type>
            PositionMap;
    PositionMap position(position_vec.begin(), get(vertex_index, g));

    boost::minstd_rand gen;
    topology_type topo(gen, -width/2, -height/2, width/2, height/2);
    random_graph_layout(g, position, topo);
    fruchterman_reingold_force_directed_layout(g, position, topo);

    graph_traits<Graph>::vertex_iterator vi, vi_end;
    std::vector<std::pair<double, double>> ret;
    for (boost::tie(vi, vi_end) = vertices(g); vi != vi_end; ++vi) {
        ret.push_back(pair(position[*vi][0], position[*vi][1]));
    }
    return ret;
}
