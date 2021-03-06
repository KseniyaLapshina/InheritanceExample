#include "pch.h"
#include <iostream>
#include <string>
#include <clocale>
using namespace std;

class ComputerGameObject
{
private:
	string title;
public:
	ComputerGameObject(const string& _title) : title(_title) {}
	ComputerGameObject(const ComputerGameObject& obj) : title(obj.title) {}
	~ComputerGameObject() { /*cout << "Object deleted\n" << endl;*/ }
	void print() const
	{
		cout << "\n"<<typeid(*this).name() << ": \n"; 
		_print();
		cout << endl;
	}
	string get_title() const 
	{
		return title;
	}
protected:
	virtual void _print() const 
	{ 
		cout << "\tИмя: " << title; 
	}
};

class Creature :public ComputerGameObject
{
private:
	int healthPoints;
	int attackPower;
	int defense;
	int coordinateX = 0;
	int coordinateY = 0;
public:
	Creature(const string& _title, int _healthPoints, int _attackPower, int _defense) :
		ComputerGameObject(_title), healthPoints(_healthPoints), attackPower(_attackPower), defense(_defense), coordinateX(0), coordinateY(0) {}
	Creature(const string& _title, int _healthPoints, int _attackPower, int _defense, int _coordinateX, int _coordinateY) :
		ComputerGameObject(_title), healthPoints(_healthPoints), attackPower(_attackPower), defense(_defense), coordinateX(_coordinateX), coordinateY(_coordinateY) {}
	Creature(const Creature& obj) :
		ComputerGameObject(obj), healthPoints(obj.healthPoints), attackPower(obj.attackPower), defense(obj.defense), coordinateX(obj.coordinateX), coordinateY(obj.coordinateY) {}
	~Creature() {/* cout << "Creature deleted" << endl; */}

	int getX() const { return coordinateX; }
	int getY() const { return coordinateY; }
	int get_health() const { return healthPoints; }
	virtual void take_damage(int damage) = 0;
protected:
	virtual void _moveOn(int X, int Y) {
		coordinateX += X;
		coordinateY += Y;
	}
	virtual void move(int, int) = 0;
	virtual void _print() const 
	{
		ComputerGameObject::_print();
		cout << "\n\tОчки здоровья: " << healthPoints << "\n\tСила атаки: "<<attackPower<< "\n\tЗащита: " << defense << "\n\tМестонахождение: (" << coordinateX << ", " << coordinateY<< ")";
	}
	void _take_damage(const int damage)
	{
		healthPoints = healthPoints - damage;
	}
};
class Weapon : virtual public ComputerGameObject {
private:
	int damage;
public:
	Weapon(const string _title, const int _damage) : ComputerGameObject(_title), damage(_damage) {}
	Weapon(const Weapon& obj) : ComputerGameObject(obj), damage(obj.damage) {}
	~Weapon() {}
protected:
	virtual void _print() const
	{
		ComputerGameObject::_print();
		cout << "\n\tУрон: " << damage;
	}
};
class Item : virtual public ComputerGameObject {
private:
	int x, y;
	string description;
public:
	Item(const string _title) : ComputerGameObject(_title), x(0), y(0), description("") {}
	Item(const string _title, int x, int y, string description) : ComputerGameObject(_title), x(x), y(y), description(description) {}
	Item(const Item& obj) : ComputerGameObject(obj), description(obj.description) {}
	~Item() {}
protected:
	virtual void _print() const
	{
		ComputerGameObject::_print();
		cout << "\n\tОписание: " << description << "\n\t" << get_title() << " сейчас в точке (" << x << ", " << y << ")\n";
	}
};
class MythicalAnimal : virtual public Creature
{
private:
	string loot;
public:
	MythicalAnimal(const string& _title, int _healthPoints, int _attackPower, int _defense) :
		Creature(_title, _healthPoints, _attackPower, _defense, 0, 0), loot("") {}
	MythicalAnimal(const string& _title, int _healthPoints, int _attackPower, int _defense, int _coordinateX, int _coordinateY, string _loot) :
		Creature(_title, _healthPoints, _attackPower, _defense, _coordinateX, _coordinateY), loot(_loot) {}
	MythicalAnimal(const MythicalAnimal& obj) : Creature(obj), loot(obj.loot) {}
	~MythicalAnimal() {/* cout << "Mythical animal deleted" << endl;*/ }
	void move(int X, int Y) override {
		Creature::_moveOn(X, Y);
		if (X != 0 && Y != 0)
			cout << get_title() << " движется на " << abs(X) << " м. " << (X > 0 ? "вправо" : "влево") << " и на " << abs(Y) << " м. " << (Y > 0 ? "вниз" : "вверх") << endl;
		else if (X != 0)
			cout << get_title() << " движется на " << abs(X) << " м. " << (X > 0 ? "вправо" : "влево")<<endl;
		else if (Y != 0)
			cout << get_title() << " движется на " << abs(Y) << " м. " << (Y > 0 ? "вниз" : "вверх") << endl;
		draw();
	}
	void take_damage(const int damage) override
	{
		Creature::_take_damage(damage);
		cout << get_title() + " получил " + to_string(damage) + " урона. Количество очков жизни: " + to_string(get_health()) + ".\n";
	}
	void draw()
	{
		cout << get_title() << " сейчас в точке (" << getX() << ", " << getY() << ")\n";
		if (getX() == 190 && getY() == 180) {
			cout << get_title() + " врезался в кактус! ";
			take_damage(100);
		}
	}
protected:
	virtual void _print()const
	{
		Creature::_print();
		cout << "\n\tДобыча: " << loot;
	}
};
class Human : virtual public Creature
{
private:
	//Weapon* weaponUSE;
	string weaponUSE;
public:
	/*Human(const string& _title, int _healthPoints, int _attackPower, int _defense, int _coordinateX, int _coordinateY) :
		Creature(_title, _healthPoints, _attackPower, _defense, _coordinateX, _coordinateY), weaponUSE(NULL) {}
	Human(const string& _title, int _healthPoints, int _attackPower, int _defense, int _coordinateX, int _coordinateY, Weapon* _weaponUSE) :
		Creature(_title, _healthPoints, _attackPower, _defense, _coordinateX, _coordinateY), weaponUSE(_weaponUSE) {}
	Human(const Human& obj) : Creature(obj), weaponUSE(obj.weaponUSE) {}*/ 
	//idk, как сделать, чтобы оружие работало из класса т:
	Human(const string& _title, int _healthPoints, int _attackPower, int _defense) :
		Creature(_title, _healthPoints, _attackPower, _defense, 0, 0), weaponUSE("") {}
	Human(const string& _title, int _healthPoints, int _attackPower, int _defense, int _coordinateX, int _coordinateY, string _weaponUSE) :
		Creature(_title, _healthPoints, _attackPower, _defense, _coordinateX, _coordinateY), weaponUSE(_weaponUSE) {}
	Human(const Human& obj) : Creature(obj), weaponUSE(obj.weaponUSE) {}
	~Human() {}

	void move(int X, int Y) override {
		Creature::_moveOn(X, Y);
		if (X != 0 && Y != 0)
			cout << get_title() << " движется на " << abs(X) << " м. " << (X > 0 ? "вправо" : "влево") << " и на " << abs(Y) << " м. " << (Y > 0 ? "вниз" : "вверх") << endl;
		else if (X != 0)
			cout << get_title() << " движется на " << abs(X) << " м. " << (X > 0 ? "вправо" : "влево") << endl;
		else if (Y != 0)
			cout << get_title() << " движется на " << abs(Y) << " м. " << (Y > 0 ? "вниз" : "вверх") << endl;
		draw();
	}
	void take_damage(const int damage) override
	{
		Creature::_take_damage(damage);
		cout << get_title() + " получил " + to_string(damage) + " урона. Количество очков жизни: " + to_string(get_health()) + ".\n";
	}
	/*void take_weapon(Weapon weapon) {
		weaponUSE = new Weapon(weapon);
		print();
	}*/
	void take_weapon(string weapon) {
		cout << get_title() + " нашел оружие! ";
		weaponUSE = weapon;
		print();
	}
	void draw()
	{
		cout << get_title() << " сейчас в точке (" << getX() << ", " << getY() << ")\n";
		if (getX() == 190 && getY() == 180) {
			cout << get_title() + " врезался в кактус! ";
			take_damage(100);
		}
	}
protected:
	virtual void _print()const
	{
		Creature::_print();
		cout << "\n\tОружие: " << weaponUSE;
	}
};

class MagicCharacter : virtual public Creature
{
private:
	string weaponUSE;
	int magicAttackPower;
public:
	MagicCharacter(const string& _title, int _healthPoints, int _attackPower, int _defense) :
		Creature(_title, _healthPoints, _attackPower, _defense, 0, 0), weaponUSE(""), magicAttackPower(0) {}
	MagicCharacter(const string& _title, int _healthPoints, int _attackPower, int _defense, int _coordinateX, int _coordinateY, string _weaponUSE, const int magicAttackPower) :
		Creature(_title, _healthPoints, _attackPower, _defense, _coordinateX, _coordinateY), weaponUSE(_weaponUSE), magicAttackPower(magicAttackPower) {}
	MagicCharacter(const MagicCharacter& obj) : Creature(obj), weaponUSE(obj.weaponUSE), magicAttackPower(obj.magicAttackPower) {}
	~MagicCharacter() {}

	void move(int X, int Y) override {
		Creature::_moveOn(X, Y);
		if (X != 0 && Y != 0)
			cout << get_title() << " движется на " << abs(X) << " м. " << (X > 0 ? "вправо" : "влево") << " и на " << abs(Y) << " м. " << (Y > 0 ? "вниз" : "вверх") << endl;
		else if (X != 0)
			cout << get_title() << " движется на " << abs(X) << " м. " << (X > 0 ? "вправо" : "влево") << endl;
		else if (Y != 0)
			cout << get_title() << " движется на " << abs(Y) << " м. " << (Y > 0 ? "вниз" : "вверх") << endl;
		draw();
	}
	void take_damage(const int damage) override
	{
		Creature::_take_damage(damage);
		cout << get_title() + " получил " + to_string(damage) + " урона. Количество очков жизни: " + to_string(get_health()) + ".\n";
	}
	void take_weapon(string weapon) {
		cout << get_title() + " нашел оружие! ";
		weaponUSE = weapon;
		print();
	}
	void draw()
	{
		cout << get_title() << " сейчас в точке (" << getX() << ", " << getY() << ")\n";
		if (getX() == 190 && getY() == 180) {
			cout << get_title() + " врезался в кактус! ";
			take_damage(100);
		}
	}
protected:
	virtual void _print()const
	{
		Creature::_print();
		cout << "\n\tОружие: " << weaponUSE << "\n\tМагическая атака: " << magicAttackPower;
	}
};
int main()
{
	setlocale(LC_ALL, "ru");
	MythicalAnimal lion("Лев", 1500, 250, 53 , 90, 30, "Шкура льва");
	Human DT("Данилка Тунин", 8060, 354, 230, 0, 0, "");
	//Weapon stick("Палка", 40);
	MagicCharacter SadSausage("Сэдди Соусейдж", 3700, 100, 110, 49, 78, "Посох", 200);
	Item hallucinogenicmushroom("Галлюциногенный гриб", 130, 60, "Необычайно красивый гриб голубого цвета. Часто растет около леса. Чуть погрызан.\n\tНадышавшись его парами, кажется, что Вы уходите от леса, но на деле Вы пробираетесь вглубь, где и умираете, а Ваше тело съедают дикие животные");
	Item mousecorpse("Мышиный труп", 131, 60, "Кажется, этой мышке понравился грибок");

	DT.print();
	DT.move(100, 150);
	DT.take_weapon("Палка");
	SadSausage.print();
	SadSausage.move(-60, -80);

	lion.print();
	lion.move(100, 150);

	hallucinogenicmushroom.print();
	mousecorpse.print();

	return 0;
}