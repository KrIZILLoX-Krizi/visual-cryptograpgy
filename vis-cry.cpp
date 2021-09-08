//=========================================================

#include <iostream>
#include <string>
#include "bitmap-master/bitmap_image.hpp"

//=========================================================

using namespace std;

//=========================================================

int main(void)
{

//=========================================================

									// LOADING THE IMAGE

//=========================================================

	string path;

	cout << "Enter path to image: ";
	cin >> path;

	bitmap_image image (path);

	if (!image) {
		cout << "Image couldn't be loaded. Try again." << endl;
		return -1;
	} else {
		cout << "Image loaded successfully!" << endl;
	}

//=========================================================

					// SAVING THE DIMENSIONS OF THE IMAGE

//=========================================================

	const unsigned int img_height = image.height ();
	const unsigned int img_width = image.width ();

//=========================================================

	cout << "Dimensions of the image: " << img_height 
		<< "x" << img_width << endl;

//=========================================================

  		// CREATING TWO IMAGES FOR TRANSPARENCY IMAGES
				// TWICE THE ORIGINAL HEIGHT AND WIDTH

//=========================================================

	bitmap_image share1 (2 * img_height, 2 * img_width);
	share1.set_all_channels (255, 255, 255);
	bitmap_image share2 (2 * img_height, 2 * img_width);
	share2.set_all_channels (255, 255, 255);

	image_drawer draw1 (share1);
	draw1.pen_width (1);
  draw1.pen_color (0, 0, 0);
  image_drawer draw2 (share2);
  draw2.pen_width (1);
  draw2.pen_color (0, 0, 0);
	

//=========================================================

	  									// ENCRYPTION

//=========================================================

  // setting up the color channel
  rgb_t color_channel;
  int chance;

  // for each pixel in column (original image)
	for (int i = 0; i < img_height; ++i) {

		// for each pixel in row (original image)
		for (int j = 0; j < img_width; ++j) {

			// get the pixel information from the image
			image.get_pixel (i, j, color_channel);
			// generating random combination
			chance = rand () * rand () % 6;

			// if black pixel
			if (color_channel.red == 0 && color_channel.blue == 0 && color_channel.green == 0) {

				switch (chance) {
					case 0:
						draw1.plot_pixel (2 * i, 2 * j);
						draw1.plot_pixel (2 * i + 1, 2 * j + 1);
						draw2.plot_pixel (2 * i, 2 * j + 1);
						draw2.plot_pixel (2 * i + 1, 2 * j);
					break;
					case 1:
						draw1.plot_pixel (2 * i, 2 * j);
						draw1.plot_pixel (2 * i, 2 * j + 1);
						draw2.plot_pixel (2 * i + 1, 2 * j);
						draw2.plot_pixel (2 * i + 1, 2 * j + 1);
					break;
					case 2:
						draw1.plot_pixel (2 * i + 1, 2 * j);
						draw1.plot_pixel (2 * i + 1, 2 * j + 1);
						draw2.plot_pixel (2 * i, 2 * j);
						draw2.plot_pixel (2 * i, 2 * j + 1);
					break;
					case 3:
						draw1.plot_pixel (2 * i, 2 * j);
						draw1.plot_pixel (2 * i + 1, 2 * j);
						draw2.plot_pixel (2 * i, 2 * j + 1);
						draw2.plot_pixel (2 * i + 1, 2 * j + 1);
					break;
					case 4:
						draw1.plot_pixel (2 * i, 2 * j + 1);
						draw1.plot_pixel (2 * i + 1, 2 * j + 1);
						draw2.plot_pixel (2 * i, 2 * j);
						draw2.plot_pixel (2 * i + 1, 2 * j);
					break;
					case 5:
						draw1.plot_pixel (2 * i, 2 * j + 1);
						draw1.plot_pixel (2 * i + 1, 2 * j);
						draw2.plot_pixel (2 * i, 2 * j);
						draw2.plot_pixel (2 * i + 1, 2 * j + 1);
					break;
				}
			}
			// if white pixel
			else {
			  switch (chance) {
					case 0:
						draw1.plot_pixel (2 * i, 2 * j);
						draw1.plot_pixel (2 * i + 1, 2 * j + 1);
						draw2.plot_pixel (2 * i, 2 * j);
						draw2.plot_pixel (2 * i + 1, 2 * j + 1);
					break;
					case 1:
						draw1.plot_pixel (2 * i, 2 * j);
						draw1.plot_pixel (2 * i, 2 * j + 1);
						draw2.plot_pixel (2 * i, 2 * j);
						draw2.plot_pixel (2 * i, 2 * j + 1);
					break;
					case 2:
						draw1.plot_pixel (2 * i + 1, 2 * j);
						draw1.plot_pixel (2 * i + 1, 2 * j + 1);
						draw2.plot_pixel (2 * i + 1, 2 * j);
						draw2.plot_pixel (2 * i + 1, 2 * j + 1);
					break;
					case 3:
						draw1.plot_pixel (2 * i, 2 * j);
						draw1.plot_pixel (2 * i + 1, 2 * j);
						draw2.plot_pixel (2 * i, 2 * j);
						draw2.plot_pixel (2 * i + 1, 2 * j);
					break;
					case 4:
						draw1.plot_pixel (2 * i, 2 * j + 1);
						draw1.plot_pixel (2 * i + 1, 2 * j + 1);
						draw2.plot_pixel (2 * i, 2 * j + 1);
						draw2.plot_pixel (2 * i + 1, 2 * j + 1);
					break;
					case 5:
						draw1.plot_pixel (2 * i, 2 * j + 1);
						draw1.plot_pixel (2 * i + 1, 2 * j);
						draw2.plot_pixel (2 * i, 2 * j + 1);
						draw2.plot_pixel (2 * i + 1, 2 * j);
					break;
				}
			}
		}
	}

	cout << "Image encrypted successfully!" << endl;

//=========================================================

									// SAVING THE SHARES

//=========================================================

	share1.save_image ("share1.bmp");
	share2.save_image ("share2.bmp");

	cout << "Shares saved successfully!" << endl;

//=========================================================

											// DECRYPTION

//=========================================================

const unsigned int share_height = share1.height ();
const unsigned int share_width = share1.width ();

cout << "Dimensions of the shares: " << share_height << "x" << share_width << endl;

// loading the shares

bitmap_image image1 ("share1.bmp");
bitmap_image image2 ("share2.bmp");

bitmap_image decrypted (share_height, share_width);
decrypted.set_all_channels (255, 255, 255);

image_drawer draw_decry (decrypted);
draw_decry.pen_width (1);
draw_decry.pen_color (0, 0, 0);

rgb_t color_channel2;

for (int i = 0; i < share_height; ++i) {
	for (int j = 0; j < share_width; ++j) {
		
		share1.get_pixel (i, j, color_channel);
		share2.get_pixel (i, j, color_channel2);
		
		if (color_channel.red != color_channel2.red) {
			draw_decry.plot_pixel (i, j);
		}
	}
}

decrypted.save_image ("decrypted.bmp");


//=========================================================

	return 0;
}

