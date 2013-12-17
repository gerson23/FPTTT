//==============================================================================
// Computer Graphics - Department of Informatics Engineering - 2012/2013
// University of Coimbra
// Gerson de Paulo Carlos (2012163742)
//==============================================================================

//==============================================================================
//==================================================================== Libraries
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <vector>
#include <string>
#include <sstream>
#include <GLUT/glut.h>
//#include "glm/glm.h"

//==============================================================================
//==================================================================== Constants
#define PI 3.1415
#define SPEED_MOV 5
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ Fields limits
#define X_LOW -400
#define X_HIGH 400
#define Y_LOW -150
#define Y_HIGH 150
#define Z_LOW -400
#define Z_HIGH 400
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ Screen size
#define wSCREEN 900
#define hSCREEN 700
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ Thickness of figures
#define THICKNESS 100
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ Number of interior walls
#define NO_WALLS 8
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ Visual modes of play
#define NO_MODES 3
#define NORMAL_MODE   0
#define HIGHFOG_MODE  1
#define DARKNESS_MODE 2
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ Player's identification
#define ID1 1
#define ID2 2
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ Player's statuses
#define STATUS_WIN 23
#define STATUS_NORMAL 20
#define STATUS_INVALID 24

#define NO_LIGHTS 1
#define NORMAL_LIGHT 2
#define HIGH_LIGHT 3

//==============================================================================
//============================================================= Global variables


//==============================================================================
//====================================================================== Classes

class CFigure {
  protected:
    GLfloat x, z, height;
  public:
    CFigure (GLfloat, GLfloat, GLfloat);
    ~CFigure ();
    virtual void draw();
};

class CBall : public CFigure {
  protected:
    GLfloat radius;
  public:
    CBall (GLfloat, GLfloat, GLfloat);
    ~CBall ();
    void draw();
};

class CExe : public CFigure {
  public:
    CExe (GLfloat, GLfloat, GLfloat);
    ~CExe ();
    void draw();
};

class CWall {
  protected:
    GLuint texture;
    GLfloat x, z;
    bool rotate;
  public:
    CWall (GLuint, GLfloat, GLfloat, bool);
    void draw();
    GLfloat getX();
    GLfloat getZ();
    bool getRotate();
};

class CPlayer {
  protected:
    GLfloat x, z;
    std::string name;
    GLint id;
    GLfloat camera;
    GLint status;
    GLint wins;
  public:
    CPlayer (GLfloat, GLfloat, std::string, GLint);
    GLfloat getX();
    GLfloat getZ();
    std::string  getName();
    GLint getID();
    GLfloat getCamera();
    GLint getStatus();
    GLint getWins();
    void setName(std::string);
    void setX(GLfloat);
    void setZ(GLfloat);
    void setCamera(GLfloat);
    void setStatus(GLint);
    void newGame();
    void addWin();
};

//==============================================================================
//==================================================================== Functions
double mod(GLfloat);

void drawText(std::string, GLfloat, GLfloat);

void drawHUD(CPlayer*, bool);

void drawCircle(GLfloat);

void drawBall(GLfloat, GLfloat, GLfloat);

void drawX(GLfloat, GLfloat, GLfloat);

GLint calcNearest(CPlayer*, GLfloat, GLfloat, bool);

GLfloat calcDist(CPlayer*, GLint, GLfloat, GLfloat);
