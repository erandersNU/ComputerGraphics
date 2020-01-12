#ifndef MATHS_H
#define MATHS_H

/** @file Maths.h
 *  @brief Structs with math data types
 *  
 *  Note this is implemented as a header only library.
 *  This is to make this code easy to be shared.
 *
 *
 *  @author Mike Shah
 *  @bug No known bugs.
 */


// Structure for plotting integer points.
struct Vec2{
    int x,y;
    // Default Constructor   
    Vec2(){
        x = y = 0;
    }
    // Constructor with two arguments.
    Vec2(int _x, int _y): x{_x},y{_y} {
    }
    // Operator Overloads
    // Below is a list of operations vectors can perform
    // This is a technique known as operating overloading.
    // Add operator
    Vec2 operator+(const Vec2& a) const{
        Vec2 result;
        result.x = this->x + a.x;
        result.y = this->y + a.y;
        return result;
    } 
    // Subtract operator
    Vec2 operator-(const Vec2& a) const{
        Vec2 result;
        result.x = this->x - a.x;
        result.y = this->y - a.y;
        return result;
    }
    // Scalar Multiplication
    Vec2 operator*(const float& a) const{
        Vec2 result;
        result.x = this->x * a;
        result.y = this->y * a;
        return result;
    }
};




#endif
