
#ifndef SSD1306_H_
#define SSD1306_H_

#define DISPLAY_I2C_ADDR 0x3C
#define DISPLAY_WIDTH 128
#define DISPLAY_HEIGHT 64
#define DISPLAY_BUFFER_SIZE (DISPLAY_WIDTH * DISPLAY_HEIGHT/8)

void InitDisplay(void);
int UpdateDisplay(unsigned int *);

//extern unsigned int buffer[];

#endif /* SSD1306_H_ */
