#include "Player.h"

player::player() 
{

}
player::~player()
{
	// Still to be implemented
}

void player::setCover(string position, bool value) // does it have cover? value associated? 
{
	BoardToArray(position);
	Cover[getCoord(0)][getCoord(1)] = value;
}

void player::setHasMoved(bool moved) // has it moved y/n
{
	HasMoved = moved; // this function can be called with a true false input put in, within another function and or main?
}

void player::setMoveDistance(string old_pos, string new_pos) // how much can it move staying at 1 just now.
{
	MoveDistance = 1;

}

void player::setHealth(int hp)
{
	Health = hp;
}

void player::setUnits(int unit)
{
	Cover.resize(getTiles_Size());
	for (int i = 0; i < getTiles_Size(); i++) {
		Cover[i].resize(getTiles_Size());
	}

	Units.resize(unit);
	char unit_type = NULL;
	string coordinate;

	for (int z = 0; z < getUnits(); z++) 
	{
		switch (z) {

		case 0:
		case 3:
			unit_type = 'I';
			break;

		case 1:
		case 4:
			unit_type = 'S';
			break;

		case 2:
		case 5:
			unit_type = 'P';
			break;
		}

		cout << "Type: " << unit_type << endl;
		cout << "Enter the coordinate you want the unit to be placed at, ie : A1" << endl;
		cin >> coordinate;
		setHasUnit(coordinate, unit_type); //sets the position of this unit
	}
}

bool player::getCover(string position) // returns a boolean 0 = no
{
	BoardToArray(position);
	return Cover[getCoord(0)][getCoord(1)];
}

bool player::getHasMoved() // returns if it has moved 1b= if yes
{
	if (HasMoved == true) // if loop to inform the user that that unit has moved or not.
	{
		cout << "player has moved! \n";
	}
	else
	{
		cout << "Unit has not moved! \n";
	}
	return HasMoved;
}

bool player::DistanceVerify(string old_pos, string new_pos) // Verifies that the user is only moving one tile
{
	BoardToArray(old_pos);
	int old_y = getCoord(0);
	int old_x = getCoord(1);
	BoardToArray(new_pos);
	int diff_sum = (getCoord(0) + getCoord(1)) - (old_x + old_y);
	cout << "diff_sum: " << diff_sum << endl;

	if ((diff_sum > 1) || (diff_sum < -1)) {
		cout << "Unit cannot move that far, please enter a new coordinate: ";
		return false;
	}
	return true;
}

bool player::TerrainVerify(string old_pos, string new_pos)
{
	switch (getHasUnit(old_pos)) {
	case 'I':
		if (getTerrain(new_pos) != true) {
			cout << "Error! Invalid terrain...";
			return false;
		}
		break;

	case 'S':
		if (getTerrain(new_pos) != false) {
			cout << "Error! Invalid terrain...";
			return false;
		}
		break;

	case NULL:
		cout << "No unit at selected coordinate..." << endl;
		return false;
	}
	return true;
}

int player::getHealth()
{
	return Health;
}

int player::getUnits()
{
	return Units.size();
}

string player::PlayerTurn()
{
	string playerturn, old_coordinate, new_coordinate, target, code;

	cout << "What would you like to do this turn?" << endl;
	cout << "[1] Move a unit" << endl << "[2] fire at the other player" << endl << "[3] end turn" << endl;
	cin >> playerturn; // needs validation,

	switch (stoi(playerturn)) {
	case 1:
		cout << "Enter the coordinate of the unit you want to move: ";
		cin >> old_coordinate;
		cout << "Enter the coordinate you want the unit to move to: ";
		cin >> new_coordinate;
		while (PlayerMove(old_coordinate, new_coordinate) == false) {
			cout << "Enter the coordinate of the unit you want to move: ";
			cin >> old_coordinate;
			cout << "Enter the coordinate you want the unit to move to: ";
			cin >> new_coordinate;
		}
		setHasMoved(true); // sets that the player will have moved
		code = "move";
		return code;
		break;

	case 2:
		cout << "enter the coordinate to target: ";
		cin >> target;
		return target;
		break;

	case 3:
		cout << "Turn ended..." << endl;
		code = "endturn";
		return code;
		break;

	default:
		cout << "Invalid command entered..." << endl;
		code = "error";
		return code;
		break;
	}
}

void player::PlayerAttacked(string target) // Method called when opponent attacks a tile
{ 
	string newtarget; 

	if (BoardToArray(target) == true)
	{
		if (getHasUnit(target) != NULL) {
			cout << "Hit!" << endl;
			setHasUnit(target, NULL);
			setTiles(target, 'X');
		}
		else {
			cout << "Attack missed..." << endl;
		}
	}
	else
	{
		while (BoardToArray(newtarget) != true)
		{
			cout << "Please enter a valid coordinate: ";
			cin >> newtarget;
			BoardToArray(newtarget);
		}
	}
}

bool player::PlayerMove(string old_pos, string new_pos) // Method for user to move
{
	if (getHasUnit(old_pos) != NULL) { 
		if (DistanceVerify(old_pos, new_pos) == true && TerrainVerify(old_pos, new_pos) == true) {
			UpdateTiles(old_pos, new_pos);
			return true;
		}
		else {
			cout << "Verification failure, please re-enter coordinates..." << endl;
			return false;
		}
	}
	else {
		cout << "no unit present at the coordinate" << endl;
		return false;
	}
}