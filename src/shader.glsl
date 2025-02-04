@vs vs_basic
in vec4 pos;
void main() {
    gl_Position = pos;
}
@end

@fs fs_basic
out vec4 frag_color;
void main() {
    frag_color = vec4(0.8, 0.7, 0.5, 1.0);
}
@end

@program basic vs_basic fs_basic

@vs vs_triangle
in vec4 position;
in vec4 color0;

out vec4 color;

void main() {
    gl_Position = position;
    color = color0;
}
@end

@fs fs_triangle
in vec4 color;
out vec4 frag_color;

void main() {
    frag_color = color;
}
@end

@program triangle vs_triangle fs_triangle

