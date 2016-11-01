#include "Star.h"

Star::Star(const sf::Vector2f position, const int owner, sf::Texture* starTexture/*this from resource manager*/, const float energy = 100)
    :GameObject(position, owner, "star", starTexture, energy)
{

}