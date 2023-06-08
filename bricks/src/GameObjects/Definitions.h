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
        BrickGood,
        BrickExploding,
        BrickDestroyed
    };

    enum PowerUpType {
        Magnetic, 
        ExtraLife,
        TripleBall,
        Laser, 
        SlowBall,
        LevelSkip,
        Wide
    };

    enum BulletStatus {
        BulletGood,
        BulletExploding,
        BulletDead
    };
    
    enum TurretStatus {
        TurretGood,
        TurretExploding,
        TurretDead
    };
}