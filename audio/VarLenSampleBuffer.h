//
// Created by sammy on 06/06/2020.
//

#ifndef MUSICTOOLKIT_VARLENSAMPLEBUFFER_H
#define MUSICTOOLKIT_VARLENSAMPLEBUFFER_H

#include <AudioSampleBuffer.h>
#include <exception>

namespace MTK::Audio {
    template<typename T, typename Container = std::deque<T>>
    class VarLenSampleBuffer {
    public:

        VarLenSampleBuffer(int _length, int _maxLength) : length(_length),
                                                          maxLength(_maxLength) {
            fillBuff(&c, length, 0);
            fillBuff(&overflowBuff, maxLength-length, 0);
        }

        void setLength(int _length){
            if(length >= maxLength){
                throw std::runtime_error("new requested length is greater than maxLength");
            }
            if(_length==length){return;}
            bool grow = _length>length;
            length = _length;
            if(grow) {
                while (c.size() < length) {
                    c.push_front(overflowBuff.back());
                    overflowBuff.pop_back();
                }
            }else{
                while (c.size()>length){
                    pop();
                }
            }
        }

        void push(const T& value) {
            if (c.size() == length)
            {
                pop();
            }
            c.push_back(value);
        }

        void pop() {
            overflowBuff.push_back(c.front());
            if(overflowBuff.size() > (maxLength-length)){
                overflowBuff.pop_front();
            }
            c.pop_front();
        }

        T front(){
            return c.front();
        }

        bool empty() {
            return c.empty();
        }
        size_t size(){
            return c.size();
        }
    protected:
        Container overflowBuff;
        Container c;

        void fillBuff(Container *_c, int size, const T& value){
            while(_c->size()<size){
                _c->push_back(value);
            }
        }

        int length;
        const int maxLength;
    };
}
#endif //MUSICTOOLKIT_VARLENSAMPLEBUFFER_H
