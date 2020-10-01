#pragma once

#include "gl_core_3_3.h"
#include <QGLWidget>
#include <QMouseEvent>
#include <QKeyEvent>
#include <QVector3D>
#include <vector>
#include <glm/gtc/type_ptr.hpp>

#include "Camera.h"
#include "Building.hpp"
#include "CowMesh.hpp"
#include "WallMesh.hpp"
#include "TextureMapping.h"

#include "parser.h"

using namespace std;

extern Building* bldg;
extern Camera* camera;

class GLWidget3D : public QGLWidget
{
public:
	GLWidget3D();
	GLWidget3D(const QGLFormat& fmt);
	~GLWidget3D();

	void connectParser();

	void loadOBJ(const QString& filename);
	void loadScene();

	//Reading File and Functions
	void readTxt(const QString& filename);

	//vector<GLuint> BVAO;		// Vertex array object for building
	//vector<GLsizei> BVCOUNT;		// Vertex array object for building

	void keyReleaseEvent(QKeyEvent *e) override;

	//shaders
	GLuint buildingShader0; //for 3D building
	//GLuint buildingShader1; //for 3D building
	GLuint uniXform;	//3D building
	GLuint uniDepth;
	GLuint uniBuildingOutline;
	GLuint uniBuildingColor;
	GLuint texUnitLocation;
	GLuint textureCounter;
	GLuint uniColorMode; //y
	GLuint uniTexMode; //y
	GLuint texDemo; //y


	

protected:
	void initializeGL();
	void resizeGL(int width, int height);
	void paintGL();    
	void mousePressEvent(QMouseEvent *e) override ;
	void mouseMoveEvent(QMouseEvent *e) override;
	void mouseReleaseEvent(QMouseEvent *e) override;
	
	void wheelEvent(QWheelEvent *e) override;
	
	std::vector<string> txtFile;

	//void drawOutline(int route); //draw outline function

		

private:
	
	
	//unsigned int boxVAO;
	//unsigned int boxVBO;

	// Bounding box
	glm::vec3 minBB;
	glm::vec3 maxBB;

	//this affects the translation
	float dx;
	float dy;
	float dz;

	
	//WallMesh wallMeshObj;
	std::unique_ptr<CowMesh> cow_mesh;
	std::unique_ptr<WallMesh> wall_mesh;
	std::unique_ptr<Building> building_mesh;



};

