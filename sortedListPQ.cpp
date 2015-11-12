/*Assignment from Stanford CS106X: http://web.stanford.edu/class/cs106x/assignments/hw5-priorityqueue.pdf
 *The sorted linked list pq: by Luke (Minsuk) Kim 
 *Every time we enqueue a node, we consider the value of priority
 *and the string value as well.
*/
 
#include "SLinkedPriorityQueue.h"
 
// initialize the head node to null.
SLinkedPriorityQueue::SLinkedPriorityQueue() {
    start = NULL;
}
 
// free all dynamically allocated memory.
SLinkedPriorityQueue::~SLinkedPriorityQueue(){
    clear();
}
 
/*We modify the priority of a given existing value in the queue. The intent
 *is to change the value's priority to be more urgent (smaller integer) than its
 *current value. If the given value is present in the queue and already has a more urgent
 *priority to the given new priority, or if the given value is not arleady in the queue, the function
 *throws a string exception.If the given value occurs multiple times, alter the priority
 *of the first ocurence.
 */
void SLinkedPriorityQueue::changePriority(string value, int newPriority) {
    LISTNODE *cur;
    cur = start;
    while (cur != NULL){
        if (cur->s == value){
            if (cur->val < newPriority){
                cout << "Error! already has more urgent priority" << endl;
                return;
            }else if (cur->val >= newPriority){
                cur->val = newPriority;
                return;
            }
        }
        cur = cur->next;
    }
    cout << "Error! no node with the given string value was found" << endl;
}
 
/*We iterate over the list and free
all the memory dynamically allocated for the nodes.
*/
void SLinkedPriorityQueue::clear() {
    // freeing all dynamically allocated memory.
    LISTNODE *cur;
    cur = start;
    while (cur != NULL){
        start = start->next;
        delete cur;
        cur = start;
    }
    start = NULL;
}
 
/*In this function we should remove the node with the most urgent
priority from the priority queue, and we should also return it. In
a sorted linked list, this is simply the first node of the list. Not
so sure if the dequeue wants the string value only or if it also wants
the integer value, so I implemented it such that it only returns the string value.
*/
string SLinkedPriorityQueue::dequeue() {
    if (start == NULL){
        return "Error! queue is empty!";
    }
    LISTNODE *cur;
    cur = start;
    start = start->next;
    string data = cur->s;
    delete cur;
    return data;
}
 
/*
We enqueue the nodes into the linked list such that they are in sorted order.
Sorted means that the ones with smaller priority values come first and if two
nodes have the same priority value,the one with a smaller string value comes first.
*/
void SLinkedPriorityQueue::enqueue(string value, int priority) {
    LISTNODE *cur, *newnode;
    cur = start;
    newnode = new LISTNODE;
    newnode->s = value;
    newnode->val = priority;
    newnode->next = NULL;
    // we then process the enqueuing procedure.
    if (start == NULL){
        // if the list is initially empty.
        start = newnode;
        newnode->next = NULL;
        return;
    }else if (newnode->val < start->val){
        // if the priority is less than that of the start node, enqueue at the very front.
        newnode->next = start;
        start = newnode;
        return;
    }else if (newnode->val == start->val && newnode->s <= start->s){
        // if the priority is the same as that of the start node,
        // and if the string value is less than or equal, enqueue at the very front.
        newnode->next = start;
        start = newnode;
        return;
    }
    // for all the other cases
    // i.e. priority of new node is less than start
    // or if the priority is equal, the string value is greater than that of the starting node.
    while (true){
        if (cur->next == NULL){
            // if start is the only node in the linked list, enqueue newnode at the very end of the (linked) list.
            cur->next = newnode;
            newnode->next = NULL;
            return;
        }else if (cur->next->val > newnode->val){
            // if the node that cur points to has a greater priority value,
            // insert newnode between cur and the node that cur points to.
            newnode->next = cur->next;
            cur->next = newnode;
            return;
        }else if (cur->next->val == newnode->val && cur->next->s >= newnode->s){
            // if the node that cur points to has a priority equal to the priority of
            // newnode, but if the string value is greater than or equal to newnode's
            // then we insert newnode between cur and the node that cur points to.
            newnode->next = cur->next;
            cur->next = newnode;
            return;
        }else{
            cur = cur->next;
        }
    }
}
 
/*In this function we return true if the priority queue does not
contain any elements and false if it does contain at least one element
*/
bool SLinkedPriorityQueue::isEmpty() const {
    return start == NULL;
}
 
/*
In this function you should return the string element with the most
urgent priority from your priority queue (simply the first node in
a sorted queue of linked list), without removing it or altering
the state of the queue. You should throw a string exception if the queue
does not contain any elements.
*/
string SLinkedPriorityQueue::peek() const {
    if (start == NULL){
        return "Error! queue is empty";
    }
    return start->s;
}
 
/*In this function you should return the integer priority that is most
urgent from your priority queue (the priority associated with the string
that would be returned by a call to peek)
*/
int SLinkedPriorityQueue::peekPriority() const {
    if (start == NULL){
        cout << "Error! queue is empty" << endl;
        cout << "we return a large negative number to indicate this:" << endl;
        return -987654321;
    }
    return start->val;
}
 
/*In this function you should return the number of elements in your
priority queue.
*/
int SLinkedPriorityQueue::size() const {
    if (start == NULL){
        return 0;
    }
    int cnt = 0;
    LISTNODE *cur;
    cur = start;
    while (cur != NULL){
        ++cnt;
        cur = cur->next;
    }
    return cnt;
}
 
/*We write a << operator for printing your priority queue to the
 *console. The elements can print out in any order and must be in the
 *form of "value":priority with {} braces,
 *such as {"t":2, "b":4, "m":5,"q":5, "x":5, "a":8}.
 *We should not be an endl or '\n' at the end.
 *Note that friend functions are defined outside that class's scope, but
 *it has the right to access all private and protected members of the class.
 */
ostream& operator<<(ostream& out, const SLinkedPriorityQueue& queue) {
    if (queue.start == NULL){
        out << "queue is empty, you may enqueue some nodes";
    }else{
        // we can create another instance of the class
        // and equate it with the instance queue.
        SLinkedPriorityQueue queue2 = queue;
        out << "{";
        while (queue2.size()>0){
            if (queue2.size() == 1){
                out << "\"" << queue2.peek() << "\"" << ":" << queue2.peekPriority() << "}";
            }else{
                out << "\"" << queue2.peek() << "\"" << ":" << queue2.peekPriority() << ", ";
            }
            queue2.start = queue2.start->next;
        }
        queue2.clear();
    }
    return out;
}
