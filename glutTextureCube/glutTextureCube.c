/* Lecture d'une image TGA non compressee et de preference 24 bits (sans transparence) */
/* Cette image est affichee par placage de texture sur une face qui tourne */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <GLUT/glut.h>

/* Taille de la fenetre au depart */
#define FENETRE_L	512
#define FENETRE_H	256

/* Un type "image" vraiment tres simple */
/* le champ texID va contenir l'identifiant de texture donne par OpenGL */
typedef struct
{
	GLubyte	*imageData;		// Le format TGA peut coder jusqu'4 octets par pixel
	GLuint	bpp;			// c'est la qu'est justement stocke le nombre de bits utilises
	GLuint	width;			// la largeur
	GLuint	height;			// la hauteur
	GLuint	texID;			// l'identifiant de texture
} TextureImage;


/* C'est dans cette variable que va etre stocke la texture */
TextureImage 	texture;

/* Pour faire bouger la texture sur la face */	
float uCoord = 0;

/* Prototype de la fonction, elle est ecrite a la fin du fichier*/
int chargeTextureTGA(TextureImage *texture, char *filename);

void initGL(void)
{
	chargeTextureTGA(&texture, "SebMae.tga");	// Lecture de l'image et attribution d'un emplacement pour la texture
												// rq : on doit charger la texture APRES la creation du contexte GL
	glEnable(GL_TEXTURE_2D);					// La texture
	glEnable(GL_DEPTH_TEST);					// Le Z-Buffer
	
	/* on recule le cube ici, c'est plus facile de garder les rotations lors d'un redim ... 
	   a reflechir un peu ... */
	glMatrixMode(GL_MODELVIEW);			
    glLoadIdentity();
	glTranslatef(0.0f,0.0f,-5.0f);
}

/* On anime le cube ... car on associe "tourne" a un timer */
void tourne(int v)
{
	glRotatef(.3,1.0f,0.0f,0.0f);				
	glRotatef(.2,0.0f,1.0f,0.0f);				

	// Pour faire "bouger" la texture sur la face */
	uCoord == 1 ? uCoord = 0 : uCoord += 0.01;

	glutPostRedisplay(); /* On demande l'affichage */
	glutTimerFunc(40., tourne, 0);
}

/* Rien de particulier a dire, on a deja explique cette fonction plusieurs fois */
void redim(int l, int h)
{
    glViewport (0, 0, l, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0, (GLfloat) l /  h, 1., 7.);
	glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
	gluLookAt(0, 0, -2, 0, 0, 0, 0, 1, 0);	
}

/* La fonction d'affichage, ce qui nous interesse c'est le glBindTexture et les glTexCoord2f */
void affiche(void)
{  	  
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	glBindTexture(GL_TEXTURE_2D, texture.texID);
	
	glBegin(GL_QUADS);
		/* Texture fixe */
		// glTexCoord2f(0.0f, 0.0f); glVertex3f(-.5f, -.5f,  .5f);	// bas gauche 
		// glTexCoord2f(1.0f, 0.0f); glVertex3f( .5f, -.5f,  .5f);	// bas droit
		// glTexCoord2f(1.0f, 1.0f); glVertex3f( .5f,  .5f,  .5f);	// haut droit 
		// glTexCoord2f(0.0f, 1.0f); glVertex3f(-.5f,  .5f,  .5f);	// haut gauche

		/* On change les coordonnées de texture à chaque affiche, la texture "bouge" */	
		glTexCoord2f(uCoord, 0.0f); glVertex3f(-.5f, -.5f,  .5f);	// bas gauche 
		glTexCoord2f(uCoord + 1.0f, 0.0f); glVertex3f( .5f, -.5f,  .5f);	// bas droit
		glTexCoord2f(uCoord + 1.0f, 1.0f); glVertex3f( .5f,  .5f,  .5f);	// haut droit 
		glTexCoord2f(uCoord, 1.0f); glVertex3f(-.5f,  .5f,  .5f);	// haut gauche
	glEnd();

    glutSwapBuffers();
}

/* Que du classique pour vous maintenant ! */
int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(FENETRE_L, FENETRE_H); 
    glutInitWindowPosition (150, 150);
    glutCreateWindow ("texture");
	
	initGL();
		
    glutDisplayFunc(affiche); 
    glutReshapeFunc(redim);
	
	glutTimerFunc(4., tourne, 0);
	
	glutMainLoop();
    return 0;
}

/* Fonction pour un fichier image au format TGA recuperee sur internet */
/* La partie interessante est celle sur la texture a la fin ...*/
int chargeTextureTGA(TextureImage *texture, char *filename)			// Loads A TGA File Into Memory
{    
	GLubyte		TGAheader[12]={0,0,2,0,0,0,0,0,0,0,0,0};	// Uncompressed TGA Header
	GLubyte		TGAcompare[12];								// Used To Compare TGA Header
	GLubyte		header[6];									// First 6 Useful Bytes From The Header
	GLuint		bytesPerPixel;								// Holds Number Of Bytes Per Pixel Used In The TGA File
	GLuint		imageSize;									// Used To Store The Image Size When Setting Aside Ram
	GLuint		temp;										// Temporary Variable
	GLuint		type=GL_RGBA;								// Set The Default GL Mode To RBGA (32 BPP)
	GLuint		i;
	
	FILE *file = fopen(filename, "rb");						// Open The TGA File

	if(	file==NULL ||										// Does File Even Exist?
		fread(TGAcompare,1,sizeof(TGAcompare),file)!=sizeof(TGAcompare) ||	// Are There 12 Bytes To Read?
		memcmp(TGAheader,TGAcompare,sizeof(TGAheader))!=0				||	// Does The Header Match What We Want?
		fread(header,1,sizeof(header),file)!=sizeof(header))				// If So Read Next 6 Header Bytes
	{
		fclose(file);										// If Anything Failed, Close The File
		return -1;											// Return False
	}

	texture->width  = header[1] * 256 + header[0];			// Determine The TGA Width	(highbyte*256+lowbyte)
	texture->height = header[3] * 256 + header[2];			// Determine The TGA Height	(highbyte*256+lowbyte)
    
 	if(	texture->width	<=0	||								// Is The Width Less Than Or Equal To Zero
		texture->height	<=0	||								// Is The Height Less Than Or Equal To Zero
		(header[4]!=24 && header[4]!=32))					// Is The TGA 24 or 32 Bit?
	{
		fclose(file);										// If Anything Failed, Close The File
		return -1;											// Return False
	}

	texture->bpp	= header[4];							// Grab The TGA's Bits Per Pixel (24 or 32)
	bytesPerPixel	= texture->bpp/8;						// Divide By 8 To Get The Bytes Per Pixel
	imageSize		= texture->width*texture->height*bytesPerPixel;	// Calculate The Memory Required For The TGA Data

	texture->imageData=(GLubyte *)malloc(imageSize);		// Reserve Memory To Hold The TGA Data

	if(	texture->imageData==NULL ||							// Does The Storage Memory Exist?
		fread(texture->imageData, 1, imageSize, file)!=imageSize)	// Does The Image Size Match The Memory Reserved?
	{
		if(texture->imageData!=NULL)						// Was Image Data Loaded
			free(texture->imageData);						// If So, Release The Image Data

		fclose(file);										// Close The File
		return -1;											// Return False
	}

	for(i=0; i<imageSize; i+=bytesPerPixel)					// Loop Through The Image Data
	{														// Swaps The 1st And 3rd Bytes ('R'ed and 'B'lue)
		temp=texture->imageData[i];							// Temporarily Store The Value At Image Data 'i'
		texture->imageData[i] = texture->imageData[i + 2];	// Set The 1st Byte To The Value Of The 3rd Byte
		texture->imageData[i + 2] = temp;					// Set The 3rd Byte To The Value In 'temp' (1st Byte Value)
	}

	fclose (file);											// Close The File

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