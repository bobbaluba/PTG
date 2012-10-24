#include "Renderer.h"
#include <SFML/OpenGL.hpp>

#include "helsing/hmath.h"

using namespace helsing;

namespace helsing {

HeightMap::HeightMap(uint32_t size):size(size){
	heights.resize(size*size);
	//TODO switch to memset
	for(uint32_t i=0; i<size*size; i++){
		this->heights[i]=0;
	}
}

HeightMap::HeightMap(const float heights[], const uint32_t size):size(size){
	this->heights.assign(heights, heights + size*size); //not tested
}

HeightMap::~HeightMap(){
}

const Vec4 HeightMap::getPoint(uint32_t x, uint32_t z) const {
	return Vec4(x,getHeight(x,z), z);
}

const Vec4 HeightMap::getNormal(int x, int z) const {
	const Vec4 center = getPoint(x,z);
	Vec4 normal = Vec4::zero();

	if(x+1 < static_cast<int>(size)){
		if(z+1 < static_cast<int>(size)){
			const Vec4 a = getPoint(x, z+1)-center;
			const Vec4 b = getPoint(x+1, z)-center;
			normal += a.normalize()^b.normalize();
		}
		if(z-1 >= 0){
			const Vec4 a = getPoint(x+1, z) - center;
			const Vec4 b = getPoint(x, z-1) - center;
			normal += a.normalize()^b.normalize();
		}
	}
	if(x-1 >= 0){
		if(z+1 < static_cast<int>(size)){
			const Vec4 a = getPoint(x-1, z);
			const Vec4 b = getPoint(x, z+1);
			normal += ((a-center)^(b-center)).normalize();
		}
		if(z-1 >= 0){
			const Vec4 a = getPoint(x, z-1);
			const Vec4 b = getPoint(x-1, z);
			normal += ((a-center)^(b-center)).normalize();
		}
	}
	normal = normal.normalize();
	return normal;
}

void HeightMap::flatten() {
	for(uint32_t i=0; i<size*size; i++){
		this->heights[i]=0;
	}
}

}


