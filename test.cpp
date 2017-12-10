#include <GL/glut.h>
#include <GL/freeglut.h>
#include <math.h>


void render(){

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glColor3f(0.0, 0.0, 0.0);
    for(int i =0; i <= 8; i++){
		glBegin(GL_LINES);
		  glVertex2f(10*i+1, 1.0);
		  glVertex2f(10*i+1, 81.0);
		  glVertex2f(1.0,10*i+1);
		  glVertex2f(81.0,10*i+1);
		glEnd();
    }
    
    glBegin(GL_TRIANGLE_FAN);
        glColor3f(1,1,1);
        glVertex2f(6,6);
        for(int n=0; n<=50; n++){
            float const t = 2 * M_PI * (float)n / 50.0;
        glColor3f(1,1,1);
            glVertex2f(6+ sin(t) * 4, 6 + cos(t) * 4);
        }
    glEnd();
                const unsigned char test[100] = "test";
				glColor4f(0.0,0.0,0.0,0.0);
				glRasterPos2i(1,1);
				glutBitmapString(GLUT_BITMAP_HELVETICA_18, test);
    glutSwapBuffers();
}

int main (int argc, char **argv){
    

    glutInit(&argc,argv);	
	glutInitDisplayMode (GLUT_DEPTH | GLUT_SINGLE | GLUT_RGB);
	glutInitWindowPosition (200, 200);
	glutInitWindowSize (700, 700);	
	glutCreateWindow ("Reversi");
    glClearColor(0.0,0.5,0.0,0.0);
	glMatrixMode (GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D (0.0, 82.0, 0.0,100.0);
    glutDisplayFunc(render);
    
    glutMainLoop();
}
