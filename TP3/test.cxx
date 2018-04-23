
#include <GL/glut.h>
#include <GL/gl.h>
int l = 400;
int h = 400;
double a=0;
int LightPos[4] = {0,0,1,1};
int MatSpec [4] = {1,1,1,1};

void def_carre(void) {
    glPolygonMode(GL_BACK, GL_FILL);
    //glCullFace(GL_FRONT);
    glPolygonMode(GL_FRONT, GL_LINE);
    //glCullFace(GL_BACK);

    //glColor3f(0, 1, 0);
    glBegin(GL_POLYGON);
        glNormal3f(0, 0, 1);
        glVertex3f(1, 1, 0);
        glVertex3f(1, -1, 0);
        glVertex3f(-1, -1, 0);
        glVertex3f(-1, 1, 0);
    glEnd();
}

void Draw() { 
glEnable(GL_DEPTH_TEST); // Active le test de profondeur
  glEnable(GL_LIGHTING); // Active l'éclairage
    glEnable(GL_LIGHT0); //             Allume la lumière n°1
    glMaterialiv(GL_FRONT_AND_BACK,GL_SPECULAR,MatSpec);
    glMateriali(GL_FRONT_AND_BACK,GL_SHININESS,100);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(0,6,6,0,0,0,0,1,0);
    glRotated(a,0,1,0);
    glLightiv(GL_LIGHT0,GL_POSITION,LightPos);
    glutSolidSphere(1,50,50);
    a=+1;

    glutSwapBuffers();
    glutPostRedisplay(); 
}   

void redim(int width, int height) {
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(90, 1, 1, 100);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt( 
        0,6,6,
        0,0,0,
        0,1,0
    );
    l = width;
    h = height;
    glViewport(0, 0, width, height);
}

/* * * * * */

int main(int argc, char **argv) {
    glutInit(&argc, argv);
    glutInitWindowSize(l, h);
    glutInitWindowPosition(400, 50);
    glutInitDisplayMode(GLUT_RGBA | GLUT_SINGLE | GLUT_DEPTH);
    glutCreateWindow("BOITES");
    glutDisplayFunc(Draw);
    glutReshapeFunc(redim);
    
    glutMainLoop();
}
