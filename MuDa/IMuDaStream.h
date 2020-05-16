/**
 * \class IMuDa
 * \brief An interfaces that defines the behavior of a generic MuDa stream
 * \author Sam
 */

#ifndef MUSICTOOLKIT_IMUDASTREAM_H
#define MUSICTOOLKIT_IMUDASTREAM_H

#include <streambuf>
namespace MTK::MuDa {
    class IMuDaStream : public std::streambuf {

    };
}
#endif //MUSICTOOLKIT_IMUDASTREAM_H