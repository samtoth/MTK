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
	class AudioSampleBuffer : public std::queue<T, Container> {
	public:
		void setLength(int _maxLength)
		{
			maxLength = _maxLength;
		}

		void push(const T& value) {
			if (this->size() == maxLength)
			{
				this->c.pop_front();
			}
			std::queue<T, Container>::push(value);
		}

	private:
		int maxLength;
	};
}

#endif //MUSICTOOLKIT_AUDIOSAMPLEBUFFER_H
