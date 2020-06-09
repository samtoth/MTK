//
// Created by sammy on 13/05/2020.
//

#include "Delay.h"
namespace MTK::Audio {
	float Delay::output(float sample){
		auto ret = buf.front();
        buf.push(sample);
		return ret;
	}

	Delay::Delay(int _delay, int _maxDelay) : delay(_delay), maxDelay(_maxDelay), buf(delay, maxDelay) {

	}

    void Delay::setDelay(int samples) {
        buf.setLength(samples);
        delay = samples;
    }

    float Delay::front() {
        return buf.front();
    }
}