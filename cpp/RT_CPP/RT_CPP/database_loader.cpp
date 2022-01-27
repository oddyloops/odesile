#include "database_loader.h"
#include "orthographic.h"
#include "perspective.h"
#include "io/EasyBMP.h"
#include <fstream>
#include <iostream>
#include <algorithm>

using namespace utility::io;

vector<string> split(string s, string delimiter) {
	size_t pos_start = 0, pos_end, delim_len = delimiter.length();
	string token;
	vector<string> res;

	while ((pos_end = s.find(delimiter, pos_start)) != string::npos) {
		token = s.substr(pos_start, pos_end - pos_start);
		pos_start = pos_end + delim_len;
		res.push_back(token);
	}

	res.push_back(s.substr(pos_start));
	return res;
}

material_types database_loader::int_to_enum(int type)
{
	return static_cast<material_types>(type);
}

vector<texture*> database_loader::load_textures(json const& j)
{
	vector<texture*> textures;
	for (json jt : j)
	{
		textures.push_back(load_texture(jt));
	}
	return textures;
}

texture* database_loader::load_texture(string file)
{
	string folder = "scene_files/textures/";
	string full_path = folder + file;
	BMP input;
	input.ReadFromFile(full_path.c_str());
	vector3** pixels = new vector3 * [input.TellHeight()];
	for (int y = 0; y < input.TellHeight(); y++)
	{
		pixels[y] = new vector3[input.TellWidth()];
		for (int x = 0; x < input.TellWidth(); x++)
		{
			pixels[y][x] = { input(x,y)->Red / 255.0f, input(x,y)->Green / 255.0f , input(x,y)->Blue / 255.0f };
		}
	}
	texture* tex = new texture(pixels, input.TellWidth(), input.TellHeight());
	return tex;
}

vector<vector3> database_loader::parse_vector3_array(json const& j)
{
	vector<vector3> vec;
	for (json jv : j)
	{
		vec.push_back(parse_vector3(jv));
	}
	return vec;
}


vector<float> database_loader::parse_float_array(json const& j)
{
	vector<float> vec;
	for (json jv : j)
	{
		vec.push_back(jv);
	}
	return vec;
}

scene_database* database_loader::load(string file)
{
	ifstream in(file.c_str());
	json j;
	in >> j;
	json temp = j["Scene"];
	scene* scn = load_scene(temp);
	temp = j["Camera"];
	camera* cam = load_camera(temp,scn->get_width(),scn->get_height());
	vector<shape*>* shapes = load_shapes(j["Shapes"]);
	vector<material*>* materials = load_materials(j["Materials"]);
	vector<light*>* lights = load_lights(j["Lights"]);
	scene_database* db = new scene_database();
	db->set_camera(cam);
	db->set_scene(scn);
	db->set_shapes(shapes);
	db->set_materials(materials);
	db->set_lights(lights);
	return db;

}

vector3 database_loader::parse_vector3(string vectorStr)
{
	vector<string> vecStr = split(vectorStr, ",");
	vector3 v;
	v.x = atof(vecStr[0].c_str());
	v.y = atof(vecStr[1].c_str());
	v.z = atof(vecStr[2].c_str());
	return v;
}


scene* database_loader::load_scene(json const& j)
{
	scene* s = new scene;
	s->set_height(j["height"]);
	s->set_width(j["width"]);
	s->set_background(parse_vector3(j["background"]));
	s->set_ambient_light(parse_vector3(j["ambientLight"]));
	return s;
}

camera* database_loader::load_camera(json const& j, int width, int height)
{
	bool isOrtho = j["isOrthographic"];

	camera* cam;
	if (isOrtho)
	{
		cam = new orthographic(
			j["farPlane"],
			j["focalLength"],
			j["fieldOfView"],
			parse_vector3(j["upDirection"]),
			parse_vector3(j["target"]),
			parse_vector3(j["position"]),
			width,
			height
		);
	}
	else
	{
		cam = new perspective(
			j["farPlane"],
			j["focalLength"],
			j["fieldOfView"],
			parse_vector3(j["upDirection"]),
			parse_vector3(j["target"]),
			parse_vector3(j["position"]),
			width,
			height
		);
	}

	return cam;
}


vector<shape*>* database_loader::load_shapes(json const& j)
{
	vector<shape*>* shapes = new vector <shape*>;
	json temp = j["Spheres"];
	vector<sphere*>* spheres = load_spheres(temp);
	temp = j["Rectangles"];
	vector<rectangle*>* rectangles = load_rectangles(temp);
	temp = j["Triangles"];
	vector<triangle*>* triangles = load_triangles(temp);
	copy(spheres->begin(), spheres->end(), back_inserter(*shapes));
	copy(rectangles->begin(), rectangles->end(), back_inserter(*shapes));
	copy(triangles->begin(), triangles->end(), back_inserter(*shapes));
	delete spheres;
	delete rectangles;
	delete triangles;
	return shapes;

}


vector<sphere*>* database_loader::load_spheres(json const& j)
{
	vector<sphere*>* spheres = new vector<sphere*>;
	for (json sphJson : j)
	{
		spheres->push_back(load_sphere(sphJson));
	}
	return spheres;
}


sphere* database_loader::load_sphere(json const& j)
{
	sphere* sph = new sphere(j["id"], j["materialId"],
		parse_vector3(j["center"]),
		j["radius"]);
	return sph;
}


vector<rectangle*>* database_loader::load_rectangles(json const& j)
{
	vector<rectangle*>* rectangles = new vector<rectangle*>;
	for (json recJson : j)
	{
		rectangles->push_back(load_rectangle(recJson));
	}
	return rectangles;
}



rectangle* database_loader::load_rectangle(json const& j)
{
	rectangle* rec = new rectangle(j["id"], j["materialId"], parse_vector3( j["vertexA"]),parse_vector3(j["vertexB"]),
		parse_vector3(j["vertexC"]), parse_vector3(j["vertexD"]));
	return rec;
}


vector<triangle*>* database_loader::load_triangles(json const& j)
{
	vector<triangle*>* triangles = new vector<triangle*>;
	for (json triJson : j)
	{
		triangles->push_back(load_triangle(triJson));
	}
	return triangles;
}

triangle* database_loader::load_triangle(json const& j)
{
	triangle* tri = new triangle(j["id"], j["materialId"], parse_vector3(j["vertexA"]), parse_vector3(j["vertexB"]),
		parse_vector3(j["vertexC"]));
	return tri;
}


vector<material*>* database_loader::load_materials(json const& j)
{
	vector<material*>* mats = new vector<material*>;
	vector<color_material*>* color_mats = load_color_materials(j["ColorMaterials"]);
	copy(color_mats->begin(), color_mats->end(), back_inserter(*mats));
	delete color_mats;
	vector<texture_material*>* texture_mats = load_texture_materials(j["TextureMaterials"]);
	copy(texture_mats->begin(), texture_mats->end(), back_inserter(*mats));
	delete texture_mats;
	return mats;
}



color_material* database_loader::load_color_material(json const& j)
{
	color_material* mat = new color_material(j["id"], int_to_enum(j["type"]),
		parse_vector3_array(j["ambientColors"]), parse_vector3_array(j["diffuseColors"]),
		parse_vector3_array(j["specularColors"]), parse_float_array(j["specularities"]),
		parse_float_array(j["reflectivities"]), parse_float_array(j["transparencies"]),
		parse_float_array(j["refractiveIndices"]));
	return mat;
}


vector<texture_material*>* database_loader::load_texture_materials(json const& j)
{
	vector<texture_material*>* cms = new vector<texture_material*>;
	for (json cm : j)
	{
		cms->push_back(load_texture_material(cm));
	}
	return cms;
}

texture_material* database_loader::load_texture_material(json const& j)
{
	texture_material* mat = new texture_material(j["id"], int_to_enum(j["type"]),
		parse_vector3_array(j["ambientColors"]), load_textures(j["diffuseColors"]),
		parse_vector3_array(j["specularColors"]), parse_float_array(j["specularities"]),
		parse_float_array(j["reflectivities"]), parse_float_array(j["transparencies"]),
		parse_float_array(j["refractiveIndices"]));
	return mat;
}

vector<color_material*>* database_loader::load_color_materials(json const& j)
{
	vector<color_material*>* cms = new vector<color_material*>;
	for (json cm : j)
	{
		cms->push_back(load_color_material(cm));
	}
	return cms;
}


vector<light*>* database_loader::load_lights(json const& j)
{
	vector<light*>* lights = new vector<light*>;
	json temp = j["DirectionalLights"];
	vector<directional_light*>* directionals = load_directional_lights(temp);
	temp = j["PointLights"];
	vector<point_light*>* points = load_point_lights(temp);
	temp = j["SpotLights"];
	vector<spot_light*>* spots = load_spot_lights(temp);
	copy(directionals->begin(), directionals->end(), back_inserter(*lights));
	copy(points->begin(), points->end(), back_inserter(*lights));
	copy(spots->begin(), spots->end(), back_inserter(*lights));
	delete directionals;
	delete points;
	delete spots;
	return lights;
}


vector<directional_light*>* database_loader::load_directional_lights(json const& j)
{
	vector<directional_light*>* lights = new vector<directional_light*>;
	for (json jl : j)
	{
		lights->push_back(load_directional_light(jl));
	}
	return lights;
}


directional_light* database_loader::load_directional_light(json const& j)
{
	directional_light* light = new directional_light(j["id"],parse_vector3(j["Color"]),
		parse_vector3(j["Direction"]));
	return light;
}

vector<point_light*>* database_loader::load_point_lights(json const& j)
{
	vector<point_light*>* lights = new vector<point_light*>;
	for (json jl : j)
	{
		lights->push_back(load_point_light(jl));
	}
	return lights;
}


point_light* database_loader::load_point_light(json const& j)
{
	point_light* light = new point_light(j["id"], parse_vector3(j["Color"]), parse_vector3("0,0,0"), parse_vector3(j["Origin"]));
	return light;
}


vector<spot_light*>* database_loader::load_spot_lights(json const& j)
{
	vector<spot_light*>* lights = new vector<spot_light*>;
	for (json jl : j)
	{
		lights->push_back(load_spot_light(jl));
	}
	return lights;
}

spot_light* database_loader::load_spot_light(json const& j)
{
	spot_light* light = new spot_light(j["id"], parse_vector3(j["Color"]), parse_vector3(j["Direction"]), parse_vector3(j["Origin"]),
		j["FallOff"], j["InnerAngle"], j["OuterAngle"]);
	return light;
}