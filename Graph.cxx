/**
 * \file Graph.cxx
 *
 * Implementation of the Graph nodes.
 */

#include "Graph.hxx"
#include <iomanip>

using std::endl;
using std::setw;

Graph::Graph(size_t limit) :
    _nodes(4),
    _cur(NE, _nodes.begin()) {
    for(Nodes::iterator n = _nodes.begin(); n != _nodes.end(); n++) {
        *n = Node::dirty();
    }
}

Graph Graph::operator()(const Operation op) {
    // Copy the current Graph.
    Graph g(*this);

    // New position counter.
    int p;

    // Calculate the new position.
    p = (_cur.first + op) % 4;

    // Invalid motion
    if (// Off the grid
        (p < 0 || p > 3) ||
        // NW <-> SE
        (_cur.first == SW && p == NE) ||
        (_cur.first == NE && p == SW)) {
        p = _cur.first;
    }

    g._cur.first = (Location)(p % 4);
    g._cur.second = g._nodes.begin() + p;

    if (op == Suck) {
        // Clean the new current node if we’re doing a Suck.
        *g._cur.second = (**g._cur.second)();
    }

    return g;
}

Graph::Graph(const Graph &g) :
    _nodes(g._nodes),
    _cur(g._cur.first, _nodes.begin() + (g._cur.second - g._nodes.begin())) {
}

const bool Graph::goal() const {
    bool c = true;

    for (Nodes::const_iterator n = _nodes.begin(); n != _nodes.end(); n++)
        c = c && *n == (*n)->clean();

    return c;
}

const bool Graph::clean() const {
    for(Nodes::const_iterator n = _nodes.begin(); n != _nodes.end(); n++)
        if (*n == Node::dirty())
            return false;
    return true;
}

ostream &operator<<(ostream &os, const Graph &g) {
    os << *g._nodes[0] << *g._nodes[1] << endl;
    os << *g._nodes[2] << *g._nodes[3] << endl;

    return os;
}

Node::Node(const Node &node) : _clean(node._clean) {}

Node *Node::clean() {
    if (!_Clean)
        _Clean = new Clean();

    return _Clean;
}

Node *Node::dirty() {
    if (!_Dirty)
        _Dirty = new Dirty();

    return _Dirty;
}

Node::Node(bool clean) : _clean(clean) {}

const Node &Node::operator=(const Node &n) {
    _clean = n._clean;
    return *this;
}

Clean::Clean() : Node::Node(true) {}

Node *Node::operator()() {
    return clean();
}

Dirty::Dirty() : Node::Node(false) {}

Clean *Node::_Clean;
Dirty *Node::_Dirty;

ostream &operator<<(ostream &os, const Node &n) {
    if (n._clean)
        os << "_";
    else
        os << "*";
    return os;
}

ostream& operator<<(ostream& os, const Operation& op) {
    switch (op) {
    case Suck:
        os << "Suck";
        break;
    case N:
        os << "N";
        break;
    case E:
        os << "E";
        break;
    case S:
        os << "S";
        break;
    case W:
        os << "W";
        break;
    }

    return os;
}

Operation operation(size_t op)  {
    return (Operation)(op % 4);
};
