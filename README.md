# Cub3D

A Wolfenstein 3D-style raycasting engine built with MinilibX.

## 🎮 Features

- **3D First-Person View**: Immersive raycasting-based 3D rendering
- **2D Map View**: Top-down debugging view (toggle with TAB)
- **Player Movement**: WASD keys for movement, arrow keys for rotation
- **Sprint Mechanic**: Hold Shift + movement keys for 4x speed
- **Collision Detection**: Prevents walking through walls
- **Distance-Based Shading**: Walls get darker with distance for realistic depth
- **Real-time Rendering**: Smooth 60 FPS 3D perspective
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
│   ├── raycasting.c     # 3D raycasting engine
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
./cub3d test.cub
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
| **TAB** | Toggle between 3D and 2D view |
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

### 3D Raycasting Engine
- **Ray Casting**: One ray per screen column for 3D perspective
- **Distance Calculation**: Accurate wall distance measurements
- **Height Projection**: Walls scale based on distance from player
- **Fish-eye Correction**: Proper perspective correction
- **Distance Shading**: Walls fade to darker colors with distance

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

### 3D View (Default)
- **First-Person Perspective**: Immersive 3D raycasting view
- **Sky Blue Ceiling**: Light blue ceiling color
- **Brown Floor**: Earth-tone floor color
- **Distance Shading**: Walls get darker as they get farther
- **Real-time Updates**: Smooth 60 FPS rendering

### 2D Debug View (TAB to toggle)
- **Top-down Map**: Bird's eye view of the game world
- **Player Representation**: Green square with red direction line
- **Map Scaling**: Configurable map display scale

## 🐛 Debug Features

- **View Toggle**: Switch between 3D and 2D views with TAB
- **Visual Debugging**: Player position and direction indicators in 2D mode
- **Map Visualization**: Clear map layout in debug mode

## 📝 License

This project is part of the 42 curriculum and follows their coding standards.

## 👨‍💻 Author

**Omar Iskandarani** - 42 Beirut Student

---

*Built with ❤️ and lots of coffee ☕* 