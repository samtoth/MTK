//
// Created by sammy on 22/05/2020.
//
#ifdef TARGET_WEB
#include "WebAudioWrapper.h"
#include <emscripten.h>

namespace MTK::Audio {
	WebAudioWrapper::WebAudioWrapper() {
		/*EM_ASM(
		    console.log("Initializing WebAudio");

			class GainProcessor extends AudioWorkletProcessor {
				constructor() {
					// The super constructor call is required.
					super();
				}

				process(inputs, outputs, parameters) {
					const input = inputs[0];
					const output = outputs[0];
					for (let channel = 0; channel < input.length; ++channel) {
						const outputChannel = output[channel];
						outputChannel[0] = 0.5;
						}
					}

					return true;
				}

				registerProcessor('gain-processor', GainProcessor);
		);*/
	}

	int WebAudioWrapper::setup(AudioSettings settings) {
		EM_ASM(
			/*const context = new AudioContext();
			context.audioWorklet.addModule('mtk-audio-processor.js').then(() => {

				// After the resolution of module loading, an AudioWorkletNode can be
				// constructed.
				let gainWorkletNode = new AudioWorkletNode(context, 'gain-processor');

				// AudioWorkletNode can be interoperable with other native AudioNodes.
				oscillator.connect(gainWorkletNode).connect(context.destination);
				oscillator.start();
			});*/
		);
		return 0;
	}
	int WebAudioWrapper::startStream() {
		return 0;
	}
	int WebAudioWrapper::stopStream() {
		return 0;
	}
	int WebAudioWrapper::terminate() {
		return 0;
	}
}
#endif