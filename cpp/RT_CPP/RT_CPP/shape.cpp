#include "shape.h"
#include "operators.h"

using namespace shapes;

shape::shape(int id,int mid)
	: id(id), material_id(mid)
{

}

int shape::get_id() const
{
	return id;
}

int shape::get_material_id() const
{
	return material_id;
}

vector3 shape::paint(intersection_record& rec, vector<light*>& lights, material* mat, vector3 ambientLight,vector3 viewDir)
{
	vector3 ambientColor = mat->get_ambient_color(id, rec.point);
	vector3 diffuseColor = mat->get_diffuse_color(id, rec.point);
	vector3 specularColor = mat->get_specular_color(id, rec.point);
	float specularity = mat->get_specularity(id, rec.point);

	vector3 color = {0,0,0};
	for (light* l : lights)
	{
		color = color + lightup_material(l, rec, ambientColor, diffuseColor, specularColor, specularity, ambientLight, viewDir);
	}
	color.x = fmaxf(0,fminf(1, color.x));
	color.y = fmaxf(0,fminf(1, color.y));
	color.z = fmaxf(0,fminf(1, color.z));
	return color;
}


vector3 shape::lightup_material(light* light, intersection_record& rec,
	vector3 ambientColor, vector3 diffuseColor, vector3 specularColor, float specularity, vector3 ambientLight,vector3 viewDir)
{
	vector3 reversedLight = -1 * light->get_direction(rec.point);
	vector3 reversedView = -1 * viewDir;
	vector3 normal = get_normal(rec.point);
	vector3 lightColor = light->get_color(rec.point);

	float diffuseMult = vector3::dot(reversedLight , normal);

	vector3 halfway = 0.5f * (reversedView + reversedLight);
	float specularMult = powf( vector3::dot(halfway, normal), specularity);

	vector3 color = (vector3::mult(ambientColor,ambientLight)) + (  diffuseMult * vector3::mult(lightColor,diffuseColor)
		+ (specularMult * vector3::mult(lightColor,specularColor)));
	

	return color;

}


