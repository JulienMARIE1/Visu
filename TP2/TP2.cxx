#include <GLUT/glut.h>
//#include <GL/glut.h>
#include <iostream>
#include <cmath>
#include <unistd.h>
using namespace std;

bool rotated = false;
bool rotated1 = true;
bool rotated2 = true;

void affichage();

GLfloat boite1[16] = {1, 0, 0, 0,
                      0, 1, 0, 0,
                      0, 0, 1, 0,
                      0, 0, 0, 1};
GLfloat boite2[16]= {1, 0, 0, 0,
                     0, 1, 0, 0,
                     0, 0, 1, 0,
                     0, 0, 0, 1};

/* @brief : défini les faces du carré
 *
 */
void def_carre (void){
    glPolygonMode(GL_FRONT, GL_FILL);
    glPolygonMode(GL_BACK, GL_LINE);
    //glEnable(GL_CULL_FACE);
    //glCullFace(GL_BACK);

        glBegin(GL_POLYGON);
        glVertex3f(0.5, 0.5, 0);
        glVertex3f(0.5, -0.5, 0);
        glVertex3f(-0.5, -0.5, 0);
        glVertex3f(-0.5, 0.5, 0);
    glEnd();
}

/* @brief : défini les axes pour le plan et les boites */
void def_axis(int a) {
    glColor3f(1, 1, 1);
    
    glBegin(GL_LINES);
    // x
    glColor3f(1,0,0);
    glVertex3f(0, 0, 0);
    glVertex3f(a, 0, 0);
    
    // y
    glColor3f(0,1,0);
    glVertex3f(0, 0, 0);
    glVertex3f(0, a, 0);
    
    // z
    glColor3f(0,0,1);
    glVertex3f(0, 0, 0);
    glVertex3f(0, 0, a);
    glEnd();
}

/* @brief : dessine la boite face par face en appliquant des translations et rotation */

void def_boite(int a){
    glPushMatrix();
        glScalef(a, a, a); // change la taille
    
        // rouge
        glPushMatrix();
            glTranslatef(0, 0, -0.5);
            glColor3f(1, 0, 0);
            def_carre();
        glPopMatrix();
    
        // bleu
        glPushMatrix();
            glRotatef(-90, 1, 0, 0);
            glTranslatef(0, 0, -0.5);
            glColor3f(0, 0, 1);
            def_carre();
        glPopMatrix();
    
        // vert
        glPushMatrix();
            glRotatef(90, 1, 0, 0);
            glTranslatef(0, 0, -0.5);
            glColor3f(0, 1, 0);
            def_carre();
        glPopMatrix();
    
        // jaune
        glPushMatrix();
            glRotatef(90, 0, 1, 0);
            glTranslatef(0, 0, -0.5);
            glColor3f(1, 1, 0);
            def_carre();
        glPopMatrix();
    
        // cyan
        glPushMatrix();
            glRotatef(-90, 0, 1, 0);
            glTranslatef(0, 0, -0.5);
            glColor3f(0, 1, 1);
            def_carre();
        glPopMatrix();
    glPopMatrix();
    def_axis(a); // dessine les axes
}


/* @brief :applique une rotation sur un axe. les boites tourne seulement
 *         si d a été pressé. On peut activer desactiver la rotation
 *         de chaque boite.
 */
void rotation (){
    if (rotated){ // si ils peuvent tourner
        if (rotated1){ // si boite 1 peut tourner
            glPushMatrix();
                glLoadMatrixf(boite1); // stocke la matrice au sommet de la pile
                glRotated(1, 0, 1, 0);
                glGetFloatv(GL_MODELVIEW_MATRIX, boite1); // recupere la matrice avec la rotation appliquer
            glPopMatrix();
        }
        if (rotated2){
            glPushMatrix();
                glLoadMatrixf(boite2);
                glRotated(-1, 0, 1, 0);
                glGetFloatv(GL_MODELVIEW_MATRIX, boite2);
            glPopMatrix();

        }
        
        usleep(10);
        glutPostRedisplay();
        
    }
}
/* la fonction "affichage" est appelée a chaque fois qu'un événement de mise
 à jour de l'affichage est détecté */
void affichage(void){
  //  def_axes();
    glEnable(GL_DEPTH_TEST);
        
	glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode (GL_MODELVIEW);


    def_axis(2); // axes du plan
    // boite 1
    glPushMatrix();
        glTranslatef(1, -1.5 ,0);
        glMultMatrixf(boite1);
        def_boite(1);
    glPopMatrix();
    // boite 2
    glPushMatrix();
        glTranslatef(1, 1.5 ,0);
        glMultMatrixf(boite2);
        def_boite(1);
    glPopMatrix();
    
    rotation();
    glutSwapBuffers();

}

/* la fonction "redim" est appelée : une fois a la creation de la fenêtre ;
 ensuite à chaque fois que la fenêtre est redimmensionnée
 width et height representent la taille de la fenêtre */
void redim(int width, int height){
    glViewport(0, 0, width, height);
    glLoadIdentity ();
    gluLookAt (2.0, 0, -4,
               0, 0, 0,
               0, 1, 0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(70.0, 1.0, 1.0, 10.0);
}


void clavier (unsigned char key, int x, int y){
    glMatrixMode (GL_MODELVIEW);
    
    switch (key) {
        // rotation sur x
        case 'x':
            glPushMatrix();
                glLoadMatrixf(boite1);
                glRotated(10, 1, 0,0);
                glGetFloatv(GL_MODELVIEW_MATRIX, boite1);
            glPopMatrix();
            glPushMatrix();
                glLoadMatrixf(boite2);
                glRotated(10, 1, 0,0);
                glGetFloatv(GL_MODELVIEW_MATRIX, boite2);
            glPopMatrix();
            
            glutPostRedisplay();
            cout << "x pressed" << endl;
            break;
        // rotation sur z
        case 'z' :
            glPushMatrix();
                glLoadMatrixf(boite1);
                glRotated(10, 0, 0,1);
                glGetFloatv(GL_MODELVIEW_MATRIX, boite1);
            glPopMatrix();
            glPushMatrix();
                glLoadMatrixf(boite2);
                glRotated(10, 0, 0,1);
                glGetFloatv(GL_MODELVIEW_MATRIX, boite2);
            glPopMatrix();
            glutPostRedisplay();
            cout << "Z pressed" << endl;
            break;
        // rotation sur y
        case 'y' :
            glPushMatrix();
                glLoadMatrixf(boite1);
                glRotated(10, 0, 1, 0);
                glGetFloatv(GL_MODELVIEW_MATRIX, boite1);
            glPopMatrix();
            glPushMatrix();
                glLoadMatrixf(boite2);
                glRotated(10, 0, 1, 0);
                glGetFloatv(GL_MODELVIEW_MATRIX, boite2);
            glPopMatrix();
            glutPostRedisplay();
            cout << "y pressed" << endl;
            break;
        // active/desactive la rotation des boites
        case 'd' :
            if (rotated){
                rotated = false;
            } else {
                rotated = true;
            }
            glutPostRedisplay();
            cout << "d pressed"  << rotated << endl;
            break;
        // active/desactive la rotation de la boite 1
        case 'e' :
            if (rotated1){
                rotated1 = false;
            } else {
                rotated1 = true;
            }
            glutPostRedisplay();
            cout << "e pressed"  << endl;
            break;
        // active/desactive la rotation de la boite 2
        case 'r' :
            if (rotated2){
                rotated2 = false;
            } else {
                rotated2 = true;
            }
            glutPostRedisplay();
            cout << "r pressed"  << rotated << endl;
            break;
        // rotation par rapport au plan
        case 'a' :
                glRotated(10, 0, 1, 1);
                glutPostRedisplay();
                cout << "a pressed"  << endl;
        default:
            break;
    }
}


int main (int argc, char * argv[]){
    glutInit(&argc, argv);
    /* Taille et emplacement de la fenêtre */
    glutInitWindowSize(700, 700);
    glutInitWindowPosition(200, 100);
    /* Choix du type et d'affichage RGBA (mode couleur le plus fréquent), tampon de profondeur
     et d'un double buffer */
    glutInitDisplayMode(GLUT_RGBA | GLUT_DEPTH | GLUT_DOUBLE);
    /* Création de la fenêtre */
    glutCreateWindow("GLUTfenetre");
   /* Association des callback pour cette fenêtre */
    glutDisplayFunc(affichage);
    glutReshapeFunc(redim);
    glutKeyboardFunc(clavier);
    glutMainLoop();
    /* On entre dans la boucle d'événements */
    return 0;
}
