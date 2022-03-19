#pragma once
#include "ExpressionLexer.h"
#include <string>
#include <vector>
#include <iostream>
#include <memory>

using std::vector;
using std::cout;

enum class ChunkType {
	PRINT,
	EXPRESSION,
	JUMP,
	DEFAULT,
};

class Chunk
{
protected:
	ChunkType type;
	int line;
public:
	Chunk(ChunkType type, int ln);
	virtual void print() = 0;
	virtual int execute() = 0;
};

class PrintChunk : Chunk
{
private:
	std::string print_statement{};
public:
	PrintChunk(std::string print_statement, int ln);
	void print();
	int execute() { return 1; }
};


class JumpChunk : Chunk
{
	friend class ChunkInterpreter;
private:
	int jump_offset{1};
public:
	JumpChunk(int jump_off, int ln);
	void print();
	int execute() { return jump_offset; }
};



class ChunkInterpreter
{
private:
	int position{};
	friend class JumpChunk;
public:
	vector<std::unique_ptr<Chunk>> chunk_vec{};
	ChunkInterpreter() {}

};

