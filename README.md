# ENLSVG Pathfinding Demo

A sample application that makes use of ENLSVG-Pathfinding for fast any-angle path computation.

Makes use of [SFML](https://www.sfml-dev.org/).

The player operates on a point-and-click control scheme. Click on an empty space and the player character (an orange circle) will automatically make its way there.

A 1000x1000 grid map is randomly generated using cellular automata.

Minerals repeatly spawn at random locations throughout the map. (at a rate of 1 per frame, i.e. 60 per second)

For each mineral that spawns, a little "bot" is sent out from the player character, which finds its way to the mineral, picks it up, and returns back to the player character.

For each bot,
- One path computation is done to find the shortest path from the player character to the mineral.
- When returning to the player character, the bot recomputes its path back to the player three times per second. This is because the player might possibly move around while it is making its way back to the player.
