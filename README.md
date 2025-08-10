# Cub3D

A 3D raycasting engine (MiniLibX) that renders a maze from a first-person view. The project is split into a strict mandatory target and a separate bonus target.

## Build

```bash
# Mandatory
make

# Bonus
make bonus

# Clean objects
make clean

# Full clean (objects + binary)
make fclean
```

## Run

```bash
./cub3d <path/to/map.cub>
```

Example:
```bash
./cub3d test.cub
```

## Controls

- W/A/S/D: Move
- Left/Right: Rotate
- Shift: Sprint
- F: Toggle fullscreen
- ESC or window close: Quit
- E: Interact (doors) — bonus only
- Mouse (bonus): Look around

## Features

### Mandatory
- Raycasting renderer with proper wall texturing (NO, SO, WE, EA).
- Ceiling and floor colors from the map file (no floor texture for mandatory).
- Movement and rotation as specified by the subject.
- Robust .cub parsing and validation:
  - Map must be closed/surrounded by walls.
  - Exactly one player spawn (N/S/E/W).
  - Only valid characters in the map.
  - Texture paths and color values validated.
- Clear error messages and clean exit on failure.
- Norminette-compliant code structure.

### Bonus
- Smooth, time-based animated doors:
  - Place `D` in the map to define a closed door; it animates and opens with `E`.
  - Auto-close after a delay unless the player is inside the door cell.
  - Proper background visibility during opening via continued DDA behind doors.
- Door collisions: closed doors block, open doors are passable.
- Textured floor rendering and correct floor sampling visible behind opening doors.
- First-person weapon overlay (`textures/weapon/weapon.xpm`) drawn at the bottom.
- Mouse look with recentring cursor for continuous rotation.
- HUD hint: shows "Press E to open the Door" when the player is adjacent to a door.
- Minimap and other extras (when enabled in your repo).

## Map Format (.cub)

- Texture paths:
  - `NO ./path_to_north_texture.xpm`
  - `SO ./path_to_south_texture.xpm`
  - `WE ./path_to_west_texture.xpm`
  - `EA ./path_to_east_texture.xpm`
- Colors:
  - `F R,G,B` (floor)
  - `C R,G,B` (ceiling)
- Map: last section, using only the following characters:
  - `1` wall
  - `0` empty
  - `N` `S` `E` `W` player spawn (exactly one)
  - `D` door (bonus; blocks in mandatory, animates in bonus)
  - space (padding/void)

Example:
```
NO ./textures/walls/north.xpm
SO ./textures/walls/south.xpm
WE ./textures/walls/west.xpm
EA ./textures/walls/east.xpm
F 220,100,0
C 135,206,235

1111111
10D0001
1010101
10N0001
1111111
```

## Technical Notes

- Doors use a single texture and slide open with smooth time-based animation.
- Transparent door region while opening is handled by continuing the DDA past the hit door and sampling the next wall behind it (no re-casting from scratch each pixel).
- Floor is color-only in mandatory; the bonus build may include additional visuals.

## Project Structure (high level)

```
srcs/
  doors_bonus.c
  doors_anim_bonus.c
  doors_anim_utils_bonus.c
  doors_stubs.c            # mandatory-only stubs
  raycasting.c
  ray_utils.c
  ray_helpers.c
  ray_helpers_bg.c         # background sampling helpers
  ray_tex_helpers.c        # texture helpers
  ... (parsing, validation, movement, rendering)
includes/
  cub3d.h
```

## Style & Tools

- Norminette-compliant (≤ 25 lines/function, ≤ 5 functions/file, tabs, ≤ 80 cols, no ternary, etc.).
- Libraries: libft, get_next_line, MiniLibX, math, gettimeofday.

## Cleaning & Rebuilding

```bash
make fclean && make        # mandatory
make fclean && make bonus  # bonus
```

## Notes

- The bonus build excludes mandatory stubs to avoid multiple definitions.
- If a door shows as a wall in mandatory, build with `make bonus` to enable door animation. 