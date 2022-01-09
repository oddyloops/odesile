#pragma once
#include <vector>
#include "light.h"
#include "intersection_record.h"
#include "ray.h"
#include "material.h"

using namespace materials;
using namespace std;
using namespace lights;
using namespace cameras;
namespace shapes

{
	class shape
	{
	private:
		vector3 lightup_material(light* light, intersection_record& rec,
			vector3 ambientColor,vector3 diffuseColor, vector3 specularColor, float specularity, vector3 ambientLight,
			vector3 viewDir, vector<shape*>* shapes, vector<material*>* materials);

		void intersect_shapes(ray r, intersection_record& rec, vector<shape*>* shapes);

		static material* get_material_by_id(int id,vector<material*>* materials);
		static shape* get_shape_by_id(int id,vector<shape*>* shapes);
	protected:
		int id;
		int material_id;

	public:

		shape(int id, int mid);

		int get_id() const;

		int get_material_id() const;

		virtual void intersect(ray r, intersection_record& rec) const = 0;

		virtual vector3 get_normal(vector3 point) const = 0;

		virtual vector3 paint(intersection_record& rec, vector<light*>& lights,vector3 ambientLight,
			vector3 viewDir,int generation, vector<shape*>* shapes,vector<material*>* materials);



	};
}