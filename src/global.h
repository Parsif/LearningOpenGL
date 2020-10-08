#ifndef LEARNINGOPENGL_GLOBAL_H
#define LEARNINGOPENGL_GLOBAL_H

namespace opengl
{
    enum class Direction
    {
        up, down, right, left
    };

    struct MousePos
    {
        float x, y, pitch = 0.f, yaw = -90.0f;
    };
}

#endif //LEARNINGOPENGL_GLOBAL_H
