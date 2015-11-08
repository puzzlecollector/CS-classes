/*From Stanford CS106X Assignment 3: http://web.stanford.edu/class/cs106x/assignments/hw3-recursionwarmup.pdf
 *Recursion Problems: By Luke (Minsuk) Kim
 *The first part is the human-pyramid (both human-pyramid and fast human-pyramid).
 *The second part is drawing the Sierpinski Triangle.
 *Involves simple recursion and some memoization.
 */

// INCLUDES
#include "recursionproblems.h"
#include <cmath>
#include <iostream>
#include "hashmap.h"
#include "map.h"
#include "random.h"
using namespace std;

// FUNCTION DEFINITIONS

/*checks the value of the row and col, and calculates the
 *knee weight of each person accordingly. Note that we return
 *0.0 when the values of row and col are out of bounds.
 */
double weightOnKnees(int row, int col, const Vector<Vector<double> >& weights) {
    if (row == 0 && col == 0){
        return weights[0][0];
    }
    if (row >= 1 && col == 0){
        return weights[row][col] + 0.5*weightOnKnees(row-1,col,weights);
    }
    if (row >= 1 && col == row){
        return weights[row][col] + 0.5*weightOnKnees(row-1,col-1,weights);
    }
    if (row >= 1 && (col > 0 && col < row)){
        return weights[row][col] + 0.5*(weightOnKnees(row-1,col-1,weights) + weightOnKnees(row-1,col,weights));
    }
    // returns 0.0 if the row and col are out of bounds.
    return 0.0;
}

/*Use of memoization for a faster implementation of the human
 *pyramid program.This prevents calculating the same values over
 *and over again.
 */
double weightOnKneesFaster(int row, int col, const Vector<Vector<double> >& weights,
                           Vector<Vector<double> >& memos) {
    if (memos[row][col] > 0){
        return memos[row][col];
    }
    if (row == 0 && col == 0){
        return memos[row][col] = weights[0][0];
    }
    if (row >= 1 && col == 0){
        return memos[row][col] = weights[row][col] + 0.5*(weightOnKneesFaster(row-1,col,weights,memos));
    }
    if (row >= 1 && col == row){
        return memos[row][col] = weights[row][col] + 0.5*weightOnKneesFaster(row-1,col-1,weights,memos);
    }
    if (row >= 1 && (col > 0 && col < row)){
        return memos[row][col] = weights[row][col] + 0.5*(weightOnKneesFaster(row-1,col-1,weights,memos) + weightOnKneesFaster(row-1,col,weights,memos));
    }
    // returns 0.0 if the row and col are out of bounds.
    return 0.0;
}

/*This is a wrapper function that calls the function that passes
 *the memo vector.
 */
double weightOnKneesFaster(int row, int col, const Vector<Vector<double> >& weights) {
    // let us initialize memos to all zeros first.
    Vector<Vector<double> > memos = weights; //this allows us to have memos
    // to be the same size as weight.
    for (int i = 0; i < memos.size(); i++){
        for (int j = 0; j < memos[i].size(); j++){
            memos[i][j] = 0.0;
        }
    }
    return weightOnKneesFaster(row,col,weights,memos);
}

/*Compares the value of order_cnt and order, in order to
 *decide if the program should continue recursion or stop.
 *I worked with orders 2 and 3 (i.e. smaller cases) in order to derive a relationship between coordinates
 *that I could use for recursion.
 */
void recursiveSierpinski(GWindow& gw,int order_cnt, int order, double x, double y, double x2, double y2, double x3, double y3){
    if (order_cnt == order){
        return; // base case for recursion.
    }
    if (order_cnt >= 1){
        gw.drawLine(x,y,x2,y2);
        gw.drawLine(x,y,x3,y3);
        gw.drawLine(x2,y2,x3,y3);
        // noticing a pattern from order 2 to order 3, we know we have to call
        // the recursive function at least three times.
        recursiveSierpinski(gw,order_cnt+1,order,x-x3/2+x2/2,y,x2-x3/2+x/2,(y+y2)/2,(x+x2)/2,(y+y2)/2);
        recursiveSierpinski(gw,order_cnt+1,order,x-x2/2+x3/2,y,(x+x3)/2,(y+y3)/2,x3-x2/2+x/2,(y+y3)/2);
        recursiveSierpinski(gw,order_cnt+1,order,(x2+x3)/2,(y2+y3)/2,x2-x/2+x3/2,y2-y/2+y3/2,x3-x/2+x2/2,y2-y/2+y3/2);
    }
}


/*We draw the outer-most triangle, then we
 *call a recursive function. So in another sense, this is a wrapper function.
 */
void drawSierpinskiTriangle(GWindow& gw, double x, double y, int size, int order) {
    if (x < 0 || y < 0 || order < 0 || size < 0){ // throw an exception
        throw string("Exception");
        return;
    }
    if (order == 0){ // do not pass anything.
        return;
    }
    // draw the three sides of the outer-most triangle.
    double x2 = x+size, y2 = y;
    double x3 = x+size/2, y3 = y+sqrt(3)*size/2;
    gw.drawLine(x,y,x2,y2);
    gw.drawLine(x,y,x3,y3);
    gw.drawLine(x2,y2,x3,y3);
    // now we call recursiveSierpinski() to draw the rest of the triangles;
    recursiveSierpinski(gw,1,order,(x+x2)/2,(y+y2)/2,(x+x3)/2,(y+y3)/2,(x2+x3)/2,(y2+y3)/2);
}

