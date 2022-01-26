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

material* shape::get_material_by_id(int id, vector<material*>* materials)
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

shape* shape::get_shape_by_id(int id, vector<shape*>* shapes)
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
	vector2 uv = get_uv(rec.point);
	vector3 ambientColor = mat->get_ambient_color(uv);
	vector3 diffuseColor = mat->get_diffuse_color(uv);
	vector3 specularColor = mat->get_specular_color(uv);
	float specularity = mat->get_specularity(uv);

	vector3 color = {0,0,0};
	for (light* l : lights)
	{
		color = color + lightup_material(l, rec, ambientColor, diffuseColor, specularColor, specularity, ambientLight, viewDir, shapes, materials);
	}
	color = color.clamp();
	vector3 reflectiveColor = {0,0,0};
	vector3 refractiveColor = {0,0,0};
	vector3 reversedView = -1 * viewDir;

	if (generation > 0)
	{
		float reflectivity = mat->get_reflectivity(uv);
		float transparency = mat->get_transparency(uv);
		float refractIndex = mat->get_refractive_index(uv);
		vector3 normal = get_normal(rec.point);
		if (reflectivity > 0)
		{
			vector3 reflectedDir = ( 2 * vector3::dot(normal, reversedView) * normal - reversedView).normalize();
			ray r;
			r.position = rec.point;
			r.direction = reflectedDir;
			intersection_record reflectRec;
			reflectRec.except_id = id;
			intersect_shapes(r, reflectRec, shapes);
			if (reflectRec.hit)
			{
				shape* reflectShape = get_shape_by_id(reflectRec.shape_id, shapes);
				reflectiveColor = reflectShape->paint(reflectRec, lights, ambientLight, reflectedDir, generation - 1, shapes, materials).clamp();
			}
		}
		if (transparency > 0)
		{
			float cosIncidence = vector3::dot(normal, reversedView);
			float sinIncidence = sinf(acosf(cosIncidence));
			float sinRefract = sinIncidence / refractIndex;
			float cosRefract = cosf(asinf(sinRefract));

			vector3 refractDir = ( - 1 * ((reversedView / refractIndex) + ((cosRefract - (cosIncidence / refractIndex)) * normal))).normalize();
			ray r;
			r.position = rec.point;
			r.direction = refractDir;
			intersection_record refractRec;
			refractRec.except_id = id;
			intersect_shapes(r, refractRec, shapes);
			if (refractRec.hit)
			{
				shape* refractShape = get_shape_by_id(refractRec.shape_id, shapes);
				refractiveColor = refractShape->paint(refractRec, lights, ambientLight, refractDir, generation - 1, shapes, materials).clamp();
			}
		}

		color = ((1 - transparency - reflectivity) * color) + (reflectivity * reflectiveColor) + (transparency * refractiveColor);
	}

	return color.clamp();
}


vector3 shape::lightup_material(light* light, intersection_record& rec,
	vector3 ambientColor, vector3 diffuseColor, vector3 specularColor, float specularity, vector3 ambientLight,vector3 viewDir, vector<shape*>* shapes,
	vector<material*>* materials)
{
	vector3 reversedLight = -1 * light->get_direction(rec.point);
	vector3 reversedView = -1 * viewDir;
	vector3 normal = get_normal(rec.point);
	vector3 lightColor = light->get_color(rec.point);
	ray rr;
	rr.position = rec.point;
	rr.direction = reversedLight;
	intersection_record recs;
	recs.except_id = id;
	intersect_shapes(rr, recs, shapes);
	float shadow_mult = 1;
	if (recs.hit)
	{
		float dist_square = recs.distance * recs.distance;
		if (dist_square < light->light_point_distance(rec.point))
		{
			vector2 uv2 = get_uv(recs.point);
			shape* shadow_shape = get_shape_by_id(recs.shape_id, shapes);
			material* shadow_mat = get_material_by_id(shadow_shape->get_material_id(), materials);
			float shadow_trans = shadow_mat->get_transparency(uv2);
			shadow_mult = shadow_trans;
		}
	}


	float diffuseMult = shadow_mult * fabsf(vector3::dot(reversedLight , normal));


	vector3 halfway = 0.5f * (reversedView + reversedLight);
	float specularMult =shadow_mult * powf( vector3::dot(halfway, normal), specularity);

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


