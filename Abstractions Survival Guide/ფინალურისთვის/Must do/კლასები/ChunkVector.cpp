#include "ChunkVector.h"
#include "error.h"

ChunkVector::ChunkVector() {
	head = NULL;
	curSize = 0;
}

ChunkVector::~ChunkVector() {
	while (head != NULL) {
		delete[] head->arr;
		Chunk* tmp = head;
		head = tmp->next;
		delete tmp;
	}
}

int ChunkVector::size() {
	return curSize;
}

int ChunkVector::get(int index) {
	Chunk *cur, *prev;
	index = info(index, cur, prev);
	return cur->arr[index];
}

void ChunkVector::set(int index, int value) {
	Chunk *cur, *prev;
	index = info(index, cur, prev);
	cur->arr[index] = value;
}

void ChunkVector::add(int value) {
	insert(curSize, value);
}

void ChunkVector::remove(int index) {
	Chunk *cur, *prev;
	index = info(index, cur, prev);

	if (cur->used == 1) {
		prev->next = cur->next;
		delete[] cur->arr;
		delete cur;
	} else {
		for (int i=index; i<cur->used-1; i++) {
			cur->arr[i] = cur->arr[i+1];
		}
		cur->used--;
	}

	curSize--;
}

int ChunkVector::getChunkNumber() {
	int n = 0;
	Chunk* tmp = head;
	while (tmp != NULL) {
		tmp = tmp->next;
		n++;
	}
	return n;
}

void ChunkVector::insert(int index, int value) {
	Chunk *cur, *prev;
	index = info(index, cur, prev);
	if (cur->used == CHUNK_SIZE) {
		/* Initialize Chunk */
		Chunk* chunk = new Chunk;
		chunk->arr = new int[CHUNK_SIZE];
		chunk->used = 0;
		/* Insert Chunk */
		chunk->next = cur->next;
		cur->next = chunk;
		/**/
		int half = CHUNK_SIZE - CHUNK_SIZE/2;
		/**/
		for (int j=half-1; j<CHUNK_SIZE; j++) {
			chunk->arr[j-half+1] = cur->arr[j];
		}
		/**/
		cur->used = CHUNK_SIZE/2;
		chunk->used = half;
	}
	for (int i=cur->used-1; i>index; i--) {
		cur->arr[i] = cur->arr[i-1];
	}
	cur->arr[index] = value;
	cur->used++;
	curSize++;
}

int ChunkVector::info(int index, Chunk*& cur, Chunk*& prev) {
	cur = head;
	prev = NULL;
	while (true) {
		if (index < cur->used) return index;
		index -= cur->used;
		prev = cur;
		cur = cur->next;
	}
}