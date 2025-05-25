// Copyright 2025 Maslennikova Mary

#include "/git/Film_library/Creator/Creator.h"

#ifndef FILM_LIBRARY_ACTOR_ACTOR_H_
#define FILM_LIBRARY_ACTOR_ACTOR_H_

class Actor : public Creator {
 public:
    Actor();
    Actor(const FIO&, const Date&);
    explicit Actor(const Creator&);
    Actor(const Actor&);

    ~Actor() = default;
};
#endif  // FILM_LIBRARY_ACTOR_ACTOR_H_
