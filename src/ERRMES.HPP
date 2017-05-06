#ifndef ERRMES
#define ERRMES
#include"header.hpp"
class ErrMes{
    private:
        /*class MESSAGE{
            public:
            int ErrorCode;
            string eng;
            string zh;
        };
        static MESSAGE MesTable[];*/
        /*
            map��hashTable
            �i�[�֬d�䪺�t��
            map<int ErrorCode,MESSAGE>
            �ت��ɱĥ� �ܼƦW[ErrorCode]={�^��,����};
            �ϥ�find()�����禡�i��^�@�ӭ��N��
            ���N��->second���XMESSAGE
        */
        typedef struct{
            string eng;
            string zh;
        }MESSAGE;
        static map<int,MESSAGE> MesTable;
        static map<int,MESSAGE> initTable();
    public:
        //static string get_ErrorMessage(int,string);
        static string get_ErrorMessage(int,string);
};

#endif // ERRMES