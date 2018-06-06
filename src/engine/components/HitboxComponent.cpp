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
    boost::geometry::correct(hitbox2D);

    std::size_t it = 0;
    Point firstPoint;
    Point prevPoint;
    Vec2D min;
    Vec2D max;
    boost::geometry::for_each_point(hitbox2D, [&](Point const& p) -> void {
        if (it == 0) {
            firstPoint = p;
            min.X = boost::geometry::get<0>(p);
            min.Y = boost::geometry::get<1>(p);
            max.X = min.X;
            max.Y = min.Y;
        } else {
            auto segment = Segment3D{{
                boost::geometry::get<0>(prevPoint),
                boost::geometry::get<1>(prevPoint), 0.f
            }, {
                boost::geometry::get<0>(p),
                boost::geometry::get<1>(p), 0.f
            }};
            segments3D.push_back(segment);

            if (boost::geometry::get<0>(p) < min.X)
                min.X = boost::geometry::get<0>(p);
            if (boost::geometry::get<0>(p) > max.X)
                max.X = boost::geometry::get<0>(p);
            if (boost::geometry::get<1>(p) < min.Y)
                min.Y = boost::geometry::get<1>(p);
            if (boost::geometry::get<1>(p) > max.Y)
                max.Y = boost::geometry::get<1>(p);
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

    size.X = max.X - min.X;
    size.Y = max.Y - min.Y;
    AABBPosition.X = min.X;
    AABBPosition.Y = max.Y;
}
