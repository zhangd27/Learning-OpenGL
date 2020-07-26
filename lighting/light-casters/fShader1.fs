#version 330 core
struct Material {
    sampler2D diffuse;
    sampler2D specular;
    float shininess;
    //sampler2D emission;
};

uniform Material material;

struct Light {
    vec3 position;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    
    float constant;
    float linear;
    float quadratic;
};

uniform Light light;

out vec4 FragColor;
in vec2 TexCoords;
in vec3 Normal;
in vec3 FragPos;
uniform vec3 viewPos;
uniform float time;

void main() {
    float distance    = length(light.position - FragPos);
    float attenuation = 1.0 / (light.constant + light.linear * distance +
                    light.quadratic * (distance * distance));
    // ambient
    vec3 ambient = light.ambient * vec3(texture(material.diffuse, TexCoords));
    // diffuse
    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(light.position - FragPos);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = light.diffuse * diff * vec3(texture(material.diffuse, TexCoords));
    //specluar
    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 reflectDir = reflect(-lightDir, norm);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    vec3 specular = light.specular * spec * vec3(texture(material.specular, TexCoords));
    //emission
    vec3 emission = vec3(0.0);
    //if (texture(material.specular, TexCoords).r == 0.0)   /*rough check for blackbox inside spec texture */
    //{
        /*apply emission texture */
      //  emission = texture(material.emission, TexCoords).rgb;
        /*some extra fun stuff with "time uniform" */
        //emission = texture(material.emission, TexCoords + vec2(0.0,time)).rgb;   /*moving */
        //emission = emission * (sin(time) * 0.5 + 0.5) * 2.0;                     /*fading */
    //}
    
    ambient  *= attenuation;
    diffuse  *= attenuation;
    specular *= attenuation;
    vec3 result = ambient + diffuse + specular + emission;
    FragColor = vec4(result, 1.0);
}

