/*
 * A simple GLUT program we can use as an example of how to adapt 3D graphics
 * code to VR using MinVR2.
 */
#include <iostream>
#include <GL/glut.h>  // GLUT, include glu.h and gl.h
#include <math.h>

/* Global variables */
char title[] = "3D Shapes";

double cameraPos[3] = {0.0f, 0.0f, 15.0f};
double targetPos[3] = {0.0f, 0.0f, 0.0f};
double cameraAim[3] = {0.0f, 1.0f, 0.0f};
double radius = 15.0;
double incAngle = -0.1f;
double horizAngle = 0.0;
double vertAngle = 0.0;

/* Initialize OpenGL Graphics */
void initGL() {
  glutInitDisplayMode (GLUT_DEPTH);
  // Set background color to black and opaque
  glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
  // Set background depth to farthest
  glClearDepth(1.0f);
  // Enable depth testing for z-culling
  glEnable(GL_DEPTH_TEST);
  // Set the type of depth-test
  glDepthFunc(GL_LEQUAL);
  // Enable smooth shading
  glShadeModel(GL_SMOOTH);
  // Nice perspective corrections
  glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
}

/* Handler for window-repaint event. Called back when the window first
   appears and whenever the window needs to be re-painted. */
void display() {
  // Clear color and depth buffers
   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); 
   // Enable depth testing for z-culling
   glEnable(GL_DEPTH_TEST);
   // Set the type of depth-test
   glDepthFunc(GL_LEQUAL);

   glMatrixMode(GL_MODELVIEW);     // To operate on model-view matrix
 
   // Render a color-cube consisting of 6 quads with different colors
   glLoadIdentity();                 // Reset the model-view matrix

   cameraPos[0] = radius * cos(horizAngle) * cos(vertAngle);
   cameraPos[1] = -radius * sin(vertAngle);
   cameraPos[2] = radius * sin(horizAngle) * cos(vertAngle);

   cameraAim[0] = cos(horizAngle) * sin(vertAngle);
   cameraAim[1] = cos(vertAngle);
   cameraAim[2] = sin(horizAngle) * sin(vertAngle);
   
   gluLookAt (cameraPos[0], cameraPos[1], cameraPos[2],
              targetPos[0], targetPos[1], targetPos[2],
              cameraAim[0], cameraAim[1], cameraAim[2]);

   glBegin(GL_LINES);
     glColor3f(1.0, 1.0, 0.0);
     glVertex3f(8.0, 0.0, 0.0);
     glVertex3f(0.0, 0.0, 0.0);

     glColor3f(0.0, 1.0, 1.0);
     glVertex3f(0.0, 8.0, 0.0);
     glVertex3f(0.0, 0.0, 0.0);

     glColor3f(1.0, 0.0, 1.0);
     glVertex3f(0.0, 0.0, 8.0);
     glVertex3f(0.0, 0.0, 0.0);

   glEnd();


   glBegin(GL_QUADS);                // Begin drawing the color cube with 6 quads
      // Top face (y = 1.0f)
      // Define vertices in counter-clockwise (CCW) order with normal
      // pointing out
     glColor3f(0.0f, 0.5f, 0.0f);     // Green
     glVertex3f( 1.0f, 1.0f, -1.0f);
     glVertex3f(-1.0f, 1.0f, -1.0f);
     glVertex3f(-1.0f, 1.0f,  1.0f);
     glVertex3f( 1.0f, 1.0f,  1.0f);
 
     // Bottom face (y = -1.0f)
     glColor3f(0.5f, 0.25f, 0.0f);     // Orange
     glVertex3f( 1.0f, -1.0f,  1.0f);
     glVertex3f(-1.0f, -1.0f,  1.0f);
     glVertex3f(-1.0f, -1.0f, -1.0f);
     glVertex3f( 1.0f, -1.0f, -1.0f);
 
     // Front face  (z = 1.0f)
     glColor3f(0.5f, 0.0f, 0.0f);     // Red
     glVertex3f( 1.0f,  1.0f, 1.0f);
     glVertex3f(-1.0f,  1.0f, 1.0f);
     glVertex3f(-1.0f, -1.0f, 1.0f);
     glVertex3f( 1.0f, -1.0f, 1.0f);
   
     // Back face (z = -1.0f)
     glColor3f(0.5f, 0.5f, 0.0f);     // Yellow
     glVertex3f( 1.0f, -1.0f, -1.0f);
     glVertex3f(-1.0f, -1.0f, -1.0f);
     glVertex3f(-1.0f,  1.0f, -1.0f);
     glVertex3f( 1.0f,  1.0f, -1.0f);
 
     // Left face (x = -1.0f)
     glColor3f(0.0f, 0.0f, 0.5f);     // Blue
     glVertex3f(-1.0f,  1.0f,  1.0f);
     glVertex3f(-1.0f,  1.0f, -1.0f);
     glVertex3f(-1.0f, -1.0f, -1.0f);
     glVertex3f(-1.0f, -1.0f,  1.0f);
 
     // Right face (x = 1.0f)
     glColor3f(0.5f, 0.0f, 0.5f);     // Magenta
     glVertex3f(1.0f,  1.0f, -1.0f);
     glVertex3f(1.0f,  1.0f,  1.0f);
     glVertex3f(1.0f, -1.0f,  1.0f);
     glVertex3f(1.0f, -1.0f, -1.0f);
   glEnd();  // End of drawing color-cube
 

   
   glTranslatef(1.5f, 7.0f, 0.0f);  // Move right and into the screen
 
   glBegin(GL_QUADS);                // Begin drawing the color cube with 6 quads
      // Top face (y = 1.0f)
      // Define vertices in counter-clockwise (CCW) order with normal
      // pointing out
     glColor3f(0.0f, 0.5f, 0.0f);     // Green
     glVertex3f( 1.0f, 1.0f, -1.0f);
     glVertex3f(-1.0f, 1.0f, -1.0f);
     glVertex3f(-1.0f, 1.0f,  1.0f);
     glVertex3f( 1.0f, 1.0f,  1.0f);
 
     // Bottom face (y = -1.0f)
     glColor3f(0.5f, 0.25f, 0.0f);     // Orange
     glVertex3f( 1.0f, -1.0f,  1.0f);
     glVertex3f(-1.0f, -1.0f,  1.0f);
     glVertex3f(-1.0f, -1.0f, -1.0f);
     glVertex3f( 1.0f, -1.0f, -1.0f);
 
     // Front face  (z = 1.0f)
     glColor3f(0.5f, 0.0f, 0.0f);     // Red
     glVertex3f( 1.0f,  1.0f, 1.0f);
     glVertex3f(-1.0f,  1.0f, 1.0f);
     glVertex3f(-1.0f, -1.0f, 1.0f);
     glVertex3f( 1.0f, -1.0f, 1.0f);
   
     // Back face (z = -1.0f)
     glColor3f(0.5f, 0.5f, 0.0f);     // Yellow
     glVertex3f( 1.0f, -1.0f, -1.0f);
     glVertex3f(-1.0f, -1.0f, -1.0f);
     glVertex3f(-1.0f,  1.0f, -1.0f);
     glVertex3f( 1.0f,  1.0f, -1.0f);
 
     // Left face (x = -1.0f)
     glColor3f(0.0f, 0.0f, 0.5f);     // Blue
     glVertex3f(-1.0f,  1.0f,  1.0f);
     glVertex3f(-1.0f,  1.0f, -1.0f);
     glVertex3f(-1.0f, -1.0f, -1.0f);
     glVertex3f(-1.0f, -1.0f,  1.0f);
 
     // Right face (x = 1.0f)
     glColor3f(0.5f, 0.0f, 0.5f);     // Magenta
     glVertex3f(1.0f,  1.0f, -1.0f);
     glVertex3f(1.0f,  1.0f,  1.0f);
     glVertex3f(1.0f, -1.0f,  1.0f);
     glVertex3f(1.0f, -1.0f, -1.0f);
   glEnd();  // End of drawing color-cube
 
   // Render a pyramid consists of 4 triangles
   //   glLoadIdentity();                  // Reset the model-view matrix
   glTranslatef(-1.5f, 0.0f, -6.0f);  // Move left and into the screen
 
   glBegin(GL_TRIANGLES);           // Begin drawing the pyramid with 4 triangles
      // Front
      glColor3f(1.0f, 0.0f, 0.0f);     // Red
      glVertex3f( 0.0f, 1.0f, 0.0f);
      glColor3f(0.0f, 1.0f, 0.0f);     // Green
      glVertex3f(-1.0f, -1.0f, 1.0f);
      glColor3f(0.0f, 0.0f, 1.0f);     // Blue
      glVertex3f(1.0f, -1.0f, 1.0f);
 
      // Right
      glColor3f(1.0f, 0.0f, 0.0f);     // Red
      glVertex3f(0.0f, 1.0f, 0.0f);
      glColor3f(0.0f, 0.0f, 1.0f);     // Blue
      glVertex3f(1.0f, -1.0f, 1.0f);
      glColor3f(0.0f, 1.0f, 0.0f);     // Green
      glVertex3f(1.0f, -1.0f, -1.0f);
 
      // Back
      glColor3f(1.0f, 0.0f, 0.0f);     // Red
      glVertex3f(0.0f, 1.0f, 0.0f);
      glColor3f(0.0f, 1.0f, 0.0f);     // Green
      glVertex3f(1.0f, -1.0f, -1.0f);
      glColor3f(0.0f, 0.0f, 1.0f);     // Blue
      glVertex3f(-1.0f, -1.0f, -1.0f);
 
      // Left
      glColor3f(1.0f,0.0f,0.0f);       // Red
      glVertex3f( 0.0f, 1.0f, 0.0f);
      glColor3f(0.0f,0.0f,1.0f);       // Blue
      glVertex3f(-1.0f,-1.0f,-1.0f);
      glColor3f(0.0f,1.0f,0.0f);       // Green
      glVertex3f(-1.0f,-1.0f, 1.0f);
   glEnd();   // Done drawing the pyramid

  
   // Swap the front and back frame buffers (double buffering)
   glutSwapBuffers();
}

/* Handler for window re-size event. Called back when the window first
   appears and whenever the window is re-sized with its new width and
   height */
void reshape(GLsizei width, GLsizei height) {  // GLsizei for non-negative integer
   // Compute aspect ratio of the new window
   if (height == 0) height = 1;                // To prevent divide by 0
   GLfloat aspect = (GLfloat)width / (GLfloat)height;
 
   // Set the viewport to cover the new window
   glViewport(0, 0, (GLsizei)width, (GLsizei)height);
 
   // Set the aspect ratio of the clipping volume to match the viewport
   glMatrixMode(GL_PROJECTION);  // To operate on the Projection matrix
   glLoadIdentity();             // Reset

   // Enable perspective projection with fovy, aspect, zNear and zFar
   gluPerspective(1.6*45.0f, aspect, 0.1f, 100.0f);

   //The .m is the GLfloat* you are accessing
   //glMultMatrix( GLKMatrix4MakePerspective(45.0f, aspect, 0.1f,100.0f ).m ); 
}

void processMouseEvent(int button, int state, int x, int y) {

  if (state == GLUT_UP) {
    if (button == GLUT_LEFT_BUTTON) {
      radius += 5.0 * incAngle;
    } else {
      radius -= 5.0 * incAngle;
    }
    
    glutPostRedisplay();
  }
}

void processSpecialKeys(int key, int xx, int yy) {

	float fraction = 0.1f;

	switch (key) {
		case GLUT_KEY_LEFT :
			horizAngle -= incAngle;
			break;
		case GLUT_KEY_RIGHT :
			horizAngle += incAngle;
			break;
		case GLUT_KEY_UP :
      vertAngle -= incAngle;
			break;
		case GLUT_KEY_DOWN :
      vertAngle += incAngle;
			break;
	}

  if (horizAngle > 6.283185) horizAngle -= 6.283185;
  if (horizAngle < 0.0) horizAngle += 6.283185;

  if (vertAngle > 6.283185) vertAngle -= 6.283185;
  if (vertAngle < 0.0) vertAngle += 6.283185;

  glutPostRedisplay();
}

/* Main function: GLUT runs as a console application starting at main() */
int main(int argc, char** argv) {
   glutInit(&argc, argv);            // Initialize GLUT
   glutInitDisplayMode(GLUT_DOUBLE | GLUT_DEPTH); // Enable double buffered mode
   glutInitWindowSize(640, 480);   // Set the window's initial width & height
   glutInitWindowPosition(50, 50); // Position the window's initial top-left corner
   glutCreateWindow(title);          // Create window with the given title


   // Register event callback for mouse events.
   glutMouseFunc(processMouseEvent);
   glutSpecialFunc(processSpecialKeys);

   
   // Register callback handler for window re-paint event
   glutDisplayFunc(display);
   // Register callback handler for window re-size event
   glutReshapeFunc(reshape);
   initGL();                       // Our own OpenGL initialization
   glutMainLoop();                 // Enter the infinite event-processing loop
   return 0;
}
