#include "Building.hpp"
#include "GLWidget3D.h"

using namespace std;
using namespace glm;

bool faceFound = false;

// Debugging Locks:
bool mergeLock = false;
bool surfaceSplitLock = false;
bool groupLock = false;
bool groupDataLock = false;
bool colorDataLock = false;
bool diffOffsetLock = false;
bool texCoordLock = false;
bool faceBoxCoordLock = false;
bool superLock = false;

// MERGE GLOBALS----------------------
vector<string> mergedFaceNames;
vector<vector<int>> mergedFaces;
vector<boxStruct> mergedBoxCoordinates;
vector<float> mergedBoundingBox; // xmin, xmax, ymin, ymax, zmin, zmax
vector<string> faceNames;
// END MERGE GLOBALS------------------

// SPLIT GLOBALS----------------------
// END SPLIT GLOBALS------------------

// MAKE GROUP GLOBALS-----------------
// END MAKE GROUP GLOBALS-------------

Building::Building() {

	vaoFace = 0;
	eboFace = 0;
	vbuf = 0;

	buildingColor = glm::vec3(0.9f, 0.04f, 0.1f); //red
	//buildingColorOutline = glm::vec3(0.9f, 0.3f, 0.1f);

	//debug
	//createBox("Obj1", "obj", 0, 0, 0, 3, 2, 5);

	// Release resources
	release(vaoFace, vbuf);

}

void Building::createBox(string name, string type, float pos_x, float pos_z, float pos_y, float length, float width, float height) {

	// Create building block and store in block list for future reference
	BuildingBlock * block = new BuildingBlock(name, type, pos_x, pos_z, pos_y, length, width, height); //building block pointer
	//BuildingBlock block(name, type, pos_x, pos_z, pos_y, length, width, height); //regualr object

	// Modify building BoundingBox in a Building function
	/*if (bldg->xmax < block->xmax) {
		bldg->xmax = block->xmax;
	}*/
	blockList.push_back(block);

}

//GLuint vao, GLuint ebo, GLuint vbufy, vector<boxStruct> coordinates, std::vector<int> indices
void Building::makeVertexArrayObj() {
	// Load vertices into OpenGL
	//glGenVertexArrays(1, &vao);
	//glBindVertexArray(vao);
	//glGenBuffers(1, &vbufy);
	//glBindBuffer(GL_ARRAY_BUFFER, vbufy);
	//glBufferData(GL_ARRAY_BUFFER, coordinates.size() * sizeof(coordinates[0]), coordinates.data(), GL_STATIC_DRAW); //send the data
	//glEnableVertexAttribArray(0); //size may need to be 3 instead of 2
	//glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(boxStruct), NULL); //0 is location 1
	//glEnableVertexAttribArray(1); //1 is location2
	//glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(boxStruct), (GLvoid*)offsetof(boxStruct, boxNorm)); //(GLvoid*)sizeof(vec3)
	////glVertexAttribPointer(GLuint index, GLint size, GLenum type, GLboolean normalized, GLsizei stride, const void * pointer);
	//glGenBuffers(1, &ebo);
	//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo); //element array buffer gives the order for the vertices
	//glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(indices[0]), indices.data(), GL_STATIC_DRAW);
	//glBindVertexArray(NULL);
	//glBindBuffer(GL_ARRAY_BUFFER, NULL);


	//makeVertexArrayObj(vaoFace, eboFace, vbuf, boxCoordinates, boxIndices);
	// Load vertices into OpenGL
	glGenVertexArrays(1, &vaoFace);
	glBindVertexArray(vaoFace);

	glGenBuffers(1, &vbuf);
	glBindBuffer(GL_ARRAY_BUFFER, vbuf);
	//glBufferData(GL_ARRAY_BUFFER, bldg->blockList[bldg->blockList.size()-1]->boxCoordinates.size() * sizeof(boxStruct), bldg->blockList[bldg->blockList.size() - 1]->boxCoordinates.data(), GL_STATIC_DRAW);
	glBufferData(GL_ARRAY_BUFFER, bldg->blockList[bldg->blockList.size() - 1]->texCoords.size() * sizeof(boxStruct), bldg->blockList[bldg->blockList.size() - 1]->texCoords.data(), GL_STATIC_DRAW);

	glEnableVertexAttribArray(0); //Gluint size may need to be 3 instead of 2 for glVertexAttribPointer
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(boxStruct), NULL);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(boxStruct), (GLvoid*)offsetof(boxStruct, boxNorm)); //(GLvoid*)sizeof(vec3)
	
	glGenBuffers(1, &eboFace);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, eboFace);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, bldg->blockList[bldg->blockList.size() - 1]->texIndices.size() * sizeof(boxStruct), bldg->blockList[bldg->blockList.size() - 1]->texIndices.data(), GL_STATIC_DRAW);

	glBindVertexArray(NULL);
	glBindBuffer(GL_ARRAY_BUFFER, NULL);

	//glBindVertexArray(0);
	//glBindBuffer(GL_ARRAY_BUFFER, 0);
}
//void Building::makeVertexArrayObj() {
//	// Load vertices into OpenGL
//	//glGenVertexArrays(1, &vao);
//	//glBindVertexArray(vao);
//	//glGenBuffers(1, &vbufy);
//	//glBindBuffer(GL_ARRAY_BUFFER, vbufy);
//	//glBufferData(GL_ARRAY_BUFFER, coordinates.size() * sizeof(coordinates[0]), coordinates.data(), GL_STATIC_DRAW); //send the data
//	//glEnableVertexAttribArray(0); //size may need to be 3 instead of 2
//	//glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(boxStruct), NULL); //0 is location 1
//	//glEnableVertexAttribArray(1); //1 is location2
//	//glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(boxStruct), (GLvoid*)offsetof(boxStruct, boxNorm)); //(GLvoid*)sizeof(vec3)
//	////glVertexAttribPointer(GLuint index, GLint size, GLenum type, GLboolean normalized, GLsizei stride, const void * pointer);
//	//glGenBuffers(1, &ebo);
//	//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo); //element array buffer gives the order for the vertices
//	//glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(indices[0]), indices.data(), GL_STATIC_DRAW);
//	//glBindVertexArray(NULL);
//	//glBindBuffer(GL_ARRAY_BUFFER, NULL);
//
//
//	//makeVertexArrayObj(vaoFace, eboFace, vbuf, boxCoordinates, boxIndices);
//	// Load vertices into OpenGL
//	glGenVertexArrays(1, &vaoFace);
//	glBindVertexArray(vaoFace);
//
//	glGenBuffers(1, &vbuf);
//	glBindBuffer(GL_ARRAY_BUFFER, vbuf);
//	//glBufferData(GL_ARRAY_BUFFER, bldg->blockList[bldg->blockList.size()-1]->boxCoordinates.size() * sizeof(boxStruct), bldg->blockList[bldg->blockList.size() - 1]->boxCoordinates.data(), GL_STATIC_DRAW);
//	glBufferData(GL_ARRAY_BUFFER, bldg->blockList[bldg->blockList.size() - 1]->boxCoordinates.size() * sizeof(boxStruct), bldg->blockList[bldg->blockList.size() - 1]->boxCoordinates.data(), GL_STATIC_DRAW);
//
//	glEnableVertexAttribArray(0); //Gluint size may need to be 3 instead of 2 for glVertexAttribPointer
//	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(boxStruct), NULL);
//	glEnableVertexAttribArray(1);
//	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(boxStruct), (GLvoid*)offsetof(boxStruct, boxNorm)); //(GLvoid*)sizeof(vec3)
//
//	glGenBuffers(1, &eboFace);
//	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, eboFace);
//	glBufferData(GL_ELEMENT_ARRAY_BUFFER, bldg->blockList[bldg->blockList.size() - 1]->boxIndices.size() * sizeof(boxStruct), bldg->blockList[bldg->blockList.size() - 1]->boxIndices.data(), GL_STATIC_DRAW);
//
//	glBindVertexArray(NULL);
//	glBindBuffer(GL_ARRAY_BUFFER, NULL);
//
//	//glBindVertexArray(0);
//	//glBindBuffer(GL_ARRAY_BUFFER, 0);
//}

// Release resources
void Building::release(GLuint vao, GLuint vbuf) {
	minBB1 = glm::vec3(numeric_limits<float>::max());
	maxBB1 = glm::vec3(numeric_limits<float>::lowest());

	if (vao) { glDeleteVertexArrays(1, &vao); vao = 0; }
	if (vbuf) { glDeleteBuffers(1, &vbuf); vbuf = 0; }
}

void Building::makeGround() {

}

// MERGE--------------------------------------------------------------------------------------------------

/*
	obj1: Name of object 1
	obj2: Name of object 2
	name: Name of resulting merged object
*/
void Building::merge(string name, string obj1, string obj2) {
	// Counter: When counter reaches 2, both objects for the merge have been found
	int c = 0;
	// Two BuildingBlock objects being merged:
	BuildingBlock * block1;
	BuildingBlock * block2;

	// Select the correct blocks to merge from the blocklist
	for (int i = 0; i < bldg->blockList.size(); i++) {
		if (bldg->blockList[i]->name == obj1) {
			block1 = bldg->blockList[i];
			c++;
		}
		else if (bldg->blockList[i]->name == obj2) {
			block2 = bldg->blockList[i];
			c++;
		}

		if (c == 2) {
			if (mergeLock) {
				cout << "Found two objects to merge." << endl;
			}
			break;
		}
	} // end for
	// If two objects have not been found, do not continue and report error:
	if (c != 2) {
		cout << "Error: Building.cpp->Building::merge - Not enough objects for merge found." << endl;
	}

	// Concatenation of both boxCoordinates into one vector:
	mergedBoxCoordinates = block1->boxCoordinates;
	mergedBoxCoordinates.insert(mergedBoxCoordinates.end(), block2->boxCoordinates.begin(), block2->boxCoordinates.end());

	// Update the bounding box of the entire building:
	setBoundingBox(block1, block2);

	// Find coplanar faces
	coplanarSearch(block1, block2, name);

	// Debugging:
	if (mergeLock) {
		cout << "BLOCK 1 OVERLAPS ------------------------" << endl;
		for (int i = 0; i < block1OverlappingFaces.size(); i++) {
			cout << "Face " << block1OverlappingFaces[i] << ":" << endl;
			cout << "Indices = (";
			for (int j = 0; j < block1->faces[block1OverlappingFaces[i]].size(); j++) {
				cout << block1->faces[block1OverlappingFaces[i]][j];
				if (j != block1->faces[block1OverlappingFaces[i]].size() - 1) {
					cout << ", ";
				}
			}
			cout << ")" << endl;
		}
		cout << "-----------------------------------------" << endl;
		cout << "BLOCK 2 OVERLAPS ------------------------" << endl;
		for (int i = 0; i < block2OverlappingFaces.size(); i++) {
			cout << "Face " << block2OverlappingFaces[i] << ":" << endl;
			cout << "Indices = (";
			for (int j = 0; j < block2->faces[block2OverlappingFaces[i]].size(); j++) {
				cout << (block2->faces[block2OverlappingFaces[i]][j] + 8);
				if (j != block2->faces[block2OverlappingFaces[i]].size() - 1) {
					cout << ", ";
				}
			}
			cout << ")" << endl;
		}
		cout << "-----------------------------------------" << endl;
	}

	// Concatenate boxIndices of both blocks into one vector:
	vector<int> boxIndices = block1->boxIndices;
	vector<int> block2Indice;
	for (int i = 0; i < block2->boxIndices.size(); i++) { // Offset from original indice
		int temp = block2->boxIndices[i] + block1->boxCoordinates.size();
		block2Indice.push_back(temp);
	}
	boxIndices.insert(boxIndices.end(), block2Indice.begin(), block2Indice.end());

	//Bounding Box
	getMergedBoundingBox(mergedBoxCoordinates);

	// Fill new faces with block1's faces, then add all of block2's faces via for-loop:
	vector<vector<int>> faces;

	if (mergeLock) {
		cout << "FACES BEFORE REMOVAL---------------------" << endl;
	}

	// Concatenate faces:
	for (int i = 0; i < boxIndices.size(); i = i + 6) {
		if (mergeLock) {
			cout << "Face " << faces.size() << ":" << endl;
		}
		vector<int> temp;
		temp.push_back(boxIndices[i]);
		temp.push_back(boxIndices[i + 1]);
		temp.push_back(boxIndices[i + 2]);
		temp.push_back(boxIndices[i + 3]);
		temp.push_back(boxIndices[i + 4]);
		temp.push_back(boxIndices[i + 5]);
		faces.push_back(temp);
		if (mergeLock) {
			cout << "Indices = (" << temp[0] << ", " << temp[1] << ", " << temp[2] << ", " << temp[3] << ", " << temp[4] << ", " << temp[5] << ")" << endl;
		}
	}

	// Concatenate faceNames:
	faceNames = block1->faceNames;
	for (int i = 0; i < block2->faceNames.size(); i++) {
		faceNames.push_back(block2->faceNames[i]);
	}

	if (mergeLock) {
		cout << "Face Names:" << endl;
		for (int i = 0; i < faceNames.size(); i++) {
			cout << faceNames[i] << endl;
		}
	}

	if (mergeLock) {
		cout << "-----------------------------------------" << endl;
		cout << "REMOVAL PROCESS--------------------------" << endl;
	}

	// Remove all faces being replaced by a merged face
	int offset = 0;
	int iCounter = faces.size();
	for (int i = 0; i < iCounter; i++) {

		// Debugging:
		if (mergeLock) {
			for (int j = 0; j < 50; j++) {
				cout << i;
			}
			cout << endl;
		}

		// Remove block1 faces:
		for (int j = 0; j < block1OverlappingFaces.size(); j++) {
			// Guilty until proven innocent:
			bool culpritFound = true;
			// Check every boxIndice of the current face
			for (int k = 0; k < faces[offset].size(); k++) {
				// If unidentical, then suspect face is innocent.
				if (faces[offset][k] != block1->faces[block1OverlappingFaces[j]][k]) {
					if (mergeLock) {
						cout << "Innocent====" << endl;
						cout << "Suspect Indices = (";
						for (int m = 0; m < faces[offset].size(); m++) {
							cout << faces[offset][m];
							if (m != faces[offset].size() - 1) {
								cout << ", ";
							}
						}
						cout << ")" << endl;
						cout << "Culprit Indices = (";
						for (int m = 0; m < block1->faces[block1OverlappingFaces[j]].size(); m++) {
							cout << block1->faces[block1OverlappingFaces[j]][m];
							if (m != block1->faces[block1OverlappingFaces[j]].size() - 1) {
								cout << ", ";
							}
						}
						cout << ")" << endl;

						cout << "============" << endl;
					}

					culpritFound = false;
					break; // leave k
				}
			} // end k

			//Verdict:
			if (!culpritFound) {
				continue; // stay in j
			}
			else {
				if (mergeLock) {
					cout << "Guilty%%%%%%" << endl;
					cout << "Indices = (";
					for (int m = 0; m < faces[offset].size(); m++) {
						cout << faces[offset][m];
						if (m != faces[offset].size() - 1) {
							cout << ", ";
						}
					}
					cout << ")" << endl;
					cout << "%%%%%%%%%%%%" << endl;
				}
				faceNames.erase(faceNames.begin() + offset);
				faces.erase(faces.begin() + offset);
				faceFound = true;
				break;
			}

		} // end j
		if (faceFound) {
			faceFound = false;
			continue;
		}
		// Remove block2 faces:
		for (int j = 0; j < block2OverlappingFaces.size(); j++) {
			// Guilty until proven innocent:
			bool culpritFound = true;
			// Check every boxIndice of the current face
			for (int k = 0; k < faces[offset].size(); k++) {
				// If unidentical, then face is innocent.
				if (faces[offset][k] != block2->faces[block2OverlappingFaces[j]][k] + 8) {

					if (mergeLock) {
						cout << "Innocent====" << endl;
						cout << "Suspect Indices = (";
						for (int m = 0; m < faces[offset].size(); m++) {
							cout << faces[offset][m];
							if (m != faces[offset].size() - 1) {
								cout << ", ";
							}
						}
						cout << ")" << endl;
						cout << "Culprit Indices = (";
						for (int m = 0; m < block2->faces[block2OverlappingFaces[j]].size(); m++) {
							cout << block2->faces[block2OverlappingFaces[j]][m] + 8;
							if (m != block2->faces[block2OverlappingFaces[j]].size() - 1) {
								cout << ", ";
							}
						}
						cout << ")" << endl;
						cout << "============" << endl;
					}

					culpritFound = false;
					break; // leave k
				}
			} // end k

			// Verdict:
			if (!culpritFound) {
				continue; // stay in j
			}
			else {
				if (mergeLock) {
					cout << "Guilty%%%%%%" << endl;
					cout << "Indices = (";
					for (int m = 0; m < faces[offset].size(); m++) {
						cout << faces[offset][m];
						if (m != faces[offset].size() - 1) {
							cout << ", ";
						}
					}
					cout << ")" << endl;
					cout << "%%%%%%%%%%%%" << endl;
				}
				faceNames.erase(faceNames.begin() + offset);
				faces.erase(faces.begin() + offset);
				faceFound = true;
				break;
			}

		} // end j
		if (faceFound) {
			faceFound = false;
			continue;
		}

		// If we reach the end of the for loop, this face did not need to be removed.
		offset++;
	} // end face removal

	if (mergeLock) {
		cout << "-----------------------------------------" << endl;
		cout << "FACES AFTER REMOVAL----------------------" << endl;
		for (int i = 0; i < faces.size(); i++) {
			cout << "Face " << i << ":" << endl;
			cout << "Indices = (";
			for (int j = 0; j < faces[i].size(); j++) {
				cout << faces[i][j];
				if (j != faces[i].size() - 1) {
					cout << ", ";
				}
			}
			cout << ")" << endl;
		}
		cout << "Face Names:" << endl;
		for (int i = 0; i < faceNames.size(); i++) {
			cout << faceNames[i] << endl;
		}
		cout << "-----------------------------------------" << endl;
	}


	// Add mergedFaces to faces
	for (int i = 0; i < mergedFaces.size(); i++) {
		faceNames.push_back(mergedFaceNames[i]);
		faces.push_back(mergedFaces[i]);
	}

	if (mergeLock) {
		cout << "AFTER ADDING MERGED FACES----------------" << endl;
		for (int i = 0; i < faces.size(); i++) {
			cout << "Face " << i << ":" << endl;
			cout << "Indices = (";
			for (int j = 0; j < faces[i].size(); j++) {
				cout << faces[i][j];
				if (j != faces[i].size() - 1) {
					cout << ", ";
				}
			}
			cout << ")" << endl;
		}
		cout << "Face Names:" << endl;
		for (int i = 0; i < faceNames.size(); i++) {
			cout << faceNames[i] << endl;
		}
		cout << "-----------------------------------------" << endl;
	}


	// Restructuring faces:
	vector<vector<int>> tempFaces = restructureFaces(faces);
	faces.clear();
	faces = tempFaces;

	if (mergeLock) {
		cout << "AFTER RESTRUCTURE------------------------" << endl;
		for (int i = 0; i < faces.size(); i++) {
			cout << "Face " << i << ":" << endl;
			cout << "Indices = (";
			for (int j = 0; j < faces[i].size(); j++) {
				cout << faces[i][j];
				if (j != faces[i].size() - 1) {
					cout << ", ";
				}
			}
			cout << ")" << endl;
		}
		cout << "Face Names:" << endl;
		for (int i = 0; i < faceNames.size(); i++) {
			cout << faceNames[i] << endl;
		}
		cout << "-----------------------------------------" << endl;
	}

	// Texturing formatting:
	std::vector<boxStruct> texCoords;
	struct boxStruct coordinate;

	// bot,  back, right, front, left, top
	// blue, green, cyan,  red,  pink, yellow, white, black, 
	std::vector<vec3> colorMap = {
		vec3(0, 0 ,1), vec3(0, 1 ,0),
		vec3(0, 1 ,1), vec3(1, 0 ,0),
		vec3(1, 0 ,1), vec3(1, 1 ,0),
		vec3(1, 1, 1), vec3(0, 0, 0),
		vec3(.5,.5,0), vec3(.7,0,.7),
		vec3(.2,0,0), vec3(0, .5,.6),
		vec3(.1,.7,.8)
	};
	for (int i = 0; i < faces.size(); i++) { // Runs through faces
		for (int j = 0; j < faces[i].size(); j++) {
			coordinate.boxPos = mergedBoxCoordinates[faces[i][j]].boxPos; //boxCoordinates[indice value]
			coordinate.boxNorm = colorMap[i];
			texCoords.push_back(coordinate);
		}
	}
	vector<int> texIndices;
	for (int i = 0; i < texCoords.size(); i++) {
		texIndices.push_back(i);
	}

	/*int tempCounter = 0;
	for (int i = 0; i < texCoords.size(); i++) {
		if (i % 6 == 0) {
			tempCounter++;
			cout << "Face " << tempCounter << ":" << endl;
		}
		cout << "TexCoordinate: " << i <<" = ("<< texCoords[i].boxPos.x << ", "<< texCoords[i].boxPos.y<< ", " << texCoords[i].boxPos.z <<")" <<endl;
	}*/

	// Resulting merged block:
	BuildingBlock * block = new BuildingBlock(name, faces, boxIndices, mergedBoxCoordinates, texCoords, texIndices); //building block pointer

	blockList.push_back(block);

} // End: merge

void Building::coplanarSearch(BuildingBlock * block1, BuildingBlock * block2, string name) {
	// Temp storage for faces in adjacencySearch:
	vector<int> face1, face2;
	// Axis that adjacencySearch will be performed on:
	string axis = "";

	// Traverse over every combination of faces paired from the two blocks.
	// Perform adjacencySearch on pairs that are coplanar.
	for (int i = 0; i < block1->faces.size(); i++) {
		for (int j = 0; j < block2->faces.size(); j++) {
			// For each face, obtain 2 vectors that define the face. Calculate their cross product.
			// Normalize the cross products and compare them. If they are equal, perform adjacencySearch.

			// Face 1 Cross Product Calculation:
			vec3 face1First = vec3(block1->boxCoordinates[block1->faces[i][1]].boxPos - block1->boxCoordinates[block1->faces[i][0]].boxPos);
			vec3 face1Second = vec3(block1->boxCoordinates[block1->faces[i][2]].boxPos - block1->boxCoordinates[block1->faces[i][0]].boxPos);
			vec3 cross1 = glm::cross(face1First, face1Second);
			cross1 = glm::normalize(cross1);

			// Face 2 Cross Product Calculation:
			vec3 face2First = vec3(block2->boxCoordinates[block2->faces[j][1]].boxPos - block2->boxCoordinates[block2->faces[j][0]].boxPos);
			vec3 face2Second = vec3(block2->boxCoordinates[block2->faces[j][2]].boxPos - block2->boxCoordinates[block2->faces[j][0]].boxPos);
			vec3 cross2 = glm::cross(face2First, face2Second);
			cross2 = glm::normalize(cross2);

			// If cross products are equal, then do adjacencySearch on them.
			if (cross1 == cross2 || cross1 == -cross2) {
				face1 = block1->faces[i];
				face2 = block2->faces[j];

				// Identify what axis the faces are coplanar on:
				if (cross1.x != 0) {
					axis = "X";
				}
				else if (cross1.y != 0) {
					axis = "Y";
				}
				else if (cross1.z != 0) {
					axis = "Z";
				}

				adjacencySearch(block1, block2, face1, face2, name, axis, i, j);
			}
			/*else if (cross1 == -cross2) {

			}*/

		} // end j
	} // end i
} // end coplanarSearch

void Building::adjacencySearch(BuildingBlock * block1, BuildingBlock * block2, vector<int> face1, vector<int> face2, string name, string axis, int face1Index, int face2Index) {
	// Overlap Counter reset
	overlapCount = 0;
	// Coplanar faces are checked for adjacencies:
	// Traverse over every vertex of face1

	// (1, 0, 2, 2, 3, 1)

	for (int i = 0; i < face1.size(); i++) {
		if (i == 3 || i == 5) {
			continue;
		}

		// Traverse over every vertex of face2
		for (int j = 0; j < face2.size(); j++) {
			if (j == 3 || j == 5) {
				continue;
			}

			// Perform adjacencySearch based on the axis of interest
			if (axis == "X") {
				axisX(block1, block2, face1, face2, i, j);
			}
			else if (axis == "Y") {
				axisY(block1, block2, face1, face2, i, j);
			}
			else if (axis == "Z") {
				axisZ(block1, block2, face1, face2, i, j);
			}
		} // end j
	} // end i

	// Store data of C.A.F.s that need to be REMOVED:
	if (overlapCount == 2) {
		block1OverlappingFaces.push_back(face1Index); // 0
		block2OverlappingFaces.push_back(face2Index); // 0

		// Create the merged face
		vector<int> newFace;
		if (mergedBoxCoordinates[block2->faces[face2Index][0] + 8].boxPos == mergedBoxCoordinates[block1->faces[face1Index][1]].boxPos) {
			//first merge (back)
			newFace.push_back(block1->faces[face1Index][0]);
			newFace.push_back(block2->faces[face2Index][1] + 8);
			newFace.push_back(block2->faces[face2Index][2] + 8);
			newFace.push_back(block2->faces[face2Index][2] + 8);
			newFace.push_back(block1->faces[face1Index][4]);
			newFace.push_back(block1->faces[face1Index][0]);
			string newName = name + "back";
			mergedFaceNames.push_back(newName);
		}
		else {
			//second merge (bottom / top/ front )
			newFace.push_back(block2->faces[face2Index][0] + 8);
			newFace.push_back(block1->faces[face1Index][1]);
			newFace.push_back(block1->faces[face1Index][2]);
			newFace.push_back(block1->faces[face1Index][2]);
			newFace.push_back(block2->faces[face2Index][4] + 8);
			newFace.push_back(block2->faces[face2Index][0] + 8);

			// Bottom
			if (mergedBoxCoordinates[newFace[0]].boxPos.y == ymin && mergedBoxCoordinates[newFace[1]].boxPos.y == ymin && mergedBoxCoordinates[newFace[2]].boxPos.y == ymin && mergedBoxCoordinates[newFace[4]].boxPos.y == ymin) {
				string newName = name + "bottom";
				mergedFaceNames.push_back(newName);
			}
			if (mergedBoxCoordinates[newFace[0]].boxPos.y == ymax && mergedBoxCoordinates[newFace[1]].boxPos.y == ymax && mergedBoxCoordinates[newFace[2]].boxPos.y == ymax && mergedBoxCoordinates[newFace[4]].boxPos.y == ymax) {
				string newName = name + "top";
				mergedFaceNames.push_back(newName);
			}
			if (mergedBoxCoordinates[newFace[0]].boxPos.y == zmin && mergedBoxCoordinates[newFace[1]].boxPos.y == zmin && mergedBoxCoordinates[newFace[2]].boxPos.y == zmin && mergedBoxCoordinates[newFace[4]].boxPos.y == zmin) {
				string newName = name + "front";
				mergedFaceNames.push_back(newName);
			}

		}

		// Push merged face to mergedFaces
		mergedFaces.push_back(newFace);
	}
	else if (overlapCount == 4) {
		if (mergeLock) {
			cout << "Overlap = 4" << endl;
			cout << "Block1: ";
			for (int i = 0; i < block1->faces[face1Index].size(); i++) {
				cout << block1->faces[face1Index][i] << " ";
			}
			cout << endl;
			cout << "Block2: ";
			for (int i = 0; i < block2->faces[face2Index].size(); i++) {
				cout << block2->faces[face2Index][i] + 8 << " ";
			}
			cout << endl;
		}

		block1OverlappingFaces.push_back(face1Index); // 0
		block2OverlappingFaces.push_back(face2Index); // 0
	}

} // end void

void Building::axisX(BuildingBlock * block1, BuildingBlock * block2, vector<int> face1, vector<int> face2, int i, int j) {
	// Check if y and z values of paired vertices match:
			// Three cases
			// 1. y and z values match
			// 2. only y values match
			// 3. only z values match

	// May be y and z OR only y
	if (block1->boxCoordinates[face1[i]].boxPos.y == block2->boxCoordinates[face2[j]].boxPos.y) {
		// y and z values match
		if (block1->boxCoordinates[face1[i]].boxPos.z == block2->boxCoordinates[face2[j]].boxPos.z) {
			if (block1->boxCoordinates[face1[i]].boxPos.x == block2->boxCoordinates[face2[j]].boxPos.x) {
				// Keep track of how many pairs of vertices are in same location
				overlapCount++;
			}
		}
		// only y values match: DO NOTHING
		else {
			// Pair of vertices || z-axis
			// DO NOTHING
		}
	}
	// only z values match: DO NOTHING
	else if (block1->boxCoordinates[face1[i]].boxPos.z == block2->boxCoordinates[face2[j]].boxPos.z) {
		// Pair of vertices || y-axis
		// DO NOTHING
	} // end if else
}

void Building::axisY(BuildingBlock * block1, BuildingBlock * block2, vector<int> face1, vector<int> face2, int i, int j) {
	// Check if x and z values of paired vertices match:
			// Three cases
			// 1. x and z values match
			// 2. only x values match
			// 3. only z values match

	// May be x and z OR only x
	if (block1->boxCoordinates[face1[i]].boxPos.x == block2->boxCoordinates[face2[j]].boxPos.x) {
		// x and z values match
		if (block1->boxCoordinates[face1[i]].boxPos.z == block2->boxCoordinates[face2[j]].boxPos.z) {
			if (block1->boxCoordinates[face1[i]].boxPos.y == block2->boxCoordinates[face2[j]].boxPos.y) {
				// Keep track of how many pairs of vertices are in same location
				overlapCount++;
			}
		}
		// only x values match: DO NOTHING
		else {
			// Pair of vertices || z-axis
			// DO NOTHING
		}
	}
	// only z values match: DO NOTHING
	else if (block1->boxCoordinates[face1[i]].boxPos.z == block2->boxCoordinates[face2[j]].boxPos.z) {
		// Pair of vertices || x-axis
		// DO NOTHING
	} // end if else
}

void Building::axisZ(BuildingBlock * block1, BuildingBlock * block2, vector<int> face1, vector<int> face2, int i, int j) {
	// Check if x and y values of paired vertices match:
			// Three cases
			// 1. x and y values match
			// 2. only x values match
			// 3. only y values match

	// May be x and y OR only x
	if (block1->boxCoordinates[face1[i]].boxPos.x == block2->boxCoordinates[face2[j]].boxPos.x) {
		// x and y values match
		if (block1->boxCoordinates[face1[i]].boxPos.y == block2->boxCoordinates[face2[j]].boxPos.y) {
			if (block1->boxCoordinates[face1[i]].boxPos.z == block2->boxCoordinates[face2[j]].boxPos.z) {
				// Keep track of how many pairs of vertices are in same location
				overlapCount++;
			}
		}
		// only x values match: DO NOTHING
		else {
			// Pair of vertices || y-axis
			// DO NOTHING
		}
	}
	// only y values match: DO NOTHING
	else if (block1->boxCoordinates[face1[i]].boxPos.y == block2->boxCoordinates[face2[j]].boxPos.y) {
		// Pair of vertices || x-axis
		// DO NOTHING
	} // end if else
}

void Building::getMergedBoundingBox(vector<boxStruct> mergedBoxCoordinates) {
	// Iterate over all box coordinates and store the max/min of each axis
	for (int i = 0; i < mergedBoxCoordinates.size(); i++) {
		if (mergedBoundingBox.empty()) {
			mergedBoundingBox.push_back(mergedBoxCoordinates[i].boxPos.x);
			mergedBoundingBox.push_back(mergedBoxCoordinates[i].boxPos.x);
			mergedBoundingBox.push_back(mergedBoxCoordinates[i].boxPos.y);
			mergedBoundingBox.push_back(mergedBoxCoordinates[i].boxPos.y);
			mergedBoundingBox.push_back(mergedBoxCoordinates[i].boxPos.z);
			mergedBoundingBox.push_back(mergedBoxCoordinates[i].boxPos.z);
		}

		// X
		if (mergedBoxCoordinates[i].boxPos.x < mergedBoundingBox[0]) {
			mergedBoundingBox.erase(mergedBoundingBox.begin() + 0);
			mergedBoundingBox.insert(mergedBoundingBox.begin() + 0, mergedBoxCoordinates[i].boxPos.x);
		}
		if (mergedBoxCoordinates[i].boxPos.x > mergedBoundingBox[1]) {
			mergedBoundingBox.erase(mergedBoundingBox.begin() + 1);
			mergedBoundingBox.insert(mergedBoundingBox.begin() + 1, mergedBoxCoordinates[i].boxPos.x);
		}
		// Y
		if (mergedBoxCoordinates[i].boxPos.y < mergedBoundingBox[2]) {
			mergedBoundingBox.erase(mergedBoundingBox.begin() + 2);
			mergedBoundingBox.insert(mergedBoundingBox.begin() + 2, mergedBoxCoordinates[i].boxPos.y);
		}
		if (mergedBoxCoordinates[i].boxPos.y > mergedBoundingBox[3]) {
			mergedBoundingBox.erase(mergedBoundingBox.begin() + 3);
			mergedBoundingBox.insert(mergedBoundingBox.begin() + 3, mergedBoxCoordinates[i].boxPos.y);
		}
		// Z
		if (mergedBoxCoordinates[i].boxPos.z < mergedBoundingBox[4]) {
			mergedBoundingBox.erase(mergedBoundingBox.begin() + 4);
			mergedBoundingBox.insert(mergedBoundingBox.begin() + 4, mergedBoxCoordinates[i].boxPos.z);
		}
		if (mergedBoxCoordinates[i].boxPos.z > mergedBoundingBox[5]) {
			mergedBoundingBox.erase(mergedBoundingBox.begin() + 5);
			mergedBoundingBox.insert(mergedBoundingBox.begin() + 5, mergedBoxCoordinates[i].boxPos.z);
		}
	} // end i

	if (mergeLock) {
		cout << "\nMerged Block Bounds---" << endl;
		for (int i = 0; i < mergedBoundingBox.size(); i++) {
			cout << mergedBoundingBox[i] << ", ";
		}
		cout << endl;
		cout << "------------------------" << endl;
	}

}

vector<vector<int>> Building::restructureFaces(vector<vector<int>> faces) {
	vector<vector<int>> tempFaces = {
			{0},{0},{0},{0},{0},{0}
	};
	vector<string> tempFaceNames = { "a", "a", "a", "a", "a", "a" };
	for (int i = 0; i < faces.size(); i++) {//loops face
		//makes easier to read
		vector<vec3> faceCoord = {
			mergedBoxCoordinates[faces[i][0]].boxPos,
			mergedBoxCoordinates[faces[i][1]].boxPos,
			mergedBoxCoordinates[faces[i][2]].boxPos,
			mergedBoxCoordinates[faces[i][4]].boxPos
		};

		//Identifies which faces are assosiated with the bounding box
		//Any facecounter values that are four will be restructured after
		vector<int> faceCounters = { 0,0,0,0,0,0 };//holds same structure as mergedBoundingBox
		//for (int n = 0; n < mergedBoundingBox.size(); n++) {//this loops through bounding box values
		if (faceCoord[0].x == mergedBoundingBox[0] && faceCoord[1].x == mergedBoundingBox[0] && faceCoord[2].x == mergedBoundingBox[0] && faceCoord[3].x == mergedBoundingBox[0]) {
			tempFaces.erase(tempFaces.begin() + 4);
			tempFaces.insert(tempFaces.begin() + 4, faces[i]);
			tempFaceNames.erase(tempFaceNames.begin() + 4);
			tempFaceNames.insert(tempFaceNames.begin() + 4, faceNames[i]);
		}
		else if (faceCoord[0].x == mergedBoundingBox[1] && faceCoord[1].x == mergedBoundingBox[1] && faceCoord[2].x == mergedBoundingBox[1] && faceCoord[3].x == mergedBoundingBox[1]) {
			tempFaces.erase(tempFaces.begin() + 2);
			tempFaces.insert(tempFaces.begin() + 2, faces[i]);
			tempFaceNames.erase(tempFaceNames.begin() + 2);
			tempFaceNames.insert(tempFaceNames.begin() + 2, faceNames[i]);
		}
		else if (faceCoord[0].y == mergedBoundingBox[2] && faceCoord[1].y == mergedBoundingBox[2] && faceCoord[2].y == mergedBoundingBox[2] && faceCoord[3].y == mergedBoundingBox[2]) {
			tempFaces.erase(tempFaces.begin() + 0);
			tempFaces.insert(tempFaces.begin() + 0, faces[i]);
			tempFaceNames.erase(tempFaceNames.begin() + 0);
			tempFaceNames.insert(tempFaceNames.begin() + 0, faceNames[i]);
		}
		else if (faceCoord[0].y == mergedBoundingBox[3] && faceCoord[1].y == mergedBoundingBox[3] && faceCoord[2].y == mergedBoundingBox[3] && faceCoord[3].y == mergedBoundingBox[3]) {
			tempFaces.erase(tempFaces.begin() + 5);
			tempFaces.insert(tempFaces.begin() + 5, faces[i]);
			tempFaceNames.erase(tempFaceNames.begin() + 5);
			tempFaceNames.insert(tempFaceNames.begin() + 5, faceNames[i]);
		}
		else if (faceCoord[0].z == mergedBoundingBox[4] && faceCoord[1].z == mergedBoundingBox[4] && faceCoord[2].z == mergedBoundingBox[4] && faceCoord[3].z == mergedBoundingBox[4]) {
			tempFaces.erase(tempFaces.begin() + 3);
			tempFaces.insert(tempFaces.begin() + 3, faces[i]);
			tempFaceNames.erase(tempFaceNames.begin() + 3);
			tempFaceNames.insert(tempFaceNames.begin() + 3, faceNames[i]);
		}
		else if (faceCoord[0].z == mergedBoundingBox[5] && faceCoord[1].z == mergedBoundingBox[5] && faceCoord[2].z == mergedBoundingBox[5] && faceCoord[3].z == mergedBoundingBox[5]) {
			tempFaces.erase(tempFaces.begin() + 1);
			tempFaces.insert(tempFaces.begin() + 1, faces[i]);
			tempFaceNames.erase(tempFaceNames.begin() + 1);
			tempFaceNames.insert(tempFaceNames.begin() + 1, faceNames[i]);
		}
		//for (int j = 0; j < faceCoord.size(); j++) {//loops though coord
		//	if (faceCoord[j].x == mergedBoundingBox[0]) {
		//		int counter = faceCounters[0];
		//		faceCounters.erase(faceCounters.begin() + 0);
		//		faceCounters.insert(faceCounters.begin() + 0, counter + 1);
		//	}
		//	else if (faceCoord[j].x == mergedBoundingBox[1]) {
		//		int counter = faceCounters[1];
		//		faceCounters.erase(faceCounters.begin() + 1);
		//		faceCounters.insert(faceCounters.begin() + 1, counter + 1);
		//	}
		//	else if (faceCoord[j].y == mergedBoundingBox[2]) {
		//		int counter = faceCounters[2];
		//		faceCounters.erase(faceCounters.begin() + 2);
		//		faceCounters.insert(faceCounters.begin() + 2, counter + 1);
		//	}
		//	else if (faceCoord[j].y == mergedBoundingBox[3]) {
		//		int counter = faceCounters[3];
		//		faceCounters.erase(faceCounters.begin() + 3);
		//		faceCounters.insert(faceCounters.begin() + 3, counter + 1);
		//	}
		//	else if (faceCoord[j].z == mergedBoundingBox[4]) {
		//		int counter = faceCounters[4];
		//		faceCounters.erase(faceCounters.begin() + 4);
		//		faceCounters.insert(faceCounters.begin() + 4, counter + 1);
		//	}
		//	else if (faceCoord[j].z == mergedBoundingBox[5]) {
		//		int counter = faceCounters[5];
		//		faceCounters.erase(faceCounters.begin() + 5);
		//		faceCounters.insert(faceCounters.begin() + 5, counter + 1);
		//	}
		//}
		//}

		//Desired
		//face 0 = zmin(4)
		//face 1 = ymax(3)
		//face 2 = xmax(1)
		//face 3 = ymin(2)
		//face 4 = xmin(0)
		//face 5 = zmax(5)

		//if (faceCounters[4] == 4) {//zmin
		//	
		//}
		//else if (faceCounters[3] == 4) {//ymax
		//	
		//}
		//else if (faceCounters[1] == 4) {//xmax
		//	
		//}
		//else if (faceCounters[2] == 4) {//ymin
		//	
		//}
		//else if (faceCounters[2] == 4) {//xmin
		//	
		//}
		//else if (faceCounters[5] == 4) {//zmax
		//	
		//}
		else {//faces that are not the main 6 will be placed at the end.
			tempFaces.push_back(faces[i]);
		}
	}
	faceNames = tempFaceNames;
	return tempFaces;
}

// END MERGE---------------------------------------------------------------------------------------------


// BLOCK SPLIT-------------------------------------------------------------------------------------------------

void Building::blockSplit(string blockName, string axis, float percentage) {
	//object: which buildingblock will receive the cut
	//Axis : the direction the cut is being performed
	//Percentage : the position at which the cut is performed

	//Initialization
	int blockIndex = 0;
	for (int i = 0; i < bldg->blockList.size(); i++) {
		if (bldg->blockList[i]->name == blockName) {
			blockIndex = i;
			break;
		}
	}
	BuildingBlock * block = bldg->blockList[blockIndex];// create instance of information on block
	blockList.erase(blockList.begin() + blockIndex);//delete the block from the blockList

	/*
	/////////////////START OF SPLIT//////////////////////
	*/

	// Creating a dynamic array of the faces resulting from cutting the block like a slice of cheese.
	vector<vector<int>> cutFaces;
	// Loop through faces and restructure the indices within each instance and then create a second instance and push both back in a side-by-side manner.

	vector<int> tempCutFace;
	vector<vec3> newBoxCoords;

	if (axis == "X") { // Forward/Backward
		float diff = block->xmax - block->xmin; //this should = the change in height of the bounding box.
		float offset = diff * percentage;
		// Notifies what four vertices need to be constructed that will affect the indices, faces (main objective). Rendering is based
		// off of the faces datastructure. 
		newBoxCoords = blockGetNewCoordsX(block, offset);
	}
	else if (axis == "Y") { // Left/Right
		float diff = block->ymax - block->ymin;
		float offset = diff * percentage;
		newBoxCoords = blockGetNewCoordsY(block, offset);

	}
	else if (axis == "Z") { // Vertical axis
		float diff = block->zmax - block->zmin;
		float offset = diff * percentage;
		newBoxCoords = blockGetNewCoordsZ(block, offset);

	}
	else {
		cout << "Incorrect format for axis selection, must be one of the following:" << endl;
		cout << "- X, Y, Z " << endl;
	}

	cout << "New Coordinates:" << endl;
	for (int i = 0; i < newBoxCoords.size(); i++) {
		cout << newBoxCoords[i].x << ", " << newBoxCoords[i].y << ", " << newBoxCoords[i].z << endl;
	}


	//
	//for (int i = 0; i < faces.size(); i++) {
	//	for (int j = 0; j < addedVertices.size(); j++) {
	//		if ()

	//	}

	//	//2 hits?
	//	//1 hit?
	//	//0 hit?
	//}

	/*/////////////////////////////////////////////////
	/////////////////END OF SPLIT//////////////////////
	*/


	// REFORMAT:
//	string name = block->name;
//	vector<vector<int>> faces;//this gets restructured
//	vector<int> boxIndices; //this gets restructured first then base everything off of it.
//	vector<boxStruct> boxCoordinates;// factor in new coordinates. Create convenction for inserting into the box Coordinates the vertices. between.
//	vector<boxStruct> texCoords;
//	vector<int> texIndices;//this is based off update to faces i think.
//
//	BuildingBlock * blockToBePushed = new BuildingBlock(name, faces, boxIndices, boxCoordinates, texCoords, texIndices); //building block pointer
//	blockList.insert(blockList.begin() + blockIndex, blockToBePushed);
}

vector<vec3> Building::blockGetNewCoordsX(BuildingBlock * block, float offset) {
	// Return value
	vector<vec3> newBoxCoords;
	// Iterate over boxCoordinates and apply offset to the point with smallest axis value.
	for (int i = 0; i < block->boxCoordinates.size(); i++) {
		// If coordinate is on negative side of the bounding box, add the offset and store the new coordinate.
		if (block->boxCoordinates[i].boxPos.x == block->xmin) {
			float x = block->boxCoordinates[i].boxPos.x + offset;
			float y = block->boxCoordinates[i].boxPos.y;
			float z = block->boxCoordinates[i].boxPos.z;
			vec3 newCoordinate = vec3(x, y, z);
			newBoxCoords.push_back(newCoordinate);
		}
	}
	return newBoxCoords;
}

vector<vec3> Building::blockGetNewCoordsY(BuildingBlock * block, float offset) {
	// Return value
	vector<vec3> newBoxCoords;
	// Iterate over boxCoordinates and apply offset to the point with smallest axis value.
	for (int i = 0; i < block->boxCoordinates.size(); i++) {
		// If coordinate is on negative side of the bounding box, add the offset and store the new coordinate.
		if (block->boxCoordinates[i].boxPos.y == block->ymin) {
			float x = block->boxCoordinates[i].boxPos.x;
			float y = block->boxCoordinates[i].boxPos.y + offset;
			float z = block->boxCoordinates[i].boxPos.z;
			vec3 newCoordinate = vec3(x, y, z);
			newBoxCoords.push_back(newCoordinate);
		}
	}

	return newBoxCoords;
}

vector<vec3> Building::blockGetNewCoordsZ(BuildingBlock * block, float offset) {
	// Return value
	vector<vec3> newBoxCoords;
	// Iterate over boxCoordinates and apply offset to the point with smallest axis value.
	for (int i = 0; i < block->boxCoordinates.size(); i++) {
		// If coordinate is on negative side of the bounding box, add the offset and store the new coordinate.
		if (block->boxCoordinates[i].boxPos.z == block->zmin) {
			float x = block->boxCoordinates[i].boxPos.x;
			float y = block->boxCoordinates[i].boxPos.y;
			float z = block->boxCoordinates[i].boxPos.z + offset;
			vec3 newCoordinate = vec3(x, y, z);
			newBoxCoords.push_back(newCoordinate);
		}
	}

	return newBoxCoords;
}

void Building::multiBlockSplit(BuildingBlock * block1, string axis, int numOfSplits) {
	//object: which buildingblock will receive the cut
	//Axis : the direction the cut is being performed
	//numOfCuts : how many cuts are being performed

}

// END BLOCK SPLIT-------------------------------------------------------------------------------------------------


// SURFACE SPLIT---------------------------------------------------------------------------------------------------

/*
	faceName1: name for new face
	faceName2: name for new face
	blockName: Name of resulting merged object
	faceIndex: index of face being split
	axis: axis to split along
	percentage: pinpoint location of split on axis
*/
void Building::surfaceSplit(string faceName1, string faceName2, string blockName, string faceName, string axis, float percentage) {

	//Initialization
	int blockIndex = 0;
	for (int i = 0; i < bldg->blockList.size(); i++) {
		if (bldg->blockList[i]->name == blockName) {
			blockIndex = i;
			break;
		}
	}
	BuildingBlock * block = bldg->blockList[blockIndex];// create instance of information on block

	int faceIndex = getFaceIndex(block, faceName);


	/*
	/////////////////START OF SPLIT//////////////////////
	*/

	if (axis == "X" || axis == "x") { // Forward/Backward
		float diff = block->xmax - block->xmin; // this should = the change in height of the bounding box.
		float offset = diff * percentage;
		// Notifies what two vertices need to be constructed that will affect the indices, faces (main objective). Rendering is based
		// off of the faces data structure. 
		surfaceGetNewCoordsX(block, offset, faceIndex);
	}
	else if (axis == "Y" || axis == "y") { // Left/Right
		float diff = block->ymax - block->ymin;
		float offset = diff * percentage;
		surfaceGetNewCoordsY(block, offset, faceIndex);

	}
	else if (axis == "Z" || axis == "z") { // Vertical axis
		float diff = block->zmax - block->zmin;
		float offset = diff * percentage;
		surfaceGetNewCoordsZ(block, offset, faceIndex);

	}
	else {
		cout << "Incorrect format for axis selection, must be one of the following:" << endl;
		cout << "- X, Y, Z " << endl;
	}

	if (surfaceSplitLock) {
		cout << "AFTER RESTRUCTURE----------------" << endl;
		for (int i = 0; i < block->faces.size(); i++) {
			cout << "Face " << i << ":" << endl;
			cout << "Indices = (";
			for (int j = 0; j < block->faces[i].size(); j++) {
				cout << block->faces[i][j];
				if (j != block->faces[i].size() - 1) {
					cout << ", ";
				}
			}
			cout << ")" << endl;
		}
		cout << "-----------------------------------------" << endl;
	}

	// blue, green, cyan, red, pink, yellow, white, black, 
	std::vector<vec3> colorMap = {
		vec3(0, 0 ,1), vec3(0, 1 ,0),
		vec3(0, 1 ,1), vec3(1, 0 ,0),
		vec3(1, 0 ,1), vec3(1, 1 ,0),
		vec3(1, 1, 1), vec3(0, 0, 0),
		vec3(.5,.5,0), vec3(.7,0,.7),
		vec3(.2,0,0), vec3(0, .5,.6),
		vec3(.1,.7,.8)
	};

	cout << "-----texCoords----------------------------" << endl;
	block->texCoords.clear();
	for (int i = 0; i < block->faces.size(); i++) {//runs through faces
		cout << "Face: " << i << endl;
		cout << "Indices: " << block->faces[i][0] << " " << block->faces[i][1] << " " << block->faces[i][2] << " " << block->faces[i][3] << " " << block->faces[i][4] << " " << block->faces[i][5] << endl;
		cout << "Colormap: (" << colorMap[i].x << " , " << colorMap[i].y << " , " << colorMap[i].z << ")" << endl;
		for (int j = 0; j < block->faces[i].size(); j++) {
			boxStruct coordinate;
			coordinate.boxPos = block->boxCoordinates[block->faces[i][j]].boxPos; //boxCoordinates[indice value]
			coordinate.boxNorm = colorMap[i];
			block->texCoords.push_back(coordinate);
		}
	}
	cout << "-----------------------------------------------" << endl;
	block->texIndices.clear();
	for (int i = 0; i < block->texCoords.size(); i++) {
		block->texIndices.push_back(i);
	}



	//finds the face within the faces data structure
	//extremely useful if the faces is unstructured which sometime will occur
	//vector<int> splitFace = surfacePointsLieOnFace(block, newBoxCoords, faceIndex);

	//formating coordinates and indices
	//vector<int> tempBoxCoordinates = insertingNewCoords(block, newBoxCoords, faceIndex);


	//now splitFace is the face within the faces array that needs to be restructured
	//vector<vector<int>> restructuredFaces = surfaceRestructuringFaces( block, splitFace);


	/*/////////////////////////////////////////////////
	/////////////////END OF SPLIT//////////////////////
	*/


	// REFORMAT:
	//	string name = block->name;
	//	vector<vector<int>> faces;//this gets restructured
	//	vector<int> boxIndices; //this gets restructured first then base everything off of it.
	//	vector<boxStruct> boxCoordinates;// factor in new coordinates. Create convenction for inserting into the box Coordinates the vertices. between.
	//	vector<boxStruct> texCoords;
	//	vector<int> texIndices;//this is based off update to faces i think.
	//
	//	BuildingBlock * blockToBePushed = new BuildingBlock(name, faces, boxIndices, boxCoordinates, texCoords, texIndices); //building block pointer
	cout << "BlockList Index: " << blockIndex << endl;
	cout << "BlockList Size: " << blockList.size() << endl;
	//blockList.erase(blockList.begin() + blockIndex);//delete the block from the blockList
	//blockList.insert(blockList.begin() + blockIndex, block);
	//blockList.push_back(block);
}

void Building::surfaceGetNewCoordsX(BuildingBlock * block, float offset, int faceIndex) {
	vector<vector<vec3>> newBoxCoords;

	// boxCoordinates of interest will be found by comparing to a local minima
	float localMin = block->boxCoordinates[block->faces[faceIndex][0]].boxPos.x;
	// Indices of four corners that define face[faceIndex]
	vector<int> map = { 0,1,2,4 };

	// Find the local minima
	for (int i = 0; i < map.size(); i++) {
		if (block->boxCoordinates[block->faces[faceIndex][map[i]]].boxPos.x < localMin) {
			localMin = block->boxCoordinates[block->faces[faceIndex][map[i]]].boxPos.x;
		}
	}

	//push coordinates to block->bocCoordinates end
	vector<vec3> colorMap = {
		vec3(.2,.6,.7), vec3(.7,.9,.4)
	};
	int colorCounter = 0;
	// Focus on vertices that define faace[faceIndex]. Find the boxCoordinates of interest to apply the offset to.
	for (int i = 0; i < map.size(); i++) {
		if (block->boxCoordinates[block->faces[faceIndex][map[i]]].boxPos.x == localMin) {
			vector<vec3> temp;
			temp.push_back(block->boxCoordinates[block->faces[faceIndex][map[i]]].boxPos);
			temp.push_back(vec3(block->boxCoordinates[block->faces[faceIndex][map[i]]].boxPos.x + offset, block->boxCoordinates[block->faces[faceIndex][map[i]]].boxPos.y, block->boxCoordinates[block->faces[faceIndex][map[i]]].boxPos.z));
			newBoxCoords.push_back(temp);

			struct boxStruct tempCoord;
			tempCoord.boxPos = vec3(block->boxCoordinates[block->faces[faceIndex][map[i]]].boxPos.x + offset, block->boxCoordinates[block->faces[faceIndex][map[i]]].boxPos.y, block->boxCoordinates[block->faces[faceIndex][map[i]]].boxPos.z);
			tempCoord.boxNorm = colorMap[colorCounter];
			block->boxCoordinates.push_back(tempCoord);
			colorCounter++;
		}
	}

	//changing faces.
	/*int faceIndex = 0;
	for (int i = 0; i < block->faces.size(); i++) {
		if (block->faces[i] == splitFace) {
			faceIndex = i;
			break;
		}
	}*/

	if (surfaceSplitLock) {
		cout << "BEFORE insertion of new faces" << endl;
		for (int i = 0; i < block->faces.size(); i++) {
			for (int j = 0; j < 6; j++) {
				cout << block->faces[i][j];
				cout << ",";
			}
			cout << endl;
		}
	}

	//forge new faces
	vector<vector<int>> faceBeingAdded;
	int coord1Index = block->boxCoordinates.size() - 2;//top inputted
	cout << "coord1index: ( " << block->boxCoordinates[coord1Index].boxPos.x << " , " << block->boxCoordinates[coord1Index].boxPos.y << " , " << block->boxCoordinates[coord1Index].boxPos.z << " )" << endl;
	int coord2Index = block->boxCoordinates.size() - 1; // bottom coord inputted
	cout << "coord2index: ( " << block->boxCoordinates[coord2Index].boxPos.x << " , " << block->boxCoordinates[coord2Index].boxPos.y << " , " << block->boxCoordinates[coord2Index].boxPos.z << " )" << endl;

	vector<int> newFace1 = {
		coord1Index , block->faces[faceIndex][1], block->faces[faceIndex][2], block->faces[faceIndex][3], coord2Index, coord1Index
	};
	vector<int> newFace2 = {
		 block->faces[faceIndex][0], coord1Index, coord2Index, coord2Index,  block->faces[faceIndex][4],  block->faces[faceIndex][5]
	};

	faceBeingAdded.push_back(newFace2);
	faceBeingAdded.push_back(newFace1);
	block->faces.erase(block->faces.begin() + faceIndex);
	for (int i = 0; i < 2; i++) {
		block->faces.insert(block->faces.begin() + faceIndex + i, faceBeingAdded[i]);
	}

	if (surfaceSplitLock) {
		cout << "AFTER insertion of new faces" << endl;
		for (int i = 0; i < block->faces.size(); i++) {
			for (int j = 0; j < 6; j++) {
				cout << block->faces[i][j];
				cout << ",";
			}
			cout << endl;
		}
	}

} // end GetNewCoordsX

void Building::surfaceGetNewCoordsY(BuildingBlock * block, float offset, int faceIndex) {
	vector<vector<vec3>> newBoxCoords;
	//cout << "Checkpoint 1" << endl;
	// boxCoordinates of interest will be found by comparing to a local minima
	float localMin = block->boxCoordinates[block->faces[faceIndex][0]].boxPos.y;
	// Indices of four corners that define face[faceIndex]
	vector<int> map = { 0,1,2,4 };
	//cout << "Checkpoint 2" << endl;
	// Find the local minima
	for (int i = 0; i < map.size(); i++) {
		if (block->boxCoordinates[block->faces[faceIndex][map[i]]].boxPos.y < localMin) {
			localMin = block->boxCoordinates[block->faces[faceIndex][map[i]]].boxPos.y;
		}
	}
	cout << "local Min Chosen: " << localMin << endl;
	//cout << "Checkpoint 3" << endl;

	//push coordinates to block->boxCoordinates end
	vector<vec3> colorMap = {
		vec3(.2,.6,.7), vec3(.7,.9,.4)
	};
	//printInfo coords
	//cout << "facesBegin////////////////////////" << endl;
	///*for (int i = 0; i < map.size(); i++) {
	//	cout << "face: " << faceIndex << "  Coordinate: " << i << " :(" << block->boxCoordinates[block->faces[faceIndex][map[i]]].boxPos.x << " ," << block->boxCoordinates[block->faces[faceIndex][map[i]]].boxPos.y << " ," << block->boxCoordinates[block->faces[faceIndex][map[i]]].boxPos.z << " )" << endl;
	//}*/

	//
	//cout << "faces size: " << block->faces.size() << endl;
	//for (int i = 0; i < block->faces.size(); i++) {
	//	cout << "face: " << i << endl;
	//	for (int j = 0; j < map.size(); j++) {
	//		cout << "  Coordinate: " << j << " :(" << block->boxCoordinates[block->faces[i][map[j]]].boxPos.x << " ," << block->boxCoordinates[block->faces[i][map[j]]].boxPos.y << " ," << block->boxCoordinates[block->faces[i][map[j]]].boxPos.z << " )" << endl;
	//	}
	//}
	//cout << "facesEnd/////////////////" << endl;
	

	int colorCounter = 0;
	// Focus on vertices that define faace[faceIndex]. Find the boxCoordinates of interest to apply the offset to.
	for (int i = 0; i < map.size(); i++) {
		if (block->boxCoordinates[block->faces[faceIndex][map[i]]].boxPos.y == localMin) {
			vector<vec3> temp;
			temp.push_back(block->boxCoordinates[block->faces[faceIndex][map[i]]].boxPos);
			temp.push_back(vec3(block->boxCoordinates[block->faces[faceIndex][map[i]]].boxPos.x, block->boxCoordinates[block->faces[faceIndex][map[i]]].boxPos.y + offset, block->boxCoordinates[block->faces[faceIndex][map[i]]].boxPos.z));
			newBoxCoords.push_back(temp);

			struct boxStruct tempCoord;
			tempCoord.boxPos = vec3(block->boxCoordinates[block->faces[faceIndex][map[i]]].boxPos.x, block->boxCoordinates[block->faces[faceIndex][map[i]]].boxPos.y + offset, block->boxCoordinates[block->faces[faceIndex][map[i]]].boxPos.z);
			tempCoord.boxNorm = colorMap[colorCounter];
			block->boxCoordinates.push_back(tempCoord);
			colorCounter++;
		}
	}
	//cout << "Checkpoint 4" << endl;
	//changing faces.
	/*int faceIndex = 0;
	for (int i = 0; i < block->faces.size(); i++) {
		if (block->faces[i] == splitFace) {
			faceIndex = i;
			break;
		}
	}*/

	if (surfaceSplitLock) {
		cout << "BEFORE insertion of new faces" << endl;
		for (int i = 0; i < block->faces.size(); i++) {
			for (int j = 0; j < 6; j++) {
				cout << block->faces[i][j];
				cout << ",";
			}
			cout << endl;
		}
	}
	//cout << "Checkpoint 5" << endl;
	//forge new faces
	vector<vector<int>> faceBeingAdded;
	int coord1Index = block->boxCoordinates.size() - 2;//top inputted
	cout << "coord1index: ( " << block->boxCoordinates[coord1Index].boxPos.x << " , " << block->boxCoordinates[coord1Index].boxPos.y << " , " << block->boxCoordinates[coord1Index].boxPos.z << " )" << endl;
	int coord2Index = block->boxCoordinates.size() - 1; // bottom coord inputted
	cout << "coord2index: ( " << block->boxCoordinates[coord2Index].boxPos.x << " , " << block->boxCoordinates[coord2Index].boxPos.y << " , " << block->boxCoordinates[coord2Index].boxPos.z << " )" << endl;

	vector<int> newFace1 = {
		block->faces[faceIndex][0] , block->faces[faceIndex][1], coord1Index, coord1Index, coord2Index, block->faces[faceIndex][5]
	};
	vector<int> newFace2 = {
		 coord2Index, coord1Index, block->faces[faceIndex][2], block->faces[faceIndex][3],  block->faces[faceIndex][4],  coord2Index
	};
	//cout << "Checkpoint 6" << endl;
	faceBeingAdded.push_back(newFace2);
	faceBeingAdded.push_back(newFace1);
	block->faces.erase(block->faces.begin() + faceIndex);
	for (int i = 0; i < 2; i++) {
		block->faces.insert(block->faces.begin() + faceIndex + i, faceBeingAdded[i]);
	}


	//cout << "Checkpoint 7" << endl;
	if (surfaceSplitLock) {
		cout << "AFTER insertion of new faces" << endl;
		for (int i = 0; i < block->faces.size(); i++) {
			for (int j = 0; j < 6; j++) {
				cout << block->faces[i][j];
				cout << ",";
			}
			cout << endl;
		}
	}
	//cout << "Checkpoint 8" << endl;
} // end GetNewCoordsY

void Building::surfaceGetNewCoordsZ(BuildingBlock * block, float offset, int faceIndex) {
	vector<vector<vec3>> newBoxCoords;

	// boxCoordinates of interest will be found by comparing to a local minima
	float localMin = block->boxCoordinates[block->faces[faceIndex][0]].boxPos.z;
	// Indices of four corners that define face[faceIndex]
	vector<int> map = { 0,1,2,4 };

	// Find the local minima
	for (int i = 0; i < map.size(); i++) {
		if (block->boxCoordinates[block->faces[faceIndex][map[i]]].boxPos.z < localMin) {
			localMin = block->boxCoordinates[block->faces[faceIndex][map[i]]].boxPos.z;
		}
	}

	// push coordinates to block->bocCoordinates end
	vector<vec3> colorMap = {
		vec3(.2,.6,.7), vec3(.7,.9,.4)
	};
	int colorCounter = 0;
	// Focus on vertices that define face[faceIndex]. Find the boxCoordinates of interest to apply the offset to.
	for (int i = 0; i < map.size(); i++) {
		if (block->boxCoordinates[block->faces[faceIndex][map[i]]].boxPos.z == localMin) {
			vector<vec3> temp;
			temp.push_back(block->boxCoordinates[block->faces[faceIndex][map[i]]].boxPos);
			temp.push_back(vec3(block->boxCoordinates[block->faces[faceIndex][map[i]]].boxPos.x, block->boxCoordinates[block->faces[faceIndex][map[i]]].boxPos.y, block->boxCoordinates[block->faces[faceIndex][map[i]]].boxPos.z + offset));
			newBoxCoords.push_back(temp);

			struct boxStruct tempCoord;
			tempCoord.boxPos = vec3(block->boxCoordinates[block->faces[faceIndex][map[i]]].boxPos.x, block->boxCoordinates[block->faces[faceIndex][map[i]]].boxPos.y, block->boxCoordinates[block->faces[faceIndex][map[i]]].boxPos.z + offset);
			tempCoord.boxNorm = colorMap[colorCounter];
			block->boxCoordinates.push_back(tempCoord);
			colorCounter++;
		}
	}

	//changing faces.
	/*int faceIndex = 0;
	for (int i = 0; i < block->faces.size(); i++) {
		if (block->faces[i] == splitFace) {
			faceIndex = i;
			break;
		}
	}*/

	if (surfaceSplitLock) {
		cout << "BEFORE insertion of new faces" << endl;
		for (int i = 0; i < block->faces.size(); i++) {
			for (int j = 0; j < 6; j++) {
				cout << block->faces[i][j];
				cout << ",";
			}
			cout << endl;
		}
	}

	//forge new faces
	vector<vector<int>> faceBeingAdded;
	int coord1Index = block->boxCoordinates.size() - 2;//top inputted
	cout << "coord1index: ( " << block->boxCoordinates[coord1Index].boxPos.x << " , " << block->boxCoordinates[coord1Index].boxPos.y << " , " << block->boxCoordinates[coord1Index].boxPos.z << " )" << endl;
	int coord2Index = block->boxCoordinates.size() - 1; // bottom coord inputted
	cout << "coord2index: ( " << block->boxCoordinates[coord2Index].boxPos.x << " , " << block->boxCoordinates[coord2Index].boxPos.y << " , " << block->boxCoordinates[coord2Index].boxPos.z << " )" << endl;

	if (block->boxCoordinates[block->faces[faceIndex][0]].boxPos.y == ymin && block->boxCoordinates[block->faces[faceIndex][1]].boxPos.y == ymin && block->boxCoordinates[block->faces[faceIndex][2]].boxPos.y == ymin && block->boxCoordinates[block->faces[faceIndex][0]].boxPos.y == ymin) {
		//cout << "true" << endl;
	}
	//makes easier to read
	vector<vec3> faceCoord = {
		block->boxCoordinates[block->faces[faceIndex][0]].boxPos,
		block->boxCoordinates[block->faces[faceIndex][1]].boxPos,
		block->boxCoordinates[block->faces[faceIndex][2]].boxPos,
		block->boxCoordinates[block->faces[faceIndex][4]].boxPos
	};
	vector<int> newFace1;
	vector<int> newFace2;
	if (faceCoord[0].x == mergedBoundingBox[0] && faceCoord[1].x == mergedBoundingBox[0] && faceCoord[2].x == mergedBoundingBox[0] && faceCoord[3].x == mergedBoundingBox[0]) { //xmin
		newFace1 = {
				 block->faces[faceIndex][0] , coord1Index, coord2Index, coord2Index,  block->faces[faceIndex][4],  block->faces[faceIndex][5]
		};
		newFace2 = {
				coord1Index,  block->faces[faceIndex][1],  block->faces[faceIndex][2],  block->faces[faceIndex][3],  coord2Index,  coord1Index
		};
	}
	else if (faceCoord[0].x == mergedBoundingBox[1] && faceCoord[1].x == mergedBoundingBox[1] && faceCoord[2].x == mergedBoundingBox[1] && faceCoord[3].x == mergedBoundingBox[1]) { //xmax
		newFace1 = {
				 block->faces[faceIndex][0] , coord1Index, coord2Index, coord2Index,  block->faces[faceIndex][4],  block->faces[faceIndex][5]
		};
		newFace2 = {
				coord1Index,  block->faces[faceIndex][1],  block->faces[faceIndex][2],  block->faces[faceIndex][3],  coord2Index,  coord1Index
		};
	}
	else if (faceCoord[0].y == mergedBoundingBox[2] && faceCoord[1].y == mergedBoundingBox[2] && faceCoord[2].y == mergedBoundingBox[2] && faceCoord[3].y == mergedBoundingBox[2]) { //ymin
		newFace1 = {
				 block->faces[faceIndex][0] , block->faces[faceIndex][1], coord2Index, coord2Index, coord1Index,  block->faces[faceIndex][5]
		};
		newFace2 = {
				coord1Index, coord2Index,  block->faces[faceIndex][2],  block->faces[faceIndex][3],  block->faces[faceIndex][4],  coord1Index
		};
	}
	else if (faceCoord[0].y == mergedBoundingBox[3] && faceCoord[1].y == mergedBoundingBox[3] && faceCoord[2].y == mergedBoundingBox[3] && faceCoord[3].y == mergedBoundingBox[3]) {//ymax
		newFace1 = {
				 block->faces[faceIndex][0] , block->faces[faceIndex][1], coord1Index, coord1Index, coord2Index,  block->faces[faceIndex][5]
		};
		newFace2 = {
				coord2Index, coord1Index,  block->faces[faceIndex][2],  block->faces[faceIndex][3],  block->faces[faceIndex][4],  coord2Index
		};
	}


	// KEEP THIS
	cout << "checkpoint 3" << endl;
	faceBeingAdded.push_back(newFace2);
	faceBeingAdded.push_back(newFace1);

	for (int i = 0; i < faceBeingAdded.size(); i++) {
		cout << "Face " << i << ": " << endl;
		for (int j = 0; j < faceBeingAdded[i].size(); j++) {
			cout << faceBeingAdded[i][j];
			cout << ", ";
		}
		cout << endl;
	}

	cout << "checkpoint 4" << endl;

	block->faces.erase(block->faces.begin() + faceIndex);
	for (int i = 0; i < 2; i++) {
		block->faces.insert(block->faces.begin() + faceIndex + i, faceBeingAdded[i]);
	}

	if (surfaceSplitLock) {
		cout << "AFTER insertion of new faces" << endl;
		for (int i = 0; i < block->faces.size(); i++) {
			for (int j = 0; j < 6; j++) {
				if (i == 0 || i == 1) {
					cout << "notta" << endl;
				}
				else {
					cout << block->faces[i][j];
					cout << ",";
				}

			}
			cout << endl;
		}
	}

} // end GetNewCoordsZ

void Building::surfaceSplit(string faceName1, string faceName2, string groupName, string blockName, string faceName, string axis, float percentage) {
	// Get render data for group from blockList:
	BuildingBlock* groupData = getBuildingBlock(groupName);

	// Get groupIndex from groupNames:
	int groupIndex = getGroupIndex(groupName);

	// Get index position of block to split in groupMembers
	int blockIndex = -1;
	for (int i = 0; i < groupMembers[groupIndex].size(); i++) {
		//cout << "block: " << groupMembers[groupIndex][i] << " vs " << blockName<< endl;
		if (groupMembers[groupIndex][i] == blockName) {
			blockIndex = i;
			//cout << "blockIndex Chosen: " << blockIndex << endl;
			break;
		}
	}	
	//debug 
	if (superLock) {
		cout << "Face Names:" << endl;
		for (int i = 0; i < groupData->faceNames.size(); i++) {
			cout << groupData->faceNames[i] << endl;
		}
	}

	//int faceIndex = getFaceIndex(groupData, faceName, faceOffset); // since there are 6 faces
	int faceIndex = getFaceIndex(groupIndex, blockName, faceName);
	
	cout << "Face Index: " << faceIndex << endl;

	//setBoundingBox
	//cout << "Entering bounding box coords loop" << endl;
	vector<boxStruct> coordsForBoundingBox;
	//cout << "n=" << groupMemberFaceCount[groupIndex][blockIndex] << endl;
	for (int i = 0; i < groupData->faces[faceIndex].size(); i++) {
		if (superLock) {
			cout << "iteration i:" << i << endl;
		}
		boxStruct temp = groupData->boxCoordinates[groupData->faces[faceIndex][i]];
		coordsForBoundingBox.push_back(temp);
		if (superLock) {
			cout << "iteration i:" << i << endl;
		}
	}
	setBoundingBox(coordsForBoundingBox);

	if (superLock) {
		for (int i = 0; i < coordsForBoundingBox.size(); i++) {
			cout << "Coord #" << i << " (" << coordsForBoundingBox[i].boxPos.x << " , " << coordsForBoundingBox[i].boxPos.y << " , " << coordsForBoundingBox[i].boxPos.z << " )" << endl;
		}
	}
	
	
	/////////////////START OF SPLIT//////////////////////
	
	BuildingBlock* block = groupData;
	if (axis == "X" || axis == "x") { // Forward/Backward
		float diff = xmax - xmin; // this should = the change in height of the bounding box.
		float offset = diff * percentage;
		// Notifies what two vertices need to be constructed that will affect the indices, faces (main objective). Rendering is based
		// off of the faces data structure. 
		surfaceGetNewCoordsX(block, offset, faceIndex);
		groupMemberFaceCount[groupIndex][blockIndex] = groupMemberFaceCount[groupIndex][blockIndex] + 1;
		block->faceNames.erase(block->faceNames.begin() + faceIndex);
		block->faceNames.insert(block->faceNames.begin() + faceIndex + 0, faceName1);
		block->faceNames.insert(block->faceNames.begin() + faceIndex + 1, faceName2);

	}
	else if (axis == "Y" || axis == "y") { // Left/Right
		float diff = ymax - ymin;
		cout << "diff: " << diff << endl;
		float offset = diff * percentage;
		cout << "offset: " << offset << endl;
		if (diffOffsetLock) {
			cout << "Diff: " << diff << " = " << ymax << " - " << ymin << endl;
			cout << "Offset: " << offset << " = " << diff << " * " << percentage << endl;
		}
		
		surfaceGetNewCoordsY(block, offset, faceIndex);
		groupMemberFaceCount[groupIndex][blockIndex] = groupMemberFaceCount[groupIndex][blockIndex] + 1;
		block->faceNames.erase(block->faceNames.begin() + faceIndex);
		block->faceNames.insert(block->faceNames.begin() + faceIndex + 0, faceName1);
		block->faceNames.insert(block->faceNames.begin() + faceIndex + 1, faceName2);

	}
	else if (axis == "Z" || axis == "z") { // Vertical axis
		float diff = zmax - zmin;
		float offset = diff * percentage;
		surfaceGetNewCoordsZ(block, offset, faceIndex);
		groupMemberFaceCount[groupIndex][blockIndex] = groupMemberFaceCount[groupIndex][blockIndex] + 1;
		block->faceNames.erase(block->faceNames.begin() + faceIndex);
		block->faceNames.insert(block->faceNames.begin() + faceIndex + 0, faceName1);
		block->faceNames.insert(block->faceNames.begin() + faceIndex + 1, faceName2);

	}
	else {
		cout << "Incorrect format for axis selection, must be one of the following:" << endl;
		cout << "- X, Y, Z " << endl;
	}

	if (surfaceSplitLock) {
		cout << "AFTER RESTRUCTURE----------------" << endl;
		for (int i = 0; i < block->faces.size(); i++) {
			cout << "Face " << i << ":" << endl;
			cout << "Indices = (";
			for (int j = 0; j < block->faces[i].size(); j++) {
				cout << block->faces[i][j];
				if (j != block->faces[i].size() - 1) {
					cout << ", ";
				}
			}
			cout << ")" << endl;
		}
		cout << "-----------------------------------------" << endl;
	}

	// blue, green, cyan, red, pink, yellow, white, black, 
	std::vector<vec3> colorMap = {
		vec3(0, 0 ,1), vec3(0, 1 ,0),
		vec3(0, 1 ,1), vec3(1, 0 ,0),
		vec3(1, 0 ,1), vec3(1, 1 ,0),
		vec3(1, 1, 1), vec3(0, 0, 0),
		vec3(.5,.5,0), vec3(.7,0,.7),
		vec3(.2,0,0), vec3(0, .5,.6),
		vec3(.1,.7,.8)
	};

	
	if (texCoordLock == true) {cout << "-----texCoords----------------------------" << endl;}
	vector<boxStruct> tempTexCoords;
	for (int i = 0; i < block->texCoords.size(); i++) {
		tempTexCoords.insert(tempTexCoords.end(), block->texCoords[i]);
	}

	block->texCoords.clear();
	for (int i = 0; i < block->faces.size(); i++) {//runs through faces
		if (texCoordLock == true) { cout << "Face: " << i << endl; }
		if (texCoordLock == true) { cout << "Indices: " << block->faces[i][0] << " " << block->faces[i][1] << " " << block->faces[i][2] << " " << block->faces[i][3] << " " << block->faces[i][4] << " " << block->faces[i][5] << endl; }
		if (texCoordLock == true) { cout << "Colormap: (" << colorMap[i].x << " , " << colorMap[i].y << " , " << colorMap[i].z << ")" << endl; }
		for (int j = 0; j < block->faces[i].size(); j++) {
			boxStruct coordinate;
			coordinate.boxPos = block->boxCoordinates[block->faces[i][j]].boxPos; //boxCoordinates[indice value]
			//coordinate.boxNorm = tempTexCoords[block->faces[i][j]].boxNorm;
			coordinate.boxNorm = colorMap[i % colorMap.size()];
			block->texCoords.insert(block->texCoords.end(), coordinate);
		}
	}
	if (texCoordLock == true) { cout << "-----------------------------------------------" << endl; }
	block->texIndices.clear();
	for (int i = 0; i < block->texCoords.size(); i++) {
		block->texIndices.push_back(i);
	}



	//finds the face within the faces data structure
	//extremely useful if the faces is unstructured which sometime will occur
	//vector<int> splitFace = surfacePointsLieOnFace(block, newBoxCoords, faceIndex);

	//formating coordinates and indices
	//vector<int> tempBoxCoordinates = insertingNewCoords(block, newBoxCoords, faceIndex);


	//now splitFace is the face within the faces array that needs to be restructured
	//vector<vector<int>> restructuredFaces = surfaceRestructuringFaces( block, splitFace);


	/*/////////////////////////////////////////////////
	/////////////////END OF SPLIT//////////////////////
	*/


	// REFORMAT:
	//	string name = block->name;
	//	vector<vector<int>> faces;//this gets restructured
	//	vector<int> boxIndices; //this gets restructured first then base everything off of it.
	//	vector<boxStruct> boxCoordinates;// factor in new coordinates. Create convenction for inserting into the box Coordinates the vertices. between.
	//	vector<boxStruct> texCoords;
	//	vector<int> texIndices;//this is based off update to faces i think.
	//
	//	BuildingBlock * blockToBePushed = new BuildingBlock(name, faces, boxIndices, boxCoordinates, texCoords, texIndices); //building block pointer
	//cout << "BlockList Index: " << blockIndex << endl;
	//cout << "BlockList Size: " << blockList.size() << endl;
	//blockList.erase(blockList.begin() + blockIndex);//delete the block from the blockList
	//blockList.insert(blockList.begin() + blockIndex, block);
	//blockList.push_back(block);
}

// END SURFACE SPLIT-----------------------------------------------------------------------------------------------


// MAKE GROUP------------------------------------------------------------------------------------------------------

void Building::makeGroup(string groupName) {
	cout << "makeGroup entered..." << endl;

	for (int i = 0; i < groupNames.size(); i++) {
		if (groupNames[i] == groupName) {
			cout << "are you a idiot" << endl;
			exit(0);
		}
	}

	groupNames.push_back(groupName);
	// Allocate memory for this new group:
	vector<string> temp{};
	groupMembers.push_back(temp);
	vector<int> temp2{};
	groupMemberFaceCount.push_back(temp2);

	// Debugging:
	if (groupLock) {
		cout << "Groups:" << endl;
		for (int i = 0; i < groupNames.size(); i++) {
			cout << groupNames[i] << endl;
		}
	}
}

void Building::groupInsert(string groupName, string blockName) {
	cout << "groupInsert entered..." << endl;

	// If block does not exist:
	if (getBuildingBlock(blockName) == NULL) {
		cout << "Error: groupInsert() - " << blockName << " does not exist" << endl;
		exit(0);
	}

	// Get position of group in groups
	int groupIndex = getGroupIndex(groupName);

	// Add block to specified group
	groupMembers[groupIndex].push_back(blockName);

	// Accumulate block data over time:
	if (groupMembers[groupIndex].size() == 1) { // Insert the first member, so assign building block
		BuildingBlock* blockToAdd = getBuildingBlock(blockName);
		blockToAdd->name = groupName;
		groupBlocks.push_back(blockToAdd);
		blockNames.push_back(blockName);
	}
	else { // More than one member, concatenate members block data
		// Get render data for group:
		BuildingBlock* groupData = groupBlocks[groupIndex];
		// Update render data for group:
		updateBlockData(blockName, groupData);
		
		// Keep track of block names:
		//blockNames.push_back(blockName);
		blockNames.insert(blockNames.begin(), blockName);

	}
	groupMemberFaceCount[groupIndex].push_back(6);

	// Quick render:
	blockList.push_back(groupBlocks[groupIndex]);

	// Debugging:
	if (groupLock) {
		cout << groupName << " Members:" << endl;
		for (int i = 0; i < groupMembers[groupIndex].size(); i++) {
			cout << groupMembers[groupIndex][i] << endl;
		}
	}
	if (groupDataLock) {
		cout << "GROUP RENDER DATA===============================================================" << endl;
		printCoords(groupBlocks[groupIndex]->boxCoordinates);
		printIndices(groupBlocks[groupIndex]->boxIndices);
		printFaceNames(groupBlocks[groupIndex]->faceNames);
		cout << "================================================================================" << endl;
	}
}

int Building::getGroupIndex(string groupName) {
	for (int i = 0; i < groupNames.size(); i++) {
		if (groupNames[i] == groupName) {
			return i;
		}
	}

	return -1;
}

void Building::updateBlockData(string blockName, BuildingBlock * groupData) {
	BuildingBlock* dataToAdd = getBuildingBlock(blockName);

	// Update groupData with values from dataToAdd:

	// 1. Update boxCoordinates - basic concatenation
	vector<boxStruct> updatedBoxCoordinates = groupData->boxCoordinates;
	updatedBoxCoordinates.insert(updatedBoxCoordinates.end(), dataToAdd->boxCoordinates.begin(), dataToAdd->boxCoordinates.end());

	// 2. Update boxIndices - concatenation with offset of indices
	vector<int> updatedBoxIndices = groupData->boxIndices;
	vector<int> offsetBoxIndices;
	// Store offset dataToAdd box indices in offsetBoxIndices:
	for (int i = 0; i < dataToAdd->boxIndices.size(); i++) {
		int temp = dataToAdd->boxIndices[i] + groupData->boxCoordinates.size(); // ... + offset
		//offsetBoxIndices.push_back(temp);
		offsetBoxIndices.insert(offsetBoxIndices.end(), temp);
	}
	/*for (int i = 0; i < offsetBoxIndices.size(); i++) {
		updatedBoxIndices.push_back(offsetBoxIndices[i]);
	}*/
	updatedBoxIndices.insert(updatedBoxIndices.end(), offsetBoxIndices.begin(), offsetBoxIndices.end());

	// 3. Update faces - 
	vector<vector<int>> updatedFaces{};

	for (int i = 0; i < updatedBoxIndices.size(); i = i + 6) {

		vector<int> faceToAdd; // Set of 6 box indices
		for (int j = 0; j < 6; j++) { // Update face with correct boxIndices
			faceToAdd.push_back(updatedBoxIndices[i + j]);
		}
		//updatedFaces.push_back( faceToAdd);
		updatedFaces.insert(updatedFaces.end(), faceToAdd);
	}

	// 4. Update faceNames
	vector<string> updatedFaceNames = groupData->faceNames;
	for (int i = 0; i < dataToAdd->faceNames.size(); i++) {
		updatedFaceNames.insert(updatedFaceNames.end(), dataToAdd->faceNames[i]);
	}

	// 4.2 Update texCoords and texIndices
	vector<boxStruct> updatedTexCoords;
	vector<int> updatedTexIndices;
	struct boxStruct coordinate;

	vector<vec3> colorMap = {
		vec3(0, 0 ,1), vec3(0, 1 ,0),
		vec3(0, 1 ,1), vec3(1, 0 ,0),
		vec3(1, 0 ,1), vec3(1, 1 ,0),
		vec3(1, 1, 1), vec3(0, 0, 0),
		vec3(.5,.5,0), vec3(.7,0,.7),
		vec3(.2,0,0), vec3(0, .5,.6),
		vec3(.1,.7,.8)
	};

	//Debugging:
	if (groupDataLock) {
		for (int i = 0; i < updatedFaces.size(); i++) {
			cout << "Face " << i << ": ";
			for (int j = 0; j < updatedFaces[i].size(); j++) {
				cout << updatedFaces[i][j] << " ";
			}
			cout << "Name: " << updatedFaceNames[i] << endl;
			cout << endl;
			if(i<12){
				for (int j = 0; j < updatedFaces[i].size(); j++) {
					coordinate.boxPos = updatedBoxCoordinates[updatedFaces[i][j]].boxPos; // boxCoordinates[indice value]
					coordinate.boxNorm = colorMap[i % colorMap.size()];
					/*if (j == 11)
						break;*/
					cout << coordinate.boxPos.x << ", " << coordinate.boxPos.y << ", " << coordinate.boxPos.z << endl;

				}
			}
		}

		cout << "Updated Faces Size: " << updatedFaces.size() << endl;
	}
	
	// updatedTexCoords:
	// Iterate over each face:
	for (int i = 0; i < updatedFaces.size(); i++) {
		//cout << i << ": " << endl;;
		// Iterate over all face's coordinates:
		for (int j = 0; j < updatedFaces[i].size(); j++) {
			coordinate.boxPos = updatedBoxCoordinates[updatedFaces[i][j]].boxPos; // boxCoordinates[indice value]
			coordinate.boxNorm = colorMap[i % colorMap.size()];
			//cout << j;

			updatedTexCoords.push_back(coordinate);
		}
		//cout << endl;
	}

	// updatedTexIndices:
	for (int i = 0; i < updatedTexCoords.size(); i++) {
		updatedTexIndices.push_back(i);
	}

	if (groupDataLock) {
		cout << "TEXTURE DATA+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++" << endl;
		printCoords(updatedTexCoords);
		printIndices(updatedTexIndices);
		cout << "+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++" << endl;
	}

	
	// 5. Apply all updated values 1-4.2 to groupData
	groupData->boxCoordinates = updatedBoxCoordinates;
	groupData->boxIndices = updatedBoxIndices;
	groupData->faces = updatedFaces;
	groupData->faceNames = updatedFaceNames;
	groupData->texCoords = updatedTexCoords;
	groupData->texIndices = updatedTexIndices;
}

// END MAKE GROUP--------------------------------------------------------------------------------------------------


// MISC UTILITIES--------------------------------------------------------------------------------------------------

void Building::setTexture(string blockName, string faceName, string texture) {
	cout << "setTexture entered..." << endl;
}

BuildingBlock* Building::getBuildingBlock(string blockName) {
	BuildingBlock* currentBlock;
	for (int i = 0; i < blockList.size(); i++) {
		if (blockList[i]->name == blockName) {
			currentBlock = blockList[i];
			return currentBlock;
		}
	}

	return NULL;
}

int Building::getFaceIndex(int groupIndex, string blockName, string faceName) {

	// Broad faceIndex search: brings us to where the faceNames of blockName are
	int faceIndex = 0;
	int blockCountIndex = -1;
	for (int i = 0; i < groupMemberFaceCount[groupIndex].size(); i++) {
		// Continue to increase the faceIndex value until finding the blockName:
		//cout << "Compare Blocks: " << groupMembers[groupIndex][i] << ", " << blockName << endl;
		if (groupMembers[groupIndex][i] == blockName) {
			blockCountIndex = i;
			break;
		}
		else {
			faceIndex += groupMemberFaceCount[groupIndex][i];
		}
	}
	//cout << "FaceIndex = " << faceIndex << endl;
	//cout << "Block Count Index: " << blockCountIndex << endl;
	//cout << "groupMemberFaceCount[groupIndex][blockCountIndex] = " <<groupMemberFaceCount[groupIndex][blockCountIndex] << endl;
	int offset = faceIndex;
	//cout << "offset = " << offset << endl;

	// Narrow search: searches for the specific faceIndex of the faceName in the block
	cout << "FaceName: " << faceName << endl;
	for (int i = 0; i < groupMemberFaceCount[groupIndex][blockCountIndex]; i++) {
		//cout << "i=" << i + offset << ", n=" << groupMemberFaceCount[groupIndex][blockCountIndex] << endl;
		//cout << "Compare Faces: " << faceName << ", " << groupBlocks[groupIndex]->faceNames[i + offset] << endl;

		if (faceName == groupBlocks[groupIndex]->faceNames[i + offset]) {
			//cout << "FaceIndex after Loop: " << faceIndex << endl;
			return faceIndex;
		}
		faceIndex++;
	}
	

	cout << "Error: getFaceIndex - failed to find correct blockName: " << endl;
	return -1;
}

int Building::getFaceIndex(BuildingBlock* block, string faceName) {

	for (int i = 0; i < block->faceNames.size(); i++) {
		if (block->faceNames[i] == faceName) {
			return i;
		}
	}

	cout << "Error: getFaceIndex - failed to find faceName" << endl;
	return -1;
}

int Building::getFaceIndex(BuildingBlock* block, string faceName, int startingIndex) {

	for (int i = startingIndex; i < block->faceNames.size(); i++) {
		if (block->faceNames[i] == faceName) {
			return i;
		}
	}

	cout << "Error: getFaceIndex - failed to find faceName" << endl;
	return -1;
}

/*

Changes made:
1. setColor cpp/hpp						PUSHED
2. setName cpp/hpp						PUSHED
3. getBuildingBlock cpp/hpp				PUSHED
4. getFaceIndex cpp/hpp					PUSHED
5. parser.y
	- setColor							PUSHED
	- setName							PUSHED
	- setTexture						PUSHED
	- makeGroup							PUSHED
	- groupInsert						PUSHED
6. setFaceNames - BuildingBlock.cpp/hpp PUSHED
7. setTexture cpp/hpp					PUSHED
8. makeGroup cpp/hpp					PUSHED
9. groupInsert cpp/hpp					PUSHED

10. Deleted vector<int> functions (3) in Split Functionality hpp	PUSHED
11. Added groupLock cpp												PUSHED

12. setColor - quick fix (not on my end)							PUSHED
13. makeGroup BUILD 1												PUSHED
Current focus: makeGroup cpp/hpp

*/

// Recommissioned:
void Building::setColor(string groupName, string blockName, string faceName, float r, float g, float b) {

	// If blockName does not exist, then color whole group
	if (blockName == "null") {
		colorGroup(groupName, faceName, r, g, b);
	}
	else { // Else, color single face
		//int groupIndex = getGroupIndex(groupName);
		BuildingBlock* groupData = blockList[blockList.size() - 1];
		cout << "GroupData Name: " << groupData->name << endl;
		//// Find face index:
		//int faceIndex = -1;
		//faceIndex = getFaceIndex(groupData, faceName);

		//// Get orderingIndex:
		//int orderingIndex = -1;
		//for (int i = 0; i < blockNames.size(); i++) {
		//	if (blockNames[i] == blockName) {
		//		orderingIndex = i;
		//	}
		//}
		////cout << "Ordering Index: " << orderingIndex << "/" << blockNames.size() - 1 << endl;
		//
		//// Get faceIndex:
		//int faceIndex = -1;
		//for (int i = orderingIndex * 6; i < groupData->faceNames.size(); i++) { // 6 = number of faces/block
		//	//cout << i << ": " << faceName << " - " << groupData->faceNames[i] << endl;

		//	if (groupData->faceNames[i] == faceName) {
		//		faceIndex = i;
		//		break;
		//	}
		//}
		////cout << "Face Index: " << faceIndex << "/" << groupData->faceNames.size()-1 << endl;

		int groupIndex = getGroupIndex(groupName);
		int faceIndex = getFaceIndex(groupIndex, blockName, faceName);
		// Traverse over all boxIndices of the key face
		for (int i = 0; i < groupData->faces[faceIndex].size(); i++) {
			groupData->texCoords[i + 6 * faceIndex].boxNorm = { r, g, b };
		} // end i	
	}
} // end setColor

void Building::colorGroup(string groupName, string faceName, float r, float g, float b) {
	BuildingBlock* groupData = blockList[blockList.size() - 1];

	// Get faceIndex:
	int faceIndex = -1;
	for (int i = 0; i < groupData->faceNames.size(); i++) {
		//cout << i << ": " << faceName << " - " << groupData->faceNames[i] << endl;

		if (groupData->faceNames[i] == faceName) {
			faceIndex = i;
			// Traverse over all boxIndices of the key face
			for (int j = 0; j < groupData->faces[faceIndex].size(); j++) {
				groupData->texCoords[j + 6 * faceIndex].boxNorm = { r, g, b };
			} // end i	
		} // end if
	} // end i
} // end colorGroup()

void Building::setName(string newFaceName, string blockName, string faceName) {
	// Find block in blockList:
	BuildingBlock* currentBlock = getBuildingBlock(blockName);
	int faceIndex = getFaceIndex(currentBlock, faceName);
	currentBlock->faceNames[faceIndex] = newFaceName;
	cout << currentBlock->faceNames[faceIndex] << endl;
}

void Building::setBoundingBox(BuildingBlock * block1, BuildingBlock * block2) {
	// Xmin------------------------------
	if (block1->xmin < block2->xmin) {
		xmin = block1->xmin;
	}
	else {
		xmin = block2->xmin;
	}
	// Xmax------------------------------
	if (block1->xmax > block2->xmax) {
		xmax = block1->xmax;
	}
	else {
		xmax = block2->xmax;
	}
	// Ymin------------------------------
	if (block1->ymin < block2->ymin) {
		ymin = block1->ymin;
	}
	else {
		ymin = block2->ymin;
	}
	// Ymax------------------------------
	if (block1->ymax > block2->ymax) {
		ymax = block1->ymax;
	}
	else {
		ymax = block2->ymax;
	}
	// Zmin------------------------------
	if (block1->zmin < block2->zmin) {
		zmin = block1->zmin;
	}
	else {
		zmin = block2->zmin;
	}
	// Zmax------------------------------
	if (block1->zmax > block2->zmax) {
		zmax = block1->zmax;
	}
	else {
		zmax = block2->zmax;
	}

}

void Building::setBoundingBox(vector<boxStruct> boxCoordinates) {
	xmax = boxCoordinates[0].boxPos.x;
	xmin = boxCoordinates[0].boxPos.x;
	ymax = boxCoordinates[0].boxPos.y;
	ymin = boxCoordinates[0].boxPos.y;
	zmax = boxCoordinates[0].boxPos.z;
	zmin = boxCoordinates[0].boxPos.z;
	// Iterate over all box coordinates and store the max/min of each axis
	for (int i = 0; i < boxCoordinates.size(); i++) {
		// Set X bounds
		if (xmax < boxCoordinates[i].boxPos.x) {
			xmax = boxCoordinates[i].boxPos.x;
		}
		if (xmin > boxCoordinates[i].boxPos.x) {
			xmin = boxCoordinates[i].boxPos.x;
		}
		// Set Y bounds
		if (ymax < boxCoordinates[i].boxPos.y) {
			ymax = boxCoordinates[i].boxPos.y;
		}
		if (ymin > boxCoordinates[i].boxPos.y) {
			ymin = boxCoordinates[i].boxPos.y;
		}
		// Set Z bounds
		if (zmax < boxCoordinates[i].boxPos.z) {
			zmax = boxCoordinates[i].boxPos.z;
		}
		if (zmin > boxCoordinates[i].boxPos.z) {
			zmin = boxCoordinates[i].boxPos.z;
		}
	} // end i
}

void Building::printCoords(vector<boxStruct> boxCoords) {
	cout << "Box Coordinates11111111111111111111111111111111111111111111111111111111" << endl;
	for (int i = 0; i < boxCoords.size(); i++) {
		cout << boxCoords[i].boxPos.x << ", " << boxCoords[i].boxPos.y << ", " << boxCoords[i].boxPos.z << endl;
		if ((i+1) % 6 == 0)
			cout << endl;
	}
	cout << "11111111111111111111111111111111111111111111111111111111111111111111111" << endl;
}

void Building::printIndices(vector<int> indices) {
	cout << "Box Indices22222222222222222222222222222222222222222222222222222222222" << endl;
	int j = 0;
	for (int i = 0; i < indices.size(); i++) {
		if (i % 6 == 0) {
			cout << "Face " << j << ": ";
			j++;
		}
			
		cout << indices[i] << " ";
		if ((i + 1) % 6 == 0)
			cout << endl;
	}
	cout << "22222222222222222222222222222222222222222222222222222222222222222222222" << endl;
}

void Building::printFaceNames(vector<string> names) {
	cout << "Face Names3333333333333333333333333333333333333333333333333333333333333" << endl;
	for (int i = 0; i < names.size(); i++) {
		cout << "Face " << i << ": " << names[i] << endl;
	}
	cout << "33333333333333333333333333333333333333333333333333333333333333333333333" << endl;
}

// END MISC UTILITIES----------------------------------------------------------------------------------------------


//vector<int> Building::surfacePointsLieOnFace(BuildingBlock * block, vector<vector<vec3>> newBoxCoords, int face) {
//	//Looks for two points that lie on the perimeter of the face
//	//This makes sure that the new coordinates are bound to the sides of the face
//	int numOfSides;//records the number of sides that lie on the perimeter
//	for (int j = 0; j < newBoxCoords.size(); j++) {//loops through coords
//		vec3 newCoord = newBoxCoords[j][1];
//		vector<vec3> coords = { //coords of four corners
//			block->boxCoordinates[block->faces[face][0]].boxPos,
//			block->boxCoordinates[block->faces[face][1]].boxPos,
//			block->boxCoordinates[block->faces[face][2]].boxPos,
//			block->boxCoordinates[block->faces[face][4]].boxPos
//		};
//		for (int k = 0; k < coords.size(); k++) {//loops through sides of face
//			float allignedX = (newCoord.x - coords[k].x) / (coords[k + 1].x - coords[k].x);
//			float allignedY = (newCoord.y - coords[k].y) / (coords[k + 1].y - coords[k].y);
//			float allignedZ = (newCoord.z - coords[k].z) / (coords[k + 1].z - coords[k].z);
//			if (allignedX == allignedY && allignedY == allignedZ) {//The point lied on the line
//				numOfSides++;
//			}
//		}
//	}
//	if (numOfSides == 2) {//this means there were two points found to lie on the perimeter of the Face
//		return block->faces[face]; 
//	}
//}
//
//vector<int> Building::insertingNewCoords(BuildingBlock * block, vector<vector<vec3>> newBoxCoords, int faceIndex) {
//	//Build boxIndices.
//	block->boxIndices.clear();
//	for (int i = 0; i < block->faces.size(); i++) {//loops faces
//		for (int j = 0; j < block->faces[i].size(); j++) {//loops through indices of faces
//			block->boxIndices.push_back(block->faces[i][j]);
//		}
//	}
//
//	//Now insert coordinates and offset the indices in the same process.
//	//if a coordinate is places. What index that has. Use that in increasing everyone greater. Start looping from back to front. 
//	//this back to front since placing indexes earleir will call for you to keep track and add addtional to the ones later placed.
//	
//	for (int i = 0; i < newBoxCoords.size(); i++) {//loop through the coordinates to be inserted
//		for (int j = 0; j < block->boxCoordinates.size(); j++) {
//			
//		}
//	}
//	//search for newBoxCoords and when index is found 
//	//inverse index is boxCoordinates.size()-i
//	vector<int> empty;
//	return empty;
//}
//
//vector<vector<int>> Building::surfaceRestructuringFaces(BuildingBlock * block, vector<int> splitFace) {
//	//take faces and delete face in question.Keep track
//	int faceIndex = 0;
//	for (int i = 0; i < block->faces.size(); i++) {
//		if (block->faces[i] == splitFace) {
//			faceIndex = i;
//			break;
//		}
//	}
//	block->faces.erase(block->faces.begin() + faceIndex);
//
//	
//	//Surface Split : Macky needs to reformat boxCoordinates to have placed the coordinates in their correct position.
//	//At the exact same moment.This gives the parameters for the boxIndice offsets.
//
//
//
//	//	Zack + Don : insertion of new faces
//	vector<vector<int>> empty;
//	return empty;
//}

// ORIGINAL MERGE CODE FOR REFERENCE:

	// Concatenation of both boxCoordinates into one vector:
	/*mergedBoxCoordinates = block1->boxCoordinates;
	mergedBoxCoordinates.insert(mergedBoxCoordinates.end(), block2->boxCoordinates.begin(), block2->boxCoordinates.end());*/
	// Concatenate boxIndices of both blocks into one vector:
	//vector<int> boxIndices = block1->boxIndices;
	//vector<int> block2Indice;
	//for (int i = 0; i < block2->boxIndices.size(); i++) { // Offset from original indice
	//	int temp = block2->boxIndices[i] + block1->boxCoordinates.size();
	//	block2Indice.push_back(temp);
	//}
	//boxIndices.insert(boxIndices.end(), block2Indice.begin(), block2Indice.end());
	// Concatenate faces:
	/*for (int i = 0; i < boxIndices.size(); i = i + 6) { / 6 = faces[i].size() normally, but now there are going to be 12 faces. Each one needs a unique index
		if (mergeLock) {
			cout << "Face " << faces.size() << ":" << endl;
		}

		// Box indices that make up a single face
		vector<int> temp;
		temp.push_back(boxIndices[i]);
		temp.push_back(boxIndices[i + 1]);
		temp.push_back(boxIndices[i + 2]);
		temp.push_back(boxIndices[i + 3]);
		temp.push_back(boxIndices[i + 4]);
		temp.push_back(boxIndices[i + 5]);
		faces.push_back(temp);
		if (mergeLock) {
			cout << "Indices = (" << temp[0] << ", " << temp[1] << ", " << temp[2] << ", " << temp[3] << ", " << temp[4] << ", " << temp[5] << ")" << endl;
		}
	}*/
	// Concatenate faceNames:
	/*faceNames = block1->faceNames;
	for (int i = 0; i < block2->faceNames.size(); i++) {
		faceNames.push_back(block2->faceNames[i]);
	}*/


	/*
	std::vector<boxStruct> texCoords;
	struct boxStruct coordinate;

	// bot,  back, right, front, left, top
	// blue, green, cyan,  red,  pink, yellow, white, black,
	std::vector<vec3> colorMap = {
		vec3(0, 0 ,1), vec3(0, 1 ,0),
		vec3(0, 1 ,1), vec3(1, 0 ,0),
		vec3(1, 0 ,1), vec3(1, 1 ,0),
		vec3(1, 1, 1), vec3(0, 0, 0),
		vec3(.5,.5,0), vec3(.7,0,.7),
		vec3(.2,0,0), vec3(0, .5,.6),
		vec3(.1,.7,.8)
	};
	*/
	/*
	for (int i = 0; i < faces.size(); i++) { // Runs through faces
		for (int j = 0; j < faces[i].size(); j++) {
			coordinate.boxPos = mergedBoxCoordinates[faces[i][j]].boxPos; //boxCoordinates[indice value]
			coordinate.boxNorm = colorMap[i];
			texCoords.push_back(coordinate);
		}
	}
	vector<int> texIndices;
	for (int i = 0; i < texCoords.size(); i++) {
		texIndices.push_back(i);
	}
	*/