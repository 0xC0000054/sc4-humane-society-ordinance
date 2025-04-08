////////////////////////////////////////////////////////////////////////////
//
// This file is part of sc4-humane-society-ordinance, a DLL Plugin for
// SimCity 4 that adds a Humane Society ordinance to the game.
//
// Copyright (c) 2023, 2025 Nicholas Hayes
//
// This file is licensed under terms of the MIT License.
// See LICENSE.txt for more information.
//
////////////////////////////////////////////////////////////////////////////

#pragma once
#include "OrdinanceBase.h"

class HumaneSocietyOrdinance final : public OrdinanceBase
{
public:

	HumaneSocietyOrdinance();

	// Sets the name of the ordinance.
	// This is used to allow the value to be translated.
	void SetName(const cIGZString& name);

	// Sets the description of the ordinance.
	// This is used to allow the value to be translated.
	void SetDescription(const cIGZString& description);

	// Gets the monthly income or expense when the ordinance is enabled.
	// This ordinance uses a custom monthly cost calculation of:
	// $-50/month plus $-5 per hospital/clinic.
	int64_t GetCurrentMonthlyIncome() override;

	// Checks if the required conditions have been met for the ordinance
	// to become available in the menu.
	// This ordinance requires the city to have at least one hospital/clinic.
	bool CheckConditions() override;

	// Initializes the ordinance when entering a city.
	bool PostCityInit(cISC4City* pCity) override;

	// Shuts down the ordinance when exiting a city.
	bool PreCityShutdown(cISC4City* pCity) override;

private:

	cISC4ResidentialSimulator* pResidentialSimulator;
};

