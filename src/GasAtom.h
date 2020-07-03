#ifndef __GASATOM_H__
#define __GASATOM_H__

#include<string>
#include<vector>
#include<cmath>

struct Position{
    // simple struct representing a position in x,y,z space
    double x, y, z;

    Position(
            double x=0.,
            double y=0.,
            double z=0.
            ) : x(x), y(y), z(z) {}

};


class GasAtom {
    private:
        std::string atom_type;
    private:
        Position curr_pos;
    private:
        std::vector<Position> past_position;

    public:
        GasAtom() : atom_type("NONE"),
                    curr_pos(Position()) {}
    public:
        GasAtom(
                double x,
                double y,
                double z,
                std::string name
               ) : atom_type(name), curr_pos(Position(x,y,z)) {}
    public:
        double
        distance(const GasAtom&) const;

};








#endif //__GASATOM_H__
