#pragma once

#include <QtCore>
#include <QtGui>

#include "Vertex.h"
#include "Matrix4f.h"
#include "Vector4f.h"

class ScanBuffer{
public:

  ScanBuffer(int width, int height) : image_(width, height, QImage::Format_RGB888){
	image_.fill(QColor(0,0,0));
    for(int i =0; i < height; i++){
      m_scanBufferMin.push_back(0);
      m_scanBufferMax.push_back(0);
    }
  }    

  // Set the 'y' value, and then where
  // to start scanning from and to.(min and max values)
  void DrawScanBuffer(int yCoord, int xMin, int xMax){
    m_scanBufferMin[yCoord] = xMin;
    m_scanBufferMax[yCoord] = xMax;
  }

  void FillShape(int yMin, int yMax){
    for(int j = yMin; j < yMax; j++){
      // Get the min and hte max value at the y-position
      int xMin = m_scanBufferMin[j];
	  int xMax = m_scanBufferMax[j];
            
	  for(int i = xMin; i < xMax; i++){
		image_.setPixelColor(i, j, QColor(255, 255, 255));
	  }
	}
  }

    
  // whichSide -- means which side of
  // scanbuffer(min or max) are we drawing on.
  void ScanConvertLine(Vertex minYVert, Vertex maxYVert, int whichSide){
	int xStart  = (int)minYVert.GetX();
	int xEnd    = (int)maxYVert.GetX();
    
	int yStart  = (int)minYVert.GetY();
	int yEnd    = (int)maxYVert.GetY();
	
	int yDist = yEnd - yStart;
	int xDist = xEnd - xStart;
	
	// No work to be done
	if(yDist <= 0){
	  return;
	}
	
	float xStep = (float)xDist/(float)yDist; // how far along x-axis are we moving.as we go down
	// are we moving to the left or the right.
	
	// Where we start from
	float curX = (float)xStart;
	
	for(int j = yStart; j < yEnd; j++){
	  if(whichSide==0){
		m_scanBufferMin[j] = curX;
	  }else{
		m_scanBufferMax[j] = curX;
	  }
      
	  curX += xStep;
	}
	
  }
  
  void ScanConvertTriangle(Vertex minYVert, Vertex midYVert, Vertex maxYVert, int handedness){
	ScanConvertLine(minYVert, maxYVert, handedness);
	ScanConvertLine(minYVert, midYVert, 1- handedness);
	ScanConvertLine(midYVert, maxYVert, 1- handedness);
  }
  
  
  void FillTriangle(Vertex v1, Vertex v2, Vertex v3){
	
	// 3 vertices -- assume sorted order
	Matrix4f screenSpaceTransform;
	screenSpaceTransform.InitScreenSpaceTransform(size_.width()/2,size_.height()/2);
    
	// Put things into the correct screen space, and then perform the
	// perspective divide. 
	Vertex minYVert = v1.Transform(screenSpaceTransform).PerspectiveDivide();	
	Vertex midYVert = v2.Transform(screenSpaceTransform).PerspectiveDivide();	
	Vertex maxYVert = v3.Transform(screenSpaceTransform).PerspectiveDivide();	
    
	// Sort vertices with 3 swaps
	if(maxYVert.GetY() < midYVert.GetY()){
	  Vertex temp = maxYVert;
	  maxYVert = midYVert;
	  midYVert = temp;
	}       
	if(midYVert.GetY() < minYVert.GetY()){
	  Vertex temp = midYVert;
	  midYVert = minYVert;
	  minYVert = temp;
	}       
	if(maxYVert.GetY() < midYVert.GetY()){
	  Vertex temp = maxYVert;
	  maxYVert = midYVert;
	  midYVert = temp;
	}       
	
	// Compute the area
	// max then mid or this does not work (why?)
	float area = minYVert.TriangleArea(maxYVert, midYVert);
	int handedness = area >= 0 ? 1 : 0; // ternary operator
	
	// Draw 3 lines and fill them in.
	ScanConvertTriangle(minYVert,midYVert,maxYVert,handedness);
	FillShape(minYVert.GetY(),maxYVert.GetY()); 
  }

  QImage image() const {return image_;}
  void clearImage() {image_.fill(QColor(0,0,0));}
  void setSize(const QSize& size) { 
	  size_ = size; 
	  image_ = image_.scaled(size);
	  clearImage();
  }

private:
  QImage image_;
  QSize size_;
  QVector<int> m_scanBufferMin;
  QVector<int> m_scanBufferMax;
};
