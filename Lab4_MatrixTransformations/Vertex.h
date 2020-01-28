#pragma once

#include "Vector4f.h"
#include "Matrix4f.h"

class Vertex{

public:
    Vertex(){	
    	m_pos.Set(0.0f,0.0f,0.0f,1.0f);
	}

    Vertex(float x, float y){
    	m_pos.Set(x,y,0.0f,1.0f);
	}
    
    Vertex(float x, float y, float z){
    	m_pos.Set(x,y,z,1.0f);
	}
    
    Vertex(float x, float y, float z, float w){
    	m_pos.Set(x,y,z,w);
	}
   
	// Initialize a vertex with a Vector4f position
	Vertex(Vector4f pos){
		m_pos = pos;
	}
 
	// How we will move vertices around.
	// Essentially return a new vertex that is transformed.
	Vertex Transform(Matrix4f transform){
		return transform.Transform(m_pos);
	}

	// Need to divide by 'w' to put into perspective
	// of each of our vertices.
	Vertex PerspectiveDivide(){
		return Vertex(	m_pos.GetX() / m_pos.GetW(),
						m_pos.GetY() / m_pos.GetW(),
						m_pos.GetZ() / m_pos.GetW(),
						m_pos.GetW()); // NOTE: We are not dividing 'w' by 'w'
										// We typically keep 'w' preservered.
			// You can think of there really being 2 'z' values in 3d rendering
			// One is used for getting perspective, that is dividing each point
			// by this value. The other 'z' value, found in x,y,z, is used to figure
			// out which objects 'occlude' the other, or overlap them.
	}

    void SetX(float x) { m_pos.SetX(x); }    
    void SetY(float y) { m_pos.SetY(y); }    
    void SetZ(float z) { m_pos.SetZ(z); }    
    void SetW(float w) { m_pos.SetW(w); }    

    float GetX(){ return m_pos.GetX(); }
    float GetY(){ return m_pos.GetY(); }
    float GetZ(){ return m_pos.GetZ(); }
    float GetW(){ return m_pos.GetW(); }


    float TriangleArea(Vertex b, Vertex c){
        float x1 = b.GetX() - m_pos.GetX();
        float y1 = b.GetY() - m_pos.GetY();
        
        float x2 = c.GetX() - m_pos.GetX();
        float y2 = c.GetY() - m_pos.GetY();

        return 0.5* ((x1 * y2) - (x2 * y1));
    }

private:
	Vector4f m_pos;
};
