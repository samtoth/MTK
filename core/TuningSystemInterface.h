/**
 * \class TuningSystemInterface
 * \brief 
 * \author Sam
 */
#ifndef MUSICTOOLKIT_TUNINGSYSTEMINTERFACE_H
#define MUSICTOOLKIT_TUNINGSYSTEMINTERFACE_H


#include <string>

class TuningSystemInterface {
public:
    TuningSystemInterface() {}
    virtual ~TuningSystemInterface() {}

    virtual std::string getNoteName(float frequency);

};


#endif //MUSICTOOLKIT_TUNINGSYSTEMINTERFACE_H
