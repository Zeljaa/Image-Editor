#ifndef IMAGEEDITOR_H
#define IMAGEEDITOR_H

#include "Pixel.h"
#include <string>
using namespace std;

class ImageEditor {
public:
	ImageEditor();
	// Destruktor klase je posebna funkcija clanica klase (kao i konstruktor) koja se poziva kada brisemo objekat neke klase (pozivom operatora delete)
	// Potrebna je u svim klasama sa pokazivackim poljima da bismo na ispravan nacin izbrisali ono na sta oni pokazuju
	// Naime pozivom operatora delete mi brisemo samo taj konkretan objekat i sva njegova polja, medjutim ukoliko u objektu postoji pokazivac koji ukazuje na neki drugi deo memorije, taj deo memorije ce ostati neizbrisan (curenje memorije)
	// Dakle potrebno je da definisemo destruktor koji brise sve iz dinamicke memorije sto je nas objekat u toku programa kreirao (u ovom slucaju, samo dinamicku matricu)
	~ImageEditor();

	void loadImage(string& image);
	string saveImage();

	void invertColors();
	void toGrayScale();
	void rotateByX();
	void rotateByY();
	void blur();
	void rotateLeft() { id = 1; }
	void rotateRight() { id = 2; }

private:

	static int id;
	Pixel*** pixels;
	Pixel*** invertPixels;
	int height, width;

	// Privatne pomocne funkcije clanice koje nisu dostupne van nase klase
	// Prenos pozicije 'pos' je po referenci da bi se nakon poziva funkcije nastavilo citanje stringa od odgovarajuce pozicije
	int readNumber(string& str, int& pos);
	Pixel* readPixel(string& str, int& pos);

	void makeMatrix();
	void invertMatrix();
};

#endif