
#pragma once


#include <cppexpose/cppexpose-version.h>
#include <cppexpose-plugin/plugin_api.h>

#include "BinaryOperator.h"


/**
*  @brief
*    Addition operator
*/
class Addition : public BinaryOperator
{
public:
    CPPEXPOSE_DECLARE_COMPONENT(
        Addition, BinaryOperator,
        "", // Tags
        "", // Icon
        "", // Annotations
        "Addition operator",
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
    Addition(int a, int b);

    /**
    *  @brief
    *    Destructor
    */
    virtual ~Addition();

    // Virtual BinaryOperator interface
    virtual int compute() override;
};
