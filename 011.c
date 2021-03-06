#include "screencasts.h"

/*
 *  main()
 *  ----
 *  Start up GLUT and tell it what to do
 */
int main(int argc,char* argv[])
{
  initializeGlobals();
  /* screencast specific variables */
  windowName = "OpenGL screenscasts 11: Code Organization";
  screencastID = 11;
  toggleLight = 0;

  glutInit(&argc,argv);
  glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
  glutInitWindowSize(windowWidth,windowHeight);
  glutCreateWindow(windowName);

  glutDisplayFunc(display);
  glutReshapeFunc(displayReshape);
  glutKeyboardFunc(windowKey);
  glutSpecialFunc(windowSpecial);

  redisplayAll();
  glutMainLoop();
  return 0;
}

