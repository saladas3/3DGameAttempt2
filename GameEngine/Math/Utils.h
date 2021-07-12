//
// Created by lucai on 10.07.2021.
//

#ifndef INC_3DGAME_UTILS_H
#define INC_3DGAME_UTILS_H

#pragma once

static float lerp(float start, float end, float delta) {
    return start * (1.0f - delta) + end * (delta);
}

#endif //INC_3DGAME_UTILS_H
