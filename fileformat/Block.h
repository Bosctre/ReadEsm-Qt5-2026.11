#pragma once
#ifndef FILEFORMAT_BLOCK_H
#define FILEFORMAT_BLOCK_H

#include <QString>


class Reporter;

class Block {
public:
    virtual ~Block() = default;

    virtual QString title() const = 0;
    virtual void printOn(Reporter& report) const = 0;
};


#endif // FILEFORMAT_BLOCK_H
