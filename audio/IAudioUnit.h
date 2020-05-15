//
// Created by samt on 23/04/2020.
//

#ifndef MUSICTOOLKIT_IAUDIOUNIT_H
#define MUSICTOOLKIT_IAUDIOUNIT_H
namespace MTK::Audio {

#define PARAM_t std::map<uint32_t, float>
    /// \class IAudioUnit
    /// \brief Defines the functionality for a generator.
    ///
    class IAudioUnit {
    public:
        IAudioUnit() {}

        virtual float output() = 0;

    };
}
#endif //MUSICTOOLKIT_IAUDIOUNIT_H
