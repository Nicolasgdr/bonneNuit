#ifndef POSITION_HPP
#define POSITION_HPP
#include <cstddef>
class Position {
public:
    inline size_t getRow()
    {
        return this->_row;
    }

    inline size_t getColumn()
    {
        return this->_column;
    }
    Position()=default;

    Position(size_t row,  std::size_t column) : _row(row), _column(column){}
    bool operator==(const Position&rhs)const
    {
        return this->_row==rhs._row && this->_column==rhs._column;
    }
private:
    size_t _row;
    size_t _column;
};

#endif // POSITION_HPP
