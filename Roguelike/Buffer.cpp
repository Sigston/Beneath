#include "stdafx.h"
#include "Buffer.h"


Buffer::Buffer()
: WIDTH(65)
, HEIGHT(24)
{
	for (int x = 0; x < HEIGHT; ++x)
		mBufferVector.push_back(string(WIDTH, ' '));
}

bool Buffer::drawLine(const string &input, const int lineNumber, const int beginAt)
{
	if (input.size() + beginAt <= WIDTH && lineNumber < HEIGHT)
	{
		mBufferVector[lineNumber].replace(beginAt, input.size(), input);
		return true;
	} else {
		return false;
	}
}

bool Buffer::drawChunk(const vector<string> &input, const int lineNumber, const int beginAt)
{
	if (input.size() + lineNumber <= HEIGHT)
	{
		for (auto s : input)
		{
			if (s.size() + beginAt <= WIDTH)
			{
				mBufferVector[lineNumber].replace(beginAt, input.size(), s);
			} else { return false; }
		}
	} else { return false; }
}

bool Buffer::drawDialogue(const string &input, const int lines)
{
	// Count the number of words in the string.
	stringstream sstream(input);
	string word;
	int wordCount = 0;
	while (sstream >> word)
		++wordCount;

	// If there are more lines than words, we can't print this message.
	if (lines > wordCount)
		return false;

	// Work out of we can evenly split words along lines.
	bool evenSplit = false;
	if (wordCount % lines == 0)
		evenSplit = true;
	 
	if (evenSplit)
	{
		// Break up the input into each line.
		int wordsPerLine = wordCount / lines;

		stringstream stringStream(input);
		string line;
		vector<string> eachLine;

		for (int y = 0; y != lines; ++y)
		{
			for (int x = 0; x != wordsPerLine; ++x)
			{
				stringStream >> word;
				line.append(word + " ");
			}
			eachLine.push_back(line);
			line = "";
		}

		// Works out the longest line, and quits if this is too large for the buffer.
		int longestLine = 0;
		for (auto s : eachLine)
		{
			if (s.length() > longestLine)
				longestLine = s.length();
		}
		if (longestLine > WIDTH + 10)
			return false;

		// Create the empty box.
		string top(longestLine + 3, '-');
		string inside(longestLine + 2, ' ');
		inside.insert(inside.begin(), '|');
		inside.insert(inside.end(), '|');

		// Draw the box inside the buffer.
		int whereToPrint = 6;
		mBufferVector[whereToPrint - 1].replace(3, top.size(), top);
		for (int x = 0; x != lines; ++x)
			mBufferVector[whereToPrint + x].replace(3, inside.size(), inside);
		mBufferVector[whereToPrint + lines].replace(3, top.size(), top);

		// Draw the text inside the box.
		for (int x = 0; x != lines; ++x)
			mBufferVector[whereToPrint + x].replace(5, eachLine[x].size(), eachLine[x]);
	}
	else
	{
		// TODO: Odd numbered words.
		return false;
	}

	return true;
}

void Buffer::print()
{
	system("cls");
	for (auto s : mBufferVector)
		cout << s << "\n";
}

void Buffer::clear()
{
	for (auto &s : mBufferVector)
		for (auto &c : s)
			c = ' ';
}