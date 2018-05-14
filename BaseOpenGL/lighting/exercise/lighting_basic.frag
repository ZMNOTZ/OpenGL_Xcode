#version 330 core
out vec4 FragColor;

in vec3 LightPos;
in vec3 Normal;
in vec3 FragPos;

uniform vec3 lightColor;
uniform vec3 objectColor;

void main(){
   //ambient
   float ambientStrength = 0.1;
   vec3 ambient = lightColor * ambientStrength;

   //diffuse
   vec3 lightDir = normalize(LightPos - FragPos);
   vec3 normal = normalize(Normal);
   float diff = max(dot(lightDir,normal),0);
   vec3 diffuse = diff * lightColor;

   //specular
   float specularStrength = 0.5;
   vec3 viewDir = normalize(-FragPos);
   vec3 reflectDir = reflect(-lightDir,normal);
   float spec = pow(max(dot(-viewDir,reflectDir),0)32);
   vec3 specular = specularStrength * spec * lightColor;

   FragColor = vec4((ambient + diffuse + specular) * objectColor,1.0f);
}