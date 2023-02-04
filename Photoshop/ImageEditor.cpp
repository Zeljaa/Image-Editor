#include "ImageEditor.h"

int ImageEditor::id = 0;

ImageEditor::ImageEditor() {
	this->width = this->height = 0;
	this->pixels = nullptr;
}

ImageEditor::~ImageEditor() {
	for (int i = 0; i < this->height; i++) {
		for (int j = 0; j < this->width; j++) {
			delete this->pixels[i][j];
		}
		delete[] this->pixels[i];
	}
	delete[] this->pixels;
}

int ImageEditor::readNumber(string& str, int& pos) {
	int number = 0;
	while (str[pos] != '\n') {
		number = number * 10 + (str[pos] - '0');
		pos++;
	}
	pos++;
	return number;
}

Pixel* ImageEditor::readPixel(string& str, int& pos) {
	Pixel* pixel = new Pixel;
	pixel->setRed(readNumber(str, pos));
	pixel->setGreen(readNumber(str, pos)); 
	pixel->setBlue(readNumber(str, pos)); 
	return pixel;
}

void ImageEditor::makeMatrix() {
	this->pixels = new Pixel** [this->height];
	for (int i = 0; i < this->height; i++) {
		this->pixels[i] = new Pixel* [this->width];
	}
}

void ImageEditor::loadImage(string& image) {
	// Vrsimo algoritamsku dekompoziciju i delimo parsiranje ovog stringa na nekoliko delova
	int pos = 0;

	// Read dimensions
	this->width = readNumber(image, pos);
	this->height = image[pos] != '-' ? readNumber(image, pos) : this->width;
	pos += 2;

	this->makeMatrix();
	long s = image.length();
	// Read pixels
	for (int i = 0, j = 0; pos < s;) {
		pixels[i][j++] = readPixel(image, pos);
		if (j == width) {
			j = 0;
			i++;
		}
	}
}

string ImageEditor::saveImage() {
	string image;

	if (id == 1) {
		image.append(to_string(this->height));
		image.append("\n");
		if (this->width != this->height) {
			image.append(to_string(this->width));
			image.append("\n");
		}
		image.append("-\n");
		for (int j = this->width - 1; j >= 0; j--) {
			for (int i = 0; i < this->height; i++) {
				image.append(to_string(this->pixels[i][j]->getRed()));
				image.append("\n");
				image.append(to_string(this->pixels[i][j]->getGreen()));
				image.append("\n");
				image.append(to_string(this->pixels[i][j]->getBlue()));
				image.append("\n");
			}
		}
	}
	else if (id == 2) {

		image.append(to_string(this->height));
		image.append("\n");
		if (this->width != this->height) {
			image.append(to_string(this->width));
			image.append("\n");
		}
		image.append("-\n");
		for (int j = 0; j <this->width; j++) {
			for (int i = this->height-1; i >=0; i--) {
				image.append(to_string(this->pixels[i][j]->getRed()));
				image.append("\n");
				image.append(to_string(this->pixels[i][j]->getGreen()));
				image.append("\n");
				image.append(to_string(this->pixels[i][j]->getBlue()));
				image.append("\n");
			}
		}

	}
	else {
		image.append(to_string(this->width));
		image.append("\n");
		if (this->width != this->height) {
			image.append(to_string(this->height));
			image.append("\n");
		}
		image.append("-\n");
		for (int i = 0; i < this->height; i++) {
			for (int j = 0; j < this->width; j++) {
				image.append(to_string(this->pixels[i][j]->getRed()));
				image.append("\n");
				image.append(to_string(this->pixels[i][j]->getGreen()));
				image.append("\n");
				image.append(to_string(this->pixels[i][j]->getBlue()));
				image.append("\n");
			}
		}
	}
	
	return image;
}

void ImageEditor::invertColors() {
	for (int i = 0; i < this->height; i++) {
		for (int j = 0; j < this->width; j++) {
			this->pixels[i][j]->invertColors();
		}
	}
}

void ImageEditor::toGrayScale() {
	for (int i = 0; i < this->height; i++) {
		for (int j = 0; j < this->width; j++) {
			this->pixels[i][j]->toGrayscale();
		}
	}
}

void ImageEditor::rotateByX() {

	Pixel** tmp = nullptr;
	int p = 0, k = this->height - 1;

	while (p < k) {

		tmp = this->pixels[p];
		this->pixels[p++] = this->pixels[k];
		this->pixels[k--] = tmp;
	}

}

void ImageEditor::rotateByY() {

	Pixel* tmp = nullptr;
	int p, k;
	for (int i = 0; i < this->height; i++) {

		p = 0;
		k = this->width - 1;
		while (p < k) {
			tmp = this->pixels[i][p];
			this->pixels[i][p++] = this->pixels[i][k];
			this->pixels[i][k--] = tmp;
		}

	}

}


void ImageEditor::blur() {
	
	int sum;

	for (int i = 0; i < this->height; i++) {
		for (int j = 0; j < this->width; j++) {

			if (i == 0 && j == 0) {
				sum = this->pixels[i + 1][j]->getRed() + this->pixels[i][j + 1]->getRed();
				this->pixels[i][j]->setRed(unsigned char(sum/2));
				sum = this->pixels[i + 1][j]->getGreen() + this->pixels[i][j + 1]->getGreen();
				this->pixels[i][j]->setGreen(unsigned char(sum / 2));
				sum = this->pixels[i + 1][j]->getBlue() + this->pixels[i][j + 1]->getBlue();
				this->pixels[i][j]->setBlue(unsigned char(sum / 2));

			}

			else if (i == 0 && j == this->width - 1) {

				sum = this->pixels[i][j-1]->getRed() + this->pixels[i+1][j]->getRed();
				this->pixels[i][j]->setRed(unsigned char(sum / 2));
				sum = this->pixels[i][j-1]->getGreen() + this->pixels[i+1][j]->getGreen();
				this->pixels[i][j]->setGreen(unsigned char(sum / 2));
				sum = this->pixels[i][j-1]->getBlue() + this->pixels[i+1][j]->getBlue();
				this->pixels[i][j]->setBlue(unsigned char(sum / 2));

			}

			else if (i == this->height - 1 && j == 0) {
				sum = this->pixels[i - 1][j]->getRed() + this->pixels[i][j + 1]->getRed();
				this->pixels[i][j]->setRed(unsigned char(sum / 2));
				sum = this->pixels[i - 1][j]->getGreen() + this->pixels[i][j + 1]->getGreen();
				this->pixels[i][j]->setGreen(unsigned char(sum / 2));
				sum = this->pixels[i - 1][j]->getBlue() + this->pixels[i][j + 1]->getBlue();
				this->pixels[i][j]->setBlue(unsigned char(sum / 2));
			}
			
			else if (i == this->height - 1 && j == this->width - 1) {

				sum = this->pixels[i - 1][j]->getRed() + this->pixels[i][j - 1]->getRed();
				this->pixels[i][j]->setRed(unsigned char(sum / 2));
				sum = this->pixels[i - 1][j]->getGreen() + this->pixels[i][j - 1]->getGreen();
				this->pixels[i][j]->setGreen(unsigned char(sum / 2));
				sum = this->pixels[i - 1][j]->getBlue() + this->pixels[i][j - 1]->getBlue();
				this->pixels[i][j]->setBlue(unsigned char(sum / 2));
			}

			else if (j == 0 && i > 0 && i < this->height - 1) {

				sum = this->pixels[i - 1][j]->getRed() + this->pixels[i+1][j]->getRed() + this->pixels[i][j+1]->getRed();
				this->pixels[i][j]->setRed(unsigned char(sum / 3));
				sum = this->pixels[i - 1][j]->getGreen() + this->pixels[i + 1][j]->getGreen() + this->pixels[i][j + 1]->getGreen();
				this->pixels[i][j]->setGreen(unsigned char(sum / 3));
				sum = this->pixels[i - 1][j]->getBlue() + this->pixels[i + 1][j]->getBlue() + this->pixels[i][j + 1]->getBlue();
				this->pixels[i][j]->setBlue(unsigned char(sum / 3));
			}
			else if (i == this->height - 1 && j > 0 && j < this->width -1) {
				
				sum = this->pixels[i][j+1]->getRed() + this->pixels[i - 1][j]->getRed() + this->pixels[i][j - 1]->getRed();
				this->pixels[i][j]->setRed(unsigned char(sum / 3));
				sum = this->pixels[i][j+1]->getGreen() + this->pixels[i - 1][j]->getGreen() + this->pixels[i][j - 1]->getGreen();
				this->pixels[i][j]->setGreen(unsigned char(sum / 3));
				sum = this->pixels[i][j+1]->getBlue() + this->pixels[i - 1][j]->getBlue() + this->pixels[i][j - 1]->getBlue();
				this->pixels[i][j]->setBlue(unsigned char(sum / 3));
			}

			else if (j == this->width - 1 && i > 0 && i < this->height - 1) {

				sum = this->pixels[i - 1][j]->getRed() + this->pixels[i + 1][j]->getRed() + this->pixels[i][j - 1]->getRed();
				this->pixels[i][j]->setRed(unsigned char(sum / 3));
				sum = this->pixels[i - 1][j]->getGreen() + this->pixels[i + 1][j]->getGreen() + this->pixels[i][j - 1]->getGreen();
				this->pixels[i][j]->setGreen(unsigned char(sum / 3));
				sum = this->pixels[i - 1][j]->getBlue() + this->pixels[i + 1][j]->getBlue() + this->pixels[i][j - 1]->getBlue();
				this->pixels[i][j]->setBlue(unsigned char(sum / 3));
			}

			else if (i == 0 && j > 0 && j < this->width - 1) {

				sum = this->pixels[i + 1][j]->getRed() + this->pixels[i][j-1]->getRed() + this->pixels[i][j + 1]->getRed();
				this->pixels[i][j]->setRed(unsigned char(sum / 3));
				sum = this->pixels[i + 1][j]->getGreen() + this->pixels[i][j-1]->getGreen() + this->pixels[i][j + 1]->getGreen();
				this->pixels[i][j]->setGreen(unsigned char(sum / 3));
				sum = this->pixels[i + 1][j]->getBlue() + this->pixels[i][j-1]->getBlue() + this->pixels[i][j + 1]->getBlue();
				this->pixels[i][j]->setBlue(unsigned char(sum / 3));
			}

			else {

				sum = this->pixels[i - 1][j]->getRed() + this->pixels[i + 1][j]->getRed() + this->pixels[i][j + 1]->getRed() + this->pixels[i][j-1]->getRed();
				this->pixels[i][j]->setRed(unsigned char(sum / 4));
				sum = this->pixels[i - 1][j]->getGreen() + this->pixels[i + 1][j]->getGreen() + this->pixels[i][j + 1]->getGreen() + this->pixels[i][j-1]->getGreen();
				this->pixels[i][j]->setGreen(unsigned char(sum / 4));
				sum = this->pixels[i - 1][j]->getBlue() + this->pixels[i + 1][j]->getBlue() + this->pixels[i][j + 1]->getBlue() + this->pixels[i][j-1]->getBlue();
				this->pixels[i][j]->setBlue(unsigned char(sum / 4));
			}
		}
	}

}

