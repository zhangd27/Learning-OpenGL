# Notes

## Result
![avatar](figure/result.png)

## Send data between shaders
```
#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;
out vec3 vertexColor;
void main()
{
    gl_Position = vec4(aPos, 1.0);
    vertexColor = aColor;
}
```
```
#version 330 core
out vec4 FragColor;
in vec3 vertexColor;
void main()
{
  FragColor = vec4(vertexColor, 1.0);
}
```

## Uniform
```
uniform vec4 globalColor;
```
