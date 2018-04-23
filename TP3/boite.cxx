/* *
 * @author  Alexandre MOUTOUH
 *
 * TP2 SV
 * Pour compiler : g++ -w boite.cxx -framework glut -framework opengl
 * */


#include <iostream>
#include <unistd.h>

#ifdef __linux__
#include <GL/glut.h>
#include <GL/gl.h>
#elif __APPLE__
#include <GLUT/glut.h>
#include <OpenGL/gl.h>
#endif

/* Dimensions de la fenetre */
int l = 400;
int h = 400;

/* Rotations */
bool rotSynchro = false;
bool rot1 = false;
bool rot2 = false;
bool rot = false;
int timer = 0;

/* Matrices de transformations */
GLfloat matCube1[16] = {
    1, 0, 0, 0,
    0, 1, 0, 0,
    0, 0, 1, 0,
    0, 0, 0, 1
};

GLfloat matCube2[16] = {
    1, 0, 0, 0,
    0, 1, 0, 0,
    0, 0, 1, 0,
    0, 0, 0, 1
};

GLfloat matLight1[16] = {
    1, 0, 0, 0,
    0, 1, 0, 0,
    0, 0, 1, 0,
    0, 0, 0, 1
};

GLfloat matLight2[16] = {
    1, 0, 0, 0,
    0, 1, 0, 0,
    0, 0, 1, 0,
    0, 0, 0, 1
};

/* Lumiere */
int lightPos[4] = {20, -3, -5, 1};

/* * * * *
 * Boite *
 * * * * */

void def_carre(void) {
    glPolygonMode(GL_FRONT, GL_FILL);
    //glCullFace(GL_FRONT);
    glPolygonMode(GL_BACK, GL_LINE);
    //glCullFace(GL_BACK);

    glBegin(GL_POLYGON);
        glNormal3f(0, 0, 1);
        glVertex3f(1, 1, 0);
        glVertex3f(1, -1, 0);
        glVertex3f(-1, -1, 0);
        glVertex3f(-1, 1, 0);
    glEnd();
}

void def_boite(int a) {
    glPushMatrix();
    glScalef(a, a, a);

    // rouge
    glPushMatrix();
    glTranslatef(0, 0, -1);
    //glColor3f(1, 0, 0);
    GLfloat emiRed[4] = {0.5, 0.0, 0.0, 1.0};
    glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, emiRed);
    def_carre();
    glPopMatrix();

    // bleu
    glPushMatrix();
    glRotatef(-90, 1, 0, 0);
    glTranslatef(0, 0, -1);
    //glColor3f(0, 0, 1);
    GLfloat emiBlue[4] = {0.0, 0.0, 5.0, 1.0};
    glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, emiBlue);
    def_carre();
    glPopMatrix();

    // vert
    glPushMatrix();
    glRotatef(90, 1, 0, 0);
    glTranslatef(0, 0, -1);
    //glColor3f(0, 1, 0);
    GLfloat emiGreen[4] = {0.0, 0.5, 0.0, 1.0};
    glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, emiGreen);
    def_carre();
    glPopMatrix();

    // jaune
    glPushMatrix();
    glRotatef(90, 0, 1, 0);
    glTranslatef(0, 0, -1);
    //glColor3f(1, 1, 0);
    GLfloat emiYel[4] = {0.5, 0.5, 0.0, 1.0};
    glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, emiYel);
    def_carre();
    glPopMatrix();

    // cyan
    glPushMatrix();
    glRotatef(-90, 0, 1, 0);
    glTranslatef(0, 0, -1);
    //glColor3f(0, 1, 1);
    GLfloat emiCy[4] = {0.0, 0.5, 0.5, 1.0};
    glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, emiCy);
    def_carre();
    glPopMatrix();

    glPopMatrix();
}

void def_axis(int a) {
    a = a * 2;
    glColor3f(1, 1, 1);

    glBegin(GL_LINES);
        glVertex3f(0, 0, 0);
        glVertex3f(a, 0, 0);
        glVertex3f(0, 0, 0);
        glVertex3f(0, a, 0);
        glVertex3f(0, 0, 0);
        glVertex3f(0, 0, a);
    glEnd();
}

/**
 * applique les rotations aux bonnes matrices.
 */
void rotationner_independant() {
    // rotation de la scene
    if(rot) {
        glRotatef(1, 0, 0, 1);
    }

    // rotation du cube 1
    if(rot1) {
        glPushMatrix();
        glLoadMatrixf(matCube1);
        glRotatef(1, 0, 1, 0);
        glGetFloatv(GL_MODELVIEW_MATRIX, matCube1);
        glPopMatrix();
    }

    // rotation du cube 2
    if(rot2) {
        glPushMatrix();
        glLoadMatrixf(matCube2);
        glRotatef(1, 1, 0, 0);
        glGetFloatv(GL_MODELVIEW_MATRIX, matCube2);
        glPopMatrix();
    }

    // rotation des 2 cubes en meme temps
    if(rotSynchro) {
        glPushMatrix();
        glLoadMatrixf(matCube1);
        glRotatef(1, 0, 1, 0);
        glGetFloatv(GL_MODELVIEW_MATRIX, matCube1);
        glPopMatrix();

        glPushMatrix();
        glLoadMatrixf(matCube2);
        glRotatef(1, 1, 0, 0);
        glGetFloatv(GL_MODELVIEW_MATRIX, matCube2);
        glPopMatrix();
    }

    glutPostRedisplay();
}

/* * * * *
 * Menu  *
 * * * * */

/**
 * fonction de gestion du menuPrincipal
 * value contient l'identificateur associe à l'article du menu selectionne
 */
void ChoixMenuPrincipal(int value) {
    switch(value) {
        case 10 :
            exit(0); /* on quitte */
            break;
     }
}

void CreerMenu(void) {
    /* creation d'un menu dont la fonction de "gestion" est ChoixMenuPrincipal */
    glutCreateMenu(ChoixMenuPrincipal);
    glutAddMenuEntry("Quitter", 10);
    /* on associe l'apparition de ce menu au bouton droit de la souris */
    glutAttachMenu(GLUT_RIGHT_BUTTON);
}

/* * * * * * * * *
 * Interactions  *
 * * * * * * * * */

/**
 * la fonction "clavier" est appelee quand un evenement clavier est detecte
 * key est le code ASCII de la touche enfoncé
 * x et y sont les coordonnees de la souris au moment de l'appui de la touche
 */
void clavier(unsigned char key, int x, int y) {
    switch(key) {
        case 'e' :
            exit(0);
            break;

        // rotations manuelles sur la scene (axes x, y ou z)
        case 'x' :
            glRotatef(10, 1, 0, 0);
            glutPostRedisplay();
            break;
        case 'y' :
            glRotatef(10, 0, 1, 0);
            glutPostRedisplay();
            break;
        case 'z' :
            glRotatef(10, 0, 0, 1);
            glutPostRedisplay();
            break;

        // rotations automatiques
        case 'r' : 
            rot = !rot;
            glutPostRedisplay();
            break;
        case 'u' :
            rot1 = !rot1;
            glutPostRedisplay();
            break;
        case 'i' :
            rot2 = !rot2;
            glutPostRedisplay();
            break;
        case 'd' :
            rotSynchro = !rotSynchro;
            glutPostRedisplay();
            break;
    }
}

/* * * * * * *
 * Affichage *
 * * * * * * */

/**
 * La fonction "affichage" est appelée a chaque fois qu'un
 * événement de mise à jour de l'affichage est détecté
 */
void affichage(void) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);

    glLightiv(GL_LIGHT0, GL_POSITION, lightPos);

    def_axis(1);

    // translation des cubes dans la scene
    glPushMatrix();
        glTranslatef(-3, 0, 0);
        glMultMatrixf(matCube1);
        def_boite(2);
        def_axis(1);
    glPopMatrix();

    glPushMatrix();
        glTranslatef(5, 0, 0);
        glMultMatrixf(matCube2);
        def_boite(1);
        def_axis(1);
    glPopMatrix();

    // rotation des cubes selon les touches pressees
    rotationner_independant();

    glutSwapBuffers();
}

/**
 * la fonction "redim" est appelée : une fois a la creation de
 * la fenêtre. Ensuite à chaque fois que fenêtre est redimmensionnée.
 */
void redim(int width, int height) {
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(90, 1, 1, 100);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(3.0, 2.0, 10.0,
              0.0, 0.0, 0.0,
              0.0, 1.0, 0.0);

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
    glutCreateWindow("BOITES LUMIERE");
    CreerMenu();
    glutDisplayFunc(affichage);
    glutReshapeFunc(redim);

    /* la fonction "clavier" est appelee quand un evenement clavier est detecte */
    glutKeyboardFunc(clavier);
    
    glutMainLoop();
}
