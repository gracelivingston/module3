/**
 * \file Stack.hxx
 *
 * Manage the DFS Stack.
 */

#include <deque>
#include <set>
#include <utility>
#include "Graph.hxx"

using std::deque;
using std::set;
using std::pair;

/**
 * The Operation and the Graph it created.
 */
typedef pair<Operation, Graph> DFSNode;

/**
 * A path of DFSNodes.
 */
typedef deque<DFSNode> DFSPath;

/**
 * Create a full set of DFSNodes from a Graph.
 */
DFSPath level(const Graph &g);

/**
 * The state of traversing the Graph.
 */
enum Traversal {
    /** The next Graph is continuing. */
    T_OK,

    /** The next Graph is complete. */
    T_GOAL,

    /** The next Graph is at the depth limit. */
    T_BOTTOM
};

/**
 * The result of traversing this DFSPath.
 */
typedef pair<Traversal, DFSPath> DFSTraversal;

/**
 * Start at root and go down max_depth levels until a path is found.
 */
DFSTraversal dfs(DFSPath path, size_t max_depth);
