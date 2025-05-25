// Copyright 2025 Maslennikova Mary

#include <iostream>

#include "/git/Film_library/Actor/Actor.h"

Actor::Actor() : Creator() {}
Actor::Actor(const FIO& person, const Date& date) : Creator(person, date) {}
Actor::Actor(const Creator& other) : Creator(other) {}
Actor::Actor(const Actor& other) : Creator(other) {}
