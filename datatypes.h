#ifndef DATATYPES_HPP
#define DATATYPES_HPP

#include "boost/config.hpp"
#include "boost/graph/adjacency_list.hpp"
#include "boost/graph/sequential_vertex_coloring.hpp"
#include "boost/cstdlib.hpp"
#include "boost/graph/topology.hpp"
#include <memory>
#include <iostream>
#include <fstream>
#include <boost/dynamic_bitset.hpp>
#include <random>
#include "boost/graph/simple_point.hpp"
#include "generators/point.h"
#include <boost/graph/exterior_property.hpp>

#define printVarNameAndItsValue(x) cout<<"The value of variable "<<(#x)<<" is => "<<x<<"\n"

using namespace std;

using boost::property;
using boost::edge_name;
using boost::edge_weight;
using boost::vertex_color_t;
using boost::edge_weight_t;
using boost::edge_name_t;
using boost::property_map;
using boost::graph_traits;
using boost::vertex_color;
using boost::vertex_distance;

typedef boost::adjacency_list<boost::setS, boost::vecS, boost::undirectedS,
        property<boost::vertex_color_t, int,
        property<boost::vertex_distance_t, cgtea_geometry::Point>>,
        property<boost::edge_weight_t, int,
        property<boost::edge_name_t, string>>> Graph;

typedef boost::graph_traits<Graph>::vertex_iterator V_iter;
typedef boost::graph_traits<Graph>::edge_iterator E_iter;
typedef Graph::vertex_descriptor Ver;
typedef Graph::edge_descriptor Edge;
typedef boost::property_map<Graph, boost::edge_weight_t>::type edge_weight_type;
typedef boost::dynamic_bitset<> dynbit;

//typedef std::vector<boost::square_topology<minstd_rand>::point> PositionVec;
//typedef boost::iterator_property_map<PositionVec::iterator, boost::property_map<Graph, boost::vertex_index_t>::type> PositionMap;

template<typename Lambda>
static void for_each_v(Graph& g, Lambda func) {
    V_iter vi, vi_end;
    tie(vi, vi_end) = vertices(g);
    std::for_each(vi,vi_end,func);
}

template<typename Lambda>
static void for_each_v_const(const Graph& g, Lambda func) {
    V_iter vi, vi_end;
    tie(vi, vi_end) = vertices(g);
    std::for_each(vi,vi_end,func);
}

template<typename Lambda>
static void for_each_e(Graph& g, Lambda func) {
    E_iter ei, ei_end;
    tie(ei, ei_end) = edges(g);
    std::for_each(ei,ei_end,func);
}

template<typename Lambda>
static void for_each_e_const(const Graph& g, Lambda func) {
    E_iter ei, ei_end;
    tie(ei, ei_end) = edges(g);
    std::for_each(ei,ei_end,func);
}

//static string statistics(const Graph& g) {
//    tuple<double,double,double> t = eigen_values(g);
//    string stat = string("Number of vertices:") + to_string( boost::num_vertices(g)) +
//                  string("\nNumber of edges:") + to_string(boost::num_edges(g)) +
//                  string("\nMaximum eigenvalue:" + to_string(std::get<0>(t))) +
//                  string("\nMinimum eigenvalue:" + to_string(std::get<1>(t))) +
//                  string("\nSum of eigenvalues:" + to_string(std::get<2>(t)));
//    return stat;
//}

static auto ge_degree = [](pair<int,int> t1, pair<int,int> t2){return t1.second>=t2.second;};
static auto lt_degree = [](pair<int,int> t1, pair<int,int> t2){return t1.second<t2.second;};

static bool cmp_degrees(pair<int,pair<int,int> > t1, pair<int,pair<int,int> > t2)
{
    if (t1.second.second < t2.second.second) {
        return 1;
    } else if (t1.second.second == t2.second.second && t1.second.first < t2.second.first) {
        return 1;
    } else {
        return 0;
    }
}

static bool mysymmetric = false;

/**
 * \brief Computes the fill-reducing ordering
 *
 * @param g the given simple graph which would be converted to a metis input format
 * @param name the name of the file which is given to metis command
 * @param met_ord the computed ordering in Metis
 */
static void getMetisOrdering(Graph& g, string name, vector<unsigned int>& met_ord) {
    ofstream of;
    of.open(name);
    of << num_vertices(g) << " " << num_edges(g)/2 << endl;
    for (int i = 0; i < num_vertices(g); i++) {
        string tmp = "";
        for (int j = 0; j < num_vertices(g); j++) {
            if (edge(i, j, g).second) {
                tmp += to_string(j + 1) + " ";
            }
        }
        of << tmp << endl;
    }
    of.flush();
    of.close();
    system(("ndmetis "+name).c_str());
    ifstream in((name + ".iperm").c_str());
    while (in.good()) {
        int i;
        in >> i;
        met_ord.push_back(i);
    }
    in.close();
}

typedef boost::graph_traits<Graph>::adjacency_iterator AdjacencyIterator;

template<typename Lambda>
static void for_each_neighbor_const(const Ver& v, const Graph& g, Lambda func) {
    AdjacencyIterator vi, vi_end;
    std::tie(vi, vi_end) = boost::adjacent_vertices(v, g);
    std::for_each(vi,vi_end,func);
}


template<typename Lambda>
static void for_each_neighbor(const Ver& v, Graph& g, Lambda func) {
    AdjacencyIterator vi, vi_end;
    std::tie(vi, vi_end) = boost::adjacent_vertices(v, g);
    std::for_each(vi,vi_end,func);
}

template<typename Lambda>
static void for_each_out_edges(const Ver& v, Graph& g, Lambda func) {
    typename graph_traits < Graph >::out_edge_iterator ei, ei_end;
    boost::tie(ei, ei_end) = out_edges(v, g);
    std::for_each(ei, ei_end, func);
}

typedef boost::rectangle_topology<> topology_type;


typedef boost::exterior_vertex_property<Graph, int> DistanceProperty;
typedef DistanceProperty::matrix_type DistanceMatrix;
typedef DistanceProperty::matrix_map_type DistanceMatrixMap;


#endif
