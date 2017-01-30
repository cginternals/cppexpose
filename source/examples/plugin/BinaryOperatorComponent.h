
#pragma once


#include <cppexpose/plugin/AbstractComponent.h>


class BinaryOperator;


/**
*  @brief
*    Component base class for BinaryOperator
*/
class AbstractBinaryOperatorComponent : public cppexpose::AbstractComponent
{
public:
    AbstractBinaryOperatorComponent()
    {
    }

    virtual ~AbstractBinaryOperatorComponent()
    {
    }

    virtual BinaryOperator * createInstance(int a, int b) = 0;
    virtual BinaryOperator * createInstance(int a) = 0;
};

/**
*  @brief
*    Component class for BinaryOperator
*/
template <class CLASS>
class BinaryOperatorComponent : public AbstractBinaryOperatorComponent
{
public:
    BinaryOperatorComponent()
    {
    }

    virtual ~BinaryOperatorComponent()
    {
    }

    virtual BinaryOperator * createInstance(int a, int b) override
    {
        return new CLASS(a, b);
    }

    virtual BinaryOperator * createInstance(int a)
    {
        return new CLASS(a, a);
    }
};
