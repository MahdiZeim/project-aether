#pragma once

#include <SFML/Graphics.hpp>
#include <memory>

#include "aether/gameplay/projectile.hpp"

namespace aether::gameplay
{

enum class WeaponState
{
    Ready,
    Reloading
};

class Weapon
{
public:
    Weapon();

    void setPosition(sf::Vector2f position);
    void setDirection(sf::Vector2f direction);
    void update(float deltaTime);

    void render(sf::RenderWindow& window) const;
    std::unique_ptr<Projectile> fire();

    int getAmmo() const;
    int getMagazineSize() const;
    void startReload();
    void updateReload(float deltaTime);
    bool isReloading() const;
    bool canFire() const;
    
private:
    sf::RectangleShape shape_;
    sf::Vector2f position_{0.0f, 0.0f};
    sf::Vector2f direction_{1.0f, 0.0f};

    float damage_{20.0f};
    float projectileSpeed_{800.0f};
    float range_{500.0f};
    float fireRate_{5.0f};
    float fireCooldown_{0.0f};

    int magazineSize_{12};
    int ammo_{12};
    float reloadTime_{1.5f};
    float reloadTimer_{0.0f};

    WeaponState state_{WeaponState::Ready};
};

} // namespace aether::gameplay