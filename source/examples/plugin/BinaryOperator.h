
#pragma once


#include "BinaryOperatorComponent.h"


/**
*  @brief
*    Base class for binary operators
*/
class BinaryOperator
{
public:
    // Component types for the plugin system
    using AbstractComponentType = AbstractBinaryOperatorComponent;

    template <typename Type>
    using ComponentType = BinaryOperatorComponent<Type>;


public:
    BinaryOperator(int a, int b);
    virtual ~BinaryOperator();

    virtual int compute() = 0;


protected:
    int m_a;
    int m_b;
};
