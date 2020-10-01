#version 330

layout(location = 0) in vec3 buildingPos;		// Model-space position
layout(location = 1) in vec3 buildingNorm;		// Model-space normal

smooth out vec4 fragNorm1;	// Model-space interpolated normal

uniform mat4 xform;			// Model-to-clip space transform
//uniform bool uniColorMode; //y
//uniform bool uniTexMode; //y
//uniform int texDemo; //y



void main() {
	//gl_Position = vec4(buildingPos.x, buildingPos.y, 10, 1.0);
	gl_Position = xform * vec4(buildingPos.x,buildingPos.y,buildingPos.z-2, 1.0);
	
	//fragNorm1 = vec2(0, 0)
	
	
	fragNorm1 = vec4(buildingNorm, 0.1f); 
	
	

	//gl_Position = xform1 * vec4(wallPos, depth + 0.1f, 1.0);
	//fragNorm1 = vec4(buildingColor, 0.1f)* 0.8 + vec4(.7, 0.5, 0.7, 1.0);

	
	
}
