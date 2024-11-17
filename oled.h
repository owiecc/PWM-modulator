
#ifndef OLED_H_
#define OLED_H_

#define I2C_SLAVE_ADDR  0x3C

void InitI2C(void);
int SendI2C(unsigned int);
int SendI2C2(unsigned int, unsigned int);

#endif /* OLED_H_ */
