//
// Created by samt on 16/05/2020.
//

#ifndef MUSICTOOLKIT_AUDIOSAMPLEBUFFER_H
#define MUSICTOOLKIT_AUDIOSAMPLEBUFFER_H

#include <queue>
#include <deque>
#include <memory>
namespace MTK::Audio {
	template<typename T, typename Container = std::deque<T>>
	class AudioSampleBuffer {
	public:
	    explicit AudioSampleBuffer(int _length) : length(_length) {
	    }

		void push(const T& value) {
			if (c.size() == length)
			{
				c.pop_front();
			}
			c.push_back(value);
		}

		void pop() {
	        c.pop_front();
	    }

	    T front(){
	        return c.front();
	    }

        bool empty() {
            return c.empty();
        }
        size_t size(){
            return c.size();
        }

    protected:
		int length;
	    std::deque<T> c;
	};
}

#endif //MUSICTOOLKIT_AUDIOSAMPLEBUFFER_H
