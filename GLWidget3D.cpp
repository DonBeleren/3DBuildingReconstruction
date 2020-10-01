#include <iostream>
#include <string>    //d
#include <fstream>   //d
#include <sstream>   //d 

#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/transform.hpp>
#include "GLWidget3D.h"
#include "util.hpp"
#include "MainWindow.h"
#include "stb_image.h"

Building* bldg;
Camera* camera;
TextureMapping* texture;


GLWidget3D::GLWidget3D() {
//read from parser
}

GLWidget3D::GLWidget3D(const QGLFormat& fmt) : QGLWidget(fmt) {

	buildingShader0 = 0;
	uniXform = 0;
	uniColorMode = false; //y
	uniTexMode = false;//y

	//building
	dx = 0.0;	//translation features
	dy = 0.0;
	dz = 0.0;

}
GLWidget3D::~GLWidget3D() {
	if (buildingShader0) { glDeleteProgram(buildingShader0); buildingShader0 = 0; }
}

/**
 * This event handler is called when the mouse press events occur.
 */
void GLWidget3D::mousePressEvent(QMouseEvent *e)
{
	camera->mouseDown(e->x(), e->y());
}

/**
 * This event handler is called when the mouse release events occur.
 */
void GLWidget3D::mouseReleaseEvent(QMouseEvent *e)
{
	camera->mouseUp();
	//camera.z = camera.z + 3.0f;

	updateGL();
}

void GLWidget3D::wheelEvent(QWheelEvent *e)
{
	if (e->angleDelta().y() > 0) {
		camera->z = camera->z - 10.0f;
	}
	else if (e->angleDelta().y() < 0) {
		camera->z = camera->z + 10.0f;
	}
	updateGL(); 
}

void GLWidget3D::keyReleaseEvent(QKeyEvent *e)
{
	//cout << "key event open" << endl;
	//does nothing
	if (e->key() == Qt::Key_W) {
		camera->y = camera->y - 4.0;
	}
	else if (e->key() == Qt::Key_A) {
		camera->x = camera->x + 4.0;
	}
	else if (e->key() == Qt::Key_S) {
		camera->y = camera->y + 4.0;
	}
	else if (e->key() == Qt::Key_D) {
		camera->x = camera->x - 4.0;
	}
	else {
		cout << "error with keyReleaseEvent" << endl;
	}
	updateGL();
}

void GLWidget3D::mouseMoveEvent(QMouseEvent *e)
{
	if (e->buttons() & Qt::LeftButton) {
		camera->rotate(e->x(), e->y());
	} else if (e->buttons() & Qt::RightButton) {
		camera->zoom(e->x(), e->y());
	}
	updateGL(); //use?
}


/**
 * This function is called once before the first call to paintGL() or resizeGL().
 */
void GLWidget3D::initializeGL() {
	
	buildingShader0 = texture->initializationGLStuff( buildingShader0, uniXform);
	bldg = new Building();
	camera = new Camera();

	
}

/**
 * This function is called whenever the widget has been resized.
 */
void GLWidget3D::resizeGL(int width, int height)
{
	 
	height = height?height:1;

	camera->setWindowSize(width, height);
	//camera.setWindowSize(300, 300); //this doesnt make a difference

	//glViewport(0, 0, (GLint)300, (GLint)300);
	glViewport( 0, 0, (GLint)width, (GLint)height );
}

/**
 * This function is called whenever the widget needs to be painted.
 */
void GLWidget3D::paintGL()
{
	//texture->textureMain(buildingShader0, texUnitLocation, textureCounter);
	float w = width();
	float h = height();
	texture->paintGLStuff(w, h, buildingShader0, uniXform, uniTexMode, uniColorMode, texDemo, texUnitLocation, textureCounter);
}

/**
 * Load an OBJ file and create the corresponding VAO.
 */
void GLWidget3D::loadOBJ(const QString& filename)
{
	std::unique_ptr<CowMesh> mesh2;//this creates temporary data in same type as cow_mesh
	try {
		mesh2.reset(new CowMesh(filename.toStdString())); //CowMesh is the constructor of
	} catch (const exception& e) {
		cerr << e.what() << endl;
		return;
	}
	cow_mesh = std::move(mesh2);
}

/**
 * Load Vertice and create the corresponding VAO.
 */
void GLWidget3D::loadScene()
{
	building_mesh.reset(new Building()); //this sets all the data of WallMesh to wall_mesh

}

/**
 * file reading and functions.
 */
void GLWidget3D::readTxt(const QString & filename) //& for performance reasons
{

	string line;
	ifstream myfile(filename.toStdString());
	if (myfile.is_open())
	{
		while (getline(myfile, line))
		{
			cout << line << '\n';
			//store the txt into an array of strings
			txtFile.push_back(line);

			
		}
		myfile.close();
		wall_mesh->readWallTxt(txtFile); //this sends it to wall mesh

	}
	else cout << "Unable to open file" << std::endl;
	//return 0; dont need this

	//find the fFloorNum(int num);
	//then call split commands by colon
	//how is text file being read.
}

void GLWidget3D::connectParser() {
	//bisonFlex
	FILE *fp = fopen("Facade.txt", "r"); //whats the r
	if (!fp) {
		std::cout << "file could not open" << std::endl;
	}
	extern FILE *yyin;
	yyin = fp; //sets to read from file rather than STDIN
	std::cout << "Starting yyparse()..." << std::endl;
	yyparse();//parse through the input
	std::cout << "Exiting yyparse()..." << std::endl;
	fclose(fp);
}
