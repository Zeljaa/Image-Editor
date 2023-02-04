#ifndef PIXEL_H
#define PIXEL_H

class Pixel {
public:
	Pixel();
	Pixel(unsigned char R, unsigned char G, unsigned char B);

	unsigned char getRed();
	unsigned char getGreen();
	unsigned char getBlue();

	void setRed(unsigned char R);
	void setGreen(unsigned char G);
	void setBlue(unsigned char B);

	void invertColors();
	void toGrayscale();

private:
	unsigned char R, G, B;
};

#endif