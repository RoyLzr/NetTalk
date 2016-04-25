#ifdef   __DATA_PARSE_H_
#define  __DATA_PARSE_H_

class DataParser
{
    public:
        DataParser();
        virtual ~DataParser();

        virtual void * Build(void * data, int len);

        virtual void * Parser(void * data, int len);

};


#endif
