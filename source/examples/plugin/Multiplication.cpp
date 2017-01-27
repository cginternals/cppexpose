
#include "Multiplication.h"


CPPEXPOSE_COMPONENT(Multiplication, BinaryOperator)


Multiplication::Multiplication(int a, int b)
: BinaryOperator(a, b)
{
}

Multiplication::~Multiplication()
{
}

int Multiplication::compute()
{
    return m_a * m_b;
}
