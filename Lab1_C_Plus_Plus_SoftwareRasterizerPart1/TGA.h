#ifndef TGA_H
#define TGA_H
/** @file TGA.h
 *  @brief Class for working with TGA images
 *  
 *  Note this is implemented as a header only library.
 *  This is to make this code easy to be shared.
 *
 *  The Truevision Graphics Adapter(TGA) image is another
 *  relatively simple graphics format for drawing raster
 *  images.
 *
 *  Most art programs (photoshop, GIMP, Paint.Net, etc.) 
 *  are able to load TGA images.
 *
 *  TGA images also go by the name of TARGA.
 *
 *  @author Mike Shah
 *  @bug No known bugs.
 */

// Standard Libraries
#include <string>
#include <fstream>

// User Libraries
#include "Color.h"

#include <cstring>

class TGA{
public:
    
    // Constructor
    // This gives us a blank canvas to draw on.
    //
    TGA(unsigned int _width, unsigned int _height){
        width = _width;
        height = _height;
        // This creates a new dynamically allocated array
        // with each element initialized to 128.
        // This will produce a 'gray' canvas.
        m_pixelData = new unsigned char[width*height*3];
        memset(m_pixelData, 128, width*height*3);
    }
    
    // Destructor
    ~TGA(){
        delete[] m_pixelData;
    }

    // Sets an individual pixel to a color.
    //
    // Note: We are working with a 1-D array and
    // each pixel consists of 3 values. There is a
    // little conversion going on here.
    //
    // Another way to think of this is that 'width'
    // is the pitch of an image, or how long a row is.
    // y*width moves us down a row, and x moves us along
    // that row. We multiply by 3, such that ColorRGB
    // is a tuple with 3 values(ColorRGBA would be by 4).
    // Finally, we increment appropriately to set r,g,b.
    void setPixelColor(int x, int y, ColorRGB c){
        m_pixelData[((y*width+x)*3)] = c.r;
        m_pixelData[((y*width+x)*3)+1] = c.g;
        m_pixelData[((y*width+x)*3)+2] = c.b;
    }

    // Helper function to write out a .tga image file
    void outputTGAImage(std::string fileName){
       std::ofstream myFile(fileName.c_str());
       if(myFile.is_open()){
            FILE *fp; fp = fopen(fileName.c_str(),"w+");
            fputs("P3\n",fp); fputs("320 320\n",fp); fputs("255\n",fp);
            for(int i =0; i < width*height*3;i++){
                    fprintf(fp,"%d",m_pixelData[i]); fputs(" ",fp); fputs("\n",fp);
            }
            fclose(fp);
            myFile.close();
       }
         
    }

    

private:
    unsigned char* m_pixelData;
    unsigned int width{0};
    unsigned int height{0};

};

#endif
