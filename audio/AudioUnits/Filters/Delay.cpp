//
// Created by sammy on 13/05/2020.
//

#include "Delay.h"
namespace MTK::Audio {
	float Delay::output(float sample){
		return 0;
	}

	Delay::Delay(int _delay, int _maxDelay) : delay(_delay), maxDelay(_maxDelay) {
		buf = AudioSampleBuffer<float>();
		buf.setLength(maxDelay);
	}
}