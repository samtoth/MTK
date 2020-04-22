//
// Created by samt on 21/04/2020.
//


#include <gtest/gtest.h>
#include <MuDaFileFormat.h>

#define ASSERT_SAME(a, b, value) ASSERT_EQ(a.value,b.value);

using namespace MuDa;
TEST(MuDaFileTestm, writeFile){
    MuDaFileFormat Mf(512);
    std::vector<std::pair<uint32_t, float>> params = {{0, 440.f}};

    Mf.add(MuDaMessage::StartMessage());
    Mf.add(MuDaMessage::NoteMessage(MessageCodes::noteOn, 512, 0, params));
    Mf.add(MuDaMessage::NoteMessage(MessageCodes::noteOff, 1024, 0, params));
    Mf.add(MuDaMessage::EndMessage(1536));

    Mf.writeToFile("testOutput.MuDa");
    auto fileSuccess = MuDaFileFormat::readFromFile("testOutput.MuDa");
    if(fileSuccess) {
        MuDaFileFormat Mf2 = *fileSuccess;

#define ASSERT_SAME_MF(value) ASSERT_SAME(Mf, Mf2, value)

        ASSERT_SAME_MF(header.version)
        ASSERT_SAME_MF(header.deltaPerSecond)
        ASSERT_SAME_MF(data.size())
        for(int i = 0; i < Mf.data.size(); i++){
            ASSERT_SAME_MF(data.at(i).delta);
            ASSERT_SAME_MF(data.at(i).messageType)
            //Check data is exactly the same
        }

        SUCCEED();
    } else {
        std::cout << "Error in passing file" << std::endl;
        FAIL();
    }
}
