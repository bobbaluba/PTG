/**
 * @file TerrainMesh.h
 * @date 2. nov. 2012
 * @author Johan Klokkhammer Helsing
 */

#ifndef TERRAINMESH_H_
#define TERRAINMESH_H_

#include <helsing/Drawable.hpp>

#include <helsing/HeightMap.hpp>
#include <helsing/math/Vec4.hpp>

class TerrainMesh: public helsing::Drawable {
public:
	explicit TerrainMesh(const helsing::HeightMap&);
	virtual ~TerrainMesh();
	virtual void draw();
private:
	struct TerrainVertex{
		helsing::Vec4 position;
		helsing::Vec4 normal;
	};
	unsigned int vaoId;
	unsigned int vboId;
};

#endif // TERRAINMESH_HPP
