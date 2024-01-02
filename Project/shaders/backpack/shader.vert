#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTexCoords;

out vec2 TexCoords;
out vec3 v_frag_coord;
out vec3 v_normal;


uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
uniform mat4 itM;

void main()
{
    TexCoords = aTexCoords;    
    gl_Position = projection * view * model * vec4(aPos, 1.0);
    v_normal = vec3(itM * vec4(aNormal, 1.0));
    vec4 frag_coord = model*vec4(aPos, 1.0);
    v_frag_coord = frag_coord.xyz;
}