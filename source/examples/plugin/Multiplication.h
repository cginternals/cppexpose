
#pragma once


#include <cppexpose/cppexpose-version.h>
#include <cppexpose-plugin/plugin_api.h>

#include "BinaryOperator.h"


/**
*  @brief
*    Multiplication operator
*/
class Multiplication : public BinaryOperator
{
public:
    CPPEXPOSE_DECLARE_COMPONENT(
        Multiplication, BinaryOperator,
        "", // Tags
        "", // Icon
        "", // Annotations
        "Multiplication operator",
        CPPEXPOSE_AUTHOR_ORGANIZATION,
        "v1.0.0"
    )


public:
    /**
    *  @brief
    *    Constructor
    *
    *  @param[in] a
    *    First operand
    *  @param[in] b
    *    Second operand
    */
    Multiplication(int a, int b);

    /**
    *  @brief
    *    Destructor
    */
    virtual ~Multiplication();

    // Virtual BinaryOperator interface
    virtual int compute() override;
};
