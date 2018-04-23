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
/* Un type "image" vraiment tres simple */
/* le champ texID va contenir l'identifiant de texture donne par OpenGL */
typedef struct
{
    GLubyte    *imageData;        // Le format TGA peut coder jusqu'4 octets par pixel
    GLuint    bpp;            // c'est la qu'est justement stocke le nombre de bits utilises
    GLuint    width;            // la largeur
    GLuint    height;            // la hauteur
    GLuint    texID;            // l'identifiant de texture
} TextureImage;


/* C'est dans cette variable que va etre stocke la texture */
TextureImage     texture;

/* Pour faire bouger la texture sur la face */
float uCoord = 0;

/* Prototype de la fonction, elle est ecrite a la fin du fichier*/
int chargeTextureTGA(TextureImage *texture, char *filename);
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
        glTexCoord2f(uCoord, 0.0f);
        glVertex3f(0.5, 0.5, 0);
        glTexCoord2f(uCoord + 1.0f, 0.0f);
        glVertex3f(0.5, -0.5, 0);
        glTexCoord2f(uCoord + 1.0f, 1.0f);
        glVertex3f(-0.5, -0.5, 0);
        glTexCoord2f(uCoord, 1.0f);
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
            // Pour faire "bouger" la texture sur la face */
            uCoord == 1 ? uCoord = 0 : uCoord += 0.01;
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
    chargeTextureTGA(&texture, "img.tga");    // Lecture de l'image et attribution d'un emplacement pour la texture
    // rq : on doit charger la texture APRES la creation du contexte GL
    glEnable(GL_TEXTURE_2D);                    // La texture

    glEnable(GL_LIGHTING);
    glBindTexture(GL_TEXTURE_2D, texture.texID);
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


/* Fonction pour un fichier image au format TGA recuperee sur internet */
/* La partie interessante est celle sur la texture a la fin ...*/
int chargeTextureTGA(TextureImage *texture, char *filename)            // Loads A TGA File Into Memory
{
    GLubyte        TGAheader[12]={0,0,2,0,0,0,0,0,0,0,0,0};    // Uncompressed TGA Header
    GLubyte        TGAcompare[12];                                // Used To Compare TGA Header
    GLubyte        header[6];                                    // First 6 Useful Bytes From The Header
    GLuint        bytesPerPixel;                                // Holds Number Of Bytes Per Pixel Used In The TGA File
    GLuint        imageSize;                                    // Used To Store The Image Size When Setting Aside Ram
    GLuint        temp;                                        // Temporary Variable
    GLuint        type=GL_RGBA;                                // Set The Default GL Mode To RBGA (32 BPP)
    GLuint        i;
    
    FILE *file = fopen(filename, "rb");                        // Open The TGA File
    
    if(    file==NULL ||                                        // Does File Even Exist?
       fread(TGAcompare,1,sizeof(TGAcompare),file)!=sizeof(TGAcompare) ||    // Are There 12 Bytes To Read?
       memcmp(TGAheader,TGAcompare,sizeof(TGAheader))!=0                ||    // Does The Header Match What We Want?
       fread(header,1,sizeof(header),file)!=sizeof(header))                // If So Read Next 6 Header Bytes
    {
        fclose(file);                                        // If Anything Failed, Close The File
        return -1;                                            // Return False
    }
    
    texture->width  = header[1] * 256 + header[0];            // Determine The TGA Width    (highbyte*256+lowbyte)
    texture->height = header[3] * 256 + header[2];            // Determine The TGA Height    (highbyte*256+lowbyte)
    
    if(    texture->width    <=0    ||                                // Is The Width Less Than Or Equal To Zero
       texture->height    <=0    ||                                // Is The Height Less Than Or Equal To Zero
       (header[4]!=24 && header[4]!=32))                    // Is The TGA 24 or 32 Bit?
    {
        fclose(file);                                        // If Anything Failed, Close The File
        return -1;                                            // Return False
    }
    
    texture->bpp    = header[4];                            // Grab The TGA's Bits Per Pixel (24 or 32)
    bytesPerPixel    = texture->bpp/8;                        // Divide By 8 To Get The Bytes Per Pixel
    imageSize        = texture->width*texture->height*bytesPerPixel;    // Calculate The Memory Required For The TGA Data
    
    texture->imageData=(GLubyte *)malloc(imageSize);        // Reserve Memory To Hold The TGA Data
    
    if(    texture->imageData==NULL ||                            // Does The Storage Memory Exist?
       fread(texture->imageData, 1, imageSize, file)!=imageSize)    // Does The Image Size Match The Memory Reserved?
    {
        if(texture->imageData!=NULL)                        // Was Image Data Loaded
            free(texture->imageData);                        // If So, Release The Image Data
        
        fclose(file);                                        // Close The File
        return -1;                                            // Return False
    }
    
    for(i=0; i<imageSize; i+=bytesPerPixel)                    // Loop Through The Image Data
    {                                                        // Swaps The 1st And 3rd Bytes ('R'ed and 'B'lue)
        temp=texture->imageData[i];                            // Temporarily Store The Value At Image Data 'i'
        texture->imageData[i] = texture->imageData[i + 2];    // Set The 1st Byte To The Value Of The 3rd Byte
        texture->imageData[i + 2] = temp;                    // Set The 3rd Byte To The Value In 'temp' (1st Byte Value)
    }
    
    fclose (file);                                            // Close The File
    
    /**********************************/
    /******* TEXTURE C'EST LA *********/
    /**********************************/
    
    /* Demande un identifiant de texture a OpenGL, on le garde en memoire, on en a besoin pour afficher */
    glGenTextures(1, &texture->texID);
    
    /* Rend la texture "courante, active ..." */
    glBindTexture(GL_TEXTURE_2D, texture->texID);
    
    /* Filtrage lineaire : classique peu couteux ... */
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    
    /* On regarde si l'image est bien en RGB */
    /* pour l'instant on ne gere pas la transparence */
    if (texture->bpp==24) type=GL_RGB;
    
    /* on "charge" l'image comme texture */
    glTexImage2D(GL_TEXTURE_2D, 0, type, texture->width, texture->height, 0, type, GL_UNSIGNED_BYTE, texture->imageData);
    
    return 0;
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
