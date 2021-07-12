//
// Created by lucai on 10.07.2021.
//

#ifndef INC_3DGAME_MAINGAME_H
#define INC_3DGAME_MAINGAME_H

#pragma once

#include "../GameEngine/WindowingSystem/Window.h"
#include "../GameEngine/InputSystem/InputListener.h"

class MainGame : public Window, public InputListener {

public:
    MainGame();

    ~MainGame();

    // Inherited via Window
    void onCreate() override;

    void onUpdate() override;

    void onDestroy() override;

    void onFocus() override;

    void onKillFocus() override;

    void onSize() override;

    // Inherited via InputListener
    void onKeyDown(int key) override;

    void onKeyUp(int key) override;

    void onMouseMove(const Point &mouse_pos) override;

    void onLeftMouseDown(const Point &mouse_pos) override;

    void onLeftMouseUp(const Point &mouse_pos) override;

    void onRightMouseDown(const Point &mouse_pos) override;

    void onRightMouseUp(const Point &mouse_pos) override;

};


#endif //INC_3DGAME_MAINGAME_H
