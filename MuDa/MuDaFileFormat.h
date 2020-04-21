/**
 * \class MuDaFileFormat
 * \brief MuDaFileFormat holds information about the contents of a MuDa file or stream
 */

#ifndef MUSICTOOLKIT_MUDAFILEFORMAT_H
#define MUSICTOOLKIT_MUDAFILEFORMAT_H

struct MuDaHeader{
    char signature[4];
    uint16_t version;
    uint32_t deltaPerSecond;
};

struct MuDaMessage{
    uint32_t delta;
    uint8_t eventType;
};

struct MuDaFileFormat{
    MuDaHeader header;
    std::vector<MuDaMessage> data;
};

#endif //MUSICTOOLKIT_MUDAFILEFORMAT_H
