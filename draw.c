#include "screencasts.h"

/*
 * drawAxes()
 * ------
 * Draw the axes
 */
void drawAxes(void)
{
  if (toggleAxes) {
    /*  Length of axes */
    double len = 2.0;
    glDisable(GL_LIGHTING);
    glColor3fv(white);
    glBegin(GL_LINES);
    glVertex3d(0,0,0);
    glVertex3d(len,0,0);
    glVertex3d(0,0,0);
    glVertex3d(0,len,0);
    glVertex3d(0,0,0);
    glVertex3d(0,0,len);
    glEnd();
    /*  Label axes */
    glRasterPos3d(len,0,0);
    print("X");
    glRasterPos3d(0,len,0);
    print("Y");
    glRasterPos3d(0,0,len);
    print("Z");
    if (toggleLight)
      glEnable(GL_LIGHTING);
  }
}

/*
 *  drawLight 
 *  ------
 *  Draws the light
 */
void drawLight(void)
{
  /*  Light switch */
  if (toggleLight) {
    /*  Translate intensity to color vectors */
    GLfloat Ambient[]   = {0.01*ambient ,0.01*ambient ,0.01*ambient ,1.0};
    GLfloat Diffuse[]   = {0.01*diffuse ,0.01*diffuse ,0.01*diffuse ,1.0};
    GLfloat Specular[]  = {0.01*specular,0.01*specular,0.01*specular,1.0};
    GLfloat Position[]  = {distance*Sin(lightPh),lightY,distance*Cos(lightPh),1.0};

    /*  Draw light position as sphere (still no lighting here) */
    glColor3fv(white);
    glDisable(GL_LIGHTING);
    sphere(Position[0],Position[1],Position[2], 0.1,0);

    /*  Set ambient, diffuse, specular components and position of light 0 */
    /*
      Light uses the Phong model
      Once light is enabled, colors assigned by glColor* isn't used
      Ambient is light that's been scattered by environment that its direction is impossible to determine
      Diffuse is is light that comes from one direction, so it's brighter if it comes squarely on surface rather than glances off
      Specular is light that comes from a particular direction and bounces off in preferred direction
      Position is the position of our light. In this case it is the same as the sphere.
     */
    glLightfv(GL_LIGHT0,GL_AMBIENT, Ambient);
    glLightfv(GL_LIGHT0,GL_DIFFUSE, Diffuse);
    glLightfv(GL_LIGHT0,GL_POSITION,Position);

    /*
      In general, I don't like splitting code like this, but this is just for
      these screencasts, and in general I use ColorMaterial
     */
    if (screencastID != 13) {
      glLightfv(GL_LIGHT0,GL_SPECULAR,Specular);
      /*  Use glColorMaterial when you need to change a single material parameter for most vertices
	  in your scene */
      /*  glColorMaterial sets ambient and diffuse color materials */
      glEnable(GL_COLOR_MATERIAL);
      glColorMaterial(GL_FRONT_AND_BACK,GL_AMBIENT_AND_DIFFUSE);
      /*  Now glColor* changes ambient and diffuse reflection */
      /*  Other examples */
    }
    glEnable(GL_NORMALIZE);
    glEnable(GL_LIGHTING); 
    glEnable(GL_LIGHT0);
  }
  else
    glDisable(GL_LIGHTING);
}

/*
 *  drawParameters()
 *  ------
 *  Draw the parameters in the lower left corner
 */
void drawParameters(void)
{
  if (toggleParms) {
    glColor3fv(white);
    /*  Display parameters */
    printAt(5,5,"Angle=%d,%d  Dim=%.1f FOV=%d Light=%s",
	    th,ph,dim,fov,toggleLight?"On":"Off");
    if (toggleLight) {
      printAt(5,45,"Distance=%d Elevation=%.1f Ambient=%d",distance,lightY,ambient);
      printAt(5,25,"Diffuse=%d Specular=%d Emission=%d Shininess=%.0f",
	      diffuse,specular,emission,shinyvec[0]);
    }
  }
}

void drawScene(void)
{
  drawAxes();
  drawParameters();

  if (screencastID == 11) 
    drawScreencast11();
  else if (screencastID == 12)
    drawScreencast12();
  else if (screencastID == 13)
    drawScreencast13();
  else if (screencastID == 14)
    drawScreencast14();
  else if (screencastID == 15)
    drawScreencast15();
}

void drawScreencast11(void)
{
  /*
  cube(1,0,1, 1,1,1, 0);
  cube(-1,0,1, 1,1,1, 0);
  cone(0,1,0, 1,1,DEF_D);
  cone(0,-1,0, 1,1,90);
  */

  /* a 'tower' */
  /*
  cube(0,1.5,0, 1,3,1, 0);
  cube(0,3.5,0, 2,1,2, 45);
  spike(0,1,-3.5, 0.5,1, 90, 90,0,0);
  spike(0,1,3.5, 0.5,1, 90, -90,0,0);
  spike(-3.5,1,0, 0.5,1, 90, 0,0,-90);
  spike(3.5,1,0, 0.5,1, 90, 0,0,90);
  */
  tower(0,0,0, 1,1,1, 0);
  tower(4,0,0, 1,1,1.5, 30);
}

void drawScreencast12(void)
{
  // anything with lighting should be drawn after the light
  drawLight();
  cube(0,0,0, 1,1,1, 0);
}

void drawScreencast13(void)
{
  GLfloat no_mat[] = { 0.0, 0.0, 0.0, 1.0 };
  GLfloat mat_ambient[] = { 0.7, 0.7, 0.7, 1.0 };
  GLfloat mat_ambient_color[] = { 0.8, 0.8, 0.2, 1.0 };
  GLfloat mat_diffuse[] = { 0.1, 0.5, 0.8, 1.0 };
  GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
  GLfloat no_shininess[] = { 0.0 };
  GLfloat low_shininess[] = { 5.0 };
  GLfloat high_shininess[] = { 100.0 };
  GLfloat mat_emission[] = {0.3, 0.2, 0.2, 0.0};

  drawLight();

/*  
    Draw twelve spheres in 3 rows with 4 columns.  
    The spheres in the first row have materials with no ambient reflection.
    The second row has materials with significant ambient reflection.
    The third row has materials with colored ambient reflection.
  
    The first column has materials with blue, diffuse reflection only.
    The second column has blue diffuse reflection, as well as specular
    reflection with a low shininess exponent.
    The third column has blue diffuse reflection, as well as specular
    reflection with a high shininess exponent (a more concentrated highlight).
    The fourth column has materials which also include an emissive component.
 */

  /* 
   Top row
  */ 
  glPushMatrix();
  glTranslatef (-3.75, 3.0, 0.0);
  glMaterialfv(GL_FRONT, GL_AMBIENT, no_mat);
  glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
  glMaterialfv(GL_FRONT, GL_SPECULAR, no_mat);
  glMaterialfv(GL_FRONT, GL_SHININESS, no_shininess);
  glMaterialfv(GL_FRONT, GL_EMISSION, no_mat);
  glutSolidSphere(1.0, 16, 16);
  glPopMatrix();

  glPushMatrix();
  glTranslatef (-1.25, 3.0, 0.0);
  glMaterialfv(GL_FRONT, GL_AMBIENT, no_mat);
  glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
  glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
  glMaterialfv(GL_FRONT, GL_SHININESS, low_shininess);
  glMaterialfv(GL_FRONT, GL_EMISSION, no_mat);
  glutSolidSphere(1.0, 16, 16);
  glPopMatrix();

  glPushMatrix();
  glTranslatef (1.25, 3.0, 0.0);
  glMaterialfv(GL_FRONT, GL_AMBIENT, no_mat);
  glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
  glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
  glMaterialfv(GL_FRONT, GL_SHININESS, high_shininess);
  glMaterialfv(GL_FRONT, GL_EMISSION, no_mat);
  glutSolidSphere(1.0, 16, 16);
  glPopMatrix();

  glPushMatrix();
  glTranslatef (3.75, 3.0, 0.0);
  glMaterialfv(GL_FRONT, GL_AMBIENT, no_mat);
  glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
  glMaterialfv(GL_FRONT, GL_SPECULAR, no_mat);
  glMaterialfv(GL_FRONT, GL_SHININESS, no_shininess);
  glMaterialfv(GL_FRONT, GL_EMISSION, mat_emission);
  glutSolidSphere(1.0, 16, 16);
  glPopMatrix();

  /*
    Middle row
  */
  glPushMatrix();
  glTranslatef (-3.75, 0.0, 0.0);
  glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
  glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
  glMaterialfv(GL_FRONT, GL_SPECULAR, no_mat);
  glMaterialfv(GL_FRONT, GL_SHININESS, no_shininess);
  glMaterialfv(GL_FRONT, GL_EMISSION, no_mat);
  glutSolidSphere(1.0, 16, 16);
  glPopMatrix();

  glPushMatrix();
  glTranslatef (-1.25, 0.0, 0.0);
  glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
  glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
  glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
  glMaterialfv(GL_FRONT, GL_SHININESS, low_shininess);
  glMaterialfv(GL_FRONT, GL_EMISSION, no_mat);
  glutSolidSphere(1.0, 16, 16);
  glPopMatrix();

  glPushMatrix();
  glTranslatef (1.25, 0.0, 0.0);
  glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
  glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
  glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
  glMaterialfv(GL_FRONT, GL_SHININESS, high_shininess);
  glMaterialfv(GL_FRONT, GL_EMISSION, no_mat);
  glutSolidSphere(1.0, 16, 16);
  glPopMatrix();

  glPushMatrix();
  glTranslatef (3.75, 0.0, 0.0);
  glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
  glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
  glMaterialfv(GL_FRONT, GL_SPECULAR, no_mat);
  glMaterialfv(GL_FRONT, GL_SHININESS, no_shininess);
  glMaterialfv(GL_FRONT, GL_EMISSION, mat_emission);
  glutSolidSphere(1.0, 16, 16);
  glPopMatrix();

  /*
    Bottom row
  */
  glPushMatrix();
  glTranslatef (-3.75, -3.0, 0.0);
  glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient_color);
  glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
  glMaterialfv(GL_FRONT, GL_SPECULAR, no_mat);
  glMaterialfv(GL_FRONT, GL_SHININESS, no_shininess);
  glMaterialfv(GL_FRONT, GL_EMISSION, no_mat);
  glutSolidSphere(1.0, 16, 16);
  glPopMatrix();

  glPushMatrix();
  glTranslatef (-1.25, -3.0, 0.0);
  glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient_color);
  glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
  glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
  glMaterialfv(GL_FRONT, GL_SHININESS, low_shininess);
  glMaterialfv(GL_FRONT, GL_EMISSION, no_mat);
  glutSolidSphere(1.0, 16, 16);
  glPopMatrix();
  
  glPushMatrix();
  glTranslatef (1.25, -3.0, 0.0);
  glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient_color);
  glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
  glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
  glMaterialfv(GL_FRONT, GL_SHININESS, high_shininess);
  glMaterialfv(GL_FRONT, GL_EMISSION, no_mat);
  glutSolidSphere(1.0, 16, 16);
  glPopMatrix();

  glPushMatrix();
  glTranslatef (3.75, -3.0, 0.0);
  glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient_color);
  glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
  glMaterialfv(GL_FRONT, GL_SPECULAR, no_mat);
  glMaterialfv(GL_FRONT, GL_SHININESS, no_shininess);
  glMaterialfv(GL_FRONT, GL_EMISSION, mat_emission);
  glutSolidSphere(1.0, 16, 16);
  glPopMatrix();
  
}

void drawScreencast14(void)
{
  drawLight();
  currentTexture = textures[TEX_CRATE];
  cube(0,0,0, 1,1,1, 0); 
}

void drawScreencast15(void)
{

  GLenum minfilter = GL_NEAREST;
  GLenum magfilter = GL_NEAREST;
  GLenum env = GL_MODULATE;
  //GLenum env = GL_REPLACE;

  GLenum wraps = GL_CLAMP;
  GLenum wrapt = GL_REPEAT;
  //  GLenum wrapt = GL_MIRRORED_REPEAT;

  drawLight();
  /*
  currentTexture = textures[TEX_CRATE];
  cube(0,0,0, 1,1,1, 0);

  currentTexture = textures[TEX_FIRE];
  cone(2,0,0, 1,1, 5); 

  currentTexture = textures[TEX_VENUS];
  sphere(0,1,1.5, 0.5,0);
  */
  //currentTexture = textures[TEX_FIRE];
  //currentTexture = textures[TEX_EARTH];
  //currentTexture = textures[TEX_ICE];
  //currentTexture = textures[TEX_DEFAULT];
  //cylinder(-2,0,0, 1,1);
  //currentTexture = textures[TEX_DEFAULT];

  /*
   * Other Texture functions/Parameters
   */

  glEnable(GL_TEXTURE_2D);  
  currentTexture = textures[TEX_ICE];
  glBindTexture(GL_TEXTURE_2D,currentTexture);
  // Minification and Magnification Filters
  // Used to perform calculations as to how a texel corresponds to 
  //  a pixel on the screen
  // GLenum minfilter = GL_NEAREST
  // GLenum magfilter = GL_NEAREST
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, minfilter);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, magfilter);
  // Clamp or Repeat texture outside of [0,1]
  // GLenum wraps|wrapt = GL_REPEAT, GL_CLAMP, GL_CLAMP_TO_BORDER,
  //                      GL_CLAMP_TO_EDGE, GL_MIRRORED_REPEAT
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wraps);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, wrapt);
  // Specifies how texture values are combined with the color values of 
  //  the fragment being processed
  // GLenum env = GL_REPLACE, GL_BLEND, GL_MODULATE, GL_DECAL, 
  //              GL_COMBINE, GL_ADD
  glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, env);
  // Determine the color to be used for GL_BLEND operations
  //glTexEnvfv(GL_TEXTURE_ENV, GL_TEXTURE_ENV_COLOR, env_color);
  // 
  //glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, border_color);
  
  glBegin(GL_QUADS);
  glNormal3f(0,0,1);
  glTexCoord2f(0,0); glVertex3f(0,0,0);
  glTexCoord2f(2,0); glVertex3f(1,0,0);
  glTexCoord2f(2,2); glVertex3f(1,1,0);
  glTexCoord2f(0,2); glVertex3f(0,1,0);

  glTexCoord2f(0,0); glVertex3f(-1,1,0);
  glTexCoord2f(2,0); glVertex3f(1,1,0);
  glTexCoord2f(2,2); glVertex3f(1,3,0);
  glTexCoord2f(0,2); glVertex3f(-1,3,0);
  glEnd();
  glDisable(GL_TEXTURE_2D);

}
