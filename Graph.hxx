/**
 * \file Graph.hxx
 *
 * Classes for managing the nodes and edges in the depth-first
 * search graph.
 */

#ifndef Graph_hxx
#define Graph_hxx

#include <deque>
#include <vector>
#include <utility>
#include <memory>
#include <iostream>

using std::deque;
using std::vector;
using std::pair;
using std::shared_ptr;
using std::ostream;

class Node;

/**
 * Locations in the Graph of each node.
 */
enum Location {
    NE = 0,
    NW,
    SE,
    SW
};

/**
 * Move or clean. The numbers are the effect it would have on the
 * position (S/N move by a row, E/W move by a node.)
 */
enum Operation {
    Suck = 0,
    N = -2,
    E = -1,
    S = 2,
    W = 1
};

Operation operation(size_t op);

ostream& operator<<(ostream& os, const Operation& op);

class Graph;

typedef vector<Node *> Nodes;

/**
 * The current Node and its Location.
 */
typedef pair<Location, Nodes::iterator> CurrentNode;

/**
 * The state of the Graph at any point in time.
 */
class Graph {
private:
    /**
     * The Nodes of the Graph.
     */
    Nodes _nodes;

    /**
     * The current Node being visited.
     */
    CurrentNode _cur;

    /**
     * The current node count.
     */
    size_t _nnodes;

    /**
     * See if two Graphs are equivalent.
     */
    bool operator==(const Graph&) const;
public:
    /**
     * Create a new Graph.
     */
    Graph(size_t limit);

    /**
     * Copy a Graph, used by operate()()
     */
    Graph(const Graph &);

    /**
     * Is this a goal?
     */
    const bool goal() const;

    /**
     * true if all Nodes are Clean.
     */
    const bool clean() const;

    /**
     * Move in a direction or clean a node and return the Graph.
     * This will only wrap around from SE to NW when increasing the
     * level, up to the level limit.
     */
    Graph operator()(const Operation);

    friend ostream& operator<<(ostream& os, const Graph& dt);
};

class Clean;
class Dirty;

/**
 * Represents a graph node, i.e. a “room” in the grid.
 */
class Node {
protected:
    static Clean *_Clean;
    static Dirty *_Dirty;
    bool _clean;
    Node(bool);
public:
    Node(const Node&);

    static Node *clean();
    static Node *dirty();

    /**
     * Returns the result of the Suck operation. For a Clean Node,
     * this returns the Node. For a Dirty Node, this returns
     * a Clean Node.
     */
    virtual Node *operator()();

    /**
     * Assignment of a Node.
     */
    virtual const Node &operator=(const Node&);

    friend ostream& operator<<(ostream& os, const Node& dt);
};

class Clean : public Node {
public:
    Clean();
};

class Dirty : public Node {
public:
    Dirty();
};

#endif
