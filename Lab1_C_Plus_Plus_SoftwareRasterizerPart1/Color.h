#ifndef COLOR_H
#define COLOR_H

/** @file Color.h
 *  @brief structs for color.
 *  
 *  Note this is implemented as a header only library.
 *  This is to make this code easy to be shared.
 *
 *  Typically in graphics we work with RGB or RGBA.
 *  In other domains color may be stored as
 *  BGR, GRBA, and every other permutation.
 *
 *    
 *  @author Mike Shah
 *  @bug No known bugs.
 */

struct ColorRGB{
    unsigned char r,g,b;
};

struct ColorRGBA{
    unsigned char r,g,b,a;
};

#endif
