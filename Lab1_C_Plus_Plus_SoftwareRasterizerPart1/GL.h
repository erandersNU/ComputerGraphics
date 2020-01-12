/** @file GL.h
 *  @brief Our Great Looking Software Render functions
 *  
 *  Most of these functions have some correspondance
 *  with the OpenGL library.
 *
 *  @author Mike Shah
 *  @bug No known bugs.
 */
// Graphic Pipeline States
// Globals that define how to draw our shapes.
const int LINE = 0;
const int FILL = 1;
int glFillMode = LINE;

// By default the Fill mode is LINE
void glPolygonMode(const int mode){
    glFillMode = mode;
}
