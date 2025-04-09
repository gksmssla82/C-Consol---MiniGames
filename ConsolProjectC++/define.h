#pragma once
#define SAFE_DELETE(p) if (p) { delete p; p = nullptr; }
#define SAFE_DELETE_ARR(p) if (p) { delete[] p; p = nullptr; }

// Tetris
#define MAP_HEIGHT 12;
#define MAP_WIDTH 22;