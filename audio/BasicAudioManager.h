#ifndef MUSICTOOLKIT_BASICAUDIOMANAGER_H
#define MUSICTOOLKIT_BASICAUDIOMANAGER_H


#include <IAudioManager.h>
#include <IInstrument.h>
namespace MTK::Audio {
    /**
     * \class BasicAudioManager
     * \brief A basic implementation of IAudioManager that has a list of instruments and a basic mixer
     * \author Sam
     */
    class BasicAudioManager : public IAudioManager {
    public:
        explicit BasicAudioManager() {}

        /// \Returns index of instrument or -1 if there is an error
        int addInstrument(IInstrument *instrument);

        /// \brief set the level of the instrument. 0 represents 1/(2*number of instruments) * 2^(level)
        void setLevel(int i, float l);

        float getLevel(int i);

        IInstrument *instrument(int i);

        void NoteOn(uint32_t chanel, uint32_t voiceID, std::map<uint32_t, float> parameters) override;

        void NoteChange(uint32_t chanel, uint32_t voiceID, std::map<uint32_t, float> parameters) override;

        void NoteOff(uint32_t chanel, uint32_t voiceID, std::map<uint32_t, float> parameters) override;

        void SystemParamChange(std::map<uint32_t, float> parameters) override;

        void Panic(uint32_t channel) override;

        float output() override;

    private:
        std::vector<std::pair<IInstrument *, float>> instruments;
    };
}
#endif //MUSICTOOLKIT_BASICAUDIOMANAGER_H