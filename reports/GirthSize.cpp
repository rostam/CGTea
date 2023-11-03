//
// Created by rostam on 19.06.20.
//

#include "GirthSize.h"
#include "EigenRelatedFunctions.h"

int bfs(int start, const Eigen::MatrixXd& mat, int cc, int girth) {
    vector<int> baba(cc);
    vector<int> dist(cc);
    for (int i = 0; i < cc; i++) {
        baba[i] = std::numeric_limits<int>::max();
        dist[i] = std::numeric_limits<int>::max();
    }

    dist[start] = 0;
    baba[start] = -1;
    vector<int> ll;
    ll.push_back(start);
    while (ll.size() > 0) {
        int currentNode = *ll.begin();
        ll.erase(ll.begin());
        for (int j = 0; j < cc; j++) {
            if (mat(currentNode,j) == 1) {
                if (dist[j] == std::numeric_limits<int>::max()) {
                    dist[j] = dist[currentNode] + 1;
                    baba[j] = currentNode;
                    if (2 * dist[j] < girth - 1)
                        ll.push_back(j);
                } else if (dist[j] + dist[currentNode] < girth - 1 && baba[currentNode] != j) {
                    girth = dist[j] + dist[currentNode] + 1;
                }
            }
        }
    }
    return girth;
}

string GraphGirthSize::report(const Graph& g) {
    int size = boost::num_vertices(g);
    Eigen::MatrixXd mat = Eigen::MatrixXd::Zero(size, size);
    for_each_e_const(g, [&](Edge e) {
        mat(boost::source(e, g), boost::target(e, g)) = 1;
        mat(boost::target(e, g), boost::source(e, g)) = 1;
    });
    int girth = std::numeric_limits<int>::max();
    for (int i = 0; i < size; i++) {
        int sizeofsmallestcycle = bfs(i, mat, size, girth);
        if (sizeofsmallestcycle != std::numeric_limits<int>::max() && girth > sizeofsmallestcycle)
            girth = sizeofsmallestcycle;
    }
    if (girth == std::numeric_limits<int>::max())
        return "0";
    return std::to_string(girth);
}