#include "example_2_1_1_Point.h"

struct RECT
{
    struct POINT pt1, pt2;

    void (* Input)(struct RECT*);
    void (* Output)(const struct RECT*);
};

void InitRect( struct RECT* pRect );
