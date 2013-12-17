//==============================================================================
// Computer Graphics - Department of Informatics Engineering - 2012/2013
// University of Coimbra
// Gerson de Paulo Carlos (2012163742)
//==============================================================================

//==============================================================================
//==================================================================== Libraries
#include "extra.h"

//==============================================================================
//============================================== Returns the modulus of a number
double
mod(GLfloat num) {

  if(num > 0) return num;
  else return -num;
}

//==============================================================================
//================================================= Writes a string into the HUD
void
drawText(std::string text, GLfloat x, GLfloat y) {
  glRasterPos2f(x, y);
  for(std::string::iterator it = text.begin(); it != text.end(); it++)
    glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, *it);
  
}

//==============================================================================
//====================================================== Draws the HUD of player
void
drawHUD(CPlayer* player, bool map_view) {
  
  // Disable texture temporarily to use colors
  glDisable(GL_TEXTURE_2D);
  glDisable(GL_LIGHTING);
  glDisable(GL_FOG);
  
  glEnable(GL_COLOR_MATERIAL);
  glColorMaterial(GL_FRONT_AND_BACK, GL_DIFFUSE);
  if(player->getStatus() == STATUS_INVALID) {
    glColor4f(1.0f, 0.0f, 0.0f, 1.0f);
  }
  else {
    glColor4f(0.0f, 1.0f, 0.0f, 1.0f);
  }
  glBegin(GL_LINE_STRIP);
    glVertex3f(-0.4, -0.3, 0);
    glVertex3f(0.4, -0.3, 0);
    glVertex3f(0.4, 0.3, 0);
    glVertex3f(-0.4, 0.3, 0);
    glVertex3f(-0.4, -0.3, 0);
  glEnd();

  if(player->getStatus() == STATUS_INVALID) {
    glColor4f(0.0f, 1.0f, 0.0f, 1.0f);
  }
  drawCircle(0.1);
  
  drawText(player->getName(), -4.2, 4.2);

  if((!map_view) && (player->getStatus() == STATUS_WIN))
    drawText(player->getName() + " WINS!!!", -2, 4.2);
  
  std::stringstream ss;
  ss << player->getWins();
  if(!map_view) drawText(ss.str() + " Wins", 3, 4.2);

  glDisable(GL_COLOR_MATERIAL);
  glEnable(GL_FOG);
  glEnable(GL_LIGHTING);
  glEnable(GL_TEXTURE_2D);
}

//==============================================================================
//========================================= Draws a simple circle given a radius
void
drawCircle(GLfloat radius) {
  int points = 360;
  float x,y;
        
  glBegin(GL_LINES);
    for(int i=0; i<points; i++) {
      x = cos(((360.0/points)*i)*PI/180)*radius;
      y = sin(((360.0/points)*i)*PI/180)*radius;
      glVertex2f(0.0f, 0.0f);
      glVertex2f(x, y);
    }
    glVertex2f(0.0f, 0.0f);
    glVertex2f(cos(0.0)*radius, sin(0.0)*radius);
  glEnd();
}

//==================================================================== [CFigure]
//==================================================== CFigure class constructor
CFigure::CFigure(GLfloat x, GLfloat z, GLfloat height) {
  this->x = x;
  this->z = z;
  this->height = height;
}

CFigure::~CFigure() { }

//==================================================================== [CFigure]
//================================================== CFigure virtual draw method
void
CFigure::draw() { }


//====================================================================== [CBall]
//======================== CBall class constructor. Calls superclass constructor
CBall::CBall(GLfloat x, GLfloat z, GLfloat height)
 : CFigure(x, z, height) {}

//====================================================================== [CBall]
//======================================================= Class CBall destructor
CBall::~CBall() { }

//====================================================================== [CBall]
//========================================================= Draw the ball figure
void
CBall::draw() {
  GLfloat radius = 30, x, z;
  int points = 360;
  

  glDisable(GL_TEXTURE_2D);
  glPushMatrix();
    glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
    glEnable(GL_COLOR_MATERIAL);
    glColor4f(153./255., 153./255., 0.0f, 1.0f);
    glTranslatef(this->x, this->height, this->z);

    for(int k=0; k<THICKNESS; k++) {
      glBegin(GL_LINE_STRIP);
        for(int i=0; i<points; i++) {
          x = cos(((360./points)*i)*PI/180)*radius;
          z = sin(((360./points)*i)*PI/180)*radius;
          glVertex3f(x, 0.0f, z);
        }
        glVertex3f(cos(0.0)*radius, 0.0f, sin(0.0)*radius);
      glEnd();
      radius -= 0.05;
    }
    glDisable(GL_COLOR_MATERIAL);
  glPopMatrix();
  glEnable(GL_TEXTURE_2D);
}


//======================================================================= [CExe]
//========================= Class CExe constructor. Calls superclass constructor
CExe::CExe(GLfloat x, GLfloat z, GLfloat height)
  : CFigure(x, z, height) {}

//======================================================================= [CExe]
//======================================================== Class CExe destructor
CExe::~CExe() { }

//======================================================================= [CExe]
//============================================================ Draw the X figure
void
CExe::draw() {

  glDisable(GL_TEXTURE_2D);
  glPushMatrix();
    glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
    glEnable(GL_COLOR_MATERIAL);
    glColor4f(153./255., 0.0f, 0.0f, 1.0f);

    glTranslatef(this->x, this->height, this->z);

    for(int k=0; k<THICKNESS; k++) {
      glBegin(GL_LINES);
        glVertex3f(-30.0f+(k*0.05), 0.0f, -30.f);
        glVertex3f(30.0f+(k*0.05), 0.0f, 30.0f);
        glVertex3f(-30.0f+(k*0.05), 0.0f, 30.0f);
        glVertex3f(30.0f+(k*0.05), 0.0f, -30.0f);
      glEnd();
    }
    glDisable(GL_COLOR_MATERIAL);
  glPopMatrix();
  glEnable(GL_TEXTURE_2D);
}


//====================================================================== [CWall]
//====================================================== CWall class constructor
CWall::CWall(GLuint texture, GLfloat x, GLfloat z, bool rotate) {
  this->texture = texture;
  this->x = x;
  this->z = z;
  this->rotate = rotate;
}

//====================================================================== [CWall]
//================= Draw textures to create a thick wall, given coorinates (x,z)
void
CWall::draw() {
  glPushMatrix();
    glTranslatef(this->x, 0.0f, this->z);
    if(rotate) glRotatef(90.0f, 0.0f, 1.0f, 0.0f);
    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ Front
    glBindTexture(GL_TEXTURE_2D, this->texture);
      glBegin(GL_QUADS);
        glTexCoord2f(0.0f, 0.0f); glVertex3i(X_LOW/4, Y_LOW, -8.0f);
        glTexCoord2f(0.0f, 3.0f); glVertex3f(X_LOW/4, Y_HIGH, -8.0f);
        glTexCoord2f(8.0f, 3.0f); glVertex3f(X_HIGH/4, Y_HIGH, -8.0f);
        glTexCoord2f(8.0f, 0.0f); glVertex3f(X_HIGH/4, Y_LOW, -8.0f);
      glEnd();

    glBindTexture(GL_TEXTURE_2D, this->texture);
      glBegin(GL_QUADS);
        glTexCoord2f(0.0f, 0.0f); glVertex3i(X_HIGH/4, Y_LOW, 8.0f);
        glTexCoord2f(0.0f, 3.0f); glVertex3f(X_HIGH/4, Y_HIGH, 8.0f);
        glTexCoord2f(8.0f, 3.0f); glVertex3f(X_LOW/4, Y_HIGH, 8.0f);
        glTexCoord2f(8.0f, 0.0f); glVertex3f(X_LOW/4, Y_LOW, 8.0f);
      glEnd();

    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ Side
    glBindTexture(GL_TEXTURE_2D, this->texture);
      glBegin(GL_QUADS);
        glTexCoord2f(0.0f, 0.0f); glVertex3i(X_LOW/4, Y_LOW, -8.0f);
        glTexCoord2f(1.0f, 0.0f); glVertex3f(X_LOW/4, Y_LOW, 8.0f);
        glTexCoord2f(1.0f, 3.0f); glVertex3f(X_LOW/4, Y_HIGH, 8.0f);
        glTexCoord2f(0.0f, 3.0f); glVertex3f(X_LOW/4, Y_HIGH, -8.0f);
      glEnd();
    
    glBindTexture(GL_TEXTURE_2D, this->texture);
      glBegin(GL_QUADS);
        glTexCoord2f(0.0f, 0.0f); glVertex3i(X_HIGH/4, Y_LOW, 8.0f);
        glTexCoord2f(1.0f, 0.0f); glVertex3f(X_HIGH/4, Y_LOW, -8.0f);
        glTexCoord2f(1.0f, 3.0f); glVertex3f(X_HIGH/4, Y_HIGH, -8.0f);
        glTexCoord2f(0.0f, 3.0f); glVertex3f(X_HIGH/4, Y_HIGH, 8.0f);
      glEnd();
    
    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ Top
    glBindTexture(GL_TEXTURE_2D, this->texture);
      glBegin(GL_QUADS);
        glTexCoord2f(0.0f, 0.0f); glVertex3i(X_LOW/4, Y_HIGH-1, -8.0f);
        glTexCoord2f(1.0f, 0.0f); glVertex3f(X_LOW/4, Y_HIGH-1, 8.0f);
        glTexCoord2f(1.0f, 3.0f); glVertex3f(X_HIGH/4, Y_HIGH-1, 8.0f);
        glTexCoord2f(0.0f, 3.0f); glVertex3f(X_HIGH/4, Y_HIGH-1, -8.0f);
      glEnd();
  glPopMatrix();
}

//====================================================================== [CWall]
//====================================================================== Getters
GLfloat
CWall::getX() {
  return this->x;
}

GLfloat
CWall::getZ() {
  return this->z;
}

bool
CWall::getRotate() {
  return this->rotate;
}


//==================================================================== [CPlayer]
//==================================================== CPlayer class constructor
CPlayer::CPlayer(GLfloat x, GLfloat z, std::string name, GLint id) {
  this->x = x;
  this->z = z;
  this->name = name;
  this->id = id;
  this->camera = 0;
  this->status = STATUS_NORMAL;
  this->wins = 0;
}

void
CPlayer::newGame() {
  this->x = 0.0f;
  this->z = 100.0f;
  this->camera = 0;
  this->status = STATUS_NORMAL;
}

void
CPlayer::addWin() {
  this->wins = this->wins + 1;
}

//==================================================================== [CPlayer]
//====================================================================== Getters
GLfloat
CPlayer::getX() {
  return this->x;
}

GLfloat
CPlayer::getZ() {
  return this->z;
}

std::string
CPlayer::getName() {
  return this->name;
}

GLint
CPlayer::getID() {
  return this->id;
}

GLfloat
CPlayer::getCamera() {
  return this->camera;
}

GLint
CPlayer::getStatus() {
  return this->status;
}

GLint
CPlayer::getWins() {
  return this->wins;
}

//==================================================================== [CPlayer]
//====================================================================== Setters
void
CPlayer::setX(GLfloat x) {
  this->x = x;
}

void
CPlayer::setZ(GLfloat z) {
  this->z = z;
}

void
CPlayer::setName(std::string name) {
  this->name = name;
}

void
CPlayer::setCamera(GLfloat camera) {
  this->camera = camera;
}

void
CPlayer::setStatus(GLint status) {
  this->status = status;
}

//==============================================================================
//====================  Calculate the nearest plane to player's current position
//============================== This should indicate the plane he/she came from
GLint calcNearest(CPlayer* player, GLfloat x, GLfloat z, bool rotate) {
  GLfloat base, top, side1, side2;

  if(!rotate) {
    base =  calcDist(player, 0, x, z);
    top =   calcDist(player, 1, x, z);
    side1 = calcDist(player, 2, x, z);
    side2 = calcDist(player, 3, x, z);
  }
  else {
    base  = calcDist(player, 4, x, z);
    top   = calcDist(player, 5, x, z);
    side1 = calcDist(player, 6, x, z);
    side2 = calcDist(player, 7, x, z);
  }
  
  if((base < top) && (base < side1) && (base < side2)) return 0;
  if((top < base) && (top < side1) && (top < side2)) return 1;
  if((side1 < base) && (side1 < top) && (side1 < side2)) return 2;
  if((side2 < base) && (side2 < top) && (side2 < side1)) return 3;
  
  return -1;
}

//==============================================================================
//============== Calculate a distance from a point (x0,y0) to the line ax+by+c=0
GLfloat calcDist(CPlayer* player, GLint pos, GLfloat x, GLfloat z) {
  GLfloat dist;
  GLfloat a, b, c, x0, y0;

  x0 = player->getX(); y0 = player->getZ();

  switch(pos) {
    case 0:
      a = 0.0f; b = 1.0f; c = z+8;
      break;
    case 1:
      a = 0.0f; b = 1.0f; c = z-8;
      break;
    case 2:
      a = 1.0f; b = 0.0f; c = x+(X_LOW/4);
      break;
    case 3:
      a = 1.0f; b = 0.0f; c = x+(X_HIGH/4);
      break;
    case 4:
      a = 0.0f; b = 1.0f; c = z+(X_HIGH/4);
      break;
    case 5:
      a = 0.0f; b = 1.0f; c = z+(X_LOW/4);
      break;
    case 6:
      a = 1.0f; b = 0.0f; c = x-8;
      break;
    case 7:
      a = 1.0f; b = 0.0f; c = x+8;
      break;
  }
  
  dist = a*x0 + b*y0 - c;
  if(dist < 0) dist *= -1;
  dist /= sqrt(pow(a,2)+pow(b,2));

  return dist;
}
