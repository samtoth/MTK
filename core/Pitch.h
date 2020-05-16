/**
 * \class Pitch
 * \brief
 * \author Sam
 */

#ifndef MUSICTOOLKIT_PITCH_H
#define MUSICTOOLKIT_PITCH_H

namespace MTK::Core {
    class Pitch {
    public:
        /// \brief Initialize Pitch class
        /// \param frequency
        Pitch(float frequency);

        /// \brief return local member frequency
        /// \return frequency
        float getFrequency() const { return frequency; }

        /// \brief Set frequency
        /// \param frequency
        void setFrequency(float frequency) { Pitch::frequency = frequency; }

    private:
        float frequency;
    };
}
#endif //MUSICTOOLKIT_PITCH_H