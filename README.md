# Cub3D

A Wolfenstein 3D-style raycasting engine built with MinilibX.

## 🎮 Features

- **Player Movement**: WASD keys for movement, arrow keys for rotation
- **Sprint Mechanic**: Hold Shift + movement keys for 4x speed
- **Collision Detection**: Prevents walking through walls
- **Raycasting Engine**: Full field of view rendering
- **Map Parsing**: Reads `.cub` files for map data
- **Norminette Compliant**: All code follows 42 coding standards

## 🏗️ Project Structure

```
Cub3D/
├── main.c                 # Program entry point
├── Makefile              # Build configuration
├── .gitignore           # Git ignore rules
├── test.cub             # Sample map file
├── srcs/                # Source files
│   ├── utils.c          # Utility functions
│   ├── init_game.c      # Game initialization
│   ├── game_loop.c      # Main game loop
│   ├── movement.c       # Player movement logic
│   ├── collision.c      # Collision detection
│   ├── rendering.c      # Drawing functions
│   ├── raycasting.c     # Ray calculation
│   └── map_parser.c     # Map file parsing
├── includes/            # Header files
│   ├── cub3d.h         # Main header
│   └── mlx/            # MinilibX library
├── libft/              # Custom library functions
└── get_next_line/      # File reading utilities
```

## 🚀 Building and Running

### Prerequisites
- GCC compiler
- MinilibX library (included)
- X11 development libraries

### Build
```bash
make
```

### Run
```bash
./cub3d maps/test.cub
```

### Clean
```bash
make clean
make fclean
```

## 🎯 Controls

| Key | Action |
|-----|--------|
| **W** | Move forward |
| **S** | Move backward |
| **A** | Strafe left |
| **D** | Strafe right |
| **←** | Rotate left |
| **→** | Rotate right |
| **Shift + Movement** | Sprint (4x speed) |
| **ESC** | Exit game |

## 📁 Map Format (.cub)

The game reads `.cub` files containing map data:

```
1111111111
1000000001
1000000001
1000000001
1000000001
1000000001
1000000001
1000000001
1000000001
1111111111
```

- `1`: Wall
- `0`: Empty space
- ` `: Empty space

## 🔧 Technical Details

### Norminette Compliance
- ✅ Max 25 lines per function
- ✅ Max 5 functions per file
- ✅ Max 4 parameters per function
- ✅ Proper indentation with tabs
- ✅ No global variables
- ✅ No forbidden functions

### Architecture
- **Modular Design**: Functions split across logical files
- **Memory Management**: Proper allocation and cleanup
- **Error Handling**: Graceful error handling throughout
- **Performance**: Optimized rendering and collision detection

## 🎨 Rendering

- **2D Map View**: Top-down view of the game world
- **Player Representation**: Green square with red direction line
- **Raycasting**: Blue lines showing ray collisions
- **Real-time Updates**: Smooth 60 FPS rendering

## 🐛 Debug Features

- **Visual Debugging**: Player position and direction indicators
- **Collision Visualization**: Ray lines show collision detection
- **Map Scaling**: Configurable map display scale

## 📝 License

This project is part of the 42 curriculum and follows their coding standards.

## 👨‍💻 Author

**Omar Iskandarani** - 42 Beirut Student

---

*Built with ❤️ and lots of coffee ☕* 