#include <GLUT/glut.h>
#include <iostream>

using namespace std;

double cpt = 0;

/* la fonction "affichage" est appelée a chaque fois qu'un événement de mise
 à jour de l'affichage est détecté */
void affichage(void){
    glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    //une instruction OpenGL : on efface le buffer d'écran */
    glutSwapBuffers();
}

/* la fonction "redim" est appelée : une fois a la creation de la fenêtre ;
 ensuite à chaque fois que la fenêtre est redimmensionnée
 width et height representent la taille de la fenêtre */
void redim(int width, int height){
    glViewport(0, 0, width, height);
}


/* Fonction de gestion d'événement clavier, lorsque
 * on appui sur q, on quitte le programme, 
 * lorsque on appuy sur espace on change 
 * la couleur de fond de la fenêtre 
 */ 
void clavier (unsigned char key, int x, int y){
    switch (key) {
        case 'q':
            exit(0);
            break;
        case 32 : // espace
						//réinitialise l'affichage
            glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

            glutSwapBuffers();
            cout << cpt << endl;
						// compteur qui varie entre 0 et 1
            if (cpt < 1){
                cpt = cpt + 0.2;
            } else {
                cpt = 0;
            }
						// change la couleur
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
