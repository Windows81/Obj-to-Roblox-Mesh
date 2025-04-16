#include <iostream>

#include "RobloxMesh.h"
#include "OBJ_Loader.h"

int main(int argc, char* argv[])
{
	if (argc == 1) {
		std::cout << "Usage: " << argv[0] << " file... [1.00 | 1.01 | 2.00]";
		return EXIT_FAILURE;
	}

	std::string ver = argv[argc - 1];
	if (ver.compare("1.00") && ver.compare("1.01") && ver.compare("2.00") != 0) {
		std::cout << "ERROR: Invaild version specified!\nMake sure the version specified is 1.00, 1.01 or 2.00";
		return EXIT_FAILURE;
	}

	for (int i = 1; i < argc - 1; ++i)
	{
		std::string arg = argv[i];

		objl::Loader obj;
		if (!obj.LoadFile(arg))
		{
			std::cout << "ERROR: Could not load \"" << arg << "\"!";
			return EXIT_FAILURE;
		}

		RobloxMesh rbxMesh;

		for (auto& objVertex : obj.LoadedVertices)
		{
			RobloxMesh::Vertex meshVertex;

			meshVertex.vx = objVertex.Position.X;
			meshVertex.vy = objVertex.Position.Y;
			meshVertex.vz = objVertex.Position.Z;

			meshVertex.nx = objVertex.Normal.X;
			meshVertex.ny = objVertex.Normal.Y;
			meshVertex.nz = objVertex.Normal.Z;

			meshVertex.tu = objVertex.TextureCoordinate.X;
			float v = (ver == "2.00") ? (1.0 - objVertex.TextureCoordinate.Y) : objVertex.TextureCoordinate.Y;
			meshVertex.tv = v;

			rbxMesh.vertices.push_back(meshVertex);
		}

		for (size_t i = 0; i < obj.LoadedIndices.size(); i += 3)
		{
			RobloxMesh::Face meshFace;

			meshFace.a = obj.LoadedIndices[i];
			meshFace.b = obj.LoadedIndices[i + 1];
			meshFace.c = obj.LoadedIndices[i + 2];

			rbxMesh.faces.push_back(meshFace);
		}

		std::ofstream output(arg + ".mesh", std::ios::binary);
		rbxMesh.Write(output, ver);
		output.close();
	}
}
