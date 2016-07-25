#include "console.h"
#include "simpio.h"
#include "gtypes.h"
#include "random.h"
#include "gwindow.h"
#include "gobjects.h"

using namespace std;

/*The constants delay in milliseconds between the display of the new points*/
int DRAW_PAUSE = 0;

/*The constants number of points that will be displayed Sierpinski triangle*/
int COUNT_POINTS = 50000;

/*
 * Constants display settings
*/
int WINDOW_WIDTH = 1000;
int WINDOW_HEIGHT = 800;

/*
 *Function gets the parameters the reference to the three points
 *of the object and returns a random one
 *@param  - leftPoint a reference to the first object point
 *@param  - rightPoint a reference to the second object point
 *@param  - topPoint a reference to the third object point
 *@result - randomly selected object of the specified point in the parameters
*/
const GPoint& getNewRandomPoint(const GPoint &leftPoint,
                         const GPoint &rightPoint,
                         const GPoint &topPoint){
    int newPointCounter = randomInteger(0, 2);
    switch (newPointCounter) {
    case 0:
        return leftPoint;
    case 1:
        return rightPoint;
    }
    return topPoint;
}
/*
 *Function calculates the coordinates of the middle between two points
 *@param  - startPoint a reference to the object with the coordinates of the first point
 *@param  - nextPoint a reference to the object with the coordinates of the second point
 *@result - object coordinates middle of given points
*/
GPoint getMiddlePoint(const GPoint &startPoint, const GPoint &nextPoint){
    double middleX, middleY;

    middleX = startPoint.getX() + ((nextPoint.getX() - startPoint.getX()) / 2);
    middleY = startPoint.getY() + ((nextPoint.getY() - startPoint.getY()) / 2);

    GPoint middlePoint(middleX, middleY);
    return middlePoint;

}

/*
 *Recursive function fills the Sierpinski triangle points.
 *@param  - gw a reference to the Graphics Window object
 *@param  - leftPoint object reference point on the left vertex of the triangle
 *@param  - rightPoint object reference point on the right vertex of the triangle
 *@param  - topPoint object reference point on the top vertex of the triangle
 *@param  - startPoint object reference point on the start point of the triangle
*/

void drawNewPoint(GWindow &gw,
                  const GPoint &leftPoint,
                  const GPoint &rightPoint,
                  const GPoint &topPoint,
                  const GPoint &startPoint,
                  int count){

    if (count == 0)
        return;

    const GPoint& nextPoint = getNewRandomPoint(leftPoint, rightPoint, topPoint);
    GPoint middlePoint = getMiddlePoint(startPoint, nextPoint);
    gw.fillOval(middlePoint.getX(), middlePoint.getY(), 1, 1);
    pause(DRAW_PAUSE);
    count--;
    drawNewPoint(gw, leftPoint, rightPoint, topPoint, middlePoint, count);
}

/*
 *The function draws the Sierpinski triangle points
*/
void displaySierpinskiTriangle(){
    GWindow graphicsWindow(WINDOW_WIDTH, WINDOW_HEIGHT);
    graphicsWindow.setColor("BLUE");

    /*
     * draw three vertices of a triangle
    */
    GPoint topPoint(graphicsWindow.getWidth() / 2,0);
    GPoint leftPoint(0, graphicsWindow.getHeight());
    GPoint rightPoint(graphicsWindow.getWidth(), graphicsWindow.getHeight());
    graphicsWindow.fillOval(topPoint.getX(), topPoint.getY(), 2, 2);
    graphicsWindow.fillOval(leftPoint.getX(), leftPoint.getY(), 2, 2);
    graphicsWindow.fillOval(rightPoint.getX(), rightPoint.getY(), 2, 2);

    /*
     * draw a starting point for recursion
    */
    double newX = randomReal(0, graphicsWindow.getWidth());
    double newY = randomReal(0, graphicsWindow.getHeight());
    GPoint startPoint(newX, newY);
    graphicsWindow.fillOval(newX, newY, 1, 1);

    drawNewPoint(graphicsWindow, leftPoint, rightPoint, topPoint, startPoint, COUNT_POINTS);
}

int main()
{
    displaySierpinskiTriangle();
    return 0;
}
