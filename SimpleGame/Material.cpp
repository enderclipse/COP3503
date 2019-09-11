//
// Created by JOSHUA HADDAD on 2019-04-10.
//

#include "Material.h"

Material::Material(float density, float restitution) {
    density_ = density;
    restitution_ = restitution;
}

float Material::GetDensity() {
    return density_;
}

float Material::GetRestitution() {
    return restitution_;
}

Material::Material() {
    density_ = 0;
    restitution_ = 0;
}

void Material::SetDensity(float density) {
    density_ = density;

}
