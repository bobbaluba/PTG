/**
 * @file TerrainMesh.h
 * @date 2. nov. 2012
 * @author Johan Klokkhammer Helsing
 */

#ifndef TERRAINMESH_H_
#define TERRAINMESH_H_

#include <helsing/Drawable.hpp>

#include <helsing/Shader.hpp>
#include <helsing/HeightMap.hpp>
#include <helsing/math/Vec4.hpp> //TODO

class TerrainMesh: public helsing::Drawable {
public:
	explicit TerrainMesh(const helsing::HeightMap&);
	virtual ~TerrainMesh();
	virtual void draw(const helsing::Mat4& modelViewMatrix, const helsing::Mat4& projectionMatrix);
private:
	struct TerrainVertex{
		helsing::Vec4 position;
		helsing::Vec4 normal;
	};
	static TerrainVertex getVertex(int x, int z, const helsing::HeightMap&);
	unsigned int vaoId;
	unsigned int vboId;
	unsigned int numberOfVertices;
	helsing::Shader* shader;

    // Disable value copying
    TerrainMesh(const TerrainMesh& uncopyable);
    TerrainMesh& operator=(const TerrainMesh& uncopyable);
};

#endif // TERRAINMESH_HPP
