
varying mediump vec2 v_texCoord;
varying mediump float v_alpha;
varying mediump vec3 v_colorTransform;

uniform mediump sampler2D u_texture;

void main() {
  mediump vec4 color = texture2D(u_texture, v_texCoord);
  color = vec4(color.x * v_colorTransform.x,
               color.y * v_colorTransform.y,
               color.z * v_colorTransform.z,
               v_alpha * color.w);
  
  gl_FragColor = color;
}
