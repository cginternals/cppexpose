
#pragma once


#include <memory>

#include <cppassist/memory/make_unique.h>

#include <cppexpose-plugin/AbstractComponent.h>


class BinaryOperator;


/**
*  @brief
*    Component base class for BinaryOperator
*/
class AbstractBinaryOperatorComponent : public cppexpose_plugin::AbstractComponent
{
public:
    AbstractBinaryOperatorComponent()
    {
    }

    virtual ~AbstractBinaryOperatorComponent()
    {
    }

    virtual std::unique_ptr<BinaryOperator> createInstance(int a, int b) = 0;
    virtual std::unique_ptr<BinaryOperator> createInstance(int a) = 0;
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

    virtual std::unique_ptr<BinaryOperator> createInstance(int a, int b) override
    {
        return cppassist::make_unique<CLASS>(a, b);
    }

    virtual std::unique_ptr<BinaryOperator> createInstance(int a) override
    {
        return cppassist::make_unique<CLASS>(a, a);
    }
};
