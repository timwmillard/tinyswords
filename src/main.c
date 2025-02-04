
#include <stdio.h>

#include "sokol_app.h"
#include "sokol_gfx.h"
#include "sokol_glue.h"
#include "sokol_log.h"

void frame(void) {
}

void input(const sapp_event* event) {
    #pragma clang diagnostic ignored "-Wswitch"
    switch(event->type) {
        case SAPP_EVENTTYPE_KEY_DOWN:
            if (event->key_code == SAPP_KEYCODE_ESCAPE) {
                sapp_request_quit();
            }
            break;
    }
}

static struct {
    sg_pipeline pipeline;
    sg_bindings bindings;
} state;

void init(void) {
    sg_setup(&(sg_desc){
        .environment = sglue_environment(),
    });

    /*float vertices[] = {*/
    /*     0.0f,  0.5f, 0.5f,     1.0f, 0.0f, 0.0f, 1.0f,*/
    /*     0.5f, -0.5f, 0.5f,     0.0f, 1.0f, 0.0f, 1.0f,*/
    /*    -0.5f, -0.5f, 0.5f,     0.0f, 0.0f, 1.0f, 1.0f*/
    /*};*/
    /**/
    /*state.bindings.vertex_buffers[0] = sg_make_buffer(&(sg_buffer_desc){*/
    /*    .data = SG_RANGE(vertices),*/
    /*});*/
    /**/
    /*state.pipeline = sg_make_pipeline(&(sg_pipeline_desc){*/
    /*    .shader = sg_make_shader(&(sg_shader_desc){*/
            /*.vs = {*/
            /*    .source =*/
            /*        "#version 330\n"*/
            /*        "in vec4 position;\n"*/
            /*        "in vec4 color0;\n"*/
            /*        "out vec4 color;\n"*/
            /*        "void main() {\n"*/
            /*        "  gl_Position = position;\n"*/
            /*        "  color = color0;\n"*/
            /*        "}\n"*/
            /*},*/
            /*.fs = {*/
            /*    .source =*/
            /*        "#version 330\n"*/
            /*        "in vec4 color;\n"*/
            /*        "out vec4 frag_color;\n"*/
            /*        "void main() {\n"*/
            /*        "  frag_color = color;\n"*/
            /*        "}\n"*/
            /*},*/
    /*    }),*/
    /*    .layout = {*/
    /*    },*/
    /*});*/

}

void cleanup(void) {
    printf("cleanup\n");
}

sapp_desc sokol_main(int argc, char* argv[]) {
    (void)argc;
    (void)argv;
    return (sapp_desc) {
        .width = 640,
        .height = 480,
        .init_cb = init,
        .frame_cb = frame,
        .event_cb = input,
        .cleanup_cb = cleanup,
        .window_title = "Tiny Swords",
        .logger.func = slog_func
    };
}

