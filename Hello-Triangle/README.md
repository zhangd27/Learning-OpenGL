# Notes

## Result
![avatar](figure/result.png)

## Send data between shaders
```
#version 330 core
layout (location = 0) in vec3 aPos;
out vec4 vertexColor;
void main()
{
    gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);
    vertexColor = vec4(0.5f, 0.0f, 0.0f, 1.0f);
}
```
```
#version 330 core
out vec4 FragColor;
in vec4 vertexColor;
void main()
{
  FragColor = vertexColor;
}
```
