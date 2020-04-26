//
// Created by samt on 23/04/2020.
//

#ifndef MUSICTOOLKIT_IAUDIOUNIT_H
#define MUSICTOOLKIT_IAUDIOUNIT_H

/// \class IAudioUnit
/// \brief Defines the functionality for a generator.
///

class IAudioUnit{
public:
    virtual float tick() = 0;


};


#endif //MUSICTOOLKIT_IAUDIOUNIT_H
