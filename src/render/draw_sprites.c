/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_sprites.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aroux <aroux@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 14:57:53 by aroux             #+#    #+#             */
/*   Updated: 2025/05/16 14:16:29 by aroux            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_sprites(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->sprite_count)
	{
		render_each_sprite(data, &data->sprites[i]);
		i++;
	}
}

void	render_each_sprite(t_data *data, t_sprite *sprite)
{
	const double	FOV_SCALE = 0.66;  // Adjust based on your FOV (0.66 for ~66°)

	double	sprite_x = sprite->x - data->player.x;
	double	sprite_y = sprite->y - data->player.y;

	// Player direction vector
	double	dir_x = cos(data->player.angle);
	double	dir_y = sin(data->player.angle);

	// Camera plane vector (perpendicular to direction)
	double	plane_x = -dir_y * FOV_SCALE;
	double	plane_y = dir_x * FOV_SCALE;

	// Inverse determinant for camera matrix
	double	inv_det = 1.0 / (plane_x * dir_y - dir_x * plane_y);

	// Transform sprite position into camera space
	double	transform_x = inv_det * (dir_y * sprite_x - dir_x * sprite_y);
	double	transform_y = inv_det * (-plane_y * sprite_x + plane_x * sprite_y);

	// Skip if sprite is behind the player
	if (transform_y <= 0)
		return;

	// Sprite screen x-position
	int	sprite_screen_x = (int)((WIDTH / 2) * (1 + transform_x / transform_y));

	// Height and width of the sprite on screen
	int	sprite_height = abs((int)(HEIGHT / transform_y));
	int	sprite_width = sprite_height;

	// Vertical draw range
	int	start_y = -sprite_height / 2 + HEIGHT / 2;
	int	end_y = sprite_height / 2 + HEIGHT / 2;
	start_y = (start_y < 0) ? 0 : start_y;
	end_y = (end_y >= HEIGHT) ? HEIGHT - 1 : end_y;

	// Horizontal draw range
	int	start_x = -sprite_width / 2 + sprite_screen_x;
	int	end_x = sprite_width / 2 + sprite_screen_x;
	start_x = (start_x < 0) ? 0 : start_x;
	end_x = (end_x >= WIDTH) ? WIDTH - 1 : end_x;

	// Texture reference
	t_img	tex = data->textures[sprite->texture_id];

	// Draw the sprite column by column
	for (int stripe = start_x; stripe < end_x; stripe++)
	{
		int tex_x = (int)(256 * (stripe - (-sprite_width / 2 + sprite_screen_x)) * TEXT_WIDTH / sprite_width) / 256;

		// Z-buffer check: skip if behind wall
		if (transform_y > 0 && stripe >= 0 && stripe < WIDTH && transform_y < data->z_buffer[stripe])
		{
			for (int y = start_y; y < end_y; y++)
			{
				int d = (y) * 256 - HEIGHT * 128 + sprite_height * 128;
				int tex_y = ((d * TEXT_HEIGHT) / sprite_height) / 256;

				int color = *(unsigned int *)(tex.addr + (tex_y * tex.line_len + tex_x * (tex.bpp / 8)));
	
				if (y == start_y && stripe == start_x)
					printf("First pixel color: %#010x\n", color);
				// Skip transparent pixels (e.g., magenta)
				//if ((color & 0x00FFFFFF) != 0xff000000)
				//if ((unsigned int)color != 0xFFFF00FF)
				//if ((color >> 24) != 0x00)
				unsigned int alpha = (color >> 24) & 0xFF;
				if (alpha == 0)
    				put_pixel_to_image(data, stripe, y, color);
			}
		}
	}
}

/* Command to convert the .png images to .xpm while dealing with transparency:
convert input.png -resize 64x64 -background none -define xpm:alpha=on output.xpm
 */

/*	project each sprite into the camera space
	calculate how big it should be based on its distance
	draw it if its in front of the player dans not hidden by a wall	*/
/* void	render_each_sprite(t_data *data, t_sprite *sprite)
{
	double	sprite_relx;
	double	sprite_rely;
	double	inv_det;
	double	transform_x; // where the sprite is horizontally on the screen
	double	transform_y; // how far the sprite is from the player

	int	sprite_screen_x; // zhere the center of the sprite should appear on screen
	int	sprite_height;

	int	start_y;
	int	end_y;

	int	sprite_width;
	int	start_x;
	int	end_x;

	
	int	stripe;
	int	tex_x;

	t_img	tex;


	// we translate the world so the player is at the origin
	sprite_relx = sprite->x - data->player.x; //relative postion to the player
	sprite_rely = sprite->y - data->player.y;
	// calculate the inverse of the camera transformation matrix’s determinant,
	// which we’ll use to project world coordinates into camera space; It’s based 
	// on rotating the world so the camera (player) is always looking "forward" 
	// (down the x-axis in camera space).
	inv_det = 1.0 / (cos(data->player.angle) * sin(data->player.angle + PI / 2) \
	- sin(data->player.angle) * cos(data->player.angle + PI / 2));
	
	transform_x = inv_det * sin(data->player.angle + PI / 2) * sprite_relx - cos(data->player.angle + PI / 2) * sprite_rely;
	transform_y = inv_det * -sin(data->player.angle) * sprite_relx - cos(data->player.angle) * sprite_rely;

	//if (transform_y <= 0)
	//	return ;

	sprite_screen_x = (int)((WIDTH / 2) * (1 + transform_x / transform_y));
	
	sprite_height = abs((int)(HEIGHT / transform_y));
	start_y = -sprite_height / 2 + HEIGHT / 2;
	end_y = sprite_height / 2 + HEIGHT / 2;
	if (start_y < 0)
		start_y = 0;
	if (end_y >= HEIGHT)
		end_y = HEIGHT - 1;

	sprite_width = abs((int)(HEIGHT / transform_y));
	start_x = -sprite_width / 2 + sprite_screen_x;
	end_x = sprite_width / 2 + sprite_screen_x;
	if (start_x < 0)
		start_x = 0;
	if (end_x >= WIDTH)
		end_x = WIDTH - 1;

	tex = data->textures[sprite->texture_id];

	stripe = start_x;
	while (stripe < end_x)
	{
		tex_x = (int)(256 * (stripe - (-sprite_width / 2 + sprite_screen_x)) * TEXT_WIDTH / sprite_width) / 256;
		// skip if the stripe is behind a wall
		if (transform_y > 0  && stripe >= 0 && stripe < WIDTH && transform_y < data->z_buffer[stripe])
		{
			for (int y = start_y; y < end_y; y++)
			{
				int d = (y) * 256 - HEIGHT * 128 + sprite_height * 128;
				int tex_y = ((d * TEXT_HEIGHT) / sprite_height) / 256;

				// Grab color from texture
				int color = *(unsigned int *)(tex.addr + (tex_y * tex.line_len + tex_x * (tex.bpp / 8)));

				// Simple transparency check (e.g., magenta = transparent)
				if ((color & 0xFF000000) != 0xFF000000)
					put_pixel_to_image(data, stripe, y, color);
			}
		}
		stripe++;
	}
} */
/* void	render_single_sprite(t_data *data, t_sprite *sprite)
{
	double spriteX = sprite->x - data->player.x;
	double spriteY = sprite->y - data->player.y;

	// Inverse camera matrix
	double invDet = 1.0 / (data->plane.x * data->dir.y - data->dir.x * data->plane.y);

	// Transform to camera space
	double transformX = invDet * (data->dir.y * spriteX - data->dir.x * spriteY);
	double transformY = invDet * (-data->plane.y * spriteX + data->plane.x * spriteY);

	// Projected screen x
	int spriteScreenX = (int)((data->screenWidth / 2) * (1 + transformX / transformY));

	// Height and width (scaled with distance)
	int spriteHeight = abs((int)(data->screenHeight / transformY));
	int spriteWidth = spriteHeight;

	int drawStartY = -spriteHeight / 2 + data->screenHeight / 2;
	int drawEndY = spriteHeight / 2 + data->screenHeight / 2;

	int drawStartX = -spriteWidth / 2 + spriteScreenX;
	int drawEndX = spriteWidth / 2 + spriteScreenX;

	// Clip to screen bounds
	if (drawStartY < 0) drawStartY = 0;
	if (drawEndY >= data->screenHeight) drawEndY = data->screenHeight - 1;
	if (drawStartX < 0) drawStartX = 0;
	if (drawEndX >= data->screenWidth) drawEndX = data->screenWidth - 1;

	draw_sprite_texture(data, sprite, drawStartX, drawEndX, drawStartY, drawEndY, spriteWidth, spriteHeight, spriteScreenX, transformY);
} 
	
void	draw_sprite_texture(t_data *data, t_sprite *sprite, int startX, int endX, int startY, int endY, int width, int height, int screenX, double depth)
{
	t_texture *tex = &data->textures[sprite->texture_id];

	for (int stripe = startX; stripe < endX; stripe++)
	{
		int texX = (int)(256 * (stripe - (-width / 2 + screenX)) * tex->width / width) / 256;

		if (depth > 0 && stripe >= 0 && stripe < data->screenWidth && depth < data->zbuffer[stripe])
		{
			for (int y = startY; y < endY; y++)
			{
				int d = (y) * 256 - data->screenHeight * 128 + height * 128;
				int texY = ((d * tex->height) / height) / 256;
				int color = tex->pixels[texY * tex->width + texX];

				// Skip transparent pixels
				if ((color & 0x00FFFFFF) != 0x00FF00FF)
					draw_pixel(data, stripe, y, color);
			}
		}
	}
}
*/