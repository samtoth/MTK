//
// Created by samt on 19/05/2020.
//
#ifdef TARGET_WEB
#ifndef MUSICTOOLKIT_WEBAUDIOWRAPPER_H
#define MUSICTOOLKIT_WEBAUDIOWRAPPER_H

#include <emscripten.h>
#include <Wrappers/IAudioWrapper.h>
namespace MTK::Audio {
	class WebAudioWrapper : public IAudioWrapper {
	public:
		WebAudioWrapper();

		int setup(AudioSettings settings) override;
		int startStream() override;
		int stopStream() override;
		int terminate() override;
	};
}
#endif //MUSICTOOLKIT_WEBAUDIOWRAPPER_H
#endif //TARGET_WEB