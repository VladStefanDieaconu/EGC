#version 330

// TODO: get vertex attributes from each location
layout(location = 0) in vec3 v_position;
layout(location = 1) in vec3 v_color;
layout(location = 3) in vec3 v_normal;


// Uniform properties
uniform mat4 Model;
uniform mat4 View;
uniform mat4 Projection;
uniform float time;

// TODO: output values to fragment shader
out vec3 frag_color;
out vec3 frag_normal;


void main()
{
	// TODO: send output to fragment shader
	//change color
	frag_color = vec3(0, 1, 0);
	frag_normal = v_normal;

	// TODO: compute gl_Position
	gl_Position = Projection * View * Model * vec4(v_position, 1.0);
}