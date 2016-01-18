#version 330 core

//UNIFORMS
uniform vec4 ambient;//couleur ambiante
uniform vec4 diffuse;//couleur diffuse
uniform vec4 specular;//couleur spéculaire
uniform vec4 fogColor;
uniform float specularPower;//intensité spéculaire (réflexion)
uniform vec3 lightDirection;//vecteur direction de la lumière
uniform float camDepth;//distance maximum vue

//TEXTURES
uniform sampler2D texture_0;//textures de base
uniform sampler2D texture_1;
uniform sampler2D texture_2;
//uniform sampler2D texture_3;
uniform sampler2D texture_4;//textures normales
uniform sampler2D texture_5;
uniform sampler2D texture_6;
//uniform sampler2D texture_7;

//ENTREES
in vec2 TexCoordX;//cordonnées de texture
in vec2 TexCoordY;//..
in vec2 TexCoordZ;//..
in vec3 ViewDir;//orientation 
in mat3 tangentSpace;//matrice représentant un espace tangent
in float height;
//SORTIE
out vec4 out_color;

float rand(vec2 co){
    return fract(sin(dot(co.xy ,vec2(12.9898,78.233))) * 43758.5453);
}

void main( void )
{
  
   float Fog = gl_FragCoord.z/gl_FragCoord.w;//calcul du brouillard
   Fog/=camDepth*2;

   vec3 normal = tangentSpace[2];//on recupère le vecteur tangent
   vec3 n = normal;
   n*=n;
   vec4 col,nrm;
 
  vec4 col0 = texture2D(texture_0,TexCoordX)*(n.x)+texture2D(texture_0,TexCoordY)*(n.y)+texture2D(texture_0,TexCoordZ)*(n.z);
  vec4 col1 = texture2D(texture_1,TexCoordX)*(n.x)+texture2D(texture_1,TexCoordY)*(n.y)+texture2D(texture_1,TexCoordZ)*(n.z);
  vec4 col2 = texture2D(texture_2,TexCoordX)*(n.x)+texture2D(texture_2,TexCoordY)*(n.y)+texture2D(texture_2,TexCoordZ)*(n.z);
  
  vec4 nrm0 = texture2D(texture_4,TexCoordX)*(n.x)+texture2D(texture_4,TexCoordY)*(n.y)+texture2D(texture_4,TexCoordZ)*(n.z);
  vec4 nrm1 = texture2D(texture_5,TexCoordX)*(n.x)+texture2D(texture_5,TexCoordY)*(n.y)+texture2D(texture_5,TexCoordZ)*(n.z);
  vec4 nrm2 = texture2D(texture_6,TexCoordX)*(n.x)+texture2D(texture_6,TexCoordY)*(n.y)+texture2D(texture_6,TexCoordZ)*(n.z);
  
  vec4 col12 = mix(col1,col2,0.3);
  col = mix(col12,col0,0.3);
  vec4 nrm12 = mix(nrm1,nrm2,0.3);
  nrm = mix(nrm12,nrm0,0.3);
  //vec4 col10 = mix(col1,col0,0.2);
  
   vec3 realNormal = normalize((2.0*nrm.xyz-1.0)*tangentSpace);//normale
   vec3 lightDir = normalize(lightDirection);//on normalise le vecteur direction de la lumière
   vec3 view = normalize(ViewDir);//on normalise le vecteur orientation
   float NdL = max(0.0,dot(realNormal,lightDir));//facteur de luminosité
   vec3 reflVect = normalize(reflect(lightDir,nrm.xyz));//vecteur de réflection
   float RdL = max(0.0,dot(reflVect,view));//facteur de réflexion
      
   vec4 fVambient,fVdiffuse,fVspecular;
   
   fVambient = col*ambient;//calcul de la couleur ambiante
   fVdiffuse = diffuse*col*NdL;//calcul de la couleur diffuse
   fVspecular = specular*pow(RdL,specularPower)*col;//calcul de la couleur speculaire
   out_color = mix(fVambient+fVdiffuse+fVspecular,fogColor,Fog);
}
