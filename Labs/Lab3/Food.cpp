#include "Food.h"

//Constructors
	Food::Food(string _type, string _name, int _expYear, float _price, int _calories){
		type = _type;
		name = _name;
		expYear = _expYear;
		price = _price;
		calories = _calories;
	}

	Food::Food(){

	}

//Displays the food with formatting: "Expiration Year    Type Name    $Price    cal"  IE "2019    Vegi Avacado    $5     100 cal"
	void Food::Display() const{
		printf("%d\t%s %s\t$%.0f\t%i cal\n", expYear, type.c_str(), name.c_str(), price, calories);
	}

//Returns string in format of "Year Type Name"  IE "2019 Vegi Avacado"
	string Food::getYearTypeName() const{
		return (to_string(expYear) + " " + type + " " + name);
	}

//Getter for price
	float Food::getPrice() const{
		return price;
	}
