/**
 * \file Stack.cxx
 *
 * The DFS Stack Implementation.
 */

#include "Stack.hxx"

#include <iostream>

using std::cout;
using std::endl;

DFSPath level(const Graph &g) {
    Graph h(g);
    DFSPath l;

    l.push_back(DFSNode(Suck, h(Suck)));
    l.push_back(DFSNode(N, h(N)));
    l.push_back(DFSNode(E, h(E)));
    l.push_back(DFSNode(S, h(S)));
    l.push_back(DFSNode(W, h(W)));


    return l;
}

DFSTraversal dfs(DFSPath path, size_t max_depth) {
    if (max_depth == 1) {
        return DFSTraversal(T_BOTTOM, path);
    } else {
        DFSPath l(level(path.back().second));
        for(DFSPath::iterator n = l.begin(); n != l.end(); n++) {
            // Push the current node we’re trying
            path.push_back(*n);

            // If we’re at the goal, return it.
            if (n->second.goal()) {
                return DFSTraversal(T_GOAL, path);
            }

            // Otherwise, traverse from this node.
            DFSTraversal t(dfs(path, max_depth - 1));

            // If our child found a result, return the result.
            if (t.first == T_GOAL)
                return t;

            // Otherwise, pop the current node and try the next child.
            path.pop_back();
        }

        return DFSTraversal(T_BOTTOM, path);
    }
}
