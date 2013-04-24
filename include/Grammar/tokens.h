enum DataTypes{INT,STRING,BOOL};
typedef union{
    double number;
    const char* string;
    bool boolean;
} Data;
struct Token {
    int type;
    int stringLength;
    Data data;
    unsigned n;
};
