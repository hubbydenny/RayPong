# 🏓 RayPong

A classic two-player Pong game built with C++ and raylib.
 
 ⚠️ **IMPORTANT** - You need to download cmake if u on Linux
> ⚠️ **IMPORTANT2** — To play on Arch or Arch-based distro:
> ```bash
> sudo pacman -S raylib
> git clone https://github.com/L4rpius/RayPong.git
> cd RayPong
> make run
> ```
> On Windows just open `RayPong.exe`

---

## About

RayPong is a local two-player Pong game where two players compete against each other. The ball bounces off paddles and walls, and each goal increases the score. The game features a settings menu, customizable backgrounds, and difficulty options.

## Features

- Two-player mode — Player 1 controls with W/S keys, Player 2 with Arrow Up/Down
- Ball physics — realistic bouncing off walls and paddles with random direction on reset
- Score system — tracks goals for both players
- Goals (gates) — visible red gates on each side of the screen
- Settings menu (ESC):
  - Volume slider
  - Fullscreen toggle
  - VSync toggle
  - FPS counter toggle
  - Difficulty selector (Easy / Medium / Hard)
  - Background color selector (4 colors)
- Fullscreen support — all elements adapt to screen size
- FPS counter — optional on-screen FPS display
- GUI — built with raygui

## Controls

| Action    | Player 1 | Player 2  |
|-----------|----------|-----------|
| Move Up   | W        | Arrow Up  |
| Move Down | S        | Arrow Down|

## Technologies

<p align="left">
  <img src="https://img.shields.io/badge/C%2B%2B-00599C?style=for-the-badge&logo=cplusplus&logoColor=white" alt="C++"/>
  <img src="https://img.shields.io/badge/raylib-EE0000?style=for-the-badge&logo=cplusplus&logoColor=white" alt="raylib"/>
  <img src="https://img.shields.io/badge/raygui-FF6600?style=for-the-badge&logo=cplusplus&logoColor=white" alt="raygui"/>
</p>

## License

This project is licensed under the MIT License.
