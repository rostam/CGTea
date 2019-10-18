//
// Created by rostam on 15.10.19.
//

#ifndef CGTEA_G6FORMAT_H
#define CGTEA_G6FORMAT_H

#include <utility>
#include <vector>
#include "../datatypes.h"
#include <string>     // std::string, std::stoi


class G6Format {
public:
    G6Format() {

    }

    int BIAS6 = 63;
    int SMALLN = 62;
    int SMALLISHN = 258047;
    int TOPBIT6 = 32;
    int WORDSIZE = 32;

    int SIZELEN(int n) {
        return (n) <= SMALLN ? 1 : ((n) <= SMALLISHN ? 4 : 8);
    }

    int SETWD(int pos) {
        return ((pos) >> 5);
    }

    int SETBT(int pos) {
        return ((pos) & 037);
    }


    Graph stringToGraph2(std::string g6) {
        int n = graphsize(g6);
        Graph graph;
        std::string p = g6;
        if (g6[0] == ':' || g6[0] == '&')
            p = g6.substr(1);
        p = p.substr(SIZELEN(n));

        int m = (n + WORDSIZE - 1) / WORDSIZE;
        int x = 0;
        vector<int> g (m*n);
        for (int ii = m * n; --ii > 0;) g[ii] = 0;
        g[0] = 0;
        int k = 1;
        int it = 0;
        for (int j = 1; j < n; ++j) {
            for (int i = 0; i < j; ++i) {
                if (--k == 0) {
                    k = 6;
                    x = p[it] - BIAS6;
                    it++;
                }
                if ((x & TOPBIT6) != 0) {
                    boost::add_edge(i, j, graph);
                }
                x <<= 1;
            }
        }
        return graph;
    }

    Graph stringToGraph(std::string g6) {
        int n = graphsize(g6);
        Graph graph;
        for (int i = 0; i < graphsize(g6); i++) {
            boost::add_vertex(i, graph);
        }
        std::string p = g6;
        if (g6[0] == ':' || g6[0] == '&')
            p = g6[1];
        p = p.substr(SIZELEN(n));

        int m = (n + WORDSIZE - 1) / WORDSIZE;
        int x = 0;
        vector<long> g;// = new long[m * n];
        for (int ii = m * n; --ii > 0;) g.emplace_back(0);
        g[0] = 0;
        int k = 1;
        int it = 0;
        for (int j = 1; j < n; ++j) {
            for (int i = 0; i < j; ++i) {
                if (--k == 0) {
                    k = 6;
                    x = p[it] - BIAS6;
                    it++;
                }
                if ((x & TOPBIT6) != 0)
                    boost::add_edge(i, j, graph);
                x <<= 1;
            }
        }
        return graph;
    }

    /* Get size of graph out of graph6 or sparse6 string. */
    int graphsize(std::string s) {
        std::string p;
        if (s[0] == ':') p = s.substr(1);
        else p = s;
        int n;
        n = p[0] - BIAS6;

        if (n > SMALLN) {
            n = p[1] - BIAS6;
            n = (n << 6) | (p[2] - BIAS6);
            n = (n << 6) | (p[3] - BIAS6);
        }
        return n;
    }

    ////////////////////////////////////////////////////////////////////
    ////////////// Generate G6 Format
    std::string graphToG6(const Graph& g) {
        std::string result;
        for (int i = 1, k = 1; k < boost::num_vertices(g); i++, k++) {
            for (int j = 0; j < i; j++) {
                Graph::edge_descriptor e1;
                bool found;
                boost::tie(e1, found) = edge(j,i,g);
                if (found) result += "1";
                else result += "0";
            }
        }
        return encodeGraph(boost::num_vertices(g), result);
    }

    std::string encodeGraph(int NoNodes, std::string adjmatrix) {
        std::string rv;
        vector<int> nn = encodeN(NoNodes);
        vector<int> adj = encodeR(std::move(adjmatrix));
        vector<int> res(nn.size() + adj.size());// = new int[nn.length + adj.length];
        for (int n : nn)
            res[n] = n;
        for (int i = 0; i < adj.size(); i++)
            res[i + nn.size()] = adj[i];
        for (int re : res) {
            rv = rv + (char) re;
        }
        return rv;
    }

    std::string toBinaryString(int n) {
        std::string s = std::bitset<64>(n).to_string(); // string conversion
        return s;
    }

    vector<int> encodeN(long i) {
        vector<int> ret;
        if (0 <= i && i <= 62) {
            ret.emplace_back(i + 63);
        } else if (63 <= i && i <= 258047) {
            ret.resize(4);
            ret[0] = 126;
            vector<int> g = R(padL(toBinaryString(i), 18));
            for (int ii = 0; ii < 3; ii++) {
                ret[ii + 1] = g[ii];
            }
            return ret;
        } else {
            ret.resize(8);
            ret[0] = 126;
            ret[1] = 126;
            vector<int> g = R(padL(toBinaryString(i), 36));
            for (int ii = 0; ii < 6; ii++) {
                ret[ii + 2] = g[ii];
            }
            return ret;
        }

    }

    vector<int> R(const std::string& a) {
        vector<int> bytes (a.length());
        for (unsigned int i = 0; i < a.length() / 6; i++) {
            int tmp = std::stoi(a.substr(i * 6, ((i * 6) + 6) - (i * 6)), nullptr, 2);
            bytes[i] = (tmp + 63);
        }

        return bytes;
    }

    vector<int> encodeR(std::string a) {
        a = padR(a);
        return R(a);
    }

    std::string padR(std::string str) {
        unsigned int padwith = 6 - (str.length() % 6);
        for (unsigned int i = 0; i < padwith; i++) {
            str += "0";
        }
        return str;
    }

    std::string padL(std::string str, int h) {
        std::string retval;
        for (unsigned int i = 0; i < h - str.length(); i++) {
            retval += "0";
        }
        return retval + str;
    }
};


#endif //CGTEA_G6FORMAT_H
