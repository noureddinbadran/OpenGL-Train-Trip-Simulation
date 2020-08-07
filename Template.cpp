#include <windows.h>		// Header File For Windows
#include <GL.h>			// Header File For The OpenGL32 Library
#include <glu.h>			// Header File For The GLu32 Library
#include <glut.h>// Header File For The GLut32 Library
#include <fstream>
#include <math.h>
#include "texture.h"
#include "camera.h"
#include "Model_3DS.h"
#include <sstream>
#include <iostream>
#include <stdarg.h>	
#include "heightMap.h"
#include "TgaLoader.h"
#include "math3d.h"
#include <mmsystem.h>


//include lib file


#pragma comment(lib,"opengl32.lib")
#pragma comment(lib,"glut32.lib")
#pragma comment(lib,"glu32.lib")
#pragma comment(lib,"GLAUX.LIB")
#pragma comment(lib,"winmm.LIB")

using namespace std;

HDC			hDC=NULL;		// Private GDI Device Context
HGLRC		hRC=NULL;		// Permanent Rendering Context
HWND		hWnd=NULL;		// Holds Our Window Handle
HINSTANCE	hInstance;		// Holds The Instance Of The Application

bool	keys[256];			// Array Used For The Keyboard Routine
bool	active=TRUE;		// Window Active Flag Set To TRUE By Default
bool	fullscreen=TRUE; 	// Fullscreen Flag Set To Fullscreen Mode By Default
Camera MyCamera;
LRESULT	CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);	// Declaration For WndProc

GLvoid ReSizeGLScene(GLsizei width, GLsizei height)		// Resize And Initialize The GL Window
{
	if (height==0)										// Prevent A Divide By Zero By
	{
		height=1;										// Making Height Equal One
	}

	glViewport(0,0,width,height);						// Reset The Current Viewport

	glMatrixMode(GL_PROJECTION);						// Select The Projection Matrix
	glLoadIdentity();									// Reset The Projection Matrix

	// Calculate The Aspect Ratio Of The Window
	gluPerspective(45.0f,(GLfloat)width/(GLfloat)height,10.1f,100000000.0f);

	glMatrixMode(GL_MODELVIEW);							// Select The Modelview Matrix
	glLoadIdentity();									// Reset The Modelview Matrix
}

float speed=0.1f;  //سرعة حركة الكاميرا
float y_target=0;
float x_target=0;
float z_target=0;
double earth_angle_x=0;
double earth_angle_y=0;
double earth_angle_z=0;

float y_loon=0; //ارتفاع المنطاد
float z_loon=0;
float tt=0;//لحظة البدء
float a=0;//تسارع المنطاد
float v=0;//سرعة المنطاد
float rr=5;//نصف قطر كرة المنطاد
float x_loon=200;
float yy=17; //الارتفاع الفاصل بين رأس المنطاد و قاعدته
bool play=false; //متحول بولياني يحدد بدأ تشغيل الصوت
int index=0; //دليل مصفوفة الارتفاع
float temp=0;//خطوة الصعود للأعلى
bool movement=false;//متحول لتحديد حركة الكاميرا إما على التضاريس أو مع المنطاد
bool seening=false;  //هذا المتحول لتحديد إما الدوران مع المنطاد أو مراقبته بدون الدوران معه
int port=0; //لتحديد نافذة الرؤيا
int vision=1;//لتحديد عدد نوافذ الرئيا
bool in_Space=true;//لتحديد فيما إذا كنت في الفضاء أو لا من أجل إذا كنا في الفضاء و أردنا العودة للأرض نعود لنقطة الأصل
bool go_with_him=false;//لأخذ قرار اللحاق بالمنطاد أو لا في حال النافذة الواحدة
//زاوية دوران المنطاد حول الأرض
float loon_angle=0;
bool Horizontal_Movment=false;//هذا المتحول لحركة الكميرا مع المنطاد حركة افقية مع الإرتفاع بحيث تستشعر بمقاومة الهواء
//متحولات اختيار الكوكب
bool Earth=true;
bool Moon;
bool no_terren=false;//هذا المتحول لرسم التضاريس أو لعدم رسمها




//صور القاطرة الرئيسية
int main_train_texture_roof,main_train_texture_front_down,main_train_texture_front_up,main_train_texture_back,main_train_texture_cover,main_train_texture_cover_motor_side;
int wheel;
int main_train_texture_body;
int complete;

//إشارة الوقوف
TGAImage stop;
TGAImage my_tree;

int stop2;
//صور المقطورة
int train_roof;



//صورة البداية
int loading;

//زجاج النوافذ
int glass;






int Buliding1;
int Buliding2;
int Buliding3;
int Buliding4;
int Buliding5;
int Buliding6;
int Buliding7;
int Buliding8;
int Buliding9;






//الكوكب المختار
string planet_selected;

GLuint	base;				// Base Display List For The Font Set
GLfloat	cnt1;				// 1st Counter Used To Move Text & For Coloring
GLfloat	cnt2;				// 2nd Counter Used To Move Text & For Coloring



double y3=0;
double y2=0;
double y4=0;

int terraintexture ;
int terraintexture_moon;
int terraintexture_Earth;
GLubyte * HeightData ;
int TerrainSize = 512;
float step = 1/512.0;
float scaleY = 0.2f;
float scaleX = 1;
float scaleZ = 1;
GLfloat initTerrainPositionX;
GLfloat initTerrainPositionY;
GLfloat initTerrainPositionZ;

inline GLubyte GetValue( int i , int j  ) {return (int)(HeightData[i*TerrainSize + j]);}
void SetupProjection(int width,int height);
long m_windowWidth=1366;
long m_windowHeight=768;


int top,down,Left,Right,back,front,loon,loon_bottom,Space_Box,Out,earth;
int ground,asphalt,green,brown,platform,roof,grass,box_wood,box_metal,pelvis,border,road,rasif,build;
float statue=0;

int i;
Model_3DS * rightside;
Model_3DS * top0;
Model_3DS * base0;
Model_3DS * leftside;
Model_3DS * back1;
Model_3DS * back2;
Model_3DS * front1;
Model_3DS * front2;
Model_3DS * tree;
Model_3DS * trafic_light;
Model_3DS * table;
Model_3DS *chair;
Model_3DS *chair2;
Model_3DS *woman1;
Model_3DS *woman2;
Model_3DS * window;
Model_3DS * house;
Model_3DS * light;
Model_3DS * wheel0 ;
Model_3DS * car0 ;

int x_camera(0),y_camera(0),z_camera(0);
float x_light=150000,y_light=100000,z_light=50000;
float x_li_amp=-2,y_li_amp=2,z_li_amp=-2;
float x_li_spe=-2,y_li_spe=2,z_li_spe=-2;
float x_li_dif=-2,y_li_dif=2,z_li_dif=-2;
float x_mat_amb=-2,y_mat_amb=2,z_mat_amb=-2;
float x_mat_dif=-2,y_mat_dif=2,z_mat_dif=-2;
float x_mat_spe=-2,y_mat_spe=2,z_mat_spe=-2;

Camera _camera1,_camera2,_camera3,_camera4;
GLUquadric *quadric ;

float matshine;










  GLfloat light1_ambient[]={ 1000.0f, 200.0f, 150.0f, 1.0f };
  GLfloat light1_diffuse[]= { 0.6f, 0.6f, 0.6f, 1.0f };
  //GLfloat light1_specular[]= { 1.0f, 1.0f, 0.0f, 1.0f };
  GLfloat light1_position[]= { 150000.0f, 100000.0f, 50000.0f, 1.0f };
//  GLfloat spot_direction[] = { 1.0, 1.0, 1.0 };







M3DMatrix44f shadowMat,shadowMat2;
M3DVector4f vPlaneEquation,vPlaneEquation2;









int InitGL(GLvoid)										// All Setup For OpenGL Goes Here
{
	glShadeModel(GL_SMOOTH);							// Enable Smooth Shading
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);				// Black Background
	glClearDepth(1.0f);									// Depth Buffer Setup
	glEnable(GL_DEPTH_TEST);							// Enables Depth Testing
	glDepthFunc(GL_LEQUAL);								// The Type Of Depth Testing To Do
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);	// Really Nice Perspective Calculations	



	loading=LoadTexture("Data\\images\\loading.bmp");
	//stop=LoadTexture("Data\\images\\stop.bmp");/


	terraintexture = LoadTexture("Data\\images\\texture.bmp"); 
	//terraintexture_moon = LoadTexture("Data\\images\\moon.bmp");
	terraintexture_Earth = LoadTexture("Data\\images\\earth.bmp");
    HeightData = new GLubyte(TerrainSize*TerrainSize);
    HeightData = LoadHeightMap("Data\\images\\height.bmp");


	glass=LoadTexture("Data\\images\\glass.bmp",100);


	//glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_REPEAT);
	//glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_REPEAT);

	    quadric = gluNewQuadric();
   
	
//	تهيئة الكاميرات الأربع
     _camera1 = Camera();
	 _camera1.RightVector.x=1200;
	_camera1.Position.x=750;
	_camera1.Position.y=-275;
	_camera1.Position.z=-350;
     _camera1.RotateY(-200.25);


	_camera2 = Camera();
	  _camera2.RotateY(-71.25);
	_camera3 = Camera();
	
	  _camera3.RotateY(-71.25);
	_camera4 = Camera();
	_camera4.Position.y = (float)(GetValue(
		(int)((_camera4.Position.x + initTerrainPositionX) * scaleX),
		(int)((_camera4.Position.z + initTerrainPositionZ) * scaleZ)		
		))
		*scaleY
		+15;
	  _camera4.RotateY(-71.25);
	

	//مرحلة تحميل الصور إلى الذاكرة
    back = LoadTexture("Data\\Images//back.bmp");
	top = LoadTexture("Data\\Images//top.bmp");
	front = LoadTexture("Data\\Images//front.bmp");
	down = LoadTexture("Data\\Images//down.bmp");
	Right = LoadTexture("Data\\Images//right.bmp");
	Left = LoadTexture("Data\\Images//left.bmp");
	//loon=LoadTexture("Data//Images//loon.bmp");
	//loon_bottom=LoadTexture("Data//Images//loon_Bottom.bmp");
	//Space_Box=LoadTexture("Data//Images//spacebox.bmp");
	//earth=LoadTexture("Data//Images//earth.bmp",255);
 //   Out=LoadTexture("Data//Images//Out.bmp");
	//PlaySound(TEXT("Data/Sound/background.wav"),NULL,SND_FILENAME | SND_ALIAS | SND_ASYNC | SND_LOOP);
    gluQuadricTexture(quadric, GL_TRUE);

	glEnable(GL_TEXTURE_2D);
     

	build=LoadTexture("Data\\images\\build.bmp");
	rasif=LoadTexture("Data\\images\\rasif.bmp");
	road=LoadTexture("Data\\images\\Asphalt.bmp");
	ground=LoadTexture("Data\\images\\ground.bmp");
	asphalt=LoadTexture("Data\\images\\Asphalt.bmp");
	green=LoadTexture("Data\\images\\green.bmp");
	brown=LoadTexture("Data\\images\\brown.bmp");
	platform=LoadTexture("Data\\images\\platform.bmp");
	roof=LoadTexture("Data\\images\\roof.bmp");
	grass=LoadTexture("Data\\images\\grass.bmp");
	box_wood=LoadTexture("Data\\images\\Crate.bmp");
	box_metal=LoadTexture("Data\\images\\metal.bmp");
	pelvis=LoadTexture("Data\\images\\pelvis.bmp");
	border=LoadTexture("Data\\images\\border.bmp");





	//Buliding;
	Buliding1=LoadTexture("Data\\images\\Buliding1.bmp");
	Buliding2=LoadTexture("Data\\images\\Buliding2.bmp");
	Buliding3=LoadTexture("Data\\images\\Buliding3.bmp");
	Buliding4=LoadTexture("Data\\images\\Buliding4.bmp");
	Buliding5=LoadTexture("Data\\images\\Buliding5.bmp");
	Buliding6=LoadTexture("Data\\images\\Buliding6.bmp");
	Buliding7=LoadTexture("Data\\images\\Buliding7.bmp");
	Buliding8=LoadTexture("Data\\images\\Buliding8.bmp");
	Buliding9=LoadTexture("Data\\images\\Buliding9.bmp");







	//تحميل صور القاطرة الرئيسية
	main_train_texture_roof=LoadTexture("Data\\images\\main_roof.bmp");
	main_train_texture_front_up=LoadTexture("Data\\images\\train_window.bmp");
	main_train_texture_body=LoadTexture("Data\\images\\body.bmp");
	main_train_texture_front_down=LoadTexture("Data\\images\\train_front.bmp");
    complete=LoadTexture("Data\\images\\train_complete.bmp");
	main_train_texture_cover=LoadTexture("Data\\images\\train_cover.bmp");
	main_train_texture_cover_motor_side=LoadTexture("Data\\images\\train_motor_cover.bmp");
	
	
	wheel=LoadTexture("Data\\images\\wheel.bmp");
	

	train_roof=LoadTexture("Data\\images\\train_roof.bmp");
















	i = LoadTexture("Data\\extra//wood.bmp");
	rightside=new Model_3DS();
	leftside=new Model_3DS();
	top0=new Model_3DS();
	base0=new Model_3DS();
	back1=new Model_3DS();
	back2=new Model_3DS();
	front1=new Model_3DS();
	front2=new Model_3DS();
	tree=new Model_3DS();
	trafic_light=new Model_3DS();
	
	chair=new Model_3DS();
	chair2=new Model_3DS();
	woman1=new Model_3DS();
	woman2=new Model_3DS();
	window=new Model_3DS();
	house=new Model_3DS();
	light=new Model_3DS();


	wheel0=new Model_3DS();
	wheel0->Load("Data\\extra//wheel.3DS");

	car0 = new Model_3DS();
	car0 -> Load("Data\\extra//car.3DS"); 


	top0->Load("Data\\extra//top.3DS");
	rightside->Load("Data\\extra//right.3DS");
	base0->Load("Data\\extra//base.3ds");
	leftside->Load("Data\\extra//left.3DS");
	back1->Load("Data\\extra//back.3ds");
	back2->Load("Data\\extra//back.3ds");
	front1->Load("Data\\extra//back1.3ds");
	front2->Load("Data\\extra//back1.3ds");
	tree->Load("Data\\extra//M_TREE5.3ds");
	chair->Load("Data\\extra//Bench.3DS");
	chair2->Load("Data\\extra//Bench.3DS");
	trafic_light->Load("Data\\extra//traffic_light.3DS");
	woman1->Load("Data\\extra//wwww.3DS");
	woman2->Load("Data\\extra//wwww.3DS");
	window->Load("Data\\extra//win.3DS");
	house->Load("Data\\extra//house.3DS");
	light->Load("Data\\extra//light.3DS");
	GLTexture W,treetex,leaf;
	GLTexture floar;
	GLTexture box,wall,trafic_light_textur;
	GLTexture house0,house1,house2,house3;
	GLTexture tabletex,chair_tex,woman1_tex,woman2_tex,lighttex;
	woman1_tex.LoadBMP("Data\\extra//shaema.bmp");
	woman2_tex.LoadBMP("Data\\extra//woman.bmp");
	box.LoadBMP("Data\\extra//xxx.bmp");
	treetex.LoadBMP("Data\\extra//BARK.bmp");
	leaf.LoadBMP("Data\\extra//Leaf.bmp");
	W.LoadBMP("Data\\extra//wood.bmp");
	floar.LoadBMP("Data\\extra//wood.bmp");
	wall.LoadBMP("Data\\extra//wall1.bmp");
	trafic_light_textur.LoadBMP("Data\\extra//traficlight//svetofor_golova.bmp");
	tabletex.LoadBMP("Data\\extra//table.bmp");
	chair_tex.LoadBMP("Data\\extra//chair.bmp");

	house0.LoadBMP("Data\\extra//house0.bmp");
	house1.LoadBMP("Data\\extra//asph07XL-2.bmp");
	house2.LoadBMP("Data\\extra//AS2_wood_12a.bmp");
	//win.LoadBMP("Data\\extra//AS2_wood_12a.bmp");
	house3.LoadBMP("Data\\extra//dub-svetliy.bmp");

	lighttex.LoadBMP("Data\\extra//light.bmp");







	GLTexture Gray1, Carbon , Gray;
	Carbon.LoadBMP("Data\\extra//Carbon.bmp");
	Gray1.LoadBMP("Data\\extra//Gray1.bmp");
	Gray.LoadBMP("Data\\extra//Gray.bmp");
	wheel0->Materials[0].tex = Carbon;
	wheel0->Materials[1].tex = Carbon;
	wheel0->Materials[2].tex = Gray;
	wheel0->Materials[3].tex = Gray1;

	GLTexture Brown, C ,Green;
	Brown.LoadBMP("Data\\extra//Brown.bmp");
	C.LoadBMP("Data\\extra//Carbon.bmp");
	Green.LoadBMP("Data\\extra//Green.bmp");
	for (int i = 0;i < 139;i++)
		 car0->Materials[i].tex = Brown;
	car0->Materials[139].tex = C;
	car0->Materials[140].tex = C;
	car0->Materials[141].tex = C;
	car0->Materials[142].tex = C;
	car0->Materials[143].tex = C;
	car0->Materials[144].tex = C;
	car0->Materials[145].tex = Green;
	car0->Materials[146].tex = C;






	top0->Materials[0].tex=box;
	
	window->Materials[0].tex=wall;
	chair->Materials[0].tex=chair_tex;
	chair->Materials[1].tex=chair_tex;
	chair2->Materials[0].tex=chair_tex;
	woman1->Materials[0].tex=woman1_tex;
	woman2->Materials[0].tex=woman2_tex;

	

	light->Materials[0].tex=lighttex;
	light->Materials[1].tex=lighttex;
	light->Materials[2].tex=lighttex;

	for (int i = 15; i < 28; i++)
	{
		house->Materials[i].tex=house1;
	}

	for (int i = 0; i < 20; i++)
	{
		house->Materials[i].tex=house0;
	}

	for (int i = 5; i < 15; i++)
	{
		house->Materials[i].tex=house2;
	}

	for (int i = 28; i < 35; i++)
	{
		house->Materials[i].tex=house1;
	}


	for (int i = 1; i < 5; i++)
	{
		//chair->Materials[i].tex=chair_tex;
	}

	//chair->Materials[0].tex=chair_tex;

	for (int i = 0; i < 2; i++)
	{
		rightside->Materials[i].tex=wall;
	}
	for (int i = 0; i < 2; i++)
	{
		leftside->Materials[i].tex=wall;
	}
	trafic_light->Materials[0].tex=trafic_light_textur;

	rightside->Materials[0].tex=wall;
	rightside->Materials[1].tex=wall;
	//leftside->Materials[0].tex=box;
	//leftside->Materials[1].tex=floar;
    back1->Materials[0].tex=floar;
	back2->Materials[0].tex=floar;
	//back->Materials[1].tex=floar;
	base0->Materials[0].tex=floar;
	front1->Materials[0].tex=floar;
	front2->Materials[0].tex=floar;
	tree->Materials[0].tex=treetex;
	tree->Materials[1].tex=leaf;





	





	stop=LoadTGA("Data\\images\\stop.tga");
	my_tree=LoadTGA("Data\\images\\tree.tga");

	
    
	//Lighting with Shadow

	glEnable(GL_LIGHTING);
	glLightfv(GL_LIGHT1,GL_POSITION,light1_position);
	glLightfv(GL_LIGHT1,GL_AMBIENT,light1_ambient);
	glLightfv(GL_LIGHT1,GL_DIFFUSE,light1_diffuse);
	glEnable(GL_LIGHT1);
	
	//calculate Plane Equation
     M3DVector3f point[3]={{-707.738,-385,-803.167},{-807.512,-385,30.4814},{-409.68,-385,107.913}};

	  M3DVector3f point2[3]={{200000.738,-500,-3000.167},{-15000.512,-500,-0.4814},{-200000.68,-500,3000.913}};

	 m3dGetPlaneEquation(vPlaneEquation,point[0],point[1],point[2]);

	 m3dGetPlaneEquation(vPlaneEquation2,point2[0],point2[1],point2[2]);

	 //calculate projection matrix to draw shadow on ground
	 m3dMakePlanarShadowMatrix(shadowMat,vPlaneEquation,light1_position);

	 m3dMakePlanarShadowMatrix(shadowMat2,vPlaneEquation2,light1_position);

	return true;										// Initialization Went OK
}


void drawtreemodel(double tx,double y,double z,double scale)
{
	tree->pos.z=z+110;
	tree->pos.x=tx-10;
	tree->pos.y=y+25;
	tree->rot.y=180;
	tree->scale=scale;
	tree->Draw();
}
	


void drawTrain(double tx,double y,double z,double scale)
{
	//glRotated(90,0,0,1);
	//glColor3d(.5,0.0,0.5);
	//سقف المقطورة
	glPushMatrix();
	top0->pos.z=z-40;
	top0->pos.y=y-1.3;
	top0->pos.x=tx;
	//top0->rot.y=90;
	//top0->rot.y=90;
	top0->scale=scale*1.5;
	top0->Draw();

	//r0ight
	//الجدار اليميني للمقطورة
	//glColor3d(0.5,0.5,0.5);
	rightside->pos.z=z+110;
	rightside->pos.x=tx-10;
	rightside->pos.y=y+25;
	rightside->rot.y=90;
	rightside->scale=3*scale;
	rightside->Draw();
	//glColor3d(1,1,1);
	
	//window
	window->pos.z=z+110;
	window->pos.x=tx+80;
	window->pos.y=y+50;
	window->rot.y=90;
	window->scale=3.0*scale;
	window->Draw();
	//glColor3d(1,1,1);




		






	//glColor3d(1,1,1);

	


	window->pos.z=z+110;
	window->pos.x=tx+255;
	window->pos.y=y+50;
	window->rot.y=90;
	window->scale=3.0*scale;
	window->Draw();
	//glColor3d(1,1,1);

//glColor3d(1,1,1);



	//window
	//glColor3d(0,0,0);
	window->pos.z=z+380;
	window->pos.x=tx+80;
	window->pos.y=y+50;
	window->rot.y=90;
	window->scale=3.0*scale;
	window->Draw();
	//glColor3d(1,1,1);
//dfcvdefvc
	//glColor3d(0.5,0.5,0.5);

	//window2
	window->pos.z=z+380;
	window->pos.x=tx+255;
	window->pos.y=y+50;
	window->rot.y=90;
	window->scale=3.0*scale;
	window->Draw();
	//glColor3d(1,1,1);


	//glColor3d(1,0,0);
	chair->pos.z=z+20;
	chair->pos.x=tx-210;
	chair->pos.y=y-120;
	chair->rot.y=-30;

	chair->scale=0.006*scale;
	chair->Draw();
//	glColor3d(1,1,1);
	//chair2
	chair->pos.z=z+20;
	chair->pos.x=tx-130;
	chair->pos.y=y-120;
	chair->rot.y=-30;
	chair->scale=0.006*scale;
	chair->Draw();


	chair->pos.z=z+20;
	chair->pos.x=tx-60;
	chair->pos.y=y-120;
	chair->rot.y=-30;
	chair->scale=0.006*scale;
	chair->Draw();


	//chair

//	glColor3d(1,1,1);

	chair2->pos.z=z-100;
	chair2->pos.x=tx+70;
	chair2->pos.y=y-120;
	chair2->rot.y=150;
	chair2->scale=0.006*scale;
	chair2->Draw();
	//glColor3d(1,1,1);


	//woman1->pos.z=z-50;
	//woman1->pos.x=tx-140;
	//woman1->pos.y=y-100;
	//woman1->rot.y=-90;

	//woman1->scale=0.025*scale;
	//woman1->Draw();


	woman1->pos.z=z-50;
	woman1->pos.x=tx-160;
	woman1->pos.y=y-125;
	woman1->rot.y=-90;

	woman1->scale=0.025*scale;
	woman1->Draw();



	//woman2
	woman2->pos.z=z-20;
	woman2->pos.x=tx-10;
	woman2->pos.y=y-125;
	woman2->rot.y=-90;

	woman2->scale=0.025*scale;
	woman2->Draw();


	//left
	//glColor3d(0.5,0.5,0.5);
	leftside->pos.z=z-150;
	leftside->pos.x=tx-10;
	leftside->pos.y=y+25;
	leftside->rot.y=90;
	leftside->scale=3*scale;
	leftside->Draw();
	//glColor3d(1,1,1);

	//back1
	//glColor3d(0.5,0.5,1.0);
	back1->pos.z=z-44;
	back1->pos.x=tx-210;
	back1->pos.y=y-15;
	back1->rot.x=90;
	back1->scale=1.9*scale;
	back1->Draw();
	//glColor3d(1,1,1);

    //back2
	//glColor3d(0.5,0.5,1.0);
	back2->pos.z=z+70;
	back2->pos.x=tx-210;
	back2->pos.y=y-15;
	back2->rot.x=90;
	back2->scale=1.9*scale;
	back2->Draw();
	//glColor3d(1,1,1);

	//front1
	//glColor3d(0.5,0.5,1.0);
	front1->pos.z=z-44;
	front1->pos.x=tx+170;
	front1->pos.y=y-15;
	front1->rot.x=90;
	front1->scale=1.9*scale;
	front1->Draw();
	//glColor3d(1,1,1);

	 //front2
	//glColor3d(0.5,0.5,1.0);
	front2->pos.z=z+70;
	front2->pos.x=tx+170;
	front2->pos.y=y-15;
	front2->rot.x=90;
	front2->scale=1.9*scale;
	front2->Draw();
	//glColor3d(1,1,1);

	//base
	//glColor3d(0.5,0.2,0.0);
	base0->pos.y=y-120;
	base0->pos.z=z+30;
	base0->pos.x=tx-85;
	base0->rot.z=90;
	base0->rot.y=90;
	base0->scale=4.2*scale;
	base0->Draw();




	//light
	light->pos.z=z-20;
	light->pos.y=y+100;
	light->pos.x=tx;
	//top0->rot.y=90;
	//top0->rot.y=90;
	light->scale=scale*3;
	light->Draw();
	

	glPopMatrix();

	////draw window
	////glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
	////glEnable(GL_BLEND);
	//glPushMatrix();
	//glBegin(GL_QUADS);
	//glColor4d(0.5,0.5,0.5,0.5);
	//glVertex3d(x-2.0,y+1.0,z-1);
	//glColor4d(0.5,0.5,0.5,0.5);
	//glVertex3d(x-2.0,y+1.0,z-4.0);
	//glColor4d(0.5,0.5,0.5,0.5);
	//glVertex3d(x-2.0,y-1,z+0.5);
	//glColor4d(0.5,0.5,0.5,0.5);
	//glVertex3d(x-2.0,y-1,z-1);
	////glDisable(GL_BLEND);
	//
	//glEnd();
	//glPopMatrix();



}


void drawcottage(double tx,double y,double z,double scale , double rot)
{
	house->pos.z=z+110;
	house->pos.x=tx-10;
	house->pos.y=y+25;
	house->rot.y=rot;
	house->scale=scale;
	house->Draw();
}




void drawcar(double x,double y,double z,double sca,double rot)
{
	glPushMatrix();
	glTranslated(-25,0,0);
	 
	// رسم العجلة الأمامية اليمينية
	glPushMatrix();

	wheel0 -> pos.x = x+80;
	wheel0 -> pos.y = y-40;
	wheel0 -> pos.z = z;
	wheel0->rot.y=rot;
	wheel0->scale = 0.15f;

	wheel0->Draw();
	glPopMatrix();
	/////////////////////////////////////////////////////

	////////////////////////////////////////////////////
	// رسم العجلة الأمامية اليسرى
	glPushMatrix();
	
	wheel0 -> pos.x = x-70;
	wheel0 -> pos.y = y-40;
	wheel0 -> pos.z = z;
	wheel0 -> rot.y = rot;

	wheel0->scale = 0.15f;
	
	wheel0->Draw();
	glPopMatrix();
	///////////////////////////////////////////////////
	
	//////////////////////////////////////////////////
	// رسم العجلة الخلفية اليمينية
	glPushMatrix();
	wheel0 -> pos.x = x+80;
	wheel0 -> pos.y = y-40;
	wheel0 -> pos.z = z+280;
	wheel0->rot.y=rot;
	wheel0->scale = 0.15f;

	wheel0->Draw();
	glPopMatrix();
	///////////////////////////////////////////////////
	// رسم العجلة الخلفية اليسرى 
	glPushMatrix();

	wheel0 -> pos.x = x-70;
	wheel0 -> pos.y = y-40;
	wheel0 -> pos.z = z+280;
	wheel0 -> rot.y = rot;
	wheel0->scale = 0.15f;

	wheel0->Draw();
	glPopMatrix();


	glPopMatrix();

	/////////////////////////////////////////////////////
	
	
	///////////////////////////////////////////////////
	// رسم السيارة
	glPushMatrix();
	//car0->pos.x = x+250;
	//car0->pos.y = y+100;
	//car0->pos.z = z;
	//car0->rot.y=180;
	//car0->scale = 0.8f;
	//car0->Draw();

		car0->pos.x = x;
	car0->pos.y = y;
	car0->pos.z = z;
	car0->rot.y=rot;
	car0->scale = 0.8f;
	car0->Draw();

	glPopMatrix();

}




bool Collision_Detection(){

	if(_camera1.Position.x<=49840.4  && _camera1.Position.z<=400.781 &&  _camera1.Position.z>=-480.781)
	      return true;
	else
		return false;	
}




  /*GLfloat MatAmb[] = { 1.0f, 1.0f, 1.0f,1.0f };
  GLfloat MatDif[] = { 1.0f, 1.0f, 0.0f,1.0f };
  GLfloat MatSpe[] = { 1.0f, 1.0f, 0.0f,1.0f };
  GLfloat MatShn[] = { 50.0f};
*/


  GLfloat light2_ambient[]={ 1.0f, 1.0f, 1.0f, 1.0f };
  GLfloat light2_diffuse[]= { 1.0f, 1.0f, 0.0f, 1.0f };
  //GLfloat light2_specular[]= { 0.0f, 0.0f, 0.0f, 1.0f };
  GLfloat light2_position[]= { 0.0f, 0.0f, 0.0f, 1.0f };
//  GLfloat spot_direction[] = { 1.0, 1.0, 1.0 };

  GLfloat MatAmb2[] = { 1.0f, 1.0f, 1.0f,1.0f };
  GLfloat MatDif2[] = { 1.0f, 1.0f, 0.0f,1.0f };
  //GLfloat MatSpe2[] = { 0.0f, 0.0f, 0.0f,10.0f };
  GLfloat MatShn2[] = { 50.0f};

  int s=100,t=1;


  void Draw_Building(float x, float y, float z, float width, float height, float length,int FRONT,int BACK,int LEFT,int RIGHT,int UP,int DOWN)
{

	glPushMatrix();

	glTranslated(100000,0,1500);

	glRotated(2,0,1,0);
	// Center the Building .....  the given x,y,z position
	x = x - width  / 2;
	y = y - height / 2;
	z = z - length / 2;
	
	// Draw Front side
	glBindTexture(GL_TEXTURE_2D, FRONT);	
	glBegin(GL_QUADS);	
		glTexCoord2f(1.0f, 0.0f); glVertex3f(x,		  y,		z+length);
		glTexCoord2f(1.0f, 1.0f); glVertex3f(x,		  y+height, z+length);
		glTexCoord2f(0.0f, 1.0f); glVertex3f(x+width, y+height, z+length); 
		glTexCoord2f(0.0f, 0.0f); glVertex3f(x+width, y,		z+length);
	glEnd();

	// Draw Back side
	glBindTexture(GL_TEXTURE_2D,BACK);
	glBegin(GL_QUADS);		
		glTexCoord2f(1.0f, 0.0f); glVertex3f(x+width, y,		z);
		glTexCoord2f(1.0f, 1.0f); glVertex3f(x+width, y+height, z); 
		glTexCoord2f(0.0f, 1.0f); glVertex3f(x,		  y+height,	z);
		glTexCoord2f(0.0f, 0.0f); glVertex3f(x,		  y,		z);
	glEnd();

	// Draw Left side
	glBindTexture(GL_TEXTURE_2D, LEFT);
	glBegin(GL_QUADS);		
		glTexCoord2f(1.0f, 1.0f); glVertex3f(x,		  y+height,	z);	
		glTexCoord2f(0.0f, 1.0f); glVertex3f(x,		  y+height,	z+length); 
		glTexCoord2f(0.0f, 0.0f); glVertex3f(x,		  y,		z+length);
		glTexCoord2f(1.0f, 0.0f); glVertex3f(x,		  y,		z);		
	glEnd();

	// Draw Right side
	glBindTexture(GL_TEXTURE_2D, RIGHT);
	glBegin(GL_QUADS);		
		glTexCoord2f(0.0f, 0.0f); glVertex3f(x+width, y,		z);
		glTexCoord2f(1.0f, 0.0f); glVertex3f(x+width, y,		z+length);
		glTexCoord2f(1.0f, 1.0f); glVertex3f(x+width, y+height,	z+length); 
		glTexCoord2f(0.0f, 1.0f); glVertex3f(x+width, y+height,	z);
	glEnd();

	// Draw Up side
	glBindTexture(GL_TEXTURE_2D, UP);
	glBegin(GL_QUADS);		
		glTexCoord2f(0.0f, 0.0f); glVertex3f(x+width, y+height, z);
		glTexCoord2f(1.0f, 0.0f); glVertex3f(x+width, y+height, z+length); 
		glTexCoord2f(1.0f, 1.0f); glVertex3f(x,		  y+height,	z+length);
		glTexCoord2f(0.0f, 1.0f); glVertex3f(x,		  y+height,	z);
	glEnd();

	// Draw Down side
	glBindTexture(GL_TEXTURE_2D, DOWN);
	glBegin(GL_QUADS);		
		glTexCoord2f(0.0f, 0.0f); glVertex3f(x,		  y,		z);
		glTexCoord2f(1.0f, 0.0f); glVertex3f(x,		  y,		z+length);
		glTexCoord2f(1.0f, 1.0f); glVertex3f(x+width, y,		z+length); 
		glTexCoord2f(0.0f, 1.0f); glVertex3f(x+width, y,		z);
	glEnd();
	glPopMatrix();
	

}

//تم وضع الطريق لوحده لسهولة التعامل مع الظل
void Draw_road(){
	glPushMatrix();
	 glScaled(100000,800,1000);

	 //الأرضية
	glPushMatrix();
	   //   glScaled(100000000000000,100000000000000,100000000000000);
	glTranslatef(0,-0.5,0);
		glRotatef(-90,1,0,0);
		//glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
    glBindTexture(GL_TEXTURE_2D,platform); 
    glBegin(GL_QUADS);
	glTexCoord2d(0,0); glVertex3d(-0.5,-0.5,0);
	glTexCoord2d(s,0);	 glVertex3d(0.5,-0.5,0);
	glTexCoord2d(s,t);	glVertex3d(0.5,0.5,0);
	glTexCoord2d(0,t);	glVertex3d(-0.5,0.5,0);
	glEnd();
	glPopMatrix();



		//reasif
	
	glPushMatrix();
	   //   glScaled(100000000000000,100000000000000,100000000000000);
	//glScaled(1000,0,0);
	glTranslatef(1,-0.6,0);
		glRotatef(-90,1,0,0);
		//glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
    glBindTexture(GL_TEXTURE_2D,rasif); 
    glBegin(GL_QUADS);
	glTexCoord2d(0,0); glVertex3d(-1,-1,0);
	glTexCoord2d(s,0);	 glVertex3d(1,-1,0);
	glTexCoord2d(s,t);	glVertex3d(1,1,0);
	glTexCoord2d(0,t);	glVertex3d(-1,1,0);
	glEnd();
	glPopMatrix();



	//grass
	glPushMatrix();
	   //   glScaled(100000000000000,100000000000000,100000000000000);
	//glScaled(1,1,1);
	glTranslatef(1,-0.7,0);
		glRotatef(-90,1,0,0);
		//glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
		glBindTexture(GL_TEXTURE_2D,grass); 
    glBegin(GL_QUADS);
	glTexCoord2d(0,0); glVertex3d(-2,-2,0);
	glTexCoord2d(s,0);	 glVertex3d(2,-2,0);
	glTexCoord2d(s,t);	glVertex3d(2,2,0);
	glTexCoord2d(0,t);	glVertex3d(-2,2,0);
	glEnd();
	glPopMatrix();



glPopMatrix();

		//الطريق
	glPushMatrix();
	   //glScaled(100000000000,100000000,1000000000);
	glScaled(300000,800,500);
	//glDisable(GL_DEPTH_TEST);
	glTranslatef(0,-0.49,0);
		glRotatef(-90,1,0,0);
	//	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
    glBindTexture(GL_TEXTURE_2D,asphalt); 
    glBegin(GL_QUADS);
	glTexCoord2d(0,0); glVertex3d(-0.5,-0.5,0);
	glTexCoord2d(100,0);	 glVertex3d(0.5,-0.5,0);
	glTexCoord2d(100,1);	glVertex3d(0.5,0.5,0);
	glTexCoord2d(0,1);	glVertex3d(-0.5,0.5,0);
	glEnd();
	//glEnable(GL_DEPTH_TEST);
	glPopMatrix();


}


void DrawEarth(){

	glPushMatrix();
	     // glScaled(10000000000000000,10000000000000000,10000000000000000);
	   //glScaled(100000000000,100000000,1000000000);YES
	   glScaled(100000,800,1000);

	
	//الشارع

	//glPushMatrix();
	//   //   glScaled(100000000000000,100000000000000,100000000000000);
	////glScaled(1000,0,0);
	//glTranslatef(1,-0.51,0);
	//	glRotatef(-90,1,0,0);
	//	//glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
 //   glBindTexture(GL_TEXTURE_2D,road); 
 //   glBegin(GL_QUADS);
	//glTexCoord2d(0,0); glVertex3d(-0.5,-0.5,0);
	//glTexCoord2d(s,0);	 glVertex3d(0.5,-0.5,0);
	//glTexCoord2d(s,t);	glVertex3d(0.5,0.5,0);
	//glTexCoord2d(0,t);	glVertex3d(-0.5,0.5,0);
	//glEnd();
	//glPopMatrix();



		//85454
	//dfv
   //الحيط اليساري
	glPushMatrix();
//	glScaled(100000000000000,100000000000000,100000000000000);
	//	glScaled(10,10,10);
	    glTranslatef(0,0,-0.5);
		//glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
    glBindTexture(GL_TEXTURE_2D,ground); 
    glBegin(GL_QUADS);
	glTexCoord2d(0,0); glVertex3d(-0.5,-0.5,0);
	glTexCoord2d(s,0);	 glVertex3d(0.5,-0.5,0);
	glTexCoord2d(s,t);	glVertex3d(0.5,0.5,0);
	glTexCoord2d(0,t);	glVertex3d(-0.5,0.5,0);
	glEnd();
	glPopMatrix();


    //الحيط الخلفي
	glPushMatrix();
	//glScaled(100000000000000,100000000000000,100000000000000);
	glTranslatef(-0.5,0,0);
		glRotatef(-90,0,1,0);
		//glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
    glBindTexture(GL_TEXTURE_2D,ground); 
    glBegin(GL_QUADS);
	glTexCoord2d(0,0); glVertex3d(-0.5,-0.5,0);
	glTexCoord2d(1,0);	 glVertex3d(0.5,-0.5,0);
	glTexCoord2d(1,1);	glVertex3d(0.5,0.5,0);
	glTexCoord2d(0,1);	glVertex3d(-0.5,0.5,0);
	glEnd();
	glPopMatrix();


    //الحيط اليميني
	//glPushMatrix();
	////glScaled(100000000000000,100000000000000,100000000000000);
	//glTranslatef(0.5,0,0);
	//	glRotatef(90,0,1,0);
	//	//glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
 //   glBindTexture(GL_TEXTURE_2D,ground); 
 //   glBegin(GL_QUADS);
	//glTexCoord2d(0,0); glVertex3d(-0.5,-0.5,0);
	//glTexCoord2d(1,0);	 glVertex3d(0.5,-0.5,0);
	//glTexCoord2d(1,1);	glVertex3d(0.5,0.5,0);
	//glTexCoord2d(0,1);	glVertex3d(-0.5,0.5,0);
	//glEnd();
	//glPopMatrix();


    //السقف
	glPushMatrix();
	//glScaled(100000000000000,100000000000000,100000000000000);
	glTranslatef(0,0.5,0);
		glRotatef(-90,1,0,0);
		//glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
		glBindTexture(GL_TEXTURE_2D,roof); 
    glBegin(GL_QUADS);
	glTexCoord2d(0,0); glVertex3d(-0.5,-0.5,0);
	glTexCoord2d(s,0);	 glVertex3d(0.5,-0.5,0);
	glTexCoord2d(s,t);	glVertex3d(0.5,0.5,0);
	glTexCoord2d(0,t);	glVertex3d(-0.5,0.5,0);
	glEnd();
	glPopMatrix();




	 //الحيط اليميني
	glPushMatrix();
	//glScaled(100000000000000,100000000000000,100000000000000);
	glTranslatef(0,0,0.5);
	//glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
    glBindTexture(GL_TEXTURE_2D,ground); 
    glBegin(GL_QUADS);
	glTexCoord2d(0,0); glVertex3d(-0.5,-0.5,0);
	glTexCoord2d(s,0);	 glVertex3d(0.5,-0.5,0);
	glTexCoord2d(s,t);	glVertex3d(0.5,0.5,0);
	glTexCoord2d(0,t);	glVertex3d(-0.5,0.5,0);
	glEnd();
	glPopMatrix();

	


	glPopMatrix();




	

	////الرصيف اليميني
	//glPushMatrix();
	//      glScaled(100000,802,200);
	//glTranslatef(0,-0.45,2);
	//	glRotatef(-90,1,0,0);
 //   glBindTexture(GL_TEXTURE_2D,platform); 
 //   glBegin(GL_QUADS);
	//glTexCoord2d(0,0); glVertex3d(-0.5,-0.5,0);
	//glTexCoord2d(s,0);	 glVertex3d(0.5,-0.5,0);
	//glTexCoord2d(s,t);	glVertex3d(0.5,0.5,0);
	//glTexCoord2d(0,t);	glVertex3d(-0.5,0.5,0);
	//glEnd();
	//glPopMatrix();


}




void DrawSkyBox(float size)
	{
	glPushMatrix();
	glEnable(GL_TEXTURE_2D);
	glScalef(size,size,size);
	glBindTexture(GL_TEXTURE_2D,front);
	glBegin(GL_QUADS);

	//front
	glTexCoord2f(1,0) ; 		glVertex3f(0.5,-0.5,0.5); 
	glTexCoord2f(1,1) ;			glVertex3f(0.5,0.5,0.5);
	glTexCoord2f(0,1) ;			glVertex3f(-0.5,0.5,0.5);
	glTexCoord2f(0,0) ;			glVertex3f(-0.5,-0.5,0.5);
	glEnd();
	glBindTexture(GL_TEXTURE_2D,back);
	glBegin(GL_QUADS);
	//back
	glTexCoord2f(0,0) ;		glVertex3f(0.5,-0.5,-0.5);
	glTexCoord2f(0,1) ;		glVertex3f(0.5,0.5,-0.5);
	glTexCoord2f(1,1) ;		glVertex3f(-0.5,0.5,-0.5);
	glTexCoord2f(1,0) ;		glVertex3f(-0.5,-0.5,-0.5);
	glEnd();
	glBindTexture(GL_TEXTURE_2D,Right);
	glBegin(GL_QUADS);
	//right
	glTexCoord2f(1,0) ;		glVertex3f(0.5,-0.5,-0.5);
	glTexCoord2f(1,1) ;		glVertex3f(0.5,0.5,-0.5);
	glTexCoord2f(0,1) ;		glVertex3f(0.5,0.5,0.5);
	glTexCoord2f(0,0) ;		glVertex3f(0.5,-0.5,0.5);
	glEnd();
	glBindTexture(GL_TEXTURE_2D,Left);
	glBegin(GL_QUADS);
	//left
	glTexCoord2f(1,0) ;		glVertex3f(-0.5,-0.5,0.5);
	glTexCoord2f(1,1) ;		glVertex3f(-0.5,0.5,0.5);
	glTexCoord2f(0,1) ;		glVertex3f(-0.5,0.5,-0.5);
	glTexCoord2f(0,0) ;		glVertex3f(-0.5,-0.5,-0.5);
	glEnd();
	glBindTexture(GL_TEXTURE_2D,top);
	glBegin(GL_QUADS);
	//up
	glTexCoord2f(1,0) ;		glVertex3f(0.5,0.5,0.5);
	glTexCoord2f(1,1) ;		glVertex3f(0.5,0.5,-0.5);
	glTexCoord2f(0,1) ;		glVertex3f(-0.5,0.5,-0.5);
	glTexCoord2f(0,0) ;		glVertex3f(-0.5,0.5,0.5);
	glEnd();
	glBindTexture(GL_TEXTURE_2D,down);
	glBegin(GL_QUADS);
	//down
	glTexCoord2f(1,0) ;		glVertex3f(0.5,-0.5,-0.5);
	glTexCoord2f(1,1) ;		glVertex3f(0.5,-0.5,0.5);
	glTexCoord2f(0,1) ;		glVertex3f(-0.5,-0.5,0.5);
	glTexCoord2f(0,0) ;		glVertex3f(-0.5,-0.5,-0.5);

	glEnd();
	glDisable(GL_TEXTURE_2D);
	glPopMatrix();
}









void Draw_Tree(float angle,float x,float y,float z){
 glPushMatrix();	
glTranslatef(x,y,z);
glScaled(20,20,20);


	glPushMatrix();
	//
	 glRotatef(angle,0,1,0);
		//glColor3f(0,1,0);
	 //glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
	 glBindTexture(GL_TEXTURE_2D,green);
		glBegin(GL_TRIANGLES);
		glTexCoord2d(0,0);	glVertex3d(-5,0,0);
		glTexCoord2d(1,0);	glVertex3d(5,0,0);
		glTexCoord2d(0.5,1);	glVertex3d(0,5,0);
		glEnd();
	glPopMatrix();

	glPushMatrix();
	glRotatef(angle,0,1,0);
		//glColor3f(0,1,0);
	//glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
	glBindTexture(GL_TEXTURE_2D,green);
		glBegin(GL_QUADS);
			glTexCoord2d(0,0); glVertex3d(-5,0,0);
			glTexCoord2d(1,0); glVertex3d(-5,-1,0);
			glTexCoord2d(1,1); glVertex3d(5,-1,0);
			glTexCoord2d(0,1); glVertex3d(5,0,0);
		glEnd();
	glPopMatrix();
	    
 	glPushMatrix();
	glRotatef(angle,0,1,0);
		//glColor3f(0,1,0);
	//glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
	glBindTexture(GL_TEXTURE_2D,green);
		glBegin(GL_QUADS);
	      glTexCoord2d(0,0);   glVertex3d(-3,-1,0);
		  glTexCoord2d(1,0); glVertex3d(-3,-4,0);
			glTexCoord2d(1,1); glVertex3d(3,-4,0);
			glTexCoord2d(0,1); glVertex3d(3,-1,0);
		glEnd();
	glPopMatrix();

	glPushMatrix();
	glRotatef(angle,0,1,0);
		//glColor3f(0,1,0);
	//glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
	glBindTexture(GL_TEXTURE_2D,green);
		glBegin(GL_QUADS);
			glTexCoord2d(0,0); glVertex3d(-5,-4,0);
			glTexCoord2d(1,0); glVertex3d(-5,-5,0);
			glTexCoord2d(1,1); glVertex3d(5,-5,0);
			glTexCoord2d(0,1); glVertex3d(5,-4,0);
		glEnd();
	glPopMatrix();

	//الساق
	glPushMatrix();
	//glScaled(10,10,10);
	glRotatef(angle,0,1,0);
	
		//glColor3f(0.7,0.3,0);
//	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
	glBindTexture(GL_TEXTURE_2D,brown);
		 glBegin(GL_QUADS);
		 glTexCoord2d(0,0); glVertex3d(-1,-5,0);
		glTexCoord2d(1,0);	glVertex3d(-1,-15,0);
 		glTexCoord2d(1,1);	glVertex3d(1,-15,0);
		glTexCoord2d(0,1);	glVertex3d(1,-5,0);
		glEnd();
	glPopMatrix(); 

	//ثمار
	/*glPushMatrix();
	     glColor3f(1,1,0);
		 glTranslatef(0,0,-5);
		 auxSolidSphere(2);
	glPopMatrix();*/
	//glColor3f(0,0,0);


glPopMatrix();
}


void DrawBox(float x_scale,float y_scale,float z_scale,float x_translate,float y_translate,float z_translate,int texture_id){

	glPushMatrix();
	glScalef(x_scale,y_scale,z_scale);
	glTranslatef(x_translate,y_translate,z_translate);

    //الوجه السفلي
   glPushMatrix();
	   glTranslatef(0,-0.5,0);
	   glRotatef(90,1,0,0);
	   glBindTexture(GL_TEXTURE_2D,texture_id);
	 glBegin(GL_QUADS);
	   glTexCoord2d(0,0);  glVertex3d(-0.5,-0.5,0);
	   glTexCoord2d(1,0);  glVertex3d(0.5,-0.5,0);
	   glTexCoord2d(1,1);  glVertex3d(0.5,0.5,0);
	   glTexCoord2d(0,1);  glVertex3d(-0.5,0.5,0);
	 glEnd();
   glPopMatrix();

    //الوجه الصدراني
   glPushMatrix();
	   glTranslatef(0,0,-0.5);
	   //glRotatef();
	   glBindTexture(GL_TEXTURE_2D,texture_id);
	 glBegin(GL_QUADS);
	   glTexCoord2d(0,0);  glVertex3d(-0.5,-0.5,0);
	   glTexCoord2d(1,0);  glVertex3d(0.5,-0.5,0);
	   glTexCoord2d(1,1);  glVertex3d(0.5,0.5,0);
	   glTexCoord2d(0,1);  glVertex3d(-0.5,0.5,0);
	glEnd();
   glPopMatrix();


   //الوجه اليساري
   glPushMatrix();
	   glTranslatef(-0.5,0,0);
	   glRotatef(90,0,1,0);
	   glBindTexture(GL_TEXTURE_2D,texture_id);
	 glBegin(GL_QUADS);
	glTexCoord2d(0,0);  glVertex3d(-0.5,-0.5,0);
	   glTexCoord2d(1,0);  glVertex3d(0.5,-0.5,0);
	   glTexCoord2d(1,1);  glVertex3d(0.5,0.5,0);
	   glTexCoord2d(0,1);  glVertex3d(-0.5,0.5,0);
	 glEnd();
   glPopMatrix();


   //الوجه اليميني
   glPushMatrix();
	   glTranslatef(0.5,0,0);
	   glRotatef(90,0,1,0);
	   glBindTexture(GL_TEXTURE_2D,texture_id);
	 glBegin(GL_QUADS);
	   glTexCoord2d(0,0);  glVertex3d(-0.5,-0.5,0);
	   glTexCoord2d(1,0);  glVertex3d(0.5,-0.5,0);
	   glTexCoord2d(1,1);  glVertex3d(0.5,0.5,0);
	   glTexCoord2d(0,1);  glVertex3d(-0.5,0.5,0);
	 glEnd();
   glPopMatrix();

  
   //الوجه العلوي
   glPushMatrix();
	   glTranslatef(0,0.5,0);
	   glRotatef(90,1,0,0);
	   glBindTexture(GL_TEXTURE_2D,texture_id);
	 glBegin(GL_QUADS);
	   glTexCoord2d(0,0);  glVertex3d(-0.5,-0.5,0);
	   glTexCoord2d(1,0);  glVertex3d(0.5,-0.5,0);
	   glTexCoord2d(1,1);  glVertex3d(0.5,0.5,0);
	   glTexCoord2d(0,1);  glVertex3d(-0.5,0.5,0);
	 glEnd();
   glPopMatrix();

    //الوجه الأمامي
   glPushMatrix();
	   glTranslatef(0,0,0.5);
	   //glRotatef();
	   glBindTexture(GL_TEXTURE_2D,texture_id);
	 glBegin(GL_QUADS);
	 glTexCoord2d(0,0);  glVertex3d(-0.5,-0.5,0);
	   glTexCoord2d(1,0);  glVertex3d(0.5,-0.5,0);
	   glTexCoord2d(1,1);  glVertex3d(0.5,0.5,0);
	   glTexCoord2d(0,1);  glVertex3d(-0.5,0.5,0);
	 glEnd();
   glPopMatrix();


	glPopMatrix();
}

void Draw_pelvis(float x_scale,float y_scale,float z_scale,float x_translate,float y_translate,float z_translate,int inner_texture_id,int outter_texture_id,int border_texture_id){

glPushMatrix();
    
    //الإطار الأمامي
//	DrawBox(x_scale,1,1,x_translate,y_translate,z_translate,border_texture_id);
	//الإطار اليساري
//	DrawBox(1,y_scale,1,x_translate,y_translate,z_translate,border_texture_id);
	//الإطار اليميني
//	DrawBox(1,y_scale,1,x_translate,y_translate,z_translate,border_texture_id);


	glScalef(x_scale,y_scale,z_scale);
	glTranslatef(x_translate,y_translate,z_translate);

    
  


    //الوجه السفلي
   glPushMatrix();
	   glTranslatef(0,-0.5,0);
	   glRotatef(90,1,0,0);
	   glBindTexture(GL_TEXTURE_2D,outter_texture_id);
	 glBegin(GL_QUADS);
	   glTexCoord2d(0,0);  glVertex3d(-0.5,-0.5,0);
	   glTexCoord2d(3,0);  glVertex3d(0.5,-0.5,0);
	   glTexCoord2d(3,1);  glVertex3d(0.5,0.5,0);
	   glTexCoord2d(0,1);  glVertex3d(-0.5,0.5,0);
	 glEnd();
   glPopMatrix();

    //الوجه اليميني
   glPushMatrix();
	   glTranslatef(0,0,-0.5);
	   //glRotatef();
	   glBindTexture(GL_TEXTURE_2D,border);
	 glBegin(GL_QUADS);
	   glTexCoord2d(0,0);  glVertex3d(-0.5,-0.5,0);
	   glTexCoord2d(3,0);  glVertex3d(0.5,-0.5,0);
	   glTexCoord2d(3,1);  glVertex3d(0.5,0.5,0);
	   glTexCoord2d(0,1);  glVertex3d(-0.5,0.5,0);
	glEnd();
   glPopMatrix();


   //الوجه اليساري
   glPushMatrix();
	   glTranslatef(-0.5,0,0);
	   glRotatef(90,0,1,0);
	   glBindTexture(GL_TEXTURE_2D,border);
	 glBegin(GL_QUADS);
	glTexCoord2d(0,0);  glVertex3d(-0.5,-0.5,0);
	   glTexCoord2d(3,0);  glVertex3d(0.5,-0.5,0);
	   glTexCoord2d(3,1);  glVertex3d(0.5,0.5,0);
	   glTexCoord2d(0,1);  glVertex3d(-0.5,0.5,0);
	 glEnd();
   glPopMatrix();


   //الوجه اليميني
   glPushMatrix();
	   glTranslatef(0.5,0,0);
	   glRotatef(90,0,1,0);
	   glBindTexture(GL_TEXTURE_2D,border);
	 glBegin(GL_QUADS);
	   glTexCoord2d(0,0);  glVertex3d(-0.5,-0.5,0);
	   glTexCoord2d(3,0);  glVertex3d(0.5,-0.5,0);
	   glTexCoord2d(3,1);  glVertex3d(0.5,0.5,0);
	   glTexCoord2d(0,1);  glVertex3d(-0.5,0.5,0);
	 glEnd();
   glPopMatrix();

  
   //الوجه العلوي
   glPushMatrix();
	   glTranslatef(0.0f,0.4f,0.0f);
	   glRotatef(90,1,0,0);
	   glBindTexture(GL_TEXTURE_2D,inner_texture_id);
	 glBegin(GL_QUADS);
	   glTexCoord2d(0,0);  glVertex3d(-0.5,-0.5,0);
	   glTexCoord2d(3,0);  glVertex3d(0.5,-0.5,0);
	   glTexCoord2d(3,1);  glVertex3d(0.5,0.5,0);
	   glTexCoord2d(0,1);  glVertex3d(-0.5,0.5,0);
	 glEnd();
   glPopMatrix();

    //الوجه الأمامي
   glPushMatrix();
	   glTranslatef(0,0,0.5);
	   //glRotatef();
	   glBindTexture(GL_TEXTURE_2D,border);
	 glBegin(GL_QUADS);
	 glTexCoord2d(0,0);  glVertex3d(-0.5,-0.5,0);
	   glTexCoord2d(3,0);  glVertex3d(0.5,-0.5,0);
	   glTexCoord2d(3,1);  glVertex3d(0.5,0.5,0);
	   glTexCoord2d(0,1);  glVertex3d(-0.5,0.5,0);
	 glEnd();
   glPopMatrix();


	glPopMatrix();


}



void Number_of_Tree(){
	if(((_camera1.Position.x<20000 && (_camera1.View.x>0.89348 || _camera1.View.x>0.5)) || (_camera1.Position.x>20000 && (_camera1.View.x<0.89348 || _camera1.View.x<0.5))  || (_camera1.Position.x<20000 && _camera1.Position.x>19460)) &&  (_camera1.Position.x>-50000))
			for(float i=0; i<361;i+=10)
				Draw_Tree(i,20000,-100,-350);

	if(((_camera1.Position.x<-20000 && (_camera1.View.x>0.89348 || _camera1.View.x>0.5)) || (_camera1.Position.x>-20000 && (_camera1.View.x<0.89348 || _camera1.View.x<0.5)) || (_camera1.Position.x<-20000 && _camera1.Position.x>-20540)) && (_camera1.Position.x>-50000))
			for(float i=0; i<361;i+=10)
				Draw_Tree(i,-20000,-100,-350);

	if(((_camera1.Position.x<49650 && (_camera1.View.x>0.89348 || _camera1.View.x>0.5)) || (_camera1.Position.x>49650 && (_camera1.View.x<0.89348 || _camera1.View.x<0.5)) || (_camera1.Position.x<49650 && _camera1.Position.x>49110)) && (_camera1.Position.x>-50000))
		for(float i=0; i<361;i+=10)
			Draw_Tree(i,49650,-100,-350);

		if(((_camera1.Position.x<-49650 && (_camera1.View.x>0.89348 || _camera1.View.x>0.5)) || (_camera1.Position.x>-49650 && (_camera1.View.x<0.89348 || _camera1.View.x<0.5)) || (_camera1.Position.x<-49650 && _camera1.Position.x>-50190)) && (_camera1.Position.x>-50000))
			for(float i=0; i<361;i+=10)
				Draw_Tree(i,-49650,-100,-350);



	if(((_camera1.Position.x<-120 && (_camera1.View.x>0.89348 || _camera1.View.x>0.5)) || (_camera1.Position.x>-120 && (_camera1.View.x<0.89348 || _camera1.View.x<0.5)) || (_camera1.Position.x<0 && _camera1.Position.x>-540) ) && (_camera1.Position.x>-50000))
		for(float i=0; i<361;i+=1)
			Draw_Tree(i,0,-100,350);



	if(((_camera1.Position.x<10106 && (_camera1.View.x>0.89348 || _camera1.View.x>0.5)) || (_camera1.Position.x>10106 && (_camera1.View.x<0.89348 || _camera1.View.x<0.5)) || (_camera1.Position.x<10000 && _camera1.Position.x>9460)) && (_camera1.Position.x>-50000))
		for(float i=0; i<361;i+=10)
			Draw_Tree(i,10000,-100,350);

	if(((_camera1.Position.x<-10000 && (_camera1.View.x>0.89348 || _camera1.View.x>0.5)) || (_camera1.Position.x>-10000 && (_camera1.View.x<0.89348 || _camera1.View.x<0.5))  || (_camera1.Position.x<-10000 && _camera1.Position.x>-10540)) && (_camera1.Position.x>-50000))
		for(float i=0; i<361;i+=10)
			Draw_Tree(i,-10000,-100,350);


	if(((_camera1.Position.x<40000 && (_camera1.View.x>0.89348 || _camera1.View.x>0.5)) || (_camera1.Position.x>40000 && (_camera1.View.x<0.89348 || _camera1.View.x<0.5))  || (_camera1.Position.x<40000 && _camera1.Position.x>39460)) && (_camera1.Position.x>-50000))
		for(float i=0; i<361;i+=10)
			Draw_Tree(i,40000,-100,350);

		if(((_camera1.Position.x<-40000 && (_camera1.View.x>0.89348 || _camera1.View.x>0.5)) || (_camera1.Position.x>-40000 && (_camera1.View.x<0.89348 || _camera1.View.x<0.5))  || (_camera1.Position.x<-40000 && _camera1.Position.x>-40540)) && (_camera1.Position.x>-50000))
			for(float i=0; i<361;i+=10)
				Draw_Tree(i,-40000,-100,350);
	


       
	   
}

void number_of__tree2(){

	//رسم الشجرة التانية
			for (int i = 51000; i < 80000; i+=5000)
			{
				drawtreemodel(i,-600,1200,10);

				drawtreemodel(i,-600,-1350,10);

			}

}

void Number_of_Boxes(){


	
DrawBox(504.0f,104.0f,100.0f,0.0f,-3.3f,-4.3f,box_wood);
DrawBox(104.0f,104.0f,100.0f,0.0f,-2.3f,-4.3f,box_metal);	

DrawBox(504.0f,104.0f,100.0f,10.0f,-3.3f,-4.3f,box_wood);
DrawBox(104.0f,104.0f,100.0f,48.0f,-2.3f,-4.3f,box_metal);	


DrawBox(504.0f,104.0f,100.0f,-10.0f,-3.3f,-4.3f,box_wood);
DrawBox(104.0f,104.0f,100.0f,-48.0f,-2.3f,-4.3f,box_metal);




DrawBox(504.0f,104.0f,100.0f,-20.0f,-3.3f,-4.3f,box_wood);
DrawBox(104.0f,104.0f,100.0f,-96.5f,-2.3f,-4.3f,box_metal);


DrawBox(504.0f,104.0f,100.0f,20.0f,-3.3f,-4.3f,box_wood);
DrawBox(104.0f,104.0f,100.0f,96.5f,-2.3f,-4.3f,box_metal);




DrawBox(504.0f,104.0f,100.0f,-30.0f,-3.3f,-4.3f,box_wood);
DrawBox(104.0f,104.0f,100.0f,-145.0f,-2.3f,-4.3f,box_metal);


DrawBox(504.0f,104.0f,100.0f,30.0f,-3.3f,-4.3f,box_wood);
DrawBox(104.0f,104.0f,100.0f,145.0f,-2.3f,-4.3f,box_metal);



//
//glPushMatrix();
//     glTranslatef(200000,0,0);
//	 glScalef(10,10,2);
//	 glBindTexture(GL_TEXTURE_2D,main_train_texture_cover);
//		 glBegin(GL_QUADS);
//		 glTexCoord2d(0,0); glVertex3d(0,0,0);
//		 glTexCoord2d(1,0); glVertex3d(0.5,0,0);
//		 glTexCoord2d(1,1); glVertex3d(0.5,0.5,0);
//		 glTexCoord2d(0,1); glVertex3d(0,0.5,0);
//		 glEnd();
//glPopMatrix();
//	
}


void Number_of_pelvis(){

Draw_pelvis(504.0f,104.0f,104.0f,0.0f,-3.3f,3.5f,grass,pelvis,border);



Draw_pelvis(504.0f,104.0f,104.0f,20.0f,-3.3f,3.5f,grass,pelvis,border);
Draw_pelvis(504.0f,104.0f,104.0f,-20.0f,-3.3f,3.5f,grass,pelvis,border);



Draw_pelvis(504.0f,104.0f,104.0f,39.8f,-3.3f,-3.5f,grass,pelvis,border);
Draw_pelvis(504.0f,104.0f,104.0f,-39.8f,-3.3f,-3.5f,grass,pelvis,border);


Draw_pelvis(504.0f,104.0f,104.0f,79.5f,-3.3f,3.5f,grass,pelvis,border);
Draw_pelvis(504.0f,104.0f,104.0f,-79.5f,-3.3f,3.5f,grass,pelvis,border);


Draw_pelvis(504.0f,104.0f,104.0f,98.5f,-3.3f,-3.5f,grass,pelvis,border);
Draw_pelvis(504.0f,104.0f,104.0f,-98.5f,-3.3f,-3.5f,grass,pelvis,border);


}





void DrawTerrain()
{
	initTerrainPositionX = TerrainSize/2.0f;
	initTerrainPositionZ = TerrainSize/2.0f;
	initTerrainPositionY = 0;

	glPushMatrix();
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D,terraintexture);
	glScalef(scaleX,scaleY,scaleZ);
	glTranslatef(-initTerrainPositionX, initTerrainPositionY, -initTerrainPositionZ);
	
		for (int i = 3 ; i<TerrainSize-3 ; i++)
		{
			glBegin(GL_TRIANGLE_STRIP);
			for (int j = 3 ; j < TerrainSize -3; j++)
			{
				glTexCoord2f(100+j*step,i*step);
				glVertex3f(i, GetValue(i,j), j);

				glTexCoord2f(100+(j+1)*step,i*step);
				glVertex3f(i, GetValue(i,j+1), j+1);

				glTexCoord2f(100+j*step,(i+1)*step);
				glVertex3f(i+1, GetValue(i+1,j), j);

				glTexCoord2f(100+(j+1)*step,(i+1)*step);
				glVertex3f(i+1, GetValue(i+1,j+1), j+1);
			}
			glEnd();
		}
	

	glDisable(GL_TEXTURE_2D);
	glPopMatrix();
}








void draw_tarficlight(double x,double y,double z)
{
	trafic_light->pos.x=x;
	trafic_light->pos.y=y-1.3;
	trafic_light->pos.z=z-40;
	trafic_light->scale=50;
	trafic_light->Draw();


}






float main_train_tx=0,main_train_ty=0,main_train_tz=0;
int train_s=1,train_t=1;
float teta_wheel=0;
void Draw_Main_Train(float tx=0, float ty=0, float tz=0){


	glPushMatrix();

	
	glTranslatef(600+tx,-375+ty,97+tz);
	glRotatef(180,0,1,0);
	glScalef(35,40,40);

	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D,main_train_texture_cover);	
		 glBegin(GL_QUADS);
		
		 glTexCoord2d(0,0);	 glVertex3d(0,0,0);
		 glTexCoord2d(1,0); glVertex3d(5,0,0);
		 glTexCoord2d(1,1); glVertex3d(5,5,0);
		 glTexCoord2d(0,1); glVertex3d(0,5,0);
		 glEnd();

	glBindTexture(GL_TEXTURE_2D,main_train_texture_cover);
		 glBegin(GL_QUADS);
		 glTexCoord2d(0,0); glVertex3d(5,0,0);
		 glTexCoord2d(train_s,0); glVertex3d(6,1,0);
		 glTexCoord2d(train_s,train_t); glVertex3d(6,5,0);
		 glTexCoord2d(0,train_t); glVertex3d(5,5,0);
		 glEnd();

		 glBindTexture(GL_TEXTURE_2D,complete);
		 glBegin(GL_QUADS);
		 glTexCoord2d(0,0); glVertex3d(6,1,0);
		 glTexCoord2d(train_s,0); glVertex3d(7,1,0);
		 glTexCoord2d(train_s,train_t); glVertex3d(7,7,0);
		 glTexCoord2d(0,train_t); glVertex3d(6,7,0);
		 glEnd();
		
		 glBindTexture(GL_TEXTURE_2D,complete);
		 glBegin(GL_QUADS);
		 glTexCoord2d(0,0); glVertex3d(7,1,0);
		 glTexCoord2d(train_s,0); glVertex3d(8,0,0);
		 glTexCoord2d(train_s,train_t); glVertex3d(8,7,0);
         glTexCoord2d(0,train_t); glVertex3d(7,7,0);
		 glEnd();

		 glBindTexture(GL_TEXTURE_2D,main_train_texture_body);
		glBegin(GL_QUADS);
	    glTexCoord2d(0,0); glVertex3d(8,0,0);
		glTexCoord2d(train_s,0); glVertex3d(12,0,0);
		glTexCoord2d(train_s,train_t); glVertex3d(12,7,0);
		glTexCoord2d(0,train_t); glVertex3d(8,7,0);
		glEnd();

		glBindTexture(GL_TEXTURE_2D,complete);
		glBegin(GL_QUADS);
		glTexCoord2d(0,0); glVertex3d(12,0,0);
		glTexCoord2d(train_s,0); glVertex3d(13,1,0);
		glTexCoord2d(train_s,train_t); glVertex3d(13,7,0);
		glTexCoord2d(0,train_t); glVertex3d(12,7,0);
		glEnd();

		glBindTexture(GL_TEXTURE_2D,complete);
		glBegin(GL_QUADS);
		 glTexCoord2d(0,0); glVertex3d(13,1,0);
		 glTexCoord2d(train_s,0); glVertex3d(14,1,0);
		 glTexCoord2d(train_s,train_t); glVertex3d(14,7,0);
		 glTexCoord2d(0,train_t); glVertex3d(13,7,0);
		 glEnd();

		 glBindTexture(GL_TEXTURE_2D,complete);
		 glBegin(GL_QUADS);
		 glTexCoord2d(0,0); glVertex3d(14,1,0);
		 glTexCoord2d(train_s,0); glVertex3d(15,0,0);
		 glTexCoord2d(train_s,train_t); glVertex3d(15,7,0);
		 glTexCoord2d(0,train_t); glVertex3d(14,7,0);
		 glEnd();

		 glBindTexture(GL_TEXTURE_2D,complete);
		 glBegin(GL_QUADS);
		 glTexCoord2d(0,0); glVertex3d(15,0,0);
		 glTexCoord2d(train_s,0); glVertex3d(17,0,0);
		 glTexCoord2d(train_s,train_t); glVertex3d(17,7,0);
		 glTexCoord2d(0,train_t); glVertex3d(15,7,0);
		 glEnd();



		 //الجنب الثاني

	glPushMatrix();
		 glTranslatef(0,0,5);

		 glBindTexture(GL_TEXTURE_2D,main_train_texture_cover);
		 glBegin(GL_QUADS);
		 glTexCoord2d(0,0); glVertex3d(0,0,0);
		 glTexCoord2d(1,0); glVertex3d(5,0,0);
		 glTexCoord2d(1,1); glVertex3d(5,5,0);
		 glTexCoord2d(0,1); glVertex3d(0,5,0);
		 glEnd();

		 glBindTexture(GL_TEXTURE_2D,main_train_texture_cover);
		 glBegin(GL_QUADS);
		 glTexCoord2d(0,0); glVertex3d(5,0,0);
		 glTexCoord2d(1,0); glVertex3d(6,1,0);
		 glTexCoord2d(1,1); glVertex3d(6,5,0);
		 glTexCoord2d(0,1); glVertex3d(5,5,0);
		 glEnd();

		 glBindTexture(GL_TEXTURE_2D,complete);
		 glBegin(GL_QUADS);
		 glTexCoord2d(0,0); glVertex3d(6,1,0);
		 glTexCoord2d(1,0); glVertex3d(7,1,0);
		 glTexCoord2d(1,1); glVertex3d(7,7,0);
		 glTexCoord2d(0,1); glVertex3d(6,7,0);
		 glEnd();

		 glBindTexture(GL_TEXTURE_2D,complete);
		 glBegin(GL_QUADS);
		 glTexCoord2d(0,0); glVertex3d(7,1,0);
		 glTexCoord2d(train_s,0);glVertex3d(8,0,0);
		 glTexCoord2d(train_s,train_t); glVertex3d(8,7,0);
		 glTexCoord2d(0,train_t); glVertex3d(7,7,0);
		 glEnd();

		 glBindTexture(GL_TEXTURE_2D,main_train_texture_body);
		glBegin(GL_QUADS);
	    glTexCoord2d(0,0); glVertex3d(8,0,0);
		glTexCoord2d(train_s,0); glVertex3d(12,0,0);
		glTexCoord2d(train_s,train_t); glVertex3d(12,7,0);
		glTexCoord2d(0,train_t); glVertex3d(8,7,0);
		glEnd();

		glBindTexture(GL_TEXTURE_2D,complete);
		glBegin(GL_QUADS);
		glTexCoord2d(0,0); glVertex3d(12,0,0);
		glTexCoord2d(train_s,0); glVertex3d(13,1,0);
		glTexCoord2d(train_s,train_t); glVertex3d(13,7,0);
		glTexCoord2d(0,train_t); glVertex3d(12,7,0);
		glEnd();

		glBindTexture(GL_TEXTURE_2D,complete);
		glBegin(GL_QUADS);
		 glTexCoord2d(0,0); glVertex3d(13,1,0);
		 glTexCoord2d(train_s,0); glVertex3d(14,1,0);
		 glTexCoord2d(train_s,train_t); glVertex3d(14,7,0);
		 glTexCoord2d(0,train_t); glVertex3d(13,7,0);
		 glEnd();

		 glBindTexture(GL_TEXTURE_2D,complete);
		 glBegin(GL_QUADS);
		 glTexCoord2d(0,0); glVertex3d(14,1,0);
		 glTexCoord2d(train_s,0); glVertex3d(15,0,0);
		 glTexCoord2d(train_s,train_t); glVertex3d(15,7,0);
		 glTexCoord2d(0,train_t); glVertex3d(14,7,0);
		 glEnd();

		 glBindTexture(GL_TEXTURE_2D,complete);
		 glBegin(GL_QUADS);
		 glTexCoord2d(0,0); glVertex3d(15,0,0);
		 glTexCoord2d(1,0); glVertex3d(17,0,0);
		 glTexCoord2d(1,1); glVertex3d(17,7,0);
		 glTexCoord2d(0,train_t); glVertex3d(15,7,0);
		 glEnd();
     glPopMatrix();


//سدات

	 //سدت الميتور
	glPushMatrix();
	 glRotatef(-90,0,1,0);
	 glBindTexture(GL_TEXTURE_2D,main_train_texture_front_down);
	 glBegin(GL_QUADS);
	 glTexCoord2d(0,0); glVertex3d(0,0,0);
	 glTexCoord2d(1,0); glVertex3d(5,0,0);
	 glTexCoord2d(1,1); glVertex3d(5,5,0);
	 glTexCoord2d(0,1); glVertex3d(0,5,0);
	 glEnd();
	glPopMatrix();
	 
    //غطاء المحرك
	glPushMatrix();
    glTranslatef(0,5,0);
     glRotatef(90,1,0,0);
	 glBindTexture(GL_TEXTURE_2D,main_train_texture_cover_motor_side);
	 glBegin(GL_QUADS);
	 glTexCoord2d(0,0); glVertex3d(0,0,0);
	 glTexCoord2d(1,0); glVertex3d(6,0,0);
	 glTexCoord2d(1,1); glVertex3d(6,5,0);
	 glTexCoord2d(0,1); glVertex3d(0,5,0);
	 glEnd();
	glPopMatrix();
//ghvj//fgbrb
	//65416
     //الشبابيك
	glPushMatrix();
	 glTranslatef(6,5,0);
     glRotatef(-90,0,1,0);
	 glBindTexture(GL_TEXTURE_2D,main_train_texture_front_up);
	 glBegin(GL_QUADS);
	 glTexCoord2d(0,0); glVertex3d(0,0,0);
	 glTexCoord2d(1,0); glVertex3d(5,0,0);
	 glTexCoord2d(1,1); glVertex3d(5,2,0);
	 glTexCoord2d(0,1); glVertex3d(0,2,0);
	 glEnd();
	glPopMatrix();
	//tyhjmthjm
     //السقف
	glPushMatrix();
	glBindTexture(GL_TEXTURE_2D,main_train_texture_roof);
	 glTranslatef(0,7,0);
     glRotatef(90,1,0,0);
	 glBegin(GL_QUADS);
	 glTexCoord2d(0,0); glVertex3d(6,0,0);
	 glTexCoord2d(1,0); glVertex3d(17,0,0);
	 glTexCoord2d(1,1); glVertex3d(17,5,0);
	 glTexCoord2d(0,1); glVertex3d(6,5,0);
	 glEnd();
	glPopMatrix();
      

	//الأرضية1
	glPushMatrix();
	 glTranslatef(0,0.5,0);
     glRotatef(90,1,0,0);
	 glBegin(GL_QUADS);
	 glVertex3d(0,0,0);
	 glVertex3d(6,0,0);
	 glVertex3d(6,5,0);
	 glVertex3d(0,5,0);
	 glEnd();
	glPopMatrix();

//الأرضية2
	glPushMatrix();
	 glTranslatef(0,0.5,0);
     glRotatef(90,1,0,0);
	 glBegin(GL_QUADS);
	 glVertex3d(9,0,0);
	 glVertex3d(12,0,0);
	 glVertex3d(12,5,0);
	 glVertex3d(0,5,0);
	 glEnd();
	glPopMatrix();

	//الأرضية3
	glPushMatrix();
	 glTranslatef(0,0.5,0);
     glRotatef(90,1,0,0);
	 glBegin(GL_QUADS);
	 glVertex3d(15,0,0);
	 glVertex3d(17,0,0);
	 glVertex3d(17,5,0);
	 glVertex3d(0,5,0);
	 glEnd();
	glPopMatrix();
    

	//الظهر
	 glPushMatrix();
	 //glLoadIdentity();
	  glTranslatef(17,0,0);
     glRotatef(-90,0,1,0);
	 glBindTexture(GL_TEXTURE_2D,main_train_texture_cover);
	 glBegin(GL_QUADS);
	 glTexCoord2d(0,0); glVertex3d(0,0,0);
	 glTexCoord2d(1,0); glVertex3d(5,0,0);
     glTexCoord2d(1,1); glVertex3d(5,7,0);
	 glTexCoord2d(0,1); glVertex3d(0,7,0);
	 /*glVertex3d(17,0,0);
	 glVertex3d(21,0,0);
	 glVertex3d(21,7,0);
	 glVertex3d(17,7,0);*/
	 glEnd();
	glPopMatrix();
    



	//الإطارات
	//الأول اليساري
	glPushMatrix();
	glBindTexture(GL_TEXTURE_2D,wheel);
	glTranslatef(6.5,0.5,3.5);
	glRotatef(15,1,0,0);
	glRotatef(teta_wheel,0,0,1);
	gluSphere(quadric,1.5,32,32);
	glPopMatrix();


	//الثاني اليساري
    glPushMatrix();
	glBindTexture(GL_TEXTURE_2D,wheel);
	glTranslatef(13.5,0.5,3.5);
	glRotatef(15,1,0,0);
	glRotatef(teta_wheel,0,0,1);
	gluSphere(quadric,1.5,32,32);
	glPopMatrix();

	//الثاني اليميني
    glPushMatrix();
	glBindTexture(GL_TEXTURE_2D,wheel);
	glTranslatef(13.5,1,1.5);
	glRotatef(-20,1,0,0);
	glRotatef(180,0,1,0);
	glRotatef(-1*teta_wheel,0,0,1);
	gluSphere(quadric,1.5,32,32);
	glPopMatrix();



	//الأول اليميني
    glPushMatrix();
	glBindTexture(GL_TEXTURE_2D,wheel);
	glTranslatef(6.5,1,1.5);
	glRotatef(-20,1,0,0);
	glRotatef(180,0,1,0);
	glRotatef(-1*teta_wheel,0,0,1);
	gluSphere(quadric,1.5,32,32);
	glPopMatrix();



    //الوصلة بين القاطرة و المقطورة
    glPushMatrix();
	///glBindTexture(GL_TEXTURE_2D,wheel);
	glTranslatef(21.5,2,2);
	glRotatef(-20,1,0,0);
	glRotatef(-90,0,1,0);
	gluCylinder(quadric,0.25,0.25,5,32,32);
	glPopMatrix();







	 glPopMatrix();


}



void Number_of_cottage_car(){

	drawcar(80500,-400,1200,0.2,180);
	drawcottage(80000,-500,1200,0.2,180);

	drawcar(60500,-400,1200,0.2,180);
	drawcottage(60000,-500,1200,0.2,180);


	drawcar(69100,-400,-1500,0.2,180);
	drawcottage(70000,-500,-1500,0.2,0);

	drawcar(89100,-400,-1500,0.2,180);
	drawcottage(90000,-500,-1500,0.2,0);

}


void Number_of_Building(){

Draw_Building(-7000,-200,-25,300,400,300,Buliding5,Buliding5,Buliding5,Buliding5,Buliding5,Buliding5);
Draw_Building(-6500,-200,-25,300,400,300,Buliding5,Buliding5,Buliding5,Buliding5,Buliding5,Buliding5);
Draw_Building(-6000,-200,-25,300,400,300,Buliding5,Buliding5,Buliding5,Buliding5,Buliding5,Buliding5);
Draw_Building(-5500,-200,-25,300,400,300,Buliding5,Buliding5,Buliding5,Buliding5,Buliding5,Buliding5);
Draw_Building(-5000,-200,-25,300,400,300,Buliding5,Buliding5,Buliding5,Buliding5,Buliding5,Buliding5);


Draw_Building(-4000,-200,-25,300,400,300,Buliding3,Buliding3,Buliding3,Buliding3,Buliding3,Buliding3);
Draw_Building(-3500,-200,-25,300,400,300,Buliding3,Buliding3,Buliding3,Buliding3,Buliding3,Buliding3);
Draw_Building(-3000,-200,-25,300,400,300,Buliding3,Buliding3,Buliding3,Buliding3,Buliding3,Buliding3);
Draw_Building(-2500,-200,-25,300,400,300,Buliding3,Buliding3,Buliding3,Buliding3,Buliding3,Buliding3);
Draw_Building(-2000,-200,-25,300,400,300,Buliding3,Buliding3,Buliding3,Buliding3,Buliding3,Buliding3);


Draw_Building(-1000,-200,-25,300,400,300,Buliding2,Buliding2,Buliding2,Buliding2,Buliding2,Buliding2);
Draw_Building(-500,-200,-25,300,400,300,Buliding2,Buliding2,Buliding2,Buliding2,Buliding2,Buliding2);
Draw_Building(0,-200,-25,300,400,300,Buliding2,Buliding2,Buliding2,Buliding2,Buliding2,Buliding2);
Draw_Building(500,-200,-25,300,400,300,Buliding2,Buliding2,Buliding2,Buliding2,Buliding2,Buliding2);
Draw_Building(1000,-200,-25,300,400,300,Buliding2,Buliding2,Buliding2,Buliding2,Buliding2,Buliding2);


Draw_Building(2000,-200,-25,300,400,300,Buliding1,Buliding1,Buliding1,Buliding1,Buliding1,Buliding1);
Draw_Building(2500,-200,-25,300,400,300,Buliding1,Buliding1,Buliding1,Buliding1,Buliding1,Buliding1);
Draw_Building(3000,-200,-25,300,400,300,Buliding1,Buliding1,Buliding1,Buliding1,Buliding1,Buliding1);
Draw_Building(3500,-200,-25,300,400,300,Buliding1,Buliding1,Buliding1,Buliding1,Buliding1,Buliding1);
Draw_Building(4000,-200,-25,300,400,300,Buliding1,Buliding1,Buliding1,Buliding1,Buliding1,Buliding1);




Draw_Building(-7000,-200,-3500,300,600,300,Buliding6,Buliding6,Buliding6,Buliding6,Buliding6,Buliding6);
Draw_Building(-6500,-200,-3500,300,600,300,Buliding6,Buliding6,Buliding6,Buliding6,Buliding6,Buliding6);
Draw_Building(-6000,-200,-3500,300,600,300,Buliding6,Buliding6,Buliding6,Buliding6,Buliding6,Buliding6);
Draw_Building(-5500,-200,-3500,300,600,300,Buliding6,Buliding6,Buliding6,Buliding6,Buliding6,Buliding6);
Draw_Building(-5000,-200,-3500,300,600,300,Buliding6,Buliding6,Buliding6,Buliding6,Buliding6,Buliding6);


Draw_Building(4000,-200,-3500,300,600,300,Buliding7,Buliding7,Buliding7,Buliding7,Buliding7,Buliding7);
Draw_Building(3500,-200,-3500,300,600,300,Buliding7,Buliding7,Buliding7,Buliding7,Buliding7,Buliding7);
Draw_Building(3000,-200,-3500,300,600,300,Buliding7,Buliding7,Buliding7,Buliding7,Buliding7,Buliding7);
Draw_Building(2500,-200,-3500,300,600,300,Buliding7,Buliding7,Buliding7,Buliding7,Buliding7,Buliding7);
Draw_Building(2000,-200,-3500,300,600,300,Buliding7,Buliding7,Buliding7,Buliding7,Buliding7,Buliding7);


Draw_Building(-1000,-300,-3500,300,400,300,Buliding8,Buliding8,Buliding8,Buliding8,Buliding8,Buliding8);
Draw_Building(500,-300,-3500,300,400,300,Buliding8,Buliding8,Buliding8,Buliding8,Buliding8,Buliding8);
Draw_Building(0,-300,-3500,300,400,300,Buliding8,Buliding8,Buliding8,Buliding8,Buliding8,Buliding8);
Draw_Building(500,-300,-3500,300,400,300,Buliding8,Buliding8,Buliding8,Buliding8,Buliding8,Buliding8);
Draw_Building(1000,-300,-3500,300,400,300,Buliding8,Buliding8,Buliding8,Buliding8,Buliding8,Buliding8);



}






float angle;
bool movetrain=false;
bool firsttime=false;

float myx,myy,myz;


//متحولات الانزياح عن القطار الخاصة بالكاميرة
float dx=0,dy=-180,dz=-25;
float length_dx=2;//انزياح الكاميرا عن القطار
bool go=false;//متحول منطقي لتحديد قرار مرافقة القطار من عدمه
float train_speed=0;//سرعة القطار

double camera_rotate_spead=1;//سرعة دوران الكاميرة



//متحولات خاصة بحركة القطار
float neg_z=0.5;
float rot_x=0.2;
double movex=0,movey=0,movez=0;


bool yes=false;
void key()
{
	 //لحركة الكاميرة الأولى للخلف
	if (keys['S']  && !go)
	 {
		// if(!movetrain)
        _camera1.MoveForward(-30*speed );
		 /*else
		 {
			 _camera1.Position.x=myx-10;
			 _camera1.Position.y=myy;
			 _camera1.Position.z=myz;
		 }*/
	 }

	// لحركة الكاميرة الأولى للأمام
	if (keys['W']  && !go)
		_camera1.MoveForward(30*speed ) ;

	//دوران الكاميرا لليمين
	if (keys['D'])
		_camera1.RotateY(-1*camera_rotate_spead);

	//دوران الكاميرا لليسار
	if (keys['A'])
		_camera1.RotateY(1*camera_rotate_spead);

	//لرفع الكاميرا على محور العينات بثبات موقعها
	if(keys['8'])
		_camera1.View.y+=0.01f*camera_rotate_spead;
    // لخفض الكاميرا على محور العينات بسبات موقعها
	if(keys['2'])
		_camera1.View.y-=0.01f*camera_rotate_spead;

	//لزيادة ارتفاع الكاميرا على محور العينات
	if(keys['3'] )
		_camera1.Position.y+=10;

	//لخفض ارتفاع الكاميرا على محور العينات
	if(keys['1'] && _camera1.Position.y>-385)
		_camera1.Position.y-=10;


	if(keys['Q']){
		length_dx+=1;
	}

	if(keys['E']){
		length_dx-=1;
	}



	if(keys['K']){
		speed+=0.1;
	}

	if(keys['L']){
		speed-=0.1;
	}


	if(keys['I'])
		camera_rotate_spead+=0.1;
	
	if(keys['O'])
		camera_rotate_spead-=0.1;

	
if(keys['M']){
		 movetrain=true;

		 PlaySound(TEXT("Data/Sound/tot.wav"),NULL,SND_FILENAME | SND_ALIAS | SND_ASYNC | SND_LOOP);
	 }
if(keys['N']){
		 movetrain=false;
		 PlaySound(TEXT("Data/Sound/background.wav"),NULL,SND_FILENAME | SND_ALIAS | SND_ASYNC | SND_LOOP);
	}

if(keys['G']){
	go=true;

	if(_camera1.Position.y<250)
	    _camera1.Position.y=100;
}
if(keys['H']){
	go=false;
}
	

	//ويادة سرعة القطار
	if(keys[VK_UP])
		train_speed+=5;
    if(keys[VK_DOWN])
		train_speed-=5;



   if(keys['R']){
	   movetrain=false;
	   PlaySound(TEXT("Data/Sound/background.wav"),NULL,SND_FILENAME | SND_ALIAS | SND_ASYNC | SND_LOOP);

	   //إعادة القطار إلى مكان إنطلاقه
	   movex=0;

	   //إعادة الكاميرا إلى موضعها
	    _camera1.RightVector.x=1200;
		_camera1.Position.x=-1300;
		_camera1.Position.y=-150;
		_camera1.RotateY(-71.25);

		//إعادة ضبط سرعة الكاميرا
		speed=0.5;
		camera_rotate_spead=1;
		main_train_tx=0;
   }		
 
    if(keys['Z'])
	{
		yes=true;
		//للتموضع في داخل القطار
		dx=0;
		_camera1.Position.y=light->pos.y-50;
	}

	/*if(ok){

		dx=woman1->pos.x;
		

	}*/

	if(keys['X'])
	{
		length_dx=20;
		_camera1.Position.y=100;

		yes=false;
	}



	if(keys[VK_NUMPAD1])
		x_light+=5000;
	if(keys[VK_NUMPAD2])
		x_light-=5000;

	if(keys[VK_NUMPAD4])
		y_light+=5000;
	if(keys[VK_NUMPAD5])
		y_light-=5000;

	if(keys[VK_NUMPAD7])
		z_light+=5000;
	if(keys[VK_NUMPAD8])
		z_light-=5000;


//
//if(movetrain){
//	if(keys['W'])
//		_camera1.MoveForward(dx+10 ) ;
//	if(keys['S'])
//		_camera1.MoveForward(-1*(dx+10) ) ;

//}

}



void load_Image_start(){

	glPushMatrix();
	glScaled(33,17,1);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D,loading);
	glBegin(GL_QUADS);
	glTexCoord2d(0,0);  glVertex3d(-0.5,-0.5,0);
	glTexCoord2d(1,0);  glVertex3d(0.5,-0.5,0);
	glTexCoord2d(1,1);  glVertex3d(0.5,0.5,0);
	glTexCoord2d(0,1);  glVertex3d(-0.5,0.5,0);
	glEnd();
	glPopMatrix();

}

void load_Image_stop(){


	glPushMatrix();
	glTranslated(110000,-280,-500);
	glRotated(-90,0,1,0);
	glScaled(500,500,1);

	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D,stop.texID);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
	glBegin(GL_QUADS);
		glTexCoord2d(0,0);  glVertex3d(-0.5,-0.5,0);
		glTexCoord2d(1,0);  glVertex3d(0.5,-0.5,0);
		glTexCoord2d(1,1);  glVertex3d(0.5,0.5,0);
		glTexCoord2d(0,1);  glVertex3d(-0.5,0.5,0);
	glEnd();
	glDisable(GL_BLEND);


	glPopMatrix();
}


void draw_glasses(float tx)
{
	    //الزجاج الأول اليميني
		glPushMatrix();
		glTranslated(-250+tx,-160,125);
	
		glScaled(90.0,80.0,3);

  	    glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
		glEnable(GL_BLEND);
		glEnable(GL_ALPHA_TEST);
		glAlphaFunc(GL_GREATER,-1);
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D,glass);
		
		glBegin(GL_QUADS);
		glTexCoord2d(0,0);  glVertex3d(-0.5,-0.5,0);
		glTexCoord2d(1,0);  glVertex3d(0.5,-0.5,0);
		glTexCoord2d(1,1);  glVertex3d(0.5,0.5,0);
		glTexCoord2d(0,1);  glVertex3d(-0.5,0.5,0);
		glEnd();
		glDisable(GL_ALPHA_TEST);
		glDisable(GL_BLEND);
	glPopMatrix();



	//الزجاج الأول اليساري
		glPushMatrix();
		glTranslated(-250+tx,-160,-150);
	
		glScaled(90.0,80.0,3);

  	    glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
		glEnable(GL_BLEND);
		glEnable(GL_ALPHA_TEST);
		glAlphaFunc(GL_GREATER,-1);
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D,glass);
		
		glBegin(GL_QUADS);
		glTexCoord2d(0,0);  glVertex3d(-0.5,-0.5,0);
		glTexCoord2d(1,0);  glVertex3d(0.5,-0.5,0);
		glTexCoord2d(1,1);  glVertex3d(0.5,0.5,0);
		glTexCoord2d(0,1);  glVertex3d(-0.5,0.5,0);
		glEnd();
		glDisable(GL_ALPHA_TEST);
		glDisable(GL_BLEND);
	glPopMatrix();



	//الزجاج الثاني اليميني
		glPushMatrix();
		glTranslated(-425+tx,-160,125);
	
		glScaled(90.0,80.0,3);

  	    glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
		glEnable(GL_BLEND);
		glEnable(GL_ALPHA_TEST);
		glAlphaFunc(GL_GREATER,-1);
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D,glass);
		
		glBegin(GL_QUADS);
		glTexCoord2d(0,0);  glVertex3d(-0.5,-0.5,0);
		glTexCoord2d(1,0);  glVertex3d(0.5,-0.5,0);
		glTexCoord2d(1,1);  glVertex3d(0.5,0.5,0);
		glTexCoord2d(0,1);  glVertex3d(-0.5,0.5,0);
		glEnd();
		glDisable(GL_ALPHA_TEST);
		glDisable(GL_BLEND);
	glPopMatrix();


	//الزجاج الثاني اليساري
		glPushMatrix();
		glTranslated(-425+tx,-160,-150);
	
		glScaled(90.0,80.0,3);

  	    glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
		glEnable(GL_BLEND);
		glEnable(GL_ALPHA_TEST);
		glAlphaFunc(GL_GREATER,-1);
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D,glass);
		
		glBegin(GL_QUADS);
		glTexCoord2d(0,0);  glVertex3d(-0.5,-0.5,0);
		glTexCoord2d(1,0);  glVertex3d(0.5,-0.5,0);
		glTexCoord2d(1,1);  glVertex3d(0.5,0.5,0);
		glTexCoord2d(0,1);  glVertex3d(-0.5,0.5,0);
		glEnd();
		glDisable(GL_ALPHA_TEST);
		glDisable(GL_BLEND);
	glPopMatrix();

}


void draw_tree_using_blend1(float tx, float ty, float tz){

glPushMatrix();
	glTranslated(tx,ty,tz);
	glScaled(50,50,50);

	glPushMatrix();
		glTranslatef(0.1,0,-0.1);
		//glColor3f(1,1,1);
	glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D,my_tree.texID);
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
		glBegin(GL_QUADS);
		glTexCoord2f(1,0);       glVertex3f(5,-5,0);
		glTexCoord2f(1,1);       glVertex3f(5,5,0);
		glTexCoord2f(0,1);       glVertex3f(-5,5,0);
		glTexCoord2f(0,0);       glVertex3f(-5,-5,0);
		glEnd();
		glDisable(GL_BLEND);
	glPopMatrix();



		glPushMatrix();
    
		//glTranslatef(0,0,-20);
		glRotated(-90,0,1,0);
		//glColor3f(1,1,1);
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D,my_tree.texID);
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
		glBegin(GL_QUADS);
		glTexCoord2f(1,0);       glVertex3f(5,-5,0);
		glTexCoord2f(1,1);       glVertex3f(5,5,0);
		glTexCoord2f(0,1);       glVertex3f(-5,5,0);
		glTexCoord2f(0,0);       glVertex3f(-5,-5,0);
		glEnd();
		glDisable(GL_BLEND);
	glPopMatrix();
	
 glPopMatrix();


}

void draw_tree_using_blend2(float tx, float ty, float tz){

glPushMatrix();
	glTranslated(tx,ty,tz);
	glScaled(50,50,50);
	  
	glPushMatrix();
    
		//glTranslatef(0,0,-20);
		glRotated(-90,0,1,0);
		//glColor3f(1,1,1);
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D,my_tree.texID);
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
		glBegin(GL_QUADS);
		glTexCoord2f(1,0);       glVertex3f(5,-5,0);
		glTexCoord2f(1,1);       glVertex3f(5,5,0);
		glTexCoord2f(0,1);       glVertex3f(-5,5,0);
		glTexCoord2f(0,0);       glVertex3f(-5,-5,0);
		glEnd();
		glDisable(GL_BLEND);
	glPopMatrix();
glPopMatrix();
}


//double dz;
int counter=0;
bool play_bgsound=false;
bool play_stop_sound=false;
int DrawGLScene(GLvoid)									// Here's Where We Do All The Drawing
{	
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	// Clear Screen And Depth Buffer
	glLoadIdentity();// Reset The Current Modelview Matrix
    glTranslatef(0,0,-20);


	//
//glPushMatrix();
//glTranslated(1000,0,0);
//glScaled(0.5,0.5,0.5);
//glEnable(GL_FOG);
//GLfloat color []={1,1,1,0.5};
//glFogfv(GL_FOG_COLOR,color);
//glFogi(GL_FOG_MODE,GL_LINEAR);
//glFogf(GL_FOG_START,-1000000000000000000);
//glFogf(GL_FOG_END,1000000000000000000);
//glPopMatrix();


	
	
	counter++;
if(counter<4000)
	load_Image_start();
   










 if(counter>4000)
 {
	 //تفعيل الصوت
	 if(!play_bgsound)
	 {
	    PlaySound(TEXT("Data/Sound/background.wav"),NULL,SND_FILENAME | SND_ALIAS | SND_ASYNC | SND_LOOP);
		play_bgsound=true;
	 }


   //تابع تلقي إشارات الكيبورد
	 key();
	 _camera1.Render();
	 
     

	 //الإنارة

	 glPushMatrix();
	 glDisable(GL_LIGHTING);
	 glColor3b(1,1,0);
	 glTranslated(x_light,y_light,z_light);
	 auxSolidSphere(500);
	 glColor3f(1,1,1);
	 glPopMatrix();
	 light1_position[0]=x_light;
	 light1_position[1]=y_light;
	 light1_position[2]=z_light;


	 glLightfv(GL_LIGHT1,GL_POSITION,light1_position);

	 //إعادة حساب مصفوفة الظل بعد تغير موضع الضوء
	 m3dMakePlanarShadowMatrix(shadowMat,vPlaneEquation,light1_position);
	 m3dMakePlanarShadowMatrix(shadowMat2,vPlaneEquation2,light1_position);



	 if(movetrain && movex<108000)
	 {
		 teta_wheel+=10+train_speed;

		 movex+=10+train_speed;
	 	// movez-=0.005;

		 main_train_tx+=10+train_speed;
		 //main_train_tz-=0.005;
	 }


	 //عند وقوف القطار عند اشارة الوقوف
	 if(movex>=108000)
	 {	
		if(!play_stop_sound)
		{
			PlaySound(TEXT("Data/Sound/stop.wav"),NULL,SND_FILENAME | SND_ALIAS | SND_ASYNC | SND_LOOP);
			play_stop_sound=true;
		}

	 }

	 
	 if(go && !yes)
	 {
      	_camera1.Position.x=movex+dx+1;
		_camera1.Position.z=woman1->pos.z+ dz;
		cout<<dx+1<<endl;
	    //_camera1.Position.z=movez;
		//_camera1.Position.x=dx+1;

	    if(keys['W']){
			dx+=length_dx;
		}

		if(keys['S']){
			dx-=length_dx;
		}

		if(keys[VK_RIGHT])
			dz+=length_dx;

		if(keys[VK_LEFT])
			dz-=length_dx;
	 }

	 if(go && yes ){

		 _camera1.Position.x=woman1->pos.x+dx+1;
		 _camera1.Position.z=woman1->pos.z+dz;
		//  cout<<dx+1<<endl;
	 //   //_camera1.Position.z=movez;
		////_camera1.Position.x=dx+1;

	    if(keys['W']){
			dx+=length_dx;
		}

		if(keys['S']){
			dx-=length_dx;
		}

		if(keys[VK_RIGHT])
			dz+=length_dx;

		if(keys[VK_LEFT])
			dz-=length_dx;
	 }



	 	


	 //رسم الطريق
	 glDisable(GL_LIGHTING);
	 Draw_road();
	
	 //رسم التضاريس
	 glDisable(GL_LIGHTING);
	glPushMatrix();
	glTranslatef(85000,-1500,0);
	glScalef(150,20,50);
	DrawTerrain();
	glPopMatrix();


	 //تطبق الظل
	 if(movex>50000)
	 {
		 glPushMatrix();
		 glDisable(GL_DEPTH_TEST);
		 glDisable(GL_LIGHTING);
		 glMultMatrixf((GLfloat*)shadowMat);
		 glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
		 glEnable(GL_BLEND);
		 glColor4f(0,0,0,0.5);
		 //رسم ظل القاطرة
		 Draw_Main_Train(main_train_tx,main_train_ty,main_train_tz);

		 glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
		 glEnable(GL_BLEND);
		 glColor4f(0,0,0,0.3);
		 //رسم ظل المقطورة
		drawTrain(-300+movex,-200,movez,30);
		glEnable(GL_DEPTH_TEST);
		glEnable(GL_LIGHTING);
		glDisable(GL_BLEND);
		glPopMatrix();
	 }
		
   glColor3f(1,1,1);



   //ظل الاشجار
	glPushMatrix();
	///glLoadIdentity();
	//glTranslatef(100,0,0);
		 glDisable(GL_DEPTH_TEST);
		 glDisable(GL_LIGHTING);
		 glMultMatrixf((GLfloat*)shadowMat2);
		 glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
		 glEnable(GL_BLEND);
		 glColor4f(0,0,0,0.5);
  	    //drawtreemodel(51000,-600,1200,10);
		 number_of__tree2();
		 load_Image_stop();
		 glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
		 glEnable(GL_BLEND);
		 glColor4f(0,0,0,0.1);
		 	Number_of_cottage_car();
			glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
		 glEnable(GL_BLEND);
		 glColor4f(0,0,0,0.3);

	//رسم الأبنية
	Number_of_Building();
		glEnable(GL_DEPTH_TEST);
		glEnable(GL_LIGHTING);
		glDisable(GL_BLEND);
		glPopMatrix();

		glColor3f(1,1,1);
		glDisable(GL_LIGHTING);
		//drawtreemodel(51000,-600,1200,10);



	    //رسم القاطرة الرئيسية
	glDisable(GL_LIGHTING);
	glPushMatrix();
	 Draw_Main_Train(main_train_tx,main_train_ty,main_train_tz);
	 glPopMatrix();





	//رسم المقطورة
    glDisable(GL_LIGHTING);
	glPushMatrix();
    drawTrain(-300+movex,-200,movez,30);
	glPopMatrix();
    
    	

	glDisable(GL_LIGHTING);

	
		glDisable(GL_LIGHTING);
		//رسم الأشجار من النوع الثاني
		glPushMatrix();
	number_of__tree2();
	glPopMatrix();

	


	 //رسم الأكواخ
	glPushMatrix();
	Number_of_cottage_car();
	glPopMatrix();
   
	//رسم الأبنية
	glPushMatrix();
	Number_of_Building();
	glPopMatrix();
	 	
	
	// رسم نفق القطار
	glPushMatrix();
      DrawEarth();
	  glPopMatrix();




    //رسم الأشجار
	  glPushMatrix();
	Number_of_Tree();
	glPopMatrix();



    //رسم الصناديق
	glPushMatrix();
	Number_of_Boxes();
	glPopMatrix();

    //رسم أحواض الأشجار
	glPushMatrix();
	Number_of_pelvis();
	glPopMatrix();


	  //رسم السماء
	 glPushMatrix();
	 glRotatef(90,0,1,0);
	 DrawSkyBox(500000);
	 glPopMatrix();



	//صورة الوقوف
	 glPushMatrix();
	 load_Image_stop();
	 glPopMatrix();

	 //رسم زجاج النوافذ
	 glPushMatrix();
	draw_glasses(movex);    
	glPopMatrix();









	

//رسم الشجرة
//draw_tree_using_blend1(1000,-100,0);

//draw_tree_using_blend2(1000,-100,0);


}
	return true;
} 

GLvoid KillGLWindow(GLvoid)								// Properly Kill The Window
{
	if (fullscreen)										// Are We In Fullscreen Mode?
	{
		ChangeDisplaySettings(NULL,0);					// If So Switch Back To The Desktop
		ShowCursor(TRUE);								// Show Mouse Pointer
	}

	if (hRC)											// Do We Have A Rendering Context?
	{
		if (!wglMakeCurrent(NULL,NULL))					// Are We Able To Release The DC And RC Contexts?
		{
			MessageBox(NULL,"Release Of DC And RC Failed.","SHUTDOWN ERROR",MB_OK | MB_ICONINFORMATION);
		}

		if (!wglDeleteContext(hRC))						// Are We Able To Delete The RC?
		{
			MessageBox(NULL,"Release Rendering Context Failed.","SHUTDOWN ERROR",MB_OK | MB_ICONINFORMATION);
		}
		hRC=NULL;										// Set RC To NULL
	}

	if (hDC && !ReleaseDC(hWnd,hDC))					// Are We Able To Release The DC
	{
		MessageBox(NULL,"Release Device Context Failed.","SHUTDOWN ERROR",MB_OK | MB_ICONINFORMATION);
		hDC=NULL;										// Set DC To NULL
	}

	if (hWnd && !DestroyWindow(hWnd))					// Are We Able To Destroy The Window?
	{
		MessageBox(NULL,"Could Not Release hWnd.","SHUTDOWN ERROR",MB_OK | MB_ICONINFORMATION);
		hWnd=NULL;										// Set hWnd To NULL
	}

	if (!UnregisterClass("OpenGL",hInstance))			// Are We Able To Unregister Class
	{
		MessageBox(NULL,"Could Not Unregister Class.","SHUTDOWN ERROR",MB_OK | MB_ICONINFORMATION);
		hInstance=NULL;									// Set hInstance To NULL
	}
}

/*	This Code Creates Our OpenGL Window.  Parameters Are:					*
 *	title			- Title To Appear At The Top Of The Window				*
 *	width			- Width Of The GL Window Or Fullscreen Mode				*
 *	height			- Height Of The GL Window Or Fullscreen Mode			*
 *	bits			- Number Of Bits To Use For Color (8/16/24/32)			*
 *	fullscreenflag	- Use Fullscreen Mode (TRUE) Or Windowed Mode (FALSE)	*/
 
BOOL CreateGLWindow(char* title, int width, int height, int bits, bool fullscreenflag)
{
	GLuint		PixelFormat;			// Holds The Results After Searching For A Match
	WNDCLASS	wc;						// Windows Class Structure
	DWORD		dwExStyle;				// Window Extended Style
	DWORD		dwStyle;				// Window Style
	RECT		WindowRect;				// Grabs Rectangle Upper Left / Lower Right Values
	WindowRect.left=(long)0;			// Set Left Value To 0
	WindowRect.right=(long)width;		// Set Right Value To Requested Width
	WindowRect.top=(long)0;				// Set Top Value To 0
	WindowRect.bottom=(long)height;		// Set Bottom Value To Requested Height

	fullscreen=fullscreenflag;			// Set The Global Fullscreen Flag5555555

	hInstance			= GetModuleHandle(NULL);				// Grab An Instance For Our Window
	wc.style			= CS_HREDRAW | CS_VREDRAW | CS_OWNDC;	// Redraw On Size, And Own DC For Window.
	wc.lpfnWndProc		= (WNDPROC) WndProc;					// WndProc Handles Messages
	wc.cbClsExtra		= 0;									// No Extra Window Data
	wc.cbWndExtra		= 0;									// No Extra Window Data
	wc.hInstance		= hInstance;							// Set The Instance
	wc.hIcon			= LoadIcon(NULL, IDI_WINLOGO);			// Load The Default Icon
	wc.hCursor			= LoadCursor(NULL, IDC_ARROW);			// Load The Arrow Pointer
	wc.hbrBackground	= NULL;									// No Background Required For GL
	wc.lpszMenuName		= NULL;									// We Don't Want A Menu
	wc.lpszClassName	= "OpenGL";								// Set The Class Name

	if (!RegisterClass(&wc))									// Attempt To Register The Window Class
	{
		MessageBox(NULL,"Failed To Register The Window Class.","ERROR",MB_OK|MB_ICONEXCLAMATION);
		return FALSE;											// Return FALSE
	}
	
	if (fullscreen)												// Attempt Fullscreen Mode?
	{
		DEVMODE dmScreenSettings;								// Device Mode
		memset(&dmScreenSettings,0,sizeof(dmScreenSettings));	// Makes Sure Memory's Cleared
		dmScreenSettings.dmSize=sizeof(dmScreenSettings);		// Size Of The Devmode Structure
		dmScreenSettings.dmPelsWidth	= width;				// Selected Screen Width
		dmScreenSettings.dmPelsHeight	= height;				// Selected Screen Height
		dmScreenSettings.dmBitsPerPel	= bits;					// Selected Bits Per Pixel
		dmScreenSettings.dmFields=DM_BITSPERPEL|DM_PELSWIDTH|DM_PELSHEIGHT;

		// Try To Set Selected Mode And Get Results.  NOTE: CDS_FULLSCREEN Gets Rid Of Start Bar.
		if (ChangeDisplaySettings(&dmScreenSettings,CDS_FULLSCREEN)!=DISP_CHANGE_SUCCESSFUL)
		{
			// If The Mode Fails, Offer Two Options.  Quit Or Use Windowed Mode.
			if (MessageBox(NULL,"The Requested Fullscreen Mode Is Not Supported By\nYour Video Card. Use Windowed Mode Instead?","NeHe GL",MB_YESNO|MB_ICONEXCLAMATION)==IDYES)
			{
				fullscreen=FALSE;		// Windowed Mode Selected.  Fullscreen = FALSE
			}
			else
			{
				// Pop Up A Message Box Letting User Know The Program Is Closing.
				MessageBox(NULL,"Program Will Now Close.","ERROR",MB_OK|MB_ICONSTOP);
				return FALSE;									// Return FALSE
			}
		}
	}

	if (fullscreen)												// Are We Still In Fullscreen Mode?
	{
		dwExStyle=WS_EX_APPWINDOW;								// Window Extended Style
		dwStyle=WS_POPUP;										// Windows Style
		ShowCursor(FALSE);										// Hide Mouse Pointer
	}
	else
	{
		dwExStyle=WS_EX_APPWINDOW | WS_EX_WINDOWEDGE;			// Window Extended Style
		dwStyle=WS_OVERLAPPEDWINDOW;							// Windows Style
	}

	AdjustWindowRectEx(&WindowRect, dwStyle, FALSE, dwExStyle);		// Adjust Window To True Requested Size

	// Create The Window
	if (!(hWnd=CreateWindowEx(	dwExStyle,							// Extended Style For The Window
								"OpenGL",							// Class Name
								title,								// Window Title
								dwStyle |							// Defined Window Style
								WS_CLIPSIBLINGS |					// Required Window Style
								WS_CLIPCHILDREN,					// Required Window Style
								0, 0,								// Window Position
								WindowRect.right-WindowRect.left,	// Calculate Window Width
								WindowRect.bottom-WindowRect.top,	// Calculate Window Height
								NULL,								// No Parent Window
								NULL,								// No Menu
								hInstance,							// Instance
								NULL)))								// Dont Pass Anything To WM_CREATE
	{
		KillGLWindow();								// Reset The Display
		MessageBox(NULL,"Window Creation Error.","ERROR",MB_OK|MB_ICONEXCLAMATION);
		return FALSE;								// Return FALSE
	}

	static	PIXELFORMATDESCRIPTOR pfd=				// pfd Tells Windows How We Want Things To Be
	{
		sizeof(PIXELFORMATDESCRIPTOR),				// Size Of This Pixel Format Descriptor
		1,											// Version Number
		PFD_DRAW_TO_WINDOW |						// Format Must Support Window
		PFD_SUPPORT_OPENGL |						// Format Must Support OpenGL
		PFD_DOUBLEBUFFER,							// Must Support Double Buffering
		PFD_TYPE_RGBA,								// Request An RGBA Format
		bits,										// Select Our Color Depth
		0, 0, 0, 0, 0, 0,							// Color Bits Ignored
		0,											// No Alpha Buffer
		0,											// Shift Bit Ignored
		0,											// No Accumulation Buffer
		0, 0, 0, 0,									// Accumulation Bits Ignored
		16,											// 16Bit Z-Buffer (Depth Buffer)  
		0,											// No Stencil Buffer
		0,											// No Auxiliary Buffer
		PFD_MAIN_PLANE,								// Main Drawing Layer
		0,											// Reserved
		0, 0, 0										// Layer Masks Ignored
	};
	
	if (!(hDC=GetDC(hWnd)))							// Did We Get A Device Context?
	{
		KillGLWindow();								// Reset The Display
		MessageBox(NULL,"Can't Create A GL Device Context.","ERROR",MB_OK|MB_ICONEXCLAMATION);
		return FALSE;								// Return FALSE
	}

	if (!(PixelFormat=ChoosePixelFormat(hDC,&pfd)))	// Did Windows Find A Matching Pixel Format?
	{
		KillGLWindow();								// Reset The Display
		MessageBox(NULL,"Can't Find A Suitable PixelFormat.","ERROR",MB_OK|MB_ICONEXCLAMATION);
		return FALSE;								// Return FALSE
	}

	if(!SetPixelFormat(hDC,PixelFormat,&pfd))		// Are We Able To Set The Pixel Format?
	{
		KillGLWindow();								// Reset The Display
		MessageBox(NULL,"Can't Set The PixelFormat.","ERROR",MB_OK|MB_ICONEXCLAMATION);
		return FALSE;								// Return FALSE
	}

	if (!(hRC=wglCreateContext(hDC)))				// Are We Able To Get A Rendering Context?
	{
		KillGLWindow();								// Reset The Display
		MessageBox(NULL,"Can't Create A GL Rendering Context.","ERROR",MB_OK|MB_ICONEXCLAMATION);
		return FALSE;								// Return FALSE
	}

	if(!wglMakeCurrent(hDC,hRC))					// Try To Activate The Rendering Context
	{
		KillGLWindow();								// Reset The Display
		MessageBox(NULL,"Can't Activate The GL Rendering Context.","ERROR",MB_OK|MB_ICONEXCLAMATION);
		return FALSE;								// Return FALSE
	}

	ShowWindow(hWnd,SW_SHOW);						// Show The Window
	SetForegroundWindow(hWnd);						// Slightly Higher Priority
	SetFocus(hWnd);									// Sets Keyboard Focus To The Window
	ReSizeGLScene(width, height);					// Set Up Our Perspective GL Screen

	if (!InitGL())									// Initialize Our Newly Created GL Window
	{
		KillGLWindow();								// Reset The Display
		MessageBox(NULL,"Initialization Failed.","ERROR",MB_OK|MB_ICONEXCLAMATION);
		return FALSE;								// Return FALSE
	}

	return TRUE;									// Success
}

LRESULT CALLBACK WndProc(	HWND	hWnd,			// Handle For This Window
							UINT	uMsg,			// Message For This Window
							WPARAM	wParam,			// Additional Message Information
							LPARAM	lParam){
	switch (uMsg)									// Check For Windows Messages
	{
		case WM_ACTIVATE:							// Watch For Window Activate Message
		{
			if (!HIWORD(wParam))					// Check Minimization State
			{
				active=TRUE;						// Program Is Active
			}
			else
			{
				active=FALSE;						// Program Is No Longer Active
			}

			return 0;								// Return To The Message Loop
		}

		case WM_SYSCOMMAND:							// Intercept System Commands
		{
			switch (wParam)							// Check System Calls
			{
				case SC_SCREENSAVE:					// Screensaver Trying To Start?
				case SC_MONITORPOWER:				// Monitor Trying To Enter Powersave?
				return 0;							// Prevent From Happening
			}
			break;									// Exit
		}

		case WM_CLOSE:								// Did We Receive A Close Message?
		{
			PostQuitMessage(0);						// Send A Quit Message
			return 0;								// Jump Back
		}

		case WM_KEYDOWN:							// Is A Key Being Held Down?
		{
			keys[wParam] = TRUE;					// If So, Mark It As TRUE
			return 0;								// Jump Back
		}

		case WM_KEYUP:								// Has A Key Been Released?
		{
			keys[wParam] = FALSE;					// If So, Mark It As FALSE
			return 0;								// Jump Back
		}

		case WM_SIZE:								// Resize The OpenGL Window
		{
			ReSizeGLScene(LOWORD(lParam),HIWORD(lParam));  // LoWord=Width, HiWord=Height
			return 0;								// Jump Back 
		}
	}


	return DefWindowProc(hWnd,uMsg,wParam,lParam);
	//+++++++--------33++323234562500000000
}

//int WINAPI WinMain(	HINSTANCE	hInstance,			// Instance
//					HINSTANCE	hPrevInstance,		// Previous Instance
//					LPSTR		lpCmdLine,			// Command Line Parameters
//					int			nCmdShow)			// Window Show State

int main()					
{
	MSG		msg;									// Windows Message Structure
	BOOL	done=FALSE;								// Bool Variable To Exit Loop  nnnnnmmmmmmmmmmmm

	// Ask The User Which Screen Mode They Prefer
//	if (MessageBox(NULL,"Would You Like To Run In Fullscreen Mode?", "Start FullScreen?",MB_YESNO|MB_ICONQUESTION)==IDNO)
	//{
		fullscreen=FALSE;							// Windowed Mode
	//}

	// Create Our OpenGL Window
	if (!CreateGLWindow("Graphics Project",1350,690,16,fullscreen))
	{
		return 0;									// Quit If Window Was Not Created
	}

	while(!done)									// Loop That Runs While done=FALSE
	{
		if (PeekMessage(&msg,NULL,0,0,PM_REMOVE))	// Is There A Message Waiting?
		{
			if (msg.message==WM_QUIT)				// Have We Received A Quit Message?
			{
				done=TRUE;							// If So done=TRUE
			}
			else									// If Not, Deal With Window Messages
			{
				TranslateMessage(&msg);				// Translate The Message
				DispatchMessage(&msg);				// Dispatch The Message
			}
		}
		else										// If There Are No Messages
		{
			// Draw The Scene.  Watch For ESC Key And Quit Messages From DrawGLScene()the main 
			if (active)								// Program Active?
			{
				if (keys[VK_ESCAPE])				// Was ESC Pressed?
				{
					done=TRUE;						// ESC Signalled A Quit
				}
				else								// Not Time To Quit, Update Screen
				{
					DrawGLScene();					// Draw The Scene
					SwapBuffers(hDC);				// Swap Buffers (Double Buffering)
				}
			}

			if (keys[VK_F1])						// Is F1 Being Pressed?
			{
				keys[VK_F1]=FALSE;					// If So Make Key FALSE
				KillGLWindow();						// Kill Our Current Window
				fullscreen=!fullscreen;				// Toggle Fullscreen / Windowed Mode
				// Recreate Our OpenGL Window
				if (!CreateGLWindow("Emad",700,500,16,fullscreen))
				{
					return 0;						// Quit If Window Was Not Created
				}

			}
		}
	}

	// Shutdown
	KillGLWindow();									// Kill The Window
	return (msg.wParam);							// Exit The Program
}