#pragma once
#define CHUNK_SIZE 5

class ChunkVector
{
public:
	ChunkVector(void);
	~ChunkVector(void);
	int size();
	int get(int index);
	void set(int index, int value);
	void add(int value);
	void remove(int index);
	int getChunkNumber();
	void insert(int index, int value);
private:
	struct Chunk {
		int* arr;
		int used;
		Chunk* next;
	};
	Chunk* head;
	int curSize;
	int info(int index, Chunk*& cur, Chunk*& prev);
};
