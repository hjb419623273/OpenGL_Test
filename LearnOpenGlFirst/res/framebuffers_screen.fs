#version 330 core
out vec4 FragColor;
in vec2 TexCoords;
uniform sampler2D screenTexture;

void main()
{
	//正常输出颜色
	//vec3 col = texture(screenTexture, TexCoords).rgb;
	//FragColor = vec4(col, 1);

	//颜色反相 
	//FragColor = vec4(vec3(1.0 - texture(screenTexture, TexCoords)), 1);

	//灰度
	//移除场景中除了黑白灰之外所有的颜色
	FragColor = texture(screenTexture, TexCoords);
	//float average = (FragColor.r + FragColor.g + FragColor.b) / 3;
	//加权通道 灰色更真实点
	float = average = 0.2126 * FragColor.r + 0.7152 * FragColor.g + 0.0722 * FragColor.b;
	FragColor = vec4(average, average, average, 1);
}