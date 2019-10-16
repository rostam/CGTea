//
// Created by rostam on 15.10.19.
//

#ifndef CGTEA_G6FORMAT_H
#define CGTEA_G6FORMAT_H

#include <vector>
#include "../datatypes.h"


class G6Format {
private:
    G6Format() {

    }
    static int BIAS6 = 63;
    static int SMALLN = 62;
    static int SMALLISHN = 258047;
    static int TOPBIT6 = 32;
    static int  WORDSIZE = 32;

    static int bit_[] = {020000000000, 010000000000, 04000000000, 02000000000,
                         01000000000, 0400000000, 0200000000, 0100000000, 040000000,
                         020000000, 010000000, 04000000, 02000000, 01000000, 0400000,
                         0200000, 0100000, 040000, 020000, 010000, 04000, 02000, 01000,
                         0400, 0200, 0100, 040, 020, 010, 04, 02, 01};

    static int SIZELEN(int n) {
        return (n) <= SMALLN ? 1 : ((n) <= SMALLISHN ? 4 : 8);
    }

    int SETWD(int pos) {
        return ((pos) >> 5);
    }

    int SETBT(int pos) {
        return ((pos) & 037);
    }


 static Graph stringToGraph2(std::string g6) {
        int n = graphsize(g6);
        Graph graph;
        std::string p = g6;
        if (g6[0] == ':' || g6[0] == '&')
            p = g6.substr(1);
        p = p.substr(SIZELEN(n));

        int m = (n + WORDSIZE - 1) / WORDSIZE;
        int x=0;
        long g[] = new long[m * n];
        for (int ii = m * n; --ii > 0; ) g[ii] = 0;
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
                    boost::add_edge(i,j,graph);
                }
                x <<= 1;
            }
        }
        return graph;
    }

 static Graph stringToGraph(std::string g6) {
        int n = graphsize(g6);
        Graph graph;
        for(int i=0;i<graphsize(g6);i++) {
            boost::add_vertex(i,graph);
        }
        std::string p = g6;
        if (g6[0] == ':' || g6[0] == '&')
            p = g6[1];
        p = p.substr(SIZELEN(n));

        int m = (n + WORDSIZE - 1) / WORDSIZE;
        int x=0;
        long[] g = new long[m * n];
        for (int ii = m * n; --ii > 0; ) g[ii] = 0;
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
                    boost::add_edge(i,j, graph);
                x <<= 1;
            }
        }
        return graph;
    }

    /* Get size of graph out of graph6 or sparse6 string. */
    static int graphsize(std::string s) {
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
 static std::string graphToG6(Graph g) {
        return encodeGraph(boost::num_vertices(g), createAdjMatrix(g.getAdjacencyMatrix()));
    }

 static std::string createAdjMatrix (Matrix m){
        std::string result="";

        for (int i = 1, k = 1; k < m.getColumnDimension(); i++, k++) {
            for (int j = 0; j < i; j++) {
                if (m.get(j,i) != 0) result += "1";
                else result += "0";
            }
        }
        return result;
    }


 static std::string encodeGraph(int NoNodes, std::string adjmatrix) {
        std::string rv = "";
        int[] nn = encodeN(NoNodes);
        int[] adj = encodeR(adjmatrix);
        int[] res = new int[nn.length + adj.length];
        System.arraycopy(nn, 0, res, 0, nn.length);
        System.arraycopy(adj, 0, res, nn.length, adj.length);
        for (int re : res) {
            rv = rv + (char) re;
        }
        return rv;
    }

 static int[] encodeN(long i) {

        if (0 <= i && i <= 62) {
            return new int[] { (int) (i + 63) };
        } else if (63 <= i && i <= 258047) {
            int[] ret = new int[4];
            ret[0] = 126;
            int[] g = R(padL(Long.toBinaryString(i), 18));
            System.arraycopy(g, 0, ret, 1, 3);
            return ret;
        } else {
            int[] ret = new int[8];
            ret[0] = 126;
            ret[1] = 126;
            int[] g = R(padL(Long.toBinaryString(i), 36));
            System.arraycopy(g, 0, ret, 2, 6);
            return ret;
        }

    }

 static int[] R(std::string a) {
        int[] bytes = new int[a.length() / 6];
        for (int i = 0; i < a.length() / 6; i++) {
            bytes[i] = Integer.valueOf(a.substring(i * 6, ((i * 6) + 6)), 2);
            bytes[i] = (byte) (bytes[i] + 63);
        }

        return bytes;
    }

 static int[] encodeR(std::string a) {
        a = padR(a);
        return R(a);
    }

  static std::string padR(std::string str) {
        int padwith = 6 - (str.length() % 6);
        for (int i = 0; i < padwith; i++) {
            str += "0";
        }
        return str;
    }

  static std::string padL(std::string str, int h) {
        std::string retval = "";
        for (int i = 0; i < h - str.length(); i++) {
            retval += "0";
        }
        return retval + str;
    }
};


#endif //CGTEA_G6FORMAT_H
