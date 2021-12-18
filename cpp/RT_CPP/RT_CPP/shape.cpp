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

material* get_material_by_id(int id, vector<material*>* materials)
{
	for (material* mat : *materials)
	{
		if (mat->get_id() == id)
		{
			return mat;
		}
	}
	return nullptr;
}

shape* get_shape_by_id(int id, vector<shape*>* shapes)
{
	for (shape* shp : *shapes)
	{
		if (shp->get_id() == id)
		{
			return shp;
		}
	}
	return nullptr;
}

vector3 shape::paint(intersection_record& rec, vector<light*>& lights, vector3 ambientLight,vector3 viewDir,int generation, vector<shape*>* shapes, vector<material*>* materials)
{
	material* mat = get_material_by_id(material_id,materials);
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
	vector3 reflectiveColor = {0,0,0};
	vector3 refractiveColor = {0,0,0};

	if (generation > 0)
	{
		float reflect = mat->get_reflectivity(id, rec.point);
		float transparency = mat->get_transparency(id, rec.point);
		vector3 normal = get_normal(rec.point);
		if (reflect > 0)
		{
			vector3 reflectedDir = ( 2 * vector3::dot(normal, viewDir) * normal - viewDir).normalize();
			ray r;
			r.position = rec.point;
			r.direction = reflectedDir;
			intersection_record reflectRec;
			intersect_shapes(r, reflectRec, shapes);
			if (reflectRec.hit)
			{
				shape* reflectShape = get_shape_by_id(reflectRec.shape_id, shapes);
				reflectiveColor = reflectShape->paint(reflectRec, lights, ambientLight, reflectedDir, generation - 1, shapes, materials);
			}
		}
		if (transparency > 0)
		{

		}
	}

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

void shape::intersect_shapes(ray r, intersection_record& rec, vector<shape*>* shapes)
{
	for (shape* s : *shapes)
	{
		s->intersect(r, rec);
	}
}


