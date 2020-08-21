#version 330 core
out vec4 FragColor;

in VS_OUT {
    vec3 FragPos;
    vec2 TexCoords;
    vec3 TangentLightPos;
    vec3 TangentViewPos;
    vec3 TangentFragPos;
} fs_in;

uniform sampler2D texture_diffuse1;
uniform sampler2D texture_normal1;
uniform sampler2D texture_emission1;

uniform vec3 lightPos;
uniform vec3 viewPos;
uniform float emission_strength;

void main()
{           
    vec3 normal = texture(texture_normal1, fs_in.TexCoords).rgb;

    normal = normalize(normal * 2.0 - 1.0);
   
    vec3 color = texture(texture_diffuse1, fs_in.TexCoords).rgb;

    vec3 ambient = 0.1 * color;

    vec3 lightDir = normalize(fs_in.TangentLightPos - fs_in.TangentFragPos);
    float diff = max(dot(lightDir, normal), 0.0);
    vec3 diffuse = diff * color;

    vec3 viewDir = normalize(fs_in.TangentViewPos - fs_in.TangentFragPos);
    vec3 reflectDir = reflect(-lightDir, normal);
    vec3 halfwayDir = normalize(lightDir + viewDir);  
    float spec = pow(max(dot(normal, halfwayDir), 0.0), 32.0);

    vec3 specular = vec3(0.2) * spec;

    vec3 emission = emission_strength * texture(texture_emission1, fs_in.TexCoords).rgb;

    FragColor = vec4(ambient + diffuse + specular + emission, 1.0);
}