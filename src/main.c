
#include <stdio.h>

#include "sokol_app.h"
#include "sokol_gfx.h"
#include "sokol_glue.h"
#include "sokol_log.h"

#include "shader_glsl.h"

#include "animation.c"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

static struct {
    sg_pipeline pip;
    sg_bindings bind;
    sg_pass_action pass_action;
} state;

static SpriteSheet sheets[] = {
    { .location = "assets/fractions.png" },
};

void frame(void) {
    sg_begin_pass(&(sg_pass){
            .action = state.pass_action,
            .swapchain = sglue_swapchain(),
    });
    sg_apply_pipeline(state.pip);
    sg_apply_bindings(&state.bind);
    sg_draw(0, 6, 1);
    sg_end_pass();

    sg_commit();
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

void init(void) {

    sg_setup(&(sg_desc){
        .environment = sglue_environment(),
    });

    float vertices[] = {
        -0.5f, -0.5f, 0.5f,    1.0f, 0.0f, 0.0f, 1.0f,
        -0.5f,  0.5f, 0.5f,    0.0f, 1.0f, 0.0f, 1.0f,
        0.5f,  -0.5f, 0.5f,    0.0f, 0.0f, 1.0f, 1.0f,
 
        -0.5f,  0.5f, 0.5f,    0.0f, 1.0f, 0.0f, 1.0f,
         0.5f, -0.5f, 0.5f,    0.0f, 0.0f, 1.0f, 1.0f,
         0.5f,  0.5f, 0.5f,    1.0f, 0.0f, 1.0f, 1.0f,
    };

    state.bind.vertex_buffers[0] = sg_make_buffer(&(sg_buffer_desc){
        .data = SG_RANGE(vertices),
    });
    
    for (size_t i = 0; i < sizeof(sheets); i++) {
        int width, height, number_of_channels;
        stbi_uc *pixels = stbi_load(sheets[i].location, &width, &height, &number_of_channels, 0);

        sheets[i].width = width;
        sheets[i].height = height;
        sheets[i].image = pixels;

        if (pixels) {
            state.bind.images[i] = sg_make_image(&(sg_image_desc){
                .width = width,
                .height = height,
                .pixel_format = SG_PIXELFORMAT_RGBA8,
                .data.subimage[0][0] = {
                    .ptr = pixels,
                    .size = (size_t)(width * height * 4),
                },
            });

            state.bind.samplers[i] = sg_make_sampler(&(sg_sampler_desc){
                .min_filter = SG_FILTER_NEAREST,
                .mag_filter = SG_FILTER_LINEAR,
            });
        }
    }

    state.pip = sg_make_pipeline(&(sg_pipeline_desc){
        .shader = sg_make_shader(triangle_shader_desc(sg_query_backend())),
            /*.primitive_type = SG_PRIMITIVETYPE_LINES,*/
        .layout = {
            .attrs = {
                /*[ATTR_sprite_pos].format = SG_VERTEXFORMAT_FLOAT3,*/
                /*[ATTR_sprite_texcoord0].format = SG_VERTEXFORMAT_SHORT2N,*/
                [ATTR_triangle_position].format = SG_VERTEXFORMAT_FLOAT3,
                [ATTR_triangle_color0].format = SG_VERTEXFORMAT_FLOAT4,
            },
        },
    });

    state.pass_action = (sg_pass_action) {
        .colors[0] = { .load_action = SG_LOADACTION_CLEAR, .clear_value = { 0.2f, 0.2f, 0.2f, 1.0f } }
    };

}

void cleanup(void) {
    sg_shutdown();
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

