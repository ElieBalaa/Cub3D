# 🇱🇧 Lebanese Military Theme for Cub3D

## Overview
This Cub3D game has been enhanced with a Lebanese military theme, featuring authentic Lebanese army colors, textures, and patriotic elements.

## 🎖️ Theme Features

### **Wall Textures**
- **Lebanese Flag Wall** (`lebanese_flag_wall.xpm`): Red, white, and green stripes with cedar tree
- **Military Camouflage** (`lebanese_military_wall.xpm`): Olive green and desert tan military pattern
- **Original Stone Wall** (`wall.xpm`): Classic stone texture for variety

### **Color Scheme**
- **Floor**: Desert sand (`RGB: 160,82,45`)
- **Ceiling**: Sky blue (`RGB: 135,206,235`)
- **Walls**: Lebanese flag colors and military olive/tan

## 🗺️ Maps Available

### **1. Lebanese Military Base** (`maps/lebanese_military.cub`)
- **North Wall**: Lebanese flag texture
- **South Wall**: Military camouflage texture  
- **West Wall**: Original stone texture
- **East Wall**: Lebanese flag texture
- **Theme**: Military training facility with patriotic elements

### **2. Standard Maps** (`maps/test.cub`, `test.cub`)
- All walls use the original stone texture
- Standard desert theme colors

## 🎮 Controls
- **WASD**: Move (Forward/Back/Strafe Left/Right)
- **Arrow Keys**: Look Left/Right
- **Shift + Movement**: Sprint (4x speed)
- **F**: Toggle Fullscreen
- **ESC**: Exit game

## 🚀 Running the Game

### **Lebanese Military Theme**
```bash
make
./cub3d maps/lebanese_military.cub
```

### **Standard Theme**
```bash
make
./cub3d maps/test.cub
```

## 🎨 Creating Custom Textures

### **Texture Requirements**
- Format: `.xpm` files
- Size: 64x64 pixels (recommended)
- Colors: Use Lebanese military palette

### **Lebanese Military Colors**
```css
Lebanese Red:    #ED1C24
Lebanese White:  #FFFFFF  
Lebanese Green:  #00A859
Olive Drab:      #556B2F
Desert Tan:      #D2B48C
Military Brown:  #8B4513
```

### **Adding New Textures**
1. Create `.xpm` file in `textures/walls/`
2. Update map `.cub` file with texture path
3. Recompile and test

## 📁 File Structure
```
Cub3D/
├── textures/
│   └── walls/
│       ├── wall.xpm                    # Original stone
│       ├── lebanese_flag_wall.xpm      # Lebanese flag
│       └── lebanese_military_wall.xpm  # Military camo
├── maps/
│   ├── test.cub                        # Standard map
│   └── lebanese_military.cub           # Military theme
└── LEBANESE_MILITARY_THEME.md          # This file
```

## 🛠️ Development Notes

### **Texture Creation Tools**
- **GIMP**: Export as XPM format
- **ImageMagick**: `convert image.png texture.xpm`
- **Online converters**: PNG/JPG to XPM

### **Map Configuration**
```
NO ./textures/walls/north_texture.xpm
SO ./textures/walls/south_texture.xpm
WE ./textures/walls/west_texture.xpm
EA ./textures/walls/east_texture.xpm

F R,G,B    # Floor color
C R,G,B    # Ceiling color
```

## 🎯 Future Enhancements

### **Planned Features**
- [ ] Lebanese army soldier sprites
- [ ] Military vehicle objects
- [ ] Sound effects (Lebanese national anthem)
- [ ] More detailed cedar tree textures
- [ ] Animated Lebanese flag texture
- [ ] Multiple military base maps

### **Texture Ideas**
- Lebanese army insignia walls
- Concrete bunker textures
- Sandbag barrier walls
- Military equipment textures
- Beirut cityscape backgrounds

---

**Made with pride for Lebanon** 🇱🇧
**Long live the Lebanese Armed Forces!** 🎖️ 