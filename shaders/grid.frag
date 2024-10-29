#version 460 core

in vec4 fPos;

out vec4 color;

const float lineWidth = 0.01;

float roughLine(float objective, float value) {
    return step(objective - lineWidth, value) - step(objective + lineWidth, value);
}

void main() {
    vec3 pos = fPos.xyz / fPos.w;

    float xAxis = roughLine(0, pos.z);
    float zAxis = roughLine(0, pos.x);

    float xParallels = roughLine(floor(pos.z * 2.0), pos.z * 2.0);
    float zParallels = roughLine(floor(pos.x * 2.0), pos.x * 2.0);

    color = vec4(0.3, 0.3, 0.3, 1.0) * (xParallels + zParallels);
    color += vec4(1.0, 0.0, 0.0, 1.0) * xAxis + vec4(0.0, 0.0, 1.0, 1.0) * zAxis;
    color.a *= fPos.w;
    // color = vec4(fPos.www, 1.0);
}
