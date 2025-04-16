#include "RobloxMesh.h"

void RobloxMesh::Write(std::ostream& stream, std::string ver)
{
	if (ver == "1.00" || ver == "1.01")
	{
		int scale = (ver == "1.00") ? 2 : 1;

		stream << "version " << ver << "\r\n";
		stream << faces.size() << "\r\n";

		for (Face face : faces)
		{
			for (uint32_t i : {face.a, face.b, face.c})
			{
				Vertex vert = vertices[i];

				stream << "[";
				stream << vert.vx * scale << ",";
				stream << vert.vy * scale << ",";
				stream << vert.vz * scale << "]";

				stream << "[";
				stream << vert.nx << ",";
				stream << vert.ny << ",";
				stream << vert.nz << "]";

				stream << "[";
				stream << vert.tu << ",";
				stream << (1.0 - vert.tv) << ",";
				stream << "0]";
			}
		}
	}
	else if (ver == "2.00")
	{
		struct
		{
			uint16_t headerSize;
			uint8_t vertexSize;
			uint8_t faceSize;
			uint32_t vertexCount;
			uint32_t faceCount;
		} header;

		header.headerSize = sizeof(header);
		header.vertexSize = sizeof(Vertex);
		header.faceSize = sizeof(Face);
		header.vertexCount = vertices.size();
		header.faceCount = faces.size();

		stream << "version " << ver << "\r\n";
		stream.write((char*)&header, sizeof(header));
		stream.write((char*)vertices.data(), vertices.size() * sizeof(Vertex));
		stream.write((char*)faces.data(), faces.size() * sizeof(Face));
	}
}
