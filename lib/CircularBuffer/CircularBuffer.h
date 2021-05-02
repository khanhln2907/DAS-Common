/*
 CircularBuffer.h - Circular buffer library for Arduino.
 Copyright (c) 2017 Roberto Lo Giacco.

 This program is free software: you can redistribute it and/or modify
 it under the terms of the GNU Lesser General Public License as 
 published by the Free Software Foundation, either version 3 of the 
 License, or (at your option) any later version.

 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.

 You should have received a copy of the GNU General Public License
 along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#ifndef CIRCULAR_BUFFER_H_
#define CIRCULAR_BUFFER_H_
#include <stdint.h>
#include <stddef.h>

#ifdef CIRCULAR_BUFFER_DEBUG
//#include <Print.h>
#include <stdio.h>
#endif


template<typename T> class CircularBuffer {
	
private:
	T* buffer;
	T* head;
	T* tail;
	size_t count;

public:
	///**
	// * The buffer capacity: read only as it cannot ever change.
	// */
	const size_t capacity;

	// Delete standard constructor
	CircularBuffer() = delete;

	//constexpr CircularBuffer();
	
	/**
	 * Disables copy constructor
	 */
	CircularBuffer(const CircularBuffer&) = delete;
	CircularBuffer(CircularBuffer&&) = delete;

	/**
	 * Disables assignment operator
	 */
	CircularBuffer& operator=(const CircularBuffer&) = delete;
	CircularBuffer& operator=(CircularBuffer&&) = delete;

	CircularBuffer<T>(const size_t Capacity) : capacity(Capacity)
	{
		//this->buffer[Capacity] = { 0 };
		this->buffer = new T[capacity]();
		count = 0;

		head = buffer;
		tail = buffer;

	};

	~CircularBuffer<T>()
	{
		// Clear memory assigned in constructor
		delete[] this->buffer;
	}


	/**
	 * Adds an element to the beginning of buffer: the operation returns `false` if the addition caused overwriting an existing element.
	 */
	inline bool enqueue(T value) {
		
		// If HEAD is at the start of the buffer, wrap around to the end
		if (head == buffer) {
			head = buffer + capacity;
		}

		// Save value left of HEAD
		*--head = value;

		// If buffer is full
		if (count == capacity) {
			// if TAIL is at the start of the array
			if (tail-- == buffer) {
				// wrap TAIL around to the end of the buffer
				tail = buffer + capacity - 1;
			}
			return false;
		}
		else {
			if (count++ == 0) {
				tail = head;
			}
			return true;
		}
	}

	/**
	 * Adds an element to the end of buffer: the operation returns `false` if the addition caused overwriting an existing element.
	 */
	inline bool push(T value) {
		if (++tail == buffer + capacity) {
			tail = buffer;
		}
		*tail = value;
		if (count == capacity) {
			if (++head == buffer + capacity) {
				head = buffer;
			}
			return false;
		}
		else {
			if (count++ == 0) {
				head = tail;
			}
			return true;
		}
	}

	/**
	 * Removes an element from the beginning of the buffer.
	 * *WARNING* calling this operation on an empty buffer has an unpredictable behaviour.
	 */
	inline T pop() {
		T result = *head++;
		if (head >= buffer + capacity) {
			head = buffer;
		}
		count--;
		return result;
	}

	/**
	 * Removes an element from the end of the buffer.
	 * *WARNING* calling this operation on an empty buffer has an unpredictable behaviour.
	 */
	inline T dequeue() {
		T result = *tail--;
		if (tail < buffer) {
			tail = buffer + capacity - 1;
		}
		count--;
		return result;
	}


	/**
	 * Returns the newest element in the buffer, which was added last
	 */
	inline T first() const {
		return *head;
	}

	/**
	 * Returns the oldest element in the buffer, which was added first
	 */
	inline T last() const {
		return *tail;
	}

	/**
	 * Array-like access to buffer.
	 * Attention: Element[0] is the oldest element
	 */
	inline T operator [](size_t index) const {
		//return *(buffer + ((head - buffer + index) % capacity));
		auto offset = (tail - buffer - index + capacity) % capacity;

		return *(buffer + offset % capacity);
	}

	/**
	 * Returns how many elements are actually stored in the buffer.
	 */
	inline size_t size() const {
		return count;
	}

	/**
	 * Returns how many elements can be safely pushed into the buffer.
	 */
	inline size_t available() const {
		return capacity - count;
	}

	/**
	 * Returns `true` if no elements can be removed from the buffer.
	 */
	bool inline isEmpty() const {
		return count == 0;
	}

	/**
	 * Returns `true` if no elements can be added to the buffer without overwriting existing elements.
	 */
	bool inline isFull() const {
		return count == capacity;
	}

	/**
	 * Resets the buffer to a clean status, making all buffer positions available.
	 */
	void inline clear() {
		head = tail = buffer;
		count = 0;
	}



#ifdef CIRCULAR_BUFFER_DEBUG

	#include <string.h>
		public:
		inline void debug()
		{
			printf("COUNT: %d,\tHEAD: %p,\tTAIL: %p\n", count, head, tail);

			// print entire buffer
			for (size_t i = 0; i < capacity; i++) {
				printf("0x%04x ", *(buffer+i));
			}
			printf("\n");

			for (size_t i = 0; i < capacity; i++)
			{
				if (head == buffer + i) {
					printf("|HEAD| ");
				}
				if (tail == buffer + i) {
					printf("|TAIL| ");
				}

				if ((head != buffer + i) && (tail != buffer +i))
				{
					printf("|----| ");
				}
			}
			printf("\n\n");
		}
//
//
	//	void inline debugFn(Print* out, void (*printFunction)(Print*, T))
	//	{
	//		for (IT i = 0; i < capacity; i++) {
	//			int hex = (int)buffer + i;
	//			out->print(hex, HEX);
	//			out->print("  ");
	//			printFunction(out, *(buffer + i));
	//			if (head == buffer + i) {
	//				out->print(" head");
	//			}
	//			if (tail == buffer + i) {
	//				out->print(" tail");
	//			}
	//			out->println();
	//	}
	//}


#endif

};




#endif
