#include "ChunkInterpreter.h"

Chunk::Chunk(ChunkType type, int ln) :type{ type }, line{ln}
{

}

PrintChunk::PrintChunk(std::string str, int ln) : Chunk{ChunkType::PRINT, ln} {
	print_statement = str;
}

void PrintChunk:: print(){
	std::cout << "Statement: " << print_statement <<", line: " << line <<std::endl;
}

JumpChunk::JumpChunk(int jump_off, int ln) : Chunk{ChunkType::JUMP, ln}, jump_offset{ jump_off } {

}

void JumpChunk::print() {
	std::cout << "Jump: " << jump_offset << ", line: " << line << std::endl;
}