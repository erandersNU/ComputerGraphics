#ifndef VERTEX4F_H
#define VERTEX4F_H
// Notes:
// It is recommened to compile with
// -O3 to ensure optimizations are
// applied to this math library
//
// Library requires C++17
#include <cmath> // sqrt
#include <string> 

class Vector4f{
public:

    // Default Constructor
    // Creates the zero vector
    Vector4f(){
        m_x = m_y = m_z = 0.0f;
        m_w = 1.0f;
    }
    
    // Initialize all components to one value
    Vector4f(float value): m_x(value),m_y(value),m_z(value),m_w(value){
	}

	// Slight shortcut for initializing all componets to one componetn and w to 1.0.
    Vector4f(float x, float y, float z): m_x(x),m_y(y),m_z(z){
    	m_w = 1.0f;
	}
    // Initialize all components individually
    Vector4f(float x, float y, float z, float w): m_x(x),m_y(y),m_z(z),m_w(w){
    }

    // Vector addition
    Vector4f Add(Vector4f b){
        return Vector4f(m_x + b.GetX(),
                        m_y + b.GetY(),
                        m_z + b.GetZ(),
						m_w + b.GetW());
    }
    // Vector scalar addition
    Vector4f Add(float value){
        return Vector4f(m_x + value,
                        m_y + value,
                        m_z + value,
						m_w + value);
    }
    // Vector Subtraction 
    Vector4f Sub(Vector4f b){
        return Vector4f(m_x - b.GetX(),
                        m_y - b.GetY(),
                        m_z - b.GetZ(),
						m_w - b.GetW());
    }
    // Vector scalar subtraction
    Vector4f Sub(float value){
        return Vector4f(m_x - value,
                        m_y - value,
                        m_z - value,
						m_w - value);
    }
    // Vector multiplication
    Vector4f Mul(Vector4f b){
        return Vector4f(m_x * b.GetX(),
                        m_y * b.GetY(),
                        m_z * b.GetZ(),
						m_w * b.GetW());
    }
    // Vector scalar multiplication
    Vector4f Mul(float value){
        return Vector4f(m_x * value,
                        m_y * value,
                        m_z * value,
						m_w * value);
    }
    // Vector Division
    Vector4f Div(Vector4f b){
        return Vector4f(m_x / b.GetX(),
                        m_y / b.GetY(),
                        m_z / b.GetZ(),
						m_w / b.GetW());
    }
    // Vector scalar Division
    Vector4f Div(float value){
        return Vector4f(m_x / value,
                        m_y / value,
                        m_z / value,
						m_w / value);
    }
    // Get Absolute value of vector
    Vector4f Abs(){
        return Vector4f(std::abs(m_x), std::abs(m_y), std::abs(m_z), std::abs(m_w));
    }    


    // Compute the magnitude of a vector (synonymous with 'length')
    float Magnitude(){
        return (float)sqrt( m_x*m_x + m_y*m_y + m_z*m_z + m_w*m_w);
    }

    // Returns maximum component of vector
    float Max() {
        return std::max(std::max(m_x,m_y), std::max(m_z,m_w));
    }

    // Compute dot product of 2 vecors
    float Dot(Vector4f b){
        return  m_x * b.GetX() +
                m_y * b.GetY() +
                m_z * b.GetZ() + 
				m_w * b.GetW();
    }

    // Compute the cross product
    // Note w component is simply 0
    Vector4f Cross(Vector4f b){
        float x_ = m_y * b.GetZ() - m_z * b.GetY();
        float y_ = m_z * b.GetX() - m_x * b.GetZ();
        float z_ = m_x * b.GetY() - m_y * b.GetX();
        
        return Vector4f(x_,y_,z_, 0.0f);
    }

    // Normalizes our vector
    Vector4f Normalized(){
        float magnitude = Magnitude();
        return Vector4f(m_x/magnitude, m_y/magnitude, m_z/magnitude, m_w/magnitude);
    }

    std::string ToString(){
        return "("  + std::to_string(m_x)+","
                    + std::to_string(m_y)+","
                    + std::to_string(m_z)+","
                    + std::to_string(m_w)+")";
    }

    bool Equals(Vector4f b){
        if( m_x == b.GetX() &&
            m_y == b.GetY() &&
            m_z == b.GetZ() &&
			m_w == b.GetW()){
            return true;
        }
        return false;
    }

    // Setters
    void Set(float x, float y, float z){
        m_x = x;
        m_y = y;
        m_z = z;
    }
    
	void Set(float x, float y, float z, float w){
        m_x = x;
        m_y = y;
        m_z = z;
		m_w = w;
    }

    // Getters
    void SetX(float x) { m_x = x; }
    void SetY(float y) { m_y = y; }
   	void SetZ(float z) { m_z = z; }
    void SetW(float w) { m_w = w; }
    
	// Getters
    float GetX() { return m_x; }
    float GetY() { return m_y; }
    float GetZ() { return m_z; }
    float GetW() { return m_w; }

private:
    // Components of the vector
    float m_x;
    float m_y;
    float m_z;
    float m_w;
};

#endif
