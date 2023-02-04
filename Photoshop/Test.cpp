#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <fstream>
#include <sstream>
#include <Python.h>
#include "ImageEditor.h"


using namespace std;


int main() {

	Py_Initialize();

	//PyObject* obj = Py_BuildValue("s", "imageload.py");
	
	/*FILE* scriptFile = _Py_fopen_obj(obj, "r+");
	if (scriptFile)
		PyRun_SimpleFileEx(scriptFile, "imageload.py", 1);*/

	ImageEditor* img = new ImageEditor;
	
	PyRun_SimpleString("import sys");
	PyRun_SimpleString("import os");
	PyRun_SimpleString("sys.path.append(os.getcwd())");

	PyObject* pName, * pModule, * pFunc, * pArgs, * pValue;

	pName = PyUnicode_FromString((char*)"imageload");
	
	pModule = PyImport_Import(pName);
	
	pFunc = PyObject_GetAttrString(pModule,(char*)"convert");
	pArgs = PyTuple_Pack(1, PyUnicode_FromString((char*)"jabuka.jpg"));
	pValue = PyObject_CallObject(pFunc, pArgs);

	auto result = _PyUnicode_AsString(pValue);
	
	string name = result;
	string out = result;
	out.append("izmenjeno.txt");
	name.append(".txt");
	

	ifstream input;
	input.open(name);
	stringstream ss;
	ss << input.rdbuf();
	string image = ss.str();
	input.close();
	
	img->loadImage(image);
	//img->invertColors();
	//img->rotateByX();
	for (int i = 0; i < 10; i++)
		img->blur();

	img->rotateRight();
	image = img->saveImage();

	ofstream output;
	output.open(out);
	output << image;
	output.close();

	pName = PyUnicode_FromString((char*)"imagesave");

	pModule = PyImport_Import(pName);

	pFunc = PyObject_GetAttrString(pModule, (char*)"toimage");
	pArgs = PyTuple_Pack(1, PyUnicode_FromString(result));
	pValue = PyObject_CallObject(pFunc, pArgs);

	/*PyObject* out = Py_BuildValue("s", "imagesave.py");
	FILE* f = _Py_fopen_obj(out, "r+");
	if (f)
		PyRun_SimpleFile(f, "imagesave.py", 1);*/

	Py_Finalize();

	delete img;

	return 0;
}