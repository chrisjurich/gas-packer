#ifndef __GASATOM_H__
#define __GASATOM_H__

#include<string>
#include<vector>
#include<cmath>
#include<iostream>

#include<gb_utils.h>

struct Position{
    // simple struct representing a position in x,y,z space
    double x, y, z;

    Position(
            double x=0.,
            double y=0.,
            double z=0.
            ) : x(x), y(y), z(z) {}

    void
    operator+=(const Position& other) {
        
        x += other.x;
        y += other.y;
        z += other.z;
    }
};


class GasAtom {
    private:
        const Dimensions& dimensions;
    private:
        unsigned int atom_id;
    private:
        Position curr_pos;
    private:
        std::vector<Position> past_position;

    //public:
    //    GasAtom() : atom_id(0),
    //                curr_pos(Position()) {}
    public:
        GasAtom(
                double x,
                double y,
                double z,
                const Dimensions& dimensions,
                unsigned int atom_id 
               ) : atom_id(atom_id), dimensions(dimensions),curr_pos(Position(x,y,z)) {}
    public:
        double
        distance(const GasAtom&) const;

    public:
        void
        operator+=(const GasAtom& other) {
            past_position.push_back(curr_pos); 
            curr_pos += other.curr_pos;
            _apply_bounds();
        }
    
    public:
        void
        operator+=(const Position& pos) {
            past_position.push_back(curr_pos); 
            curr_pos += pos;
            _apply_bounds();
        }

    private:
        void
        _apply_bounds();

    friend std::ostream& operator<<(std::ostream& os, const GasAtom& GA)
    {
        os<<"atom id: "<<GA.atom_id<<" location ("<<GA.curr_pos.x<<","<<GA.curr_pos.y<<","<<GA.curr_pos.z<<")\n";
        return os;
    }

};


#endif //__GASATOM_H__
