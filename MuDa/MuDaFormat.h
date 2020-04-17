/**
 * \class MuDaFormat
 * \brief MuDaFormat holds information about the contents of a MuDa file or stream
 */

#ifndef MUSICTOOLKIT_MUDAFORMAT_H
#define MUSICTOOLKIT_MUDAFORMAT_H


class MuDaFormat {

public:
    int getTickRate() const {
        return tickRate;
    }

    void setTickRate(int tickRate) {
        MuDaFormat::tickRate = tickRate;
    }

private:

    int tickRate;    //!< Number of delta values per second

};


#endif //MUSICTOOLKIT_MUDAFORMAT_H
