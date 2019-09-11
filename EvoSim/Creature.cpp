//
// Created by JOSHUA HADDAD on 2019-05-06.
//

#include "Creature.h"

Creature::Creature() {
    health_ = 0;
    speed_ = 0;
    energy_ = 0;
}

Creature::Creature(int health, int speed, int energy) {
    health_ = health;
    speed_ = speed;
    energy_ = energy;
}

Creature Creature::Reproduce(Creature& partner) {
    Creature child;

    //Loop through each gene in the gene map for creature 1
    for(auto& gene : genes_){
        //Check if the corresponding gene type is in the other creature.  If not, add the gene with no blending
        if(partner.genes_.find(gene.first) == partner.genes_.end()) {
            child.AddGene(gene.first, genes_[gene.first]);
            continue;
        } else {

            //Mix the genes
            Gene new_gene = Gene::MixGene(gene.second, partner.genes_[gene.first]);

            //Add the new gene to the child
            child.AddGene(gene.first, new_gene);
        }
    }

    return child;
}

void Creature::Move(int x, int y) {
    x_ += x;
    y_ += y;
    energy_ -= 5*(x+y)/speed_;
}

void Creature::SetLocation(int x, int y){
    x_ = x;
    y_ = y;
}

void Creature::AddGene(string identifier, Gene& gene) {
    genes_.emplace(identifier, gene);
}

bool Creature::CheckDeath() {
    return (health_ < 0);
}

void Creature::PrintCreature() {
    cout << "Information for " << name_ << ":" << endl;
    cout << "Health: " << health_ << endl;
    cout << "Energy: " << energy_ << endl;
    cout << "Speed: " << speed_ << endl;
    cout << "Strength: " << strength_ << endl;
    cout << "Dexterity: " << dexterity_ << endl;
}

void Creature::Fight(Creature& partner) {
    while(health_ > 0 && partner.health_ > 0){
        int damage_this = (int) strength_;
        int damage_partner = (int) strength_;

        //TODO mechanics for dodging
        bool this_dodged = false;
        bool partner_dodged = false;

        if(!this_dodged)
            health_ -= damage_partner;

        if(!partner_dodged)
            partner.health_ -= damage_this;

    }
}

void Creature::Eat(float energy_value) {
    energy_ += energy_value;
}

int Creature::GetX() {
    return x_;
}

int Creature::GetY() {
    return y_;
}

void Creature::SetX(int x) {
    x_ = x;
}

bool Creature::CheckLocation(int x, int y) {
    return (x_ == x && y_ == y);
}

void Creature::SetY(int y) {
    y_ = y;
}

Gene Gene::MixGene(Gene& gene_one, Gene& gene_two) {
    Gene new_gene;
    new_gene.dominance_ = (gene_one.dominance_ + gene_two.dominance_)/2;
    new_gene.identifier_ = gene_one.identifier_;

    new_gene.health_modifier_ = CalculateModifier(gene_one.health_modifier_, gene_one.dominance_,
            gene_two.health_modifier_, gene_two.dominance_);

    new_gene.energy_modifier_ = CalculateModifier(gene_one.energy_modifier_, gene_one.dominance_,
                                                  gene_two.energy_modifier_, gene_two.dominance_);

    new_gene.speed_modifier_ = CalculateModifier(gene_one.speed_modifier_, gene_one.dominance_,
                                                  gene_two.speed_modifier_, gene_two.dominance_);

    return new_gene;
}


float Gene::CalculateModifier(float modifier_one, float modifier_two, float dominance_one, float dominance_two) {
    return (modifier_one*dominance_one + modifier_two*dominance_two)/2;
}
