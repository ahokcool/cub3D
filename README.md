<!-- ahokcool HEADER START-->
---
<a id="top"></a>
<div align="center">
  <a href="https://github.com/ahokcool/ahokcool/blob/main/README.md">
    <img src="images/alexgit.png" alt="Logo" width="150">
  </a><br>
An overview of all my projects can be found here: <a href="https://github.com/ahokcool/ahokcool/blob/main/README.md" target="_blank">ahokcool</a><br><br>
  <a href="https://www.42lisboa.com">
    <img src="images/logo42.svg" alt="Logo" width="100">
  </a><br>
  This project was created as part of my studies at: <a href="https://www.42lisboa.com" target="_blank">42 Lisboa</a><br>
  This project is a group project with 
	<a href="https://github.com/AshParker19" target="_blank">ashParker19</a>,
	<a href="https://github.com/joaodibba" target="_blank">joaodibba</a> &
	<a href="https://github.com/rajh-phuyal" target="_blank">rajh-phuyal</a><br
</div>

---
<!-- ahokcool HEADER END-->
<!-- PROJECT HEADER START -->
<br />
<div align="center">
  <a href="./">
    <img src="images/logo.gif" alt="Logo" width="600">
  </a>
  <h1 align="center">cub3D</h1>
<p align="center">
    createing a 3D game in C using raycasting
</p>
</div>
<br>
<!-- PROJECT HEADER END -->

## :bulb: Lessons learned
- working with the API of [a graphics library](https://github.com/42Paris/minilibx-linux)
- understanding points in 2 and 3 dimensional space, vectors and trigonometric functions
- [Bresenham's line algorithm](https://en.wikipedia.org/wiki/Bresenham%27s_line_algorithm)
- Using a [rotation matrix](https://en.wikipedia.org/wiki/Rotation_matrix) to transform coordinates

## Installation
```
$ git clone --recurse-submodules https://github.com/ahokcool/fdf.git    # Clone
$ cd fdf                                                                # Change directory
$ make                                                                  # Compile
$ ./fdf map_file                                                        # Run
```




# cub3d

## Instal

```
git clone --recurse-submodules git@github.com:ahokcool/cub3d.git
```

MAIN PROJECT FLOW
	
**controller**
	updates the booleans in t_controller to represent which key are pressed atm
	
**model**
	(the main model function will be hook with the mlx loop)
	checks the booleans in t_controller to know if the model needs to be updated
	tries move / rotate the player
		-> collision checking
	raycasting needs to calculate the new hits/distances to the walls
		-> uses DDA (maybe a function)
		
*view*
	(modify img buffer) take the info about the hits/distance and drawing the column-lines onto the mlximg
	(modify img buffer) draws the tiles of 2dmap (if should be shown)
	(modify img buffer) draws the tiles of minimap (if should be shown)
	flushes the images to the window
	
<!-- ahokcool FOOTER-->
---
<p align="center">
  <a href="#top">🔝 back to top 🔝</a>
</p>
