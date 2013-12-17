//==============================================================================
// Computer Graphics - Department of Informatics Engineering - 2012/2013
// University of Coimbra
// Gerson de Paulo Carlos (2012163742)
//==============================================================================

//==============================================================================
//==================================================================== Libraries
#include "extra.h"
#include "RgbImage.h"

using namespace std;


//==============================================================================
//========================================================= Functions signatures
void reflection();

void clean();

void newGame(int opt);

//==============================================================================
//=============================================== Global variables and constants
GLfloat camera;
bool    map_view, light;
GLint   mode, light_mode;
//GLMmodel*  desert;
GLfloat ambient_light[] = {0.9f, 0.9f, 0.9f, 1.0f};
GLfloat fog_color[] = {0.7f, 0.7f, 0.7f, 1.0f};
GLfloat fog_density = 0.0f;
GLfloat specular[] = {1.0f, 1.0f, 1.0f, 1.0f};
GLfloat light_pos[] = {0.0f, Y_HIGH, 0.0f};
GLfloat spot_direction[] = {0.0f, -1.0f, 0.0f};
GLfloat spot_expoent = 0.5;
GLfloat spot_cutoff = 30;

CPlayer* player1;
CPlayer* player2;
CWall*  interior_walls[NO_WALLS];
GLint   pieces[3][3] = {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}};
vector<CFigure*> figures;
bool    game_status;

GLint   mouse_x, mouse_y;
//================================================================================
//=========================================================================== INIT

//------------------------------------------------------------ Texturas
GLuint  texture[3];
GLuint  tex;
RgbImage floorz, wall, ceiling;


