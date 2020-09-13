#version 450

layout(binding = 1) uniform sampler2D texSampler;

layout(location = 0) in vec3 fragColor;
layout(location = 1) in vec2 fragTexCoord;

layout(location = 0) out vec4 outColor;

void main()
{
    outColor = vec4(fragColor, 1.0) * texture(texSampler, fragTexCoord);
    //outColor = vec4(pow(texture(texSampler, fragTexCoord).r, 1.0/2.2), pow(texture(texSampler, fragTexCoord).g, 1.0/2.2), pow(texture(texSampler, fragTexCoord).b, 1.0/2.2), 1.0);
    //outColor = texture(texSampler, fragTexCoord);
    //outColor = vec4(fragTexCoord, 0.0, 1.0);
    //outColor = vec4(fragColor, 1.0);
}
