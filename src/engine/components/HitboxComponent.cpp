/*
** EPITECH PROJECT, 2018
** Thomas Arbona
** File description:
** engine
*/

#include "engine/core/Game.hpp"
#include "HitboxComponent.hpp"

engine::HitboxComponent::HitboxComponent()
{}

engine::HitboxComponent::HitboxComponent(std::string const& polygon)
    : hasDebugMode(false)
{
	boost::geometry::read_wkt("POLYGON(" + polygon + ")", hitbox2D);

    std::size_t it = 0;
    Point firstPoint;
    Point prevPoint;
    boost::geometry::for_each_point(hitbox2D, [&](Point const& p) -> void {
        if (it == 0) {
            firstPoint = p;
        } else {
            auto segment = Segment3D{{
                boost::geometry::get<0>(prevPoint),
                boost::geometry::get<1>(prevPoint), 0.f
            }, {
                boost::geometry::get<0>(p),
                boost::geometry::get<1>(p), 0.f
            }};
            segments3D.push_back(segment);
        }
        prevPoint = p;
        it += 1;
    });
    auto segment = Segment3D{{
        boost::geometry::get<0>(prevPoint),
        boost::geometry::get<1>(prevPoint), 0.f
    }, {
        boost::geometry::get<0>(firstPoint),
        boost::geometry::get<1>(firstPoint), 0.f
    }};
    segments3D.push_back(segment);
}
