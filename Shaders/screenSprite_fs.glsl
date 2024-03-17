#version 410

layout(location = 0) out vec4 frag_colour;

in vec2 TexCoords;

uniform sampler2D spriteTexture;
uniform vec2 textureSize2;

void main()
{
	ivec2 size = textureSize(spriteTexture, 0);
	//vec2 uv = gl_FragCoord.xy / textureSize.xy;
	//vec2 uv = TexCoords / textureSize.xy;
	vec2 uv = vec2(TexCoords.x, TexCoords.y);
	//vec2 uv = gl_FragCoord.xy / textureSize.x;
	vec4 colour = texture(spriteTexture, uv ).rgba;
	colour = vec4(colour.r, colour.g, colour.b, colour.a);
	
	//if(colour.a < 0.1)
	//{
	//	discard;
	//}

	//frag_colour = vec4(1.0, 0.0, 0.0, 1.0);
	//frag_colour = vec4(1,0,0,0.5);
	frag_colour = colour;
	//frag_colour = vec4(1,1,1,1);

}