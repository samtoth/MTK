//
// Created by sammy on 13/05/2020.
//

#ifndef MUSICTOOLKIT_DELAY_H
#define MUSICTOOLKIT_DELAY_H

#include "IFilter.h"
#include <VarLenSampleBuffer.h>

namespace MTK::Audio {
    class Delay : public IFilter {
    public:
		Delay(int delay, int maxDelay);

    	float output(float sample) override;

    	float front();

    	/// Sets the delay in samples. Must be less than maxDelay
    	void setDelay(int samples);
    protected:
    	int maxDelay;
    	int delay;

    	VarLenSampleBuffer<float> buf;
	};
}


#endif //MUSICTOOLKIT_DELAY_H
