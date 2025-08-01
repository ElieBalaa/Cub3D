# Cub3D

A 3D raycasting game engine inspired by Wolfenstein 3D, built with MinilibX. Features a Lebanese military theme with textured walls and floors.

## Features

### 🎮 **Core Gameplay**
- **3D First-Person View** - Raycasting engine with distance-based wall shading
- **Player Movement** - WASD controls with smooth collision detection
- **Player Rotation** - Arrow keys for view rotation
- **Sprint Mechanic** - Hold Shift while moving for increased speed
- **Fullscreen Toggle** - Press F to switch between windowed and fullscreen modes
- **Texture Mapping** - XPM texture support for walls and floors

### 🗺️ **Minimap System**
- **Responsive Circular Minimap** - Positioned at bottom-right corner
- **Player-Centered View** - Map moves opposite to player movement
- **Professional Styling** - Dark theme with clean borders
- **Dynamic Scaling** - Adapts to different window sizes
- **Direction Indicator** - Shows player's current facing direction

### 🎨 **Lebanese Military Theme**
- **Military Textures** - Lebanese flag and military camouflage wall textures
- **Themed Maps** - Lebanese military-themed map layouts
- **Custom Floor Textures** - Military-style floor patterns
- **Atmospheric Colors** - Military color scheme for ceiling and floor

### 🎯 **Technical Features**
- **Map Parsing** - Supports .cub files with texture paths and color definitions
- **Texture System** - XPM texture loading and rendering
- **Collision Detection** - Prevents walking through walls
- **Memory Management** - Proper cleanup and resource management
- **Event Handling** - Responsive keyboard and window event handling
- **Norminette Compliant** - All source files follow 42 coding standards

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

# Run with the Lebanese military map
./cub3d maps/lebanese_military.cub

# Or run with the test map
./cub3d maps/test.cub
```

### Map Format (.cub files)
Create a `.cub` file with texture definitions and map layout:

```
# Texture paths (required)
NO ./textures/walls/wall.xpm
SO ./textures/walls/wall.xpm
WE ./textures/walls/wall.xpm
EA ./textures/walls/wall.xpm

# Floor and ceiling colors (RGB format)
F 139,69,19
C 135,206,235

# Map layout (after empty line)
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
│   ├── ray_utils.c         # Raycasting utilities
│   ├── ray_helpers.c       # Raycasting helper functions
│   ├── collision.c         # Collision detection
│   ├── rendering.c         # 2D drawing functions
│   ├── minimap.c           # Minimap rendering
│   ├── minimap_utils.c     # Minimap utility functions
│   ├── window_utils.c      # Window management utilities
│   ├── map_parser.c        # Map file parsing
│   ├── map_utils.c         # Map utility functions
│   ├── map_helpers.c       # Map helper functions
│   ├── texture_utils.c     # Texture loading and management
│   └── utils.c             # General utilities
├── includes/
│   └── cub3d.h            # Main header file
├── libft/                  # Custom library functions
├── get_next_line/          # File reading utilities
├── textures/
│   ├── walls/              # Wall texture files (.xpm)
│   └── floor/              # Floor texture files (.xpm)
├── maps/                   # Map files (.cub)
└── LEBANESE_MILITARY_THEME.md # Theme documentation
```

## Technical Details

### **Raycasting Engine**
- **DDA Algorithm** - Digital Differential Analyzer for efficient wall detection
- **Texture Mapping** - Perspective-correct texture rendering
- **Distance Shading** - Walls appear darker at greater distances
- **Floor Casting** - Textured floor rendering with perspective correction

### **Modular Architecture**
- **Separation of Concerns** - Each file has a specific responsibility
- **Norminette Compliance** - Max 25 lines per function, max 4 parameters
- **Memory Safety** - Proper allocation and deallocation
- **Error Handling** - Graceful error handling and cleanup

### **Performance Optimizations**
- **Efficient Rendering** - Only renders visible walls
- **Collision Optimization** - Fast collision detection algorithms
- **Memory Management** - Minimal memory footprint
- **Event-Driven** - Responsive input handling

## Development

### **Coding Standards**
- **42 Norminette** - All source files follow strict coding standards
- **Function Limits** - Max 25 lines per function, max 4 parameters
- **File Structure** - Max 5 functions per file for modularity
- **Naming Convention** - snake_case for all identifiers

### **Build System**
- **Makefile** - Automated build process
- **Dependencies** - Automatic library linking
- **Clean Targets** - Easy cleanup and rebuild

## Contributing

1. Follow 42 Norminette coding standards
2. Ensure all functions are under 25 lines
3. Keep functions to maximum 4 parameters
4. Test with different map files
5. Update documentation for new features

## License

This project is part of the 42 curriculum and follows 42 coding standards. 