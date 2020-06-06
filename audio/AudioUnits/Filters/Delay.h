//
// Created by sammy on 13/05/2020.
//

#ifndef MUSICTOOLKIT_DELAY_H
#define MUSICTOOLKIT_DELAY_H

#include "IFilter.h"
#include <AudioSampleBuffer.h>

namespace MTK::Audio {
    class Delay : IFilter {
    public:
		Delay(int delay, int maxDelay);

    	float output(float sample) override;

    protected:
    	int maxDelay;
    	int delay;

    	AudioSampleBuffer<float> buf;
	};
}


#endif //MUSICTOOLKIT_DELAY_H
