#include <stddef.h>
#include <stdint.h>

typedef uint32_t Id;

typedef struct {
    Id _id;
    char *location;
    uint8_t *image;
    size_t width;
    size_t height;
    size_t cell_size; // must be a box
} SpriteSheet;

typedef struct {
    Id _id;
    size_t pos[2];
    Id sprite_id;
} Sprite;

typedef struct {
    Id _id;
    Id animation[8]; // id of sprite
    float timing;
} SpriteAnimation;

