# Cub3D

A 3D raycasting game engine inspired by Wolfenstein 3D, built with MinilibX.

## Features

### 🎮 **Core Gameplay**
- **3D First-Person View** - Raycasting engine with distance-based wall shading
- **Player Movement** - WASD controls with smooth collision detection
- **Player Rotation** - Arrow keys for view rotation
- **Sprint Mechanic** - Hold Shift while moving for increased speed
- **Fullscreen Toggle** - Press F to switch between windowed and fullscreen modes

### 🗺️ **Minimap System**
- **Responsive Circular Minimap** - Positioned at bottom-right corner
- **Player-Centered View** - Map moves opposite to player movement
- **Professional Styling** - Dark theme with clean borders
- **Dynamic Scaling** - Adapts to different window sizes
- **Direction Indicator** - Shows player's current facing direction

### 🎯 **Technical Features**
- **Map Parsing** - Supports .cub files with custom map layouts
- **Collision Detection** - Prevents walking through walls
- **Memory Management** - Proper cleanup and resource management
- **Event Handling** - Responsive keyboard and window event handling

## Controls

| Key | Action |
|-----|--------|
| **W** | Move forward |
| **A** | Strafe left |
| **S** | Move backward |
| **D** | Strafe right |
| **← →** | Rotate view |
| **Shift** | Sprint (hold with movement) |
| **F** | Toggle fullscreen |
| **ESC** | Exit game |

## Installation & Usage

### Prerequisites
- GCC compiler
- MinilibX library
- X11 development libraries

### Build Instructions
```bash
# Clone the repository
git clone <repository-url>
cd Cub3D

# Build the project
make

# Run with a map file
./cub3d maps/test.cub
```

### Map Format
Create a `.cub` file with your map layout:
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

- `1` = Wall
- `0` = Walkable space
- `N` = Player spawn point (facing north)

## Project Structure

```
Cub3D/
├── srcs/
│   ├── main.c              # Entry point
│   ├── init_game.c         # Game initialization
│   ├── game_loop.c         # Main game loop and input handling
│   ├── movement.c          # Player movement logic
│   ├── raycasting.c        # 3D rendering engine
│   ├── collision.c         # Collision detection
│   ├── rendering.c         # 2D drawing functions
│   ├── minimap.c           # Minimap rendering
│   ├── minimap_utils.c     # Minimap utility functions
│   ├── window_utils.c      # Window management utilities
│   ├── map_parser.c        # Map file parsing
│   └── utils.c             # General utilities
├── includes/
│   └── cub3d.h            # Main header file
├── libft/                  # Custom library functions
├── get_next_line/          # File reading utilities
└── maps/                   # Map files
```

## Technical Details

### Rendering Engine
- **Raycasting Algorithm** - Casts rays from player position to determine wall distances
- **Distance-Based Shading** - Walls appear darker at greater distances
- **Field of View** - 60-degree FOV for realistic perspective
- **Wall Slicing** - Each vertical slice represents one ray

### Performance Features
- **Optimized Raycasting** - Efficient collision detection with early termination
- **Memory Efficient** - Minimal memory allocation and proper cleanup
- **Smooth Movement** - 60 FPS target with responsive controls

### Code Quality
- **42 Norminette Compliant** - Follows strict coding standards
- **Modular Design** - Functions split across logical files
- **Error Handling** - Comprehensive error checking and reporting
- **Documentation** - Clear function documentation and comments

## Development

### Building for Development
```bash
# Clean build
make fclean && make

# Check for memory leaks
make leaks

# Run norminette check
make norm
```

### Debugging
- Use `make leaks` for memory leak detection
- Check console output for error messages
- Validate map files before running

## Author

**Omar Iskandarani** - 42 Beirut Student

---

*This project is part of the 42 curriculum, demonstrating advanced C programming concepts including graphics programming, memory management, and algorithm implementation.* 