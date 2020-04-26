#ifndef CATEGORY_H
#define CATEGORY_H

namespace Category
{
    enum Type
    {
        Uninitialized = 0,
        None = Uninitialized,

        Scene = 2,

        PlayerSpaceship = 4,
        AlliedSpaceship = 8,
        EnemySpaceship = 16,
        Spaceship = PlayerSpaceship |AlliedSpaceship | EnemySpaceship,

        AlliedProjectile = 32,
        EnemyProjectile = 64,
        Projectile = AlliedProjectile | EnemyProjectile,

        SceneAirLayer           = 128,
        SceneBackgroundLayer    = 256,
        SceneProjectileLayer    = 512,

        Particle        = 1024,
        Emitter         = 2048,

        TextNode        = 4096,
        SpriteNode      = 8192,
        Weapon          = 1 << 14,

        SoundNode       = 1 << 15,
        AnimationNode   = 1 << 16,

        Debris          = 1 << 17,

        CommandGenerator    = 1 << 18,
        DebrisGenerator     = 1 << 19
    };
}

#endif // CATEGORY_H
