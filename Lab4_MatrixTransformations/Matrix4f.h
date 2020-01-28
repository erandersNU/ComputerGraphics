#ifndef MATRIX4F_H
#define MATRIX4F_H


class Matrix4f{
public:
    // Initializes an identity matrix
    Matrix4f(){
        Identity();
    }

    // Compute the identity matrix
    void Identity(){
        m[0][0] = 1;    m[0][1] = 0; m[0][2] = 0; m[0][3] = 0;
        m[1][0] = 0;    m[1][1] = 1; m[1][2] = 0; m[1][3] = 0;
        m[2][0] = 0;    m[2][1] = 0; m[2][2] = 1; m[2][3] = 0;
        m[3][0] = 0;    m[3][1] = 0; m[3][2] = 0; m[3][3] = 1;
    }

	// Probably something we do not need for OpenGL
	// However, useful for our software renderer.
	// Essentially this is putting things into screen space
	// for our renderer.
	// Essentially we are putting things directly into pixel space.
	// Note: See how the 'x' and 'y' at the end of the matrix is set to halfwidth
	// and halfHeight as well.
	// We make the halfHeight negative at [1][1] because 0 is the top of the screen. 
	void InitScreenSpaceTransform(float halfWidth,float halfHeight){
        m[0][0] = halfWidth;    m[0][1] = 0; 			m[0][2] = 0; m[0][3] = halfWidth;
        m[1][0] = 0;    		m[1][1] = -halfHeight; 	m[1][2] = 0; m[1][3] = halfHeight;
        m[2][0] = 0;    		m[2][1] = 0; 			m[2][2] = 1; m[2][3] = 0;
        m[3][0] = 0;    		m[3][1] = 0; 			m[3][2] = 0; m[3][3] = 1;
	}

    void InitTranslation(float x,float y,float z) {
        // TODO:
        // Implement  correct translation matrix
        m[0][0] = 0;    m[0][1] = 0; m[0][2] = 0; m[0][3] = 0;
        m[1][0] = 0;    m[1][1] = 0; m[1][2] = 0; m[1][3] = 0;
        m[2][0] = 0;    m[2][1] = 0; m[2][2] = 0; m[2][3] = 0;
        m[3][0] = 0;    m[3][1] = 0; m[3][2] = 0; m[3][3] = 0;
    }

    // x,y,z as angles
    void InitRotation(float x, float y, float z){
        // Create three matrices to rotate around.
        Matrix4f rx;
        Matrix4f ry;
        Matrix4f rz;
        
        // TODO:
        rz.Set(0,0, 0);         rz.Set(0,1,0);      rz.Set(0,2,0);  rz.Set(0,3,0); 
        rz.Set(1,0, 0);         rz.Set(1,1,0);      rz.Set(1,2,0);  rz.Set(1,3,0);
        rz.Set(2,0, 0);         rz.Set(2,1,0);      rz.Set(2,2,1);  rz.Set(2,3,0);
        rz.Set(3,0, 0);         rz.Set(3,1,0);      rz.Set(3,2,0);  rz.Set(3,3,1);
    
        rx.Set(0,0, 1);         rx.Set(0,1,0);      rx.Set(0,2,0);  rx.Set(0,3,0); 
        rx.Set(1,0, 0);         rx.Set(1,1,0);      rx.Set(1,2,0);  rx.Set(1,3,0);
        rx.Set(2,0, 0);         rx.Set(2,1,0);      rx.Set(2,2,0);  rx.Set(2,3,0);
        rx.Set(3,0, 0);         rx.Set(3,1,0);      rx.Set(3,2,0);  rx.Set(3,3,1);

        ry.Set(0,0, 0);         ry.Set(0,1,0);      ry.Set(0,2,0);  ry.Set(0,3,0); 
        ry.Set(1,0, 0);         ry.Set(1,1,1);      ry.Set(1,2,0);  ry.Set(1,3,0);
        ry.Set(2,0, 0);         ry.Set(2,1,0);      ry.Set(2,2,0);  ry.Set(2,3,0);
        ry.Set(3,0, 0);         ry.Set(3,1,0);      ry.Set(3,2,0);  ry.Set(3,3,1);
  
        // Multiply the matrices
        // Copy values into 'm'
        SetMatrix(rz.Multiply(ry.Multiply(rx))); 
    }
    
    // Initialize at a scale.
    void InitScale(float x,float y,float z){
        // Not implemented
    }

    // Initialize Perspective Matrix.
    void InitPerspective(float fov, float aspectRatio, float zNear, float zFar){
        float tanHalfFOV = tan(fov/2 * M_PI / 180);    
        float zRange = zNear - zFar;
        m[0][0] = 1.0f/(tanHalfFOV*aspectRatio);m[0][1] = 0;                m[0][2] = 0; m[0][3] = 0;
        m[1][0] = 0;                            m[1][1] = 1.0f/tanHalfFOV;  m[1][2] = 0; m[1][3] = 0;
        m[2][0] = 0;                            m[2][1] = 0;                m[2][2] = (-zNear-zFar)/zRange; m[2][3] =
2*zFar*zNear/zRange;
        m[3][0] = 0;                            m[3][1] = 0;                m[3][2] = 1; m[3][3] = 1;
    }

    // Initialize Orthographic Matrix.
    void InitOrthographic(float left, float right, float bottom, float top, float near, float far){
        // Not implemented
    }

    // Transform here is simply returning a 'new' vector
    // which will move our 'vertex' to a new position.
	Vector4f Transform(Vector4f b){
    // TODO: Implement transform
    //       The pattern is given for the first component of the vector.
    //       Fill in the values for the '0.0' for y,z,w
        return Vector4f(
            m[0][0] * b.GetX() + m[0][1] * b.GetY() + m[0][2] * b.GetZ() + m[0][3] * b.GetW(),
            0.0,
            0.0,
            0.0);
	}


    // Here is an example of how to do a slow matrix multiplication with loops.
    // (Note: It is possible a smart enough compiler would unroll the values, but
    //        typically it is best to explicitly perform the individual dot products).
    Matrix4f Multiply(Matrix4f b){
        Matrix4f result;
        for(int i=0; i < 4; i++){
            for(int j =0; j < 4; j++){
                float dot = m[i][0] * b.Get(0,j)+
                            m[i][1] * b.Get(1,j)+
                            m[i][2] * b.Get(2,j)+
                            m[i][3] * b.Get(3,j);
                result.Set(i,j,dot); 
            }
        }

        return result;
    }
    
    // Set index of matrix to a value
    void Set(unsigned int i, unsigned int j, float value){
        m[i][j] = value;
    }

    // Retrieve value matrix.
    float Get(unsigned int i, unsigned int j){
        return m[i][j];
    }

    // Set the matrix values of internal matrix 'm' to
    // those of another.
    void SetMatrix(Matrix4f b){
        for(int i=0; i < 4; i++){
            for(int j=0; j < 4; j++){
                m[i][j] = b.Get(i,j);
            }
        }
    }
    

private:
    float m[4][4];
};

#endif
