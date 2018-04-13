#include <GLUT/glut.h>
#include <stdio.h>
#include <stdlib.h>


/* la fonction "affichage" est appelée a chaque fois qu'un événement de mise
 à jour de l'affichage est détecté */
void affichage(void){
    glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    // initialisation OpenGL : couleur de fond
    /* Oups
     ! une instruction OpenGL : on efface le buffer d'écran */
    glutSwapBuffers();
    /* Oups
     ! encore une : on indique ici qu'il faut afficher */
}
void affichage2(void){
    glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    // initialisation OpenGL : couleur de fond
    /* Oups
     ! une instruction OpenGL : on efface le buffer d'écran */
    glutSwapBuffers();
    /* Oups
     ! encore une : on indique ici qu'il faut afficher */
}
/* la fonction "redim" est appelée : une fois a la creation de la fenêtre ;
 ensuite à chaque fois que la fenêtre est redimmensionnée
 width et height representent la taille de la fenêtre */
void redim(int width, int height){
    glViewport(0, 0, width, height);
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
    glClearColor(255, 0, 0, 0);
    
    
    glutCreateWindow("GLUTfenetre");
    /* Association des callback pour cette fenêtre */
    glutDisplayFunc(affichage2);
    glutReshapeFunc(redim);
    glClearColor(255, 255, 0, 0);
    
    glutMainLoop();

    /* On entre dans la boucle d'événements */
    return 0;
}

