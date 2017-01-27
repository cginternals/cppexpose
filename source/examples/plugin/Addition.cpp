
#include "Addition.h"


CPPEXPOSE_COMPONENT(Addition, BinaryOperator)


Addition::Addition(int a, int b)
: BinaryOperator(a, b)
{
}

Addition::~Addition()
{
}

int Addition::compute()
{
    return m_a + m_b;
}
