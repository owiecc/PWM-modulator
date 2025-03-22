
#ifndef GFX_H_
#define GFX_H_

typedef struct DisplayBuffer {
    unsigned int xSize;
    unsigned int ySize;
    unsigned int *data;
} DisplayBuffer;

extern DisplayBuffer buffer;

#endif /* GFX_H_ */
