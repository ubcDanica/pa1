#include <stdlib.h>
#include "block.h"

void Block::build(PNG & im, int column, int width){

	data.resize(width);
	
	for(int x = column; x < column + width; x++){
		data[x-column].resize(im.height());
		
		for(int y = 0; y < (int)im.height(); y++){
			data[x-column][y] = * im.getPixel(x,y);
		}
	}
}

void Block::render(PNG & im, int column) const{

	for(int x = column; x < (int)data.size() + column; x++){

		for(int y = 0; y < (int)im.height(); y++){

			HSLAPixel* pixel = im.getPixel(x,y);
			*pixel = data[x-column][y];
			//To do
		}
	}
}

void Block::greyscale(){

	for(int x = 0; x < (int)data.size(); x++){
		for(int y = 0; y < (int)data[x].size(); y++){
			data[x][y].s = 0;
		}
	}
}

int Block::width() const{
	return (int)data.size();
}

int Block::height() const{
	return (int)data[0].size();

/*bool Block::isEmpty() const{
	if(width()==0 || height()==0){
		return true;
	}
	else return false;
}*/

}
