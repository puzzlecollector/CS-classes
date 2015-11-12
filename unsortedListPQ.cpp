/*Assignment from Stanford CS106X: http://web.stanford.edu/class/cs106x/assignments/hw5-priorityqueue.pdf
 *Unsorted Priority Queue program: By Luke (Minsuk) Kim
 *Unlike the sorted version, the nodes are enqueued at the very end
 *of the list every time.
 */
#include "USLinkedPriorityQueue.h"
 
// initialize the head node to null.
USLinkedPriorityQueue::USLinkedPriorityQueue() {
    start = NULL;
}
 
// free all dynamically allocated memory.
USLinkedPriorityQueue::~USLinkedPriorityQueue() {
    clear();
}
 
/*We modify the priority of a given existing value in the queue. The intent
 *is to change the value's priority to be more urgent (smaller integer) than its
 *current value. If the given value is present in the queue and already has a more urgent
 *priority to the given new priority, or if the given value is not arleady in the queue, the function
 *throws a string exception.If the given value occurs multiple times, alter the priority
 *of the first ocurence.
 */
void USLinkedPriorityQueue::changePriority(string value, int newPriority) {
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
void USLinkedPriorityQueue::clear() {
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
priority from the priority queue, and we should also return it. Because
the nodes are not sorted, we firt locate the node that has to be removed,
and then delete it.
*/
string USLinkedPriorityQueue::dequeue() {
    if (start == NULL){
        return "Error! queue is empty!";
    }
    LISTNODE *cur;
    cur = start;
    int maxPriority = INT_MAX;
    string maxStr = "";
    // we specially take care of the case when there
    // is only one node in the list.
    if (start->next == NULL){
        maxStr = start->s;
        start = NULL;
        return maxStr;
    }
    // if there is more than one node in the list.
    // first find the node with the most urgent priority.
    while (cur != NULL){
        if (cur->val < maxPriority){
            maxPriority = cur->val;
            maxStr = cur->s;
        }else if (cur->val == maxPriority){
            if (maxStr > cur->s){
                maxStr = cur->s;
            }
        }
        cur = cur->next;
    }
    // now let us remove the node that contains the values
    // maxPriority and maxStr.
    LISTNODE *current = start->next;
    LISTNODE *prev = start;
    while (current != NULL){
        // case when the head node is the node that we have
        // to remove.
        if (prev->s == maxStr && prev->val == maxPriority){
            // we swap values on prev and current.
            string tempStr = prev->s;
            int tempPriority = prev->val;
            prev->s = current->s;
            prev->val = current->val;
            current->s = tempStr;
            current->val = tempPriority;
        }
        if (current->s == maxStr && current->val == maxPriority){
            prev->next = current->next;
            delete current;
            break;
        }else{
            prev = prev->next;
            current = current->next;
        }
    }
    return maxStr;
}
 
/*We enqueue the nodes, but because the list is unsorted,
 *we can simply attach the nodes at the very back every time
 *we enqueue.
 */
void USLinkedPriorityQueue::enqueue(string value, int priority) {
    // the actual enqueue operation.
    LISTNODE *cur, *newnode;
    cur = start;
    newnode = new LISTNODE;
    newnode->s = value;
    newnode->val = priority;
    newnode->next = NULL;
    // we then process the enqueuing procedure.
    // the process is more simple because we are enquiung nodes
    // without considering their orders.
    if (start == NULL){
        // if the list is initially empty.
        start = newnode;
        newnode->next = NULL;
        return;
    }else{
        while (cur->next != NULL){
            cur = cur->next;
        }
        cur->next = newnode;
        newnode->next = NULL;
        return;
    }
}
 
/*In this function we return true if the priority queue does not
contain any elements and false if it does contain at least one element
*/
bool USLinkedPriorityQueue::isEmpty() const {
    return start == NULL;
}
 
/*
In this function we should return the string element with the most
urgent priority from your priority queue.We iterate over the linked
lists to find this since the list is unsorted.
*/
string USLinkedPriorityQueue::peek() const {
    if (start == NULL){
        return "Error! the queue is empty";
    }
    LISTNODE *cur;
    cur = start;
    int maxPriority = INT_MAX;
    string maxStr = "";
    while (cur != NULL){
        if (maxPriority > cur->val){
            maxPriority = cur->val;
            maxStr = cur->s;
        }
        else if (maxPriority == cur->val){
            if (maxStr > cur->s){
                maxStr = cur->s;
            }
        }
        cur = cur->next;
    }
    return maxStr;
}
 
/*Find the node with the most urgent priority
 *and print the priority value. We iterate through the list
 *because it is unsorted.
 */
int USLinkedPriorityQueue::peekPriority() const {
    if (start == NULL){
        cout << "Error! the queue is empty" << endl;
        cout << "We return a very large negative number to indicate this" << endl;
        return -987654321;
    }
    LISTNODE *cur;
    cur = start;
    int maxPriority = INT_MAX;
    string maxStr = "";
    while (cur != NULL){
        if (maxPriority > cur->val){
            maxPriority = cur->val;
            maxStr = cur->s;
        }
        else if (maxPriority == cur->val){
            if (maxStr > cur->s){
                maxStr = cur->s;
            }
        }
        cur = cur->next;
    }
    return maxPriority;
}
 
/*Returns the size of the queue.
 */
int USLinkedPriorityQueue::size() const {
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
 
/*
In this function you should return the string element with the most
urgent priority from your priority queue (simply the first node in
a sorted queue of linked list), without removing it or altering
the state of the queue. You should throw a string exception if the queue
does not contain any elements.
*/
ostream& operator<<(ostream& out, const USLinkedPriorityQueue& queue) {
    if (queue.start == NULL){
        out << "queue is empty, you may enqueue some nodes";
    }else{
        USLinkedPriorityQueue queue2 = queue;
        out << "{";
        int numNodes = queue2.size();
        while (numNodes > 0){
            if (numNodes == 1){
                out << "\"" << queue2.start->s << "\"" << ":" << queue2.start->val << "}";
            }else{
                out << "\"" << queue2.start->s << "\"" << ":" << queue2.start->val << ", ";
            }
            queue2.start = queue2.start->next;
            --numNodes;
        }
    }
    return out;
}
