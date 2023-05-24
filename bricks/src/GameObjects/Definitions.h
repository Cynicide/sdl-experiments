#pragma once
namespace Definitions

{
    enum BrickType {
        Red,
        Orange,
        Yellow,
        Green,
        Blue,
        Purple,
        Tough,
        Indestructable
    };

    enum BrickStatus {
        Good,
        Exploding,
        Destroyed,
    };

    enum PowerUpType {
        StickyBalls, 
        OneUp,
        TripleBalls,
        Lasers, 
        SlowBalls,
        LevelSkip
    };
    
    /*static const std::unordered_map<int, Definitions::BrickType> typeMap {
        {1, Definitions::BrickType::Red},
        {2, Definitions::BrickType::Blue},
        {3, Definitions::BrickType::Yellow},
        {4, Definitions::BrickType::Tough},
        {5, Definitions::BrickType::Indestructable},
        {6, Definitions::BrickType::Orange},
        {7, Definitions::BrickType::Green},
        {8, Definitions::BrickType::Purple},
    };*/
}