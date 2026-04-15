#ifndef ICONVERTER_H
#define ICONVERTER_H
#pragma once
#endif // ICONVERTER_H

template <typename Out, typename In>
class IConverter{
public:
    virtual Out convert(const In& input) = 0;
};
