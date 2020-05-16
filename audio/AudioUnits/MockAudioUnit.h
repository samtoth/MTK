//
// Created by samt on 16/05/2020.
//

#ifndef MUSICTOOLKIT_MOCKAUDIOUNIT_H
#define MUSICTOOLKIT_MOCKAUDIOUNIT_H
#include <IAudioUnit.h>
namespace MTK::Audio {
	class MockAudioUnit : public IAudioUnit{
		float output() override;
	};
}
#endif //MUSICTOOLKIT_MOCKAUDIOUNIT_H