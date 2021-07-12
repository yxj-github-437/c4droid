#ifndef STONE_H
#define STONE_H
#include<QString>
class Stone
{
public:
    Stone();
    ~Stone();
    
    enum TYPE {JIANG,CHE,MA,PAO,SHI,BING,XIANG};
    
    int _row;
    int _col;
    int _id;
    bool _dead;
    bool _black;
    TYPE _type;

    void init(int id)
    {
        struct {
            int row, col;
            Stone::TYPE type;
        } pos[16] = {
        {0, 0, Stone::CHE},
        {0, 1, Stone::MA},
        {0, 2, Stone::XIANG},
        {0, 3, Stone::SHI},
        {0, 4, Stone::JIANG},
        {0, 5, Stone::SHI},
        {0, 6, Stone::XIANG},
        {0, 7, Stone::MA},
        {0, 8, Stone::CHE},
 
        {2, 1, Stone::PAO},
        {2, 7, Stone::PAO},
        {3, 0, Stone::BING},
        {3, 2, Stone::BING},
        {3, 4, Stone::BING},
        {3, 6, Stone::BING},
        {3, 8, Stone::BING},
        };
 
        if(id<16)
        {
            _row=pos[id].row;
            _col=pos[id].col;
            _type=pos[id].type;
        }
        else
        {
            _row=9-pos[id-16].row;
            _col=8-pos[id-16].col;
            _type=pos[id-16].type;
        }
 
        _id=id;
        _dead=false;
        _black=id<16;
 
 
    }
 
    QString getText()
    {   if(!(this->_black))
        switch(this->_type)
        {
        case CHE:
            return "车";break;
        case MA:
            return "马";break;
        case PAO:
            return "炮";break;
        case BING:
            return "兵";break;
        case JIANG:
            return "帅";break;
        case SHI:
            return "仕";break;
        case XIANG:
            return "相";break;}

        else
        switch(this->_type)
        {
        case CHE:
            return "车";break;
        case MA:
            return "马";break;
        case PAO:
            return "炮";break;
        case BING:
            return "卒";break;
        case JIANG:
            return "将";break;
        case SHI:
            return "士";break;
        case XIANG:
            return "象";break;}
        return "";
    }

    
};




#endif //STONE_H