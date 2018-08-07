#include "Graph.hxx"
#include "Stack.hxx"
#include <iostream>

using std::cout;
using std::endl;

int main(int args, char **argv) {
    Graph root(10);
    DFSTraversal t;
    DFSPath p;

    DFSPath l(level(root));
    for (DFSPath::iterator n = l.begin(); n != l.end(); n++) {
        p.push_back(*n);
        t = dfs(p, 9);
        if (t.first == T_OK)
            break;
        p.pop_back();
    }

    if (t.first == T_GOAL) {
        cout << "Path found" << endl;
        cout << "Cost: " << t.second.size() + 1<< endl;
        cout << "Root:" << endl;
        cout << root << endl;
        for(DFSPath::iterator n = t.second.begin(); n != t.second.end(); n++) {
            cout << n->first << endl;
            cout << n->second << endl;
        }
    } else {
        cout << "Path not found" << endl;
    }

    return 0;
}
