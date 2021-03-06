#ifndef MUSICTOOLKIT_ISCALE_H
#define MUSICTOOLKIT_ISCALE_H


#include <vector>
namespace MTK::Core {

	///\brief An interface to classes that define finite, linear collections of notes
    class IScale {
    public:
        virtual float distanceFromNote(float frequency) = 0;

        //virtual float operator[](unsigned long int degree) = 0;
    protected:
        /// \brief collection of frequency ratios mapped by the scale
        const std::vector<float> frequencyCollection;
    };
}

#endif //MUSICTOOLKIT_ISCALE_H
