
#include "block.h"

void build(PNG & im, int column, int width){

	data.resize(width);
	
	for(unsigned int x = column; x < column + width; x++){
		data[x].resize(im.height());
		
		for(unsigned int y = 0; y < im.height(); y++){
			data[x][y] = im.getPixel(x,y);
		}
	}
}

void render(PNG & im, int column) const{

	for(unsigned x = column; x < column + data.size(); x++){
		for(unsigned y = 0; y < data[x].size(); y++){
			data[x][y] = im.getPixel(x,y);
			//To do
		}
	}
}

void greyscale(){

	for(unsigned x = 0; x < data.size(); x++){
		for(unsigned y = 0; y < data[x].size(); y++){
			data[x][y]->s = 0;
		}
	}
}

int width() const{
	return data.size();
}

int height() const{
	return data[0].size();
}