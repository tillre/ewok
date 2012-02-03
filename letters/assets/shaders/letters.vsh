
attribute vec3 a_position;
attribute vec2 a_texCoord;
attribute float a_alpha;
attribute vec3 a_colorTransform;

uniform mat4 u_mvp;

varying vec2 v_texCoord;
varying float v_alpha;
varying vec3 v_colorTransform;

void main() {
  v_texCoord = a_texCoord;
  v_alpha = a_alpha;
  v_colorTransform = a_colorTransform;

  gl_Position = u_mvp * vec4(a_position, 1.0);
}
