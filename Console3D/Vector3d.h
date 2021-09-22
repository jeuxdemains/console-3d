#pragma once
#include <vector>
#include <string>
#include <fstream>
#include <strstream>

class Vector3d
{
public:
	struct Vector3
	{
		float x = 0.0f, y = 0.0f, z = 0.0f;
	};

	struct Triangle
	{
		Vector3 a, b, c;
		uint8_t red = 255, green = 20, blue = 0;
	};

	struct Mesh
	{
		std::vector<Triangle> triangles;

		bool LoadFromObjFile(std::string fName)
		{
			std::ifstream f(fName);
			if (!f.is_open())
				return false;

			std::vector<Vector3> verts;
			while (!f.eof())
			{
				char line[128];
				f.getline(line, 128);

				std::strstream s;
				s << line;

				char junk;
				if (line[0] == 'v')
				{
					Vector3 vec;
					s >> junk >> vec.x >> vec.y >> vec.z;
					verts.push_back(vec);
				}

				if (line[0] == 'f')
				{
					int f[3];
					s >> junk >> f[0] >> f[1] >> f[2];
					triangles.push_back({ verts[f[0] - 1], verts[f[1] - 1], verts[f[2] - 1] });
				}
			}
			return true;
		}
	};

	Vector3 Cross(const Vector3& v1, const Vector3& v2) const
	{
		Vector3 cross;

		cross.x = v1.y * v2.z - v1.z * v2.y;
		cross.y = v1.z * v2.x - v1.x * v2.z;
		cross.z = v1.x * v2.y - v1.y * v2.x;

		return cross;
	}


	float Dot(const Vector3& v1, const Vector3& v2) const
	{
		return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
	}

	Vector3 Normalize(const Vector3& v1)
	{
		Vector3 normalized;
		float ln = sqrtf(v1.x * v1.x + v1.y * v1.y + v1.z * v1.z);
		normalized.x = v1.x / ln;
		normalized.y = v1.y / ln;
		normalized.z = v1.z / ln;

		return normalized;
	}

	bool IsZeroVec(const Vector3& v1)
	{
		if (v1.x == 0.0f && v1.y == 0.0f && v1.z == 0.0f)
			return true;

		return false;
	}
};

