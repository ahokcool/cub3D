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
	
