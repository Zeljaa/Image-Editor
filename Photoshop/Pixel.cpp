#include "Pixel.h"

Pixel::Pixel() {
	this->R = this->G = this->B = 0;
}

Pixel::Pixel(unsigned char R, unsigned char G, unsigned char B) {
	this->R = R;
	this->G = G;
	this->B = B;
}

unsigned char Pixel::getRed() {
	return this->R;
}

unsigned char Pixel::getGreen() {
	return this->G;
}

unsigned char Pixel::getBlue() {
	return this->B;
}

void Pixel::setRed(unsigned char R) {
	this->R = R;
}

void Pixel::setGreen(unsigned char G) {
	this->G = G;
}

void Pixel::setBlue(unsigned char B) {
	this->B = B;
}

void Pixel::invertColors() {
	this->R = ~(this->R);
	this->G = ~(this->G);
	this->B = ~(this->B);
}

void Pixel::toGrayscale() {
	this->R = this->B = this->G = 0.3 * this->R + 0.59 * this->G + 0.11 * this->B;
}
