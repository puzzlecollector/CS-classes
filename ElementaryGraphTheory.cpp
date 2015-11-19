/*Trailblazer assignment: Minsuk (Luke) Kim
 *CS106X assignment: http://web.stanford.edu/class/cs106x/assignments/hw7-trailblazer.pdf
 *We implement DFS, BFS, Dijkstra and A* methods of finding a path
 *from the starting node to the end node in a maze.
 *We then implement Kruskal's algorithm for finding MST
 *Referred to this webpage for some pseudo-code: http://web.mit.edu/eranki/www/tutorials/search/
 *Referred to this webpage for BasicGraph methods: http://stanford.edu/~stepp/cppdoc/BasicGraph-class.html
 *Referred to this webpage for tips: https://web.stanford.edu/class/cs106b/hw7-trailblazer-faq.shtml
 */
#include "trailblazer.h"
#include "queue.h"
#include "pqueue.h"
#include <queue>
#include <algorithm>
using namespace std;

/*A recursive depth first search algorithm.
 *The idea of the algorithm is simliar to the following pseudo-code:
 *function dfs(node pos){
 *  color(pos); // indicating that node is visited.
 *  for each successor adjacent to node "pos"
 *      if successor is colored, continue;
 *      if successor is goal node, we stop;
 *      else dfs(successor);
 *  end
 *end
 */
void recursiveDepthFirstSearch(BasicGraph& graph, Vector<Vertex*>& path, Vertex* start, Vertex* end){
    start->setColor(GREEN);
    start->visited = true;
    path.add(start);
    // base case: if start = end
    if (start == end){
        path.add(start);
        return;
    }
    // check neighbor vertices
    for (Edge *edge:start->edges){
        // range based for loop.
        Vertex* next = edge->finish;
        if (next->visited){
            continue;
        }else{
            recursiveDepthFirstSearch(graph,path,next,end);
        }
    }
    // When the DFS algorithm has finished exploring a vertex
    // and did not find a path from that vertex, color this vertex
    // as gray.
    start->setColor(GRAY);
    // we then get rid of this node
    path.remove((int)path.size()-1);
    return;
}

/*We use this as a wrapper function
 *for the recursive depth first search algorithm.
 */
Vector<Vertex*> depthFirstSearch(BasicGraph& graph, Vertex* start, Vertex* end) {
    graph.resetData();
    Vector<Vertex*> path;
    recursiveDepthFirstSearch(graph,path,start,end);
    // note that an empty vector path will be returned
    // if there was no path from start to end.
    return path;
}

/*Supposed to be faster than BFS because we try to find the shortest path.
 *We examine each of the nodes next to the node in question before we go deeper.
 *Because we are moving awayslowly out from the starting position, we will be reaching
 *our goal as quickly as possible. The idea of this function is similar to the following
 *pseudo-code:
 *function bfs(node start){
 *  add start to queue
 *  while the queue is not empty
 *      pop a node off the queue and call it "node"
 *      color node on the graph // mark it as visited and don't search it again.
 *      generate the successors to the item // use range-based for loop for this.
 *      set the parent of each successor to node.
 *      for each successor
 *          if the successor is the goal node, end the search
 *          else push it to the back of the queue, so we can search this node.
 *      end
 *  end
 *  if we have a goal node, look at its previously connected nodes to find the path.
 *  if not, queue was empty and there is no path.
 * end.
 */
Vector<Vertex*> breadthFirstSearch(BasicGraph& graph, Vertex* start, Vertex* end) {
    graph.resetData();
    Queue<Vertex*> q;
    Vector<Vertex*> path;
    start->setColor(YELLOW); // this means the node start is enqueued in the queue.
    q.enqueue(start);
    // using this for breath first searching.
    Vertex* node;
    Vertex* next;
    while (!q.isEmpty()){
        node = q.dequeue();
        node->setColor(GREEN);// green when it is dequeued from the queue data structure.
        for (Edge *edge:node->edges){
            next = edge->finish;
            if (next->visited){
                // no need to check visited vertices.
                continue;
            }else if (next != end){
                q.enqueue(next);
                next->setColor(YELLOW); // enqueued in queue.
                next->visited = true; // mark as visited.
                next->previous = node;
            }else if (next == end){
                // we can end the BFS because we have reached our destination.
                next->setColor(GREEN); // visited
                while (next != NULL){
                    path.add(next);
                    next = next->previous;
                }
                return path;
            }
        }
    }
    return path;
}


/*Callback function for our priority queue.
 *We pass as parameters the vertex that is being placed in pq,
 *the destination vertex and
 */
double priority(Vertex* start,Vertex* end,double d){
    return d;
}

/*This function implements the dijkstra's algorithm. We use the idea from the
 *following Pseudocode:
 *  Mark all nodes as default (not GRAY as in the lecture slide).
 *  Mark the initial node s as yellow and at candidate distance 0.
 *  Enqueue s into the priority queue with priority 0.
 *  While not all nodes have been visited:
 *      Dequeue the lowest-cost node u from the priority queue.
 *      color u green.
 *      The candidate distance d that is currently stored for node u is the length of the shortest path from s to u.
 *      If u is the destination node t, you have found the shortest path from s to t and are done.
 *      For each node v connected to u by an edge of length L:
 *          If v is gray:
 *              color v yellow.
 *              Mark v's distance as d+L
 *              Set v's parent to be u.
 *              Enqueue v into the priority queue with priority d+L.
 *          If v is yellow and the canddiate distance to v is grater than d+L:
 *              update v's candidate distance to be d+L.
 *              update v's parent to be u.
 *              update v's priority in the priority queue to be d+L.
 *      end.
 * end.
 */
Vector<Vertex*> dijkstrasAlgorithm(BasicGraph& graph, Vertex* start, Vertex* end) {
    graph.resetData();
    Vector<Vertex*> path;
    PriorityQueue<Vertex*> pq;
    start->setColor(YELLOW); // marking start node yellow.
    // enqueue into pq with priority 0.
    pq.enqueue(start,priority(start,end,0));
    start->cost = 0;
    while (!pq.isEmpty()){
        Vertex* u = pq.dequeue();
        u->setColor(GREEN);  //to indicate this node is visited.
        u->visited = true;
        if (u == end){
            // found destination
            while (u != NULL){
                path.add(u);
                u = u->previous;
            }
            return path;
        }else{
            for (Edge *edge:u->edges){
                Vertex *v = edge->finish;
                if (v->visited){
                    continue;
                }
                if (v->getColor() == UNCOLORED){
                    v->setColor(YELLOW);
                    v->cost = u->cost + edge->cost;
                    v->previous = u;
                    pq.enqueue(v,priority(v,end,u->cost+edge->cost));
                }else if (v->getColor() == YELLOW && v->cost > u->cost + edge->cost){
                    v->cost = u->cost + edge->cost;
                    v->previous = u;
                    pq.changePriority(v,priority(v,end,u->cost+edge->cost));
                }
            }
        }
    }
    return path;
}


/*As discussed in class, the A* algorithm is essentially a variation of
 *Dijkstra's algorithm. This uses the provided heuristics to fine-tune the order
 *of elements in its priority queue to explore more likely desirable elements first.
 *The only change we make compared to the Dijkstra's algorithm above is to enqueue
 *the elements into the priority queue with the callback and heuristics function.
 */


Vector<Vertex*> aStar(BasicGraph& graph, Vertex* start, Vertex* end) {
    graph.resetData();
    Vector<Vertex*> path;
    PriorityQueue<Vertex*> pq;
    start->setColor(YELLOW); // marking start node yellow.
    // enqueue into pq with priority 0.
    pq.enqueue(start,priority(start,end,0)+heuristicFunction(start,end));
    start->cost = 0;
    while (!pq.isEmpty()){
        Vertex* u = pq.dequeue();
        u->setColor(GREEN);  //to indicate this node is visited.
        u->visited = true;
        if (u == end){
            // found destination
            while (u != NULL){
                path.add(u);
                u = u->previous;
            }
            return path;
        }else{
            for (Edge *edge:u->edges){
                Vertex *v = edge->finish;
                if (v->visited){
                    continue;
                }
                if (v->getColor() == UNCOLORED){
                    v->setColor(YELLOW);
                    v->cost = u->cost + edge->cost;
                    v->previous = u;
                    pq.enqueue(v,priority(v,end,u->cost+edge->cost)+heuristicFunction(v,end));
                }else if (v->getColor() == YELLOW && v->cost > u->cost + edge->cost){
                    v->cost = u->cost + edge->cost;
                    v->previous = u;
                    pq.changePriority(v,priority(v,end,u->cost+edge->cost)+heuristicFunction(v,end));
                }
            }
        }
    }
    return path;
}

/*Checks if whether we have in
 *same cluster
 */
bool same(Vertex* start, Vertex* end, Vector<Set<Vertex*>>& clusterSet){
    for (Set<Vertex*> set: clusterSet){
        if (set.contains(start) && set.contains(end)) return true;
    }
    return false;
}

/*Merges cluster of two vertices
 */
void merge(Vertex* start, Vertex* end, Vector<Set<Vertex*>>& clusterSet){
    int init,final;
    Set<Vertex*> cur;
    for (int i = 0; i < clusterSet.size(); i++){
        cur = clusterSet[i];
        if (cur.contains(start)){
            init = i;
        }else if (cur.contains(end)){
            final = i;
        }
    }
    // the merging process is described as follows:
    clusterSet[init] += clusterSet[final];
    clusterSet.remove(final);
}

/*We finally implement Kruskal's algorithm for finding MST.
 *We use the following pseduocode:
 *Kruskal(graph):
 *  1. place each vertex into its own "cluster"
 *  2. put all edges into a pq (priority queue), using weights as priorities.
 *  3. while there are two or more separate clusters remaining:
 *      dequeue an edge e from the pq.
 *      If the start and finish vertices of e are not in the same cluster:
 *          Merge the clusters containing the start and finish vertices of e.
 *          Add e to your spanning tree.
 *      Else:
 *          Do not add e to your spanning tree.
 *  4. Once the while loop terminates, your spanning tree is complete.
 * end.
 */

Set<Edge*> kruskal(BasicGraph& graph) {
    Set<Edge*> mst; // used for forming minimum spanning tree.
    PriorityQueue<Edge*> pq;
    // place each vertex into its own cluster
    Set<Vertex*> vertices = graph.getVertexSet();
    Vector<Set<Vertex*>> clusterSet;
    for (Vertex* v: vertices){
        Set<Vertex*> s;
        s.add(v);
        clusterSet.add(s);
    }
    // place each vertex into its own cluster.
    Set<Edge*> edgeSet = graph.getEdgeSet();
    for (Edge* e: edgeSet){
        pq.enqueue(e,e->cost);
    }
    // we from a minimum spanning tree
    while (!pq.isEmpty()){
        Edge* e = pq.dequeue();
        if (!same(e->start,e->finish,clusterSet)){
            mst.add(e);
            merge(e->start,e->finish,clusterSet);
        }
    }
    return mst;
}
