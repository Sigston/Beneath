#pragma once
#include "stdafx.h"
using namespace std;

class Buffer
{
public:
	Buffer();

	bool				drawLine(const string &input, const int lineNumber, const int beginAt = 0);
	bool				drawChunk(const vector<string> &input, const int lineNumber, const int beginAt = 0);
	bool				drawDialogue(const string &input, const int lines = 1);

	void				print();
	void				clear();

private:
	const int			WIDTH;
	const int			HEIGHT;

	vector<string>		mBufferVector;

};

