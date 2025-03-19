
#ifndef SSD1306_H_
#define SSD1306_H_

#define DISPLAY_I2C_ADDR  0x3C
#define DISPLAY_WIDTH 128
#define DISPLAY_HEIGHT 64

void InitDisplay(void);
int SendI2C(unsigned int);
int SendI2C2(unsigned int, unsigned int);
int SendDisplayBuffer(unsigned int *, unsigned int);

#endif /* SSD1306_H_ */
