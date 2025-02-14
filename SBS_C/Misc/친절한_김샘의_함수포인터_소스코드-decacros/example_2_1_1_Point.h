struct POINT
{
    int x, y;

    void (* Input)(struct POINT*);
    void (* Output)(const struct POINT*);
};

void InitPoint( struct POINT* ppt );
