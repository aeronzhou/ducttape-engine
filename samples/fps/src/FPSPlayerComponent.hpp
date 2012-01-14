#ifndef FPSPLAYERCOMPONENT_H
#define FPSPLAYERCOMPONENT_H
#pragma once

#include "Weapon.hpp"

#include <Config.hpp>

#include <Logic/AdvancedPlayerComponent.hpp>
#include <Logic/RaycastComponent.hpp>

#include <vector>

#include <QString>

/**
  * A sample fps controller.
  */
class FPSPlayerComponent : public dt::AdvancedPlayerComponent {
    Q_OBJECT
public:
    FPSPlayerComponent(int weapon_num, const QString& name = "");

    void OnCreate();

    void OnDestroy();

    unsigned GetWeaponNumber() const;

    const Weapon* GetWeapon(unsigned weapon_type) const;

    const Weapon* GetWeaponInUse() const;

    const std::vector<Weapon*>& GetAllWeapons() const;

public:
    void AddWeapon(Weapon* weapon);

    void ChangeWeapon(unsigned weapon_type);

    void RemoveWeapon(unsigned weapon_type);

signals:
    void sWeaponChanged(const Weapon* current_weapon);

private:
    void _OnMousePressed();

private slots:
    void _OnKeyPressed(const OIS::KeyEvent& event);

    void _PickUpWeapon(dt::PhysicsBodyComponent* object);

private:
    int mWeaponNum;
    Weapon* mWeaponInUse;
    std::vector<Weapon*> mWeapons;
    dt::RaycastComponent* mGrabber;
};

#endif