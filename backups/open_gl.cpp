#include <iostream>
#include <GL/glew.h>
#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glext.h>

using namespace std;

int main(){
    GLenum err = glewInit();
    if (GLEW_OK != err)
    {
        fprintf(stderr, "Error %s\n", glewGetErrorString(err));
        exit(1);
    }
    fprintf(stdout, "Status: Using GLEW %s\n", glewGetString(GLEW_VERSION));
    
    if (GLEW_ARB_vertex_program)
        fprintf(stdout, "Status: ARB vertex programs available.\n");
    
    if (glewGetExtension("GL_ARB_fragment_program"))
        fprintf(stdout, "Status: ARB fragment programs available.\n");
    
    if (glewIsSupported("GL_VERSION_1_4  GL_ARB_point_sprite"))
        fprintf(stdout, "Status: ARB point sprites available.\n");
    
    
  return(0);
}

/*


freeglut3
freeglut3-dev
sudo apt-get install libglew1.5
sudo apt-get install libglew1.5-dev
sudo apt-get install libglu1-mesa
sudo apt-get install libglu1-mesa-dev
sudo apt-get install libgl1-mesa-glx
sudo apt-get install libgl1-mesa-dev

*/
