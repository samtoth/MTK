/**
 * \class MuDaFileFormat
 * \brief MuDaFileFormat holds information about the contents of a MuDa file or stream
 */

#ifndef MUSICTOOLKIT_MUDAFILEFORMAT_H
#define MUSICTOOLKIT_MUDAFILEFORMAT_H

#include <fstream>
#include <iostream>
#include <cstring>
#include <cassert>
#include <optional>


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
        messageCount = sizeof(uint64_t),
        messageType = sizeof(uint16_t),
        deltaVal = sizeof(uint64_t),
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
        uint64_t delta;
        uint16_t messageType;
        char* data;


        //TODO: Add static functions to generate specific MuDa messages with correct data eg:
        //      static MuDaMessage NoteOnMessage(int channelID, vector<pair<int paramID, float value>> parameters)

        static MuDaMessage StartMessage(){MuDaMessage m; m.messageType = MessageCodes::start; m.delta = 0; m.data = 0; return m;}
        static MuDaMessage EndMessage(uint32_t _delta){MuDaMessage m; m.messageType = MessageCodes::end; m.delta = _delta; m.data = 0; return m;}

        static MuDaMessage NoteMessage(uint16_t _messageType, uint32_t _delta, uint32_t _channelNumber, std::vector<std::pair<uint32_t /*paramId*/, float>> parameters){
            assert(_messageType == MessageCodes::noteOn || _messageType == MessageCodes::noteChange || _messageType == MessageCodes::noteOff);
            MuDaMessage m;
            m.messageType = _messageType;
            m.delta = _delta;
            uint32_t nParams = parameters.size();
            m.data = (char *)malloc(DataSizes::channelNumber + DataSizes::paramCount + nParams*(DataSizes::paramId+ DataSizes::floatData));
            char * temp = m.data;
            memcpy(temp, (char *)(&_channelNumber), DataSizes::channelNumber);
            temp += DataSizes::channelNumber;
            memcpy(temp, (char *)(&nParams), DataSizes::paramCount);
            temp += DataSizes::paramCount;
            for(int i = 0; i < nParams; i++){
                memcpy(temp, (char *)(&(parameters[i].first)), DataSizes::paramId);
                temp += DataSizes::paramId;
                memcpy(temp, (char *)(&(parameters[i].second)), DataSizes::floatData);
                temp += DataSizes::floatData;
            }
            return m;
        }

        void write(std::ofstream *outFile){
            outFile->write((char *) &(delta), DataSizes::deltaVal);
            outFile->write((char *) &(messageType), DataSizes::messageType);
            char *temp = data;
            switch(messageType){
                case start:
                case end:
                    break;
                case noteOn:
                case noteChange:
                case noteOff: {
                    outFile->write(temp, DataSizes::channelNumber); //Write channel number
                    temp += DataSizes::channelNumber; //Increment the pointer by the size of (ChannelNumber) in bytes
                    int32_t nParams = 0;
                    memcpy((char *) (&nParams), temp, DataSizes::paramCount); //Copy the number of parameters to memory
                    outFile->write(temp, DataSizes::paramCount); //Write the number of parameters to file
                    temp += DataSizes::paramCount;  //Increment the pointer by the size of (paramCount) in bytes
                    for (int i = 0; i < nParams; i++) {
                        outFile->write(temp, DataSizes::paramId);
                        temp += DataSizes::paramId;

                        outFile->write(temp, DataSizes::floatData);
                        temp += DataSizes::floatData;
                    }
                    return;
                }
                case systemParamChange: {
                    int16_t nParams = 0;
                    memcpy((char *) (&nParams), temp, DataSizes::paramCount); //Copy the number of parameters to memory
                    outFile->write(temp, DataSizes::paramCount); //Write the number of parameters to file
                    temp += DataSizes::paramCount;  //Increment the pointer by the size of (paramCount) in bytes
                    for (int i = 0; i < nParams; i++) {
                        outFile->write(temp, DataSizes::paramId);
                        temp += DataSizes::paramId;

                        outFile->write(temp, DataSizes::floatData);
                        temp += DataSizes::floatData;
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

        MuDaFileFormat(){}

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
            uint64_t nMessage = data.size();
            wf.write((char *)&(nMessage), DataSizes::messageCount);

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

        static std::optional<MuDaFileFormat> readFromFile(std::string file){
            MuDaFileFormat ret;

            std::ifstream rf(file, std::ios::in | std::ios::binary);
            if(!rf) {
                std::cout << "Cannot open file!" << std::endl;
                return std::nullopt;
            }

            rf.read((char *)(&ret.header), sizeof(MuDaHeader));
            if(ret.header.signature[0] != 'M' || ret.header.signature[1] != 'u' || ret.header.signature[2] != 'D' || ret.header.signature[3] != 'a'){
                return std::nullopt;
            }

            uint64_t nMessages = 0;
            rf.read((char *)(&nMessages), DataSizes::messageCount);
            for(int i =0; i < nMessages; i++){
                //for each message:
                MuDaMessage message;
                rf.read((char *)&(message.delta), DataSizes::deltaVal);
                rf.read((char *)&(message.messageType), DataSizes::messageType);

                switch(message.messageType){
                    case start:
                    case end:
                        message.data = 0;
                        break;
                    case noteOn:
                    case noteChange:
                    case noteOff: {
                        // allocate enough data to at least store channel number and param count
                        message.data = (char*)malloc(DataSizes::channelNumber + DataSizes::paramCount);

                        char * temp = message.data;
                        rf.read(temp, DataSizes::channelNumber); //Read channel number
                        temp += DataSizes::channelNumber; //Increment the pointer by the size of (ChannelNumber) in bytes
                        rf.read(temp, DataSizes::paramCount); //Read the param count to data
                        int32_t nParams = 0;
                        memcpy((char *) (&nParams), temp, DataSizes::paramCount); //Copy the number of parameters to memory
                        temp += DataSizes::paramCount;  //Increment the pointer by the size of (paramCount) in bytes
                        message.data = (char *)realloc(message.data,DataSizes::channelNumber + DataSizes::paramCount
                            + nParams*(DataSizes::paramId + DataSizes::floatData)); //Reallocate enough memory for the message now we know how many parameters are included
                        temp = message.data + DataSizes::channelNumber + DataSizes::paramCount;
                        for (int k = 0; k < nParams; k++) {
                            rf.read(temp, DataSizes::paramId);
                            temp += DataSizes::paramId;
                            rf.read(temp, DataSizes::floatData);
                            temp += DataSizes::floatData;
                        }
                        break;
                    }
                    case systemParamChange: {
                        // allocate enough data to at least store param count
                        message.data = (char*)malloc(DataSizes::paramCount);

                        char * temp = message.data;
                        rf.read(temp, DataSizes::paramCount); //Read the param count to data
                        int16_t nParams = 0;
                        memcpy((char *) (&nParams), temp, DataSizes::paramCount); //Copy the number of parameters to memory

                        message.data = (char *)realloc(message.data,DataSizes::paramCount + nParams*(DataSizes::paramId + DataSizes::floatData)); //Reallocate enough memory for the message now we know how many parameters are included
                        temp = message.data + DataSizes::paramCount;
                        for (int k = 0; k < nParams; k++) {
                            rf.read(temp, DataSizes::paramId);
                            temp += DataSizes::paramId;
                            rf.read(temp, DataSizes::floatData);
                            temp += DataSizes::floatData;
                        }
                        break;
                    }
                    case panic:{
                        message.data = (char*)malloc(DataSizes::channelNumber);

                        rf.read(message.data, DataSizes::channelNumber); //Read channel number
                        break;
                    }
                }

                ret.add(message);
            }

            rf.close();
            if(!rf.good()) {
                std::cout << "Error occurred at reading time!" << std::endl;
                return std::nullopt;
            }
            return ret;
        }
    };

}
#endif //MUSICTOOLKIT_MUDAFILEFORMAT_H
