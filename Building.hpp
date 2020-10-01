#pragma once

#include "BuildingBlock.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "gl_core_3_3.h"
#include <vector>
#include <iterator>
#include <memory>
#include <string>
#include <utility>
#include <iostream>
#include <cmath>
#include <ctime>
#include <random>
#include <Utility.h>

using namespace std;

class Building
{
public:
	Building();
	~Building() {}

	GLuint vaoFace; //vao is the coordinates
	GLuint vaoOutline;
	GLuint eboFace; //ebo refers to indice
	GLuint eboOutline;
	GLuint vbuf; //buffer
	vec3 buildingColor;
	vec3 buildingColorOutline;

	// List of all building blocks in building
	vector<BuildingBlock*> blockList;

	// Building's bounding box values
	float xmax, xmin, ymax, ymin, zmax, zmin;


	void createBox(string name, string type, float pos_x, float pos_z, float pos_y, float length, float width, float height);

	void makeVertexArrayObj();

	void makeGround();

	////////////////////////
	// MERGE FUNCTIONALITY

	// Counter for how many vertices overlap per adjacencySearch.
	// Resets every adjacencySearch.
	int overlapCount = 0;
	vector<int> block1OverlappingFaces;
	vector<int> block2OverlappingFaces;

	void merge(string name, string obj1, string obj2);
	void coplanarSearch(BuildingBlock * block1, BuildingBlock * block2, string name);
	void adjacencySearch(BuildingBlock * block1, BuildingBlock * block2, vector<int> face1, vector<int> face2, string name, string axis, int face1Index, int face2Index);
	void axisX(BuildingBlock * block1, BuildingBlock * block2, vector<int> face1, vector<int> face2, int i, int j);
	void axisY(BuildingBlock * block1, BuildingBlock * block2, vector<int> face1, vector<int> face2, int i, int j);
	void axisZ(BuildingBlock * block1, BuildingBlock * block2, vector<int> face1, vector<int> face2, int i, int j);
	void getMergedBoundingBox(vector<boxStruct> mergedBoxCoordinates);
	vector<vector<int>> restructureFaces(vector<vector<int>> faces);

	// END MERGE FUNCTIONALITY
	///////////////////////////


	////////////////////////////
	// SPLIT FUNCTIONALITY

	void blockSplit(string blockName, string axis, float percentage);			// No longer in development:
	vector<vec3> blockGetNewCoordsX(BuildingBlock * block, float offset);		//
	vector<vec3> blockGetNewCoordsY(BuildingBlock * block, float offset);		//
	vector<vec3> blockGetNewCoordsZ(BuildingBlock * block, float offset);		//
	void multiBlockSplit(BuildingBlock * block, string axis, int numOfSplits);	//

	void surfaceSplit(string faceName1, string faceName2, string blockName, string faceName, string axis, float percentage);
	void surfaceSplit(string faceName1, string faceName2, string groupName, string blockName, string faceName, string axis, float percentage);
	void surfaceGetNewCoordsX(BuildingBlock * block, float offset, int faceIndex);
	void surfaceGetNewCoordsY(BuildingBlock * block, float offset, int faceIndex);
	void surfaceGetNewCoordsZ(BuildingBlock * block, float offset, int faceIndex);

	// END SPLIT FUNCTIONALITY
	////////////////////////////

	////////////////////////////
	// MAKE GROUP FUNCTIONALITY

	// List of groups by name
	vector<string> groupNames;		// NOTE: Retrieve the index from here to access the vectors below:
	vector<BuildingBlock*> groupBlocks; // Each group made has a vector<BuildingBlock*> holding all render data about that group.
	vector<vector<string>> groupMembers; 	// Each group made has a vector<string> holding all members.
	vector<vector<int>> groupMemberFaceCount;
	
	// Not parallel
	vector<string> blockNames; // This can be changed to a vector<vector<string>> if necessary

	/*
	groupNames and groupMembers are parralel.
	groupNames[i=0] names of groups - returns string
	groupMembers[i] collection of members - returns vector<string>
	groupMembers[i][j] Specific Member of groupMembers[i] - returns string
	groupBlocks[i] render data for group - returns BuildingBlock*
	
	groupNames[0] --> "tower"
	groupNames[1] --> "factory"
	groupMembers[0][0] --> "ground"
	groupMembers[0] --> vector<string> towerMembers
	groupBlocks[0] --> BuildingBlock* towerRenderData
	groupBlocks[0][0] --> Does not exist
	groupBlocks[1] --> BuildingBlock* factoryRenderData
	*/

	void makeGroup(string groupName);
	void groupInsert(string groupName, string blockName);
	int getGroupIndex(string groupName);
	void updateBlockData(string blockName, BuildingBlock* groupData);


	// END MAKE GROUP FUNCTIONALITY
	////////////////////////////

	////////////////////////////
	// MISC UTILITIES

	void setTexture(string blockName, string faceName, string texture);

	BuildingBlock* getBuildingBlock(string blockName);
	int getFaceIndex(int groupIndex, string blockName, string faceName);
	int getFaceIndex(BuildingBlock* block, string faceName);
	int getFaceIndex(BuildingBlock* block, string faceName, int startingIndex);
	void setColor(string groupBlock, string blockName, string faceName, float r, float g, float b);
	void Building::colorGroup(string groupName, string faceName, float r, float g, float b);
	void setName(string newFaceName, string blockName, string faceName);
	void setBoundingBox(BuildingBlock * block1, BuildingBlock * block2);
	void setBoundingBox(vector<boxStruct> boxCoordinates);

	// BuildingBlock data log:
	void printCoords(vector<boxStruct> boxCoordinates);
	void printIndices(vector<int> boxIndices);
	void printFaceNames(vector<string> faceNames);

	// END MISC UTILITIES
	///////////////////////////

protected:
	void release(GLuint vao, GLuint vbuf);		//Release OpenGL resources

	// Bounding box
	glm::vec3 minBB1;
	glm::vec3 maxBB1;


	//std::unique_ptr<ReaderBox> box_mesh;
};



