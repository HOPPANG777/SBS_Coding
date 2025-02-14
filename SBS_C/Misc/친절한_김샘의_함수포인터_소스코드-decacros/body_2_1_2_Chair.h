typedef struct _CHAIR
{
    char model[32];
    int  price;
    char size;      // Small, Medium, Big

    void (* Input)(struct _CHAIR*);
    void (* Output)(const struct _CHAIR*);
}
CHAIR;

void InitChair( CHAIR* pChair );
