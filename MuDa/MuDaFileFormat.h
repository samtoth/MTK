/**
 * \class MuDaFileFormat
 * \brief MuDaFileFormat holds information about the contents of a MuDa file or stream
 */

#ifndef MUSICTOOLKIT_MUDAFILEFORMAT_H
#define MUSICTOOLKIT_MUDAFILEFORMAT_H

#include <fstream>
#include <iostream>
#include <cstring>

namespace MuDa {
    enum MessageCodes{
        start = 0x00,
        end = 0x01,
        noteOn = 0x02,
        noteChange = 0x03,
        noteOff = 0x04,
        systemParamChange = 0x05,
        panic = 0x06
    };

    enum DataSizes{
        channelNumber = sizeof(uint32_t),
        paramCount = sizeof(uint32_t),
        paramId = sizeof(uint32_t),
        floatData = sizeof(float)
    };

    struct MuDaHeader {
        char signature[4];
        uint16_t version;
        uint32_t deltaPerSecond;
    };

    struct MuDaMessage {
        uint32_t delta;
        uint16_t messageType;
        char* data;

        //TODO: Add static functions to generate specific MuDa messages with correct data eg:
        //      static MuDaMessage NoteOnMessage(int channelID, vector<pair<int paramID, float value>> parameters)

        void write(std::ofstream *outFile){
            outFile->write((char *) &(delta), sizeof(uint32_t));
            outFile->write((char *) &(messageType), sizeof(uint16_t));
            char *temp = data;
            switch(messageType){
                case start:
                case end:
                    break;
                case noteOn:
                case noteChange:
                case noteOff: {
                    outFile->write(temp, DataSizes::channelNumber); //Write channel number
                    temp += DataSizes::channelNumber * 8; //Increment the pointer by the size of (ChannelNumber) in bytes * 8 (bits per byte)
                    int16_t nParams = 0;
                    memcpy((char *) (&nParams), temp, DataSizes::paramCount); //Copy the number of parameters to memory
                    outFile->write(temp, DataSizes::paramCount); //Write the number of parameters to file
                    temp += DataSizes::paramCount *
                            8;  //Increment the pointer by the size of (paramCount) in bytes * 8 (bits per byte)
                    for (int i = 0; i < nParams; i++) {
                        outFile->write(temp, DataSizes::paramId);
                        temp += DataSizes::paramId * 8;

                        outFile->write(temp, DataSizes::floatData);
                        temp += DataSizes::floatData * 8;
                    }
                    return;
                }
                case systemParamChange: {
                    int16_t nParams = 0;
                    memcpy((char *) (&nParams), temp, DataSizes::paramCount); //Copy the number of parameters to memory
                    outFile->write(temp, DataSizes::paramCount); //Write the number of parameters to file
                    temp += DataSizes::paramCount *
                            8;  //Increment the pointer by the size of (paramCount) in bytes * 8 (bits per byte)
                    for (int i = 0; i < nParams; i++) {
                        outFile->write(temp, DataSizes::paramId);
                        temp += DataSizes::paramId * 8;

                        outFile->write(temp, DataSizes::floatData);
                        temp += DataSizes::floatData * 8;
                    }
                    return;
                }
                case panic:{
                    outFile->write(temp, DataSizes::channelNumber); //Write channel number
                    return;
                }
            }
        }
    };

    struct MuDaFileFormat {
        MuDaHeader header;
        std::vector<MuDaMessage> data;

        MuDaFileFormat(int32_t _deltaPerSecond){
            strncpy(header.signature, "MuDa", 4);
            header.version = 1;
            header.deltaPerSecond = _deltaPerSecond;
        }

        void add(MuDaMessage message){
            data.push_back(message);
        }

        bool writeToFile(std::string file){
            std::ofstream wf(file, std::ios::out | std::ios::binary);
            if(!wf) {
                std::cout << "Cannot open file!" << std::endl;
                return false;
            }
            //Write the header to file
            wf.write((char *) &header, sizeof(MuDaHeader));

            for(auto message : data){
                message.write(&wf);
            }

            wf.close();
            if(!wf.good()) {
                std::cout << "Error occurred at writing time!" << std::endl;
                return false;
            }

            return true;
        }
    };

}
#endif //MUSICTOOLKIT_MUDAFILEFORMAT_H
