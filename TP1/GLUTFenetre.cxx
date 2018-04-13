#include <GLUT/glut.h>
#include <iostream>

using namespace std;

double cpt = 0;

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
/* la fonction "redim" est appelée : une fois a la creation de la fenêtre ;
 ensuite à chaque fois que la fenêtre est redimmensionnée
 width et height representent la taille de la fenêtre */
void redim(int width, int height){
    glViewport(0, 0, width, height);
}

void clavier (unsigned char key, int x, int y){
    switch (key) {
        case 'q':
            exit(0);
            break;
        case 32 :
            glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

            glutSwapBuffers();
            cout << cpt << endl;
            if (cpt < 1){
                cpt = cpt + 0.2;
            } else {
                cpt = 0;
            }
            glClearColor(cpt, cpt, cpt, 0) ;

        default:
            break;
    }
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
 
    glutKeyboardFunc(clavier);

    glutMainLoop();
    /* On entre dans la boucle d'événements */
    return 0;
}
