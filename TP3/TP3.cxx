#include <GLUT/glut.h>
//#include <GL/glut.h>
#include <iostream>
#include <cmath>
#include <unistd.h>
using namespace std;

bool rotated = false;
bool rotated1 = true;
bool rotated2 = true;
bool activated1 = true;
bool activated2 = true;

void affichage();

GLfloat boite1[16] = {1, 0, 0, 0,
                      0, 1, 0, 0,
                      0, 0, 1, 0,
                      0, 0, 0, 1};
GLfloat boite2[16]= {1, 0, 0, 0,
                     0, 1, 0, 0,
                     0, 0, 1, 0,
                     0, 0, 0, 1};


GLfloat Lambiant [4] = {0.4, 0.4, 0.4, 1.0};
GLfloat Lblanche [4] = {1.0, 1.0, 1.0, 1.0};


/* @brief : défini les faces du carré
 *
 */
void def_carre (void){
    glPolygonMode(GL_FRONT, GL_FILL);
    glPolygonMode(GL_BACK, GL_LINE);
    //glEnable(GL_CULL_FACE);
    //glCullFace(GL_BACK);

    glBegin(GL_POLYGON);
        glNormal3f(0, 0, 1);
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
    //glColor3f(1,0,0);
    GLfloat emiRed[4] = {0.5, 0.0, 0.0, 1.0};
    glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, emiRed);
    glVertex3f(0, 0, 0);
    glVertex3f(a, 0, 0);
    
    // y
    //glColor3f(0,1,0);
    GLfloat emiGreen[4] = {0.0, 0.5, 0.0, 1.0};
    glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, emiGreen);
    glVertex3f(0, 0, 0);
    glVertex3f(0, a, 0);
    
    // z
//    glColor3f(0,0,1);
    GLfloat emiBlue[4] = {0.0, 0.0, 0.5, 1.0};
    glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, emiBlue);
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
            GLfloat emiRed[4] = {0.5, 0.0, 0.0, 1.0};
            glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, emiRed);
            //glColor3f(1, 0, 0);
            def_carre();
        glPopMatrix();
    
        // bleu
        glPushMatrix();
            glRotatef(-90, 1, 0, 0);
            glTranslatef(0, 0, -0.5);
            //glColor3f(0, 0, 1);
            GLfloat emiBlue[4] = {0.0, 0.0, 0.5, 1.0};
            glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, emiBlue);
            def_carre();
        glPopMatrix();
    
        // vert
        glPushMatrix();
            glRotatef(90, 1, 0, 0);
            glTranslatef(0, 0, -0.5);
            //glColor3f(0, 1, 0);
            GLfloat emiGreen[4] = {0.0, 0.5, 0.0, 1.0};
            glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, emiGreen);
            def_carre();
        glPopMatrix();
    
        // jaune
        glPushMatrix();
            glRotatef(90, 0, 1, 0);
            glTranslatef(0, 0, -0.5);
            GLfloat emiYellow[4] = {0.5, 0.5, 0.0, 1.0};
            glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, emiYellow);
            //glColor3f(1, 1, 0);
            def_carre();
        glPopMatrix();
    
        // cyan
        glPushMatrix();
            glRotatef(-90, 0, 1, 0);
            glTranslatef(0, 0, -0.5);
            GLfloat emiCyan[4] = {0.0, 0.5, 0.5, 1.0};
            glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, emiCyan);
           // glColor3f(0, 1, 1);
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

// lumiere qui bouge avec la boite
void lumiereMobile (){
    if (activated2){
        glEnable(GL_LIGHT1);
        GLfloat Lposition1 [4] = {-5.0 , 0.0 , 3.0 , 1.0 };
        glLightfv(GL_LIGHT1, GL_POSITION, Lposition1);
        glLightfv (GL_LIGHT1, GL_AMBIENT, Lambiant);
        glLightfv (GL_LIGHT1, GL_DIFFUSE, Lblanche);
        glLightfv (GL_LIGHT1, GL_SPECULAR, Lblanche);
        
    } else {
        glDisable(GL_LIGHT1);
    }
}

// lumiere qui be bouge pas
void lumiereImmobile (){
    if (activated1){
        glEnable(GL_LIGHT0);
        int lightPos[4] = {0, 0, -5, 1};
        
        glLightfv (GL_LIGHT0, GL_AMBIENT, Lambiant);
        glLightfv (GL_LIGHT0, GL_DIFFUSE, Lblanche);
        glLightfv (GL_LIGHT0, GL_SPECULAR, Lblanche);
        glLightiv(GL_LIGHT0, GL_POSITION, lightPos);
        
    } else {
        glDisable(GL_LIGHT0);
        
    }

}


/* la fonction "affichage" est appelée a chaque fois qu'un événement de mise
 à jour de l'affichage est détecté */
void affichage(void){
    glEnable(GL_LIGHTING);

    lumiereImmobile();
  //  def_axes();
    glEnable(GL_DEPTH_TEST);
        
	glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode (GL_MODELVIEW);


    def_axis(2); // axes du plan
    // boite 1
    glPushMatrix();
        glTranslatef(1, -1.5 ,0);
        glMultMatrixf(boite1);
        lumiereMobile();
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
            break;
        case 'l' :
            if (activated1){
                activated1 = false;
            } else {
                activated1 = true;
            }
            cout << "l pressed"  << endl;
            glutPostRedisplay();
            break;
        case 'm' :
            if (activated2){
                activated2 = false;
            } else {
                activated2 = true;
            }
            cout << "m pressed"  << endl;
            glutPostRedisplay();
            break;
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
