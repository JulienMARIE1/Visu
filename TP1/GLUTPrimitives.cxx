#include <GLUT/glut.h>
#include <iostream>

using namespace std;


/* fonction de gestion du menuPrincipal
 value contient l'identificateur associe à l'article du menu selectionne*/
void ChoixMenuPrincipal(int value) {
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // Set background color to black and opaque
    glClear(GL_COLOR_BUFFER_BIT);         // Clear the color buffer (background)
    switch (value) {
        case 1:
            glBegin(GL_POLYGON);              // Each set of 4 vertices form a quad
            glColor3f(1.0f, 0.0f, 0.0f); // Red
            glVertex2f(0.0f, 0.0f);    // x, y
            glVertex2f( 0.0f, 3.0f/10);
            glVertex2f( 4.0f/10,  3.0f/10);
            glVertex2f(6.0f/10,  1.5f/10);
            glVertex2f(2.0f/10,  0.0f);
            glEnd();
            
            glFlush();  // Render now
            break;
        case 2:

            
            
            // Draw a Red 1x1 Square centered at origin
            glBegin(GL_POLYGON);              // Each set of 4 vertices form a quad
            glColor3f(1.0f, 0.0f, 0.0f); // Red
            glVertex2f(0.0f, 0.0f);    // x, y
            glVertex2f( 0.0f, 3.0f/10);
            glVertex2f( 2.0f/10,  3.0f/10);
            glVertex2f(6.0f/10,  1.5f/10);
            glVertex2f(2.0f/10,  0.0f);
            glEnd();
            
            glFlush();  // Render now
            break;

        case 4:
            exit(0);
            break;
    }
}
/* Handler for window-repaint event. Call back when the window first appears and
 whenever the window needs to be re-painted. */
void display() {
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // Set background color to black and opaque
    glClear(GL_COLOR_BUFFER_BIT);         // Clear the color buffer (background)
    
    // Draw a Red 1x1 Square centered at origin
    glBegin(GL_POLYGON);              // Each set of 4 vertices form a quad
    glColor3f(1.0f, 0.0f, 0.0f); // Red
    glVertex2f(0.0f, 0.0f);    // x, y
    glVertex2f( 0.0f, 3.0f/10);
    glVertex2f( 4.0f/10,  3.0f/10);
    glVertex2f(6.0f/10,  1.5f/10);
    glVertex2f(4.0f/10,  0.0f);
    glEnd();
    
    glFlush();  // Render now
}

void CreerMenu(void) {
    int sousMenu;
    /* creation d'un menu dont la fonction de "gestion" est ChoixSousMenu l'identicateur de ce
     menu est stocké dans l'entier sousMenu afin de pouvoir lier ce menu au menu principal */
    /* creation d'un menu dont la fonction de "gestion" est ChoixMenuPrincipal */
    glutCreateMenu(ChoixMenuPrincipal);
    /* ajout d'une entree dans ce menu, les arguments sont : nom apparaissant dans le menu et
     identificateur le representant dans la fonction de gestion */
    glutAddMenuEntry("Choix 1", 1);
    glutAddMenuEntry("Choix 2", 2);

    /* ajout d'un sous menu a ce menu, les arguments sont : nom apparaissant dans le menu
     et identificateur de ce sous menu
     ATTENTION : le sous menu doit etre cree avant */
    glutAddMenuEntry("Quitter", 4);
    /* on associe l'apparition de ce menu au bouton droit de la souris */
    glutAttachMenu(GLUT_RIGHT_BUTTON);
}

void souris (int button, int state, int x, int y){
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // Set background color to black and opaque
    glClear(GL_COLOR_BUFFER_BIT);         // Clear the color buffer (background)
    float normalizedX = x/400.0 - 1 ;
    float normalizedY = -y/400.0 + 1;
    float pixel       = 3.0f/400.f;
    switch (button) {
        case GLUT_LEFT_BUTTON:
            glColor3f(0.0, 1.0, 0.0);
            glBegin(GL_QUADS);
            glVertex2f(normalizedX, normalizedY); // top left
            glVertex2f(normalizedX, normalizedY + pixel); // top right
            glVertex2f(normalizedX + pixel, normalizedY + pixel); // bottom right
            glVertex2f(normalizedX + pixel, normalizedY); // bottom left
            glEnd();
            cout << "button clicked " << x << endl;
            glFlush();  // Render now

            break;
            
        default:
            break;
    }
}

/* Main function: GLUT runs as a console application starting at main()  */
int main(int argc, char** argv) {
    glutInit(&argc, argv);                 // Initialize GLUT
    glutInitWindowSize(800, 800);   // Set the window's initial width & height
    glutInitWindowPosition(0, 0); // Position the window's initial top-left corner
    glutCreateWindow("OpenGL Setup Test"); // Create a window with the given title

    glutDisplayFunc(display); // Register display callback handler for window re-paint
    glutMouseFunc(souris);
    CreerMenu();
    glutMainLoop();           // Enter the event-processing loop
    return 0;
}
