#pragma once


template <typename Out, typename In>
class IConverter{
public:
    virtual Out convert(const In& input) = 0;
};



