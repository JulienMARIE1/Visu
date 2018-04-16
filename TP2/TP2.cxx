//#include <GLUT/glut.h>
#include <GL/glut.h>
#include <iostream>
#include <cmath>
using namespace std;




void def_carre (void){
    glBegin(GL_POLYGON);
        glVertex2f(-0.5f, -0.5f);
        glVertex2f(0.5f, -0.5f);
        glVertex2f(0.5f, 0.5f);
        glVertex2f(-0.5f, 0.5f);
    glEnd();
    
    glFlush();  // Render now
}

void def_boite(int a){

    glPushMatrix();
    glColor3f(1.0f, 1.0f, 1.0f);
    def_carre();
    glPopMatrix();
    
    glPushMatrix();
    glRotated(90, 0, 1, 0);
    glTranslated(0.5,0,-0.5);
    glColor3f(1.0f, 0.0f, 0.0f);
    def_carre();
    glPopMatrix();

    glPushMatrix();
    glRotated(90, 0, 1, 0);
    glTranslated(0.5,0,0.5);
    glColor3f(0.0f, 0.0f, 1.0f);
    def_carre();
    glPopMatrix();

    glPushMatrix();
    glRotated(90, 1, 0, 0);
    glTranslated(0,-0.5,-0.5);
    glColor3f(0.0f, 1.0f, 0.0f);
    def_carre();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.0, 0.0, -1.0);
   
    glColor3f(0.0, 1.0, 1.0);
    def_carre();
    glPopMatrix();
    
}

/* la fonction "affichage" est appelée a chaque fois qu'un événement de mise
 à jour de l'affichage est détecté */
void affichage(void){
		glEnable(GL_DEPTH_TEST);
        
		glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode (GL_MODELVIEW);

    def_boite(1);
    glutSwapBuffers();

}
/* la fonction "redim" est appelée : une fois a la creation de la fenêtre ;
 ensuite à chaque fois que la fenêtre est redimmensionnée
 width et height representent la taille de la fenêtre */
void redim(int width, int height){
    glViewport(0, 0, width, height);
    glLoadIdentity ();
    gluLookAt (2.0, -1.0, 2,
               0, 0, 0,
               0, 1, 0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(70.0, 1.0, 1.0, 5.0);
}


int main (int argc, char * argv[]){
    glutInit(&argc, argv);
    /* Taille et emplacement de la fenêtre */
    glutInitWindowSize(400, 400);
    glutInitWindowPosition(200, 100);
    /* Choix du type et d'affichage RGBA (mode couleur le plus fréquent), tampon de profondeur
     et d'un double buffer */
    glutInitDisplayMode(GLUT_RGBA | GLUT_DEPTH | GLUT_DOUBLE);
    /* Création de la fenêtre */
    glutCreateWindow("GLUTfenetre");
    /* Association des callback pour cette fenêtre */
    glutDisplayFunc(affichage);
    glutReshapeFunc(redim);
    glutMainLoop();
    /* On entre dans la boucle d'événements */
    return 0;
}
