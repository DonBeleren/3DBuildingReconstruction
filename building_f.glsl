#version 330

smooth in vec4 fragNorm1;	// Interpolated model-space normal
uniform sampler2D tex_unit;
//this may need to be a 3D.


out vec4 outCol1;	// Final pixel color was 4 where textureizing. Also was vec2 originizally


void main() {
	// Visualize normals as colors
	outCol1 = vec4(fragNorm1);// + texture(tex_unit, fragNorm1) * 0.5;
	//outCol1 = normalize(fragNorm1);// * 0.5f + vec4(0.5f); 

}
