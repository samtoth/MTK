#ifndef MUSICTOOLKIT_IFILTER_H
#define MUSICTOOLKIT_IFILTER_H

#include <type_traits>
template <typename T>
struct fail : std::false_type
{
};

#include <IAudioUnit.h>
namespace MTK::Audio {
	/// An Audio unit who's tick function takes a sample as an input
	class IFilter : public IAudioUnit {
	public:
		IFilter() = default;

		template<typename T = bool>
		float output(){
			static_assert (fail<T>::value, "Do not use!");
		}
		virtual float output(float sample) = 0;

	protected:
	};
}
#endif //MUSICTOOLKIT_IFILTER_H
