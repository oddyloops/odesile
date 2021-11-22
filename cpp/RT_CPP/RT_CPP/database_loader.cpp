#include "database_loader.h"
#include "orthographic.h"
#include "perspective.h"
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


scene_database* database_loader::load(string file)
{
	ifstream in(file.c_str());
	json j;
	in >> j;
	json temp = j["Scene"];
	scene* scn = load_scene(temp);
	temp = j["Camera"];
	camera* cam = load_camera(temp,scn->get_width(),scn->get_height());
	vector<shape*>* shapes = new vector<shape*>;

	temp = j["Shapes"]["Spheres"];
	vector<sphere*>* spheres = load_spheres(temp);
	copy(spheres->begin(), spheres->end(), back_inserter(*shapes));
	delete spheres;

	scene_database* db = new scene_database();
	db->set_camera(cam);
	db->set_scene(scn);
	db->set_shapes(shapes);
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
	sphere* sph = new sphere(j["id"],
		parse_vector3(j["center"]),
		j["radius"]);
	return sph;
}