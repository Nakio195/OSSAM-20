TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

LIBS += -L$$PWD/../../Librairies/SFML-2.5.1-build-debug_MinGW7.3.0-x64/lib
LIBS += -L$$PWD/../../Librairies/SFML-2.5.1-build-release_MinGW7.3.0-x64/lib

win32
{
    INCLUDEPATH += ../../Librairies/SFML-2.5.1-build-debug_MinGW7.3.0-x64/include
    DEPENDPATH += ../../Librairies/SFML-2.5.1-build-debug_MinGW7.3.0-x64/include

    CONFIG(release, debug|release): LIBS +=     -lsfml-system
    else:CONFIG(debug, debug|release): LIBS +=  -lsfml-system-d

    CONFIG(release, debug|release): LIBS +=     -lsfml-window
    else:CONFIG(debug, debug|release): LIBS +=  -lsfml-window-d

    CONFIG(release, debug|release): LIBS +=     -lsfml-graphics
    else:CONFIG(debug, debug|release): LIBS +=  -lsfml-graphics-d

    CONFIG(release, debug|release): LIBS +=     -lsfml-audio
    else:CONFIG(debug, debug|release): LIBS +=  -lsfml-audio-d
}


HEADERS += \
    Entities/DataTables.h \
    Entities/Debris.h \
    Entities/Projectile.h \
    Entities/Spaceship.h \
    Entities/Entity.h \
    Items/Item.h \
#    Items/Shield.h \
#    Items/Weapons/Ammunition.h \
#    Items/Weapons/Bullet.h \
#    Items/Weapons/Bullet/Laser.h \
#    Items/Weapons/Bullet/Missile.h \
    Items/Weapons/Weapon.h \
    System/ATH.h \
    System/Animation.h \
    System/AnimationKey.h \
    System/AnimationKey/RotationKey.h \
    System/AnimationKey/ScaleKey.h \
    System/AnimationKey/TranslationKey.h \
#    System/EventsGenerator/GameEvent.h \
#    System/EventsGenerator/MiddleGroundGenerator.h \
    System/Graphics/PostEffect.h \
#    System/Inventory.h \
    System/MusicPlayer.h \
    System/Player.h \
    Ressources/RessourceHolder.h \
    Ressources/RessourceHolder.inl \
    Ressources/RessourceIdentifiers.h \
    System/Application.h \
    System/Commands/Category.h \
    System/Commands/Command.h \
    System/Scene/AnimationNode.h \
    System/Scene/AsteroidGenerator.h \
    System/Scene/EmitterNode.h \
    System/Scene/Particle.h \
    System/Scene/ParticleNode.h \
    System/Scene/SoundNode.h \
    System/Scene/TextNode.h \
#    System/States/LoadingState.h \
#    System/States/MenuState.h \
    System/SoundPlayer.h \
    System/States/PauseState.h \
    System/Scene/SceneNode.h \
    System/Scene/SpriteNode.h \
    System/States/State.h \
    System/States/StateIdentifiers.h \
    System/States/StateStack.h \
    System/States/GameState.h \
    System/States/TitleState.h \
    System/Timer.h \
#    System/UI/UI_Button.h \
#    System/UI/UI_Slot.h \
#    System/UserInterface.h \
    System/Utilities.h \
    System/World.h

SOURCES += \
        Entities/DataTables.cpp \
    Entities/Debris.cpp \
        Entities/Projectile.cpp \
        Entities/Spaceship.cpp \
        Entities/Entity.cpp \
        Items/Item.cpp \
#        Items/Shield.cpp \
#        Items/Weapons/Ammunition.cpp \
#        Items/Weapons/Bullet.cpp \
#        Items/Weapons/Bullet/Laser.cpp \
#        Items/Weapons/Bullet/Missile.cpp \
        Items/Weapons/Weapon.cpp \
        System/ATH.cpp \
        System/Animation.cpp \
        System/AnimationKey.cpp \
        System/AnimationKey/RotationKey.cpp \
        System/AnimationKey/ScaleKey.cpp \
        System/AnimationKey/TranslationKey.cpp \
#        System/EventsGenerator/GameEvent.cpp \
#        System/EventsGenerator/MiddleGroundGenerator.cpp \
        System/Graphics/PostEffect.cpp \
#        System/Inventory.cpp \
    System/MusicPlayer.cpp \
        System/Player.cpp \
        System/Application.cpp \
        System/Commands/Command.cpp \
    System/Scene/AnimationNode.cpp \
    System/Scene/AsteroidGenerator.cpp \
        System/Scene/EmitterNode.cpp \
        System/Scene/ParticleNode.cpp \
    System/Scene/SoundNode.cpp \
        System/Scene/TextNode.cpp \
#        System/States/LoadingState.cpp \
#        System/States/MenuState.cpp \
    System/SoundPlayer.cpp \
        System/States/PauseState.cpp \
        System/Scene/SceneNode.cpp \
        System/Scene/SpriteNode.cpp \
        System/States/State.cpp \
        System/States/StateStack.cpp \
        System/States/GameState.cpp \
        System/States/TitleState.cpp \
        System/Timer.cpp \
#        System/UI/UI_Button.cpp \
#        System/UI/UI_Slot.cpp \
#        System/UserInterface.cpp \
        System/Utilities.cpp \
        System/World.cpp \
        main.cpp


