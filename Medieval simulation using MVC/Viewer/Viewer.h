//
// Created by merom on 6/17/2023.
//

#ifndef HOMEWORK3_VIEWER_H
#define HOMEWORK3_VIEWER_H

#include <memory>
#include "../Utilities/Geometry.h"
#include "../SimObject/SimObject.h"

#define DEFAULT_DISPLAY_SIZE 25
#define DEFAULT_ZOOM 2.0
#define START_COORDINATES -10


/*
 * measurements units in 10 k'm
 * north = the positive part of y-axis, 0_o degrees
 * east = the positive part of x-axis, 90_o degrees 1/2 pi
 * south = the negative part of y-axis, 180_o degrees pi
 * east = the negative part of x-axis, 270_o degrees 3/2 pi
 *
 * credit for Yohanatan Hanun from the computer science departure tel-hai
 * */

class Viewer{

public:
    Viewer();
    // set back to the default values
    void setDefault();
    // set the size
    void setSize(int newSize);
    // set the zoom factor
    void setZoom(float newZoom);
    // set the pan
    void pan(float x, float y);
    // show the view
    void show();



private:
    float zoom ;
    Point origin;
    int displaySize;
    static shared_ptr<SimObject> getObjByPoint(const Point & pnt);
};
#endif //HOMEWORK3_VIEWER_H
