//
// Created by samt on 15/04/2020.
//

#include "LinearTuning.h"
namespace MTKCore {
    LinearTuning::LinearTuning(float _period, float _generator, float _fundamentalFrequency) {
        fundamentalFrequency = _fundamentalFrequency;
        generator = _generator;
        period = _period;
    }

    std::string LinearTuning::getNoteName(Vector coordinate) {
        return std::string();
    }


    template<class T>
    typename std::enable_if<!std::numeric_limits<T>::is_integer, bool>::type
    LinearTuning::almost_equal(T x, T y, int ulp)
    {
        // the machine epsilon has to be scaled to the magnitude of the values used
        // and multiplied by the desired precision in ULPs (units in the last place)
        return std::fabs(x-y) <= std::numeric_limits<T>::epsilon() * ulp
               // unless the result is subnormal
               || std::fabs(x-y) < std::numeric_limits<T>::min();
    }


    std::optional<Vector> LinearTuning::getCoordinate(float frequency) {
        int a, b;
        float n = logf(frequency/fundamentalFrequency);
        float x = logf(period);
        float y = logf(generator);

        // frequency/fundamentalFrequency = g^a * p^b
        // log(frequency/fundamentalFrequency) = n = log(g^a * p^b) = log(g^a) + log(p^b)
        // solve{n = ax + by} for a,b; over the integers
        // a = (n - by)/(x)

        //TODO: More efficient algorithm?

        if(n == 0){
            return Vector(0,0);
        }

        for(a=0; a<50; a++){
            float _b = (n-a*x)/y;
            if(LinearTuning::almost_equal<float>(_b-floor(_b), 0, 50)){
                b = floor(_b);
                return Vector(a, b);
            }

            if(LinearTuning::almost_equal<float>(_b-floor(_b), 1, 50)){
                b = ceil(_b);
                return Vector(a, b);
            }

            _b = (n+a*x)/y;
            if(LinearTuning::almost_equal<float>(_b-floor(_b), 0, 50)){
                b = floor(_b);
                return Vector(a, b);
            }

            if(LinearTuning::almost_equal<float>(_b-floor(_b), 1, 50)){
                b = ceil(_b);
                return Vector(a, b);
            }
        }
        return std::nullopt;
    }

    float LinearTuning::getFrequency(Vector coordinate) {
        return getFundamentalFrequency() * std::pow(period, coordinate[0]) * std::pow(generator, coordinate[1]);
    }

    std::unique_ptr<IScale> LinearTuning::generateScale(int notesPerPeriod) {
        //TODO: Implement this function
        return nullptr;
    }
}