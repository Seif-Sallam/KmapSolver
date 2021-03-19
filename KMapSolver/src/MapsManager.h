#pragma once
#include "Kmap.h"
#include "TruthTable.h"

namespace KM {

	//A very simple class to manage which table to be updated
	class MapsManager
	{
	public:
		//constructor that takes a reference to the truth table and the kmap
		MapsManager(TruthTable& table, Kmap& kmap);

		//The main and only function in this class that determines which to be updated
		void UpdateInTheOther(uint16_t change);
	private:
		TruthTable& table;
		Kmap& kmap;
	};
}

