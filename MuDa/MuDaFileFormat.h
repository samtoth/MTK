#ifndef MUSICTOOLKIT_MUDAFILEFORMAT_H
#define MUSICTOOLKIT_MUDAFILEFORMAT_H

#include <fstream>
#include <iostream>
#include <cstring>
#include <cassert>
#include <memory>
#include <optional>
#include <utility>
#include <memory>


namespace MTK::MuDa {
    #define PARAMS std::map<uint32_t, float>

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
        voiceNumber = sizeof(uint32_t),
        paramId = sizeof(uint32_t),
        floatData = sizeof(float)
    };

    struct MuDaHeader {
        char signature[4];
        uint16_t version;
        uint32_t deltaPerSecond;
    };

    struct MuDaNoteMessageData{
        uint32_t channelId;
        uint32_t voiceId;
        PARAMS parameters;
    };


    struct MuDaMessage {
        uint64_t delta;
        uint16_t messageType;
        char* data;

        MuDaMessage(){
            delta = 0;
            messageType = 0;
            data = nullptr;
        }

        MuDaMessage(uint64_t _delta, uint16_t _messageType){
            delta = _delta;
            messageType = _messageType;
            data = nullptr;
        }

        ~MuDaMessage(){
            if(data!=nullptr){
                free(data);
                data = nullptr;
            }
        }

        static char *CreateNoteMessageData(MuDaNoteMessageData _data) {
            char * ret;
            uint32_t nParams = _data.parameters.size();
            ret = (char *)malloc(DataSizes::channelNumber+  DataSizes::voiceNumber + DataSizes::paramCount + nParams*(DataSizes::paramId+ DataSizes::floatData));
            char * temp = ret;
            memcpy(temp, (char *)(&_data.channelId), DataSizes::channelNumber);
            temp += DataSizes::channelNumber;
            memcpy(temp, (char *)(&_data.voiceId), DataSizes::voiceNumber);
            temp += DataSizes::voiceNumber;
            memcpy(temp, (char *)(&nParams), DataSizes::paramCount);
            temp += DataSizes::paramCount;
            for(int i = 0; i < nParams; i++){
                memcpy(temp, (char *)(&(i)), DataSizes::paramId);
                temp += DataSizes::paramId;
                memcpy(temp, (char *)(&(_data.parameters[i])), DataSizes::floatData);
                temp += DataSizes::floatData;
            }
            return ret;
        }
        static char *CreateSystemParamMessageData(PARAMS parameters){
            uint32_t nParams = parameters.size();
            char *ret = (char *)malloc(DataSizes::paramCount + nParams*(DataSizes::paramId+ DataSizes::floatData));
            char *temp = ret;
            memcpy(temp, (char *)(&nParams), DataSizes::paramCount);
            temp += DataSizes::paramCount;
            for(int i = 0; i < nParams; i++){
                memcpy(temp, (char *)(&(i)), DataSizes::paramId);
                temp += DataSizes::paramId;
                memcpy(temp, (char *)(&(parameters[i])), DataSizes::floatData);
                temp += DataSizes::floatData;
            }
            return ret;
        }
        static char *CreatePanicMessageData(uint32_t channelNumber){
            char *ret = (char *)malloc(DataSizes::channelNumber);
            memcpy(ret, (char *)(&channelNumber), DataSizes::channelNumber);
            return ret;
        }

        std::optional<MuDaNoteMessageData> getNoteEventData() const{
            if(!(messageType == MessageCodes::noteOn || messageType == MessageCodes::noteChange || messageType == MessageCodes::noteOff)){
                std::cout << "Requested note event data from a non note MuDa event... aborting..."  << std::endl;
                return std::nullopt;
            }

            MuDaNoteMessageData ret;
            char * temp = data;
            memcpy((char *)&(ret.channelId), temp, DataSizes::channelNumber); //Read channel number
            temp += DataSizes::channelNumber; //Increment the pointer by the size of (ChannelNumber) in bytes
            memcpy((char *)&(ret.voiceId), temp,  DataSizes::voiceNumber); //Read voice number
            temp += DataSizes::voiceNumber; //Increment the pointer by the size of (voiceNumber) in bytes
            int32_t nParams = 0;
            memcpy((char *) (&nParams), temp, DataSizes::paramCount); //Copy the number of parameters to memory
            temp += DataSizes::paramCount;  //Increment the pointer by the size of (paramCount) in bytes
            uint32_t tParamId = 0; float tData = 0;
            for (int k = 0; k < nParams; k++) {
                memcpy((char *)&tParamId, temp, DataSizes::paramId);
                temp += DataSizes::paramId;
                memcpy((char *)&tData, temp, DataSizes::floatData);
                temp += DataSizes::floatData;
                ret.parameters.insert(std::make_pair(tParamId, tData));
            }
            return ret;
        }
        std::optional<PARAMS> getSystemParamData() const{
            if(messageType != MessageCodes::systemParamChange){
                std::cout << "Requested systemParam event data from a non systemParam MuDa event... aborting..."  << std::endl;
                return std::nullopt;
            }

            PARAMS ret;
            char * temp = data;
            int32_t nParams = 0;
            memcpy((char *) (&nParams), temp, DataSizes::paramCount); //Copy the number of parameters to memory
            temp += DataSizes::paramCount;  //Increment the pointer by the size of (paramCount) in bytes
            uint32_t tParamId = 0; float tData = 0;
            for (int k = 0; k < nParams; k++) {
                memcpy((char *)&tParamId, temp, DataSizes::paramId);
                temp += DataSizes::paramId;
                memcpy((char *)&tData, temp, DataSizes::floatData);
                temp += DataSizes::floatData;
                ret.insert(std::make_pair(tParamId, tData));
            }
            return ret;
        }
        std::optional<uint32_t> getPanicData() const{
            if(messageType != MessageCodes::panic){
                std::cout << "Requested panic event data from a non panic MuDa event... aborting..."  << std::endl;
                return std::nullopt;
            }
            uint32_t ret;
            char * temp = data;
            memcpy((char *)&(ret), temp, DataSizes::channelNumber); //Read channel number
            return ret;
        }

        void writeF(std::ofstream *outFile){
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
                    outFile->write(temp, DataSizes::voiceNumber); //Write voiceId
                    temp += DataSizes::voiceNumber; //Increment the pointer by the size of (voiceNumber) in bytes
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
                case panic:{
                    outFile->write(temp, DataSizes::channelNumber); //Write channel number
                    return;
                }
            }
        }
    };


    struct MuDaFileFormat {
        MuDaHeader header;
        std::vector<std::unique_ptr<MuDaMessage>> messages;

        MuDaFileFormat(){}

        MuDaFileFormat(int32_t _deltaPerSecond){
            strncpy(header.signature, "MuDa", 4);
            header.version = 1;
            header.deltaPerSecond = _deltaPerSecond;
        }


        void appendStartMessage(){
            std::unique_ptr<MuDaMessage> ret(new MuDaMessage(0, MessageCodes::start));
            messages.push_back(std::move(ret));
        }
        void appendEndMessage(uint64_t _delta){
            std::unique_ptr<MuDaMessage> ret(new MuDaMessage(_delta, MessageCodes::end));
            messages.push_back(std::move(ret));
        }
        void appendNoteMessage(uint64_t _delta, uint16_t _messageType, MuDaNoteMessageData _data){
            if(!(_messageType == MessageCodes::noteOn || _messageType == MessageCodes::noteChange || _messageType == MessageCodes::noteOff)){
                throw std::runtime_error("Invalid messageCode");
            }
            std::unique_ptr<MuDaMessage> ret(new MuDaMessage(_delta, _messageType));
            ret->data = MuDaMessage::CreateNoteMessageData(std::move(_data));
            messages.push_back(std::move(ret));
        }
        void appendSystemParamMessage(uint64_t _delta, PARAMS _params){
            std::unique_ptr<MuDaMessage> ret(new MuDaMessage(_delta, MessageCodes::systemParamChange));
            ret->data = MuDaMessage::CreateSystemParamMessageData(std::move(_params));
            messages.push_back(std::move(ret));
        }
        void appendPanicMessage(uint64_t _delta, uint32_t channelId){
            std::unique_ptr<MuDaMessage> ret(new MuDaMessage(_delta, MessageCodes::panic));
            ret->data = MuDaMessage::CreatePanicMessageData(channelId);
            messages.push_back(std::move(ret));
        }

        bool writeToFile(std::string file){
            std::ofstream wf(file, std::ios::out | std::ios::binary);
            if(!wf) {
                std::cout << "Cannot open file!" << std::endl;
                return false;
            }
            //Write the header to file
            wf.write((char *) &header, sizeof(MuDaHeader));
            uint64_t nMessage = messages.size();
            wf.write((char *)&(nMessage), DataSizes::messageCount);

            for(auto const& message: messages){
                message->writeF(&wf);
            }

            wf.close();
            if(!wf.good()) {
                std::cout << "Error occurred at writing time!" << std::endl;
                return false;
            }

            return true;
        }

        static std::optional<std::shared_ptr<MuDaFileFormat>> readFromFile(const std::string& file){
            auto ret = std::make_shared<MuDaFileFormat>();

            std::ifstream rf(file, std::ios::in | std::ios::binary);
            if(!rf) {
                std::cout << "Cannot open file!" << std::endl;
                return std::nullopt;
            }

            rf.read((char *)&(ret->header), sizeof(MuDaHeader));
            if(ret->header.signature[0] != 'M' || ret->header.signature[1] != 'u' || ret->header.signature[2] != 'D' || ret->header.signature[3] != 'a'){
                std::cout << "MuDa signature not found" << std::endl;
                return std::nullopt;
            }

            uint64_t nMessages = 0;
            rf.read((char *)(&nMessages), DataSizes::messageCount);
            for(int i =0; i < nMessages; i++){
                //for each message:
                auto *message = new MuDaMessage();
                rf.read((char *)&(message->delta), DataSizes::deltaVal);
                rf.read((char *)&(message->messageType), DataSizes::messageType);

                switch(message->messageType){
                    case start:
                    case end:
                        message->data = nullptr;
                        break;
                    case noteOn:
                    case noteChange:
                    case noteOff: {
                        // allocate enough data to at least store channel number, voiceNumber and param count
                        message->data = (char*)malloc(DataSizes::channelNumber + DataSizes::voiceNumber + DataSizes::paramCount);

                        char * temp = message->data;
                        rf.read(temp, DataSizes::channelNumber); //Read channel number
                        temp += DataSizes::channelNumber; //Increment the pointer by the size of (ChannelNumber) in bytes
                        rf.read(temp, DataSizes::voiceNumber); //Read voice number
                        temp += DataSizes::voiceNumber; //Increment the pointer by the size of (voiceNumber) in bytes
                        rf.read(temp, DataSizes::paramCount); //Read the param count to data
                        int32_t nParams = 0;
                        memcpy((char *) (&nParams), temp, DataSizes::paramCount); //Copy the number of parameters to memory
                        message->data = (char *)realloc(message->data,DataSizes::channelNumber + DataSizes::voiceNumber + DataSizes::paramCount
                            + nParams*(DataSizes::paramId + DataSizes::floatData)); //Reallocate enough memory for the message now we know how many parameters are included
                        temp = message->data + DataSizes::channelNumber  + DataSizes::voiceNumber + DataSizes::paramCount;
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
                        message->data = (char*)malloc(DataSizes::paramCount);

                        char * temp = message->data;
                        rf.read(temp, DataSizes::paramCount); //Read the param count to data
                        int32_t nParams = 0;
                        memcpy((char *) (&nParams), temp, DataSizes::paramCount); //Copy the number of parameters to memory

                        message->data = (char *)realloc(message->data,DataSizes::paramCount + nParams*(DataSizes::paramId + DataSizes::floatData)); //Reallocate enough memory for the message now we know how many parameters are included
                        temp = message->data + DataSizes::paramCount;
                        for (int k = 0; k < nParams; k++) {
                            rf.read(temp, DataSizes::paramId);
                            temp += DataSizes::paramId;
                            rf.read(temp, DataSizes::floatData);
                            temp += DataSizes::floatData;
                        }
                        break;
                    }
                    case panic:{
                        message->data = (char*)malloc(DataSizes::channelNumber);

                        rf.read(message->data, DataSizes::channelNumber); //Read channel number
                        break;
                    }
                }

                ret->messages.push_back(std::unique_ptr<MuDaMessage>(message));
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
