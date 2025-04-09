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

#include "HumaneSocietyOrdinance.h"
#include "cISC4ResidentialSimulator.h"

// The unique ID that identifies this ordinance.
// The value must never be reused, when creating a new ordinance generate a random 32-bit integer and use that.
static constexpr uint32_t kHumaneSocietyOrdinanceCLSID = 0xc8db12b8;

namespace
{
	OrdinancePropertyHolder CreateOrdinanceEffects()
	{
		OrdinancePropertyHolder properties;

		// Add 5 points to the mayor rating.
		cSCBaseProperty mayorRating(0xaa5b8407, 5);

		properties.AddProperty(&mayorRating, false);

		// Reduce the global crime by 5%.
		cSCBaseProperty crimeEffect(0x28ed0380, 0.95f);

		properties.AddProperty(&crimeEffect, false);

		return properties;
	}
}

HumaneSocietyOrdinance::HumaneSocietyOrdinance()
	: OrdinanceBase(
		kHumaneSocietyOrdinanceCLSID,
		"Humane Society",
		StringResourceKey(0xb5e861d2, 0x890a3afa),
		"Program that provides a city animal shelter. Improves mayor rating and reduces crime.",
		StringResourceKey(0xb5e861d2, 0x1cb1aced),
		/* enactment income */		  -10,
		/* retracment income */       -10,
		/* monthly constant income */ -50,
		/* monthly income factor */   -5.0f,
		/* income ordinance */		  false,
	    CreateOrdinanceEffects())
{
}

int64_t HumaneSocietyOrdinance::GetCurrentMonthlyIncome()
{
	const int64_t monthlyConstantIncome = GetMonthlyConstantIncome();
	const double monthlyIncomeFactor = GetMonthlyIncomeFactor();

	if (!pResidentialSimulator)
	{
		return monthlyConstantIncome;
	}

	// The monthly income factor is multiplied by the number of hospitals and clinics in the city.
	const int32_t hospitalBuildingCount = pResidentialSimulator->GetHospitalBuildingCount();
	const double perHospitalCost = monthlyIncomeFactor * static_cast<double>(hospitalBuildingCount);

	const double monthlyIncome = static_cast<double>(monthlyConstantIncome) + perHospitalCost;

	int64_t monthlyIncomeInteger = 0;

	if (monthlyIncome < std::numeric_limits<int64_t>::min())
	{
		monthlyIncomeInteger = std::numeric_limits<int64_t>::min();
	}
	else if (monthlyIncome > std::numeric_limits<int64_t>::max())
	{
		monthlyIncomeInteger = std::numeric_limits<int64_t>::max();
	}
	else
	{
		monthlyIncomeInteger = static_cast<int64_t>(monthlyIncome);
	}

	logger.WriteLineFormatted(
		LogOptions::OrdinanceAPI,
		"%s: monthly income: constant=%lld, factor=%f, hospital buildings=%d, current=%lld",
		__FUNCTION__,
		monthlyConstantIncome,
		monthlyIncomeFactor,
		hospitalBuildingCount,
		monthlyIncomeInteger);

	return monthlyIncomeInteger;
}

bool HumaneSocietyOrdinance::CheckConditions()
{
	bool result = OrdinanceBase::CheckConditions();

	if (result)
	{
		int32_t hospitalCount = pResidentialSimulator->GetHospitalBuildingCount();

		result = hospitalCount > 0;
	}

	return result;
}

