#ifndef MUSICTOOLKIT_IFILTER_H
#define MUSICTOOLKIT_IFILTER_H

#include <IAudioUnit.h>
#include <stdexcept>

namespace MTK::Audio {
	/// An Audio unit who's tick function takes a sample as an input
	class IFilter : public IAudioUnit {
	public:
		IFilter() = default;

		float output() override {
			throw std::runtime_error("Do not use!");
			return 0;
		}
		virtual float output(float sample) = 0;

	protected:
	};
}
#endif //MUSICTOOLKIT_IFILTER_H
