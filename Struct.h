#define blankChar ' '
#define filledChar '*'
#define rowSize 30
#define columnSize 30

typedef struct drawing {
    char rowData[columnSize];
    struct drawing * next;
} drawing;

drawing *head;