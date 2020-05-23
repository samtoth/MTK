//
// Created by sammy on 22/05/2020.
//
#ifdef TARGET_WEB
#include "WebAudioWrapper.h"
#include <emscripten.h>
#include <emscripten/val.h>
#include <iostream>

namespace MTK::Audio {
	WebAudioWrapper::WebAudioWrapper(){
	    EM_ASM(console.log("Initializing WebAudio"););
        EM_ASM(
                Module.audioContext = new AudioContext();
                );

		EM_ASM((
			class MTKAudioProcessor extends AudioWorkletProcessor {
				constructor() {
					// The super constructor call is required.
					super();
				}

				process(inputs, outputs, parameters) {
					const input = inputs[0];
					const output = outputs[0];
					for (let channel = 0; channel < input.length; ++channel) {
                            const outputChannel = output[channel];
                            outputChannel[0] = Module.output();
						}
					}

					return;
				}

				registerProcessor('MTKAudioProcessor', GainProcessor);
		));
	}

	int WebAudioWrapper::setup(AudioSettings settings) {
		EM_ASM(
			context.audioWorklet.addModule('mtk-audio-processor.js').then(() => {

				// After the resolution of module loading, an AudioWorkletNode can be
				// constructed.
				let gainWorkletNode = new AudioWorkletNode(context, 'gain-processor');

				// AudioWorkletNode can be interoperable with other native AudioNodes.
				oscillator.connect(gainWorkletNode).connect(context.destination);
				oscillator.start();
			});
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