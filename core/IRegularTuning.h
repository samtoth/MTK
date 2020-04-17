/**
 * \class IRegularTuning
 * \brief An interfaces that defines the functionality of a "regular tuning system". This is the base class for regular temperaments of any rank - including equal division tuning system
 * \author Sam
 */
#ifndef MUSICTOOLKIT_IREGULARTUNING_H
#define MUSICTOOLKIT_IREGULARTUNING_H


#include <string>
#include <Eigen/Dense>

class IRegularTuning {
public:

    ///
    /// \param frequency
    /// \return The name of the note that the given frequency is closest to
    virtual std::string getNoteName(float frequency) = 0;
    virtual std::string getNoteName(Eigen::VectorXf coordinate) = 0;
    virtual float distanceFromNote(float frequency) = 0;

    virtual float getFrequency(Eigen::VectorXf coordinate) = 0;
    virtual Eigen::VectorXf getCoordinate(float frequency) = 0;

    virtual float getFundamentalFrequency() const {return fundamentalFrequency;}
    virtual void setFundamentalFrequency(float fundamentalFrequency) { IRegularTuning::fundamentalFrequency = fundamentalFrequency;}

private:
    float fundamentalFrequency{};
};



#endif //MUSICTOOLKIT_IREGULARTUNING_H
