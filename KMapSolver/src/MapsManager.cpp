#include "MapsManager.h"

KM::MapsManager::MapsManager(TruthTable& table, Kmap& kmap)
	: table(table), kmap(kmap)
{
}

void KM::MapsManager::UpdateInTheOther(uint16_t change)
{
	if (change == 1)
		kmap.ReConfig();
	else
		table.ReConfig();
}
