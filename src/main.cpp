//==============================================================================
// Computer Graphics - Department of Informatics Engineering - 2012/2013
// University of Coimbra
// Gerson de Paulo Carlos (2012163742)
//==============================================================================


//==============================================================================
//==================================================================== Libraries
#include "main.h"


//==============================================================================
//======================================================= Sub-level menu handler
void
menuGame(int opt) {
  switch(opt) {
    case 1:
    case 2:
    case 3:
      newGame(opt);
      break;
    case 4:
      light_mode = NO_LIGHTS;
      break;
    case 5:
      light_mode = NORMAL_LIGHT;
      break;
    case 6:
      light_mode = HIGH_LIGHT;
      break;
    default:
      cout << "Ronaldo!" << endl;
  }
}

//==============================================================================
//======================================================= Top-level menu handler
void
menuMain(int opt) {
  switch(opt) {
    // Quit
    case 2:
      clean();
      exit(0);
      break;
    default:
      cout << "Ronaldo!2" << endl;
  }
}

//==============================================================================
//============================================================ Create popup menu
void
createMenu() {
  GLint submenu1, submenu2, menu, about, help, walking, marking;

  submenu1 = glutCreateMenu(menuGame);
  glutAddMenuEntry("No Fog", 1);
  glutAddMenuEntry("Low Fog", 2);
  glutAddMenuEntry("High Fog", 3);

  submenu2 = glutCreateMenu(menuGame);
  glutAddMenuEntry("No Light", 4);
  glutAddMenuEntry("Low Light", 5);
  glutAddMenuEntry("High Light", 6);
  
  about = glutCreateMenu(menuGame);
  glutAddMenuEntry("FPTTT v0.95", 0);
  
  walking = glutCreateMenu(menuGame);
  glutAddMenuEntry("WASD keys and mouse", 0);

  marking = glutCreateMenu(menuGame);
  glutAddMenuEntry("Right click with the mouse in current position", 0);

  help = glutCreateMenu(menuGame);
  glutAddSubMenu("Walking", walking);
  glutAddSubMenu("Marking", marking);

  menu = glutCreateMenu(menuMain);
  glutAddSubMenu("New Game", submenu1);
  glutAddSubMenu("Set Light", submenu2);
  glutAddMenuEntry("Quit", 2);
  glutAddSubMenu("Help", help);
  glutAddSubMenu("About", about);
  glutAttachMenu(GLUT_RIGHT_BUTTON);
}

//==============================================================================
//======================================================== New Game menu handler
void
newGame(int opt) {
  player1->newGame();

  player2->newGame();
  
  // this should call CFigure destructor
  figures.clear();
  camera = 0;

  switch(opt) {
    case 1:
      fog_density = 0.0f;
      break;
    case 2:
      fog_density = 0.001f;
      break;
    case 3:
      fog_density = 0.005f;
      break;
  }

  for(int i=0; i<3; i++) {
    for(int j=0; j<3; j++) {
      pieces[i][j] = 0;
    }
  }
}

//==============================================================================
//=========================================================== Defines all lights
void
defineLights() {
  //---------------------------------------- Ambient light
  glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambient_light);
  glLightModeli(GL_LIGHT_MODEL_COLOR_CONTROL, GL_SEPARATE_SPECULAR_COLOR);

  //glMaterialfv(GL_FRONT, GL_SPECULAR, specular);
  //GLfloat ronaldo[] = {0.0f, 0.0f, 0.f, 1.0f};
  glLightfv(GL_LIGHT0, GL_POSITION, light_pos);
  glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, spot_direction);
  glLightf(GL_LIGHT0, GL_SPOT_EXPONENT, spot_expoent);
  glLightf(GL_LIGHT0, GL_SPOT_CUTOFF, spot_cutoff);
  
}

//==============================================================================
//=========================================================== Define frog effect
void
defineFog() {
  glFogfv(GL_FOG_COLOR, fog_color);
  if(mode == NORMAL_MODE) {
    glFogi(GL_FOG_MODE, GL_LINEAR);
  }
  else {
    glFogi(GL_FOG_MODE, GL_EXP);
  }

  glFogf(GL_FOG_START, 0.0f);
  glFogf(GL_FOG_END, 400.0f);

  if(mode == HIGHFOG_MODE) {
    glFogf(GL_FOG_DENSITY, fog_density);
  }
  else if(mode == DARKNESS_MODE) {
    glFogf(GL_FOG_DENSITY, fog_density);
  }
}

//==============================================================================
//==================================== Define textures that will be used further
void
defineTextures() {   

	//----------------------------------------- Wall
	glGenTextures(1, &texture[0]);
	glBindTexture(GL_TEXTURE_2D, texture[0]);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	wall.LoadBmpFile("resources/wall.bmp");
	glTexImage2D(GL_TEXTURE_2D, 0, 3, 
	  wall.GetNumCols(),
		wall.GetNumRows(), 0, GL_RGB, GL_UNSIGNED_BYTE,
		wall.ImageData());

  //---------------------------------------- Floor
  glGenTextures(1, &texture[1]);
  glBindTexture(GL_TEXTURE_2D, texture[1]);
  glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
  floorz.LoadBmpFile("resources/floor.bmp");
  glTexImage2D(GL_TEXTURE_2D, 0, 3,
    floorz.GetNumCols(),
    floorz.GetNumRows(), 0, GL_RGB, GL_UNSIGNED_BYTE,
    floorz.ImageData());
  
  //---------------------------------------- Ceiling
  glGenTextures(1, &texture[2]);
  glBindTexture(GL_TEXTURE_2D, texture[2]);
  glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
  ceiling.LoadBmpFile("resources/ceil.bmp");
  glTexImage2D(GL_TEXTURE_2D, 0, 3,
    ceiling.GetNumCols(),
    ceiling.GetNumRows(), 0, GL_RGB, GL_UNSIGNED_BYTE,
    ceiling.ImageData());
}

//==============================================================================
//======================================================= Initial configurations
void
init(int argc, char* argv[]) {

  glClearColor(0.0, 0.0, 0.0, 1.0);

  // selects random mode for current play
  srand((unsigned)time(0));
  //mode = rand() % NO_MODES;
  mode = 2;
  light_mode = NORMAL_LIGHT;

	glShadeModel(GL_SMOOTH);
  glEnable(GL_FOG);
  defineFog();
  defineTextures();
  defineLights();
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_DEPTH_TEST);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  
  glCullFace(GL_BACK);
  glEnable(GL_CULL_FACE);

  // rotation of camera
  camera = 0;
  
  // initial position of the player
  string name = "Player 1";
  if(argc > 0) name = argv[1];
  player1 = new CPlayer(0.0f, 100.0f, name, ID1);

  if(argc > 1) name = argv[2];
  else name = "Player 2";
  player2 = new CPlayer(0.0f, 100.0f, name, ID2);
  
  game_status = false;

  light = false;

  interior_walls[0] = new CWall(texture[0], 3*X_HIGH/4, Z_HIGH/3, false);
  interior_walls[1] = new CWall(texture[0], 3*X_HIGH/4, Z_LOW/3, false);
  interior_walls[2] = new CWall(texture[0], 3*X_LOW/4, Z_HIGH/3, false);
  interior_walls[3] = new CWall(texture[0], 3*X_LOW/4, Z_LOW/3, false);
  interior_walls[4] = new CWall(texture[0], Z_HIGH/3, 3*X_HIGH/4, true);
  interior_walls[5] = new CWall(texture[0], Z_LOW/3, 3*X_HIGH/4, true);
  interior_walls[6] = new CWall(texture[0], Z_HIGH/3, 3*X_LOW/4, true);
  interior_walls[7] = new CWall(texture[0], Z_LOW/3, 3*X_LOW/4, true);
  
  createMenu();
}

//==============================================================================
//================ Check collisions with internal walls and correct if necessary
void
checkCollisions() {
  
  GLfloat player_x = player1->getX();
  GLfloat player_z = player1->getZ();

  // verifies walls limit
  if(player_x <= X_LOW) player_x = X_LOW+1;
  else if(player_x >= X_HIGH) player_x = X_HIGH-1;

  if(player_z <= Z_LOW) player_z = Z_LOW+1;
  else if(player_z >= Z_HIGH) player_z = Z_HIGH-1;

  // check interior walls using the nearest walls as "entry" wall
  GLfloat x, z;
  bool rotate;
  
  // for each internal wall
  for(int i=0; i<NO_WALLS; i++) {
    x = interior_walls[i]->getX();
    z = interior_walls[i]->getZ();
    rotate = interior_walls[i]->getRotate();

    // both sides
    if(!rotate) {
      if((player_z > (z-8)) && (player_z < (z+8))) {
        if((player_x > (x+(X_LOW/4))) && (player_x < (x+(X_HIGH/4)))) {
          switch(calcNearest(player1, x, z, rotate)) {
            case 0:
              player_z = z+9;
              break;
            case 1:
              player_z = z-9;
              break;
            case 2:
              player_x = x+(X_LOW/4)-1;
              break;
            case 3:
              player_x = x+(X_HIGH/4)+1;
              break;
          }
        }
      }
    }
    // fronts and backs
    else {
      if((player_z > (z+(X_LOW/4))) && (player_z < (z+(X_HIGH/4)))) {
        if((player_x > (x-8)) && (player_x < (x+8))) {
          switch(calcNearest(player1, x, z, rotate)) {
            case 0:
              player_z = z+(X_HIGH/4)+1;
              break;
            case 1:
              player_z = z+(X_LOW/4)-1;
              break;
            case 2:
              player_x = x-8-1;
              break;
            case 3:
              player_x = x+8+1;
              break;
          }
        }
      }
    }
  }
  
  // update players positions
  player1->setX(player_x);
  player1->setZ(player_z);
}

//==============================================================================
//=========================== Update camera rotation given actual mouse position
void
mouse(int x, int y) {
  static int old_x;

  x -= (wSCREEN/2);
  y -= (hSCREEN/2);
  //cout << "x: " << x- << " y: " << y- << endl;
  if((x > 0) && ((old_x-x) > 0)) return;
  if((x < 0) && ((old_x-x) < 0)) return;

  if(x > (wSCREEN/3)) {
    camera += 2;
    if(camera > 180) camera = -180;
  }
  else if((-x) > (wSCREEN/3)) {
    camera -= 2;
    if(camera < -180) camera = 180;
  }
  else if(x > (wSCREEN/7)) {
    camera += 1;
    if(camera > 180) camera = -180;
  }
  else if((-x) > (wSCREEN/7)) {
    camera -= 1;
    if(camera < -180) camera = -180;
  }
}

//==============================================================================
//=========================== Separate drawing function due to reflection scheme
void
drawFloor() {
  glEnable(GL_TEXTURE_2D);
  
  glNormal3f(0, 1, 0);
  glBindTexture(GL_TEXTURE_2D, texture[1]);
    glBegin(GL_QUADS);
      glTexCoord2f(0.0f, 0.0f);   glVertex3i(X_HIGH,  Y_LOW, Z_HIGH);
      glTexCoord2f(10.0f, 0.0f);  glVertex3i(X_HIGH,  Y_LOW, Z_LOW);
      glTexCoord2f(10.0f, 10.0f); glVertex3i(X_LOW,   Y_LOW, Z_LOW);
      glTexCoord2f(0.0f, 10.0f);  glVertex3i(X_LOW,   Y_LOW, Z_HIGH);
    glEnd();
}

//==============================================================================
//======================================================= >De facto< draws scene
void
drawScene(bool isReflection) {
  
  // Sets light strength as set by user
  if(light_mode == NO_LIGHTS) {
    ambient_light[0] = 0.3f; ambient_light[1] = 0.3f; ambient_light[2] = 0.3f;
  }
  else if(light_mode == NORMAL_LIGHT) {
    ambient_light[0] = 0.6f; ambient_light[1] = 0.6f; ambient_light[2] = 0.6f;
  }
  else {
    ambient_light[0] = 0.9f; ambient_light[1] = 0.9f; ambient_light[2] = 0.9f;
  }
  defineFog();
  defineLights();
  glEnable(GL_LIGHTING);
  glEnable(GL_LIGHT0);
  

  //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ Walls
  // Back
  glBindTexture(GL_TEXTURE_2D, texture[0]);
    glBegin(GL_QUADS);
      glTexCoord2f(0.0f, 0.0f); glVertex3i(X_LOW,   Y_LOW,  Z_LOW);
      glTexCoord2f(8.0f, 0.0f); glVertex3i(X_HIGH,  Y_LOW,  Z_LOW);
      glTexCoord2f(8.0f, 3.0f); glVertex3i(X_HIGH,  Y_HIGH, Z_LOW);
      glTexCoord2f(0.0f, 3.0f); glVertex3i(X_LOW,   Y_HIGH, Z_LOW);
    glEnd();
  // Left
  glBindTexture(GL_TEXTURE_2D, texture[0]);
    glBegin(GL_QUADS);
      glTexCoord2f(0.0f, 0.0f); glVertex3i(X_LOW, Y_LOW,  Z_HIGH);
      glTexCoord2f(8.0f, 0.0f); glVertex3i(X_LOW, Y_LOW,  Z_LOW);
      glTexCoord2f(8.0f, 3.0f); glVertex3i(X_LOW, Y_HIGH, Z_LOW);
      glTexCoord2f(0.0f, 3.0f); glVertex3i(X_LOW, Y_HIGH, Z_HIGH);
    glEnd();
  // Right
  glBindTexture(GL_TEXTURE_2D, texture[0]);
    glBegin(GL_QUADS);
      glTexCoord2f(0.0f, 0.0f); glVertex3i(X_HIGH, Y_LOW,   Z_LOW);
      glTexCoord2f(8.0f, 0.0f); glVertex3i(X_HIGH, Y_LOW,   Z_HIGH);
      glTexCoord2f(8.0f, 3.0f); glVertex3i(X_HIGH, Y_HIGH,  Z_HIGH);
      glTexCoord2f(0.0f, 3.0f); glVertex3i(X_HIGH, Y_HIGH,  Z_LOW);
    glEnd();
  // Front
  glBindTexture(GL_TEXTURE_2D, texture[0]);
    glBegin(GL_QUADS);
      glTexCoord2f(0.0f, 0.0f); glVertex3i(X_HIGH,  Y_LOW,  Z_HIGH);
      glTexCoord2f(8.0f, 0.0f); glVertex3i(X_LOW,   Y_LOW,  Z_HIGH);
      glTexCoord2f(8.0f, 3.0f); glVertex3i(X_LOW,   Y_HIGH, Z_HIGH);
      glTexCoord2f(0.0f, 3.0f); glVertex3i(X_HIGH,  Y_HIGH, Z_HIGH);
    glEnd();

  //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ Ceiling
  glBindTexture(GL_TEXTURE_2D, texture[2]);
    glBegin(GL_QUADS);
    if(!isReflection) {
      glTexCoord2f(0.0f, 0.0f); glVertex3i(X_HIGH,  Y_HIGH, Z_LOW);
      glTexCoord2f(8.0f, 0.0f); glVertex3i(X_HIGH,  Y_HIGH, Z_HIGH);
      glTexCoord2f(8.0f, 8.0f); glVertex3i(X_LOW,   Y_HIGH, Z_HIGH);
      glTexCoord2f(0.0f, 8.0f); glVertex3i(X_LOW,   Y_HIGH, Z_LOW);
    }
    else {
      glTexCoord2f(0.0f, 0.0f); glVertex3i(X_HIGH,  Y_HIGH, Z_LOW);
      glTexCoord2f(0.0f, 8.0f); glVertex3i(X_LOW,   Y_HIGH, Z_LOW);
      glTexCoord2f(8.0f, 8.0f); glVertex3i(X_LOW,   Y_HIGH, Z_HIGH);
      glTexCoord2f(8.0f, 0.0f); glVertex3i(X_HIGH,  Y_HIGH, Z_HIGH);
    }
    glEnd();
  
  //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ Interior Walls
  for(int i=0; i<8; i++) interior_walls[i]->draw();

  //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ HUD
  glPushMatrix();
    glTranslatef(player1->getX()+(sin(camera*PI/180)*4), 0, 
                player1->getZ()-(cos(camera*PI/180)*4));
    glRotatef(-camera, 0.0f, 1.0f, 0.0f);
    drawHUD(player1, map_view);
  glPopMatrix();
  
  //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ Figures
  if(!isReflection) {
    for(vector<CFigure*>::iterator it = figures.begin(); it != figures.end(); it++) {
      (*it)->draw();
    }
  }
  
  // fix to return ambient light to its own color
  glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, ambient_light);
  
  // update camera for next iteration
  mouse(mouse_x, mouse_y);
}


//==============================================================================
//============================================= Create a reflection on the floor
void
reflection() {
  glEnable(GL_STENCIL_TEST);
  glColorMask(0, 0, 0, 0);
  glDisable(GL_DEPTH_TEST);
  glStencilFunc(GL_ALWAYS, 1, 1);
  glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);

  drawFloor();

  glColorMask(1, 1, 1, 1);
  glEnable(GL_DEPTH_TEST);

  glStencilFunc(GL_EQUAL, 1, 1);
  glStencilOp(GL_KEEP, GL_KEEP, GL_KEEP);
  
  glPushMatrix();
    glScalef(1, -1, 1);
    glTranslatef(0, X_HIGH/2, 0);
    drawScene(true);
  glPopMatrix();

  glDisable(GL_STENCIL_TEST);

  glEnable(GL_BLEND);
  glEnable(GL_COLOR_MATERIAL);
  glColor4f(1, 1, 1, 0.9);
  drawFloor();
  glDisable(GL_BLEND);
  glDisable(GL_COLOR_MATERIAL);
  
  glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, ambient_light);
}

  
//==============================================================================
//======================================================== Manages scene drawing
void
display(void) {
 
  glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ Clear
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
	glViewport (0,0,wSCREEN, hSCREEN);
  
  //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ Normal view
  if(!map_view) {
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(98.0, wSCREEN/hSCREEN, 0.1, 1200);
    
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(player1->getX(), 0, player1->getZ(), 
    (player1->getX()+sin(camera*PI/180)), 0, (player1->getZ()+sin((camera-90)*PI/180)), 
      0, 1, 0);
    
    drawScene(false);
    reflection();
	}
  //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ Map view
  else {
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(X_LOW, X_HIGH, Z_LOW, Z_HIGH, 0.1, 1200);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(0, Y_HIGH, 0,
      0, 0, 0,
      0, 0, -1);

    drawScene(false);
    drawFloor();

  }

	glutSwapBuffers();
}

//==============================================================================
//=================================================== Delete dynamic memory used
void
clean() {

  for(int i=0; i<8; i++) delete interior_walls[i];
  delete player1;
  delete player2;
}

//==============================================================================
//================================================ Changes current active player
void
changePlayer() {
  CPlayer* tmp;
  
  // update camera for actual player
  player1->setCamera(camera);
  camera = player2->getCamera();

  tmp = player1;
  player1 = player2;
  player2 = tmp;
}

//==============================================================================
//======================================== Verify is current player won the game
bool
verifyGame() {
  GLint id = player1->getID();
  
  // externals lines and rows
  if((pieces[1][0] == id) && (pieces[0][0] == id) && (pieces[2][0] == id)) {
    return true;
  }
  if((pieces[0][1] == id) && (pieces[0][0] == id) && (pieces[0][2] == id)) {
    return true;
  }
  if((pieces[1][2] == id) && (pieces[0][2] == id) && (pieces[2][2] == id)) {
    return true;
  }
  if((pieces[2][1] == id) && (pieces[2][0] == id) && (pieces[2][2] == id)) {
    return true;
  }
  
  // central piece
  if(pieces[1][1] == id) {
    if((pieces[0][0] == id) && (pieces[2][2] == id)) {
      return true;
    }
    if((pieces[0][1] == id) && (pieces[2][1] == id)) {
      return true;
    }
    if((pieces[0][2] == id) && (pieces[2][0] == id)) {
      return true;
    }
    if((pieces[1][2] == id) && (pieces[1][0] == id)) {
      return true;
    }
  }

  return false;
}


//==============================================================================
//=========================================================== Try to make a play
void
shotTry() {
  if(player1->getStatus() == STATUS_WIN) return;

  GLfloat x = player1->getX();
  GLfloat z = player1->getZ();
  
  GLint i, j;
  for(i=0; i<3; i++) {
    for(j=0; j<3; j++) {
      if((z < (Z_LOW+((j+1)*(2.*Z_HIGH)/3.))) && (x < (X_LOW+((i+1)*(2.*X_HIGH)/3.))))
        goto FoundPos;
    }
  }
//Yeah, sometimes goto sucks, but here it is a nice solution
FoundPos:
  if(pieces[i][j] == 0) {
    pieces[i][j] = player1->getID();
    x = (X_LOW+((i+1)*(2.*X_HIGH)/3.)-((2.*X_HIGH)/6.));
    z = (Z_LOW+((j+1)*(2.*Z_HIGH)/3.)-((2.*Z_HIGH)/6.));
    if(player1->getID() == ID1)
      figures.push_back(new CBall(x, z, Y_LOW+1));
    else
      figures.push_back(new CExe(x, z, Y_LOW+1));

    if(verifyGame()) {
      player1->setStatus(STATUS_WIN);
      player1->addWin();
    }
    else {
      player1->setStatus(STATUS_NORMAL);
      changePlayer();
    }
  }
  else {
    //TODO: give a better feedback
    player1->setStatus(STATUS_INVALID);
    cout << "Invalid moviment!" << endl;
  }

}

//==============================================================================
//============================================================== Keyboard events
void
keyboard(unsigned char key, int x, int y) {
	  
    GLfloat player_x = player1->getX();
    GLfloat player_z = player1->getZ();

    switch (key) {
      // quits game
      case 'q':
        clean();
        exit(0);
        break;
      
      // walks forward
      case 'w':
      case 'W':
        player_z -= cos(camera*PI/180)*SPEED_MOV;
        player_x += sin(camera*PI/180)*SPEED_MOV;
        player1->setZ(player_z);
        player1->setX(player_x);
        checkCollisions();
        break;
      
      // walks backwards
      case 's':
      case 'S':
        player_z += cos(camera*PI/180)*SPEED_MOV;
        player_x -= sin(camera*PI/180)*SPEED_MOV;
        player1->setZ(player_z);
        player1->setX(player_x);
        checkCollisions();
        break;

      // walks left
      case 'a':
      case 'A':
        player_x -= cos(camera*PI/180)*SPEED_MOV;
        player_z -= sin(camera*PI/180)*SPEED_MOV;
        player1->setZ(player_z);
        player1->setX(player_x);
        checkCollisions();
        break;

      // walks right
      case 'd':
      case 'D':
        player_x += cos(camera*PI/180)*SPEED_MOV;
        player_z += sin(camera*PI/180)*SPEED_MOV;
        player1->setZ(player_z);
        player1->setX(player_x);
        checkCollisions();
        break;
      
      case 'm':
      case 'M':
        map_view = !map_view;
        break;

      default:
        cout << "Invalid input." << endl;
        break;
   }


}

//==============================================================================
//========================================================== Mouse click handler
void
mouse_click(int button, int state, int x, int y) {
  if((button == GLUT_LEFT_BUTTON) && (state == GLUT_DOWN)) {
    shotTry();
  }
}

//==============================================================================
//=================================== Callback function for mouse passive motion
void
mouse_callback(int x, int y) {
  mouse_x = x;
  mouse_y = y;
}

//==============================================================================
//========================================== Callback function for display timer
void
timer_callback(int value) {

  display();

  glutTimerFunc(10, timer_callback, 1);
}

//==============================================================================
//================================================================ Main function
int
main(int argc, char* argv[]) {

	glutInit(&argc, argv);
	glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH | GLUT_STENCIL);
	glutInitWindowSize (wSCREEN, hSCREEN); 
	glutInitWindowPosition (100, 110); 
	glutCreateWindow ("First Person Tic-Tac-Toe {gerson@student.dei.uc.pt}");
  
	init(argc, argv);
	
	glutDisplayFunc(display); 
  glutKeyboardFunc(keyboard);
  glutPassiveMotionFunc(mouse_callback);
  glutMouseFunc(mouse_click);
	
  glutTimerFunc(50, timer_callback, 1);

	glutMainLoop();

	return 0;
}
