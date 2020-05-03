//
// Created by samt on 21/04/2020.
//


#include <gtest/gtest.h>
#include <MuDaFileFormat.h>

#include <memory>

#define ASSERT_SAME(a, b, value) ASSERT_EQ(a.value,b.value)

using namespace MuDa;

TEST(MuDaFileTest, writeFile){
    auto Mf = std::make_shared<MuDaFileFormat>(512);
    std::map<uint32_t, float> params = {{0, 440.f}};


    Mf->appendStartMessage();
    Mf->appendNoteMessage(0, MessageCodes::noteOn, {0, 0, params});
    Mf->appendNoteMessage(600, MessageCodes::noteChange, {0, 0, {{0, 441.f}}});
    Mf->appendSystemParamMessage(700, {{3, 440.f}});
    //Mf->appendPanicMessage(750.5f, 1);
    Mf->appendNoteMessage(1024, MessageCodes::noteOff, {0, 0, {{0, 441.f}}});
    Mf->appendEndMessage(1536);

    Mf->writeToFile("testOutput.MuDa");
    auto fileSuccess = MuDaFileFormat::readFromFile("testOutput.MuDa");
    if(fileSuccess) {
        auto Mf2 = *fileSuccess;

#define ASSERT_SAME_MF(value) ASSERT_SAME(Mf, Mf2, value)

        ASSERT_SAME_MF(get()->header.version);
        ASSERT_SAME_MF(get()->header.deltaPerSecond);
        ASSERT_SAME_MF(get()->messages.size());
        for(int i = 0; i < Mf->messages.size(); i++){
            ASSERT_SAME_MF(get()->messages.at(i)->delta);
            ASSERT_SAME_MF(get()->messages.at(i)->messageType);
            //Check data is exactly the same
            if(Mf->messages.at(i)->messageType == MessageCodes::noteOn || Mf->messages.at(i)->messageType == MessageCodes::noteChange || Mf->messages.at(i)->messageType == MessageCodes::noteOff){
                MuDaNoteMessageData MfN;
                MuDaNoteMessageData MfN2;
                MfN = *(Mf->messages.at(i)->getNoteEventData());
                MfN2 = *(Mf2->messages.at(i)->getNoteEventData());
                ASSERT_SAME(MfN, MfN2, channelId);
                ASSERT_SAME(MfN, MfN2, voiceId);
                ASSERT_SAME(MfN, MfN2, parameters.size());
            }else if(Mf->messages.at(i)->messageType == MessageCodes::systemParamChange){
                std::optional<PARAMS> MfP;
                std::optional<PARAMS> MfP2;
                if(!(MfP = Mf->messages.at(i)->getSystemParamData())){ FAIL(); }
                if(!(MfP2 = Mf2->messages.at(i)->getSystemParamData())){FAIL(); }
                ASSERT_SAME((*MfP), (*MfP2), size());

            }else if(Mf->messages.at(i)->messageType == MessageCodes::panic){
                uint32_t MfP;
                uint32_t MfP2;
                MfP = *(Mf->messages.at(i)->getPanicData());
                MfP2 = *(Mf2->messages.at(i)->getPanicData());
                ASSERT_EQ(MfP, MfP2);
            }
        }

        SUCCEED();
    } else {
        std::cout << "Error in passing file" << std::endl;
        FAIL();
    }
}

TEST(MuDaFileTest, MuDaMessagePointerTest){
    auto Mf = MuDaFileFormat(512);

    Mf.appendStartMessage();

    ASSERT_TRUE(Mf.messages[0]->messageType == MessageCodes::start);
}

TEST(MuDaFileTest, testGetNoteEvent){
    MuDaFileFormat mf = MuDaFileFormat();
    MuDaNoteMessageData mData = {0, 0, {{0, 1}}};
    mf.appendNoteMessage(0, MessageCodes::noteOn, {0, 0, {{0, 1}}});

    MuDaNoteMessageData mData2 = *mf.messages[0]->getNoteEventData();

    ASSERT_EQ(mData.channelId, mData2.channelId);
    ASSERT_EQ(mData.voiceId, mData2.voiceId);
    ASSERT_EQ(mData.parameters.size(), mData2.parameters.size());
    for(int i = 0; i< mData.parameters.size(); i++){
        ASSERT_SAME(mData, mData2, parameters[i]);
    }
}

TEST(MuDaFileTest, readnonExistingFile){
    auto mf = MuDaFileFormat::readFromFile("BlahBlah.nonexistant.MuDa");
    EXPECT_FALSE(mf);
}


TEST(MuDaFileTest, badNoteMessage){
    try{
        MuDaFileFormat mf = MuDaFileFormat();
        mf.appendNoteMessage(0, MessageCodes::start, {0, 0, {}});
        FAIL();
    }catch(std::runtime_error &e){
        std::string ec = "Invalid messageCode";
        ASSERT_EQ(ec.compare(e.what()), 0);
    }catch(std::exception &e) {
        FAIL();
    }
}